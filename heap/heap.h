#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include<iostream>

template<typename T,typename Cmp=std::less<T> >	
class Heap {
public:
   Heap(int maxSize=1024);	
   ~Heap();
   int insert(T const& element);
   T top();
   int pop();
   void clear(){_size=0;};	
   bool empty()const {return _size==0;};
   bool full()const {return _size==MaxSize;};
   int size()const {return _size;};	
   int max_size()const {return MaxSize;};
private:
   T* buffer;	//存放堆的数组
   int _size;	//堆的当前数据量
   int MaxSize;
   int leftChild(int i){return 2*i+1;}
   int rightChild(int i){return 2*i+2;}
   int parent(int i){return (i-1)/2;}
   void shiftDown(int index);
   void shiftUp(int index);
   void swap(int i,int j);
   Cmp cmp;
};

#endif