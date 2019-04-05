#ifndef SEQLIST.H
#define SEQLIST.H

#include "List.h"
#include <iostream>

using namespace std;


/*˳�����*/

/*ע��㣺
	1������һ����̬������Ҫ����������ָ��������ʼλ�õ�ָ��������ģ��
	2����ʱû�뵽����������ʲô�����Ŀ�꣬������ʱʹ�ÿպ�����֮������
	�������Ҫ����˳����Ŀ������ʱ���ٽ�traverse()��������������
	3������Ĵ�����ֻ�ǵ��������һ����Ϣ���ѣ�֮���Ƿ��и��õķ�ʽ
	������չʾ������
	4�������clear()��ɾ��remove()�����У�ֻ�ǵ����ؽ�����length���٣���֮ǰ
	�Ѵ��ڵ�Ԫ��������ɾ�����𣿣����Ƿ�Ҫ��ʾ����delete��Ԫ�ؽ���ɾ��������
	*/

template<typename Type>
class seqList : public List<Type>
{
private:
	//���ö�̬�������洢���Ա�
	//ָ��������ʼλ�õ�ָ��
	Type *data;				
	//�������������е�Ԫ�ظ���
	int length;
	//�������Ա������ܴ洢�����Ԫ�ظ�������������Ҫ����洢�ռ�
	int maxSize;

	//����洢�ռ�
	void doubleSpace();

public:
	//���캯�������ڴ���һ���յ�˳���
	seqList(int initSize);
	//��������
	~seqList();
	//�ڵ�i��λ�ò���Ԫ��
	bool insert(int i, const Type &x);
	//���˳���
	void clear();
	//����˳����е�Ԫ�ظ���
	int length() const;
	//ɾ����i��λ�õ�Ԫ��
	bool remove(int i);
	//����ĳ��Ԫ���Ƿ���֣��ҵ�����λ��
	int search(const Type &x) const;
	//���ʵ�i��Ԫ�أ�������ֵ
	Type visit(int i) const;
	//����˳����������˳����е�ÿһԪ��
	void traverse() const;
};

//���캯���������ṩ�ĳ�ʼ��С
template<typename Type>
seqList<Type>::seqList(int initSize)
{
	//�����жϳ�ʼֵ�Ƿ����
	if (initSize < 0)
	{
		cout << "�����ĳ�ʼֵ������" << endl;
		return;
	}
	
	//�����ʼ��С������ռ䣬����ָ��ָ���������ʼλ��
	data = new Type[initSize];
	maxSize = initSize;
	//���ó�ʼ��Ԫ�ظ���Ϊ0
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

	//�������ռ�
	maxSize *= 2;
	//��������һ�����Ĵ洢�ռ�
	data = new Type[maxSize];

	for (int j = 0; j < length; ++j)
	{
		data[j] = temp[j];
	}

	delete[] temp;

}

//�ڵ�i��λ�ò���Ԫ��x
/*ע�⣺�������õ�i��λ�þͶ�Ӧa[i],Ҳ��λ���Ǵ�0��ʼ�����ģ�
	Ҳ�����ڵ�0��λ�ò��룬���ǲ�������ʼλ���ϣ����һ��λ����(length-1)*/
template<typename Type>
bool seqList<Type>::insert(int i, const Type &x)
{
	if (i < 0)
	{
		cout << "����ķ�Χ����ȷ����������ȷ��ֵ" << endl;
		return false;
	}
	
	if (length >= maxSize - 1)
		doubleSpace();
	//�����һ��λ�ÿ�ʼ������ƶ�һ��λ��
	for (int k = length - 1; k >= i; --k)
	{
		data[k + 1] = data[k];
	}
	//����Ԫ�ز��뵽��i��λ����
	data[i] = x;

	//�����е�Ԫ�ظ���ҲҪ��1
	++length;
	return true;
}

//���˳���
template<typename Type>
void seqList<Type>::clear()
{
	//������Ԫ�ظ�������Ϊ0�Ϳ������𣿣���֮ǰ���е�Ԫ�ز�Ҫ�����𣿣�����
	length = 0;
}

//�õ�˳����е�Ԫ�ظ���
template<typename Type>
int seqList<Type>::length() const
{
	return length;
}

//ɾ����i��λ���ϵ�Ԫ��
template<typename Type>
bool seqList<Type>::remove(int pos)
{
	//Type temp = data[pos];

	if (pox < 0 || pos >= length)
	{
		cout << "��������ȷ��Χ�ڵ�ֵ��" << endl;
		return false;
	}

	for (int i = pos; i < length - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--length;

	//Ҫ����������𣿣�����Ҫ����Ϊtemp����ָ�룡��ֻ��һ����3�� 0.8�������͵�Ԫ��
	//delete temp;

	return true;
}

//����Ԫ��x��˳����е�λ��
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

//���ʵ�i��Ԫ�أ�������ֵ
template<typename Type>
Type seqList<Type>::visit(int x) const
{
	//��ʱȱ�ٴ�����ʽ
	if(x < length && x >= 0)
		return data[x];
	else
	{
		//�����Ƿǳ����ԵĴ�����ʽ��ֻ�ǵ��������������Ϣ
		//֮���Ƿ����������õķ�ʽչ�ֳ���
		cout << "�����ֵ���ڷ�Χ�ڣ���������ȷ��ֵ��" << endl;
	}
}

//��������˳����е�Ԫ��
//��ʱ��֪��Ҫ����������ʲô��������ʱֻ�Ǹ���һ���ո�ĺ��������⣬
//֮���־���Ҫ��ʱ���ٽ�������
template<typename Type>
void seqList<Type>::traverse() const
{

}

#endif