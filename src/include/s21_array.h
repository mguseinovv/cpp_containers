#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_ARRAY_H_

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class array {
 public:
  using value_type = T;

  using reference = value_type &;

  using const_reference = const value_type &;

  using iterator = T *;

  using const_iterator = const T *;

  using size_type = size_t;

  array();

  array(std::initializer_list<value_type> const &items);

  array(const array &a);

  array(array &&a);

  ~array();

  array &operator=(array &&a) noexcept;

  reference at(size_type pos);

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference front();

  const_reference back();

  T *data() { return data_; }

  iterator begin() { return data_; }

  iterator end() { return data_ + size_; }

  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size();

  void swap(array &other);

  void fill(const_reference value);

 private:
  T *data_;
  size_type size_;
};
}  // namespace s21

#include "../templates/s21_array.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_ARRAY_H_
