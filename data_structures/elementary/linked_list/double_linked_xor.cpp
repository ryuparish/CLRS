#include <iostream>
#include <cstdint>
#include <stdlib.h>

// Implementing a queue using only a linked list
// Used some heap allocation, but there is definitely memory leakage.

struct link{
    int value = 0;
    link* np = NULL;
};

// O(1) time
void list_delete(link*& start, link*& third_link) {
    // Start is a pointer the first object in the linked list
    link* temp = (link*)malloc(sizeof(link*));
    temp = start->np;

    // Setting start to point to the second link
    start->np = (link*)((uintptr_t)start->np->np^(uintptr_t)start);

    // Setting the second link's np to the xor of start and third link
    // The second link's np need to be reset due to the first link being deleted
    start->np->np = (link*)((uintptr_t)start^(uintptr_t)third_link);
    free(temp);
}

// O(1) time
void list_insert(link*& start, link*& x){
    // Setting the np of the new link to the xor of starter and the first link
    x->np = (link*)((uintptr_t)start^(uintptr_t)start->np);
    start->np->np = (link*)((uintptr_t)x^(uintptr_t)((uintptr_t)start->np->np^(uintptr_t)start));
    start->np = x;
}


void print_list(link* start){
    link* walker = (link*)malloc(sizeof(link*));
    link* lag = (link*)malloc(sizeof(link*));
    link* temp = (link*)malloc(sizeof(link*));
    walker = start;
    while(walker != NULL){
        std::cout << walker->value  << "\n";
        if(walker == start){
            lag = walker;
            walker = walker->np;
            continue;
        }
        temp = walker;
        walker = (link*)((uintptr_t)lag^(uintptr_t)walker->np);
        lag = temp;
    }
}

// O(i) time, O(n) time in the worst case
link* search_list(link* start, link* target){
    link* walker = (link*)malloc(sizeof(link*));
    link* lag = (link*)malloc(sizeof(link*));
    link* temp = (link*)malloc(sizeof(link*));
    walker = start;
    while(walker != target && walker != NULL){
        if(walker == start){
            lag = walker;
            walker = walker->np;
            continue;
        }
        temp = walker;
        walker = (link*)((uintptr_t)lag^(uintptr_t)walker->np);
        lag = temp;
    }
    if(walker == NULL){
        std::cout << "Target not found.\n";
        return 0;
    }
    else{
        std::cout << "Target found!\n";
        return walker;
    }
}

int main() {
    link* starter = (link*)malloc(sizeof(link*));
    // Creating the links
    link* link1 = (link*)malloc(sizeof(link*)); 
    link1->value = 1; link1->np = NULL;
    link* link2 = (link*)malloc(sizeof(link*)); 
    link2->value = 2; link2->np = NULL;
    link* link3 = (link*)malloc(sizeof(link*)); 
    link3->value = 3; link3->np = NULL;
    
    // Linking them together
    // For the first link, you need to have a direct connection
    starter->np = link1;
    link1->np = (link*)((uintptr_t)starter^(uintptr_t)link2); link2->np = (link*)((uintptr_t)link1^(uintptr_t)link3);
    link3->np = (link*)((uintptr_t)link2^(uintptr_t)(NULL));

    // Print out the current list 
    print_list(starter);

    // Push a link onto the stack and print
    link* link4 = (link*)malloc(sizeof(link*));
    link4->value = 4;
    list_insert(starter, link4);
    std::cout << "Printing the list after inserting:\n";
    print_list(starter);

    //// Popping a link and printing
    link* third_link = (link*)malloc(sizeof(link*));
    third_link = search_list(starter, link2);
    list_delete(starter, third_link);
    std::cout << "Printing the list after deleting:\n";
    print_list(starter);
    
    free(starter);
    return 0;
}

// NOTE: 
// For the reversal, all you would need is the last link's np value and xor it with NULL to get the previous (or in the program's view the next) value
