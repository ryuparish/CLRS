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
    int heap_size; // This is not really the heap size, but the heap size -1 for the ease of indexing.
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
    // This is also called percolateDown
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

void changeValue(heap& Heap, int index, int new_val){
    // This function was formerly called heapIncreaseKey an only allowed increasing values
    //if(new_val < Heap[index].value){
    //    std::invalid_argument("New value is less than the current value");
    //}
    Heap[index].value = new_val;
    int temp;
    // This is also called percolateUp
    while(index > 0 && Heap[Heap[index].parent].value < Heap[index].value){
        temp = Heap[Heap[index].parent].value;
        Heap[Heap[index].parent].value = Heap[index].value;
        Heap[index].value = temp;
        index = Heap[index].parent;
    }
}
        
void maxHeapInsert(heap& Heap, int new_val){
    Heap++;
    // Setting the correct indexes for the children and parent of new node
    Heap[Heap.heap_size].value = -(int)INFINITY;
    Heap[Heap.heap_size].parent = (Heap.heap_size - 1) / 2;
    Heap[Heap.heap_size].lchild = (2 * Heap.heap_size) + 1;
    Heap[Heap.heap_size].rchild = (2 * Heap.heap_size) + 2;
    changeValue(Heap, Heap.heap_size, new_val);
}
        
void buildHeap(heap& Heap){
    if(Heap.heap_size > 0){
        for(int i = (Heap.heap_size/2); i >= 0 ; i--){
            maxHeapify(Heap, i);
        }
    }
}

void deleteHeapNode(heap& Heap, int index){
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

// I think something is wrong with this function but I am not going to fix it today
void heapSort(heap& heapNodes){
    buildHeap(heapNodes);
    int temp;
    for (int i = heapNodes.size(); i > 0; --i){
        temp = heapNodes[0].value;
        heapNodes[0].value = heapNodes[i].value;
        heapNodes[i].value = temp;
        heapNodes.heap_size--;
        maxHeapify(heapNodes, 0);
    }
}
        
int main(){
    // Making empty vector of heapNodes
    std::vector<heapNode> arrayNodes;

    char a;

    // Converting the vector into a heap object
    heap heapNodes = heap(arrayNodes);
    buildHeap(heapNodes);

    // Print the heapified heap of heapNodes
    printArray(heapNodes);

    std::cout << "All hail the Heap. Here are your options(press enter after typing):\n";
    std::cout << "a (add)\ni (increase a specific value)\nd (delete a specific value)\ns (print out the sorted heap)[Warning: Will destroy Heap in the process]\np (print array)\nq (quit)\n";
    std::cin >> a;
    // Read in the input
    while(a != 'q'){
        printf("%c", a);
        int index, value;
        if(a == 'a'){
            std::cout << "Now you can enter things one at a time (enter -1 to quit): ";
            while(true){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cin >> value;
                if(value != -1){
                    maxHeapInsert(heapNodes, value);
                    printArray(heapNodes);
                    std::cout << "Continue entering numbers or enter -1: ";
                }
                else{
                    printArray(heapNodes);
                    break;
                }
            }
        }
        if(a == 'i'){
            std::cout << "Which index to increase?:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin >> index;
            std::cout << "What value to change it to?:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin >> value;
            changeValue(heapNodes, index, value);
        }
        if(a == 'd'){
            std::cout << "Which index to delete?:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin >> index;
            deleteHeapNode(heapNodes, index);
        }
        if(a == 's'){
            heapSort(heapNodes);
        }
        if(a == 'q'){
            break;
        }
        std::cout << "current heap array: ";
        printArray(heapNodes);
        std::cout << "a (add)\ni (increase a specific value)\nd (delete a specific value)\ns (print out the sorted heap)[Warning: Will destroy Heap in the process]\np (print array)\nq (quit)\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin >> a;
    }

    // Testing
    //std::cout << "Please enter a series of numbers to add to the array (q to quit): ";
    //// Read in the numbers (To test the buildHeap from an un-maxHeapified heap)
    // int i = 0;
    // char a;
    //while(std::cin >> a){
    //    if(a == 'q'){
    //        break;
    //    }

    //    heapNode node;
    //    node.value = a;

    //    // All other nodes formula
    //    node.parent = ((i-1) / 2);
    //    node.lchild = (2 * i) + 1;
    //    node.rchild = (2 * i) + 2;

    //    arrayNodes.push_back(node);
    //    i++;
    //}
    
    // Print the heapified heap of heapNodes
    //printArray(heapNodes);
    
    // Insert a value
    //std::cout << "Inserting 11\n";
    //maxHeapInsert(heapNodes, 11);
    //printArray(heapNodes);

    //// Increase a value
    //std::cout << heapNodes[2].value << " will become 12\n";
    //changeValue(heapNodes, 2, 12);
    //printArray(heapNodes);

    //// Delete a value
    //std::cout << "Deleting 6\n";
    //deleteHeapNode(heapNodes, 5);
    //printArray(heapNodes);

    //// Sort the heap
    //std::cout << "Sorting\n";
    //heapSort(heapNodes);
    //printArray(heapNodes);
    return 0;
}
