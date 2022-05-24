# include <stdio.h>
# include "func.h"
# include "common.h"
# include <wchar.h>
# include <assert.h>

// 변수의 종류 -> 변수는 스택 또는 데이터 영역을 사용한다. 
// 1. 지역변수 -> 스택 영역
// 2. 전역변수 -> 데이터 영역
// 3. 정적변수(static) -> 데이터 영역
// 4. 외부변수(extern) -> 데이터 영역


// 메모리 영역
// 1. 스택 영역
// 2. 데이터 영역
// 3. 읽기 전용(코드, ROM)%%%
// 4. 힙 영역


// 전역변수
int g_i = 0; // Data 영역
// Data 영역 특징
// 프로그램 시작 시 생성
// 프로그램 종료 시 해제 


// 리턴하는게 없을 때는 void라고 한다. 
int Test()
{
	int i = 0;
	++i;
	// 정적 변수가 함수 안에서 선언된 경우 data영역에 생성된다. 함수 호출 스택이 아니라 data영역에 존재.
	// 함수의 호출 및 종료에 따라서 생성, 삭제되지는 않고, 다른 함수에서 사용할 수 없음. -> 사용 예시: 
	static int iStatic = 0; // 한번 초기화 된 다음에는 이 부분 건너뛴다. 
	++g_i;
	++iStatic;
	return iStatic;
}

// 정적 변수
// 선언된 곳에서 고정된 상태로 존재 -> main2.cpp 메모리에만 있다.
// func.cpp에 같은 이름으로 정의되더라도 충돌되지 않는다. 
// 이미 include common.h에서 불러왔기 때문에 다시 정의하지 않는다. 
// static int g_iStatic = 0;

int g_iExtern = 0;

int Output(const int* pI)
{

	int i = *pI; // 값을 참고해서 사용할 수는 있지만 변경은 불가능 

	return 0;
}


// 문자열 길이 구하는 함수 만들기
unsigned int GetLength(const wchar_t* _pStr)
{
	// 문자 개수 체크 용도
	int i = 0;
	// 문자 마지막에는 0이 있음.
	while (0 != _pStr[i])
	{	
		// 포인터는 데이터 타입 byte 만큼 증가한다. 

		wchar_t c = _pStr[i];
		 
		++i;
	}
	return i;
}


// 함수 오버 로딩
// 같은 이름을 가진 함수가 여러개 있는 경우 인자 개수, 타입에 따라서 맞는 함수가 불러와진다. 

// 문자열 이어 붙이는 함수 만들기
void StrCat(wchar_t* _pDest, unsigned int _iBufferSize, const wchar_t* _pSrc)
{
	// 예외처리
	// 이어붙인 최종 문자열의 길이가 원본 저장 공간을 넘어서는 경우
	int iDestLen = GetLength(_pDest);
	int iSrcLen = GetLength(_pSrc);
	if (_iBufferSize < iDestLen + iSrcLen + 1) // Null 문자 공간까지 계산

	{
		assert(nullptr);
	}

	// 문자열 이어 붙이기
	// 1. Dest 문자열의 끝을 확인(문자열이 이어 붙을 시작 위치)
	iDestLen; //Dest 문자의 끝 인덱스
	// 2. 반복적으로 Src 문자열을 Dest 끝 위치에 복사하기
	// 3. Src 문자열의 끝을 만나면 반복 종료
	for (int i = 0; i < iSrcLen + 1; ++i) // null 문자까지 더하도록 
	{
		_pDest[iDestLen + i] = _pSrc[i];
	}
}


