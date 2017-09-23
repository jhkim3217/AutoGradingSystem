#include "gtest/gtest.h"
#include "../isomorphic_array.h"
#include "../isomorphic_node.h"
#include "../isomorphic_linkedList.h"

/***********************************
          CASE 1 : Array
***********************************/
TEST(Array,Root_has_null) {
  int validArray[6] = {0,};

  EXPECT_TRUE(isomorphic_array<int>(NULL, NULL));
  EXPECT_FALSE(isomorphic_array<int>(NULL, validArray));
  EXPECT_FALSE(isomorphic_array<int>(validArray, NULL));
}

TEST(Array,has_different_size) {
  double Array_size_of_6[6] = {1,2,3,4,5,6};
  double Array_size_of_7[7] = {1,2,3,4,5,6,7};

  EXPECT_FALSE(isomorphic_array<double>(Array_size_of_6, Array_size_of_7));
}

TEST(Array,has_different_value) {
  int Array_1to6[6] = {1,2,3,4,5,6};
  int Array_multiples_of_2_from_1[6] = {1,2,4,8,16,32};
  int Array_divisors_of_12[6] = {1,2,3,4,6,12};

  EXPECT_FALSE(isomorphic_array<int>(Array_1to6, Array_multiples_of_2_from_1));
  EXPECT_FALSE(isomorphic_array<int>(Array_multiples_of_2_from_1,Array_divisors_of_12));
  EXPECT_FALSE(isomorphic_array<int>(Array_divisors_of_12,Array_1to6));
}

TEST(Array,is_isomorphic_case_of_integer) {
  int Array[6] = {1,2,3,4,5,6};
  int Array2[6] = {1,2,3,4,5,6};

  EXPECT_TRUE(isomorphic_array<int>(Array, Array2));
}

TEST(Array,is_isomorphic_case_of_double) {
  double Array[6] = {1.1,2.2,3.3,4.4,5.5,6.6};
  double Array2[6] = {1.1,2.2,3.3,4.4,5.5,6.6};

  EXPECT_TRUE(isomorphic_array<double>(Array, Array2));
}

TEST(Array,is_isomorphic_case_of_character) {
  char Array[6] = {'a','b','c','d','e','f'};
  char Array2[6] = {'a','b','c','d','e','f'};

  EXPECT_TRUE(isomorphic_array<char>(Array, Array2));
}

/***********************************
          CASE 2 : Node
***********************************/
class Node : public ::testing::Test {
 protected:
  virtual void SetUp() {
    root = new node<int>(1);

    node_size_of_3 = new node<int>(1);
    node_size_of_3->next = new node<int>(2);
    node_size_of_3->next->next = new node<int>(3);

    node_size_of_4 = new node<int>(1);
    node_size_of_4->next = new node<int>(2);
    node_size_of_4->next->next = new node<int>(3);
    node_size_of_4->next->next->next = new node<int>(4);
  }

  virtual void TearDown() {
    /*Generally, this scope must free
    the dynamic memory allocation area*/
  }

  node<int> *root;
  node<int> *node_size_of_3;
  node<int> *node_size_of_4;
};

TEST_F(Node, has_object) {
  node<int>* nodeObject = root;

  EXPECT_TRUE(isomorphic_node<int>(NULL,NULL));
  EXPECT_FALSE(isomorphic_node<int>(nodeObject,NULL));
  EXPECT_FALSE(isomorphic_node<int>(NULL,nodeObject));
}

TEST_F(Node, has_different_size) {
  EXPECT_FALSE(isomorphic_node
    (node_size_of_3,node_size_of_4));
}

TEST_F(Node, has_different_value) {
  node_size_of_3->next->next->next = new node<int>(5);
  EXPECT_FALSE(isomorphic_node
    (node_size_of_3,node_size_of_4));
}

TEST_F(Node, is_isomorphic) {
  node_size_of_3->next->next->next = new node<int>(4);

  EXPECT_TRUE(isomorphic_node
    (node_size_of_3,node_size_of_4));
}


/***********************************
          CASE 3 : Linked List
***********************************/
class Linked_List : public ::testing::Test {
 protected:
   virtual void SetUp() {
     M1 = new linkedList<int>;
     M2 = new linkedList<int>;
   }
   virtual void TearDown() {
     delete M1;
     delete M2;
   }
   linkedList<int>* M1;
   linkedList<int>* M2;
};

TEST_F(Linked_List, hasObject) {
  EXPECT_FALSE(isomorphic_linkedList<int>(M1, NULL));
  EXPECT_FALSE(isomorphic_linkedList<int>(NULL, M2));
  EXPECT_TRUE(isomorphic_linkedList<int>(NULL,NULL));
}

TEST_F(Linked_List, Insert) {
  M1->insert(30);
  M2->insert(40);
  // EXPECT_FALSE(isomorphic_linkedList(M1,M2));
}
