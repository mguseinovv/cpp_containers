#ifndef _S21_STACK_H_
#define _S21_STACK_H_

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();

  Stack &operator=(Stack &&s);

  bool empty() const;
  size_type size() const;
  const_reference top() const;
  void push(const_reference value);
  void pop();
  void swap(Stack &other);

  bool operator==(const Stack &other) const;
  bool operator!=(const Stack &other) const;
  bool operator<(const Stack &other) const;
  bool operator<=(const Stack &other) const;
  bool operator>(const Stack &other) const;
  bool operator>=(const Stack &other) const;

 private:
  struct Node {
    value_type data;
    Node *next;
    Node(const_reference data, Node *next = nullptr) : data(data), next(next) {}
  };

  Node *head_;
  size_type size_;
};
}  // namespace s21

#include "../templates/s21_stack.tpp"

#endif