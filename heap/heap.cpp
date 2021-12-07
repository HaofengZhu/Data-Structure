#include"heap.h"
#include<memory.h>
#include<iostream>
using namespace std;

template<typename T,typename Cmp>
Heap<T,Cmp>::Heap(int maxSize):MaxSize(maxSize),_size(0),cmp(Cmp()){
    buffer=new T[MaxSize];
}

template<typename T,typename Cmp>
Heap<T,Cmp>::~Heap(){
    delete[] buffer;
}

template<typename T,typename Cmp>
int Heap<T,Cmp>::insert(T const& element){
    if(full()){
        return -1;
    }
    buffer[_size]=element;
    shiftUp(_size++);
    return 0;
}

template<typename T,typename Cmp>
T Heap<T,Cmp>::top(){
    if (empty())
    {
        exit(-1);
    }
    return buffer[0];   
}

template<typename T,typename Cmp>
int Heap<T,Cmp>::pop(){
    if(empty()){
        return -1;
    }
    swap(0,--_size);
    shiftDown(0);
    return 0;
}

template<typename T,typename Cmp>
void Heap<T,Cmp>::shiftDown(int index){
    if(index<0||index>=_size){
        return ;
    }
    while (index<_size)
    {
        int leftIndex=leftChild(index);
        if(leftIndex>=_size)
            break;
        int rightIndex=rightChild(index);
        if(cmp(buffer[index],buffer[leftIndex])>0){
            if(rightIndex<_size&&cmp(buffer[leftIndex],buffer[rightIndex])>0){
                swap(index,rightIndex);
                index=rightIndex;
            }else{
                swap(index,leftIndex);
                index=leftIndex;
            }
        }else if(rightIndex<_size&&cmp(buffer[index],buffer[rightIndex])){
            swap(index,rightIndex);
            index=rightIndex;
        }else{
            break;
        }
    }
    
}

template<typename T,typename Cmp>
void Heap<T,Cmp>::shiftUp(int index){
    if(index<0||index>=_size){
        return ;
    }
    while (index>0)
    {
        int par=parent(index);
        if(cmp(buffer[par],buffer[index])){
            swap(index,par);
            index=par;
        }else{
            break;
        }
    }
}

template<typename T,typename Cmp>
void Heap<T,Cmp>::swap(int i,int j){
    T tmp=buffer[i];
    buffer[i]=buffer[j];
    buffer[j]=tmp;
}

