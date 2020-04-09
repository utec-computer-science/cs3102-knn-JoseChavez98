#ifndef NODE_H
#define NODE_H

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

template <class X, class Y> 
struct CompareNode {
  bool operator()(node<X, Y> *n1, node<X, Y> *n2) const {
    if (n1->first < n2->first)
      return true;
    else if (n1->first == n2->first) {
      if (n1->second < n2->second)
        return true;
    }
    return false;
  }
};



#endif