int main()
{
	g_iStatic = 100;
	g_iExtern = 500;
	// 지역변수와 전역 변수의 차이: 함수를 반복해서 호출할 때 지역변수는 없어졌다 새로 생기지만 전역변수는 사라지지 않고 누적된다.
	// 전역변수는 함수 안, 밖에서 호출할 수 있다. main함수 밖 메모리 영역에 존재하기 때문이다. -> 외부에서 건드리지 않기를 원할 때 사옹 가능. 

	Test();
	Test();
	Test();
	g_i = 0;
	int iCall = Test();
	// iCall은 외부 함수에서 건드리지 못한다. 
	printf("%d, %d\n", g_i, iCall);
	int data = Add(3, 5);

	// 포인터 변수 
	// 주소를 저장하는 변수 -> *이 붙으면 포인터를 의미한다. 
	// 자료형(해당 포인터에게 전달된 주소를 해석하는 단위)* + 변수명 
	// int 변수의 주소만 받는다. 다른 것이 들어오면 안된다. int 변수의 사이즈인 4바이트로 접근한다. 다른 자료형을 가리키게 하면 오류가 발생한다. float을 가리키게 하면 가서 int로 읽는다. 
	int i = 100;
	int* pInt = &i;
	char* pChar = nullptr;
	short* pShort = nullptr;
	// 주소로 접근
	// 주소의 단위: 바이트
	// 플랫폼에 따라 포인터의 크기가 달라진다. -> 32bit: 한 번에 4byte 단위로 처리한다.(2^32 -> 약 4GB)
	// 64bit 플랫폼에서는 한 번에 처리할 수 있는 단위가 8byte 이기 때문에 주소도 8byte이다. 
	(*pInt) = 100; // i에 100이 들어간다. 
	// pInt는 int* 변수이기 때문에, 가리키는 곳을 int로 해석한다.
	// 따라서 주소값을 1 증가하는 의미는 다음 int 위치로 접근하기 위해서 sizeof(int) 단위로 증가하게 된다. 
	pInt += 1;

	// 포인터와 배열
	// 배열의 특징
	// 1. 메모리가 연속적인 구조이다.
	// 2. 배열의 이름은 배열의 시작 주소이다.
	int iArr[10] = {};

	// int 단위로 접근 
	*(iArr + 0) = 20; // iArr[0] = 20;
 	*(iArr + 1) = 10; // iArr[1] = 10;

	// const

	// l-value: 변수
	// r-value: 상수
	const int cint = 100;
	// 상수화: 값이 바뀔 수 없는 상태. 문법적으로 설정한거니까 물리적으로 바뀔 수 없다는 의미는 아님. 포인터로 값 바꿀 수 있음.
	cint;

	// const와 포인터: 포인터는 가리키는 곳을 바꾸던지, 가리키는 곳의 값을 바꿀 수 있다. 일반 변수의 상수화와 다르다. 
	int x = 0;
	int* pIntx = &x;

	*pIntx = 1; // 가리키는 곳의 값을 바꾸기
	pIntx = nullptr; //가리키는 곳을 바꾸기

	const int* pConstInt = &x; // 포인터가 가리키는 원본이 상수화됨. 다른 변수를 가리키도록 바꾸는 것은 가능
	int* const pIntConst = &x; // 포인터가 다른 변수를 가리키도록 바꿀 수 없음. 
	// 초기화 시 가리킨 대상만 가리킴. 가리키는 원본을 수정할 수 없음. 
  
	const int* const pConstIntConst = nullptr;


	{
		int a = 0;
		const int* pInt = &a; // pointer의 기능을 제한한거지 a 자체와는 관련이 없다.
  		// *pInt = 100
		int* p = &a; // 별개의 포인터를 사용하면 a 값을 변경할 수 있다. 
		*p = 100;
	}

	// const pointer 예시
	// 만약에 Output함수가 엄청 큰 값을 받아서 사용한다면, 함수 호출 시 main 함수 메모리 스택과 Output 함수 메모리 스택에 중복적으로 큰 데이터가 들어간다.
	// 값을 직접 넘기지 않고, 포인터를 통해 주소를 전달하면 더 효율적이다. 대신 이 값을 변화시키지 않도록 하기 위해 constant pointer를 사용한다. 
	// 문법적으로 못바꾼다는거지 물리적으로 바꾸지 못하는 것은 아니다. 코딩한 사람의 의도를 반영하는 것. 
	Output(&x);

	// void pointer : 주소에 가서 어떤 자료형으로 읽을지 결정되지 않은 포인터
	// 1. 원본의 자료형을 정하지 않음. 
	// 2. 어떠한 타입의 변수의 주소든 다 저장 가능
	// 3. 역참조 불가능. *pVoid 불가능. 
	// 4. 주소 연산 불가능. pVoid+1 불가능

	void* pVoid = nullptr;
	{
		int a = 0;
		float f = 0.f;
		double d = 0.;
		long long ll = 0;

		pVoid = &a;
		pVoid = &f;
		pVoid = &d;
		pVoid = &ll;
	}

	// 문자
	// 문자가 끝났다는 것을 알려주기 위해 null 문자를 사용한다. (숫자 0에 대응)
	char c_ = 0;
	wchar_t wc_ = 49; // ascii 코드로 '1'에 대응함. 문자 1과 숫자 1은 다르다.
	short s = 49; // 그냥 숫자.
	// 1 byte로는 127개의 문자를 나타낼 수 있음. 7bit 사용 가능. 2 byte로 하면 더 많은 문자에 매핑시킬 수 있음. 
	// char(1)-> 문자에 따라서 가변 길이로 대응한다, wchar(2)
	char c = 'a';
	wchar_t wc = L'a';

	// 문자자료형은 다음과 같은 배열 초기화 가능하다. 
	char szChar[10] = "abcdef";
	wchar_t szWChar[10] = L"abcdef"; // 문자열 맨 마지막에는 항상 1칸이 더 필요하다. {97, 98, 99, 100, 101, 102}와 동일하다. -> 문자열에 배열을 넣은 것
	// 문자열이 애초에 const 타입이라서 const 포인터로 설정해야함. 문법적으로 read only 메모리 수정하는 것을 방어한다고 볼 수 있음. 
	const wchar_t* pChar_ = L"abcdef"; // 문자열이 주소값을 반환하기 때문에 포인터에 할당 가능. 문자열의 시작 주소를 받아옴. -> 문자열 자체의 주소를 가리킴. 수정할 수 없는 const 포인터로 함. 

	// 배열의 두번쨰 칸에 z를 넣는다.
	szWChar[1] = 'z';
	// 문자열의 두번쨰 값을 바꾼다는 의미 코드에 적혀있는 문자열을 수정하라는 의미. -> read only 메모리기 때문에 바꿀 수 없다. 
	//pChar_[1] = 'z';

	// 한글은 1byte로 표현할 수 없어서 2byte로 사용한다. -> 멀티바이트 시스템은 잘 안쓰인다. wchar를 쓰는게 일반적이다. 
	char szTest[10] = "abc한글"; // 한, 글은 각각 2byte씩 사용함. 2byte에서 '한'은 54620에 대응하는데, 1byte 관점에서 8bit씩 끊어읽으면 (-57, -47)이 됨. 
	wchar_t szTestW[10] = L"abc한글"; // 모든 문자가 2byte씩 사용함

	{
		wchar_t szName[10] = L"Raimond"; // 문자열은 읽기 전용 메모리에 존재 

		// 문자의 길이 확인하기. 길이를 확인하기 위해 문자의 주소를 전달하는데 값을 바꾸지 못하도록 const wchar*를 전달. 

		int iLen = wcslen(szName);

		int iLen2 = GetLength(szName);
	}

	{

		// 문자열 이어 붙이기

		wchar_t szString[100] = L"abc";

		wcscat_s(szString, 100, L"def");
		
	}

	wchar_t szString[100] = L"abc";
	StrCat(szString, 10, L"def");


	return 0;
}
