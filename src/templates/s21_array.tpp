#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_ARRAY_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_ARRAY_TPP_

#include "../include/s21_array.h"

namespace s21 {

// основные публичные методы для взаимодействия с классом
template <typename T>
array<T>::array() {
  size_ = 0;
  data_ = nullptr;
}

template <typename T>
array<T>::array(std::initializer_list<value_type> const &items)
    : data_(new T[items.size()]), size_(items.size()) {
  // Копирование элементов из списка инициализации в массив
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
array<T>::array(const array &a) : data_(new T[a.size_]), size_(a.size_) {
  // Копирование элементов из массива 'a' в новый массив
  std::copy(a.data_, a.data_ + size_, data_);
}

template <typename T>
array<T>::array(array &&a) {
  size_ = std::exchange(a.size_, 0);
  data_ = std::exchange(a.data_, nullptr);
}

template <typename T>
array<T> &array<T>::operator=(array<T> &&a) noexcept {
  if (this != &a) {  // Проверка на самоприсваивание

    delete[] data_;

    size_ = a.size_;
    data_ = a.data_;

    a.size_ = 0;
    a.data_ = nullptr;
  }
  return *this;
}

template <typename T>
array<T>::~array() {
  delete[] data_;

  size_ = 0;
  data_ = nullptr;
}

// публичные методы для доступа к элементам класса
template <typename T>
typename array<T>::reference array<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("array::at - index out of range");
  }

  return data_[pos];
}

//  reference operator[](size_type pos) { return data_[pos]; } // описан в
//  хэдере

template <typename T>
typename array<T>::const_reference array<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("array::front - array is empty");
  }
  return data_[0];
}

template <typename T>
typename array<T>::const_reference array<T>::back() {
  if (size_ == 0) {
    throw std::out_of_range("array::back - array is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
typename array<T>::size_type array<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

// методы для изменения контейнера
template <typename T>
void array<T>::swap(array<T> &other) {
  // Создаем временный объект для обмена данными
  array<T> temp(std::move(
      *this));  // Используем std::move для эффективного перемещения данных

  // Перемещаем данные из 'other' в текущий объект
  *this = std::move(other);

  // Перемещаем данные из временного объекта в 'other'
  other = std::move(temp);
}

template <typename T>
void array<T>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = value;  // Устанавливаем каждый элемент массива равным value
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_ARRAY_TPP_
