//
// Created by labib on 2/14/2025.
//

#include "AVL.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Get height of a node
int AVLTree::getHeight(AVLTreeNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

// Get balance factor
int AVLTree::getBalanceFactor(AVLTreeNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return leftHeight - rightHeight;
    }
}

// Right Rotation
AVLTreeNode* AVLTree::rotateRight(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left Rotation
AVLTreeNode* AVLTree::rotateLeft(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert Node and Balance
AVLTreeNode* AVLTree::insertNode(AVLTreeNode* node, string name, int gatorID) {
    // If the current node is null, create a new node with the given name and ID
    if (node == nullptr) {
        return new AVLTreeNode(name, gatorID);
    }

    // Insert into the left subtree if gatorID is smaller
    if (gatorID < node->gatorID) {
        node->left = insertNode(node->left, name, gatorID);
    }
    // Insert into the right subtree if gatorID is greater
    else if (gatorID > node->gatorID) {
        node->right = insertNode(node->right, name, gatorID);
    }
    // If the gatorID already exists, do nothing (no duplicates allowed)
    else {
        return node;
    }

    // Update the height of the current node
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + max(leftHeight, rightHeight);

    // Get the balance factor to check if rebalancing is needed
    int balance = getBalanceFactor(node);

    // Left-Left (Right Rotation)**
    if (balance > 1 && gatorID < node->left->gatorID) {
        return rotateRight(node);
    }

    // Right-Right (Left Rotation)**
    if (balance < -1 && gatorID > node->right->gatorID) {
        return rotateLeft(node);
    }

    // Left-Right (Left Rotation on left child, then Right Rotation)**
    if (balance > 1 && gatorID > node->left->gatorID) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left (Right Rotation on right child, then Left Rotation)**
    if (balance < -1 && gatorID < node->right->gatorID) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return the unchanged node pointer
    return node;
}


bool AVLTree::isValidName(const string& name) {
    for (size_t i = 0; i < name.length(); i++) {
        char c = name[i];
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

// Checks if an ID already exists in the tree
bool AVLTree::containsID(AVLTreeNode* node, int gatorID) {
    if (!node) return false;
    if (node->gatorID == gatorID) return true;
    if (gatorID < node->gatorID) {
        return containsID(node->left, gatorID);
    } else {
        return containsID(node->right, gatorID);
    }
}


// Insert function
void AVLTree::insert(string name, int gatorID) {
    if (containsID(root, gatorID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    root = insertNode(root, name, gatorID);
    cout << "successful" << endl;
}


// Inorder Traversal
void AVLTree::inorderTraversal(AVLTreeNode* node, vector<string>& names) {
    if (node) {
        inorderTraversal(node->left, names);
        names.push_back(node->name);
        inorderTraversal(node->right, names);
    }
}

// printInorder
void AVLTree::printInorder() {
    vector<string> names;
    inorderTraversal(root, names);
    for (size_t i = 0; i < names.size(); ++i) {
        cout << names[i];
        if (i < names.size() - 1) cout << ", ";
    }
    cout << endl;
}

// Level Count
int AVLTree::getLevelCount(AVLTreeNode* node) {
    if (!node) return 0;
    return 1 + max(getLevelCount(node->left), getLevelCount(node->right));
}

void AVLTree::printLevelCount() {
    cout << getLevelCount(root) << endl;
}

// Search by ID
void AVLTree::searchID(int gatorID) {
    AVLTreeNode* current = root;
    while (current) {
        if (gatorID == current->gatorID) {
            cout << current->name << endl;
            return;
        } else if (gatorID < current->gatorID) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "unsuccessful" << endl;
}

// Search by Name
void AVLTree::searchName(string name) {
    bool found = false;
    vector<int> ids;
    vector<AVLTreeNode *> stack;
    AVLTreeNode *current = root;

    while (current || !stack.empty()) {
        while (current) {
            stack.push_back(current);
            current = current->left;
        }
        current = stack.back();
        stack.pop_back();

        if (current->name == name) {
            ids.push_back(current->gatorID);
            found = true;
        }

        current = current->right;
    }

    if (found) {
        for (size_t i = 0; i < ids.size(); i++) {
            cout << ids[i] << endl;
        }
    } else {
        cout << "unsuccessful" << endl;
    }
}

AVLTreeNode* AVLTree::findMin(AVLTreeNode* node) {
    while (node->left) node = node->left;
    return node;
}

AVLTreeNode* AVLTree::removeNode(AVLTreeNode* node, int gatorID) {
    if (!node){
        return nullptr;
    }

    // Search for the node
    if (gatorID < node->gatorID)
        node->left = removeNode(node->left, gatorID);
    else if (gatorID > node->gatorID)
        node->right = removeNode(node->right, gatorID);
    else {
        // Case 1: No child
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
            // Case 2: One child
        else if (!node->left || !node->right) {
            AVLTreeNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
            // Case 3: Two children
        else {
            AVLTreeNode* successor = findMin(node->right);
            node->gatorID = successor->gatorID;
            node->name = successor->name;
            node->right = removeNode(node->right, successor->gatorID);
        }
    }

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Check balance
    int balance = getBalanceFactor(node);

    // Left Heavy
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Heavy
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::remove(int gatorID) {
    if (!root || !containsID(root, gatorID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    root = removeNode(root, gatorID);
    cout << "successful" << endl;
}


void AVLTree::inorderTraversal(AVLTreeNode* node, vector<int>& gatorIDs) {
    if (node) {
        inorderTraversal(node->left, gatorIDs);
        gatorIDs.push_back(node->gatorID);
        inorderTraversal(node->right, gatorIDs);
    }
}

void AVLTree::removeNth(int N) {
    vector<int> gatorIDs;
    inorderTraversal(root, gatorIDs);

    // Explicitly cast gatorIDs.size() to int to avoid signed/unsigned comparison issues
    if (N >= 0 && N < static_cast<int>(gatorIDs.size())) {
        remove(gatorIDs[N]);
    } else {
        cout << "unsuccessful" << endl;
    }
}

// Helper function for preorder traversal
void AVLTree::preorderTraversal(AVLTreeNode* node, vector<string>& names) {
    if (node) {
        names.push_back(node->name);
        preorderTraversal(node->left, names);
        preorderTraversal(node->right, names);
    }
}

// Public function to print preorder traversal
void AVLTree::printPreorder() {
    vector<string> names;
    preorderTraversal(root, names);
    for (size_t i = 0; i < names.size(); ++i) {
        cout << names[i];
        if (i < names.size() - 1) cout << ", ";
    }
    cout << endl;
}

// Helper function for postorder traversal
void AVLTree::postorderTraversal(AVLTreeNode* node, vector<string>& names) {
    if (node) {
        postorderTraversal(node->left, names);
        postorderTraversal(node->right, names);
        names.push_back(node->name);
    }
}

// Public function to print postorder traversal
void AVLTree::printPostorder() {
    vector<string> names;
    postorderTraversal(root, names);
    for (size_t i = 0; i < names.size(); ++i) {
        cout << names[i];
        if (i < names.size() - 1) cout << ", ";
    }
    cout << endl;
}





