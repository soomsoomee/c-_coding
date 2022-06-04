#include <iostream>

// 가변 배열
# include <vector>
// 연결형 리스트
# include <list>

#include "CArr.h"
#include "CList.h"


namespace MYSPACE
{
	int g_init; // 전역변수
}

namespace OTHERSPACE
{
	int g_init;
}

// namespace 붙이지 않아도 사용 가능. namespace 기능을 상실하므로 권장하지는 않음. 개별적으로 해제하는 게 나음
// using namespace std;
using std::cout;
using std::wcout;
using std::cin;
using std::endl;

using std::vector;
using std::list;


class CTest
{
public:
	int    m_i;
public:
	// 객체 없이 호출 가능(정적 멤버 함수)
	static void MemberFunc()
	{

	};

	// class에서 대입연산자, 복사 생성자가 자동으로 생성된다. 
	CTest& operator =(const CTest& _other)
	{
		m_i = _other.m_i;
		return *this;
	};

	// 직접 구현한 생성자가 1개 이상 있으면 자동으로 생성자를 만들어주지 않는다. 
	// 기본 생성자를 사용하고 싶지 않은 의도가 있을 수 있음. (무조건 인자를 받도록)
	CTest()
		:m_i(0)
	{

	};

	CTest(const CTest& _other)
		:m_i(_other.m_i)
	{

	};
};



class CMyOstream
{
public:
	// 연산자 오버로딩
	CMyOstream operator << (int _iData)
	{
		printf("%d", _iData);
		// 자기 자신을 반환해야 연산자를 연속해서 쓸 수 있음. 
		return *this;
	}

	CMyOstream& operator << (const wchar_t* _pString)
	{
		wprintf(L"%s",_pString);
		return *this;
	}

	CMyOstream& operator << (void(*_pFunc)(void))
	{
		_pFunc();
		return *this;
	}

	CMyOstream operator >> (int& _iData)
	{
		scanf_s("%d", &_iData);
		// 자기 자신을 반환해야 연산자를 연속해서 쓸 수 있음. 
		return *this;
	}
};

CMyOstream mycout;


void MyEndL()
{
	wprintf(L"\n");
}



int main()


{

	setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");

	// C printf
	cout << "안녕" << 10 << std::endl;
	wcout << L"안녕" << 10;

	mycout << 10 << 20 << 30 << MyEndL;
	mycout << L"한글";
	

	// scanf
	int iInput = 0;
	cin >> iInput;

	int a = 0;
	mycout >> a;

	CTest::MemberFunc();
	MYSPACE::g_init = 0;
	// 다른 namespace에 전역변수를 지정하여 같은 이름으로 선언해도 문제 없음.
	OTHERSPACE::g_init = 0;



	vector<int> vecInt;
	// 가변 배열은 push_front 기능 없음(push front할거면 연결리스트가 효율적)
	vecInt.push_back(10);
	vecInt.push_back(20);
	vecInt[0] = 100;
	vecInt.at(1); // vecInt[1]
	vecInt.data(); // 데이터의 시작주소 반환
	vecInt.size(); // 데이터 길이
	vecInt.capacity(); // 현재 기준으로 어디까지하 혀용 범위인지

	// 벡터를 순회하려면
	for (size_t i = 0; i< vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	// begin 함수가 iterator를 반환하기 때문에 iterator에 할당 가능. 
	vector<int>::iterator veciter = vecInt.begin();
	*veciter = 1000;

	list<int> listInt;
	listInt.push_back(10);
	listInt.push_front(20);
	listInt.size();
	// 리스트는 인덱스 접근 오퍼레이터 제공하지 않음. (연속된 메모리가 아님.)

	vecInt.erase(veciter);
	


	// iterator(Inner Class)
	// vector, list 등에 공통적으로 iterator가 구현되어 있다. 
	// 내부 구현은 다르겠지만 사용자 입장에서는 비슷하게 사용 가능. 
	list<int>::iterator iter = listInt.begin(); // iterator가 list의 시작 노드를 가리키도록 함. 
	// 포인터 같은 느낌을 내기 위해 * 연산자 오버로딩. 가리키는 노드의 데이터 값을 보여주는 일을 하도록 구현되어있을 것. 
	int iData = *iter;
	++iter; // 다음 데이터 접근하기. 
	iData = *iter; 

	listInt.erase(iter);

	// listInt.end()는 끝+1을 의미함. 그래서 아래 조건으로 마지막 데이터까지 출력 가능. 
	for (iter = listInt.begin() ; iter != listInt.end(); ++iter)
	{
		cout << *iter << endl;
	}

	

	// iterator 직접 구현해보기
	CArr<int> myvector;

	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);
	myvector.push_back(4);
	myvector.push_back(5);

	CArr<int>::iterator myiter = myvector.begin();

	for (; myiter != myvector.end(); ++myiter)
	{
		cout << *myiter << endl;
	}

	myiter = myvector.begin();
	int iData_before = *(++myiter); //iData=2
	myiter = myvector.begin();
	int iData_after = *(myiter++); //iData=1



	// 클래스 생성시 자동 생성되는 함수: 대입연산자, 복사 생성자
	CTest t1;
	t1.m_i = 100;
		
	CTest t2;
	t1 = t2;

	CTest t3(t1); // CTest t3 = t1 이라고 하면 컴파일러가 복사 생성자로 실행. 


	// vector::erase

	vector<int> vecInt2;

	vecInt2.push_back(100);
	vecInt2.push_back(200);
	vecInt2.push_back(300);
	vecInt2.push_back(400);
	vecInt2.push_back(500);

	vector<int>::iterator veciter2 = vecInt2.begin();
	// vecInt2.erase(veciter2); -> 다시 받아오지 않으면 사용할 수 없는 iterator가 된다. 

	// int i = *veciter; -> 이미 삭제된 곳을 역참조 하므로 오류 발생. 리턴값을 받아와서 사용해야함. 
	// 삭제가 이루어진 iterator는 더이상 사용할 수 없다고 봄. 
	veciter2 = vecInt2.erase(veciter2); 
	int i = *veciter2;
	vecInt2.clear();

	// 1~10을 벡터에 입력
	for (int i = 0; i < 10; ++i)
	{
		vecInt2.push_back(i + 1);
	}

	// 짝수만 제거
	veciter2 = vecInt2.begin();
	for (; veciter2 != vecInt2.end();)
	{
		if (*veciter2 % 2 == 0)
		{
			// 제거
			veciter2 = vecInt2.erase(veciter2); // 다음 값을 가리키게 됨. 
		}
		else
		{
			++veciter2;
		}
	}

	for (int i = 0; i < vecInt2.size(); ++i)
	{
		cout << vecInt2[i] << endl;
	}


	myiter = myvector.begin();
	myiter = myvector.erase(myiter);
	myiter = myvector.begin();
	for (; myiter != myvector.end(); ++myiter)
	{
		cout << *myiter << endl;
	}

	// list iterator

	CList<int> mylist;

	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);
	mylist.push_back(400);
	mylist.push_back(500);

	CList<int>::iterator listiter = mylist.begin();
	i = *listiter;
	*listiter = 150;
	++listiter;

	listiter = mylist.insert(listiter, 777);

	for (listiter = mylist.begin(); listiter != mylist.end(); ++listiter)
	{
		cout << *listiter << endl;
	}


	return 0;
}