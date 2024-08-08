#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_MULTISET_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_MULTISET_TPP_

#include "../include/s21_multiset.h"

namespace s21 {

template <typename T>
multiset<T>::multiset() {
  _tree = AvlTree<T>();
}

template <typename T>
multiset<T>::multiset(const std::initializer_list<value_type> &items) {
  _tree = AvlTree<T>();

  for (const auto &it : items) {
    _tree.Insert(it);
  }
}

template <typename T>
multiset<T>::multiset(const multiset &s) {
  _tree = AvlTree<T>(s._tree);
}

template <typename T>
multiset<T>::multiset(multiset &&s) noexcept {
  _tree = AvlTree<T>(std::move(s._tree));
}

template <typename T>
multiset<T> &multiset<T>::operator=(const multiset &s) {
  _tree = AvlTree<T>(s._tree);

  return *this;
}

template <typename T>
bool multiset<T>::empty() {
  return _tree.IsEmpty();
}

template <typename T>
void multiset<T>::clear() {
  _tree.~AvlTree();
}

template <typename T>
std::pair<typename multiset<T>::iterator, bool> multiset<T>::insert(
    const value_type &value) {
  auto res = _tree.Insert(value);
  return std::pair<iterator, bool>(MultiSetIterator(res.first), res.second);
}

template <typename T>
void multiset<T>::erase(multiset::iterator pos) {
  if (pos != this->end()) {
    _tree.Remove(*pos);
  }
}

template <typename T>
void multiset<T>::swap(multiset<T> &other) {
  AvlTree<T> buf = other._tree;
  other._tree = this->_tree;
  this->_tree = buf;
}

template <typename T>
void multiset<T>::merge(multiset<T> &other) {
  for (const auto &it : other) {
    _tree.Insert(*it);
  }
}

template <typename T>
typename multiset<T>::iterator multiset<T>::find(const key_type &key) {
  return MultiSetIterator(_tree.Find(key));
}

template <typename T>
bool multiset<T>::contains(const key_type &key) {
  return _tree.Include(key);
}

template <typename T>
multiset<T>::~multiset() {
  _tree.~AvlTree();
}

template <typename T>
typename multiset<T>::iterator multiset<T>::begin() {
  return MultiSetIterator(_tree.begin());
}

template <typename T>
typename multiset<T>::iterator multiset<T>::end() {
  return MultiSetIterator(_tree.end());
}

template <typename T>
template <class... Args>
vector<std::pair<typename multiset<T>::iterator, bool>>
multiset<T>::insert_many(Args &&...args) {
  vector<std::pair<iterator, bool>> res_vec;
  for (const auto &it : {args...}) {
    auto res_ins = _tree.Insert(it);
    res_vec.push_back(std::pair<typename multiset<T>::iterator, bool>(
        MultiSetIterator(res_ins.first), res_ins.second));
  }
  return res_vec;
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const T &key) {
  if (!_tree.Include(key)) {
    return std::pair<iterator, iterator>(this->end(), this->end());
  }
  auto start = this->lower_bound(key);
  auto end = --this->upper_bound(key);
  //  auto start = _tree.Find(key);
  //  auto end = start;
  //  while (*end == key && end != _tree.end()) {
  //    end++;
  //  }
  //  if (end != start) {
  //    end--;
  //  }
  return std::pair<iterator, iterator>(MultiSetIterator(start),
                                       MultiSetIterator(end));
}

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const T &key) {
  for (auto it = _tree.begin(); it != _tree.end(); it++) {
    if (*it >= key) {
      return MultiSetIterator(it);
    }
  }
  return this->end();
}

template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const T &key) {
  for (auto it = _tree.begin(); it != _tree.end(); it++) {
    if (*it > key) {
      return MultiSetIterator(it);
    }
  }
  return this->end();
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_MULTISET_TPP_
