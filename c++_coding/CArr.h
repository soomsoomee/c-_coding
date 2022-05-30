#pragma once

#include <assert.h>

template<typename T>
class CArr
{
private: // �⺻�� private
	// ctrl + rr : ������ ����
	// ���� �ڷ����� ���� �� �ִ� �Լ� �����
	T* m_pData;
	int m_iCount;
	int m_iMaxCount;


public:
	// 
	void push_back(const T& _Data);
	// ���ʿ� ���ϴ� ������ ������ �� �ֵ��� ���� ����
	void resize(int _iResizeCount);
	T* data() { return m_pData; }
	int size() { return m_iCount;  }
	int capacity{ return m_iMaxCount; }
	T& operator[](int idx);


public:
	// �����Ϸ��� ������ �����Ϸ��� public�̾�� �Ѵ�.
	CArr();
	~CArr();

};


// ���ø� �Լ��� ��� ���Ͽ� �־����. 
// ��� ���Ͽ� ���� �־��, main���� �ڷ��� �־ �Լ� ����� �� �ű⿡ ���� �Լ����� �����ϵȴ�. 

template<typename T>
CArr<T>::CArr()
// ������ ��� ������� �ϴ°� ����
	: m_pData(nullptr)
	, m_iCount(0)
	, m_iMaxCount(2)
{
	// C�� malloc ������ c++������ new ��� ����
	m_pData = new T[2];

}


template<typename T>
CArr<T>::~CArr()
{
	// �ڷ����� ������ ���� ���� []�� ����Ѵ�. 
	// m_pInt�� ���� int �ڷ����� ������ �ִٴ� ��. �� ��ü�� ���� �Ҹ��ڸ� �����Ѵ�. 
	delete[] m_pData;
}


template<typename T>
// �ڷ����� Ŀ�� �� �ֱ� ������ �����ؼ� ���� �ʰ� �����͸� �����. 
void CArr<T>::push_back(const T& _Data)
{


	// �� �������Ҵ��� ������ �� ������ Ȯ��
	if (m_iMaxCount <= m_iCount)
	{
		// ���Ҵ�
		resize(m_iMaxCount * 2);
	}

	// ������ �߰�
	m_pData[m_iCount++] = _Data;

}


template<typename T>
void CArr<T>::resize(int _iResizeCount)
{
	// ���� �ִ� ���뷮���� �� ���� ��ġ�� Ȯ���Ϸ��� ��� 
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);
	}

	// 1. 2�� �� ū ������ �����Ҵ��Ѵ�. 
	T* pNew = new T[_iResizeCount];

	// 2. ���� ������ �ִ� �����͵��� ���� �Ҵ��� �������� �����Ų��.
	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_pData[i];
	}

	// 3. ���� ������ �޸� ����
	delete[] m_pData;

	// 4. �迭�� ���� �Ҵ�� ������ ����Ű�� �Ѵ�.
	m_pData = pNew;

	// 5. MaxCount ������ ����
	m_iMaxCount = _iResizeCount;
}


template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}

