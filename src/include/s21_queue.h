#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../s21_containers.h"

using namespace std;

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using size_type = size_t;
  using const_reference = const T &;
  queue();
  ~queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &other);                 // копирования
  queue(queue &&other) noexcept;             // перемещения
  queue &operator=(queue &&other) noexcept;  // для перемещения
  queue &operator=(const queue &other);      // для копирования

  const_reference front();
  const_reference back();

  bool empty();
  void push(const_reference data_);
  void pop();
  void swap(queue &other);
  size_t size() { return size_; };

 private:
  template <typename>
  class Node {
   public:
    value_type data_;
    Node *p_next_;
    Node *p_prev_;

    Node(T data_ = T(), Node *p_next_ = nullptr, Node *p_prev_ = nullptr) {
      this->data_ = data_;
      this->p_next_ = p_next_;
      this->p_prev_ = p_prev_;
    }
  };
  size_t size_;
  Node<T> *front_;
  Node<T> *back_;

  void Clear_();
};
}  // namespace s21

#include "../templates/s21_queue.tpp"

#endif  // CPP1_S21_queue