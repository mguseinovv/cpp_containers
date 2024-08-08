#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

#include "../include/s21_queue.h"

namespace s21 {

template <typename T>
queue<T>::queue() : size_(0), front_(nullptr), back_(nullptr) {}

template <typename T>
queue<T>::~queue() {
  Clear_();
}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : size_(0), front_(nullptr), back_(nullptr) {
  for (const auto &item : items) {
    push(item);
  }
}

template <typename T>
queue<T>::queue(const queue &other) : queue() {  // копирования
  *this = other;
}

template <typename T>
queue<T> &queue<T>::operator=(const queue &other) {
  if (this != &other) {
    Clear_();
    Node<T> *temp = other.front_;
    while (temp != nullptr) {
      push(temp->data_);
      temp = temp->p_next_;
    }
  }
  return *this;
}

template <typename T>
queue<T>::queue(queue &&other) noexcept
    : size_(other.size_), front_(other.front_), back_(other.back_) {
  other.size_ = 0;
  other.front_ = nullptr;
  other.back_ = nullptr;
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&other) noexcept {
  if (this != &other) {
    Clear_();
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    other.size_ = 0;
    other.front_ = nullptr;
    other.back_ = nullptr;
  }
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (front_ == nullptr) throw std::logic_error("queue is empty");
  return front_->data_;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (back_ == nullptr) throw std::logic_error("queue is empty");
  return back_->data_;
}

template <typename T>
void queue<T>::push(const_reference data_) {
  if (front_ == nullptr) {
    front_ = back_ = new Node<T>(data_);
  } else {
    back_->p_next_ = new Node<T>(data_, nullptr, back_);
    back_ = back_->p_next_;
  }
  size_++;
}

template <typename T>
bool queue<T>::empty() {
  return size_ == 0;
}

template <typename T>
void queue<T>::pop() {
  if (front_ == nullptr) {
    throw std::out_of_range("queue is empty");
  }
  Node<T> *temp = front_;
  front_ = front_->p_next_;
  if (front_ != nullptr) {
    front_->p_prev_ = nullptr;
  } else {
    back_ = nullptr;
  }
  delete temp;
  size_--;
}

template <typename T>
void queue<T>::swap(queue<T> &other) {
  if (this != &other) {
    Node<T> *tmp_front_ = this->front_;
    this->front_ = other.front_;
    other.front_ = tmp_front_;

    Node<T> *tmp_back_ = this->back_;
    this->back_ = other.back_;
    other.back_ = tmp_back_;

    size_type tmp_size_ = this->size_;
    this->size_ = other.size_;
    other.size_ = tmp_size_;
  }
}

template <typename T>
void queue<T>::Clear_() {
  while (size_ != 0) {
    pop();
  }
}
}  // namespace s21

#endif