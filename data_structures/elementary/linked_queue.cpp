#include <iostream>
// Implementing a stack using only a linked list
// I did not use the heap and used the stack instead. This is considered
// bad practice for large lists.

struct link{
    int value = 0;
    link* next = NULL;
};

void pop(link*& start) {
    // Start is a pointer the first object in the linked list
    // If start is not pointing to NULL, point the starter at the 2nd elem
    if(start != NULL){
        start = start->next;
    }
}
        
void push(link*& start, link& x){
    if(start != NULL){
        // x will point at what start is pointing at
        x.next = start;
        start = &x;
    }
}

void print_list(link*& start){
    link* walker = (link*)malloc(sizeof(link*));
    walker = start;
    while(walker != NULL){
        std::cout << walker->value << "\n";
        walker = walker->next;
    }
}
    
int main() {
    link* starter = NULL;
    // Creating the links
    link link1; link1.value = 1; link1.next = NULL;
    link link2; link2.value = 2; link2.next = NULL;
    link link3; link3.value = 3; link3.next = NULL;
    
    // Linking them together
    starter = &link1;
    link1.next = &link2;
    link2.next = &link3;

    // Print out the current list 
    print_list(starter);

    // Push a link onto the stack and print
    link link4; link4.value = 0;
    push(starter, link4);
    std::cout << "Printing the list after pushing:\n";
    print_list(starter);

    // Popping a link and printing
    pop(starter);
    std::cout << "Printing the list after popping:\n";
    print_list(starter);
    
    return 0;
}
    
    
