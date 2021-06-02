#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

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
    void operator++ (int one){
        heap_size++;
        heapNode new_node;
        heap_array.push_back(new_node);
    }
    void operator-- (int one){
        heap_size--;
        heap_array.pop_back();
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

int heapExtractMax(heap& Heap){
    if (Heap.heap_size < 1){
        std::invalid_argument("Cannot extract from heap with no values");
    }
    int max = Heap[0].value;
    Heap[0].value = Heap[Heap.heap_size].value;
    Heap--;
    maxHeapify(Heap, 0);
    return max;
}

void heapIncreaseKey(heap& Heap, int index, int new_val){
    if(new_val < Heap[index].value){
        std::invalid_argument("New value is less than the current value");
    }
    Heap[index].value = new_val;
    int temp;
    while(index > 0 && Heap[Heap[index].parent].value < Heap[index].value){
        temp = Heap[Heap[index].parent].value;
        Heap[Heap[index].parent].value = Heap[index].value;
        Heap[index].value = temp;
        index = Heap[index].parent;
    }
}
        
void maxHeapInsert(heap& Heap, int new_val){
    Heap++;
    Heap[Heap.heap_size].value = -(int)INFINITY;
    Heap[Heap.heap_size].parent = (Heap.heap_size - 1) / 2;
    Heap[Heap.heap_size].lchild = (2 * Heap.heap_size) + 1;
    Heap[Heap.heap_size].rchild = (2 * Heap.heap_size) + 2;
    heapIncreaseKey(Heap, Heap.heap_size, new_val);
}
        
void buildHeap(heap& Heap){
    for(int i = (Heap.heap_size/2); i >= 0 ; i--){
        maxHeapify(Heap, i);
    }
}

void deleteHeapNode(heap& Heap, int index){
    //int curr_val, new_val = Heap[Heap.heap_size].value;
    // Brute force method (O(n) time)
    //for (int i = Heap.heap_size; i > index; i--){
    //    curr_val = Heap[i-1].value;
    //    Heap[i-1].value = new_val;
    //    new_val = curr_val;
    //}
    
    // O(log(n)) time
    Heap[index].value = Heap[Heap.heap_size].value;
    Heap--;
    // We assume that the last value is not larger than the index chosen, therefore, the newly-positioned last value will not have a parent that is smaller
    maxHeapify(Heap, index);
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
    std::cout << "Please enter a series of numbers to add to the array: ";
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

    // Insert a value
    std::cout << "Inserting 11\n";
    maxHeapInsert(heapNodes, 11);
    printArray(heapNodes);

    // Increase a value
    std::cout << heapNodes[2].value << " will become 12\n";
    heapIncreaseKey(heapNodes, 2, 12);
    printArray(heapNodes);

    // Delete a value
    std::cout << "Deleting 6\n";
    deleteHeapNode(heapNodes, 5);
    printArray(heapNodes);

    // Sort the heap
    std::cout << "Sorting\n";
    heapSort(heapNodes);
    printArray(heapNodes);
    return 0;
}
