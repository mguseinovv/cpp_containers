#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_AVLTREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_AVLTREE_H_

#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "../s21_containers.h"

namespace s21 {

template <typename T>
class AvlTree {
 private:
  struct Node {
    Node *left;
    Node *right;
    Node *parent;
    T value;
    unsigned char height;

    explicit Node(T k) {
      value = k;
      left = right = parent = nullptr;
      height = 1;
    }
  };

  struct triple {
    Node *now_root = nullptr;
    Node *current_node = nullptr;
    bool third = false;
  };

  static unsigned char GetHeight(Node *node) { return node ? node->height : 0; }

  static int BalanceFactor(Node *node);

  static void FixHeight(Node *node);

  static Node *RotateRight(Node *node);

  static Node *RotateLeft(Node *node);

  static Node *Balance(Node *node);

  AvlTree<T>::triple InInsert(AvlTree::Node *node, T value, bool uniq);

  static void DeleteTree(Node **p_node);

  static void PrintTree(Node *node);

  static Node *InInclude(Node *node, T value);

  static Node *FindMin(Node *node);

  static Node *FindMax(Node *node);

  static Node *InRemoveMin(Node *node);

  Node *InRemove(Node *node, T value);

  static Node *CopyNodes(Node *node);

  static int CountNodes(Node *node, const T &value);

  static Node *NextNode(Node *node);

  static Node *PrevNode(Node *node);
  Node *_root;
  bool _unique{};

  size_t _size{};

 public:
  class Iterator;
  class ConstIterator;

  using value_type = T;

  using reference = T &;

  using const_reference = const T &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  class Iterator {
   private:
    Node *cur_node;
    Node *prev_node;
    void swap(iterator &other);

   public:
    Iterator();
    explicit Iterator(Node *cur_node, Node *prev_node = nullptr);
    Iterator(const iterator &other);
    iterator &operator=(const iterator &other);
    iterator &operator++();
    const iterator operator++(int);
    iterator &operator--();
    const iterator operator--(int);
    virtual reference operator*() const;
    bool operator==(const iterator &it) const;
    bool operator!=(const iterator &it) const;
    ~Iterator() = default;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator();
    explicit ConstIterator(const Iterator &other);
    const_reference operator*() const;
  };

  AvlTree();

  explicit AvlTree(value_type value, bool unique = false)
      : _root(new Node(value)), _unique(unique), _size(1) {}

  AvlTree(const AvlTree &other);

  AvlTree(AvlTree<T> &&other) noexcept {
    _root = other._root;
    _unique = other._unique;
    _size = other._size;

    other._root = nullptr;
    other._size = 0;
    other._unique = false;
  }

  std::pair<iterator, bool> Insert(value_type value);

  void Print();

  bool Include(value_type value);

  iterator Find(value_type value);

  void Remove(value_type value);

  T Top();

  bool IsEmpty() { return _root == nullptr; }

  int Count(const_reference value) const;

  void SetUnique();

  bool IsUnique() { return _unique; }

  size_t size() { return _size; }

  size_t max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
  }

  ~AvlTree();
  AvlTree<T> &operator=(const AvlTree<T> &other);
  iterator begin();
  iterator end();
};

}  // namespace s21

#include "../templates/s21_avltree.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_INCLUDE_S21_AVLTREE_H_
