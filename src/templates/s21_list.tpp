#ifndef _S21_LIST_TPP_
#define _S21_LIST_TPP_

#include "../include/s21_list.h"

namespace s21 {

// Node constructors
template <typename T>
List<T>::Node::Node(const T &value)
    : data(value), next(nullptr), prev(nullptr) {}

template <typename T>
List<T>::Node::Node(T &&value)
    : data(std::move(value)), next(nullptr), prev(nullptr) {}

// List constructors
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0) {}

template <typename T>
List<T>::List(size_t count) : head(nullptr), tail(nullptr), size_(0) {
  for (size_t i = 0; i < count; ++i) {
    push_back(T());
  }
}

template <typename T>
List<T>::List(const List &other) : head(nullptr), tail(nullptr), size_(0) {
  for (Node *current = other.head; current != nullptr;
       current = current->next) {
    push_back(current->data);
  }
}

template <typename T>
List<T>::List(List &&other) noexcept
    : head(other.head), tail(other.tail), size_(other.size_) {
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}

template <typename T>
template <typename InputIt>
List<T>::List(InputIt first, InputIt last)
    : head(nullptr), tail(nullptr), size_(0) {
  while (first != last) {
    push_back(*first++);
  }
}

template <typename T>
// template <typename InputIt>
List<T>::List(std::initializer_list<T> const &items)
    : head(nullptr), tail(nullptr), size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

// Destructor
template <typename T>
List<T>::~List() {
  clear();
}

// Assignment operators
template <typename T>
List<T> &List<T>::operator=(const List &other) {
  if (this != &other) {
    clear();
    for (Node *current = other.head; current != nullptr;
         current = current->next) {
      push_back(current->data);
    }
  }
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List &&other) noexcept {
  if (this != &other) {
    clear();
    head = other.head;
    tail = other.tail;
    size_ = other.size_;
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }
  return *this;
}

// Iterators
template <typename T>
typename List<T>::Iterator List<T>::begin() {
  return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
  return Iterator(nullptr);
}

template <typename T>
typename List<T>::ConstIterator List<T>::begin() const {
  return ConstIterator(head);
}

template <typename T>
typename List<T>::ConstIterator List<T>::end() const {
  return ConstIterator(nullptr);
}

// Element access
template <typename T>
T &List<T>::front() {
  return head->data;
}

template <typename T>
const T &List<T>::front() const {
  return head->data;
}

template <typename T>
T &List<T>::back() {
  return tail->data;
}

template <typename T>
const T &List<T>::back() const {
  return tail->data;
}

// Modifiers
template <typename T>
void List<T>::clear() {
  while (head != nullptr) {
    pop_front();
  }
}

template <typename T>
void List<T>::push_back(const T &value) {
  Node *new_node = new Node(value);
  if (tail) {
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
  } else {
    head = tail = new_node;
  }
  ++size_;
}

template <typename T>
void List<T>::push_back(T &&value) {
  Node *new_node = new Node(std::move(value));
  if (tail) {
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
  } else {
    head = tail = new_node;
  }
  ++size_;
}

template <typename T>
void List<T>::push_front(const T &value) {
  Node *new_node = new Node(value);
  if (head) {
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
  } else {
    head = tail = new_node;
  }
  ++size_;
}

template <typename T>
void List<T>::push_front(T &&value) {
  Node *new_node = new Node(std::move(value));
  if (head) {
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
  } else {
    head = tail = new_node;
  }
  ++size_;
}

template <typename T>
void List<T>::pop_back() {
  if (tail) {
    Node *old_tail = tail;
    tail = tail->prev;
    if (tail) {
      tail->next = nullptr;
    } else {
      head = nullptr;
    }
    delete old_tail;
    --size_;
  }
}

template <typename T>
void List<T>::pop_front() {
  if (head) {
    Node *old_head = head;
    head = head->next;
    if (head) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }
    delete old_head;
    --size_;
  }
}

template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator pos, const T &value) {
  if (pos.node == nullptr) {
    push_back(value);
    return Iterator(tail);
  }
  Node *new_node = new Node(value);
  new_node->next = pos.node;
  new_node->prev = pos.node->prev;
  if (pos.node->prev) {
    pos.node->prev->next = new_node;
  } else {
    head = new_node;
  }
  pos.node->prev = new_node;
  ++size_;
  return Iterator(new_node);
}

template <typename T>
typename List<T>::Iterator List<T>::insert(Iterator pos, T &&value) {
  if (pos.node == nullptr) {
    push_back(std::move(value));
    return Iterator(tail);
  }
  Node *new_node = new Node(std::move(value));
  new_node->next = pos.node;
  new_node->prev = pos.node->prev;
  if (pos.node->prev) {
    pos.node->prev->next = new_node;
  } else {
    head = new_node;
  }
  pos.node->prev = new_node;
  ++size_;
  return Iterator(new_node);
}

template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator pos) {
  Node *node_to_delete = pos.node;
  Iterator next_node(node_to_delete->next);
  if (node_to_delete->prev) {
    node_to_delete->prev->next = node_to_delete->next;
  } else {
    head = node_to_delete->next;
  }
  if (node_to_delete->next) {
    node_to_delete->next->prev = node_to_delete->prev;
  } else {
    tail = node_to_delete->prev;
  }
  delete node_to_delete;
  --size_;
  return next_node;
}

