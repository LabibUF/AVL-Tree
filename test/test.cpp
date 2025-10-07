

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "AVL.h"
using namespace std;

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

// the provided test from the template is below.

//Test 1: Five Incorrect Commands (Invalid Inserts and Operations)
TEST_CASE("Invalid Commands", "[error_handling]") {
    AVLTree tree;

    // Invalid ID (not 8 digits)
    REQUIRE_NOTHROW(tree.insert("A11y", 45679999));

    // Invalid Name (numbers in the name)
    REQUIRE_NOTHROW(tree.insert("John123", 12345678));

    // Duplicate ID
    tree.insert("Alice", 11111111);
    REQUIRE_NOTHROW(tree.insert("Bob", 11111111));

    // Removing a non-existent ID
    REQUIRE_NOTHROW(tree.remove(99999999));

    // Searching for a non-existent ID
    REQUIRE_NOTHROW(tree.searchID(99999999));

    // Searching for a non-existent name
    REQUIRE_NOTHROW(tree.searchName("Unknown"));

    // Remove nth node when tree is too small
    REQUIRE_NOTHROW(tree.removeNth(5));
    cout << "Labib Hossain: 87035513";
}

//Test 2: Insert Command and All Four Rotation Cases
TEST_CASE("AVL Rotations", "[rotations]") {
    AVLTree tree;

    // Right Rotation (LL Case)
    tree.insert("John", 90000000);
    tree.insert("Doe", 80000000);
    tree.insert("Labib", 70000000);
    REQUIRE_NOTHROW(tree.printPreorder()); // Expect balanced tree

    // Left Rotation (RR Case)
    tree.insert("Ernesto", 10000000);
    tree.insert("Anuj", 20000000);
    tree.insert("Muhimin", 30000000);
    REQUIRE_NOTHROW(tree.printPreorder()); // Expect balanced tree

    // Left-Right Rotation (LR Case)
    tree.insert("Akeeb", 40000000);
    tree.insert("Sofia", 35000000);
    REQUIRE_NOTHROW(tree.printPreorder());

    // Right-Left Rotation (RL Case)
    tree.insert("Isabella", 60000000);
    tree.insert("Ana", 65000000);
    REQUIRE_NOTHROW(tree.printPreorder());
    cout << "Labib Hossain: 87035513";
}

// Test 3: Insert 100 Nodes, Remove 10, and Verify Order
TEST_CASE("Large Insertions and Removals", "[performance]") {
    AVLTree tree;
    vector<int> insertedIDs;

    // Insert 100 nodes
    cout << "Labib Hossain: 87035513";
    for (int i = 10000000; i < 10100000; i += 100) {
        tree.insert("Student" + to_string(i), i);
        insertedIDs.push_back(i);
    }
    REQUIRE_NOTHROW(tree.printInorder());

    // Remove 10 random nodes
    for (int i = 0; i < 10; i++) {
        int randomIndex = rand() % insertedIDs.size();
        tree.remove(insertedIDs[randomIndex]);
        insertedIDs.erase(insertedIDs.begin() + randomIndex);
    }

    REQUIRE_NOTHROW(tree.printInorder());
    cout << "Labib Hossain: 87035513";
}

TEST_CASE("AVL Delete Cases", "[deletion]") {
    AVLTree tree;
    tree.insert("Alice", 12345678);
    tree.insert("Bob", 87654321);
    tree.insert("Charlie", 11111111);

    // Remove node with no children
    REQUIRE_NOTHROW(tree.remove(87654321));
    tree.printInorder();

    // Remove node with one child
    tree.insert("David", 99999999);
    REQUIRE_NOTHROW(tree.remove(12345678));
    tree.printInorder();

    // Remove node with two children
    tree.insert("Eve", 55555555);
    tree.insert("Frank", 66666666);
    REQUIRE_NOTHROW(tree.remove(55555555));
    tree.printInorder();
}

 */