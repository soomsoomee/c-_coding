#pragma once


// c++ �������� Ŭ������ ����ü�� ���̰� ���ٰ� ���� �ȴ�. ��, ����ü�� default�� public.


template<typename T>
struct tListNode
{
	T               data;
	// ���� ���ο��� �ڽ��� ��Ī�� ���� T�� ������� �ʾƵ� ��. 
	tListNode<T>*   pPrev;
	tListNode<T>* pNext;

	tListNode()
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{

	}

	// ������ �����ε�
	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext)
		: data(_data)
		, pPrev(_pPrev)
		, pNext(_pNext)
	{

	}
};


template<typename T>
class CList
{
private:
	// �ٸ� Ŭ������ ����ü���� ���ø� ����� ������ T�� ����ؾ� ��. 
	tListNode<T>*	m_pHead;
	tListNode<T>*		m_pTail;
	int				m_iCount;

public:
	void push_back(const T& _data);
	void push_front(const T& _data);
	int size() { return m_iCount; }

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator erase();
	iterator insert(const iterator& _iter, const T& _data);

public:

	CList();
	~CList();


	class iterator
	{

	private:
		CList<T>*         m_pList;
		tListNode<T>*     m_pNode; // null�� ���, end iterator�� ����
		bool              m_bValid;


	public:
		T& operator* ()
		{
			return m_pNode->data;
		}

		bool operator ==(const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator !=(const iterator& _otheriter)
		{
			return !(*this == _otheriter);
		}

		iterator operator ++()
		{
			// end���� ++�� ���
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pNext;

			return *this;
		}

		iterator operator ++(int)
		{
			iterator copyiter(*this);

			++(*this);

			return copyiter;

		}

		iterator operator --()
		{

		}

		iterator operator --(int)
		{

		}

	public:
		iterator()
			: m_pList(nullptr)
			, m_pNode(nullptr)
			, m_bValid(false)
		{
		};
		iterator(CList<T>* _pList, tListNode<T>* _pNode)
			: m_pList(_pList)
			, m_pNode(_pNode)
			, m_bValid(false)
		{
			if (nullptr != _pList && nullptr != _pNode)
			{
				m_bValid = true;
			}
		};

		~iterator()
		{

		};

		friend class CList;
	};
	 

};

template<typename T>
CList<T>::CList()
	: m_pHead(nullptr)
	, m_pTail(nullptr)
	, m_iCount(0)
{

};

template<typename T>
inline void CList<T>::push_back(const T& _data)
{
	// �Էµ� �����͸� ������ ��带 �����Ҵ� ��. 
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, nullptr);

	// ó�� �Էµ� �����Ͷ��
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		// �����Ͱ� 1�� �̻� �Էµ� ���
		// ���� ���� ������ ������(tail)�� �����ϰ� �ִ� ���� ���� ������ ��尡 ���� ����Ű�� �Ѵ�.

		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;

		// List ������ ����� �ּҰ��� ���� �Էµ� ���� �����Ѵ�.
		m_pTail = pNewNode;
	}

	// ������ ���� ����
	++m_iCount;
};

template<typename T>
inline void CList<T>::push_front(const T& _data)
{
	// ���� ������ ����� ������ ���� �쵵����� �ּҰ����� ä��. 
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);

	// ���� ������� ���� ��� �ּҰ��� ���� ������ ����� �ּҷ� ä��.
	m_pHead->pPrev = pNewNode;

	// ���� ������ ��带 ���ο���� �ּҷ� �����Ѵ�. 
	m_pHead = pNewNode;

	++m_iCount;
}

template<typename T>
inline typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this, m_pHead);
}


template<typename T>
inline typename CList<T>::iterator CList<T>::end()
{
	// ����Ʈ�� ������� �� begin���� �޾ƿ� iterator�� end�� ����.
	// ����Ʈ ��������� ��� ���� nullptr
	// ������ ��� ������ nullptr
	return iterator(this, nullptr);
}

template<typename T>
inline typename CList<T>::iterator CList<T>::erase()
{
	return iterator();
}


template<typename T>
inline typename CList<T>::iterator CList<T>::insert(const iterator& _iter, const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
	}

	// ����Ʈ�� �߰��Ǵ� �����͸� ������ Node ����
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	// iterator�� ����Ű�� ��尡 ��� ����� ���
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pPrev = pNode;
		m_pHead = pNode;
	}
	else
	{
		// iterator�� ����Ű�� �ִ� ����� �������� ���� ���� ��� �ּҸ� ���� ������ ���� ����
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;
		
		// iterator�� ����Ű�� �ִ� ����� ������ ���ο� ���� ����
		// ���ο� ����� pNext�� iterator�� ����Ű�� �ִ� ���� ����
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
	}
	
	++m_iCount;

	return iterator(this, pNode);
}
;

template<typename T>
CList<T>:: ~CList()
{
	tListNode<T>* pDeleteNode = m_pHead;

	while (pDeleteNode)
	{
		tListNode<T>* pNext = pDeleteNode->pNext;
		free(pDeleteNode);
		pDeleteNode = pNext;

	}
};