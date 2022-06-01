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
	int size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }
	T& operator[](int idx);

	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);

	void clear()
	{
		m_iCount = 0; // �ѹ� �þ �޸� ������ �پ���� ����. 
	}

public:
	// �����Ϸ��� ������ �����Ϸ��� public�̾�� �Ѵ�.
	CArr();
	~CArr();


	// array �� �� �� iterator ��ü�� ������ ����� ���� �ƴ�. ���� �����ؼ� ����ؾ� ��. 
	// iterator�� �����ּҿ� �ε����� �˰� �־�� �Ѵ�. 
	// inner class�� �����ϰ� �ִ� Ŭ������ private ����� ���� ����. �ݴ�� �Ұ�����. friend ����Ͽ� �����ϰ� �� �� ����.  
	class iterator
	{
	private:
		// ���� �迭�� �˰� �־��, �޸� �� ���� ���Ҵ� �Ǵ��� �ùٸ� ���� ��ġ�� �� �� �ִ�. 
		CArr* m_pArr;  // iterator�� ����ų �����͸� �����ϴ� ���� �迭 �ּ�
		// ó�� �ּҿ� �ٲ� �ּ��� �������� �����ϰ� ����ó�� �Ϸ��� �� ���� ������ �־�� �Ѵ�.
		T*    m_pData;  // �����͵��� ���� �ּ�
		int   m_iIdx; // ����Ű�� �������� �ε���
		bool m_bValid; // iterator ��ȿ�� üũ(erase ����). �迭�� ������ ���� �޸𸮸� ����Ű����, �ٸ� �ڷ����� �׷��� ���� �� ����. 


	public:
		T& operator * ()
		{
			// iterator�� �˰��ִ� �ּҿ�, �����迭�� �˰� �ִ� �ּҰ� �޶��� ���(���� Ȯ������ �ּҰ� �޶��� ���)
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			return m_pData[m_iIdx];
		};


		iterator& operator ++() 
		{
			
			
			// 1. iterator�� �˰��ִ� �ּҿ�, �����迭�� �˰� �ִ� �ּҰ� �޶��� ���(���� Ȯ������ �ּҰ� �޶��� ���)
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx || !m_bValid)
			{
				assert(nullptr);
			}

			// 2. end iterator�� ���
			// 3. iterator�� ������ �����͸� ����Ű�� �ִ� ���
			if (m_pArr->size() - 1 == m_iIdx)
			{
				m_iIdx = -1;
			}
			else
			{
				++m_iIdx;
			}
			
			return *this; // ������ ���������ε� �����ϵ��� �ڱ� �ڽ��� ��ȯ. ++(++iter)
		};

		// ++ ����
		// �⺻ �ڷ����� �޸�, ȣ�� ������ �� ������ ���� �ƴϴ�. 
		// ��ȣ�� �ڷ��� ������ �����Ϸ��� ������ �ν���. 
		// �⺻ �ڷ��� �ƴ� ���, ���� ������ ���� ���ʿ��� ��ü ����, ���� ����� �߻���. Ư���� ������ ���ٸ� ���� ������ ���°� ���� ����. 
		iterator operator ++(int) // ���纻�� ��ȯ(ȣ���� ��ü ����)
		{
			iterator copy_iter = *this; // ���������
			++(*this);

			return copy_iter; // �������� ���� ��ü�� ��ȯ
		}


		iterator& operator --() 
		{
			return *this;
		};

		// �񱳿����� ==, !=
		bool operator == (const iterator& _otheriter)
		{
			// m_pData�� ������ �迭�� ���� �ּҰ� ���� ���̴ϱ� ���� �迭��. 
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

		friend class CArr; // private ���� ���� (������ �ʿ��� ���� ���� ������ ���� ����.)
	};

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

};


template<typename T>
CArr<T>::~CArr()
{
	// �ڷ����� ������ ���� ���� []�� ����Ѵ�. 
	// m_pInt�� ���� int �ڷ����� ������ �ִٴ� ��. �� ��ü�� ���� �Ҹ��ڸ� �����Ѵ�. 
	delete[] m_pData;
};


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

};


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
};


template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}


template<typename T>
typename CArr<T>::iterator CArr<T>::begin() // ��ȯ Ÿ���� ����ϱ� ���� typename�� �ٿ��� ��. 
{
	// ������ ����Ű�� iterator�� ���� ��ȯ����. ������ ���� �ӽ� ��ü�� ��ȯ. 

	if (0 == m_iCount)
		// �����Ͱ� ���� ���, begin() == end();
		return iterator(this, m_pData, -1);// idx=-1�� ���� end iterator��� �ϴ� ���.(���ϱ� ����)
	return iterator(this, m_pData, 0);
};


template<typename T>
typename CArr<T>::iterator CArr<T>::end()
{
	// ���� ������ ����Ű�� iterator�� ���� ��ȯ�� ��. 
	return iterator(this, m_pData, -1);// idx=-1�� ���� end iterator��� �ϴ� ���.(���ϱ� ����)
};


template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	// erase �Լ��� ���� iterator�� erase�� �������ϴ� �迭�� �ƴ� ���
	// iterator�� �ٸ� Arr�� ��Ҹ� ����Ű�� ���, end iterator�� ��� ���� ó��, �迭 ���̺��� �� ū ���� ������ ���
	if (this != _iter.m_pArr || end() == _iter || m_iCount <= _iter.m_iIdx)
	{
		assert(nullptr);
	};

	// iterator�� ����Ű�� �����͸� �迭 ������ �����Ѵ�.
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1);  // ������ ����� ���� �о�� �ϴ� �ݺ� Ƚ��


	for (int i = 0; i < iLoopCount; ++i)
	{
		// �������ϴ� �ε����� ����� �ʺ��� ä���� �Ѵ�. �� �ݴ�� �ϸ� �����Ͱ� ��������� ������ �ȵȴ�. 
		m_pData[i + _iter.m_iIdx] = m_pData[i + _iter.m_iIdx + 1];
	};

	_iter.m_bValid = false;
		
 
	// ī��Ʈ ����
	--m_iCount;

	return iterator(this, m_pData, _iter.m_iIdx); // ������ ���� ����Ű�� iterator���� ���� �ε����� ����Ű�� ���ο� iterator�� ��ȯ. m_bValid=true�� ��ȯ. 
};




