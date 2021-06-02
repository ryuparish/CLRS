#include <vector>
#include <iostream>

struct heapNode{
    // The heapNodes will contain the indexes of the children and parents
    int value = 0, parent = 0, lchild = 0, rchild = 0;
};

// This is needed to have both heap_size and size() in a single data structure
struct heap{
    int heap_size;
    std::vector<heapNode> heap_array;
    // Constructor
    heap(std::vector<heapNode>& heapNodes){
        heap_size = heapNodes.size() - 1;
        heap_array = heapNodes;
    }
    void push_back(heapNode new_elem){
        heap_array.push_back(new_elem);
    }
    int size(){
        return heap_array.size();
    }
    heapNode& operator[] (int index){
        return heap_array[index];
    }
};

void maxHeapify(heap& array, int index){
    int largest = index;
    int left = array[index].lchild;
    int right = array[index].rchild;
    
    // Checking which of parent, lchild, and rchild has the largest value
    // The reason for the first condition is to avoid having to make another function or making the struct a complicated class
    if(left <= array.heap_size && array[left].value > array[largest].value){
        largest = left;
    }
    else{largest = index;}
    if(right <= array.heap_size && array[right].value > array[largest].value){
        largest = right;
    }

    // If the parent was not the largest then switch nodes
    // To "float" the small values down to the bottom
    if(array[largest].value != array[index].value){
        int temp = array[index].value;
        array[index].value = array[largest].value;
        array[largest].value = temp;
        maxHeapify(array, largest);
    }
}

void buildHeap(heap& Heap){
    for(int i = (Heap.heap_size/2); i >= 0 ; i--){
        maxHeapify(Heap, i);
    }
}


void printArray(heap& heapNodes){
    for(int i = 0; i < heapNodes.size(); ++i){
        std::cout << heapNodes[i].value << " ";
    }
    std::cout << "\n";
}

void heapSort(heap& heapNodes){
    buildHeap(heapNodes);
    int temp;
    for (int i = heapNodes.size() - 1; i >= 1; --i){
        temp = heapNodes[0].value;
        heapNodes[0].value = heapNodes[i].value;
        heapNodes[i].value = temp;
        heapNodes.heap_size--;
        maxHeapify(heapNodes, 0);
    }
}
        
int main(){
    std::vector<heapNode> arrayNodes;
    int a, i = 0;
    std::cout << "Please enter a series of numbers to make the array: ";

    // Read in the numbers
    while(std::cin >> a){

        heapNode node;
        node.value = a;

        // All other nodes formula
        node.parent = ((i-1) / 2);
        node.lchild = (2 * i) + 1;
        node.rchild = (2 * i) + 2;

        arrayNodes.push_back(node);
        i++;
    }

    // Converting the vector into a heap object
    heap heapNodes = heap(arrayNodes);
    buildHeap(heapNodes);

    // Print the heapified heap of heapNodes
    printArray(heapNodes);

    // Sort then print again
    heapSort(heapNodes);
    printArray(heapNodes);

    return 0;
}
