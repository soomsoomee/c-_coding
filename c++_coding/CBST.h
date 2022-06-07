#pragma once
# include <assert.h>

enum class NODE_TYPE
{
	PARENT, // 0
	LCHILD, // 1
	RCHILD, // 2
	END, // 3
};


template<typename T1, typename T2>
struct tPair
{
	T1 first;
	T2 second;

	tPair()
		: first()
		, second()
	{}

	tPair(const T1 _first, const T2 _second)
		: first(_first)
		, second(_second)
	{}
};

template<typename T1, typename T2>
tPair<T1, T2> make_bstpair(const T1& _first, const T2& _second)
{
	return tPair<T1, T2>(_first, _second);
}

template<typename T1, typename T2>
struct tBSTNode
{
	// data
	tPair<T1, T2> pair;

	tBSTNode* arrNode[(int)NODE_TYPE::END];

	bool IsRoot()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::PARENT])
			return true;
		return false;
	}

	// 부모로 부터 왼쪽 자식인지를 리턴하는 함수
	bool IsLeftChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
		{
			return true;
		}
		return false;
	}

	bool IsRightChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
		{
			return true;
		}
		return false;
	}

	bool IsLeaf()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::LCHILD] && nullptr == arrNode[(int)NODE_TYPE::RCHILD])
			return true;
		return false;
	}

	bool IsFull()
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] && arrNode[(int)NODE_TYPE::RCHILD])
			return true;
		return false;
	}

	tBSTNode()
		: pair()
		, arrNode{}
	{
	}

	tBSTNode(const tPair<T1, T2>& _pair, tBSTNode* _pParent, tBSTNode* _pLChild, tBSTNode* _pRchild)
		: pair(_pair)
		, arrNode{ _pParent, _pLChild, _pRchild }
	{
	}
};

template <typename T1, typename T2>
class CBST
{
private:
	tBSTNode<T1, T2>* m_pRoot; // 루트 노드 주소
	int m_iCount; // 데이터 개수

public:
	bool insert(const tPair<T1, T2>& _pair);
	tBSTNode<T1, T2>* GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode);
	tBSTNode<T1, T2>* GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode);
	class iterator;

public:
	iterator begin();
	iterator end();
	iterator find(const T1& _find);
	iterator erase(const iterator& _iter);

private:
	tBSTNode<T1, T2>* DeleteNode(tBSTNode<T1, T2>* _pTargetNode);

public:
	CBST()
		: m_pRoot(nullptr)
		, m_iCount(0)
	{
	}

	// iterator
	class iterator
	{
	private:
		CBST<T1, T2>* m_pBST;
		tBSTNode<T1, T2>* m_pNode; // null인 경우 end iterator

	public:
		bool operator == (const iterator& _other)
		{
			if (m_pBST == _other.m_pBST && m_pNode == _other.m_pNode)
				return true;
			return false;
		}

		bool operator != (const iterator& _other)
		{
			return !(*this == _other);
		}

		// 수정하지 못하도록 const
		const tPair<T1, T2>& operator*()
		{
			assert(m_pNode); // nullptr인 경우(end iterator인지 아닌지)
			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator ->()
		{
			assert(m_pNode); // nullptr인 경우(end iterator인지 아닌지)
			return &m_pNode->pair;
		}

		iterator& operator ++()
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode); // 중위후속자(중위순회 기준 다음 노드) 가져오기
			return *this;
		}

	public:
		iterator()
			: m_pBST(nullptr)
			, m_pNode(nullptr)
		{}

		iterator(CBST<T1, T2>* _pBST, tBSTNode<T1, T2>* _pNode)
			: m_pBST(_pBST)
			, m_pNode(_pNode)
		{}

		friend class CBST<T1, T2>;
	};
};


template<typename T1, typename T2>
inline bool CBST<T1, T2>::insert(const tPair<T1, T2>& _pair)
{
	tBSTNode<T1, T2>* pNewNode = new tBSTNode<T1, T2>(_pair, nullptr, nullptr, nullptr);
	pNewNode->pair = _pair;

	// 첫번쨰 데이터라면
	if (nullptr == m_pRoot)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		// 단말노드가 될 떄까지 비교를 반복
		tBSTNode<T1, T2>* pNode = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;

		while (true)
		{

			// 마주친 노드 값이 더 작으면 오른쪽으로 가서 비교해야 한다.
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			// 마주친 노드의 값이 더 크면 왼쪽으로 가서 비교해야 한다.
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			// 중복 key를 허용할 것인지 정해야함. 여기서는 허용하지 않는 것으로 구현.
			// map은 허용하지 않고, multi map은 중복 가능하게 해서 중복 key 있는 경우 서로 연결해서 저장. 탐색 효율은 떨어지게 됨.
			else
			{
				return false;
			}
			
			if (nullptr == pNode->arrNode[(int)node_type])
			{
				pNode->arrNode[(int)node_type] = pNewNode;
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];
			}
			
		}
		
	}

	// 데이터 개수 증가
	++m_iCount;
}


