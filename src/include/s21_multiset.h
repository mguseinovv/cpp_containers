#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MULTISET_H_

#include "s21_set.h"

namespace s21 {
template <typename T>
class multiset {
 private:
  AvlTree<T> _tree;

 public:
  class MultiSetIterator : public AvlTree<T>::Iterator {
    friend class set<T>;

   public:
    explicit MultiSetIterator(typename AvlTree<T>::Iterator it)
        : AvlTree<T>::Iterator(it) {}
  };
  class ConstMultiSetIterator : public AvlTree<T>::ConstIterator {
    friend class set<T>;
  };
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename AvlTree<T>::Iterator;
  using const_iterator = typename AvlTree<T>::ConstIterator;
  using size_type = std::size_t;
  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &s);
  multiset(multiset &&s) noexcept;
  multiset<T> &operator=(const multiset &s);
  bool empty();
  size_type size() { return _tree.size(); }
  size_type max_size() { return _tree.max_size(); }
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(multiset<T> &other);
  void merge(multiset<T> &other);
  size_type count(const key_type &key) { return _tree.Count(key); }
  iterator find(const key_type &key);
  bool contains(const key_type &key);
  std::pair<iterator, iterator> equal_range(const T &key);
  iterator lower_bound(const T &key);
  iterator upper_bound(const T &key);
  iterator begin();
  iterator end();
  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  ~multiset();
};
}  // namespace s21
#include "../templates/s21_multiset.tpp"
#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_MULTISET_H_
