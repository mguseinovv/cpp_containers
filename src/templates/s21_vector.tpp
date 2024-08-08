#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

#include "../include/s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T>::vector(size_type n) {
  data_ = new value_type[n];
  size_ = n;
  capacity_ = n;
  std::fill_n(data_, n, value_type());
}

template <typename T>
vector<T>::~vector() {
  size_ = 0;
  capacity_ = 0;
  delete[] data_;
}

template <typename T>
vector<T>::vector(const vector &v)
    : data_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::vector(vector &&v) {
  data_ = std::exchange(v.data_, nullptr);
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  if (this != &v) {
    delete[] data_;

    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos > size_) {
    throw std::out_of_range("vector::at - out of range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("vector::front - vector is empty");
  }
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (size_ == 0) {
    throw std::out_of_range("vector::back - vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return data_ + size_;
}

template <typename T>
bool vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    throw std::out_of_range(
        "vector::reserve - too large size for a new capacity");
  }
  if (size > max_size()) {
    throw std::length_error("vecto::reserve - impossible to allocate memory");
  }

  iterator new_data = new value_type[size];
  for (size_type i = 0; i < size; i++) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;

  data_ = new_data;
  capacity_ = size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator new_data = new value_type[size_];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}
template <typename T>
void vector<T>::clear() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range(
        "vector::insert - the insert position is out of memory range");
  }

  size_type new_capacity = 1;
  if (capacity_ == size_) {
    new_capacity = capacity_ * 2;
  }

  if (capacity_ <= size_) {
    reserve(new_capacity);
    pos = begin() + index;
  }

  std::move_backward(pos, end(), end() + 1);

  *pos = value;
  size_++;

  return pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (empty()) {
    throw std::out_of_range("vector::erase Vector is already empty!");
  }
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range(
        "vector::erase - the erase position is out of memory range");
  }
  std::move(pos + 1, end(), pos);
  size_--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (capacity_ == size_) {
    if (capacity_ != 0) {
      reserve(capacity_ * 2);
    } else
      reserve(1);
  }
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <class... Args>
typename vector<T>::iterator vector<T>::insert_many(
    typename vector<T>::const_iterator pos, Args &&...args) {
  typename vector<T>::size_type index = pos - begin();
  typename vector<T>::size_type new_capacity = size_ + sizeof...(args);
  if (new_capacity > capacity_) {
    reserve(new_capacity);
    pos = begin() + index;
  }

  auto insert_position = begin() + index;

  ((void)(data_[index++] = std::forward<Args>(args)), ...);

  size_ += sizeof...(args);

  return insert_position;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  size_t new_size = size_ + sizeof...(args);

  if (new_size > capacity_) {
    reserve(new_size);
  }

  T *dest = data_ + size_;
  (..., (void)(*dest++ = std::forward<Args>(args)));

  size_ = new_size;
}

}  // namespace s21

#endif