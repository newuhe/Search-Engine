#ifndef _STACK_H_
#define _STACK_H_
#include <assert.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
const int stackIncreasement=20;
template<class T>
class Stack{
public:
	Stack(int sz=20):top(-1),maxSize(sz){elements=new T[maxSize];assert(elements!=NULL);}
	~Stack(){delete []elements;}
	void Push(const T &x){if(IsFull()==true) overflowProcess();elements[++top]=x;}
	bool Pop (T& x)	   	{if(IsEmpty()==true) return false;x=elements[top--];return true;}
	bool getTop(T& x) const{if(IsEmpty()==true) return false;x=elements[top];return true;}
	bool IsEmpty() const{return (top==-1)?true:false;}
	bool IsFull() const{return (top==maxSize-1)?true:false;}
	int getSize() const{return top+1;}
	void MakeEmpty(){top=-1;}
private:
	T *elements;
	int top;
	int maxSize;
	void overflowProcess(){
	T *newArray=new T[maxSize+stackIncreasement];
	if(newArray==NULL) {cerr<<"new stack space failed!"<<endl;exit(1);}
	for(int i=0;i<=top;i++)
		newArray[i]=elements[i];
	maxSize+=stackIncreasement;
	delete []elements;
	elements=newArray;
	}
};


#endif