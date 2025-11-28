<<<<<<< Updated upstream
=======
#ifndef Stack_Heap_nMORE_H
#define Stack_Heap_nMORE_H

>>>>>>> Stashed changes
#include <iostream>
#ifndef Stack_Heap_nMORE_H
#define Stack_Heap_nMORE_H
class NodeQ {
public:
    void* data;
    NodeQ* next;
    NodeQ(void* d) {
        data = d;
        next = nullptr;
    }
};

class myQueue {
private:
    NodeQ* front;
    NodeQ* rear;
    int currSize;

public:
    myQueue() {
        front = rear = nullptr;
        currSize = 0;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(void* d) {
        NodeQ* n = new NodeQ(d);
        if (isEmpty()) {
            front = rear = n;
        }
        else {
            rear->next = n;
            rear = n;
        }
        currSize++;
    }

    void* dequeue() {
        if (isEmpty()) return nullptr;
        NodeQ* temp = front;
        void* val = temp->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        currSize--;
        return val;
    }

    void* getFront() {
        if (isEmpty()) return nullptr;
        return front->data;
    }

    int size() { return currSize; }
};

// ======================================================
// Helper Stack (No STL Allowed)
// ======================================================
class NodeS {
public:
    void* data;
    NodeS* next;
    NodeS(void* d) {
        data = d;
        next = nullptr;
    }
};

class myStack {
private:
    NodeS* topNode;
    int currSize;

public:
    myStack() {
        topNode = nullptr;
        currSize = 0;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    void push(void* d) {
        NodeS* n = new NodeS(d);
        n->next = topNode;
        topNode = n;
        currSize++;
    }

    void* pop() {
        if (isEmpty()) return nullptr;
        NodeS* temp = topNode;
        void* val = temp->data;
        topNode = topNode->next;
        delete temp;
        currSize--;
        return val;
    }

    void* peek() {
        if (isEmpty()) return nullptr;
        return topNode->data;
    }

    int size() { return currSize; }
};
class MaxHeap
{
private:
    void** arr;
    int capacity;
    int size;
    int (*cmp)(void*, void*);

    void swap(int i, int j)
    {
        void* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (cmp(arr[index], arr[parent]) > 0)
            {
                swap(index, parent);
                index = parent;
            }
            else break;
        }
    }

    void heapifyDown(int index)
    {
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && cmp(arr[left], arr[largest]) > 0)
                largest = left;

            if (right < size && cmp(arr[right], arr[largest]) > 0)
                largest = right;

            if (largest != index)
            {
                swap(index, largest);
                index = largest;
            }
            else break;
        }
    }

    void resize()
    {
        int newcap = capacity * 2;
        void** newArr = new void* [newcap];
        for (int i = 0; i < size; i++) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        capacity = newcap;
    }

public:
    MaxHeap(int cap, int (*fun)(void*, void*))
    {
        capacity = cap;
        size = 0;
        arr = new void* [capacity];
        cmp = fun;
    }

    void insert(void* data)
    {
        if (size == capacity) resize();
        arr[size] = data;
        heapifyUp(size);
        size++;
    }

    void* getMax()
    {
        if (size == 0) return nullptr;
        return arr[0];
    }

    void* extractMax()
    {
        if (size == 0) return nullptr;

        void* ret = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return ret;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }

    ~MaxHeap()
    {
        delete[] arr;
    }
};

<<<<<<< Updated upstream

#endif
=======
#endif // !1
>>>>>>> Stashed changes
