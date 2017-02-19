#ifndef _AVL_H_
#define _AVL_H_
#include "stack.h"

using std::cin;
using std::cout;
using std::endl;
template<class E>
struct AVLNode{
	E data;
	int bf;
	AVLNode<E> *left,*right;
	AVLNode():left(NULL),right(NULL),bf(0){};
	AVLNode(const E d,AVLNode<E> *L=NULL,AVLNode<E> *R=NULL):data(d),left(L),right(R),bf(0){}
	~AVLNode(){};
	void setData(E d){data=d;}
	E getData(){return data;}
};
template<class E>
class AVL{
protected:
	AVLNode<E> *root;
	
	void makeEmpty(AVLNode<E> *&ptr);
	void PrintTree(AVLNode<E> *ptr)const;
	AVLNode<E> *Copy(const AVLNode<E> *ptr);
	AVLNode<E> Min(AVLNode<E> *ptr) const;
	AVLNode<E> Max(AVLNode<E> *ptr) const;
	bool insert0(AVLNode<E> *& ptr,E& el);
	bool Remove(E x,AVLNode<E> *&ptr,E &el);
	void RotateL(AVLNode<E> *&ptr);
	void RotateR(AVLNode<E> *&ptr);
	void RotateLR(AVLNode<E> *&ptr);
	void RotateRL(AVLNode<E> *&ptr);
	int Height(AVLNode<E> *ptr)const;
public:
	AVL():root(NULL){};
	~AVL(){};
	AVLNode<E> *get_root(){return root;}
	AVLNode<E> *search(const E x,AVLNode<E> *ptr);
	bool Search(const E x){return (search(x,root)!=NULL)?true:false;}
	AVL<E> &operator=(const AVL<E> &R);
	void makeEmpty(){makeEmpty(root);root=NULL;}
	void PrintTree()const{PrintTree(root);}
	E Min(){return Min(root)->data;}
	E Max(){return Max(root)->data;}
	bool Insert(E& el){return insert0(root,el);}
	bool Remove(const E x) {return Remove(x,root);}
	//friend istream &operator >>(istream &in,AVL<E> &Tree);
	//friend ostream &operator <<(ostream &out,const AVL<E>& Tree);
};


template<class E>
AVLNode<E> *AVL<E>::search(E x,AVLNode<E> *ptr){
	if(ptr==NULL) return NULL;
	else if(x<ptr->data) return search(x,ptr->left);
	else if(x>ptr->data) return search(x,ptr->right);
	else return ptr;
};
/*template<class E>
AVL<E>::AVL(K value){
	E x;
	root=NULL;
	RefValue=value;
	cin>>x;														
	while(x.key!=RefValue){
		Insert(x,root);cin>>x;
	}
}*/
//******************************************************************
template<class E>
void AVL<E>::RotateL(AVLNode<E> *&ptr){
	AVLNode<E> *subL=ptr;
	ptr=subL->right;
	subL->right=ptr->left;
	ptr->left=subL;
	ptr->bf=subL->bf=0;
};
template<class E>
void AVL<E>::RotateR(AVLNode<E> *&ptr){
	AVLNode<E> *subR=ptr;
	ptr=subR->left;
	subR->left=ptr->right;
	ptr->right=subR;
	ptr->bf=subR->bf=0;
};
//***************************************************************
template<class E>
void AVL<E>::RotateRL(AVLNode<E> *&ptr){
	AVLNode<E> *subL=ptr,*subR=subL->right;
	ptr=subR->left;
	subR->left=ptr->right;
	ptr->right=subR;
	if(ptr->bf>=0) subR->bf=0;
	else subR->bf=1;
	subL->right=ptr->left;
	ptr->left=subL;
	if(ptr->bf==1) subL->bf=-1;
	else subL->bf=0;
	ptr->bf=0;
};
template<class E>
void AVL<E>::RotateLR(AVLNode<E> *&ptr){
	AVLNode<E> *subR=ptr,*subL=subR->left;
	ptr=subL->right;
	subL->right=ptr->left;
	ptr->left=subL;
	if(ptr->bf<=0) subL->bf=0;
	else subL->bf=-1;
	subR->left=ptr->right;
	ptr->right=subR;
	if(ptr->bf==-1) subR->bf=1;
	else subR->bf=0;
	ptr->bf=0;
};
//****************************************************************
template<class E>
bool AVL<E>::insert0(AVLNode<E> *& ptr,E& el){
	AVLNode<E> *pr=NULL,*p=ptr,*q;
	int d;
	Stack<AVLNode<E> *>st;
	while(p!=NULL){
		if(el==p->data) return false;
		pr=p;
		st.Push(pr);
		if(el<p->data) p=p->left;
		else p=p->right;
	}
	p=new AVLNode<E>(el);
	if(p==NULL) {cerr<<"space is invalid!"<<endl;exit(1);}
	if(pr==NULL){ptr=p;return true;}
	if(el<pr->data) pr->left=p;
	else pr->right=p;
	while(st.IsEmpty()==false){
		st.Pop(pr);
		if(p==pr->left) pr->bf--;
		else pr->bf++;
		if(pr->bf==0) break;
		if(pr->bf==1||pr->bf==-1)
			p=pr;
		else {
			d=(pr->bf<0)?-1:1;
			if(p->bf==d){
				if(d==-1) RotateR(pr);
				else RotateL(pr);
			}
			else {
				if(d==-1) RotateLR(pr);
				else RotateRL(pr);
			}
			break;
		}
	}
	if(st.IsEmpty()==true) ptr=pr;
	else {
		st.getTop(q);
		if(q->data>pr->data) q->left=pr;
		else q->right=pr;
	}
	return true;
};
#endif