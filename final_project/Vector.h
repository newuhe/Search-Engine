#ifndef _VECTOR_H_
#define _VECTOR_H_

#define step 10									//每次增加10个
template<class T>
class Vector{
public:
	Vector():count(step),tail(0){str_vector=new T[step];}
	void push_back(T a){
		if(tail==count)												//已满
		{
			count+=step;									//count+10
			T *new_vector=new T[count];
			for(int i=0;i<tail;i++)
				new_vector[i]=str_vector[i];				//用一个数组暂存一下
			delete []str_vector;
			str_vector=new_vector;
			str_vector[tail++]=a;							//tail+1
		}
		else													//未满
		{
			str_vector[tail++]=a;
		}
	}
	bool IsEmpty(){
		return tail==0?true:false;
	}
	void remove(int pos){
		if(tail==0)
			exit(0);
		else {
			T *new_vector=new T[count];
			for(int i=0;i<tail;i++)
				{if(i<pos)
				new_vector[i]=str_vector[i];				//用一个数组暂存一下
				else if(i==pos);
				else if(i>pos)
					new_vector[i-1]=str_vector[i];}
			tail--;
			delete []str_vector;
			str_vector=new_vector;
		}
	}
	void clear(){
		tail=0;
	}
	int end(){
		return tail;
	}
	int begin(){
		return 0;
	}
	T &get_value(int pos){
		return str_vector[pos];
	}
	int length(){
		return tail;
	}
	T &operator[](int pos){											//重载[]操作符
		return str_vector[pos]; 
	}
	int find(int left,int right,T data){
		int mid=0;
		if(left<=right)
		{
			mid=(left+right)/2;
			if(data>str_vector[mid-1])
				mid=find(mid+1,right,data);
			else if(data<str_vector[mid-1])
				mid=find(left,right-1,data);
		}
		return mid;
	}
private:
	T *str_vector;
	int count,tail;							//count代表总容量，tail表示实际长度(指向最后一个元素后一个位置）
};

#endif
