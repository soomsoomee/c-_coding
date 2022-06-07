#include <iostream>
#include "CBST.h"

using std::wcout;
using std::endl;


// ������: �����Ϸ��� ���ӵ� ���ڷ� �޾Ƶ��δ�.
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


// ��ó����: ������ ������ ����. CLASS_1�� �׳� 0�� ����. �����Ϸ��� CLASS_1�̶�� ������ ����. 
// enum: �����Ϸ��� TYPE_1�� �־��ٰ� ������. -> ������� �� ����. 
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

	(*bstiter).first; // tPair�� ��ȯ
	bstiter->first; // tPair�� �ּҸ� ��ȯ


	for (bstiter = bstint.begin(); bstiter != bstint.end(); ++bstiter)
	{
		wcout << bstiter->first << bstiter->second << endl;
	}

	CBST<int, int>::iterator bstiter2 = bstint.begin();
	bstiter2 = bstint.find(150);

	// �����ļ��ڸ� ����Ű�� iterator�� ����
	bstiter2 = bstint.erase(bstiter2);

	return 0;
}