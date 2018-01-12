//
//  MPQ.hpp
//  skyline
//
//  Created by Bahadır on 17.12.2017.
//  Copyright © 2017 Bahadır. All rights reserved.
//

#ifndef MPQ_hpp
#define MPQ_hpp

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

template <typename comparable>
class priorityQueue {
public:
    explicit priorityQueue(int capacity): heapArr(capacity+1), location(500), size(0) {}
    
    // location i da doldurmayi unutma
    void insert(comparable value, int label){
        heapEntry obj;
        obj.value = value;
        obj.label = label;
        heapArr[++size] = obj;
        location[label] = size;
        bubble_up(size);
        heapify();
    }
    
    // Pops the head
    comparable pop(){
        if  (size > 0)
            return Remove(heapArr[1].label);
        else 
        	throw "Array is empty";
    }

    // removes and returns the head (max)
    comparable Remove(int label){
        int loc_on_heap = location[label];
        if (loc_on_heap == -1)
            throw "No item exists with that label!\n" ;
        comparable output = heapArr[loc_on_heap].value;
        
        swap(loc_on_heap, size);
        location[label] = -1;
        --size;
        bubble_down(loc_on_heap);
        heapify();
        return output;
        
    }
    
    // returns the max value
    comparable GetMax(){
        if (IsEmpty())
            throw "IsEmpty!\n";
        else
            return heapArr[1].value;
    }
    
    // Get the max of label 
    int GetMaxLabel(){
        if (IsEmpty())
            throw "IsEmpty!\n";
        else
            return heapArr[1].label;
    }
    
    comparable GetByLabel(int label){
        int loc = location[label];
        if (loc == -1)
            throw "No item exists with that label!\n" ;
        return heapArr[loc].value;
    }
    
    bool IsEmpty(){
        if (size == 0)
            return 1;
        return 0;
    }
    
    void print(){
        cout << "heapArr: ";
        for (int i = 1 ; i <= size ; i++){
            cout << heapArr[i].value << " ";
        }
        cout << endl;
       /*
        cout << "location: " << endl;
        for (int i = 0 ; i < location.size(); i++){
            cout << "(" << i << ")" << location[i] << endl;
        }
        cout << endl;
        */
    }
    
    
    
private:
    struct heapEntry{
        comparable value;
        int label;
        heapEntry(const comparable & val = comparable(), int lab = 0)
        : value(val), label(lab)
        {}
    };
    
    vector<heapEntry> heapArr;
    vector<int> location;
    int size;
    
    // useful functions
    int getLeftChildIndex(int parentIndex) { return parentIndex*2; }
    int getRightChildIndex(int parentIndex) { return parentIndex*2 + 1; }
    int getParentIndex(int childIndex) { return childIndex / 2; }
    
    bool hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
    bool hasRightChild(int index) { return getRightChildIndex(index) < size; }
    bool hasParent(int index) { return getParentIndex(index) > 0; }
    

    // Swaps the given indexes in heapArr. Also organize the location array
    void swap(int indexOne, int indexTwo){
        auto temp = heapArr[indexOne];
        int labelOne = heapArr[indexOne].label;
        int labelTwo = heapArr[indexTwo].label;
        
        location[labelOne] = indexTwo;
        location[labelTwo] = indexOne;
        
        heapArr[indexOne] = heapArr[indexTwo];
        heapArr[indexTwo] = temp;
    }
    

    // Percolate up
    void bubble_up(int index){
        while (hasParent(index) && heapArr[getParentIndex(index)].value < heapArr[index].value){
            swap(getParentIndex(index), index);
            index = getParentIndex(index);
        }
    }
    
    //  Percolate down
    void bubble_down(int index){
        if (hasLeftChild(index) && hasRightChild(index)){
            int rightChildIndex = getRightChildIndex(index);
            int leftChildIndex = getLeftChildIndex(index);

            if (heapArr[rightChildIndex].value > heapArr[leftChildIndex].value){
                if (heapArr[rightChildIndex].value > heapArr[index].value)
                	swap(rightChildIndex, index);
            }
            else{
                if (heapArr[leftChildIndex].value > heapArr[index].value)
                	swap(leftChildIndex, index);
            }

            
        }
        else if (hasRightChild(index)){
            int rightChildIndex = getRightChildIndex(index);
            if (heapArr[rightChildIndex].value > heapArr[index].value)
                	swap(rightChildIndex, index);
        }
        else if (hasLeftChild(index)){
            int leftChildIndex = getLeftChildIndex(index);
            if (heapArr[leftChildIndex].value > heapArr[index].value)
                	swap(leftChildIndex, index);
        }
        
    }

    /* Starts with size/2 and goes up one by one. 
    for each index check if the index is bigger than the 
    child node(s). if not swap
    */
    void heapify(){
        int index = size/2;
        if (size > 3){
            for (; index > 0; index--)
                bubble_down(index);
        }
        // if size is 3 or less the algorithm above does not work.
        // So do it manually :) 
        else if (size == 3){
            heapEntry obj1 = heapArr[1];
            heapEntry obj2 = heapArr[2];
            heapEntry obj3 = heapArr[3];
            
            if (obj2.value > obj3.value && obj1.value < obj2.value)
                swap(1, 2);
            else if (obj3.value > obj2.value && obj1.value < obj3.value)
                swap(1,3);
        }
        else if (size == 2){
            heapEntry obj1 = heapArr[1];
            heapEntry obj2 = heapArr[2];
            
            if (obj1.value < obj2.value)
                swap(1,2);
        }
    }
    
    
};


#endif /* MPQ_hpp */












