#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

const int CAPACITY =100;
//#define INT_MIN -1000
#include<iostream>
#include<cmath>
#include<climits>
using namespace std;
#include<list>
#include<iterator>
#include<vector>
class Heap
{private:
    vector<int> heap;

    int left(int parent){
        if((2*parent+1) < heap.size())
            return 2*parent+1;
        else return -1;
    }

    int right(int parent){
        if((2*parent+2) < heap.size())
            return 2*parent+2;
        else return -1;
    }

    int parent(int child){
        if(child == 0)
            return -1;
        else return (child-1)/2;
    }

    void minHeap(int i){
        if (i >= 0 and parent(i) >= 0 and heap[parent(i)] > heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            minHeap(parent(i));
        }
    }
     void maxHeap(int i){
        if (i >= 0 and parent(i) >= 0 and heap[parent(i)] < heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            maxHeap(parent(i));
        }
    }

public:
    Heap(){}

    void insert(int element,int type){

        heap.push_back(element);
        if(type==1)
        minHeap(heap.size() -1);
        else if(type==2) maxHeap(heap.size()-1);
    }



    int size(){
        return heap.size();
    }

   void displayHeap(){
       cout<<"Elementele sunt : ";
       for(auto i=heap.begin();i!=heap.end();i++)
        cout<<*i<<" ";
       cout<<endl;
        string indent1 = "                ";
        int i = 1;
        cout<< indent1;
        cout<< heap[0] <<"\n";
        string indent = "                    ";
        int nivel = 2;
        while(i < size()) {
            int half = indent.size() / 2 + 0.5;
            indent = indent = indent.substr(0, half);
            //indent="     ";
            for(int j = 0; j < pow(2, nivel - 1); j++) {
                cout<< indent << heap[i];
                i++;
                if(i >= size())
                    return;
            }
            cout<<"\n";
            nivel++;
        }
    }



};


#endif // HEAP_H_INCLUDED
