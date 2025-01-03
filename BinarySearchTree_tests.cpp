#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

using namespace std;


TEST(check_sorting_invariant) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(bst_public_test_rehash) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST (bst_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);

}

TEST (bst_copy_constructor) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> treeb(tree);
    ASSERT_TRUE(treeb.empty());
    ASSERT_EQUAL(tree.size(), treeb.size());
    tree.insert(7);
    tree.insert(3);
    tree.insert(9);
    BinarySearchTree<int> treec(tree);
    BinarySearchTree<int>::Iterator it = tree.begin();
    BinarySearchTree<int>::Iterator cit = treec.begin();
    ASSERT_EQUAL(tree.size(), treec.size());
    while (it != tree.end() && cit != treec.end()) {
        ASSERT_EQUAL(*it, *cit);
        ++it;
        ++cit;
    }
    ASSERT_TRUE(it == tree.end() && cit == treec.end());
    tree.insert(11);
    ASSERT_NOT_EQUAL(tree.size(), treec.size());
    BinarySearchTree<int> treed(tree);
    tree.insert(18);
    ASSERT_NOT_EQUAL(tree.size(), treed.size());
    treeb.insert(7);
    treeb.insert(9);
    treeb.insert(11);
    BinarySearchTree<int> treee(treeb);
    BinarySearchTree<int>::Iterator bit = treeb.begin();
    BinarySearchTree<int>::Iterator eit = treee.begin();
    ASSERT_EQUAL(treeb.size(), treee.size());
    while (bit != treeb.end() && eit != treee.end()) {
        ASSERT_EQUAL(*bit, *eit);
        ++bit;
        ++eit;
    }
    ASSERT_TRUE(bit == treeb.end() && eit == treee.end());
}

TEST (bst_find) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(9);
    auto it = tree.find(3);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 3);
    it = tree.find(8);
    ASSERT_TRUE(it == tree.end());
    tree.insert(13);
    it = tree.find(7);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 7)
    it = tree.find(13);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 13);
}

TEST (bst_height) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.height() == 0);
    tree.insert(5);
    ASSERT_TRUE(tree.height() == 1);
    tree.insert(8);
    ASSERT_TRUE(tree.height() == 2);
    tree.insert(15);
    ASSERT_TRUE(tree.height() == 3);
    tree.insert(2);
    ASSERT_TRUE(tree.height() == 3);
}

TEST (bst_inorder) {
    BinarySearchTree<int> tree;
    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "");
    oss_inorder.str("");
    oss_inorder.clear();
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.traverse_inorder(oss_inorder);
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
    oss_inorder.str("");
    oss_inorder.clear();
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.traverse_inorder(oss_inorder);
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "2 3 4 5 6 7 8 ");
}

TEST (bst_preorder) {
    BinarySearchTree<int> tree;
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "");
    oss_preorder.str("");
    oss_preorder.clear();
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.traverse_preorder(oss_preorder);
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");
    oss_preorder.str("");
    oss_preorder.clear();
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.traverse_preorder(oss_preorder);
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "5 3 2 4 7 6 8 ");
}

TEST (bst_insert) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_EQUAL(tree.size(), 1);
    BinarySearchTree<int>::Iterator it = tree.begin();
    ASSERT_EQUAL(*it, 5);
    BinarySearchTree<double> treed;
    treed.insert(5.0);
    ASSERT_EQUAL(treed.size(), 1);
    BinarySearchTree<double>::Iterator dit = treed.begin();
    ASSERT_EQUAL(*dit, 5.0);
    BinarySearchTree<char> treec;
    treec.insert('C');
    ASSERT_EQUAL(treec.size(), 1);
    BinarySearchTree<char>::Iterator cit = treec.begin();
    ASSERT_EQUAL(*cit, 'C');
}

TEST (bst_max) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator it = tree.max_element();
    ASSERT_TRUE(it == tree.end());
    tree.insert(5);
    it = tree.max_element();
    ASSERT_TRUE(*it = 5);
    tree.insert(3);
    it = tree.max_element();
    ASSERT_TRUE(*it = 5);
    tree.insert(7);
    tree.insert(9);
    it = tree.max_element();
    ASSERT_TRUE(*it == 9);
}

TEST (bst_min) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator it = tree.min_element();
    ASSERT_TRUE(it == tree.end());
    tree.insert(5);
    it = tree.min_element();
    ASSERT_TRUE(*it = 5);
    tree.insert(7);
    it = tree.min_element();
    ASSERT_TRUE(*it = 5);
    tree.insert(3);
    tree.insert(9);
    it = tree.min_element();
    ASSERT_TRUE(*it == 3);
}

TEST (bst_min_greater_than) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(9);
    tree.insert(1);
    BinarySearchTree<int>::Iterator it = tree.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 3);
    ++it;
    ASSERT_EQUAL(*it, 5);
    ++it;
    ASSERT_EQUAL(*it, 7);
    it = tree.begin();
    ASSERT_EQUAL(*it, 1);
}

TEST (bst_check_invariants) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST_MAIN()
