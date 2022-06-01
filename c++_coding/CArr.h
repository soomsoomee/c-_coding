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
	int size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }
	T& operator[](int idx);

	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);

	void clear()
	{
		m_iCount = 0; // 한번 늘어난 메모리 공간은 줄어들지 않음. 
	}

public:
	// 컴파일러가 생성자 실행하려면 public이어야 한다.
	CArr();
	~CArr();


	// array 생 길 때 iterator 객체가 저절로 생기는 것은 아님. 따로 선언해서 사용해야 함. 
	// iterator는 시작주소와 인덱스를 알고 있어야 한다. 
	// inner class를 포함하고 있는 클래스의 private 멤버에 접근 가능. 반대는 불가능함. friend 사용하여 가능하게 할 수 있음.  
	class iterator
	{
	private:
		// 원래 배열을 알고 있어야, 메모리 다 차서 재할당 되더라도 올바른 시작 위치를 알 수 있다. 
		CArr* m_pArr;  // iterator가 가리킬 데이터를 관리하는 가변 배열 주소
		// 처음 주소와 바뀐 주소의 차이점을 감지하고 예외처리 하려면 이 값도 가지고 있어야 한다.
		T*    m_pData;  // 데이터들의 시작 주소
		int   m_iIdx; // 가리키는 데이터의 인덱스
		bool m_bValid; // iterator 유효성 체크(erase 관련). 배열은 구조상 다음 메모리를 가리키지만, 다른 자료형은 그렇지 않을 수 있음. 


	public:
		T& operator * ()
		{
			// iterator가 알고있는 주소와, 가변배열이 알고 있는 주소가 달라진 경우(공간 확장으로 주소가 달라진 경우)
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			return m_pData[m_iIdx];
		};


		iterator& operator ++() 
		{
			
			
			// 1. iterator가 알고있는 주소와, 가변배열이 알고 있는 주소가 달라진 경우(공간 확장으로 주소가 달라진 경우)
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx || !m_bValid)
			{
				assert(nullptr);
			}

			// 2. end iterator인 경우
			// 3. iterator가 마지막 데이터를 가리키고 있는 경우
			if (m_pArr->size() - 1 == m_iIdx)
			{
				m_iIdx = -1;
			}
			else
			{
				++m_iIdx;
			}
			
			return *this; // 연산이 연속적으로도 가능하도록 자기 자신을 반환. ++(++iter)
		};

		// ++ 후위
		// 기본 자료형과 달리, 호출 순서가 더 나중인 것은 아니다. 
		// 괄호에 자료형 넣으면 컴파일러가 후위로 인식함. 
		// 기본 자료형 아닌 경우, 후위 연산자 쓰면 불필요한 객체 생성, 삭제 비용이 발생함. 특별한 이유가 없다면 전위 연산자 쓰는게 좋은 이유. 
		iterator operator ++(int) // 복사본을 반환(호출한 객체 말고)
		{
			iterator copy_iter = *this; // 복사생성자
			++(*this);

			return copy_iter; // 증가하지 않은 객체를 반환
		}


		iterator& operator --() 
		{
			return *this;
		};

		// 비교연산자 ==, !=
		bool operator == (const iterator& _otheriter)
		{
			// m_pData가 같으면 배열의 시작 주소가 같은 것이니까 같은 배열임. 
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
			{
				return true;
			}
			return false;
		};

		bool operator != (const iterator& _otheriter)
		{
			return !(*this == _otheriter);
		};

	public:
		iterator()
			:m_pArr(nullptr)
			,m_pData(nullptr)
			,m_iIdx(-1)
			,m_bValid(false)
		{

		};
		iterator(CArr* _pArr, T* _pData, int _iIdx)
			:m_pArr(_pArr)
			, m_pData(_pData)
			, m_iIdx(_iIdx)
			, m_bValid(false)
		{
			if (nullptr != _pArr && 0 <= _iIdx)
			{
				m_bValid = true;
			};
		};
		~iterator()
		{

		};

		friend class CArr; // private 공유 가능 (선언한 쪽에서 선언 당한 쪽으로 접근 가능.)
	};

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

};


template<typename T>
CArr<T>::~CArr()
{
	// 자료형이 여러개 있을 떄는 []를 사용한다. 
	// m_pInt에 가면 int 자료형이 여러개 있다는 뜻. 각 객체에 대해 소멸자를 실행한다. 
	delete[] m_pData;
};


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

};


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
};


template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}


template<typename T>
typename CArr<T>::iterator CArr<T>::begin() // 반환 타입을 명시하기 위해 typename을 붙여야 함. 
{
	// 시작을 가리키는 iterator를 만들어서 반환해줌. 변수명 없이 임시 객체로 반환. 

	if (0 == m_iCount)
		// 데이터가 없는 경우, begin() == end();
		return iterator(this, m_pData, -1);// idx=-1일 때를 end iterator라고 하는 경우.(정하기 나름)
	return iterator(this, m_pData, 0);
};


template<typename T>
typename CArr<T>::iterator CArr<T>::end()
{
	// 끝의 다음을 가리키는 iterator를 만들어서 반환해 줌. 
	return iterator(this, m_pData, -1);// idx=-1일 때를 end iterator라고 하는 경우.(정하기 나름)
};


template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	// erase 함수에 들어온 iterator가 erase가 지워야하는 배열이 아닌 경우
	// iterator가 다른 Arr쪽 요소를 가리키는 경우, end iterator인 경우 예외 처리, 배열 길이보다 더 큰 값이 들어오는 경우
	if (this != _iter.m_pArr || end() == _iter || m_iCount <= _iter.m_iIdx)
	{
		assert(nullptr);
	};

	// iterator가 가리키는 데이터를 배열 내에서 제거한다.
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1);  // 데이터 지우고 나서 밀어야 하는 반복 횟수


	for (int i = 0; i < iLoopCount; ++i)
	{
		// 지워야하는 인덱스와 가까운 쪽부터 채워야 한다. 그 반대로 하면 데이터가 덮어씌워지기 때문에 안된다. 
		m_pData[i + _iter.m_iIdx] = m_pData[i + _iter.m_iIdx + 1];
	};

	_iter.m_bValid = false;
		
 
	// 카운트 감소
	--m_iCount;

	return iterator(this, m_pData, _iter.m_iIdx); // 삭제된 곳을 가리키는 iterator말고 원래 인덱스를 가리키는 새로운 iterator를 반환. m_bValid=true로 반환. 
};




