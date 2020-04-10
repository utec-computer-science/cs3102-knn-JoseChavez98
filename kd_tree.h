#ifndef KD_TREE_H
#define KD_TREE_H

#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#include "node.h"
#include "quicksort.h"

template <class X, class Y> class Kd_tree {

private:
  node<X, Y> *root;
  int numberOfPoints = 0;
  node<X, Y> **points;
  bool switchForLevels = true;
  std::priority_queue<DistanceAndNode<X, Y> *,
                      std::vector<DistanceAndNode<X, Y> *>, CompareNode<X, Y>>
      nearestSamples;

public:
  Kd_tree() = default;
  explicit Kd_tree(const std::string &filename);
  ~Kd_tree();

  void insert(node<X, Y> *output, node<X, Y> *input);
  void print();
  void printPostOrder(node<X, Y> *root);
  void computeNearestSamples(node<X, Y> *root, node<X, Y> *objet, int k);
  void getNearestSamples(int k, node<X, Y> *object);
  void insertQueue(DistanceAndNode<X, Y> *object, int k);
  bool checkBadSide(node<X, Y> *n, node<X, Y> *object, bool x);
};

#endif