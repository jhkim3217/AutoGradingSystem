#include <iostream>
#pragma once

template<typename T>
class binary_node
{
public:
  T value;
  binary_node* left;
  binary_node* right;
public:
  binary_node(T);
  ~binary_node();

  void  setValue(T);
  void  setLeft(binary_node*);
  void  setRight(binary_node*);

  T   getValue();
  binary_node* getLeft();
  binary_node* getRight();
};

/*declaration*/
template<typename T>
binary_node<T>::binary_node(T _value = 0): value(_value), left(NULL), right(NULL) {}

template<typename T>
binary_node<T>::~binary_node() {
  left=NULL;
  right=NULL;
}

template<typename T>
void binary_node<T>::setValue(T value) {
  this->value = value;
}

template<typename T>
void binary_node<T>::setLeft(binary_node* left) {
  this->left = left;
}

template<typename T>
void binary_node<T>::setRight(binary_node* right) {
  this->right = right;
}

template<typename T>
T binary_node<T>::getValue() {
  return this->value;
}

template<typename T>
binary_node<T>* binary_node<T>::getLeft() {
  return this->left;
}

template<typename T>
binary_node<T>* binary_node<T>::getRight() {
  return this->next;
}

template<typename T>
binary_node<T>* getParent(binary_node<T>* root, binary_node<T>* target) {
  if(root == target) return NULL;

  binary_node<T>* parent = root;
  while(true) {
    if(parent->value < target->value) {
      if(parent->right != target) parent = parent->right;
      else return parent;
    }
    else {
      if(parent->left != target) parent = parent->left;
      else return parent;
    }
  }
}

template<typename T>
class bst
{
public:
  binary_node<T> *root;
public:
  bst();
  ~bst();

  bool insert(T);
  binary_node<T>* search(T);
  bool update(T, T);
  bool _delete(T);
};

template<typename T>
bst<T>::bst() {
  this->root = NULL;
}

template<typename T>
bst<T>::~bst() {
  delete this->root;
}

template<typename T>
bool bst<T>::insert(T value) {
  binary_node<T> *horse = this->root;
  if(root == NULL) root = new binary_node<T>(value);
  else {
    while(horse) {
      if(horse->value < value) {
        if(horse->right) horse = horse->right;
        else {
          horse->right = new binary_node<T>(value);
          return true;
        }
      }
      else {
        if(horse->left) horse = horse->left;
        else {
          horse->left = new binary_node<T>(value);
          return true;
        }
      }
    }
  }
  return true;
}

template<typename T>
binary_node<T>* bst<T>::search(T value) {
  binary_node<T> *horse = this->root;
  while(horse) {
    if(horse->value == value) return horse;
    else if(horse->value < value) horse = horse->right;
    else horse = horse->left;
  } return NULL;
}

template<typename T>
bool bst<T>::update(T oldValue, T newValue) {
  binary_node<T> *horse = search(oldValue);
  if(horse == NULL) return false;
  horse->value = newValue;
  return true;
}

template<typename T>
bool bst<T>::_delete(T value) {
  binary_node<T> *horse = search(value);
  binary_node<T> *target = search(value);
  binary_node<T> *parent_target = NULL;
  binary_node<T> *prev = this->root;
  binary_node<T> *candidate = NULL;
  binary_node<T> *prev_candidate = NULL;

  if(horse == NULL) return false;

  if(horse->left && horse->right) {
    /*Step 1 : find prev */
    if(horse!=root) prev = NULL;
    else while(prev) {
      if(prev->value < value) {
        if(prev->right != horse) prev = prev->right;
        else break;
      }
      else {
        if(prev->left != horse) prev = prev->left;
        else break;
      }
    }

    /*Step 2 : find prev_candidate, candidate*/
    candidate = horse->left;
    if(candidate->right) {
      prev_candidate = candidate;
      candidate = candidate->right;
    }

    /*Step 3 : rebuilding */
    if(prev_candidate) {
      prev_candidate->right = candidate->left;
      if(prev) {
        candidate->left = horse->left;
        candidate->right = horse->right;
        if(prev->left == horse) prev->left = candidate;
        else prev->right = candidate;
      }
      else {
        candidate->left = root->left;
        candidate->right = root->right;
        root=candidate;
      }
    }
    else {
      if(prev) {
        candidate->right = horse->right;
        if(prev->left == horse) prev->left = candidate;
        else prev->right = candidate;
      }
      else {
        candidate->right = root->right;
        root=candidate;
      }
    }
    delete horse;
  }
  else if(horse->left) {
    parent_target = getParent(root, target);
    if(parent_target) {
      if(parent_target->left == target) parent_target->left = target->left;
      else parent_target->right = target->left;
    }
    else root = target->left;
    delete target;
  }
  else if(target->right) {
    parent_target = getParent(root, target);
    if(parent_target) {
      if(parent_target->left == target) parent_target->left = target->right;
      else parent_target->right = target->right;
    }
    else root = target->right;
    delete target;
  }
  else {
    parent_target = getParent(root, target);

    if(parent_target) {
      if(parent_target->left == target) parent_target->left = NULL;
      else parent_target->right = NULL;
    }
    else root=NULL;
    delete target;
  }
  return true;
}
