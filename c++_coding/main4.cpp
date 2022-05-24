# include <iostream>
# include <time.h>

# include "Arr.h"
# include "LinkedList.h"


// ���Ḯ��Ʈ�� �����迭�� ���� ������ ����. �� �տ� �߰��� ��, �����迭�� �����ؼ� �ڷ� �о�ִ� ������ �ʿ��ѵ�, ���Ḯ��Ʈ�� ���� ���Ḹ ���� ���� �����ϸ� �ȴ�.
// �����迭�� ���Ḯ��Ʈ�� ���� ������ �д� �ð��� ª��. ���� �ּ� + ���ϴ� ��ġ ��� �ϸ� ���� ����. ���Ḯ��Ʈ�� ��� ��带 ���ľ���. 


// �����迭 �ƴϾ ��� ������ �Լ�
void BubbleSort(int* _pData, int _iCount)
{
	// �����Ͱ� 1�� ���ϸ� �������� ����. 
	if (_iCount <= 1)
		return;
	// �������� ����

	while (true) // ��ü �� ���ĵ� �� ���� �ݺ�
	{
		bool bFinish = true;

		// iCount - 1��ŭ ���Ѵ�. 
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


	// ���� �迭
	tArr s1 = {};
	tArr s2 = {};
	tArr s3 = {};

	// �����Լ��� ����� �� ��ü�� ����������, heap memory�� �������� ����. 
	InitArr(&s1);

	// ����(����)
	srand(time(nullptr));


	for (int i = 0; i < 10; ++i)
	{
		int iRand = rand() % 100 + 1; // 1~100 ����
		PushBack(&s1, iRand);
	}

	printf("���� ��\n");
	for (int i = 0; i < s1.iCount; ++i)
	{
		
		printf("%d\n", s1.pInt[i]);
	}

	Sort(&s1);
	// �Լ�������: call back �Լ� ���� ���� ���� ���Ŀ� ����� �߰��Ǿ �ݿ��� �� �ֵ��� ����ϴ� ��찡 ����. �Ǵ� �б⿡ ���� ȣ���ϴ� �Լ��� �ٸ� ���
	Sort_p(&s1, &BubbleSort);

	printf("���� ��\n");
	for (int i = 0; i < s1.iCount; ++i)
	{

		printf("%d\n", s1.pInt[i]);
	}

	ReleaseArr(&s1);



	// ������ ����Ʈ
	tLinkedList list = {};

	InitList(&list);

	PushBack(&list, 100);
	PushBack(&list, 200);
	PushBack(&list, 300);
	PushFront(&list, 500);

	ReleaseList(&list);

	return 0;

}