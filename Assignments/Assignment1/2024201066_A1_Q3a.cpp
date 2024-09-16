#include <iostream>
using namespace std;
#define INIT_CAPACITY 20000

class priority_queue{

    private:
        int* heap;        // Pointer pointing to heap
        int cap;          // Maximum capacity of elements heap can take
        int currSize;     // At present, the number of elements in heap
        bool isMinHeap;   // Flag to determine heap type (true for min-heap, false for max-heap)
        

    public:
        priority_queue() {
            cap = INIT_CAPACITY;      
            currSize = 0;
            isMinHeap = false;           
            heap = new int[cap];     
        }

        priority_queue(string s) {
            cap = INIT_CAPACITY;      
            currSize = 0;
            if(s=="greater" || s=="Greater" || s=="GREATER")
                isMinHeap = true;
            else 
                isMinHeap = false;           

            heap = new int[cap];       
        }


        ~priority_queue() { 
            delete[] heap;
        }

         bool compare(int a, int b) { 
            return isMinHeap ? a > b : a < b;
        }

        void resize(int newCap) { 
            int * newHeap = new int[newCap];
            for (size_t i = 0; i < currSize; ++i) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
            newHeap = nullptr;
            cap = newCap;      
        }

        
        int parent(int indx) { 
            return (indx - 1) / 2;
        }

        int leftChild(int indx) { 
            return 2 * indx + 1;
        }

        int rightChild(int indx) { 
            return 2 * indx + 2;
        }

        void push(int element) {
            if (currSize == cap) {
                resize(cap * 2); 
            }
            heap[currSize] = element;
            heapifyBottomUp(currSize);
            ++currSize;
        }

        void pop() {
            if (empty()) {
                throw runtime_error("Priority queue is empty!");
            }
            --currSize;
            swap(heap[0], heap[currSize]);
            heapifyTopDown(0);
        }

        int top() { 
            if (empty()) {
                throw runtime_error("Priority queue is empty!");
            }
            return heap[0];
        }

        bool empty() { 
            return (currSize ? false : true);
        }

        int size() { 
            return currSize;
        }

        void heapifyBottomUp(int indx) {
            while (indx > 0 && compare(heap[parent(indx)], heap[indx])) {
                swap(heap[parent(indx)], heap[indx]);
                indx = parent(indx);
            }
        }

        void heapifyTopDown(int indx) {
            int largest = indx;
            int left = leftChild(indx);
            int right = rightChild(indx);

            if (left < currSize && compare(heap[largest], heap[left])) {
                largest = left;
            }
            if (right < currSize && compare(heap[largest], heap[right])) {
                largest = right;
            }
            if (largest != indx) {
                swap(heap[indx], heap[largest]);
                heapifyTopDown(largest);
            }
        }
};

// testing for pq
void pqcheck() {
    priority_queue maxh;           // Max-heap by default
    priority_queue minh("greater");  // greater for Min-heap


    /***  MIN HEAP OPERATIONS  ***/
    cout <<"****** MIN HEAP ******" <<  endl;
    // Insert elements to min heap
    minh.push(10);
    minh.push(5);
    minh.push(17);

    cout << "Min Heap: has 3 elements: 10, 5, 17" << endl; // info
    // Access the top element
    cout << "Min Heap: Top element: " << minh.top() << endl; // Output: 5

    // Remove the top element
    minh.pop();
    minh.pop();
    // Access the new top element
    cout << "Min Heap: Top element after 2 pop: " << minh.top() << endl; // Output: 17

    // Check size
    cout << "Min Heap Size: " << minh.size() << endl; // Output: 1

    // Check if empty
    cout << "Min Heap: Is empty: " << boolalpha << minh.empty() << endl; // Output: false


    /***  MAX HEAP OPERATIONS  ***/
    cout <<endl<< "****** MAX HEAP ******" << endl;
    // Insert elements max heap
    maxh.push(10);
    maxh.push(5);
    maxh.push(15);

    cout << "Max Heap: has 3 elements: 10, 5, 15" << endl; // info
    // Access the top element
    cout << "Max Heap: Top element: " << maxh.top() << endl; // Output: 15
    // Remove the top element
    maxh.pop();
    // Access the new top element
    cout << "Max Heap: Top element after pop: " << maxh.top() << endl; // Output: 10
    // Check size
    cout << "Max Heap Size: " << maxh.size() << endl; // Output: 2
    // Check if empty
    cout << "Max Heap: Is empty: " << boolalpha << maxh.empty() << endl; // Output: false
}


int main(int arg, char *argv[]) {
    pqcheck();    
    return 0;
}

/**********************************************************************
 
        For compilation use below command
        g++ 2024201066_A1_Q3a.cpp -o 'Executable File Name'

************************************************************************/