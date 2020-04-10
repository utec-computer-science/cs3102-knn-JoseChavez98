#include "kd_tree.h"
#include "node.h"
#include <queue>

/**
 * @brief Construct a new Kd_tree<X, Y>::Kd_tree object
 * 
 * @tparam X : type of point's first coord.
 * @tparam Y : type of point's second coord.
 * @param filename : name of the input .txt file(points) 
 */
template <class X, class Y>
Kd_tree<X, Y>::Kd_tree(const std::string &filename) {
  std::fstream basicFstream(filename, std::ios::in);
  std::string line;
  getline(basicFstream, line);
  this->numberOfPoints = std::stoi(line);

  this->points = new node<X, Y> *[this->numberOfPoints];

  std::string coord;
  bool switchForInput = true;
  auto *inputNode = new node<X, Y>;
  int positionInVector = 0;
  while (basicFstream >> coord) {

    switch (switchForInput) {
    case true:
      inputNode->first = std::stoi(coord);
      switchForInput = false;
      break;

    case false:
      switchForInput = true;
      inputNode->second = std::stoi(coord);
      this->points[positionInVector] = inputNode;
      positionInVector++;
      inputNode = new node<X, Y>;
      break;
    }
  }
  quickSort<X, Y>(this->points, 0, this->numberOfPoints - 1);

  this->root = this->points[(numberOfPoints / 2) - 1];
  
  for (size_t iterator = 0; iterator < this->numberOfPoints; iterator++) {
    if (iterator != (numberOfPoints / 2) - 1)
      insert(this->root, this->points[iterator]);
  }
}

/**
 * @brief Destroy the Kd_tree<X, Y>::Kd_tree object
 * 
 * @tparam X 
 * @tparam Y 
 */
template <class X, class Y> Kd_tree<X, Y>::~Kd_tree() {}

/**
 * @brief Insert recursively a new Node or point or sample
 * 
 * @tparam X 
 * @tparam Y 
 * @param output : current node
 * @param input : the node we are inserting 
 */
template <class X, class Y>
void Kd_tree<X, Y>::insert(node<X, Y> *output, node<X, Y> *input) {

  if (this->switchForLevels) {
    if (output->first <= input->first) {
      
      if (output->right != nullptr) {
        this->switchForLevels = !switchForLevels;
        insert(output->right, input);
      } else {
        output->right = input;
        this->switchForLevels = true;
        return;
      }
    } else {
      
      if (output->left != nullptr) {
        this->switchForLevels = !switchForLevels;

        insert(output->left, input);
      }

      else {
        output->left = input;
        this->switchForLevels = true;

        return;
      }
    }
  } else {
    if (output->second <= input->second) {
     
      if (output->right != nullptr) {
        this->switchForLevels = !switchForLevels;

        insert(output->right, input);
      }

      else {
        output->right = input;
        this->switchForLevels = true;

        return;
      }
    } else {
    
      if (output->left != nullptr) {
        this->switchForLevels = !switchForLevels;
        insert(output->left, input);
      }

      else {
        output->left = input;
        this->switchForLevels = true;

        return;
      }
    }
  }
  this->switchForLevels = true;
}

/**
 * @brief Calls the recursive function for printing the tree
 * 
 * @tparam X 
 * @tparam Y 
 */
template <class X, class Y> void Kd_tree<X, Y>::print() {
  printPostOrder(this->root);
}

/**
 * @brief Prints tree recursively in PostOrder 
 * 
 * @tparam X 
 * @tparam Y 
 * @param Node : current node we are at
 */
template <class X, class Y>
void Kd_tree<X, Y>::printPostOrder(node<X, Y> *Node) {
  if (Node == nullptr)
    return;

  printPostOrder(Node->left);
  printPostOrder(Node->right);
  std::cout << Node->first << "," << Node->second << " --> ";
}

/**
 * @brief Search recursively for the nearest samples
 * 
 * @tparam X 
 * @tparam Y 
 * @param root : current node we are at
 * @param object : Sample wich neighbors will be found
 * @param k : Number of neighbors required
 */
