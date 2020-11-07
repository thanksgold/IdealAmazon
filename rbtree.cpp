#include "rbtree.h"

void RBTree::leftRotate(N x) {
    N y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
};

void RBTree::rightRotate(N x) {
    N y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
};

void RBTree::RBInsertFix(N z) { 
    while (z->parent->colour == RED) {
        if (z->parent == z->parent->parent->left) {
            N y = z->parent->parent->right;
            if (y->colour == RED) {
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            N y = z->parent->parent->left;
            if (y->colour == RED) {
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                leftRotate(z->parent->parent);
            }
        }
        if (z == root) {
            break;
        }
    }
    root->colour = BLACK;
}

int RBTree::searchTree(N node, int key, int quantity) {
    if (node == NULL)
        return 0;
    if (node->data.key == key) {
        if (node->data.quantity >= quantity) {
            node->data.quantity -= quantity;
            return 2;
        }
        return 1;
    }
    if (node->data.key > key)
        return searchTree(node->left, key, quantity);
    return searchTree(node->right, key, quantity);
}

void RBTree::printTree(N node, std::string indent, bool last) {
    if (node != nil) {
        std::cout<<indent;
        if (last) {
            std::cout<<"R----";
            indent += "     ";
        } else {
            std::cout<<"L----";
            indent += "|    ";
        }
        
        std::string sColor = (node->colour==RED)?"RED":"BLACK";
        std::cout<<node->data.key<<"("<<sColor<<")\n";
        printTree(node->left, indent, false);
        printTree(node->right, indent, true);
    }
}

void RBTree::RBInsert(RBData data) { 
    N z = new Node(data);
    z->left = nil;
    z->right = nil;

    N y = NULL;
    N x = root;

    while (x != nil) {
        y = x;
        if (z->data.key < x->data.key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        root = z;
    else if (z->data.key < y->data.key)
        y->left = z;
    else
        y->right = z;
    
    if (z->parent == NULL){
        z->colour = BLACK;
        return;
    }

    if (z->parent->parent == NULL)
        return;
    
    RBInsertFix(z);
}

std::string RBTree::search(int key, int quantity, std::string name) {
    if (quantity <= 0)
        throw std::invalid_argument("not valid quantity");
    int r = searchTree(root, key, quantity);
    if (r==0)
        return "Yo " + name + ", your order is not found. Sorry, IdealAmazon\n";
    else if (r==2)
        return "Yo " + name + ", your order is on the way! Cheers, IdealAmazon\n";
    return "Yo " + name + ", not enough quantity available for your order :( Apologies, IdealAmazon\n";
};

void RBTree::print() {
    printTree(root, "", true);
}