// 중위후속자 우선 순위 
template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* pSuccessor = nullptr;

	// 1. 오른쪽 자식이 있는 경우: 오른쪽 자식으로 가서 왼쪽 자식이 없을때까지 내려감
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	// 2. 부모로부터 왼쪽 자식일 때까지 위로 올라감
	// 그 떄 부모가 후속자 
	else
	{
		pSuccessor = _pNode;

		while (true)
		{
			// 더이상 위쪽으로 올라갈 수 없다 -> 마지막 노드
			if (pSuccessor->IsRoot())
				return nullptr;

			// 부모로부터 왼쪽 자식인지 체크
			if (pSuccessor->IsLeftChild())
			{
				// 그 떄 부모가 후속자
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}
				
		}
	
	}

	return pSuccessor;
}


template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode)
{
	return nullptr;
}


// 어차피 header에 구현하면 inline처리 되긴 함. 
template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::begin()
{
	// 중위순회로 leaf node까지 내려가기
	tBSTNode<T1, T2>* pNode = m_pRoot;
	while (pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}
	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline  typename CBST<T1, T2>::iterator CBST<T1, T2>::end()
{

	return iterator(this, nullptr);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::find(const T1& _find)
{
	// 원하는 노드가 나올 떄까지 비교를 반복: 데이터 삽입 과정과 유사
	tBSTNode<T1, T2>* pNode = m_pRoot;
	NODE_TYPE node_type = NODE_TYPE::END;

	while (true)
	{

		// 마주친 노드 값이 더 작으면 오른쪽으로 가서 비교해야 한다.
		if (pNode->pair.first < _find)
		{
			node_type = NODE_TYPE::RCHILD;
		}
		// 마주친 노드의 값이 더 크면 왼쪽으로 가서 비교해야 한다.
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		// 중복 key를 허용할 것인지 정해야함. 여기서는 허용하지 않는 것으로 구현.
		// map은 허용하지 않고, multi map은 중복 가능하게 해서 중복 key 있는 경우 서로 연결해서 저장. 탐색 효율은 떨어지게 됨.
		else
		{
			// 찾았다.
			break;
		}

		if (nullptr == pNode->arrNode[(int)node_type])
		{
			// 더이상 내려갈 자리가 없으면 못 찾은 것. 
			pNode = nullptr;
			break;
		}
		else
		{
			pNode = pNode -> arrNode[(int)node_type];
		}

	}
	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::erase(const iterator& _iter)
{
	assert(this == _iter.m_pBST);

	// 삭제 대상 노드 지우고 중위후속자를 가리키는 iterator 반환
	tBSTNode<T1, T2>* pSuccessor = DeleteNode(_iter.m_pNode);
	return iterator(this, pSuccessor);
}


template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::DeleteNode(tBSTNode<T1, T2>* _pTargetNode)
{
	// 삭제시킬 노드의 후속자 노드를 찾아둔다. 
	tBSTNode<T1, T2>* pSuccessor = GetInOrderSuccessor(_pTargetNode);

	// 1. 자식이 하나도 없는 경우 : 부모 노드의 자식을 지우고 노드를 없애면 된다.
	if (_pTargetNode->IsLeaf())
	{
		// 삭제할 노드가 루트였다. (자식이 없고 루트: BST 안에 데이터가 1개 밖에 없었다.)
		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = nullptr;
		}
		else
		{
			// 부모노드로 접근해서 삭제될 노드인 자식을 가리키는 포인터를 nullptr로 만든다.
			if (_pTargetNode->IsLeftChild())
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr;
			else
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr;

		}
		delete _pTargetNode;
		// 데이터 개수 맞춰주기
		--m_iCount;
	}

	// 2. 자식이 2개인 경우 
	else if (_pTargetNode->IsFull())
	{
		// 삭제될 자리에 중위 후속자(또는 중위 선행자)의 값을 복사시킨다.
		_pTargetNode->pair = pSuccessor->pair;

		// 중위 후속자 노드를 삭제한다. (중위 후속자는 자식이 최대 1개)
		DeleteNode(pSuccessor);


		// 삭제할 노드가 중위후속자 노드가 됨. 값을 복사하니까.
		pSuccessor = _pTargetNode;
	}


	// 3. 자식이 1개인 경우 
	else
	{

		NODE_TYPE eChildType = NODE_TYPE::LCHILD;
		if (_pTargetNode->arrNode[(int)NODE_TYPE::RCHILD])
			eChildType = NODE_TYPE::RCHILD;

		// 삭제할 노드가 루트였다. 
		if (_pTargetNode == m_pRoot)
		{
			// 자식노드(1개)를 루트로 만든다.
			m_pRoot = _pTargetNode->arrNode[(int)eChildType];
			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
		}
		else
		{
			// 삭제될 노드의 부모와, 삭제될 노드의 자식을 연결해준다. (이미 순서는 맞춰져 있음.)
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}

			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = _pTargetNode->arrNode[(int)NODE_TYPE::PARENT];
		}
		
		delete _pTargetNode;
		// 데이터 개수 맞춰주기
		--m_iCount;
	}

	
	return  pSuccessor;
}



