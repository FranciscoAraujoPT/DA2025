/**
 * @file MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

/**
 * @class MutablePriorityQueue
 * @brief A priority queue that allows updating the priority of its elements.
 *
 * This class supports efficient key updates, which is useful for algorithms like Dijkstra.
 * @tparam T The type of elements stored in the queue. Must have an `int queueIndex` and support comparison with `<`.
 */

template <class T>
class MutablePriorityQueue {
    std::vector<T *> H; /**< Binary heap of elements. */

    /**
     * @brief Moves an element up in the heap to restore heap property.
     * @param i The index of the element to move up.
     */
    void heapifyUp(unsigned i);

    /**
     * @brief Moves an element down in the heap to restore heap property.
     * @param i The index of the element to move down.
     */
    void heapifyDown(unsigned i);

    /**
     * @brief Sets the element at a given index in the heap.
     * @param i The index to set.
     * @param x Pointer to the element to set.
     */
    inline void set(unsigned i, T * x);
public:
    /**
     * @brief Constructs an empty MutablePriorityQueue.
     */
    MutablePriorityQueue();

    /**
     * @brief Inserts an element into the priority queue.
     * @param x Pointer to the element to be inserted.
    */
    void insert(T * x);

    /**
     * @brief Extracts the element with the minimum key (highest priority).
     * @return Pointer to the extracted element.
     */
    T * extractMin();

    /**
     * @brief Decreases the key of an element and restores heap order.
     * @param x Pointer to the element whose key was decreased.
     */
    void decreaseKey(T * x);

    /**
     * @brief Checks whether the priority queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */