#include <iostream>
#include <stdlib.h>
// Implementing a queue using only a linked list
// Used some heap allocation, but there is definitely memory leakage.

struct link{
    int value = 0;
    link* next = NULL;
};

void dequeue(link*& start) {
    // Start is a pointer the first object in the linked list
    // If start is not pointing to NULL, point the starter at the 2nd elem
    link* walker = (link*)malloc(sizeof(link*));
    walker = start;
    while(walker->next != NULL){
        if(walker->next->next == NULL){
            link* next_holder = (link*)malloc(sizeof(link*));
            next_holder = walker->next;
            walker->next = NULL;
            walker = next_holder;
            break;
        }
        walker = walker->next;
    }
    std::cout << "Freeing: " << walker->value << "\n";
    free(walker);
}
        
void queue(link*& start, link*& x){
    if(start != NULL){
        // x will point at what start is pointing at
        x->next = start;
        start = x;
    }
}

void print_list(link*& start){
    link* walker = (link*)malloc(sizeof(link*));
    walker = start;
    while(walker != NULL){
        std::cout << walker->value << "\n";
        walker = walker->next;
    }
    free(walker);
}
    
int main() {
    link* starter = (link*)malloc(sizeof(link*));
    // Creating the links
    link* link1 = (link*)malloc(sizeof(link*)); 
    link1->value = 1; link1->next = NULL;
    link* link2 = (link*)malloc(sizeof(link*)); 
    link2->value = 2; link2->next = NULL;
    link* link3 = (link*)malloc(sizeof(link*)); 
    link3->value = 3; link3->next = NULL;
    
    // Linking them together
    starter = link1;
    link1->next = link2;
    link2->next = link3;

    // Print out the current list 
    print_list(starter);

    // Push a link onto the stack and print
    link* link4 = (link*)malloc(sizeof(link*));
    link4->value = 0;
    queue(starter, link4);
    std::cout << "Printing the list after pushing:\n";
    print_list(starter);

    // Popping a link and printing
    dequeue(starter);
    std::cout << "Printing the list after popping:\n";
    print_list(starter);
    
    // Freeing all the data in the linked list
    while(starter != NULL){
        link* temp = (link*)malloc(sizeof(link*));
        temp = starter;
        starter = starter->next;
        free(temp);
    }
    free(starter);
    return 0;
}
