// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <vector>

template <typename T>
class BST {
public:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    int getDepth(Node* node) const {
        if (!node) return 0;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    void inOrderCollect(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        inOrderCollect(node->left, vec);
        vec.push_back({node->value, node->count});
        inOrderCollect(node->right, vec);
    }

public:
    BST() : root(nullptr) {}
    
    ~BST() {
        destroy(root);
    }

    void insert(T value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* curr = root;
        while (true) {
            if (value == curr->value) {
                curr->count++;
                return;
            } else if (value < curr->value) {
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr->left = new Node(value);
                    return;
                }
            } else {
                if (curr->right) {
                    curr = curr->right;
                } else {
                    curr->right = new Node(value);
                    return;
                }
            }
        }
    }

    int depth() const {
        int d = getDepth(root);
        return d > 0 ? d - 1 : 0;
    }

    int search(T value) const {
        Node* curr = root;
        while (curr) {
            if (value == curr->value) return curr->count;
            else if (value < curr->value) curr = curr->left;
            else curr = curr->right;
        }
        return 0;
    }

    void getElements(std::vector<std::pair<T, int>>& vec) const {
        inOrderCollect(root, vec);
    }
};
#endif  // INCLUDE_BST_H_
