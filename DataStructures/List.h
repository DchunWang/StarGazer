#pragma once
#ifndef LIST.H
#define LIST.H

/*这个类是线性表的抽象基类，用于确定之后得各种线性表
所需的各种运算*/

/*注意点：
	1、为了在积累指针指向派生类对象的场合下也能调用派生类的析构函数释放空间，
	则必须在积累定义一个析构函数；当通过基类指针析构派生类对象时会调用基类的
	析构函数，而此时基类的析构函数为虚函数，因此会找到派生类的析构函数，执行
	派生类的析构函数，把派生类申请的动态空间释放掉。
	2、后面那的=0, 是将这个虚函数说明为纯虚函数，而含有纯虚函数的类是抽象基类，
	不能直接创建抽象基类的对象。
	3、create运算的作用是创建一个空的线性表，它的功能可以由每一具体类的构造函数
	来实现。*/

template<typename Type>
class List
{
public:
	//向线性表第i个位置插入元素x
	virtual bool insert(int i, const Type &x) = 0;
	//清空线性表
	virtual void clear() = 0;
	//计算线性表中的元素个数
	virtual int length() const = 0;
	//删除第i个位置的元素
	virtual bool remove(int i) = 0;
	//搜索某个元素在线性表中是否出现，如果出现，则它的位置是多少（即第几个元素）
	virtual int search(const Type &x) const= 0;
	//访问线性表的第i个元素，返回第i个数据元素的值
	virtual Type visit(int i) const = 0;
	//遍历线性表,按序访问线性表的每一数据元素
	virtual void traverse() const = 0;
	//析构函数
	virtual ~List() {};

};


#endif