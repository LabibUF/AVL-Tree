//
// Created by labib on 2/14/2025.
//

#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class AVLTreeNode {
public:
    string name;
    int gatorID;
    int height;
    AVLTreeNode* left;
    AVLTreeNode* right;

    AVLTreeNode(string name, int gatorID) {
        this->name = name;
        this->gatorID = gatorID;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }

};

class AVLTree {
private:
    AVLTreeNode* root;

    // Helper functions
    int getHeight(AVLTreeNode* node);
    int getBalanceFactor(AVLTreeNode* node);
    AVLTreeNode* rotateRight(AVLTreeNode* y);
    AVLTreeNode* rotateLeft(AVLTreeNode* x);
    AVLTreeNode* insertNode(AVLTreeNode* node, std::string name, int gatorID);
    AVLTreeNode* findMin(AVLTreeNode* node);
    AVLTreeNode* removeNode(AVLTreeNode* node, int gatorID);
    int getLevelCount(AVLTreeNode* node);
    bool containsID(AVLTreeNode* node, int gatorID);

    // Traversal Functions
    void inorderTraversal(AVLTreeNode* node, std::vector<std::string>& names);
    void inorderTraversal(AVLTreeNode* node, std::vector<int>& gatorIDs);
    void preorderTraversal(AVLTreeNode* node, std::vector<std::string>& names);
    void postorderTraversal(AVLTreeNode* node, std::vector<std::string>& names);

public:
    AVLTree() : root(nullptr) {}
    void insert(std::string name, int gatorID);
    void remove(int gatorID);
    void removeNth(int N);
    void searchID(int gatorID);
    void searchName(std::string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    bool isValidName(const string& name);
};

#endif //PROJECT1_AVL_H
