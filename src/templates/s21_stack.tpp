#ifndef _S21_STACK_TPP_
#define _S21_STACK_TPP_

#include "../include/s21_stack.h"

namespace s21 {

template <typename T>
Stack<T>::Stack() : head_(nullptr), size_(0) {}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items)
    : head_(nullptr), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
Stack<T>::Stack(const Stack &s) : head_(nullptr), size_(0) {
  Node *current = s.head_;
  Node *last = nullptr;
  while (current) {
    Node *newNode = new Node(current->data);
    if (!head_) {
      head_ = newNode;
    } else {
      last->next = newNode;
    }
    last = newNode;
    current = current->next;
  }
  size_ = s.size_;
}

template <typename T>
Stack<T>::Stack(Stack &&s) : head_(s.head_), size_(s.size_) {
  s.head_ = nullptr;
  s.size_ = 0;
}

template <typename T>
Stack<T>::~Stack() {
  while (head_) {
    Node *temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack &&s) {
  if (this != &s) {
    while (head_) {
      Node *temp = head_;
      head_ = head_->next;
      delete temp;
    }
    head_ = s.head_;
    size_ = s.size_;
    s.head_ = nullptr;
    s.size_ = 0;
  }
  return *this;
}

template <typename T>
bool Stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
  return size_;
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() const {
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return head_->data;
}

template <typename T>
void Stack<T>::push(const_reference value) {
  Node *newNode = new Node(value, head_);
  head_ = newNode;
  ++size_;
}

template <typename T>
void Stack<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Stack is empty");
  }
  Node *temp = head_;
  head_ = head_->next;
  delete temp;
  --size_;
}

template <typename T>
void Stack<T>::swap(Stack &other) {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
}

template <typename T>
bool Stack<T>::operator==(const Stack &other) const {
  if (size_ != other.size_) return false;
  Node *current1 = head_;
  Node *current2 = other.head_;
  while (current1) {
    if (current1->data != current2->data) return false;
    current1 = current1->next;
    current2 = current2->next;
  }
  return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack &other) const {
  return !(*this == other);
}

template <typename T>
bool Stack<T>::operator<(const Stack &other) const {
  Node *current1 = head_;
  Node *current2 = other.head_;
  while (current1 && current2) {
    if (current1->data < current2->data) return true;
    if (current1->data > current2->data) return false;
    current1 = current1->next;
    current2 = current2->next;
  }
  return size_ < other.size_;
}

template <typename T>
bool Stack<T>::operator<=(const Stack &other) const {
  return *this < other || *this == other;
}

template <typename T>
bool Stack<T>::operator>(const Stack &other) const {
  return !(*this <= other);
}

template <typename T>
bool Stack<T>::operator>=(const Stack &other) const {
  return !(*this < other);
}

}  // namespace s21

#endif