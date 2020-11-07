#include <iostream>

struct RBData {
    int key;
    int x, y;
    int quantity;
};

enum Colour {RED, BLACK}; 

struct Node {
    Colour colour;
    RBData data;
    Node *left, *right, *parent;

	Node() { 
       this->colour = BLACK; 
       left = right = NULL; 
    }

	Node(RBData data) { 
       this->colour = RED; 
       this->data = data; 
       parent = NULL; 
    }
};

typedef Node *N;

class RBTree {
    private:
        N root, nil;
        void leftRotate(N x);
        void rightRotate(N x);
        void RBInsertFix(N z);
        int searchTree(N node, int key, int quantity);
        void printTree(N node, std::string indent, bool last);
    public:
        RBTree() {
            nil = new Node;
            root = nil;
        }
        void RBInsert(RBData data);
        std::string search(int key, int quantity, std::string name);
        void print();
};