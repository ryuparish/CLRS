#include <iostream>
#include <vector>
#include <stdlib.h>

struct deq{
    std::vector<int> deque{std::vector<int>(8,0)};
    int head1 = 0, head2 = 7;
    int* curr_head = (int*)malloc(sizeof(int));

    void head_setter(int** current_head, int& head){
        if(head == 1){*current_head = &head1;}
        else{*current_head = &head2;}
    }
            
    bool underflow(){
        if(curr_head == &head1){
            if(((*curr_head) - 1) % deque.size() == head2){
                std::cout << "Underflow detected! No dequeuing possible.\n";
                return true;
            }
        }

        else if(curr_head == &head2){
            if((*curr_head - 1) % deque.size() == head1){
                std::cout << "Underflow detected! No dequeuing possible.\n";
                return true;
            }
        }
        return false;
    }

    bool overflow(){
        if(curr_head == &head1){
            if(((*curr_head) + 1) % deque.size() == head2){
                std::cout << "Overflow detected! Not queing number.\n";
                return true;
            }
        }

        else if(curr_head == &head2){
            if(((*curr_head) + 1) % deque.size() == head1){
                std::cout << "Overflow detected! Not queing number.\n";
                return true;
            }
        }
        return false;
    }

    void enqueue(int x, int h){
        head_setter(&curr_head, h);
        if(h == 1){
            if(overflow()){return;}
        }
        else if(h == 2){
            if(underflow()){return;}
        }

        deque[*curr_head] = x;

        if(h == 1){
            *curr_head = (*curr_head + 1) % deque.size();
        }
        else if(h == 2){
            *curr_head = (*curr_head - 1) % deque.size();
        }

        std::cout << "Current position of the index: " << *curr_head << "\n";
    }

    int dequeue(int h){
        head_setter(&curr_head, h);
        if(h == 1){
            if(underflow()){return 0;}
        }
        else if(h == 2){
            if(overflow()){return 0;}
        }

        int x = deque[*curr_head];

        if(h == 1){
            *curr_head = (*curr_head - 1) % deque.size();
            deque[*curr_head] = 0;
        }
        else if(h == 2){
            *curr_head = (*curr_head + 1) % deque.size();
            deque[*curr_head] = 0;
        }

        std::cout << "Current position of the index: " << *curr_head << "\n";
        return x;
    }

    size_t size(){
        return deque.size();
    }

    int index(int idx){
        return deque[idx];
    }
};

int main() {
    char input;
    int integer = 0, head;
    std::cout << "The Deque of size 8 has the options below\n\n";
    deq deque;

    while(integer != -1){

        std::cout << "Options:\n"
            "q: queue\n"
            "d: dequeue\n"
            "e: exit\n";

        std::cout << "Here is the current deque:\n";

        // Presenting the array
        for(int i = 0; i < deque.size(); ++i){
            std::cout << deque.index(i) << " ";
        }
        std::cout << "\n";

        std::cin >> input;

        if (input == 'q'){
            std::cout << "Which head(1 or 2)?: ";
            std::cin >> head;
            std::cout << "\nEnter the number you would like to queue: ";
            std::cin >> integer;
            deque.enqueue(integer, head);
        }

        else if (input == 'd'){
            std::cout << "Which head(1 or 2)?: ";
            std::cin >> head;
            std::cout << "\nDequeuing!\n";
            int x = deque.dequeue(head);
            if(x == 0){continue;}
            std::cout << "You dequeued: " << x << '\n';
        }

    }
    return 0;
}

