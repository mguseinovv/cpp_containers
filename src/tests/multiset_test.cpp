#include "test_header.h"

namespace {
TEST(MultiSetConstructorTest, DefaultConstructor) {
  s21::multiset<int> multiset;

  EXPECT_TRUE(multiset.empty());
}

TEST(MultiSetConstructorTest, CopyConstructor) {
  s21::multiset<int> original = {1, 2, 3};
  s21::multiset<int> copied(original);

  EXPECT_EQ(original.size(), copied.size());
  for (auto it = original.begin(); it != original.end(); ++it) {
    EXPECT_TRUE(copied.contains(*it));
  }
}

TEST(MultiSetConstructorTest, MoveConstructor) {
  s21::multiset<int> original = {1, 2, 3};
  s21::multiset<int> moved(std::move(original));

  EXPECT_EQ(original.size(), (size_t)0);
  EXPECT_EQ(moved.size(), (size_t)3);
}

TEST(MultiSetConstructorTest, InitializerListConstructor) {
  s21::multiset<int> multiset = {1, 2, 3};

  EXPECT_EQ(multiset.size(), (size_t)3);
}

TEST(MultiSetConstructorTest, EmptyInitializerListConstructor) {
  s21::multiset<int> multiset = {};

  EXPECT_TRUE(multiset.empty());
}

TEST(MultiSetConstructorTest, DuplicateElementsInitializerListConstructor) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 3};

  EXPECT_EQ(multiset.size(), (size_t)5);
}

TEST(MultiSetConstructorTest, StringConstructor) {
  s21::multiset<std::string> multiset = {"apple", "banana", "cherry"};

  EXPECT_EQ(multiset.size(), (size_t)3);
}

TEST(MultiSetConstructorTest, LargeMultiSetConstructor) {
  s21::multiset<int> multiset;

  for (int i = 0; i < 1000; ++i) {
    multiset.insert(i);
  }

  EXPECT_EQ(multiset.size(), (size_t)1000);
}

TEST(MultiSetInsertTest, InsertSingleElement) {
  s21::multiset<int> multiset;
  multiset.insert(5);

  EXPECT_EQ(multiset.size(), (size_t)1);
}

TEST(MultiSetInsertTest, InsertDuplicateElements) {
  s21::multiset<int> multiset;
  multiset.insert(5);
  multiset.insert(5);

  EXPECT_EQ(multiset.size(), (size_t)2);
}

TEST(MultiSetInsertTest, InsertMultipleElements) {
  s21::multiset<int> multiset;
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(5);

  EXPECT_EQ(multiset.size(), (size_t)3);
}

TEST(MultiSetInsertTest, InsertLargeNumberOfElements) {
  s21::multiset<int> multiset;

  for (int i = 0; i < 1000; ++i) {
    multiset.insert(i);
  }

  EXPECT_EQ(multiset.size(), (size_t)1000);
}

TEST(MultiSetInsertTest, InsertStringElements) {
  s21::multiset<std::string> multiset;
  multiset.insert("apple");
  multiset.insert("banana");
  multiset.insert("apple");

  EXPECT_EQ(multiset.size(), (size_t)3);
}

TEST(MultiSetInsertTest, InsertMixedElements) {
  s21::multiset<int> multiset;
  multiset.insert(5);
  multiset.insert(3);
  multiset.insert(7);

  EXPECT_EQ(multiset.size(), (size_t)3);
}

TEST(MultiSetInsertTest, InsertMultipleDuplicates) {
  s21::multiset<int> multiset;
  multiset.insert(5);
  multiset.insert(5);
  multiset.insert(5);

  EXPECT_EQ(multiset.size(), (size_t)3);
}

TEST(MultiSetInsertTest, InsertLargeNumberOfElementsWithDuplicates) {
  s21::multiset<int> multiset;

  for (int i = 0; i < 1000; ++i) {
    multiset.insert(i);
    multiset.insert(i);  // Insert duplicates
  }

  EXPECT_EQ(multiset.size(), (size_t)2000);
}

TEST(MultiSetEraseTest, EraseExistingElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto it = multiset.find(2);
  multiset.erase(it);

  EXPECT_EQ(multiset.size(), (size_t)4);
  EXPECT_EQ(multiset.count(2), (size_t)1);
}

TEST(MultiSetEraseTest, EraseNonExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.find(5);
  multiset.erase(it);

  EXPECT_EQ(multiset.size(), (size_t)4);
}

