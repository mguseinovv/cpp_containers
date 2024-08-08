#include "test_header.h"

namespace {
TEST(Map, test_default_constructor) {
  s21::map<std::string, int> our_dict;
  std::map<std::string, int> orig_dict;
  EXPECT_EQ(our_dict.empty(), orig_dict.empty());
}

TEST(Map, test_initializer_list) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
  };
  EXPECT_EQ(our_dict.empty(), orig_dict.empty());
  EXPECT_TRUE(our_dict.contains(std::string("Igor")));
  // EXPECT_EQ(our_dict.size(), orig_dict.size());
  auto it = our_dict.begin();
  auto it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, test_copy_constructor) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
  };
  auto our_copy = our_dict;
  EXPECT_EQ(our_dict.empty(), our_copy.empty());
  EXPECT_EQ(our_dict.contains(std::string("Igor")),
            our_copy.contains(std::string("Igor")));
  EXPECT_EQ(our_dict.contains(std::string("Egor")),
            our_copy.contains(std::string("Egor")));
  EXPECT_NE(our_dict.contains(std::string("Igor")),
            our_copy.contains(std::string("Egor")));
  // EXPECT_EQ(our_dict.size(), orig_dict.size());
}

TEST(Map, test_move_constructor) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
  };
  auto our_copy = std::move(our_dict);
  EXPECT_TRUE(our_dict.empty());
  EXPECT_FALSE(our_copy.empty());
  EXPECT_TRUE(our_copy.contains(std::string("Igor")));
}

TEST(Map, test_move_assignment) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
  };
  s21::map<std::string, int> our_dict_2;
  our_dict_2 = std::move(our_dict);

  EXPECT_TRUE(our_dict.empty());
  EXPECT_FALSE(our_dict_2.empty());
  EXPECT_TRUE(our_dict_2.contains(std::string("Igor")));
}

TEST(Map, test_assignment) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
  };
  s21::map<std::string, int> our_dict_2;
  our_dict_2 = our_dict;

  EXPECT_FALSE(our_dict.empty());
  EXPECT_FALSE(our_dict_2.empty());
  EXPECT_TRUE(our_dict_2.contains(std::string("Igor")));
  EXPECT_TRUE(our_dict.contains(std::string("Igor")));
}

TEST(Map, iterator) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, at) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  orig_dict.at(std::string("Igor")) = 2002;
  our_dict.at(std::string("Igor")) = 2002;
  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, brackets_insert) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  orig_dict["Matvey"] = 2034;
  our_dict["Matvey"] = 2034;
  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, brackets_edit) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  orig_dict["Eva"] = 2031;
  our_dict["Eva"] = 2031;
  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, insert) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  auto inserted_orig_one_arg = orig_dict.insert({"Sofya", 2037});
  auto inserted_our_one_arg =
      our_dict.insert(std::pair<std::string, int>{"Sofya", 2037});

  auto inserted_orig_two_arg = orig_dict.insert({"Mariya", 2036});
  auto inserted_our_two_arg = our_dict.insert("Mariya", 2036);
  EXPECT_EQ(inserted_orig_one_arg.second, inserted_our_one_arg.second);
  EXPECT_EQ(inserted_orig_two_arg.second, inserted_our_two_arg.second);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

// TEST(Map, insert_many) {
//   s21::map<std::string, int> our_dict = {
//       {"Igor", 2001},
//       {"Anna", 1983},
//       {"Eva", 2015},
//       {"Christie", 2019},
//   };
//   std::map<std::string, int> orig_dict = {
//       {"Igor", 2001},     {"Anna", 1983},      {"Eva", 2015},
//       {"Christie", 2019}, {"Vladislav", 2056}, {"Miroslava", 2067},
//       {"Yaroslav", 2070},
//   };
//   auto inserted_many_our =
//       our_dict.insert_many(std::pair<std::string, int>{"Vladislav", 2056},
//                            std::pair<std::string, int>{"Miroslava", 2067},
//                            std::pair<std::string, int>{"Yaroslav", 2070});
//   typename s21::map<std::string, int>::iterator it = our_dict.begin();
//   typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
//   for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
//     EXPECT_EQ((*it).second(), (*it_).second);
//   }
// }

TEST(Map, insert_existing_key) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  auto inserted_orig_one_arg = orig_dict.insert({"Eva", 2033});
  auto inserted_our_one_arg =
      our_dict.insert(std::pair<std::string, int>{"Eva", 2033});
  EXPECT_EQ(inserted_orig_one_arg.second, inserted_our_one_arg.second);
  auto inserted_orig_two_arg = orig_dict.insert({"Mariya", 2036});
  auto inserted_our_two_arg = our_dict.insert("Mariya", 2036);
  EXPECT_EQ(inserted_orig_two_arg.second, inserted_our_two_arg.second);
  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

