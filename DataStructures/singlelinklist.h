#pragma once
#ifndef SINGLELINKLIST.H
#define SINGLELINKLIST.H

#include "List.h"

/*ע��㣺
	1���������У�ÿ�������һ������Ԫ�غ�һ�����ָ����ɣ�
	2�������struct���壬����Ϊ���class��˵��struct�ж����
	���Ժͷ�����Ĭ����public�ģ�
	3��ͷָ��head����ָ�����Ľ�㣬ֻ�����ĺ��ָ�����ָ��
	�������еĵ�һ��Ԫ��
	*/

template<typename  Type>
class singleLinkList : public List<Type>
{
private:
	//��������Ԫ�ؼ�����Ԫ��֮���ϵ�Ľ��
	struct node
	{
		//����Ԫ��
		Type data;
		//���ָ��
		Type *next;

		//���Ĺ��캯��
		node(const Type &x, node *p = nullptr)
		{
			data = x;
			next = p;
		}
		//������Ĭ�Ϲ��캯�����轫ָ������Ϊ��
		node():next(nullptr){}
		~node() {}
	};

private:
	//һ�������������һ��ָ����ʼ����ָ���ʾ
	node *head;

	//��¼�������������е�Ԫ�ظ������Կռ任ʱ��)
	int number;

protected:
	//���ڻ�ȡ��i��λ�õĽ��ָ��
	node *get(int i) const;

public:
	//���캯��
	singleLinkList();
	//��������
	~singleLinkList();
	//��յ�����
	void clear();
	//���ص�����������Ԫ�ظ���
	int length() const;
	//�ڵ�i��λ���ϲ����µ�һ������Ԫ��
	bool insert(int i, const Type &x);
	//ɾ����i��λ���ϵ�Ԫ��
	bool remove(int i);
	//����ĳ��Ԫ�أ����ҳ����ڵ������е�λ��
	int search(const Type &x) const;
	//���ʵ�i��Ԫ�أ���������ֵ
	Type visit(int i) const;
	//����������������ʵ������е�ÿ��Ԫ��
	void traverse() const;
};

//���캯��������һ���յĵ�����
template<typename Type>
singleLinkList<Type>::singleLinkList()
{
	head = new node();
	number = 0;
}

//��������
template<typename Type>
singleLinkList<Type>::~singleLinkList()
{
	//��Ҫɾ���������е�ÿһ��Ԫ�أ���
	clear();
	//clear()ֻ������������е�Ԫ�أ���ͷָ��head����û��ָ���������κ�Ԫ��
	//������Ҫ����ɾ��
	delete head;
}

//��õ�i��λ���ϵĽڵ�ָ��
template<typename Type>
singleLinkList<Type>::node *singleLinkList<Type>::get(int i) const
{
	//������Ϊ�գ��򷵻�ͷ���ָ��
	if (i < 0)
		return head;
	
	//��õ������еĵ�һ������ָ��
	node *temp = head->next;	
	for (int k = 0; k < i; ++k)
	{
		temp = temp->next;
	}
	//����ѭ�������󣬾ͻ���˴�0��ʼ�����ĵ�i������ָ��
	return temp;
}


//��յ������������������������𣿣���
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

//���㵥�����������е�Ԫ�ظ���
template<typename Type>
int singleLinkList<Type>::length() const
{
	return number;
}

//�ڵ�i��λ���ϲ���һ���µ�����Ԫ��
template<typename Type>
bool singleLinkList<Type>::insert(int i, const Type &x)
{
	if (i < 0)
	{
		cout << "�����ֵ��������������ȷ��ֵ" << endl;
		return false;
	}
	
	//��Ԫ��x�����½��
	node *newNode = new node(x);
	//��õ�i-1������ָ��
	node *temp = get(i-1);
	//��õ�i������ָ��
	node *tempi = temp->next;
	//�õ�i-1��Ԫ�صĺ��ָ��ָ���½��
	temp->next = newNode;
	//���½���nextָ��ָ��ԭ���ĵ�i��Ԫ�أ��½ڵ��Լ���Ϊ�˵�i��Ԫ��
	newNode->next = tempi;

	++number;

	return true;
}

//ɾ����i��λ���ϵ�Ԫ��
template<typename Type>
bool singleLinkList<Type>::remove(int i)
{
	if (i < 0)
	{
		cout << "��������ȷ��Χ�ڵ�ֵ" << endl;
		return false;
	}
	
	//��õ�i-1������ָ��
	node *temp = get(i-1);
	//��õ�i������ָ�룬Ҳ��Ҫ��ɾ���Ľ��
	node *del = temp->next;
	//�õ�i-1��Ԫ�ص�nextָ��ָ��ԭ�ȵĵ�i+1��Ԫ�أ�
	temp->next = del->next;

	//ɾ����i�����
	delete del;

	--number;

	return true;
}

//�����������е�ĳԪ�أ����������ڵ������е�λ��
template<typename Type>
int singleLinkList<Type>::search(const Type &x) const
{
	int k = 0;
	//��õ�1������ָ��
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

//���ʵ�i��Ԫ�أ���������ֵ
template<typename Type>
Type singleLinkList<Type>::visit(int i) const
{
	node *temp = get(i);

	return temp->data;
}

//�����������������е�ÿһ��Ԫ��
//��������ʱ��֪������Ҫ��ʲô��������ʱֻ��һ���պ��������⣬֮�󲹳�����
template<typename Type>
void singleLinkList<Type>::traverse() const
{

}



#endif SINGLELINKLIST.H