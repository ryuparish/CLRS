#include <iostream>
#include <vector>
#include <stdlib.h>

struct q{
    std::vector<int> queue{std::vector<int>(8,0)};
    int tail = 0, head = 0;

    bool overflow(){
        if((head + 1) % queue.size() == tail){
            std::cout << "Overflow detected! Not queing number.\n";
            return true;
        }
        return false;
    }

    bool underflow(){
        if((tail + 1) % queue.size() == head){
            std::cout << "Underflow detected! No dequeuing possible.\n";
            return true;
        }
        return false;
    }

    void enqueue(int x){
        if(overflow()){return;}
        queue[head] = x;
        head = (head + 1) % queue.size();
        std::cout << "Current position of the index(head): " << head << "\n";
    }

    int dequeue(){
        if(underflow()){return 0;}
        int x = queue[tail];
        queue[tail] = 0;
        tail = (tail + 1) % queue.size();
        std::cout << "Current position of the index(head): " << tail << "\n";
        return x;
    }

    size_t size(){
        return queue.size();
    }

    int index(int idx){
        return queue[idx];
    }
};

int main() {
    char input;
    int integer = 0;
    std::cout << "The Queue of size 8 has the options below\n\n";
    q queue;

    while(integer != -1){

        std::cout << "Options:\n"
            "q: queue\n"
            "d: dequeue\n"
            "e: exit\n";

        std::cout << "Here is the current queue:\n";

        for(int i = 0; i < queue.size(); ++i){
            std::cout << queue.index(i) << " ";
        }
        std::cout << "\n";

        std::cin >> input;

        if (input == 'q'){
            std::cout << "Enter the number you would like to queue: ";
            std::cin >> integer;
            queue.enqueue(integer);
        }

        else if (input == 'd'){
            std::cout << "Dequeuing!\n";
            int x = queue.dequeue();
            if(x == 0){continue;}
            std::cout << "You dequeued: " << x << '\n';
        }
    }
    return 0;
}

