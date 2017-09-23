#include "circularlinkedList.h"

template<typename T>
bool isomorphic_circularlinkedList(circularlinkedList<T>* M1, circularlinkedList<T> *M2) {
  /*assume one of input parameters has not null.
    because assistant's code is always right.*/
  if(M1 == NULL && M2 == NULL) return true;
  if(M1 == NULL || M2 == NULL) return false;

  return isomorphic_node(M1->root, M2->root);
}
