#include <gtest/gtest.h>

#include "my_shared_ptr.h"
#include "my_unique_ptr.h"

TEST(test_get, my_shared_ptr) {
  my_shared_ptr<int> ptr(new int(1));
  ASSERT_EQ(*(ptr.get()), 1);
}

TEST(test_reset, my_shared_ptr) {
  my_shared_ptr<int> ptr1(new int(1));
  ASSERT_EQ(*(ptr1.get()), 1);
  ptr1.reset(new int(5));
  ASSERT_EQ(*(ptr1.get()), 5);
  ptr1.reset();
  ASSERT_EQ(ptr1.get(), nullptr);
}

TEST(test_use_count, my_shared_ptr) {
  my_shared_ptr<int> ptr(new int(1));
  ASSERT_EQ(ptr.use_count(), 1);
  my_shared_ptr<int> ptr1(ptr);
  ASSERT_EQ(ptr.use_count(), 2);

  {
    my_shared_ptr<int> ptr2(ptr);
    ASSERT_EQ(ptr.use_count(), 3);
  }

  ASSERT_EQ(ptr.use_count(), 2);
}

TEST(test_unique_true, my_shared_ptr) {
  my_shared_ptr<int> ptr(new int(1));
  ASSERT_TRUE(ptr.unique());
}

TEST(test_unique_false, my_shared_ptr) {
  my_shared_ptr<int> ptr(new int(1));
  my_shared_ptr<int> ptr1(ptr);
  ASSERT_FALSE(ptr.unique());
}

TEST(test_observer, my_shared_ptr) {
  struct new_int {
    int val;
    new_int(int value) : val(value) {}
  };
  my_shared_ptr<new_int> ptr(new new_int(1));
  ASSERT_EQ((*ptr).val, 1);
  ASSERT_EQ(ptr->val, 1);
}

TEST(test_constructor, my_unique_ptr) {
  my_unique_ptr<int> ptr(new int(1));
  ASSERT_EQ((*ptr.get()), 1);
}

TEST(test_copy_assign, my_unique_ptr) {
  my_unique_ptr<int> ptr(new int(1));
  my_unique_ptr<int> ptr2(ptr);
  ASSERT_EQ(ptr.get(), nullptr);

  my_unique_ptr<int> ptr3 = ptr2;
  ASSERT_EQ(ptr2.get(), nullptr);
}

TEST(test_release, my_unique_ptr) {
  my_unique_ptr<int> ptr(new int(1));
  int* iptr = ptr.release();
  ASSERT_EQ(ptr.get(), nullptr);
  ASSERT_EQ(*iptr, 1);
}