template <typename T>
typename List<T>::Iterator List<T>::erase(Iterator first, Iterator last) {
  while (first != last) {
    first = erase(first);
  }
  return last;
}

template <typename T>
void List<T>::resize(size_t count) {
  while (size_ > count) {
    pop_back();
  }
  while (size_ < count) {
    push_back(T());
  }
}

template <typename T>
void List<T>::swap(List &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::merge(List &other) {
  Node *this_current = head;
  Node *other_current = other.head;
  while (this_current && other_current) {
    if (other_current->data < this_current->data) {
      Node *next_other = other_current->next;
      if (this_current->prev) {
        this_current->prev->next = other_current;
      } else {
        head = other_current;
      }
      other_current->prev = this_current->prev;
      other_current->next = this_current;
      this_current->prev = other_current;
      other_current = next_other;
    } else {
      this_current = this_current->next;
    }
  }
  if (other_current) {
    if (tail) {
      tail->next = other_current;
      other_current->prev = tail;
    } else {
      head = other_current;
    }
    tail = other.tail;
  }
  size_ += other.size_;
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}

template <typename T>
void List<T>::splice(ConstIterator pos, List &other) {
  if (other.head) {
    Node *pos_node = pos.node;
    if (pos_node) {
      if (pos_node->prev) {
        pos_node->prev->next = other.head;
        other.head->prev = pos_node->prev;
      } else {
        head = other.head;
      }
      other.tail->next = pos_node;
      pos_node->prev = other.tail;
    } else {
      if (tail) {
        tail->next = other.head;
        other.head->prev = tail;
      } else {
        head = other.head;
      }
      tail = other.tail;
    }
    size_ += other.size_;
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
void List<T>::remove(const T &value) {
  Node *current = head;
  while (current) {
    Node *next = current->next;
    if (current->data == value) {
      if (current->prev) {
        current->prev->next = next;
      } else {
        head = next;
      }
      if (next) {
        next->prev = current->prev;
      } else {
        tail = current->prev;
      }
      delete current;
      --size_;
    }
    current = next;
  }
}

template <typename T>
void List<T>::reverse() {
  Node *current = head;
  Node *temp = nullptr;
  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  if (temp) {
    temp = temp->prev;
  }
  std::swap(head, tail);
}

template <typename T>
void List<T>::unique() {
  if (!head) return;
  Node *current = head;
  while (current->next) {
    if (current->data == current->next->data) {
      Node *duplicate = current->next;
      current->next = duplicate->next;
      if (duplicate->next) {
        duplicate->next->prev = current;
      } else {
        tail = current;
      }
      delete duplicate;
      --size_;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void List<T>::sort() {
  if (size_ < 2) return;

  for (bool sorted = false; !sorted;) {
    sorted = true;
    for (Node *current = head; current->next != nullptr;
         current = current->next) {
      if (current->data > current->next->data) {
        std::swap(current->data, current->next->data);
        sorted = false;
      }
    }
  }
}

// Comparison operators
template <typename T>
bool List<T>::operator==(const List &other) const {
  if (size_ != other.size_) return false;
  Node *this_current = head;
  Node *other_current = other.head;
  while (this_current && other_current) {
    if (this_current->data != other_current->data) {
      return false;
    }
    this_current = this_current->next;
    other_current = other_current->next;
  }
  return true;
}

template <typename T>
bool List<T>::operator!=(const List &other) const {
  return !(*this == other);
}

// Iterator methods
template <typename T>
List<T>::Iterator::Iterator(Node *ptr) : node(ptr) {}

template <typename T>
T &List<T>::Iterator::operator*() {
  return node->data;
}

template <typename T>
const T &List<T>::Iterator::operator*() const {
  return node->data;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
  node = node->next;
  return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
  Iterator temp = *this;
  node = node->next;
  return temp;
}

template <typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
  node = node->prev;
  return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
  Iterator temp = *this;
  node = node->prev;
  return temp;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator &other) const {
  return node == other.node;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator &other) const {
  return node != other.node;
}

// ConstIterator methods
template <typename T>
List<T>::ConstIterator::ConstIterator(const Node *ptr) : node(ptr) {}

template <typename T>
const T &List<T>::ConstIterator::operator*() const {
  return node->data;
}

template <typename T>
typename List<T>::ConstIterator &List<T>::ConstIterator::operator++() {
  node = node->next;
  return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) {
  ConstIterator temp = *this;
  node = node->next;
  return temp;
}

template <typename T>
typename List<T>::ConstIterator &List<T>::ConstIterator::operator--() {
  node = node->prev;
  return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int) {
  ConstIterator temp = *this;
  node = node->prev;
  return temp;
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator &other) const {
  return node == other.node;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator &other) const {
  return node != other.node;
}

template <typename T>
size_t List<T>::size() const {
  return this->size_;
}

template <typename T>
bool List<T>::empty() const {
  return head == nullptr;
}

}  // namespace s21

#endif