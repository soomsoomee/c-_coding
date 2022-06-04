#pragma once


// c++ 기준으로 클래스와 구조체는 차이가 없다고 봐도 된다. 단, 구조체의 default는 public.


template<typename T>
struct tListNode
{
	T               data;
	// 선언 내부에서 자신을 지칭할 때는 T를 명시하지 않아도 됨. 
	tListNode<T>*   pPrev;
	tListNode<T>* pNext;

	tListNode()
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{

	}

	// 생성자 오버로딩
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
	// 다른 클래스나 구조체에서 템플릿 사용할 때에는 T를 명시해야 함. 
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
		tListNode<T>*     m_pNode; // null인 경우, end iterator로 간주
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
			// end에서 ++한 경우
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
	// 입력된 데이터를 저장할 노드를 동적할당 함. 
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, nullptr);

	// 처음 입력된 데이터라면
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		// 데이터가 1개 이상 입력된 경우
		// 현재 가장 마지막 데이터(tail)을 저장하고 있는 노드와 새로 생성된 노드가 서로 가리키게 한다.

		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;

		// List 마짐가 노드의 주소값을 새로 입력된 노드로 갱신한다.
		m_pTail = pNewNode;
	}

	// 데이터 개수 증가
	++m_iCount;
};

template<typename T>
inline void CList<T>::push_front(const T& _data)
{
	// 새로 생성된 노드의 다음을 현재 헤도노드의 주소값으로 채움. 
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);

	// 현재 헤드노드의 이전 노드 주소값을 새로 생성된 노드의 주소로 채움.
	m_pHead->pPrev = pNewNode;

	// 새로 생성된 노드를 새로운헤드 주소로 갱신한다. 
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
	// 리스트가 비어있을 때 begin으로 받아온 iterator를 end로 본다.
	// 리스트 비어있으면 헤드 노드는 nullptr
	// 마지막 노드 다음도 nullptr
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

	// 리스트에 추가되는 데이터를 저장할 Node 생성
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	// iterator가 가리키는 노드가 헤드 노드인 경우
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pPrev = pNode;
		m_pHead = pNode;
	}
	else
	{
		// iterator가 가리키고 있는 노드의 이전으로 가서 다음 노드 주소를 새로 생성한 노드로 지정
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;
		
		// iterator가 가리키고 있는 노드의 이전을 새로운 노드로 지정
		// 새로운 노드의 pNext를 iterator가 가리키고 있는 노드로 지정
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