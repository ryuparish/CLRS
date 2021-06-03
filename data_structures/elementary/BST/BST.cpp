#include <vector>
#include <iostream>

struct node{
    int value = 0;
    node* parent = NULL;
    node* left = NULL;
    node* right = NULL;
}

void inorder_tree_walk(node* walker){
    if(walker != NULL){
        inorder_tree_walk(walker->left);
        std::cout << walker->value << " ";
        inorder_tree_walk(walker->right);
    }
}

int main() {
    // Setting up the tree values
    node* root->value = 6, node1->value = 5, node2->value = 7, node3->value = 3, node4->value = 4, node5->value =1, node6->value = 2;

    // Setting up the children
    root->left = node1;
    root->right = node2;
    node1->left = node3; node1->right = node4;
    node2->left = node5; node2->right = node6;

    
