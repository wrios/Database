#include <gtest/gtest.h>
#include <algorithm>
#include <sstream> 
#include "../src/linear_set.h"
#include "../src/Registro.h"

template < class T > using my_set = linear_set < T > ;

class SetTest : public testing::Test {
protected:
  my_set<int> empty;
  my_set<int> ordered;
  my_set<int> inversed;
  my_set<int> smaller;
  my_set<string> string_set;

  void SetUp() {
    for (int i = 0; i < 5; i++) {
      ordered.insert(i);
      inversed.insert(4 - i);
    }
    for (int i = 0; i < 3; i++) {
      smaller.insert(i);
    }

    vector<string> string_keys = {"Haciendo", "palmas", "arriba", "y",
                                  "arriba",   "ese",    "coro"};
    for (int i = 0; i < string_keys.size(); i++) {
      string_set.insert(string_keys[i]);
    }
  }
};

TEST(set_test, empty_constructor) {
  my_set<int> a;
  my_set<string> b;
  my_set<pair<string, int>> c;
  my_set<my_set<int>> x;
}

TEST(set_test, init_list) {
  my_set<int> a = {1, 2, 3, 4, 5};
  my_set<string> b = {"Hola", "como", "va", "?"};
  my_set<my_set<int>> c = {{1, 2, 3}, {1, 2, 3}};
}

TEST_F(SetTest, count) {
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(ordered.count(i), i < 5);
    EXPECT_EQ(inversed.count(i), i < 5);
    EXPECT_EQ(smaller.count(i), i < 3);
    EXPECT_EQ(empty.count(i), false);
  }
}

TEST_F(SetTest, empty) {
  EXPECT_TRUE(empty.empty());
  EXPECT_FALSE(ordered.empty());
  EXPECT_FALSE(inversed.empty());
  EXPECT_FALSE(smaller.empty());
  EXPECT_FALSE(string_set.empty());
}

TEST_F(SetTest, size) {
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(ordered.size(), 5);
  EXPECT_EQ(inversed.size(), 5);
  EXPECT_EQ(smaller.size(), 3);
  EXPECT_EQ(string_set.size(), 6);
}

TEST_F(SetTest, copy) {
  auto copy_empty = empty;
  auto copy_ordered = ordered;
  auto copy_string = string_set;

  EXPECT_EQ(copy_empty.size(), 0);
  EXPECT_EQ(copy_ordered.size(), 5);
  EXPECT_EQ(copy_string.size(), 6);
}

TEST_F(SetTest, iterator) {
  auto copy_ordered = linear_set<int>();
  for (auto x : ordered) {
    copy_ordered.insert(x);
  }

  auto copy_string = linear_set<string>();
  for (auto x : string_set) {
    copy_string.insert(x);
  }

  EXPECT_EQ(copy_ordered, ordered);
  EXPECT_EQ(copy_string, string_set);
}

TEST_F(SetTest, const_iterator) {
  const linear_set<int> &const_ordered = ordered;
  linear_set<int> copy_ordered;
  auto end = const_ordered.end();
  for (auto it = const_ordered.begin(); it != end; ++it) {
    copy_ordered.insert(*it);
  }

  const linear_set<string> &const_string = string_set;
  linear_set<string> copy_string;
  for (auto x : const_string) {
    copy_string.insert(x);
  }

  EXPECT_EQ(copy_ordered, ordered);
  EXPECT_EQ(copy_string, string_set);
}

TEST_F(SetTest, mostrar) {
  stringstream ss_ordered;
  ss_ordered << ordered;
  EXPECT_EQ(ss_ordered.str(), string("{ 0, 1, 2, 3, 4 }"));
}

TEST_F(SetTest, algorithm_copy) {
  linear_set<int> in = {1, 2, 3, 4};
  list<int> out(in.begin(), in.end());

  linear_set<Registro> in_regs = {Registro({"LU"}, {datoStr("123/45")}),
                                  Registro({"LU"}, {datoStr("124/45")})};
  list<Registro> out_regs;
  copy(in.begin(), in.end(), out.begin());
}

TEST_F(SetTest, erase_by_key) {
  auto copy = ordered;
  EXPECT_TRUE(copy.count(3));
  EXPECT_EQ(copy.erase(3), 1);
  EXPECT_FALSE(copy.count(3));
  EXPECT_EQ(copy.size(), 4);
}

TEST_F(SetTest, iterator_find_test) {
  EXPECT_EQ(ordered.find(-1), ordered.end());
  EXPECT_EQ(ordered.find(5), ordered.end());
  EXPECT_NE(ordered.find(3), ordered.end());
}

TEST_F(SetTest, iterator_test) {
  EXPECT_EQ(empty.begin(), empty.end());
  EXPECT_NE(ordered.begin(), ordered.end());

  std::list<int> ks, vs, a = {0, 1, 2, 3, 4}, b = {4, 3, 2, 1, 0};
  for (auto p : ordered) {
    ks.push_back(p);
  }
  EXPECT_EQ(ks, a);

  for (auto p : inversed) {
    vs.push_back(p);
  }
  EXPECT_EQ(vs, b);
}

TEST_F(SetTest, insert_by_iterator) {
  auto m1 = ordered;
  EXPECT_EQ(*m1.insert(6).first, 6);
  EXPECT_EQ(*m1.insert(-1).first, -1);
}

TEST_F(SetTest, erase_by_iterator) {
  auto m1 = ordered;
  EXPECT_EQ(m1.erase(1), 1);
  EXPECT_EQ(m1.find(1), m1.end());
  EXPECT_EQ(m1.erase(4), 1);
}

