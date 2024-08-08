#ifndef CPP2_S21_CONTAINERS_1_S21_SET_TPP
#define CPP2_S21_CONTAINERS_1_S21_SET_TPP

#include "../include/s21_set.h"

namespace s21 {

template <typename T>
set<T>::set() {
  _tree = AvlTree<T>();
  _tree.SetUnique();
}

template <typename T>
set<T>::set(const std::initializer_list<value_type> &items) {
  _tree = AvlTree<T>();
  _tree.SetUnique();
  for (const auto &it : items) {
    _tree.Insert(it);
  }
}

template <typename T>
set<T>::set(const set &s) {
  _tree = AvlTree<T>(s._tree);
  _tree.SetUnique();
}

template <typename T>
set<T>::set(set &&s) noexcept {
  _tree = AvlTree<T>(std::move(s._tree));
  _tree.SetUnique();
}

template <typename T>
set<T> &set<T>::operator=(const set &s) {
  _tree = AvlTree<T>(s._tree);
  _tree.SetUnique();
  return *this;
}

template <typename T>
bool set<T>::empty() {
  return _tree.IsEmpty();
}

template <typename T>
void set<T>::clear() {
  _tree.~AvlTree();
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type &value) {
  auto res = _tree.Insert(value);
  return std::pair<iterator, bool>(SetIterator(res.first), res.second);
}

template <typename T>
void set<T>::erase(set::iterator pos) {
  if (pos != this->end()) {
    _tree.Remove(*pos);
  }
}

template <typename T>
void set<T>::swap(set<T> &other) {
  AvlTree<T> buf = other._tree;
  other._tree = this->_tree;
  this->_tree = buf;
}

template <typename T>
void set<T>::merge(set<T> &other) {
  for (const auto &it : other) {
    _tree.Insert(it);
  }
}

template <typename T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  return SetIterator(_tree.Find(key));
}

template <typename T>
bool set<T>::contains(const key_type &key) {
  return _tree.Include(key);
}

template <typename T>
set<T>::~set() {
  _tree.~AvlTree();
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return SetIterator(_tree.begin());
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return SetIterator(_tree.end());
}

template <typename T>
template <class... Args>
vector<std::pair<typename set<T>::iterator, bool>> set<T>::insert_many(
    Args &&...args) {
  vector<std::pair<iterator, bool>> res_vec;
  for (const auto &it : {args...}) {
    auto res_ins = _tree.Insert(it);
    //    auto pair = std::pair<typename set<T>::iterator, bool>(
    //                    );
    res_vec.push_back({SetIterator(res_ins.first), res_ins.second});
  }
  return res_vec;
}

// template <typename T>
// set<T>::~set() {
//   this->~AvlTree();
// }
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_SET_TPP