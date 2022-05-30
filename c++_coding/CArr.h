#pragma once

#include <assert.h>

template<typename T>
class CArr
{
private: // 기본이 private
	// ctrl + rr : 변수명 변경
	// 여러 자료형을 넣을 수 있는 함수 만들기
	T* m_pData;
	int m_iCount;
	int m_iMaxCount;


public:
	// 
	void push_back(const T& _Data);
	// 최초에 원하는 사이즈 설정할 수 있도록 공개 설정
	void resize(int _iResizeCount);
	T* data() { return m_pData; }
	int size() { return m_iCount;  }
	int capacity{ return m_iMaxCount; }
	T& operator[](int idx);


public:
	// 컴파일러가 생성자 실행하려면 public이어야 한다.
	CArr();
	~CArr();

};


// 템플릿 함수는 헤더 파일에 있어야함. 
// 헤더 파일에 전부 있어야, main에서 자료형 넣어서 함수 사용할 때 거기에 따른 함수까지 컴파일된다. 

template<typename T>
CArr<T>::CArr()
// 선언한 멤버 순서대로 하는것 권장
	: m_pData(nullptr)
	, m_iCount(0)
	, m_iMaxCount(2)
{
	// C는 malloc 쓰지만 c++에서는 new 사용 가능
	m_pData = new T[2];

}


template<typename T>
CArr<T>::~CArr()
{
	// 자료형이 여러개 있을 떄는 []를 사용한다. 
	// m_pInt에 가면 int 자료형이 여러개 있다는 뜻. 각 객체에 대해 소멸자를 실행한다. 
	delete[] m_pData;
}


template<typename T>
// 자료형이 커질 수 있기 때문에 복사해서 넣지 않고 포인터를 사용함. 
void CArr<T>::push_back(const T& _Data)
{


	// 힙 영역에할당한 공간이 다 차는지 확인
	if (m_iMaxCount <= m_iCount)
	{
		// 재할당
		resize(m_iMaxCount * 2);
	}

	// 데이터 추가
	m_pData[m_iCount++] = _Data;

}


template<typename T>
void CArr<T>::resize(int _iResizeCount)
{
	// 현재 최대 수용량보다 더 적은 수치로 확장하려는 경우 
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);
	}

	// 1. 2배 더 큰 공간을 동적할당한다. 
	T* pNew = new T[_iResizeCount];

	// 2. 기존 공간에 있던 데이터들을 새로 할당한 공간으로 복사시킨다.
	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_pData[i];
	}

	// 3. 기존 공간은 메모리 해제
	delete[] m_pData;

	// 4. 배열이 새로 할당된 공간을 가리키게 한다.
	m_pData = pNew;

	// 5. MaxCount 변경점 적용
	m_iMaxCount = _iResizeCount;
}


template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}

