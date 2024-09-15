#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>

class Node {
protected:
  int data;
  Node *left;
  Node *right;
  friend class AVL;

  Node() {
    data = 0;
    left = nullptr;
    right = nullptr;
  }
};

class AVL {
private:
  Node *root;

public:
  AVL() { root = nullptr; }

  Node *getRoot() { return root; }

  int getData(Node *node) { return node->data; }

  Node *insertNode(Node *node, int value) {
    if (node == nullptr) {
      Node *newnode = new Node();
      newnode->data = value;
      return newnode;
    } else {

      if (value < node->data) {
        node->left = insertNode(node->left, value);
      } else if (value > node->data) {
        node->right = insertNode(node->right, value);
      } else {
        return node;
      }
    }

    int balanceFactor = getBalanceFactor(node);
    int leftBalanceFactor = getBalanceFactor(node->left);
    int rightBalanceFactor = getBalanceFactor(node->right);

    // std::cout << "root: " << balanceFactor
    //           << " left tree: " << leftBalanceFactor
    //           << " right tree: " << rightBalanceFactor << std::endl;

    if (balanceFactor > 1) {       // Left subtree longer, rotate right
      if (leftBalanceFactor < 0) { // Right-left rotation
        // std::cout << "LEFT RIGHT" << std::endl;
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
      } else if (leftBalanceFactor > 0) { // LEFT LEFT
        // std::cout << "LEFT LEFT" << std::endl;
        root = rotateRight(root);
      }
    } else if (balanceFactor < -1) { // Right subtree longer, rotate left
      if (rightBalanceFactor < 0) {  //  RIGHT RIGHT
        // std::cout << "RIGHT RIGHT" << std::endl;
        node = rotateLeft(node);
      } else if (rightBalanceFactor > 0) { // Left-right rotation
        // std::cout << "RIGHT LEFT" << std::endl;
        node->left = rotateLeft(node->left);
        // std::cout << "testing" << std::endl;
        node = rotateRight(node);
      }
    }
    return node;
    // Otherwise tree is already balanced
  }

  Node *deleteNode(Node *node, int value) {
    if (node == nullptr) {
      return nullptr;
    } else {

      if (value < node->data) {
        node->left = deleteNode(node->left, value);
      } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
      } else {
        if (node->left == nullptr &&
            node->right == nullptr) { // Both children non existent
          return nullptr;
        } else if (node->left == nullptr) { // Left child non existent
          return node->right;
        } else if (node->right == nullptr) { // Right child non existent
          return node->left;
        } else { // Both children exist
          Node *maxNode = getMaxNode(node->left);

          node->data = maxNode->data;

          node->left = deleteNode(node->left, node->data);
        }
      }

      int balanceFactor = getBalanceFactor(node);
      int leftBalanceFactor = getBalanceFactor(node->left);
      int rightBalanceFactor = getBalanceFactor(node->right);

      // std::cout << "root: " << balanceFactor
      //           << " left tree: " << leftBalanceFactor
      //           << " right tree: " << rightBalanceFactor << std::endl;

      if (balanceFactor > 1) {       // Left subtree longer, rotate right
        if (leftBalanceFactor < 0) { // Right-left rotation
          // std::cout << "LEFT RIGHT" << std::endl;
          node->right = rotateRight(node->right);
          node = rotateLeft(node);
        } else if (leftBalanceFactor > 0) { // LEFT LEFT
          // std::cout << "LEFT LEFT" << std::endl;
          root = rotateRight(root);
        }
      } else if (balanceFactor < -1) { // Right subtree longer, rotate left
        if (rightBalanceFactor < 0) {  //  RIGHT RIGHT
          // std::cout << "RIGHT RIGHT" << std::endl;
          node = rotateLeft(node);
        } else if (rightBalanceFactor > 0) { // Left-right rotation
          // std::cout << "RIGHT LEFT" << std::endl;
          node->left = rotateLeft(node->left);
          node = rotateRight(node);
        }
      }
      return node;
    }
  }

  Node *getMaxNode(Node *node) {
    if (node->left == nullptr && node->right == nullptr) {
      return node;
    } else if (node->right != nullptr) {
      node = getMaxNode(node->right);
    } else if (node->left != nullptr) {
      node = getMaxNode(node->left);
    }

    return node;
  }

  int getBalanceFactor(Node *node) {
    if (node == nullptr) {
      return 0;
    } else {
      // std::cout << height(node->left) << " " << height(node->right) <<
      // std::endl;
      return height(node->left) - height(node->right);
    }
  }

  void insertNode(int value) { root = insertNode(root, value); }

  void deleteNode(int value) { root = deleteNode(root, value); }

  int height(Node *node) {
    if (node == nullptr) {
      return 0;
    } else {

      int leftSubtreeHeight = height(node->left);
      int rightSubtreeHeight = height(node->right);

      if (leftSubtreeHeight > rightSubtreeHeight) {
        return (leftSubtreeHeight + 1);
      } else {
        // std::cout << rightSubtreeHeight + 1 << std::endl;
        return (rightSubtreeHeight + 1);
      }
    }
  }

  Node *rotateRight(Node *node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }
    Node *newRoot = node->left;
    Node *rightSub = newRoot->right;

    newRoot->right = node;
    node->left = rightSub;

    return newRoot;
  }

  Node *rotateLeft(Node *node) {
    if (node == nullptr || node->right == nullptr) {
        return node;
    }

    Node *newRoot = node->right;
    Node *leftSub = newRoot->left;

    newRoot->left = node;
    node->right = leftSub;

    return newRoot;
  }

  void printPreorder(Node *node) {
    if (node == nullptr) {
      return;
    } else {
      std::cout << node->data << " ";
      printPreorder(node->left);
      printPreorder(node->right);
    }
  }

  void printPostorder(Node *node) {
    if (node == nullptr) {
      return;
    } else {
      printPostorder(node->left);
      printPostorder(node->right);
      std::cout << node->data << " ";
    }
  }

  void printInorder(Node *node) {
    if (node == nullptr) {
      return;
    } else {
      printInorder(node->left);
      std::cout << node->data << " ";
      printInorder(node->right);
    }
  }
};

int main() {
  AVL tree;
  std::string input;

  std::getline(std::cin, input);

  std::stringstream ss(input);

  std::string instruction;
  std::string printType;

  char instructionType;
  int value = 0;
  while (ss >> instruction) {
    if (instruction == "PRE") {
      printType = "PRE";
    } else if (instruction == "POST") {
      printType = "POST";
    } else if (instruction == "IN") {
      printType = "IN";
    } else {
      instructionType = instruction[0];

      value = 0;
      for (size_t i = 1; i < instruction.size(); i++) {
        value = value * 10;
        value = value + (instruction[i] - '0');
      }

      // std::cout << value << std::endl;

      if (instructionType == 'A') {
        // std::cout << "ADD" << std::endl;
        tree.insertNode(value);
      } else if (instructionType == 'D') {
        // std::cout << "DELETE" << std::endl;
        tree.deleteNode(value);
      }
    }
  }

  Node *root = tree.getRoot();

  if (printType == "PRE") {
    tree.printPreorder(root);
  } else if (printType == "IN") {
    tree.printInorder(root);
  } else if (printType == "POST") {
    tree.printPostorder(root);
  }
}