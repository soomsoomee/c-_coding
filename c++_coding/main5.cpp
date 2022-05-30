#include <iostream>
#include "Arr.h"
#include "CArr.h"
#include "CList.h"


struct tMy
{

};


class CMy
{
	// 접근 제한 지정자
	// private, protected(상속), public

private:
	int m_i;
	int m_j;
	float m_f;

public:
	// c.mi로 접근해서 바꿀 수는 없지만 c.SetInt 사용해서 바꿀 수는 있다. 
	void SetInt(int i)
	{
		// c 스타일에서는 어느 객체에 적용할 것인지 포인터 인자를 넣어줘야함. 
		// 전용함수를 사용하는 경우, 객체를 통해서만 함수가 실행되기 때문에 직접 적지 않아도 객체 주소가 들어온다. 
		// this-> m_i = i; 와 동일
		m_i = i;
	}

	// 대입 연산자: 자동으로 생성되지만 직접 구현해본다면 다음과 같다. 
	// 연산자 오버로딩
	CMy& operator = (const CMy& _Other)
	{
		m_i = _Other.m_i;
		m_f = _Other.m_f;

		return *this; // 역참조 해서 원본 가지고오고 참조해서 반환한다. 
	}


// 생성자, 소멸자 직접 만들지 않더라도 자동으로 만들어진다. 디폴트 생성자, 디폴트 소멸자가 컴파일 과정에서 생긴다.
// 컴파일러가 객체 생성할 때 생성자 실행하고, 소멸할 때 소멸자 실행하는 규칙을 가지는 것임. 
public:
	// 생성자: 객체가 만들어질 때 자동으로 호출된다. class 이름과 동일. 
	// 이니셜라이저
	CMy() : m_i(100), m_f(0.f) // 객체 생성과 동시에 실행
	{
		m_j = 100; // 객체가 생성된 후 실행
	}

	// 소멸자: 객체 없어질 때 실행하는 함수
	~CMy()
	{

	}

};

class CTest
{
private:
	int a;

public:
	CTest()
		: a(10)
	{

	}
};


template<typename T>
T Add(T a, T b)
{
	return a + b;
}



int main()
{
	// C++ 클래스의 특징
	
	// 접근 제한 지정자
	// 클래스 내의 멤버 변수, 멤버 함수의 접근 레벨 지정
	
	// 생성자, 소멸자
	// 객체 생성, 소멸시 자동으로 호출
	// 직접 만들지 않으면 기본 생성자, 기본 소멸자가 만들어짐.

	// 멤버 함수
	// 해당 클래스가 사용하는 전용 함수.
	// 해당 클래스의 객체가 필요함. (구조체로는 실행할 수 없음.)
	// 멤버 함수를 객체를 통해서 호출하면, 해당 객체의 주소가 this 포인터로 전달된다. 


	// 레퍼런스
	// 자료형* 변수명; : 포인터 변수 선언
	// *포인터변수; : 포인터로 주소 역참조
	// &변수; : 변수의 주소값
	// 자료형& 변수명; : 레퍼런스 변수 선언
	//
	// c++에 추가된 기능
	// 포인터와 유사
	// 원본을 참조한다.
	// 참조변수를 통해서 직접적으로 원본을 수정할 수 있다. 

	int a = 10;
	int* const p = &a;
	*p = 100;

	// 컴파일러 입장에서는 포인터와 동일함. c++에 추가된 기능. 
	// iRef는 다른 것을 참조할 수 없음. 역참조 연산 할 필요 없이 원본을 바꿀 수 있다. 
	int& iRef = a;
	iRef = 100;

	const int& iRefConst = a;
	// iRefConst = 10; -> 상수화 하면 원본 데이터 수정 불가능. 

	tArr arr = {};
	InitArr(&arr);
	PushBack(&arr, 10);

	// arr.iCount=100 이라고 해서 데이터 개수가 100이 되지는 않음. 밖에서 건드리면 안됨. 

	ReleaseArr(&arr);

	// c는 지역변수이므로 main 함수 종료될 때 사라진다. 
	CMy c;
	c.SetInt(15);

	CMy c2;
	CMy c3;
	// 대임 실행시 대입 연산자가 실행된다. c2가 대입 연산자를 호출하므로 this에는 c2가 들어간다. _Other은 c3.
	c = c2 = c3; // 뒤에서 부터 실행된다. c2=c3 실행되고 c=c2가 실행됨. 반환하는게 있어야 가능하다. c2(=this)를 반환해야함. 


	// 구조체 ---> 클래스


	// 객체지향 언어 특징
	// 1. 캡슐화
	// 기능을 수행하기 위해 필요한 멤버 선언, 묶음, 은닉성
	// 멤버 함수들


	// 2. 상속

	// 3. 다형성

	// 4. 추상화

	// 구조체 버전 가변 배열 ---> 클래스 버전
	

	// c++ 동적할당 new, delete
	// malloc으로 사용하는 경울 포인터를 사용해서 어떻게 사용할지를 지정해야 하지만, new는 자료형을 받아서 따로 지정할 필요 없음. 
	CTest* pTest = new CTest;
	// 어떤 객체를 가리키는 포인터인지 확인해서 소멸자 수행하도록 함. 
	delete pTest;

	// CArr 예시
	/*tArr arr = {};
	InitArr(&arr);

	PushBack(&arr, 10);
	PushBack(&arr, 20);
	PushBack(&arr, 30);

	ReleaseArr(&arr);*/


	CArr<int> carr;
	
	carr.push_back(10);
	carr.push_back(20);
	carr.push_back(30);

	// 지역변수라서 메인 함수 호출 시 소멸자 자동 실행되므로 메모리 해제 따로 할 필요 없음. 


	// 반환 타입을 레퍼런스로 하면 원본 데이터와 동일시 되어 값을 바꿀 수 있다. 
	int iData = carr[1];
	carr[1] = 100;


	// 함수 템플릿

	// 자료형에 따라 비슷한 함수를 여러개 정의해야 하는 경우 
	//int Add(int a, int b)
	//{
	//	return a + b;
	//}

	//float Add(float a, float b)
	//{
	//	return a + b;
	//}

	// 템플릿만 정의하고 사용하지 않으면 함수가 생성되지 않음. 템플릿은 그냥 틀.
	int i = Add<int>(10, 20); // int 명시하지 않아도 입력, 반환 타입 보고 컴파일러가 적용하긴 함. 


	// CList 예시
	CList<float> list;

	for (int i = 0; i < 4; ++i)
	{
		list.push_back(i);
	}

	return 0;
}