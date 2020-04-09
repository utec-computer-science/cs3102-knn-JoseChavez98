#include "kd_tree.h"
#include "node.h"
#include <queue>

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
  //   std::cout << "root - > " << this->root->first << '\n';

  for (size_t iterator = 0; iterator < this->numberOfPoints; iterator++) {
    if (iterator != (numberOfPoints / 2) - 1)
      insert(this->root, this->points[iterator]);
  }
}

template <class X, class Y> Kd_tree<X, Y>::~Kd_tree() {}

template <class X, class Y>
void Kd_tree<X, Y>::insert(node<X, Y> *output, node<X, Y> *input) {

  if (output == nullptr)
    return;

  if (this->switchForLevels) {
    if (output->first <= input->first) {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << "entre DERECHA con " << input->first << ";" <<
      //             input->second
      //             << '\n';
      if (output->right != nullptr) {
        this->switchForLevels = !switchForLevels;
        insert(output->right, input);
      } else {
        output->right = input;
        this->switchForLevels = true;
        return;
      }
    } else {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << " entre IZQUIERA con " << input->first << ";"
      //             << input->second << '\n';
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
    // std::cout << "entre Y\n";
    if (output->second <= input->second) {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << "entre DERECHA con " << input->first << ";" <<
      //             input->second
      //             << '\n';
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
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << " entre IZQUIERA con " << input->first << ";"
      //             << input->second << '\n';
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

template <class X, class Y> void Kd_tree<X, Y>::print() {
  printPostOrder(this->root);
}

template <class X, class Y>
void Kd_tree<X, Y>::printPostOrder(node<X, Y> *Node) {
  if (Node == nullptr)
    return;

  printPostOrder(Node->left);
  printPostOrder(Node->right);
  std::cout << Node->first << "," << Node->second << " --> ";
}

template <class X, class Y>
node<X, Y> *Kd_tree<X, Y>::reachLastValidNode(node<X, Y> *output,
                                              node<X, Y> *input) {
  
  if (this->switchForLevels) {
    if (output->first <= input->first) {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << "entre DERECHA con " << input->first << ";" <<
      //             input->second
      //             << '\n';
      if (output->right != nullptr) {
        this->switchForLevels = !switchForLevels;
        reachLastValidNode(output->right, input);
      } else {
        this->switchForLevels = true;
        return output;
      }
    } else {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << " entre IZQUIERA con " << input->first << ";"
      //             << input->second << '\n';
      if (output->left != nullptr) {
        this->switchForLevels = !switchForLevels;

        reachLastValidNode(output->left, input);
      }

      else {
        this->switchForLevels = true;
        return output;
      }
    }
  } else {
    // std::cout << "entre Y\n";
    if (output->second <= input->second) {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << "entre DERECHA con " << input->first << ";" <<
      //             input->second
      //             << '\n';
      if (output->right != nullptr) {
        this->switchForLevels = !switchForLevels;

        reachLastValidNode(output->right, input);
      }

      else {
        this->switchForLevels = true;
        return output;
      }
    } else {
      //   std::cout << "output: " << output->first << ":" << output->second
      //             << " entre IZQUIERA con " << input->first << ";"
      //             << input->second << '\n';
      if (output->left != nullptr) {
        this->switchForLevels = !switchForLevels;
        reachLastValidNode(output->left, input);
      }

      else {
        this->switchForLevels = true;
        return output;
      }
    }
  }
}

template <class X, class Y>
std::vector<node<X, Y> *>
Kd_tree<X, Y>::computeNearestSamples(int k, node<X, Y> *objet) {
    
    std::priority_queue<node<X, Y> *, std::vector<node<X,Y>*>, CompareNode<X,Y>>nearestPoints;
    
      auto lastNode=reachLastValidNode(this->root,objet);
      std::cout<<'\n'<<lastNode->first<<'\n';
      
      
      
      std::vector<node<X, Y> *>finalKSamples;
      return finalKSamples;
}

template <class X, class Y>
void Kd_tree<X, Y>::printNearestSamples(
    std::vector<node<X, Y> *> nearestPoints) {}