TEST(MultiSetEraseTest, EraseEmptySet) {
  s21::multiset<int> multiset;
  multiset.erase(multiset.end());

  EXPECT_TRUE(multiset.empty());
}

TEST(MultiSetEraseTest, EraseLastElement) {
  s21::multiset<int> multiset = {1, 2, 3};
  multiset.erase(multiset.find(3));

  EXPECT_EQ(multiset.size(), (size_t)2);
  EXPECT_EQ(multiset.count(3), (size_t)0);
}

TEST(MultiSetFindTest, FindExistingElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto it = multiset.find(2);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 2);
}

TEST(MultiSetFindTest, FindNonExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.find(5);

  EXPECT_EQ(it, multiset.end());
}

TEST(MultiSetFindTest, FindFirstElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.find(1);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 1);
}

TEST(MultiSetFindTest, FindLastElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.find(4);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 4);
}

TEST(MultiSetFindTest, FindMiddleElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.find(2);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 2);
}

TEST(MultiSetContainsTest, ContainsExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};

  EXPECT_TRUE(multiset.contains(2));
}

TEST(MultiSetContainsTest, ContainsNonExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};

  EXPECT_FALSE(multiset.contains(5));
}

TEST(MultiSetContainsTest, ContainsFirstElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};

  EXPECT_TRUE(multiset.contains(1));
}

TEST(MultiSetContainsTest, ContainsLastElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};

  EXPECT_TRUE(multiset.contains(4));
}

TEST(MultiSetContainsTest, ContainsMiddleElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};

  EXPECT_TRUE(multiset.contains(2));
}

TEST(MultiSetContainsTest, ContainsElementFromEmptySet) {
  s21::multiset<int> multiset;

  EXPECT_FALSE(multiset.contains(2));
}

class CustomClass {
 public:
  int value;

  CustomClass() : value(0) {}

  CustomClass(int val) : value(val) {}

  CustomClass(const CustomClass &other) : value(other.value){};

  bool operator<(const CustomClass &other) const { return value < other.value; }

  bool operator>=(const CustomClass &other) const {
    return value >= other.value;
  }
  bool operator>(const CustomClass &other) const { return value > other.value; }

  bool operator==(const CustomClass &other) const {
    return value == other.value;
  }

  CustomClass &operator=(const CustomClass &other) {
    if (this != &other) {
      value = other.value;
    }
    return *this;
  }
};

TEST(MultiSetEqualRangeTest, EqualRangeExistingElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto range = multiset.equal_range(2);

  EXPECT_EQ(++range.first, range.second);
}

TEST(MultiSetEqualRangeTest, EqualRangeNonExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto range = multiset.equal_range(5);

  EXPECT_EQ(range.first, range.second);
}

TEST(MultiSetEqualRangeTest, EqualRangeCustomClass) {
  s21::multiset<CustomClass> multiset = {CustomClass(1), CustomClass(2),
                                         CustomClass(2), CustomClass(3)};
  CustomClass target(2);
  auto range = multiset.equal_range(target);

  EXPECT_EQ(*range.first, target);
  EXPECT_EQ(*range.second, target);
  EXPECT_EQ(++range.first, range.second);
}

TEST(MultiSetEqualRangeTest, EqualRangeCustomClassNonExisting) {
  s21::multiset<CustomClass> multiset = {CustomClass(1), CustomClass(2),
                                         CustomClass(3)};
  CustomClass target(4);
  auto range = multiset.equal_range(target);

  EXPECT_EQ(range.first, multiset.end());
  EXPECT_EQ(range.second, multiset.end());
}

TEST(MultiSetEqualRangeTest, EqualRangeEmptySet) {
  s21::multiset<int> multiset;
  auto range = multiset.equal_range(1);

  EXPECT_EQ(range.first, multiset.end());
  EXPECT_EQ(range.second, multiset.end());
}

TEST(MultiSetEqualRangeTest, EqualRangeFirstElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto range = multiset.equal_range(1);

  EXPECT_EQ(range.first, range.second);
  EXPECT_EQ(*range.first, 1);
  EXPECT_EQ(*range.second, 1);
}

TEST(MultiSetEqualRangeTest, EqualRangeLastElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto range = multiset.equal_range(4);

  EXPECT_EQ(range.first, range.second);
  EXPECT_EQ(*range.first, 4);
  EXPECT_EQ(*range.second, 4);
}

