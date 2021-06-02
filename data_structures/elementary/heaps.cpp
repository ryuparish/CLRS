#include <vector>
#include <cmath>
#include <iostream>
#include <unistd.h>

struct heapNode{
    // The heapNodes will contain the indexes of the children and parents
    int value = 0, parent = 0, lchild = 0, rchild = 0;
};

void maxHeapify(std::vector<heapNode>& array, int index){
    int largest = index;
    int left = array[index].lchild;
    int right = array[index].rchild;
    
    // Checking which of parent, lchild, and rchild has the largest value
    // The reason for the first condition is to avoid having to make another function or making the struct a complicated class
    if(left <= array.size() && array[left].value > array[largest].value){
        largest = left;
    }

    else{largest = index;}

    if(right <= array.size() && array[right].value > array[largest].value){
        largest = right;
    }

    // DEBUG
    std::cout << "Out of: " << array[left].value << " " << array[right].value << " " << array[index].value << "\n" << array[largest].value << " was the largest\n";

    // If the parent was not the largest then switch nodes
    if(array[largest].value != array[index].value){
        // DEBUG
        std::cout << "Swapping: " << array[largest].value << " and " << array[index].value << "\n";
        int temp = array[index].value;
        array[index].value = array[largest].value;
        array[largest].value = temp;
        maxHeapify(array, largest);
    }
}

void buildHeap(std::vector<heapNode>& heap, int index){
    for(int i = (heap.size()/2); i >= 0 ; i--){
        maxHeapify(heap, i);
    }
}


void printArray(std::vector<heapNode>& arrayNodes){
    for(int i = 0; i < arrayNodes.size(); ++i){
        std::cout << arrayNodes[i].value << " ";
    }
    std::cout << "\n";
}

int main(){
    std::vector<heapNode> arrayNodes;
    int a, i = 0;
    std::cout << "Please enter a series of numbers to make the array: ";

    // Adding null to the very beginning to make indexing smoother

    // Read in the numbers
    while(std::cin >> a){

        heapNode node;
        node.value = a;

        // All other nodes formula
        node.parent = ((i-1) / 2);
        node.lchild = (2 * i) + 1;
        node.rchild = (2 * i) + 2;
        std::cout << "i is: " << i << "\n";
        std::cout << "Value: " << a << " has:\nParent: " << node.parent << "\nLchild: " << node.lchild << "\nRchild: " << node.rchild << "\n";

        arrayNodes.push_back(node);
        i++;
    }

    std::cout << "\n";

    // Heapify the array of heapNodes
    buildHeap(arrayNodes, 0);
    printArray(arrayNodes);
    return 0;
}


