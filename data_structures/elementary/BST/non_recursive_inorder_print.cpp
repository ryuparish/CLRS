// This is incomplete code that only includes a function definition with no other data.

void non_recursive_inorder(Tree tree){
    Stack S;
    node* curr = tree.root;
    while(true){
        if (curr != NULL){
            S.push(curr->value);
            curr = curr->left;
        }
        else {
            curr = S.pop();
            std::cout << curr->value << " ";
            curr = curr->right;
        }
    }
}
