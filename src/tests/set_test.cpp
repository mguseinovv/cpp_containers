#include "test_header.h"

namespace {
TEST(Set, Constructor_Default) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Initializer_list) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(SetConstructorTest, CopyConstructor) {
  s21::set<int> originalSet = {1, 2, 3};
  s21::set<int> copiedSet(originalSet);
  EXPECT_EQ(originalSet.size(), (size_t)copiedSet.size());
}

TEST(SetConstructorTest, MoveConstructor) {
  s21::set<int> originalSet = {1, 2, 3};
  s21::set<int> movedSet(std::move(originalSet));
  EXPECT_EQ(originalSet.size(), (size_t)0);
  EXPECT_EQ(movedSet.size(), (size_t)3);
}

TEST(Set, Modifier_Insert_1) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_set_1.begin();
  ++it;
  s21_set_1.insert('b');
  s21_set_1.insert('a');
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Insert_2) {
  s21::set<char> s21_set;

  s21_set.insert('b');
  s21_set.insert('b');
  s21_set.insert('b');

  EXPECT_EQ(s21_set.size(), size_t(1));
}

TEST(Set, Modifier_Insert_3) {
  s21::set<float> s21_set;
  std::set<float> std_set;

  s21_set.insert(0.0000000000000000000000000000000000000000001);
  s21_set.insert(0.000000000000000000000000000000000000000000099);
  std_set.insert(0.0000000000000000000000000000000000000000001);
  std_set.insert(0.000000000000000000000000000000000000000000099);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetEraseTest, EraseSingleElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.erase(mySet.find(10));
  EXPECT_TRUE(mySet.empty());
}

TEST(SetEraseTest, EraseNonExistingElement) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.erase(mySet.find(5));
  EXPECT_EQ(mySet.size(), (size_t)1);
}

TEST(SetEraseTest, EraseMultipleElements) {
  s21::set<int> mySet;
  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.erase(mySet.find(5));
  EXPECT_EQ(mySet.size(), (size_t)2);
}

TEST(SetEraseTest, EraseLastElement) {
  s21::set<int> mySet;
  mySet.insert(4);
  mySet.insert(10);
  mySet.erase(mySet.find(10));
  EXPECT_EQ(mySet.size(), (size_t)1);
}

TEST(SetSwapTest, SwapEmptySets) {
  s21::set<int> set1;
  s21::set<int> set2;

  set1.swap(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_TRUE(set2.empty());
}

TEST(SetSwapTest, SwapNonEmptyWithEmptySet) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2;

  set1.swap(set2);

  EXPECT_TRUE(set1.empty());
  EXPECT_EQ(set2.size(), (size_t)3);
}

TEST(SetSwapTest, SwapNonEmptySets) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), (size_t)3);
  EXPECT_EQ(set2.size(), (size_t)3);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_FALSE(set1.contains(1));
}

TEST(SetSwapTest, SwapSetsOfDifferentSizes) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), (size_t)2);
  EXPECT_EQ(set2.size(), (size_t)3);
  EXPECT_TRUE(set1.contains(4));
  EXPECT_FALSE(set1.contains(1));
}

TEST(Set, Modifier_Merge) {
  s21::set<int> s21_set_1 = {1, 2, 3};
  s21::set<int> s21_set_2 = {3, 4, 5, 6};
  s21::set<int> s21_set_3 = {1, 2, 3, 4, 5, 6};
  s21_set_1.merge(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it3 = s21_set_3.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_3.size());
}

TEST(Set, Lookup_Contains) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(2), true);
  EXPECT_EQ(s21_set.contains(3), true);
  EXPECT_EQ(s21_set.contains(4), true);
  EXPECT_EQ(s21_set.contains(7), false);
  EXPECT_EQ(s21_set.contains(-2), false);
  EXPECT_EQ(s21_set.contains(0), false);
}

TEST(Set, Lookup_Find) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  auto it_end = s21_set.end();
  EXPECT_EQ(*(s21_set.find(1)), 1);
  EXPECT_EQ(*(s21_set.find(3)), 3);
  EXPECT_EQ(*(s21_set.find(4)), 4);
  EXPECT_EQ(*(s21_set.find(2)), 2);
  EXPECT_EQ(s21_set.find(-4), it_end);
  EXPECT_EQ(s21_set.find(0), it_end);
  EXPECT_EQ(s21_set.find(120), it_end);
}

TEST(Set, Rehash_And_Insert_In_Collision) {
  s21::set<std::string> s21_set;
  std::unordered_set<std::string> std_set;
  s21_set.insert("asd");
  s21_set.insert("asa");
  s21_set.insert("asf");
  s21_set.insert("asg");
  s21_set.insert("ash");
  s21_set.insert("aqw");
  s21_set.insert("fgh");
  s21_set.insert("ghf");
  s21_set.insert("dghfg");
  s21_set.insert("dghfdsg");
  s21_set.insert("dghfgfsadfsd");
  s21_set.insert("dghfgfsadfsdasd");
  s21_set.insert("dghfgfsadfsasdasdd");
  s21_set.insert("dghfgfsadfsdasdasd");
  s21_set.insert("dghfgfdsasadfdsasasdsadsad");
  s21_set.insert("dghdsafgfsadfdsasasdsadsad");
  s21_set.insert("ådsdghfgfsadfdsasasdsadsad");
  s21_set.insert("dghfgfsadfdsasasdsaddsasad");
  s21_set.insert("dghfgfsadfdsasassadadsadsad");
  s21_set.insert("dghfgfsadfdsasdasasdsadsad");
  s21_set.insert("dghasdaasdfgfsadfsasdsadsad");
  s21_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  s21_set.insert("dghfgfsadfasdsasdsadsad");
  s21_set.insert("dghfgfsadfsasdsadsad");
  s21_set.insert("dghfgfsasdadfsasdsadsad");
  s21_set.insert("asdsadadghfgfsadfsasdsadsad");
  std_set.insert("asd");
  std_set.insert("asa");
  std_set.insert("asf");
  std_set.insert("asg");
  std_set.insert("ash");
  std_set.insert("aqw");
  std_set.insert("fgh");
  std_set.insert("ghf");
  std_set.insert("dghfg");
  std_set.insert("dghfdsg");
  std_set.insert("dghfgfsadfsd");
  std_set.insert("dghfgfsadfsdasd");
  std_set.insert("dghfgfsadfsasdasdd");
  std_set.insert("dghfgfsadfsdasdasd");
  std_set.insert("dghfgfdsasadfdsasasdsadsad");
  std_set.insert("dghdsafgfsadfdsasasdsadsad");
  std_set.insert("ådsdghfgfsadfdsasasdsadsad");
  std_set.insert("dghfgfsadfdsasasdsaddsasad");
  std_set.insert("dghfgfsadfdsasassadadsadsad");
  std_set.insert("dghfgfsadfdsasdasasdsadsad");
  std_set.insert("dghasdaasdfgfsadfsasdsadsad");
  std_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  std_set.insert("dghfgfsadfasdsasdsadsad");
  std_set.insert("dghfgfsadfsasdsadsad");
  std_set.insert("dghfgfsasdadfsasdsadsad");
  std_set.insert("asdsadadghfgfsadfsasdsadsad");
  for (auto i : std_set) {
    EXPECT_TRUE(s21_set.find(i) != s21_set.end());
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

}  // namespace