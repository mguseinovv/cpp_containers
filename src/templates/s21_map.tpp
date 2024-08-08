#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_MAP_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_MAP_TPP_

#include "../include/s21_map.h"

namespace s21 {
template <typename Key, typename T>
Pair<Key, T>::Pair() {
  pair_ = std::pair<Key, T>();
}

template <typename Key, typename T>
Pair<Key, T>::Pair(const std::pair<Key, T> &value) : pair_(value) {}

template <typename Key, typename T>
Pair<Key, T>::Pair(Pair &&p) {
  pair_ = std::pair<Key, T>();
  swap(p);
}

template <typename Key, typename T>
Pair<Key, T>::Pair(const Pair &other) {
  pair_ = other.pair_;
}

template <typename Key, typename T>
Pair<Key, T> &Pair<Key, T>::operator=(const Pair &other) {
  Pair(other).swap(*this);
  return *this;
}

template <typename Key, typename T>
Pair<Key, T> &Pair<Key, T>::operator=(Pair &&other) {
  swap(other);
  return *this;
}

template <typename Key, typename T>
bool Pair<Key, T>::operator<(const Pair &other) {
  return pair_.first < other.pair_.first;
}

template <typename Key, typename T>
bool Pair<Key, T>::operator==(const Pair &other) {
  return pair_.first == other.pair_.first;
}

template <typename Key, typename T>
bool Pair<Key, T>::operator>(const Pair &other) {
  return pair_.first > other.pair_.first;
}

template <typename Key, typename T>
void Pair<Key, T>::swap(Pair &other) {
  std::swap(pair_, other.pair_);
}

template <typename Key, typename T>
T &Pair<Key, T>::second() {
  return pair_.second;
}

template <typename Key, typename T>
map<Key, T>::map() : tree_(new AvlTree<value_type>()) {
  /// map не может хранить двух одинаковых ключей
  tree_->SetUnique();
}

template <typename Key, typename T>
map<Key, T>::map(const std::initializer_list<std::pair<Key, T>> &items)
    : tree_(new AvlTree<value_type>()) {
  /// map не может хранить двух одинаковых ключей
  tree_->SetUnique();
  for (value_type i : items) {
    tree_->Insert(Pair(i));
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map &other)
    : tree_(new AvlTree<value_type>(*(other.tree_))) {}

template <typename Key, typename T>
map<Key, T>::map(map &&m) : map() {
  swap(m);
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&m) {
  swap(m);
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  map<Key, T>(other).swap(*this);
  return *this;
}

template <typename Key, typename T>
map<Key, T>::~map() {
  delete tree_;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::at(const Key &key) {
  typename AvlTree<value_type>::iterator tmp =
      tree_->Find(Pair(std::pair<Key, T>(key, T())));
  if (tmp == tree_->end()) {
    throw std::out_of_range("s21::map::at:  key not found");
  }
  return (*tmp).second();
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](const Key &key) {
  std::pair<typename AvlTree<value_type>::iterator, bool> inserted =
      tree_->Insert(Pair(std::pair<Key, T>(key, T())));
  if (!inserted.second) {
    return at(key);
  }
  return (*(inserted.first)).second();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  return tree_->Insert(value);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  return tree_->Insert(std::pair<Key, T>(key, obj));
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  typename AvlTree<value_type>::iterator tmp =
      tree_->Find(Pair(std::pair<Key, T>(key, obj)));
  if (tmp == tree_->end()) {
    return insert(key, obj);
  }
  (*tmp).second() = obj;
  return std::pair<typename map<Key, T>::iterator, bool>(tmp, false);
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  tree_->Remove(*pos);
}

template <typename Key, typename T>
bool map<Key, T>::empty() {
  return tree_->IsEmpty();
}

template <typename Key, typename T>
void map<Key, T>::swap(map &other) {
  std::swap(tree_, other.tree_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key &key) {
  return tree_->Include(Pair(std::make_pair(key, T())));
}

template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  s21::vector<std::pair<typename map<Key, T>::iterator, bool>> result;
  for (const auto &arg : {args...}) {
    result.push_back(insert(arg));
  }
  return result;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return tree_->begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return tree_->end();
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_MAP_TPP_