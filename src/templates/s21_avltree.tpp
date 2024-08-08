#ifndef CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_AVLTREE_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_AVLTREE_TPP_

#include "../include/s21_avltree.h"

namespace s21 {
template <typename T>
AvlTree<T>::AvlTree() {
  _root = nullptr;
  _unique = false;
  _size = 0;
}

template <typename T>
int AvlTree<T>::BalanceFactor(Node *node) {
  return GetHeight(node->right) - GetHeight(node->left);
}

template <typename T>
void AvlTree<T>::FixHeight(Node *node) {
  unsigned char height_left = GetHeight(node->left);
  unsigned char height_right = GetHeight(node->right);
  node->height = (height_left > height_right ? height_left : height_right) + 1;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::RotateRight(Node *node) {
  Node *new_node = node->left;
  node->left = new_node->right;
  new_node->right = node;
  new_node->parent = node->parent;
  node->parent = new_node;
  if (node->left) node->left->parent = node;
  FixHeight(node);
  FixHeight(new_node);
  return new_node;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::RotateLeft(Node *node) {
  Node *new_node = node->right;
  node->right = new_node->left;
  new_node->left = node;
  new_node->parent = node->parent;
  node->parent = new_node;
  if (node->right) node->right->parent = node;
  FixHeight(node);
  FixHeight(new_node);
  return new_node;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::Balance(Node *node) {
  if (node) {         /// проверка существование узла
    FixHeight(node);  /// корректировка высот
    /// выяснение случая поворота
    if (BalanceFactor(node) == 2) {
      /// проверка условия, что левой поддерево правого поддерева меньше правого
      /// поддерева правого поддерева
      if (BalanceFactor(node->right) < 0) {
        node->right = RotateRight(node->right);
      }
      node = RotateLeft(node);
    } else if (BalanceFactor(node) == -2) {
      /// проверка условия, что правое поддерево левого поддерева меньше левого
      /// поддерева левого поддерева
      if (BalanceFactor(node->left) > 0) {
        node->left = RotateLeft(node->left);
      }
      node = RotateRight(node);
    }
  }
  return node;
}

template <typename T>
typename AvlTree<T>::triple AvlTree<T>::InInsert(AvlTree::Node *node, T value,
                                                 bool uniq) {
  /// узел не существует, создаем новый. Базовый случай
  if (!node) {
    Node *new_node = new Node(value);
    triple res = {new_node, new_node, true};
    _size++;
    return res;
  }
  /// Изначально стоит false
  triple triple = {nullptr, nullptr, false};
  /// обращение к левому поддереву. с лева всегда меньше корня. иначе правое
  if (value < node->value) {
    triple = InInsert(node->left, value, uniq);
    node->left = triple.now_root;
    node->left->parent = node;  /// родитель левого поддерева - корень
    /// уже существующее значение вставляем, если unique == false. Второе
    /// условие можно бы было сократить до value > node->value, однако требовать
    /// от класса ключа реализации operator> излишне
  } else if ((value == node->value && !uniq) ||
             (!(value < node->value) && !(value == node->value))) {
    triple = InInsert(node->right, value, uniq);
    node->right = triple.now_root;
    node->right->parent = node;  /// родитель правого поддерева - корень
  }
  /// если узел существует в дереве и при этом флаг уникальности стоит true
  /// то вставка не произошла и возвращаем указатель на найденный узел
  if (value == node->value && uniq) triple.current_node = node;
  /// всегда балансировка при изменении структуры дерева
  triple.now_root = Balance(node);
  return triple;
}

template <typename T>
std::pair<typename AvlTree<T>::iterator, bool> AvlTree<T>::Insert(
    AvlTree<T>::value_type value) {
  /// реализация обертки
  triple triple = InInsert(_root, value, _unique);
  _root =
      triple.now_root;  /// корень - новый корень(после вставки мог измениться)
  Node *it_prev_node = PrevNode(triple.current_node);
  if (!it_prev_node) {
    it_prev_node = FindMax(_root);
  }
  return std::pair<iterator, bool>(Iterator(triple.current_node, it_prev_node),
                                   triple.third);
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::InInclude(AvlTree::Node *node, T value) {
  /// при ненахождении возвращаем nullptr
  if (node == nullptr) return nullptr;
  /// найдено
  if (node->value == value) return node;
  /// ищем в левом или правом поддереве
  if (value < node->value) {
    if (node->left) {
      return InInclude(node->left, value);
    } else {
      /// не нашлось
      return nullptr;
    }
  } else {
    if (node->right) {
      return InInclude(node->right, value);
    } else {
      /// не нашлось
      return nullptr;
    }
  }
}

template <typename T>
bool AvlTree<T>::Include(value_type value) {
  /// реализация обертки
  return InInclude(_root, value);
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::FindMin(AvlTree::Node *node) {
  if (node == nullptr) return nullptr;
  /// если слева ничего нет, то это минимальный элемент
  if (node->left == nullptr) return node;
  /// иначе идем левее
  return FindMin(node->left);
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::FindMax(AvlTree::Node *node) {
  if (node == nullptr) return nullptr;
  /// если справа ничего нет, то это максимальный элемент
  if (node->right == nullptr) return node;
  /// иначе идем левее
  return FindMax(node->right);
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::InRemoveMin(AvlTree::Node *node) {
  if (node) {  /// проверка существование узла
    /// если слева пусто, то заменяем на правый элемент
    if (node->left == nullptr) {
      return node->right;
    }
    /// иначе идем левее
    node->left = InRemoveMin(node->left);
  }
  /// всегда балансировка при изменении структуры дерева
  return Balance(node);
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::InRemove(AvlTree::Node *node, T value) {
  if (!node) return nullptr;  /// если пусто, то ничего не делаем
  /// идем либо в лево либо в право по сравнению.
  /// Для типа должно быть определено сравнение, иначе ошибка
  if (value < node->value) {
    /// уход влево
    node->left = InRemove(node->left, value);
  } else if (value > node->value) {
    /// уход вправо
    node->right = InRemove(node->right, value);
  } else {
    /// сохранение левого и правого поддерева
    Node *left = node->left;
    Node *right = node->right;
    Node *parent = node->parent;
    /// удаление узла
    delete node;
    /// уменьшаем количество узлов
    _size--;
    /// если правого нет, то замещаем на левое поддерево
    if (!right) return left;
    /// иначе ищем минимальный элемент в правом поддереве
    Node *min = FindMin(right);
    /// удаляем его справа, и устанавливаем его за место удаленного элемента
    min->right = InRemoveMin(right);
    min->left = left;
    min->parent = parent;
    /// всегда балансировка при изменении структуры дерева
    return Balance(min);
  }
  /// всегда балансировка при изменении структуры дерева
  return Balance(node);
}

template <typename T>
void AvlTree<T>::Remove(value_type value) {
  /// реализация обертки
  _root = InRemove(_root, value);
}

template <typename T>
void AvlTree<T>::DeleteTree(AvlTree::Node **p_node) {
  /// проверка существования
  if (*p_node) {
    /// проходим по дереву до самого низа и начинаем удаление оттуда
    if ((*p_node)->left) {
      DeleteTree(&((*p_node)->left));
    }
    if ((*p_node)->right) {
      DeleteTree(&((*p_node)->right));
    }
    delete *p_node;
  }
}

template <typename T>
AvlTree<T>::~AvlTree() {
  DeleteTree(&_root);
  /// дополнительно сводим к случаю базовой инициализации для уверенности
  _root = nullptr;
  _unique = false;
  _size = 0;
}
template <typename T>
void AvlTree<T>::PrintTree(AvlTree::Node *node) {
  if (node) {  /// проверка существования
    /// вывод корян
    std::cout << node->value << std::endl;
    /// проходим по дереву в лево
    if (node->left) {
      PrintTree(node->left);
    }
    /// проходим по дереву в право
    if (node->right) {
      PrintTree(node->right);
    }
  } else {
    /// не выкидываем ошибки, а сообщаем о пустоте
    std::cout << "empty" << std::endl;
  }
}

template <typename T>
void AvlTree<T>::Print() {
  /// реализация обертки
  PrintTree(_root);
}

template <typename T>
T AvlTree<T>::Top() {
  /// проверка на существование
  if (_root == nullptr) {
    throw std::runtime_error("Empty tree");
  }
  return _root->value;
}

/// Вспомогательная функция для глубокой копирования дерева
template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::CopyNodes(AvlTree<T>::Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  /// обход корень-лево-право
  Node *new_node = new Node(node->value);
  new_node->left = CopyNodes(node->left);
  new_node->right = CopyNodes(node->right);
  return new_node;
}

template <typename T>
AvlTree<T>::AvlTree(const AvlTree<T> &other) {
  /// Глубокая копия дерева
  _root = CopyNodes(other._root);
  _unique = other._unique;
  _size = other._size;
}

template <typename T>
int AvlTree<T>::CountNodes(AvlTree::Node *node, const T &value) {
  if (node == nullptr) {
    return 0;
  }
  /// обход корень-лево-право
  int count = (node->value == value) ? 1 : 0;
  count += CountNodes(node->left, value);
  count += CountNodes(node->right, value);
  return count;
}

template <typename T>
int AvlTree<T>::Count(const T &value) const {
  return CountNodes(_root, value);
}

template <typename T>
void AvlTree<T>::SetUnique() {
  _unique = true;
}

/// реализация интерфейса итератора
template <typename T>
AvlTree<T>::Iterator::Iterator() : cur_node(nullptr), prev_node(nullptr) {}

template <typename T>
AvlTree<T>::Iterator::Iterator(Node *cur_node, Node *prev_node)
    : cur_node(cur_node), prev_node(prev_node) {}

template <typename T>
AvlTree<T>::Iterator::Iterator(const iterator &other)
    : cur_node(other.cur_node), prev_node(other.prev_node) {}

template <typename T>
void AvlTree<T>::Iterator::swap(iterator &other) {
  std::swap(cur_node, other.cur_node);
  std::swap(prev_node, other.prev_node);
}

template <typename T>
typename AvlTree<T>::iterator &AvlTree<T>::iterator::operator=(
    const AvlTree<T>::iterator &other) {
  if (this != &other) {
    this->cur_node = other.cur_node;
    this->prev_node = other.prev_node;
  }
  return *this;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::NextNode(AvlTree<T>::Node *node) {
  if (!node) {
    return nullptr;
  }
  /// если есть правое поддерево то возвращаем минимальный узел
  if (node->right) {
    return FindMin(node->right);
  }
  /// если нет правого поддерева то ищем предыдущий узел
  Node *parent = node->parent;
  while (parent && parent->right == node) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

template <typename T>
typename AvlTree<T>::iterator &AvlTree<T>::iterator::operator++() {
  prev_node = cur_node;
  cur_node = NextNode(cur_node);
  return *this;
}

template <typename T>
const typename AvlTree<T>::iterator AvlTree<T>::iterator::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T>
typename AvlTree<T>::Node *AvlTree<T>::PrevNode(AvlTree<T>::Node *node) {
  if (!node) {
    return nullptr;
  }
  /// если есть левое поддерево то возвращаем максимальный узел
  if (node->left) {
    return FindMax(node->left);
  }
  /// если нет левого поддерева то ищем предыдущий узел
  Node *parent = node->parent;
  while (parent && parent->left == node) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

template <typename T>
typename AvlTree<T>::iterator &AvlTree<T>::iterator::operator--() {
  if (cur_node == nullptr) {
    cur_node = prev_node;
  } else {
    cur_node = PrevNode(cur_node);
  }
  prev_node = PrevNode(cur_node);
  return *this;
}

template <typename T>
const typename AvlTree<T>::iterator AvlTree<T>::iterator::operator--(int) {
  Iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T>
bool AvlTree<T>::Iterator::operator==(const AvlTree::iterator &it) const {
  if (this != &it) {
    if (cur_node != it.cur_node || prev_node != it.prev_node) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool AvlTree<T>::Iterator::operator!=(const AvlTree::iterator &it) const {
  return !(*this == it);
}

template <typename T>
typename AvlTree<T>::reference AvlTree<T>::Iterator::operator*() const {
  if (cur_node == nullptr) {
    throw std::runtime_error("Iterator out of range");
  }
  return cur_node->value;
}

template <typename T>
typename AvlTree<T>::iterator AvlTree<T>::begin() {
  return AvlTree<T>::Iterator(FindMin(_root), nullptr);
}

template <typename T>
typename AvlTree<T>::iterator AvlTree<T>::end() {
  if (_root == nullptr) {
    return AvlTree<T>::Iterator(nullptr, nullptr);
  }
  return AvlTree<T>::Iterator(nullptr, FindMax(_root));
}

template <typename T>
typename AvlTree<T>::iterator AvlTree<T>::Find(value_type value) {
  Node *result = InInclude(_root, value);
  if (result == nullptr) {
    return end();
  }
  return Iterator(result, PrevNode(result));
}

template <typename T>
AvlTree<T>::ConstIterator::ConstIterator() : Iterator() {}

template <typename T>
AvlTree<T>::ConstIterator::ConstIterator(const Iterator &other)
    : Iterator(other) {}

template <typename T>
typename AvlTree<T>::const_reference AvlTree<T>::ConstIterator::operator*()
    const {
  return Iterator::operator*();
}

template <typename T>
AvlTree<T> &AvlTree<T>::operator=(const AvlTree<T> &other) {
  if (this != &other) {
    DeleteTree(&_root);
    /// Глубокая копия дерева
    _root = CopyNodes(other._root);
    _unique = other._unique;
    _size = other._size;
  }
  return *this;
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_FUNCTIONS_TEMPLATES_S21_AVLTREE_TPP_
