#ifndef SEQLIST.H
#define SEQLIST.H

#include "List.h"
#include <iostream>

using namespace std;


/*顺序表类*/

/*注意点：
	1、保存一个动态数组需要两个变量：指向数组起始位置的指针和数组规模。
	2、暂时没想到遍历运算有什么具体的目标，所以暂时使用空函数，之后遇到
	具体的需要遍历顺序表的目标问题时，再将traverse()函数补充完整！
	3、这里的错误处理都只是单纯滴输出一个信息而已，之后看是否有更好的方式
	将错误展示出来。
	4、在清空clear()和删除remove()函数中，只是单纯地将长度length减少，但之前
	已存在的元素这样就删除了吗？？？是否要显示调用delete对元素进行删除？？？
	*/

template<typename Type>
class seqList : public List<Type>
{
private:
	//采用动态数组来存储线性表
	//指向数组起始位置的指针
	Type *data;				
	//保存数组中已有的元素个数
	int length;
	//保存线性表中所能存储的最大元素个数，超过则需要扩大存储空间
	int maxSize;

	//扩大存储空间
	void doubleSpace();

public:
	//构造函数，用于创建一个空的顺序表
	seqList(int initSize);
	//析构函数
	~seqList();
	//在第i个位置插入元素
	bool insert(int i, const Type &x);
	//清空顺序表
	void clear();
	//计算顺序表中的元素个数
	int length() const;
	//删除第i个位置的元素
	bool remove(int i);
	//搜索某个元素是否出现，找到它的位置
	int search(const Type &x) const;
	//访问第i个元素，返回其值
	Type visit(int i) const;
	//遍历顺序表，按序访问顺序表中的每一元素
	void traverse() const;
};

//构造函数，根据提供的初始大小
template<typename Type>
seqList<Type>::seqList(int initSize)
{
	//首先判断初始值是否合理
	if (initSize < 0)
	{
		cout << "给定的初始值不合理！" << endl;
		return;
	}
	
	//申请初始大小的数组空间，并让指针指向数组的起始位置
	data = new Type[initSize];
	maxSize = initSize;
	//设置初始的元素个数为0
	length = 0;
}

template<typename Type>
seqList<Type>::~seqList()
{
	delete[] data;
}

template<typename Type>
void seqList<Type>::doubleSpace()
{
	Type *temp = data;

	//扩大最大空间
	maxSize *= 2;
	//重新申请一块更大的存储空间
	data = new Type[maxSize];

	for (int j = 0; j < length; ++j)
	{
		data[j] = temp[j];
	}

	delete[] temp;

}

//在第i个位置插入元素x
/*注意：这里我用第i个位置就对应a[i],也即位置是从0开始计数的；
	也即，在第0个位置插入，就是插入在起始位置上，最后一个位置是(length-1)*/
template<typename Type>
bool seqList<Type>::insert(int i, const Type &x)
{
	if (i < 0)
	{
		cout << "输入的范围不正确，请输入正确的值" << endl;
		return false;
	}
	
	if (length >= maxSize - 1)
		doubleSpace();
	//从最后一个位置开始，向后移动一个位置
	for (int k = length - 1; k >= i; --k)
	{
		data[k + 1] = data[k];
	}
	//将新元素插入到第i个位置上
	data[i] = x;

	//所含有的元素个数也要加1
	++length;
	return true;
}

//清空顺序表
template<typename Type>
void seqList<Type>::clear()
{
	//将已有元素个数设置为0就可以了吗？？？之前已有的元素不要销毁吗？？？？
	length = 0;
}

//得到顺序表中的元素个数
template<typename Type>
int seqList<Type>::length() const
{
	return length;
}

//删除第i个位置上的元素
template<typename Type>
bool seqList<Type>::remove(int pos)
{
	//Type temp = data[pos];

	if (pox < 0 || pos >= length)
	{
		cout << "请输入正确范围内的值！" << endl;
		return false;
	}

	for (int i = pos; i < length - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--length;

	//要有下面这句吗？？？不要，因为temp不是指针！而只是一个像3、 0.8这样类型的元素
	//delete temp;

	return true;
}

//搜索元素x在顺序表中的位置
template<typename Type>
int seqList<Type>::search(const Type &x) const
{
	for (int k = 0; k < length; ++k)
	{
		if (data[k] == x)
			return k;
	}
	return -1;
}

//访问第i个元素，返回其值
template<typename Type>
Type seqList<Type>::visit(int x) const
{
	//暂时缺少错误处理方式
	if(x < length && x >= 0)
		return data[x];
	else
	{
		//这里是非常简略的错误处理方式，只是单纯地输出错误信息
		//之后看是否有其它更好的方式展现出来
		cout << "输入的值不在范围内，请输入正确的值！" << endl;
	}
}

//遍历访问顺序表中的元素
//暂时不知道要用它具体做什么，所以暂时只是给出一个空格的函数体在这，
//之后又具体要求时，再将它补完
template<typename Type>
void seqList<Type>::traverse() const
{

}

#endif