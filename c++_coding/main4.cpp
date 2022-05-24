# include <iostream>
# include <time.h>

# include "Arr.h"
# include "LinkedList.h"


// 연결리스트는 가변배열에 비해 삽입이 쉬움. 맨 앞에 추가할 때, 가변배열은 복사해서 뒤로 밀어넣는 과정이 필요한데, 연결리스트는 앞의 연결만 끊고 새로 연결하면 된다.
// 가변배열은 연결리스트에 비해 데이터 읽는 시간이 짧음. 시작 주소 + 원하는 위치 블록 하면 접근 가능. 연결리스트는 모든 노드를 거쳐야함. 


// 가변배열 아니어도 사용 가능한 함수
void BubbleSort(int* _pData, int _iCount)
{
	// 데이터가 1개 이하면 정렬하지 않음. 
	if (_iCount <= 1)
		return;
	// 오름차순 정렬

	while (true) // 전체 다 정렬될 때 까지 반복
	{
		bool bFinish = true;

		// iCount - 1만큼 비교한다. 
		int iLoop = _iCount - 1;
		for (int i = 0; i < iLoop; ++i)
		{
			if (_pData[i] > _pData[i + 1])
			{
				int iTemp = _pData[i];
				_pData[i] = _pData[i + 1];
				_pData[i + 1] = iTemp;

				bFinish = false;
			}
		}

		if (bFinish)
		{
			break;
		}
	}
}



int main()
{
	int iArr[10] = { 3,5,1,5,4,1 };
	BubbleSort(iArr, 10);


	// 가변 배열
	tArr s1 = {};
	tArr s2 = {};
	tArr s3 = {};

	// 메인함수가 종료될 때 객체는 해제되지만, heap memory는 해제되지 않음. 
	InitArr(&s1);

	// 난수(랜덤)
	srand(time(nullptr));


	for (int i = 0; i < 10; ++i)
	{
		int iRand = rand() % 100 + 1; // 1~100 사이
		PushBack(&s1, iRand);
	}

	printf("정렬 전\n");
	for (int i = 0; i < s1.iCount; ++i)
	{
		
		printf("%d\n", s1.pInt[i]);
	}

	Sort(&s1);
	// 함수포인터: call back 함수 같은 것을 만들어서 향후에 기능이 추가되어도 반영할 수 있도록 사용하는 경우가 많음. 또는 분기에 따라 호출하는 함수가 다른 경우
	Sort_p(&s1, &BubbleSort);

	printf("정렬 후\n");
	for (int i = 0; i < s1.iCount; ++i)
	{

		printf("%d\n", s1.pInt[i]);
	}

	ReleaseArr(&s1);



	// 연결형 리스트
	tLinkedList list = {};

	InitList(&list);

	PushBack(&list, 100);
	PushBack(&list, 200);
	PushBack(&list, 300);
	PushFront(&list, 500);

	ReleaseList(&list);

	return 0;

}