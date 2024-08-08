#ifndef _S21_LIST_H_
#define _S21_LIST_H_

#include <iterator>
#include <utility>

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class List {
 private:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node(const T &value);
    Node(T &&value);
  };

  Node *head;
  Node *tail;
  size_t size_;

 public:
  // Конструкторы
  List();
  explicit List(size_t count);
  List(const List &other);
  List(List &&other) noexcept;
  template <typename InputIt>
  List(InputIt first, InputIt last);
  List(std::initializer_list<T> const &items);

  // Деструктор
  ~List();

  // Операторы присваивания
  List &operator=(const List &other);
  List &operator=(List &&other) noexcept;

  // Итераторы
  class Iterator;
  Iterator begin();
  Iterator end();
  class ConstIterator;
  ConstIterator begin() const;
  ConstIterator end() const;

  // Методы доступа
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;

  // Модификаторы
  void clear();
  void push_back(const T &value);
  void push_back(T &&value);
  void push_front(const T &value);
  void push_front(T &&value);
  void pop_back();
  void pop_front();
  Iterator insert(Iterator pos, const T &value);
  Iterator insert(Iterator pos, T &&value);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator first, Iterator last);
  void resize(size_t count);
  void swap(List &other);
  void merge(List &other);
  void splice(ConstIterator pos, List &other);
  void remove(const T &value);
  void reverse();
  void unique();
  void sort();
  size_t size() const;
  bool empty() const;

  // Операции сравнения
  bool operator==(const List &other) const;
  bool operator!=(const List &other) const;
};

// Итераторы
template <typename T>
class List<T>::Iterator {
 public:
  Iterator(Node *ptr);
  T &operator*();
  const T &operator*() const;
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  bool operator==(const Iterator &other) const;
  bool operator!=(const Iterator &other) const;

  Node *node;
};

template <typename T>
class List<T>::ConstIterator {
 public:
  ConstIterator(const Node *ptr);
  const T &operator*() const;
  ConstIterator &operator++();
  ConstIterator operator++(int);
  ConstIterator &operator--();
  ConstIterator operator--(int);
  bool operator==(const ConstIterator &other) const;
  bool operator!=(const ConstIterator &other) const;

  const Node *node;
};

}  // namespace s21

#include "../templates/s21_list.tpp"

#endif