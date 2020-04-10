#ifndef NODE_H
#define NODE_H

#include <cmath>

template <class X, class Y> struct node {
  int first{};
  int second{};
  node *left = nullptr;
  node *right = nullptr;
  node() = default;
  ;
  node(X x, Y y) {
    first = x;
    second = y;
  }
};

template <class X, class Y> struct DistanceAndNode {
  double distance;
  node<X, Y> *object;
  DistanceAndNode() = default;
  DistanceAndNode(double d, node<X, Y> *o) {
    distance = d;
    object = o;
  }
};

template <class X, class Y> struct CompareNode {
  bool operator()(DistanceAndNode<X, Y> *n1, DistanceAndNode<X, Y> *n2) const {
    return n1->distance < n2->distance;
  }
};

template <class X, class Y>
double pointDistance(node<X, Y> *n1, node<X, Y> *n2) {
  auto distance =
      sqrt(pow((n2->first - n1->first), 2) + pow((n2->second - n1->second), 2));
  return distance;
}

template <class X, class Y> void printNode(node<X, Y> *n) {
  std::cout << "(" << n->first << ',' << n->second << ")\n";
}

#endif