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

// O(1) time
void unionize(link*& end1, link*& end2){
    end1->next = end2;
}

// O(n) time
void reversal(link*& start){
    // Walker will be the guide to the n+2 link, target will be the target(or previous) link that the holder(link n+1) will be pointing at, and the holder will be the n+1 link.
    link* walker = (link*)malloc(sizeof(link*));
    link* holder = (link*)malloc(sizeof(link*));
    link* target = (link*)malloc(sizeof(link*));
    walker = start->next;
    while(walker != holder){
        // If walker is the last link, then the walker should not move and only the holder should
        if(walker->next == NULL){
            target = holder;
            holder = walker;
        }
        // If the walker is on the very first link, we need to set the first link to be target, second link to holder, and the third link to be the walker
        else if (walker == start->next){
            target = walker;
            // Setting the first link to point at NULL
            // Close the target->next ONLY after setting the walker to walker->next, otherwise walker will be set to NULL!
            walker = walker->next; 
            target->next = NULL;
            holder = walker;
            walker = walker->next;
        }
        // Else if the walker is in the middle and it is safe to move
        else{
            target = holder;
            holder = walker;
            walker = walker->next;
        }
        holder->next = target;
    }
    start->next = holder;
    return;
}

// Non circular for the ease in the union program
void print_list(link* start){
    link* walker = (link*)malloc(sizeof(link*));
    walker = start->next;
    while(walker != NULL){
        std::cout << walker->value  << "\n";
        walker = walker->next;
    }
    free(walker);
}
    
int main() {
    link* starter1 = (link*)malloc(sizeof(link*));
    link* starter2 = (link*)malloc(sizeof(link*));

    // Creating the links for list
    link* link1 = (link*)malloc(sizeof(link*)); 
    link1->value = 1; link1->next = NULL;
    link* link2 = (link*)malloc(sizeof(link*)); 
    link2->value = 2; link2->next = NULL;
    link* link3 = (link*)malloc(sizeof(link*)); 
    link3->value = 3; link3->next = NULL;
    
    // Creating the links for the second list
    link* link4 = (link*)malloc(sizeof(link*));
    link4->value = 4; link4->next = NULL;
    link* link5 = (link*)malloc(sizeof(link*));
    link5->value = 5; link5->next = NULL;
    link* link6 = (link*)malloc(sizeof(link*));
    link6->value = 6; link6->next = NULL;

    // Pointing the start of each list
    starter1->next = link1;
    link1->next = link2; link2->next = link3;
    starter2->next = link4;
    link4->next = link5; link5->next = link6;

    // Print out the current list 
    std::cout << "Current list for list: \n";
    unionize(link3, link4);
    print_list(starter1);
    reversal(starter1);

    // This should now print a reversed list
    std::cout << "List reversed: \n";
    print_list(starter1);

    // Freeing all the data in the linked list
    while(starter1 != NULL){
        link* temp = (link*)malloc(sizeof(link*));
        temp = starter1;
        starter1 = starter1->next;
        free(temp);
    }
    delete(starter1);
    return 0;
}
