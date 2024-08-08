#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include "../s21_containers.h"

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T &;
  using size_type = size_t;

  // Functions
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v) noexcept;

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  // Vector iterators
  iterator begin();
  iterator end();

  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept;
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  typename vector<T>::iterator insert_many(
      typename vector<T>::const_iterator pos, Args &&...args);

 private:
  iterator data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#include "../templates/s21_vector.tpp"

#endif