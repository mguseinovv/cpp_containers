#include "test_header.h"

namespace {
TEST(ArrayMemberFunctions, default_constructor) {
  s21::array<int> own_array;
  ASSERT_EQ(own_array.begin(), nullptr);
}

TEST(ArrayMemberFunctions, initialization_list_constructor) {
  s21::array<int> arr = {1, 2, 3, 4, 5};

  EXPECT_EQ(static_cast<int>(arr.size()), 5);

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayMemberFunctions, copy_constructor) {
  s21::array<int> original = {1, 2, 3, 4, 5};

  s21::array<int> copy(original);

  ASSERT_EQ(copy.size(), original.size());
  for (size_t i = 0; i < original.size(); ++i) {
    ASSERT_EQ(copy[i], original[i]);
  }
}

TEST(ArrayMemberFunctions, move_constructor) {
  s21::array<int> temp = {1, 2, 3};

  s21::array<int> moved(std::move(temp));

  ASSERT_EQ(static_cast<int>(temp.size()), 0);
  ASSERT_EQ(temp.data(), nullptr);

  ASSERT_EQ(static_cast<int>(moved.size()), 3);
  for (size_t i = 0; i < moved.size(); ++i) {
    ASSERT_EQ(moved[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayMemberFunctions, move_operator) {
  s21::array<int> original = {1, 2, 3, 4, 5};

  s21::array<int> move_from = {10, 20, 30};

  // Перемещаем данные из move_from в original с помощью оператора перемещения
  original = std::move(move_from);

  // Проверяем, что данные original после перемещения правильные
  EXPECT_EQ(static_cast<int>(original.size()), 3);
  EXPECT_EQ(original[0], 10);
  EXPECT_EQ(original[1], 20);
  EXPECT_EQ(original[2], 30);

  // Проверяем, что данные в move_from теперь нулевые
  EXPECT_EQ(static_cast<int>(move_from.size()), 0);
  EXPECT_EQ(move_from.data(), nullptr);
}

TEST(ArrayElementAccess, access_within_range) {
  s21::array<int> own_array{1, 2, 3, 4, 5};
  ASSERT_EQ(static_cast<int>(own_array.at(0)), 1);
  ASSERT_EQ(static_cast<int>(own_array.at(3)), 4);
  ASSERT_EQ(static_cast<int>(own_array.at(4)), 5);
}

TEST(ArrayElementAccess, access_out_of_range) {
  s21::array<int> own_array{1, 2, 3, 4, 5};
  ASSERT_THROW(own_array.at(5), std::out_of_range);
}

TEST(ArrayElementAccess, access_front_within_range) {
  s21::array<int> own_array{1, 2, 3, 4, 5};
  ASSERT_EQ(static_cast<int>(own_array.front()), 1);
}

TEST(ArrayElementAccess, access_front_empty_array) {
  s21::array<int> own_array;
  ASSERT_THROW(own_array.front(), std::out_of_range);
}

TEST(ArrayElementAccess, access_back_within_range) {
  s21::array<int> own_array{1, 2, 3, 4, 5};
  ASSERT_EQ(static_cast<int>(own_array.back()), 5);
}

TEST(ArrayElementAccess, access_back_empty_array) {
  s21::array<int> own_array;
  ASSERT_THROW(own_array.back(), std::out_of_range);
}

TEST(ArrayIterators, empty_array) {
  s21::array<int> own_array;
  ASSERT_EQ(own_array.begin(), nullptr);
  EXPECT_TRUE(own_array.empty());
  EXPECT_EQ(static_cast<int>(own_array.size()), 0);
}

TEST(ArrayIterators, begin_end) {
  s21::array<int> own_array{1, 2, 3, 4, 5};

  auto it_begin = own_array.begin();
  auto it_end = own_array.end();

  // Проверяем, что разница между итераторами равна размеру вектора
  ASSERT_EQ(static_cast<size_t>(std::distance(it_begin, it_end)),
            own_array.size());

  ASSERT_EQ(*it_begin, 1);
  ASSERT_EQ(*(--it_end), 5);
}

TEST(ArrayIterators, IterateThrougharray) {
  s21::array<int> own_array{1, 2, 3, 4, 5};

  int expected_value = 1;
  for (int& it : own_array) {
    ASSERT_EQ(it, expected_value);
    ++expected_value;
  }
}

TEST(ArrayIterators, ModifyarrayElements) {
  s21::array<int> own_array{1, 2, 3, 4, 5};

  int new_value = 10;
  for (int& it : own_array) {
    it = new_value;
    ++new_value;
  }

  new_value = 10;
  for (int& it : own_array) {
    ASSERT_EQ(it, new_value);
    ++new_value;
  }
}

TEST(ArrayCapacity, max_size) {
  // Создаем массив с типом элементов int
  s21::array<int> own_array;

  // Определяем ожидаемое максимальное количество элементов в массиве int
  typename s21::array<int>::size_type expected_max_size =
      std::numeric_limits<typename s21::array<int>::size_type>::max();

  // Вызываем метод max_size() и сохраняем результат
  typename s21::array<int>::size_type actual_max_size = own_array.max_size();

  // Проверяем, что возвращаемое значение max_size() соответствует ожидаемому
  EXPECT_EQ(actual_max_size, expected_max_size);
}

TEST(ArrayModifiers, swap) {
  s21::array<int> arr1{1, 2, 3};
  s21::array<int> arr2{4, 5};

  arr1.swap(arr2);

  ASSERT_EQ(static_cast<int>(arr1.size()), 2);
  ASSERT_EQ(static_cast<int>(arr2.size()), 3);

  ASSERT_EQ(static_cast<int>(arr1.at(0)), 4);
  ASSERT_EQ(static_cast<int>(arr1.at(1)), 5);

  ASSERT_EQ(static_cast<int>(arr2.at(0)), 1);
  ASSERT_EQ(static_cast<int>(arr2.at(1)), 2);
  ASSERT_EQ(static_cast<int>(arr2.at(2)), 3);
}

TEST(ArrayModifiers, fill) {
  const int fill_value = 777;

  s21::array<int> my_array{0, 0, 0, 0, 0};

  // Заполняем массив заданным значением
  my_array.fill(fill_value);

  // Проверяем, что все элементы массива равны заполненному значению
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(my_array[i], fill_value);
  }
}
}  // namespace