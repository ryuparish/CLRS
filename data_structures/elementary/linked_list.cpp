#include <iostream>
#include <stdlib.h>

// Implementing a queue using only a linked list
// Used some heap allocation, but there is definitely memory leakage.

struct link{
    int value = 0;
    link* next = NULL;
};

// O(1) time
void list_delete(link*& start) {
    // Start is a pointer the first object in the linked list
    link* temp = (link*)malloc(sizeof(link*));
    temp = start;
    start = start->next;
    free(temp);
}

// O(1) time
void list_insert(link*& start, link*& x){
    x->next = start->next;
    start = x;
}

// O(n) in the worst case
void list_search(link*& start, int len, int a){
    // Searching for the value a in the linked list
    link* walker = (link*)malloc(sizeof(link*));
    walker = start;
    for(int i = 0; i < len; ++i){
        if(walker->value == a){
            std::cout << "Value found!\n";
            return;
        }
        walker = walker->next;
    }
    std::cout << "Value not found.\n";
}

        

void print_list(link* start, int a){
    link* walker = (link*)malloc(sizeof(link*));
    walker = start;
    for(int i = 0; i < a; ++i){
        std::cout << walker->value  << "\n";
        walker = walker->next;
    }
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
    starter->next = link1;
    link1->next = link2; link2->next = link3;
    link3->next = starter;

    // Print out the current list 
    print_list(starter, 4);

    // Push a link onto the stack and print
    link* link4 = (link*)malloc(sizeof(link*));
    link4->value = 4;
    list_insert(starter, link4);
    std::cout << "Printing the list after inserting:\n";
    print_list(starter, 5);

    // Popping a link and printing
    list_delete(starter);
    std::cout << "Printing the list after deleting:\n";
    print_list(starter, 4);
    
    // Searching the list for the number 3
    list_search(starter, 4, 3);

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
