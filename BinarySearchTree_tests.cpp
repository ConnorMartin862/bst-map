#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(check_sorting_invariant) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST_MAIN()
