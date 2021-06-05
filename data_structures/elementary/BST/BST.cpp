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

// Only to be used by the treeDelete function
// This function seems to destroy node1 and replace it with node2
//void transplant(node*& root, node*& node1, node*& node2){
//    if(node1->parent == NULL){
//        root = node2; }
//    else if(node1 == node1->parent->left){
//        node1->parent->left = node2;
//    }
//    else{node1->parent->right == node2;}
//    if(node2 = NULL){
//        node2->parent = node2->parent;
//    }
//}

//void treeDelete(node*& root, node*& target_node){
//    if(target_node->left == NULL){
//        transplant(root, target_node, target_node->right);
//    }
//    else if(target_node->right == NULL){
//        transplant(root, target_node, target_node->left);
//    }
//    else{
//        node* smallest_left = treeMinimum(target_node->right);
//        if(smallest_left->parent != target_node){
//            transplant(root, smallest_left, smallest_left->right);
//            smallest_left->right = target_node->right;
//            smallest_left->right->parent = smallest_left;
//        }
//        transplant(root, target_node, smallest_left);
//        smallest_left->left = target_node->left;
//        smallest_left->left->parent = smallest_left;
//    }
//}
        

void treeInsert(node*& root, node*& new_node){
    // This is also called a trailing pointer
    node* previous_holder = new node;

    // Copying the value of the root so we can use the walker
    node* walker = new node;
    walker->value = root->value;
    walker->left = root->left;
    walker->right = root->right;
    walker->parent = root->parent;

    // Conclusively finds a null place to put new node
    while(walker != NULL){
        previous_holder = walker;
        if(new_node->value < walker->value){
            walker = walker->left;
        }
        else{walker = walker->right;}
    }

    new_node->parent = previous_holder;
    // If the root was NULL and there was no tree
    if(previous_holder == NULL){
        root = new_node;
    }
    else if(new_node->value < previous_holder->value){
        previous_holder->left = new_node;
    }
    else{previous_holder->right = new_node;}
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

// Unfinished, this is the same thing as the above function, and needs to be changed to give the predecessor
node* treePredecessor(node* Node){
    if(Node->left != NULL){
        return treeMaximum(Node->left);
    }
    node* left = Node->left;
    // Will conclusively return either the left child or NULL
    while(left != NULL && left->value >= Node->right->value){
        Node = left;
        left = left->left;
    }
    return left;
}

//void treeInsert(node* root, node* new_node){
//    node* 

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
    std::cout << "Here is the successor of the value 2: "; 
    if (treeSuccessor(node3) != NULL){
        std::cout << treeSuccessor(node3)->value << "\n";
    }
    else{std::cout << "nothing was found\n";}

    // The predecessor of the node with the value 2
    std::cout << "Here is the predecessor of the value 9: "; 
    if (treePredecessor(node2) != NULL){
        std::cout << treePredecessor(node2)->value << "\n";
    }
    else{std::cout << "nothing was found\n";}

    // Adding the number one to the tree
    std::cout << "Now adding the value 8 to the tree\n";
    node* node8 = new node;
    node8->value = 8;
    treeInsert(root, node8);
    inorderTreeWalk(root);

    // Too lazy to implement this today
    // Deleting the node with the number 3
    //std::cout << "Now deleting the number 3 from the list\n";
    //treeDelete(root, node1);
    //inorderTreeWalk(root);
    return 0;

}
    
