#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MAP_H_

#include <utility>

#include "s21_avltree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class Pair {
 public:
  Pair();
  Pair(const std::pair<Key, T> &value);
  Pair(Pair &&p);
  Pair(const Pair &other);

  Pair &operator=(const Pair &other);
  Pair &operator=(Pair &&other);
  bool operator<(const Pair &other);
  bool operator==(const Pair &other);
  bool operator>(const Pair &other);

  T &second();

 private:
  void swap(Pair &other);
  std::pair<Key, T> pair_;
};

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = Pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  struct iterator : AvlTree<value_type>::iterator {
    iterator() {}
    iterator(typename AvlTree<value_type>::iterator const &it)
        : AvlTree<value_type>::iterator(it) {}
  };
  struct const_iterator : AvlTree<value_type>::const_iterator {};
  map();
  map(const std::initializer_list<std::pair<Key, T>> &items);
  map(const map &other);
  map(map &&m);
  map &operator=(map &&m);
  map &operator=(const map &other);
  ~map();
  mapped_type &at(const Key &key);
  mapped_type &operator[](const Key &key);

  iterator begin();
  iterator end();

  bool empty();
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  void erase(iterator pos);
  void swap(map &other);

  void merge(map &other);
  bool contains(const Key &key);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  AvlTree<value_type> *tree_;
};
}  // namespace s21

#include "../templates/s21_map.tpp"

#endif
