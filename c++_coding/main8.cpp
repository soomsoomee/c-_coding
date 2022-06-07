#include <iostream>
#include "CBST.h"

using std::wcout;
using std::endl;


// 열거형: 컴파일러는 연속된 숫자로 받아들인다.
enum class MY_TYPE
{
	TYPE_1, // 0
	TYPE_2, // 1
	TYPE_3, // 2
	TYPE_5 = 100,
	TYPE_6, //101
};

enum class OTHER_TYPE
{
	TYPE_1,
	TYPE_2,
};


// 전처리기: 컴파일 이전에 실행. CLASS_1은 그냥 0과 같음. 컴파일러에 CLASS_1이라고 잡히지 않음. 
// enum: 컴파일러에 TYPE_1을 넣었다고 잡힌다. -> 디버깅할 때 편리함. 
#define CLASS_1 0
#define CLASS_2 1

int main()
{

	int a = (int)MY_TYPE::TYPE_3;


	CBST<int, int> bstint;

	bstint.insert(make_bstpair(100, 0)); //           100
	bstint.insert(make_bstpair(150, 0)); //     50            150
	bstint.insert(make_bstpair(50, 0)); //   25     75    125       175
	bstint.insert(make_bstpair(25, 0));
	bstint.insert(make_bstpair(75, 0));
	bstint.insert(make_bstpair(125, 0));
	bstint.insert(make_bstpair(175, 0));

	CBST<int, int>::iterator bstiter = bstint.begin();
	
	bstiter = bstint.find(150);

	(*bstiter).first; // tPair를 반환
	bstiter->first; // tPair의 주소를 반환


	for (bstiter = bstint.begin(); bstiter != bstint.end(); ++bstiter)
	{
		wcout << bstiter->first << bstiter->second << endl;
	}

	CBST<int, int>::iterator bstiter2 = bstint.begin();
	bstiter2 = bstint.find(150);

	// 중위후속자를 가리키는 iterator를 리턴
	bstiter2 = bstint.erase(bstiter2);

	return 0;
}