// TEST(Map, insert_many_existing_key) {
//   s21::map<std::string, int> our_dict = {
//       {"Igor", 2001},
//       {"Anna", 1983},
//       {"Eva", 2015},
//       {"Christie", 2019},
//   };
//   std::map<std::string, int> orig_dict = {
//       {"Igor", 2001},     {"Anna", 1983},     {"Eva", 2015},
//       {"Christie", 2019}, {"Yaroslav", 2070},
//   };
//   auto inserted_many_our =
//       our_dict.insert_many(std::pair<std::string, int>{"Igor", 2056},
//                            std::pair<std::string, int>{"Eva", 2067},
//                            std::pair<std::string, int>{"Yaroslav", 2070});
//   typename s21::map<std::string, int>::iterator it = our_dict.begin();
//   typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
//   for (; it != our_dict.end(); ++it, ++it_) {
//     EXPECT_EQ((*it).second(), (*it_).second);
//   }
// }

// TEST(Map, insert_many_empty_map) {
//   std::map<std::string, int> orig_dict = {
//       {"Igor", 2056},
//       {"Eva", 2067},
//       {"Yaroslav", 2070},
//   };
//   s21::map<std::string, int> our_dict;
//   auto inserted_many_our =
//       our_dict.insert_many(std::pair<std::string, int>{"Igor", 2056},
//                            std::pair<std::string, int>{"Eva", 2067},
//                            std::pair<std::string, int>{"Yaroslav", 2070});
//   typename s21::map<std::string, int>::iterator it = our_dict.begin();
//   typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
//   for (; it != our_dict.end(); ++it, ++it_) {
//     EXPECT_EQ((*it).second(), (*it_).second);
//   }
// }

TEST(Map, insert_empty_map) {
  s21::map<std::string, int> our_dict;
  std::map<std::string, int> orig_dict;
  auto inserted_orig = orig_dict.insert({"Eva", 2033});
  auto inserted_our = our_dict.insert(std::pair<std::string, int>{"Eva", 2033});
  EXPECT_EQ(inserted_orig.second, inserted_our.second);
  auto inserted_orig_two_arg = orig_dict.insert({"Mariya", 2036});
  auto inserted_our_two_arg = our_dict.insert("Mariya", 2036);
  EXPECT_EQ(inserted_orig_two_arg.second, inserted_our_two_arg.second);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, insert_or_assign) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  auto inserted_orig_one_arg = orig_dict.insert_or_assign("Sofya", 2037);
  auto inserted_our_one_arg = our_dict.insert_or_assign("Sofya", 2037);
  auto inserted_orig_two_arg = orig_dict.insert_or_assign("Eva", 2033);
  auto inserted_our_two_arg = our_dict.insert_or_assign("Eva", 2033);
  EXPECT_EQ(inserted_orig_one_arg.second, inserted_our_one_arg.second);
  EXPECT_EQ(inserted_orig_two_arg.second, inserted_our_two_arg.second);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, insert_or_assign_empty_map) {
  s21::map<std::string, int> our_dict;
  std::map<std::string, int> orig_dict;
  auto inserted_orig = orig_dict.insert_or_assign("Eva", 2033);
  auto inserted_our = our_dict.insert_or_assign("Eva", 2033);
  EXPECT_EQ(inserted_orig.second, inserted_our.second);
  auto inserted_orig_two_arg = orig_dict.insert_or_assign("Mariya", 2036);
  auto inserted_our_two_arg = our_dict.insert_or_assign("Mariya", 2036);
  EXPECT_EQ(inserted_orig_two_arg.second, inserted_our_two_arg.second);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, test_erase) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  our_dict.erase(our_dict.begin());
  orig_dict.erase(orig_dict.begin());

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, test_erase_2) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };

  auto iter = our_dict.begin();
  auto iter_orig = orig_dict.begin();
  ++iter;
  ++iter_orig;
  our_dict.erase(iter);
  orig_dict.erase(iter_orig);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, test_erase_doesnt_exist) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  s21::map<std::string, int> our_buf = {
      {"Mariya", 2035},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };

  auto iter = our_buf.begin();
  our_dict.erase(iter);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, test_merge) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  s21::map<std::string, int> dict_to_merge = {
      {"Danil", 2018},
      {"Dmitry", 2018},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},     {"Anna", 1983},  {"Eva", 2015},
      {"Christie", 2019}, {"Danil", 2018}, {"Dmitry", 2018},
  };
  our_dict.merge(dict_to_merge);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, merge_empty_map) {
  s21::map<std::string, int> our_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  std::map<std::string, int> orig_dict = {
      {"Igor", 2001},
      {"Anna", 1983},
      {"Eva", 2015},
      {"Christie", 2019},
  };
  s21::map<std::string, int> dict_to_merge;
  our_dict.merge(dict_to_merge);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

TEST(Map, merge_to_empty_map) {
  s21::map<std::string, int> our_dict;
  std::map<std::string, int> orig_dict = {
      {"Danil", 2018},
      {"Dmitry", 2018},
  };

  s21::map<std::string, int> dict_to_merge = {
      {"Danil", 2018},
      {"Dmitry", 2018},
  };

  our_dict.merge(dict_to_merge);

  typename s21::map<std::string, int>::iterator it = our_dict.begin();
  typename std::map<std::string, int>::iterator it_ = orig_dict.begin();
  for (; it != our_dict.end() || it_ != orig_dict.end(); ++it, ++it_) {
    EXPECT_EQ((*it).second(), (*it_).second);
  }
}

}  // namespace