#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: arrayheap-student-proj5.h
 * Name: Eugene Pak
 * Version 2.3
 * Due: 4/12/24
 * This file contains the implementation of a heap and free stack array class
 * given by the professor's h file. It allows for the implementation of a
 * min priority queue heap in array form.
 */

using namespace std;

/* ArrayHeap()
 * Constructor for the ArrayHeap class.
 * Initializes the heapAndFreeStack array and data array with default capacity.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
const int SIZE = 5;
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    this->numItems = 0;
    this->capacity = SIZE;
    this->heapAndFreeStack = new int [this->capacity];
    for (int i = 0; i < this->capacity; i++){
        this->heapAndFreeStack[i] = i;
    }
    this->data = new T [this->capacity];
}

/* ArrayHeap(ArrayHeap<T> const &h)
 * Copy constructor for the ArrayHeap class.
 * Performs a deep copy of another ArrayHeap object.
 *
 * Parameters:
 *  h: Reference to another ArrayHeap object to copy.
 *
 * Return Value:
 *  None
 */
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    this->numItems = h.numItems;
    this->capacity = h.capacity;
    delete [] this->heapAndFreeStack;
    delete [] this->data;
    this->heapAndFreeStack = new int[this->capacity];
    this->data = new T [this->capacity];
    for (int i = 0; i < this->capacity; i++){
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
        this->data[i] = h.data[i];
    }
}

/* ~ArrayHeap()
 * Destructor for the ArrayHeap class.
 * Deallocates memory used by heapAndFreeStack and data arrays.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    delete [] this->heapAndFreeStack;
    delete [] this->data;
    this->numItems = 0;
    this->capacity = SIZE;
}

/* getMinItem() const
 * Returns the minimum item in the heap.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  Constant reference to the minimum item in the heap.
 */
template <typename T>
T const& ArrayHeap<T>::getMinItem() const{
    return this->data[this->heapAndFreeStack[0]];
}

/* getNumItems() const
 * Returns the number of items in the heap.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  Integer value representing the number of items in the heap.
 */
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return this->numItems;
}

/* bubbleUp(int ndx)
 * Moves the element at the specified index up the heap to maintain heap property.
 *
 * Parameters:
 *  ndx: Index of the element to be moved up.
 *
 * Return Value:
 *  None
 */
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx) {
    if (ndx <= 0) {
        return;
    }
    int parent = (ndx - 1) / 2;
    if (this->data[heapAndFreeStack[ndx]] < this->data[heapAndFreeStack[parent]]) {
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[parent]);
        this->bubbleUp(parent);
    }
}

/* bubbleDown(int ndx)
 * Moves the element at the specified index down the heap to maintain heap property.
 *
 * Parameters:
 *  ndx: Index of the element to be moved down.
 *
 * Return Value:
 *  None
 */
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx) {
    int child1 = (ndx * 2) + 1, child2 = (ndx * 2) + 2;
    if (child1 < this->numItems) {
        int lesserChild = child1;
        if ((child2 < this->numItems) &&
            (this->data[heapAndFreeStack[child2]] < this->data[heapAndFreeStack[child1]])){
            lesserChild = child2;
        }
        if (this->data[heapAndFreeStack[lesserChild]] < this->data[heapAndFreeStack[ndx]]) {
            swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[lesserChild]);
            this->bubbleDown(lesserChild);
        }
    }
}

/* operator=(ArrayHeap<T> const &ah)
 * Assignment operator for the ArrayHeap class.
 * Performs a deep copy of another ArrayHeap object.
 *
 * Parameters:
 *  ah: Reference to another ArrayHeap object to copy.
 *
 * Return Value:
 *  Constant reference to the current ArrayHeap object after assignment.
 */
template <typename T>
ArrayHeap<T> const & ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if (this != &ah){
        this->numItems = ah.numItems;
        this->capacity = ah.capacity;
        delete [] this->heapAndFreeStack;
        delete [] this->data;
        this->heapAndFreeStack = new int[this->capacity];
        this->data = new T [this->capacity];
        for (int i = 0; i < this->capacity; i++){
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            this->data[i] = ah.data[i];
        }
    }
    return *this;
}

/* insert(T const &item)
 * Inserts an item into the heap.
 * Doubles the capacity of the heap if necessary.
 *
 * Parameters:
 *  item: Constant reference to the item to be inserted into the heap.
 *
 * Return Value:
 *  None
 */
template <typename T>
void ArrayHeap<T>::insert(T const &item){
    if (this->numItems == this->capacity){
        this->doubleCapacity();
    }
    this->data[this->heapAndFreeStack[this->numItems]] = item;
    this->bubbleUp(this->numItems);
    this->numItems++;
}

/* removeMinItem()
 * Removes the minimum item from the heap.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    if (this->numItems <= 0){
        return;
    }
    this->numItems--;
    swap(this->heapAndFreeStack[this->numItems], this->heapAndFreeStack[0]);
    this->bubbleDown(0);
}

/* doubleCapacity()
 * Doubles the capacity of the heap.
 * Allocates new memory, copies existing data, and updates capacity.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
const int MULT = 2;
template <typename T>
void ArrayHeap<T>::doubleCapacity() {
    T *tempData = new T[MULT * this->capacity];
    int *tempHAndFS = new int[MULT * this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        tempData[i] = this->data[i];
        tempHAndFS[i] = this->heapAndFreeStack[i];
    }
    for (int i = this->capacity; i < (MULT * this->capacity); i++){
        tempHAndFS[i] = i;
    }
    this->capacity *= MULT;
    delete[] this->data;
    delete[] this->heapAndFreeStack;
    this->data = tempData;
    this->heapAndFreeStack = tempHAndFS;
    return;
}

#endif
