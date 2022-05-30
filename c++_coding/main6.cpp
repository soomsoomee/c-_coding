#include <iostream>

// 가변 배열
# include <vector>
// 연결형 리스트
# include <list>


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
	// 객체 없이 호출 가능(정적 멤버 함수)
	static void MemberFunc()
	{

	}
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

	list<int> listInt;
	listInt.push_back(10);
	listInt.push_front(20);
	listInt.size();
	// 리스트는 인덱스 접근 오퍼레이터 제공하지 않음. (연속된 메모리가 아님.)

	// iterator(Inner Class)
	list<int>::iterator iter = listInt.begin(); // iterator가 list의 시작 노드를 가리키도록 함. 
	// 포인터 같은 느낌을 내기 위해 * 연산자 오버로딩. 가리키는 노드의 데이터 값을 보여주는 일을 하도록 구현되어있을 것. 
	int iData = *iter;

	return 0;
}