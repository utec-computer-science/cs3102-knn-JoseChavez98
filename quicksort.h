

#include "node.h"
#include "vector"
#include <iostream>

template <class X, class Y> void swap(node<X, Y> *a, node<X, Y> *b) {
  //    std::cout<<a->first<<":"<<a->second<<"<->"<<b->first<<":"<<b->second<<'\n';

  auto *t = new node<X, Y>;
  t->first = a->first;
  t->second = a->second;
  a->first = b->first;
  a->second = b->second;
  b->first = t->first;
  b->second = t->second;
  //    std::cout<<a->first<<":"<<a->second<<"<->"<<b->first<<":"<<b->second<<'\n';
  //    std::cout<<'\n';
}

template <class X, class Y> bool compare(node<X, Y> *a, node<X, Y> *b) {
  if (a->first < b->first)
    return true;
  else if (a->first == b->first) {
    if (a->second < b->second)
      return true;
  }
  return false;
}

template <class X, class Y> int partition(node<X, Y> **arr, int low, int high) {
  node<X, Y> *pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (compare(arr[j], pivot)) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

template <class X, class Y>
void quickSort(node<X, Y> **arr, int low, int high) {
  if (low < high) {

    int pi = partition<X, Y>(arr, low, high);

    // Separately sort elements before
    // partition and after partition
    quickSort<X, Y>(arr, low, pi - 1);
    quickSort<X, Y>(arr, pi + 1, high);
  }
}
