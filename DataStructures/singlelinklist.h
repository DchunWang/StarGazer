#pragma once
#ifndef SINGLELINKLIST.H
#define SINGLELINKLIST.H

#include "List.h"

/*注意点：
	1、单链表中，每个结点由一个数据元素和一个后继指针组成；
	2、结点用struct定义，是因为相对class来说，struct中定义的
	属性和方法等默认是public的；
	3、头指针head并不指向具体的结点，只是它的后继指针才是指向
	单链表中的第一个元素
	*/

template<typename  Type>
class singleLinkList : public List<Type>
{
private:
	//保存数据元素及数据元素之间关系的结点
	struct node
	{
		//数据元素
		Type data;
		//后继指针
		Type *next;

		//结点的构造函数
		node(const Type &x, node *p = nullptr)
		{
			data = x;
			next = p;
		}
		//结点类的默认构造函数，需将指针设置为空
		node():next(nullptr){}
		~node() {}
	};

private:
	//一个单链表可以由一个指向起始结点的指针表示
	node *head;

	//记录单链表中所含有的元素个数（以空间换时间)
	int number;

protected:
	//用于获取第i个位置的结点指针
	node *get(int i) const;

public:
	//构造函数
	singleLinkList();
	//析构函数
	~singleLinkList();
	//清空单链表
	void clear();
	//返回单链表中所含元素个数
	int length() const;
	//在第i个位置上插入新的一个数据元素
	bool insert(int i, const Type &x);
	//删除第i个位置上的元素
	bool remove(int i);
	//搜索某个元素，并找出它在单链表中的位置
	int search(const Type &x) const;
	//访问第i个元素，并返回其值
	Type visit(int i) const;
	//遍历单链表，按序访问单链表中的每个元素
	void traverse() const;
};

//构造函数，构造一个空的单链表
template<typename Type>
singleLinkList<Type>::singleLinkList()
{
	head = new node();
	number = 0;
}

//析构函数
template<typename Type>
singleLinkList<Type>::~singleLinkList()
{
	//是要删除单链表中的每一个元素？？
	clear();
	//clear()只是清除单链表中的元素，而头指针head并不没有指向单链表中任何元素
	//所以需要单独删除
	delete head;
}

//获得第i个位置上的节点指针
template<typename Type>
singleLinkList<Type>::node *singleLinkList<Type>::get(int i) const
{
	//如果结点为空，则返回头结点指针
	if (i < 0)
		return head;
	
	//获得单链表中的第一个结点的指针
	node *temp = head->next;	
	for (int k = 0; k < i; ++k)
	{
		temp = temp->next;
	}
	//以上循环结束后，就获得了从0开始计数的第i个结点的指针
	return temp;
}


//清空单链表，是起析构函数的作用吗？？？
template<typename Type>
void singleLinkList<Type>::clear()
{

	while (head->next != nullptr)
	{
		node *temp = head->next;
		head->next = temp->next;
		delete temp;
	}
	number = 0;
}

//计算单链表中所含有的元素个数
template<typename Type>
int singleLinkList<Type>::length() const
{
	return number;
}

//在第i个位置上插入一个新的数据元素
template<typename Type>
bool singleLinkList<Type>::insert(int i, const Type &x)
{
	if (i < 0)
	{
		cout << "输入的值不合理，请输入正确的值" << endl;
		return false;
	}
	
	//以元素x创建新结点
	node *newNode = new node(x);
	//获得第i-1个结点的指针
	node *temp = get(i-1);
	//获得第i个结点的指针
	node *tempi = temp->next;
	//让第i-1个元素的后继指针指向新结点
	temp->next = newNode;
	//让新结点的next指针指向原来的第i个元素，新节点自己成为了第i个元素
	newNode->next = tempi;

	++number;

	return true;
}

//删除第i个位置上的元素
template<typename Type>
bool singleLinkList<Type>::remove(int i)
{
	if (i < 0)
	{
		cout << "请输入正确范围内的值" << endl;
		return false;
	}
	
	//获得第i-1个结点的指针
	node *temp = get(i-1);
	//获得第i个结点的指针，也即要被删除的结点
	node *del = temp->next;
	//让第i-1个元素的next指针指向原先的第i+1个元素，
	temp->next = del->next;

	//删除第i个结点
	delete del;

	--number;

	return true;
}

//搜索单链表中的某元素，并返回其在单链表中的位置
template<typename Type>
int singleLinkList<Type>::search(const Type &x) const
{
	int k = 0;
	//获得第1个结点的指针
	node *temp = head->next;

	while ( temp->data != x && temp->next != nullptr )
	{
		temp = temp->next;
		++k;
	}
	if (temp->next == nullptr)
		return -1;
	else
		return k;
}

//访问第i个元素，并返回其值
template<typename Type>
Type singleLinkList<Type>::visit(int i) const
{
	node *temp = get(i);

	return temp->data;
}

//遍历单链表，访问其中的每一个元素
//但由于暂时不知道具体要做什么，所以暂时只留一个空函数体在这，之后补充完整
template<typename Type>
void singleLinkList<Type>::traverse() const
{

}



#endif SINGLELINKLIST.H