TEST(MultiSetEqualRangeTest, EqualRangeRangeWithMultipleElements) {
  s21::multiset<int> multiset = {1, 2, 1, 2, 3, 4};
  auto range = multiset.equal_range(2);

  EXPECT_EQ(*range.first, 2);
  EXPECT_EQ(*range.second, 2);
  EXPECT_EQ(++range.first, range.second);
}

TEST(MultiSetLowerBoundTest, LowerBoundExistingElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto it = multiset.lower_bound(2);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 2);
}

TEST(MultiSetLowerBoundTest, LowerBoundNonExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.lower_bound(5);

  EXPECT_EQ(it, multiset.end());
}

TEST(MultiSetLowerBoundTest, LowerBoundCustomClass) {
  s21::multiset<CustomClass> multiset = {CustomClass(1), CustomClass(2),
                                         CustomClass(3)};
  CustomClass target(2);
  auto it = multiset.lower_bound(target);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ((*it).value, 2);
}

TEST(MultiSetLowerBoundTest, LowerBoundEmptySet) {
  s21::multiset<int> multiset;
  auto it = multiset.lower_bound(1);

  EXPECT_EQ(it, multiset.end());
}

TEST(MultiSetLowerBoundTest, LowerBoundFirstElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.lower_bound(1);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 1);
}

TEST(MultiSetUpperBoundTest, UpperBoundExistingElement) {
  s21::multiset<int> multiset = {1, 2, 2, 3, 4};
  auto it = multiset.upper_bound(2);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 3);
}

TEST(MultiSetUpperBoundTest, UpperBoundNonExistingElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.upper_bound(2);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 3);
}

TEST(MultiSetUpperBoundTest, UpperBoundCustomClass) {
  s21::multiset<CustomClass> multiset = {CustomClass(1), CustomClass(2),
                                         CustomClass(2), CustomClass(3)};
  CustomClass target(2);
  auto it = multiset.upper_bound(target);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ((*it).value, 3);
}

TEST(MultiSetUpperBoundTest, UpperBoundEmptySet) {
  s21::multiset<int> multiset;
  auto it = multiset.upper_bound(1);

  EXPECT_EQ(it, multiset.end());
}

TEST(MultiSetUpperBoundTest, UpperBoundLastElement) {
  s21::multiset<int> multiset = {1, 2, 3, 4};
  auto it = multiset.upper_bound(4);

  EXPECT_EQ(it, multiset.end());
}

// TEST(MultiSetInsertManyTest, InsertManyIntegers) {
//   s21::multiset<int> multiset;
//   auto result = multiset.insert_many(1, 2, 3, 4, 5);

//   EXPECT_EQ(result.size(), (size_t)5);
//   for (const auto &pair : result) {
//     EXPECT_TRUE(pair.second);  // Ensure all elements were inserted
//   }

//   EXPECT_EQ(multiset.size(), (size_t)5);
// }

// TEST(MultiSetInsertManyTest, InsertManyStrings) {
//   s21::multiset<std::string> multiset;
//   auto result = multiset.insert_many("apple", "banana", "cherry");

//   EXPECT_EQ(result.size(), (size_t)3);
//   for (const auto &pair : result) {
//     EXPECT_TRUE(pair.second);  // Ensure all elements were inserted
//   }

//   EXPECT_EQ(multiset.size(), (size_t)3);
// }

// TEST(MultiSetInsertManyTest, InsertManyCustomClass) {
//   s21::multiset<std::pair<int, std::string>> multiset;
//   auto result =
//       multiset.insert_many(std::make_pair(1, "one"), std::make_pair(2,
//       "two"));

//   EXPECT_EQ(result.size(), (size_t)2);
//   for (const auto &pair : result) {
//     EXPECT_TRUE(pair.second);  // Ensure all elements were inserted
//   }

//   EXPECT_EQ(multiset.size(), (size_t)2);
// }

// TEST(MultiSetInsertManyTest, InsertManyDuplicates) {
//   s21::multiset<int> multiset;
//   auto result = multiset.insert_many(1, 2, 3, 3, 4, 4, 4);

//   EXPECT_EQ(result.size(),
//             (size_t)7);  // All elements should be considered inserted
//   EXPECT_EQ(multiset.size(), (size_t)7);  // Size should reflect all elements
//   for (const auto &pair : result) {
//     EXPECT_TRUE(pair.second);  // Ensure all elements were inserted
//   }
// }
}  // namespace