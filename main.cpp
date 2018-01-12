//
//  main.cpp
//  skyline
//
//  Created by Bahadır on 17.12.2017.
//  Copyright © 2017 Bahadır. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
#include "MPQ.hpp"

using namespace std;



enum side {RIGHT, LEFT};
struct xCoordinate {
    int x; // X coordinate
    side s; // which side of the building
    int b; // building ID. it is all odd number: 1 3 5 ...
    
    xCoordinate(int building, int value) : x(value), b(building) {
        if (b%2 == 0){
            b--;
            s = RIGHT;
        }
        else{
            s = LEFT;
        }
    }
};


// Takes priorityQueue object and a vector. Put the piority queue into xSorted in sorted order.
void heapSort(priorityQueue<int> &heapForSort, vector<xCoordinate> &xSorted){
    vector<xCoordinate> xRevSorted;
    
    while (!heapForSort.IsEmpty()){
        xCoordinate xCoord(heapForSort.GetMaxLabel(), heapForSort.pop());
        xRevSorted.push_back(xCoord);
    }
    for (int i = int(xRevSorted.size()-1) ; i >= 0 ; i--)
        xSorted.push_back(xRevSorted[i]);
}


int main(){
    
    //  Open file ...
    ifstream inputFile;
    inputFile.open("input.txt");
    
    int numBuilding, x1, x2, y;
    
    inputFile >> numBuilding;
    priorityQueue<int> heapForSort(numBuilding*2); // takes x coordinates. used fot sorting
    priorityQueue<int> heightHeap(numBuilding); // stores the y values in heap with building ID(1 3 5 ...)
    int i = 0;
    while (inputFile >> x1 >> y >> x2){
        // so each pair of labels 1,2 or 3,4 are x coordinate of same building.
        // Building numbers are odd 1 3 5 7 ...
        heapForSort.insert(x1,++i); // odd numbers are left x coordinates
        heightHeap.insert(y,i);
        heapForSort.insert(x2,++i); // Even numbers are right x coordinates
        
    }
    
    // Sorting X coordinates...
    
    
    vector <xCoordinate> xSorted;
    heapSort(heapForSort, xSorted);
    /*
    cout << "ordered list is ready!" << endl;
    
    for (int j = 0; j < xSorted.size(); j++){
        cout << xSorted[j].x << " building num: " << xSorted[j].b << endl;
    }
    cout << endl;
    */
    
    priorityQueue<int> currentHeightHeap(numBuilding); // Height of the current buildings corresponding x coordinate.
    

    // For each x coordinate(in ascending order) get the height of the building(s) above and decide the highest one.
    for (int i = 0; i < xSorted.size(); i++){
        int x = xSorted[i].x;
        int b = xSorted[i].b;
        int s = xSorted[i].s;
        int y = heightHeap.GetByLabel(b);
        
        // If no building starts form x = 0, print "0 0"
        if (i == 0 && x != 0)
            cout << 0 << " " << 0 << endl;
        
        // Check the x coordinate if it is left or right side
        if (s == LEFT){
            // if left insert and check if it is bigger than the previous height.
            // if it is print it out.
            currentHeightHeap.insert(y, b);
            if (y == currentHeightHeap.GetMax()){
                cout << x << " " << currentHeightHeap.GetMax() << endl;
            }
        }

        else if (s == RIGHT){
            // if right, check if it is the highest building in that range?
            // if it is update the skyline
            if (b == currentHeightHeap.GetMaxLabel()){
                currentHeightHeap.pop();
                if (currentHeightHeap.IsEmpty())
                    cout << x  << " " << 0 << endl;
                else
                    cout << x << " " << currentHeightHeap.GetMax() << endl;
            }
            // If it is not the skyline remove it from the heap.
            else{
                currentHeightHeap.Remove(b);
            }
        }
        
    }
    
    return 0;
}






