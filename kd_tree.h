#ifndef KD_TREE_H
#define KD_TREE_H

#include <fstream>
#include <iostream>
#include <string>

#include "node.h"
#include "quicksort.h"

template <class X, class Y> class Kd_tree {

private:
  node<X, Y> *root;
  int numberOfPoints = 0;
  node<X, Y> **points;
  bool switchForLevels = true;

public:
  Kd_tree() = default;
  explicit Kd_tree(const std::string &filename);
  ~Kd_tree();

  void insert(node<X, Y> *output, node<X, Y> *input);
  void print();
  void printPostOrder(node<X, Y> *root);
  std::vector<node<X, Y> *> computeNearestSamples(int k, node<X, Y> *objet);
  void printNearestSamples(std::vector<node<X, Y> *> nearestPoints);
  node<X, Y> *reachLastValidNode(node<X, Y> *output, node<X, Y> *input);
};

#endif