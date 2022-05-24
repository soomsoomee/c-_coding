# include <iostream>
#include "Arr.h"



void InitArr(tArr* _pArr)
{

	// 40byte 크기의 힙 메모리를 만들고 int 포인터로 강제 캐스팅.
	_pArr->pInt = (int*)malloc(sizeof(int)*2);
	_pArr->iCount = 0;
	// int를 40byte에 저장하므로 최대 10개를 넣을 수 있음. 
	_pArr->iMaxCount = 2;

}


void Reallocate(tArr* _pArr)
{
	// 동적할당은 원하는 위치에 이어서 할 수 없기 떄문에 새로운 공간에 힙 메모리 다시 확보해야 한다.
	// 1. 2배 더 큰 공간을 동적할당한다. 
	int* pNew = (int*)malloc(_pArr->iMaxCount * 2 * sizeof(int));

	// 2. 기존 공간에 있던 데이터들을 새로 할당한 공간으로 복사시킨다.
	for (int i = 0; i < _pArr->iCount; ++i)
	{
		pNew[i] = _pArr->pInt[i];
	}

	// 3. 기존 공간은 메모리 해제
	free(_pArr->pInt);

	// 4. 배열이 새로 할당된 공간을 가리키게 한다.
	_pArr->pInt = pNew;

	// 5. MaxCount 변경점 적용
	_pArr->iMaxCount *= 2;
}


void PushBack(tArr* _pArr, int _iData)
{
	// 힙 영역에할당한 공간이 다 차는지 확인
	if (_pArr->iMaxCount <= _pArr->iCount)
	{
		// 재할당
		Reallocate(_pArr);
	}

	// 데이터 추가
	_pArr->pInt[_pArr->iCount++] = _iData;

}


void ReleaseArr(tArr* _pArr)
{
	free(_pArr->pInt);
	_pArr->iCount = 0;
	// 가리키는 공간이 비어있으니까 최대 카운트도 0
	_pArr->iMaxCount = 0;

}


// 버블 정렬
void Sort(tArr* _pArr)
{	
	// 데이터가 1개 이하면 정렬하지 않음. 
	if (_pArr->iCount <= 1)
		return;
	// 오름차순 정렬
	
	while (true) // 전체 다 정렬될 때 까지 반복
	{
		bool bFinish = true;

		// iCount - 1만큼 비교한다. 
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

