# include <iostream>
#include "Arr.h"



void InitArr(tArr* _pArr)
{

	// 40byte ũ���� �� �޸𸮸� ����� int �����ͷ� ���� ĳ����.
	_pArr->pInt = (int*)malloc(sizeof(int)*2);
	_pArr->iCount = 0;
	// int�� 40byte�� �����ϹǷ� �ִ� 10���� ���� �� ����. 
	_pArr->iMaxCount = 2;

}


void Reallocate(tArr* _pArr)
{
	// �����Ҵ��� ���ϴ� ��ġ�� �̾ �� �� ���� ������ ���ο� ������ �� �޸� �ٽ� Ȯ���ؾ� �Ѵ�.
	// 1. 2�� �� ū ������ �����Ҵ��Ѵ�. 
	int* pNew = (int*)malloc(_pArr->iMaxCount * 2 * sizeof(int));

	// 2. ���� ������ �ִ� �����͵��� ���� �Ҵ��� �������� �����Ų��.
	for (int i = 0; i < _pArr->iCount; ++i)
	{
		pNew[i] = _pArr->pInt[i];
	}

	// 3. ���� ������ �޸� ����
	free(_pArr->pInt);

	// 4. �迭�� ���� �Ҵ�� ������ ����Ű�� �Ѵ�.
	_pArr->pInt = pNew;

	// 5. MaxCount ������ ����
	_pArr->iMaxCount *= 2;
}


void PushBack(tArr* _pArr, int _iData)
{
	// �� �������Ҵ��� ������ �� ������ Ȯ��
	if (_pArr->iMaxCount <= _pArr->iCount)
	{
		// ���Ҵ�
		Reallocate(_pArr);
	}

	// ������ �߰�
	_pArr->pInt[_pArr->iCount++] = _iData;

}


void ReleaseArr(tArr* _pArr)
{
	free(_pArr->pInt);
	_pArr->iCount = 0;
	// ����Ű�� ������ ��������ϱ� �ִ� ī��Ʈ�� 0
	_pArr->iMaxCount = 0;

}


// ���� ����
void Sort(tArr* _pArr)
{	
	// �����Ͱ� 1�� ���ϸ� �������� ����. 
	if (_pArr->iCount <= 1)
		return;
	// �������� ����
	
	while (true) // ��ü �� ���ĵ� �� ���� �ݺ�
	{
		bool bFinish = true;

		// iCount - 1��ŭ ���Ѵ�. 
		int iLoop = _pArr->iCount - 1;
		for (int i = 0; i < iLoop; ++i)
		{
			if (_pArr->pInt[i] > _pArr->pInt[i + 1])
			{
				int iTemp = _pArr->pInt[i];
				_pArr->pInt[i] = _pArr->pInt[i + 1];
				_pArr->pInt[i + 1] = iTemp;

				bFinish = false;
			}
		}

		if (bFinish)
		{
			break;
		}
	}
}

void Sort_p(tArr* _pArr, void(*SortFunc)(int*, int))
{
	SortFunc(_pArr->pInt, _pArr->iCount);
}