template <class X, class Y>
void Kd_tree<X, Y>::computeNearestSamples(node<X, Y> *root, node<X, Y> *object,
                                          int k) {

  if (root == nullptr)
    return;

  if (this->switchForLevels) {
    if (root->first <= object->first) {
      if (root->right != nullptr) {
        this->switchForLevels = !switchForLevels;
        computeNearestSamples(root->right, object, k);
        if (checkBadSide(root->left, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->left, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
      } else {
        if (checkBadSide(root->left, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->left, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
        this->switchForLevels = true;
        return;
      }
    } else {
      if (root->left != nullptr) {
        this->switchForLevels = !switchForLevels;
        computeNearestSamples(root->left, object, k);
        if (checkBadSide(root->right, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->right, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
      }

      else {
        if (checkBadSide(root->right, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->right, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
        this->switchForLevels = true;
        return;
      }
    }
  } else {
    if (root->second <= object->second) {
      if (root->right != nullptr) {
        this->switchForLevels = !switchForLevels;
        computeNearestSamples(root->right, object, k);
        if (checkBadSide(root->left, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->left, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
      } else {
        if (checkBadSide(root->left, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->left, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
        this->switchForLevels = true;
        return;
      }
    } else {

      if (root->left != nullptr) {
        this->switchForLevels = !switchForLevels;
        computeNearestSamples(root->left, object, k);
        if (checkBadSide(root->right, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->right, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
      } else {
        if (checkBadSide(root->right, object, this->switchForLevels)) {
          this->switchForLevels = !switchForLevels;
          computeNearestSamples(root->right, object, k);
        }
        auto DistanceAndNodeTemp =
            new DistanceAndNode<X, Y>(pointDistance<X, Y>(root, object), root);
        insertQueue(DistanceAndNodeTemp, k);
        this->switchForLevels = true;
        return;
      }
    }
  }
  this->switchForLevels = true;
}

/**
 * @brief Calls the recursive function to find neighbors and print them.
 * 
 * @tparam X 
 * @tparam Y 
 * @param k : Number of neighbors required
 * @param object : Sample wich neighbors will be found
 */
template <class X, class Y>
void Kd_tree<X, Y>::getNearestSamples(int k, node<X, Y> *object) {

  computeNearestSamples(this->root, object, k);

  auto samples = this->nearestSamples;

  while (!samples.empty()) {
    std::cout << '(' << samples.top()->object->first << ","
              << samples.top()->object->second << ") - ";
    samples.pop();
  }
}

/**
 * @brief Insert element in our queue of NN
 * 
 * @tparam X 
 * @tparam Y 
 * @param object : same
 * @param k : same
 */
template <class X, class Y>
void Kd_tree<X, Y>::insertQueue(DistanceAndNode<X, Y> *object, int k) {
  if (this->nearestSamples.size() <= k) {
    this->nearestSamples.push(object);
  } else {
    if (this->nearestSamples.top()->distance > object->distance) {
      this->nearestSamples.pop();
      this->nearestSamples.push(object);
    }
  }
}

/**
 * @brief check if the bad side of the node is worth of traverse.
 * 
 * @tparam X 
 * @tparam Y 
 * @param n : current  node we are at
 * @param object :same
 * @param x : switch to check if we are in X or Y level of tree.
 * @return true : If is worth checking this side 
 * @return false : !(If is worth checking this side)
 */
template <class X, class Y>
bool Kd_tree<X, Y>::checkBadSide(node<X, Y> *n, node<X, Y> *object, bool x) {
  if (n == nullptr)
    return false;
  if (x) {
    auto temp = new node<X, Y>(object->first, n->second);
    auto distance = pointDistance<X, Y>(temp, object);
    if (distance < this->nearestSamples.top()->distance)
      return true;
    return false;
  } else {
    auto temp = new node<X, Y>(n->first, object->second);
    auto distance = pointDistance<X, Y>(temp, object);
    if (distance < this->nearestSamples.top()->distance)
      return true;
    return false;
  }
}