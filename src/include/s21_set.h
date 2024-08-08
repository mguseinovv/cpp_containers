#ifndef CPP2_S21_CONTAINERS_1_S21_SET_H
#define CPP2_S21_CONTAINERS_1_S21_SET_H

#include "s21_avltree.h"
#include "s21_vector.h"

namespace s21 {

template <typename T>
class set {
 private:
  AvlTree<T> _tree;

 public:
  class SetIterator : public AvlTree<T>::Iterator {
    friend class set<T>;

   public:
    explicit SetIterator(typename AvlTree<T>::Iterator it)
        : AvlTree<T>::Iterator(it) {}
    SetIterator() {}
  };

  class ConstSetIterator : public AvlTree<T>::ConstIterator {
    friend class set<T>;
  };

  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator;
  // using const_iterator = ConstSetIterator;
  using size_type = std::size_t;

  set();

  set(std::initializer_list<value_type> const &items);

  set(const set &s);

  set(set &&s) noexcept;

  set<T> &operator=(const set &s);

  bool empty();

  size_type size() { return _tree.size(); }

  size_type max_size() { return _tree.max_size(); }

  void clear();

  std::pair<iterator, bool> insert(const value_type &value);

  void erase(iterator pos);

  void swap(set<T> &other);

  void merge(set<T> &other);

  iterator find(const key_type &key);

  bool contains(const key_type &key);
  iterator begin();
  iterator end();

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  void show() { _tree.Print(); }

  ~set();
};

}  // namespace s21

#include "../templates/s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_SET_H
