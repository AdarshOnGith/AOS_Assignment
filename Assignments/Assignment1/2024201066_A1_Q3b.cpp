#include <iostream>
#include <climits>
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

class MedianHeap {
private:    
    priority_queue maxHeap;
    priority_queue minHeap;

public:
    MedianHeap() : maxHeap(), minHeap("greater") {}
    void addNumber(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        // Balance the heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    // Find the current median
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else if (minHeap.size() > maxHeap.size()) {
            return minHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }

    // Check free day and insert a new value
    void checkFreeDay(int d, int a) {
        int n = (maxHeap.size() + minHeap.size())-1;
        int arr[n];
        int i = 0;
        
            if (!maxHeap.empty() && d <= maxHeap.top()) {
                // Decrease key in maxHeap
                while(i < n && maxHeap.size() > 0 && maxHeap.top() != d) {
                    arr[i++] = maxHeap.top();
                    maxHeap.pop();
                }
                if(maxHeap.size() > 0) maxHeap.pop();
                while(i < n && maxHeap.size() > 0 ) {
                    arr[i++] = maxHeap.top();
                    maxHeap.pop();
                }
                while(i < n && minHeap.size() > 0 ) {
                    arr[i++] = minHeap.top();
                    minHeap.pop();
                }
            } else {
                // Decrease key in minHeap
                 while(i < n && minHeap.size() > 0 && minHeap.top() != d) {
                    arr[i++] = minHeap.top();
                    minHeap.pop();
                }
                if(minHeap.size() > 0) minHeap.pop();
                while(i < n && minHeap.size() > 0 ) {
                    arr[i++] = minHeap.top();
                    minHeap.pop();
                }
                while(i < n && maxHeap.size() > 0 ) {
                    arr[i++] = maxHeap.top();
                    maxHeap.pop();
                }
            }
        for(int j = 0; j < n ; j++)
            addNumber(arr[j]);
        addNumber(a);
    }
};


int main(int argc, char *argv[])  {
    int n, d;
    cin >> n >> d;
    if(n <= 0 || d <= 0 ) {
        cerr<< " Enter Positive values of n and d";
        return -1;
    }

    int* sales = new int[n];        
    for (int i = 0; i < n; ++i) {
        cin >> sales[i];
    }      

    MedianHeap medianHeaptot;
    MedianHeap medianHeapd;

    for (int i =0; i <d; i++) {
        medianHeaptot.addNumber(sales[i]);
        medianHeapd.addNumber(sales[i]);
    }
    int l=0;
    int ans=0;

     for (int i =d; i < n; i++) {
        if( sales[i] >= (medianHeaptot.findMedian()) + (medianHeapd.findMedian())) ans++;
        medianHeaptot.addNumber(sales[i]);
        medianHeapd.checkFreeDay(sales[l++], sales[i]);  // For example Remove 5 and add 8
    }

    cout<<endl<< ans <<endl;

    delete[] sales;
    return 0;
}

/**********************************************************************
 
        For compilation use below command
        g++ 2024201066_A1_Q3b.cpp -o 'Executable File Name'

************************************************************************/
