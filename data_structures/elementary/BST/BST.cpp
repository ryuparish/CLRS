#include <iostream>

struct node{
    int value = 0;
    node* parent = NULL;
    node* left = NULL;
    node* right = NULL;
};

void inorderTreeWalk(node*& walker){
    //if(sizeof(walker) == sizeof(node*)){
    if(walker != NULL){
        // std::cout << walker->parent << " <- value of the walker pointer\n";
        inorderTreeWalk(walker->left);
        std::cout << walker->value << " ";
        inorderTreeWalk(walker->right);
    }
}

node* treeSearch(node*& Node, int k){
    // We either did or did not find the node with the key value (conclusive)
    if(Node == NULL || Node->value == k){
        return Node;
    }
    if(k < Node->value){
        return treeSearch(Node->left, k);
    }
    else {return treeSearch(Node->right, k);}
}
        
node* treeMinimum(node* Node){
    while(Node->left != NULL){
        Node = Node->left;
    }
    return Node;
}

node* treeMaximum(node* Node){
    while(Node->right != NULL){
        Node = Node->right;
    }
    return Node;
}

node* treeSuccessor(node* Node){
    if(Node->right != NULL){
        return treeMinimum(Node->right);
    }
    node* parent = Node->parent;
    while(parent != NULL && Node->value == parent->right->value){
        Node = parent;
        parent = parent->parent;
    }
    return parent;
}

int main() {
    // Setting up the tree values
    // PLEASE READ THESE! 
    //
    // REMEMBER! WHEN YOU DO "node* node_pointer" YOU ARE ONLY RECEIVING A POINTER ALLOCATION, !!!NOT!!! THE MEMORY FOR THE VALUE TO BE STORED. YOU !!!MUST!!! USE MALLOC,CALLOC,NEW...
    // Stating the type of pointer is for the purpose of the compiler knowing what type of operations can be done on the derefernced version of the pointer.
    //
    // Using new instead of (node*)malloc(sizeof(node*)) will save you from having the explicitely set the values of value, parent, left, and right. Doing so will also result in some sort of memory error I 
    // do not completely understand. The new operator will properly run the object's code and set these values to NULL, while malloc will NOT.
    node* root = new node;
    node* node1 = new node;
    node* node2 = new node;
    node* node3 = new node;
    node* node4 = new node;
    node* node5 = new node;
    node* node6 = new node;

    root->value = 6;
    node1->value = 3;
    node2->value = 9;
    node3->value = 2;
    node4->value = 4;
    node5->value = 7;
    node6->value = 10;

    // Setting up the children
    root->left = node1;
    root->right = node2;
    node1->left = node3; node1->right = node4;
    node2->left = node5; node2->right = node6;
    node3->parent = node1; node4->parent = node1; node5->parent = node2; node6->parent = node2;

    // Print out the tree in order
    inorderTreeWalk(root);

    // Search tree for the value 7
    node* found = treeSearch(root, 7);
    if(found){
        std::cout << "\nFound the value: " << 7 << "\n";
    }

    // Finding the maximum
    std::cout << "Here is the maximum: " << treeMaximum(root)->value << "\n";

    // Finding the minimum
    std::cout << "Here is the minimum: " << treeMinimum(root)->value << "\n";

    // The successor of the node with the value 2
    std::cout << "Here is the parent of the value 2: "; 
    if (treeSuccessor(node3) != NULL){
        std::cout << treeSuccessor(node3)->value << "\n";
        return 0;
    }
    std::cout << "nothing was found\n";

    return 0;
}
    
