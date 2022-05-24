#pragma once

typedef struct _tagArr
{
	int*    pInt;
	int     iCount;
	int     iMaxCount;

}tArr;


// 배열 초기화 함수
void InitArr(tArr* _pArr);


// 데이터 추가 함수
void PushBack(tArr* _pArr, int _iData);


// Release 함수는 main에서 사용할 필요 없으므로 헤더파일에 넣을 필요 없음. 


// 배열 메모리 해제 함수
void ReleaseArr(tArr* _pArr);


// 데이터 정렬 함수
void Sort(tArr* _pArr);
void Sort_p(tArr* _pArr, void(*SortFunc)(int*, int));
