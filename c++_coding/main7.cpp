#include <iostream>

#include <map>
#include <set>

#include <string>


using std::cout;
using std::wcout;
using std::endl;

using std::map;
using std::make_pair;

using std::set;

// 문자열클래스
using std::wstring;

#define MAN 1
#define WOMAN 2

struct tStdInfo
{
	wchar_t szName[20];
	unsigned char age;
	unsigned char gender;

	tStdInfo()
		: szName{}
		, age(0)
		, gender(0)
	{
	}

	tStdInfo(const wchar_t* _pName, unsigned char _age, unsigned char _gender)
		: szName{}
		, age(_age)
		, gender(_gender)
	{
		wcscpy_s(szName, _pName); //문자열 복사함수
	}
};


class MyClass
{
private:
	int a;

public:
	bool operator < (const MyClass& _other) const
	{
		if (a < _other.a)
			return true;
		else
			return false;
	}

};



int main()
{
	// 트리, 그래프
	// 그래프: node, edge로 이루어진 자료구조
	// 트리: 순회할 수 없는 그래프. 계층 관계 표현에 유리.
	// 이진트리 : 자식의 개수가 2개 이하(규칙)
	
	// 트리 관련 개념
	// level: 높이
	// root node: 부모가 존재하지 않는 노드(꼭대기 노드)
	// leaf node: 자식이 존재하지 않는 노드(마지막 노드)

	// 완전이진트리: 자식을 모두 채우는 이진트리 -> 주로 배열로 구현
	// 인덱스를 k라고 하면, 2k+1, 2k+2를 자식으로 가진다. (반대로 부모노드도 나눈 몫을 통해 찾을 수 있음)


	// 이진탐색트리: 탐색을 위한 이진트리(binary search tree)
	// 이진탐색: 탐색 대상 숫자를 순서대로 놓고 절반으로 나눠서 탐색해가는 방법
	// 1. 데이터가 정렬되어 있어야 한다.
	// 2. 해결해야 되는 데이터의 크기를 절반으로 덜어나가면서 탐색한다. 
	// 최악의 경우 log2N (배열의 경우 최악이 N: 가장 마지막에 있는 경우)
	// 이진탐색트리는 이진탐색을 위해 데이터 추가시 더 작은 데이터는 왼쪽에, 더 큰 데이터는 오른쪽에 삽입한다.(정렬)
	// 데이터 입력 시 비교횟수도 O(logN) (vector나 list는 O(1))) -> 데이터 입력시 비용이 더 크지만 탐색할 때 유리

	// 트리의 순회: 이진탐색트리는 중위순회로 접근할 때 데이터가 정렬된 형태
	// 순회 방식 별 우선순위. 우선순위 먼저 방문. 
	// 중위순회(in order): 왼쪽자식-부모-오른쪽자식 -> 이진탐색트리의 iterator
	// 전위순회(pre order): 부모-왼쪽자식-오른쪽자식 
	// 후위순회(post order): 왼쪽자식-오른쪽자식-부모

	// 데이터가 순차적으로 입력되는 경우 이진탐색트리 손해. 한쪽으로 긴 형태. 절반씩 줄어드는 효과 없음.
	// 이진탐색트리 밸런스 좋을수록 탐색에 효율적. 
	// 실제로는 self balanced를 위한 기능을 추가해서 사용. (red black binary search tree)


	// =====요약======
	// 이진탐색
	// 1. 정렬되어 있는 데이터에 적용 가능
	

	// 이진탐색트리
	// 1. 이진탐색을 사용할 수 있게 고안된 이진트리
	// 2. 데이터 입력시 O(log(N)) 효율(self balance 기능까지 포함되면 더 느릴수도)
	// 3. 탐색 효율은 O(log(N))
	// 4. 트리의 모양이 밸런스가 유지되지 않으면 제대로된 검색 효율이 나오지 않는다. - 자가균형 기능 필요(AVL, Red/Black)

	setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");

	set<int> setInt; // 탐색을 위한 red black tree container라고 생각하면 됨.

	setInt.insert(100); // 데이터는 동적할당을 통해 힙메모리에 저장하고 객체는 root node를 가리키는 형태일 것.
	setInt.insert(50);
	setInt.insert(150);

	// map을 더 많이 사용함
	// 첫번쨰 인자가 key의 자료형, 두번째 인자가 노드에 속하는 값의 자료형. (탐색 시에는 key로 찾음.)
	// 예를 들어 학생 정보를 저장한다고 할 때, 학생 이름을 key로, 학생정보 객체를 value로 사용할 수 있음.
	map<const wchar_t*, tStdInfo> mapData;
	tStdInfo info1(L"홍길동", 18, MAN);
	tStdInfo info2(L"이지혜", 25, WOMAN);

	// make_pair: pair를 만드는 함수
	mapData.insert(make_pair(L"홍길동", info1));
	mapData.insert(make_pair(L"이지혜", info2));

	// find 대상이 존재하지 않는 경우 iterator는 end iterator
	map<const wchar_t*, tStdInfo>::iterator mapiter;
	mapiter = mapData.find(L"홍길동"); // return은 pair를 가리키는 iterator 형태
	// const wchar_t*를 key로 지정했기 때문에 문자열 자체가 아니라 문자열의 주소로 찾은 것.
	// wchar_t szFind[20] = L"이지혜"; 라고 변수를 받아서 mapData.find(szFind);하면 주소가 달라서 찾지 못함. 
	// 문자열로 비교하려면 문자열 클래스를 넣어야함. 

	

	// 찾지 못했다.
	if (mapiter == mapData.end())
	{
		wcout << L"데이터를 찾을 수 없다" << endl;
	}
	else
	{
		(*mapiter).first;
		(*mapiter).second;
		// 연산자 오버로딩을 통해 구현되어있음.
		wcout << L"이름" << mapiter->second.szName << endl;
		wcout << L"나이" << mapiter->second.age << endl;
		wcout << L"성별" ;


		if (MAN == mapiter->second.gender)
		{
			wcout << L"남자" << endl;
		}
	    else if (WOMAN == mapiter->second.gender)
		{
			wcout << L"여자" << endl;
		}
		else
		{
			wcout << L"알 수 없음" << endl;
		}
	
	}

	map<wstring, tStdInfo> mapStdInfo;

	wstring str;
	// 주소가 아니라 자체적으로 문자를 관리한다.(가변배열과 유사하게 데이터를 관리할 것. vector<wchar_t>)
	str = L"abcde";
	str += L"addstr";
	// c에서는 문자일 때 작은 따옴표, 문자열일 때 큰 따옴표 사용
	str[1] = L'c'; // 읽기 전용 메모리 영역이 아니므로 수정 가능

	wstring str2;

	if (str == str2) //연산자 오버로딩. 대소비교도 가능. -> key로 사용하면 탐색 가능
	{

	}

	// 만약 직접 만든 클래스를 key로 사용하려면 대소비교를 위한 연산자 오버로딩이 구현되어 있어야함. 
	map<MyClass, tStdInfo> mapMyClassStdInfo;


	return 0;
}