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

	// �θ�� ���� ���� �ڽ������� �����ϴ� �Լ�
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
	tBSTNode<T1, T2>* m_pRoot; // ��Ʈ ��� �ּ�
	int m_iCount; // ������ ����

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
		tBSTNode<T1, T2>* m_pNode; // null�� ��� end iterator

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

		// �������� ���ϵ��� const
		const tPair<T1, T2>& operator*()
		{
			assert(m_pNode); // nullptr�� ���(end iterator���� �ƴ���)
			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator ->()
		{
			assert(m_pNode); // nullptr�� ���(end iterator���� �ƴ���)
			return &m_pNode->pair;
		}

		iterator& operator ++()
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode); // �����ļ���(������ȸ ���� ���� ���) ��������
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

	// ù���� �����Ͷ��
	if (nullptr == m_pRoot)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		// �ܸ���尡 �� ������ �񱳸� �ݺ�
		tBSTNode<T1, T2>* pNode = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;

		while (true)
		{

			// ����ģ ��� ���� �� ������ ���������� ���� ���ؾ� �Ѵ�.
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			// ����ģ ����� ���� �� ũ�� �������� ���� ���ؾ� �Ѵ�.
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			// �ߺ� key�� ����� ������ ���ؾ���. ���⼭�� ������� �ʴ� ������ ����.
			// map�� ������� �ʰ�, multi map�� �ߺ� �����ϰ� �ؼ� �ߺ� key �ִ� ��� ���� �����ؼ� ����. Ž�� ȿ���� �������� ��.
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

	// ������ ���� ����
	++m_iCount;
}


// �����ļ��� �켱 ���� 
template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* pSuccessor = nullptr;

	// 1. ������ �ڽ��� �ִ� ���: ������ �ڽ����� ���� ���� �ڽ��� ���������� ������
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	// 2. �θ�κ��� ���� �ڽ��� ������ ���� �ö�
	// �� �� �θ� �ļ��� 
	else
	{
		pSuccessor = _pNode;

		while (true)
		{
			// ���̻� �������� �ö� �� ���� -> ������ ���
			if (pSuccessor->IsRoot())
				return nullptr;

			// �θ�κ��� ���� �ڽ����� üũ
			if (pSuccessor->IsLeftChild())
			{
				// �� �� �θ� �ļ���
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


// ������ header�� �����ϸ� inlineó�� �Ǳ� ��. 
template<typename T1, typename T2>
inline typename CBST<T1, T2>::iterator CBST<T1, T2>::begin()
{
	// ������ȸ�� leaf node���� ��������
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
	// ���ϴ� ��尡 ���� ������ �񱳸� �ݺ�: ������ ���� ������ ����
	tBSTNode<T1, T2>* pNode = m_pRoot;
	NODE_TYPE node_type = NODE_TYPE::END;

	while (true)
	{

		// ����ģ ��� ���� �� ������ ���������� ���� ���ؾ� �Ѵ�.
		if (pNode->pair.first < _find)
		{
			node_type = NODE_TYPE::RCHILD;
		}
		// ����ģ ����� ���� �� ũ�� �������� ���� ���ؾ� �Ѵ�.
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		// �ߺ� key�� ����� ������ ���ؾ���. ���⼭�� ������� �ʴ� ������ ����.
		// map�� ������� �ʰ�, multi map�� �ߺ� �����ϰ� �ؼ� �ߺ� key �ִ� ��� ���� �����ؼ� ����. Ž�� ȿ���� �������� ��.
		else
		{
			// ã�Ҵ�.
			break;
		}

		if (nullptr == pNode->arrNode[(int)node_type])
		{
			// ���̻� ������ �ڸ��� ������ �� ã�� ��. 
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

	// ���� ��� ��� ����� �����ļ��ڸ� ����Ű�� iterator ��ȯ
	tBSTNode<T1, T2>* pSuccessor = DeleteNode(_iter.m_pNode);
	return iterator(this, pSuccessor);
}


template<typename T1, typename T2>
inline tBSTNode<T1, T2>* CBST<T1, T2>::DeleteNode(tBSTNode<T1, T2>* _pTargetNode)
{
	// ������ų ����� �ļ��� ��带 ã�Ƶд�. 
	tBSTNode<T1, T2>* pSuccessor = GetInOrderSuccessor(_pTargetNode);

	// 1. �ڽ��� �ϳ��� ���� ��� : �θ� ����� �ڽ��� ����� ��带 ���ָ� �ȴ�.
	if (_pTargetNode->IsLeaf())
	{
		// ������ ��尡 ��Ʈ����. (�ڽ��� ���� ��Ʈ: BST �ȿ� �����Ͱ� 1�� �ۿ� ������.)
		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = nullptr;
		}
		else
		{
			// �θ���� �����ؼ� ������ ����� �ڽ��� ����Ű�� �����͸� nullptr�� �����.
			if (_pTargetNode->IsLeftChild())
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr;
			else
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr;

		}
		delete _pTargetNode;
		// ������ ���� �����ֱ�
		--m_iCount;
	}

	// 2. �ڽ��� 2���� ��� 
	else if (_pTargetNode->IsFull())
	{
		// ������ �ڸ��� ���� �ļ���(�Ǵ� ���� ������)�� ���� �����Ų��.
		_pTargetNode->pair = pSuccessor->pair;

		// ���� �ļ��� ��带 �����Ѵ�. (���� �ļ��ڴ� �ڽ��� �ִ� 1��)
		DeleteNode(pSuccessor);


		// ������ ��尡 �����ļ��� ��尡 ��. ���� �����ϴϱ�.
		pSuccessor = _pTargetNode;
	}


	// 3. �ڽ��� 1���� ��� 
	else
	{

		NODE_TYPE eChildType = NODE_TYPE::LCHILD;
		if (_pTargetNode->arrNode[(int)NODE_TYPE::RCHILD])
			eChildType = NODE_TYPE::RCHILD;

		// ������ ��尡 ��Ʈ����. 
		if (_pTargetNode == m_pRoot)
		{
			// �ڽĳ��(1��)�� ��Ʈ�� �����.
			m_pRoot = _pTargetNode->arrNode[(int)eChildType];
			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
		}
		else
		{
			// ������ ����� �θ��, ������ ����� �ڽ��� �������ش�. (�̹� ������ ������ ����.)
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
		// ������ ���� �����ֱ�
		--m_iCount;
	}

	
	return  pSuccessor;
}



