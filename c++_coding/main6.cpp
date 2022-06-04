#include <iostream>

// ���� �迭
# include <vector>
// ������ ����Ʈ
# include <list>

#include "CArr.h"
#include "CList.h"


namespace MYSPACE
{
	int g_init; // ��������
}

namespace OTHERSPACE
{
	int g_init;
}

// namespace ������ �ʾƵ� ��� ����. namespace ����� ����ϹǷ� ���������� ����. ���������� �����ϴ� �� ����
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
	// ��ü ���� ȣ�� ����(���� ��� �Լ�)
	static void MemberFunc()
	{

	};

	// class���� ���Կ�����, ���� �����ڰ� �ڵ����� �����ȴ�. 
	CTest& operator =(const CTest& _other)
	{
		m_i = _other.m_i;
		return *this;
	};

	// ���� ������ �����ڰ� 1�� �̻� ������ �ڵ����� �����ڸ� ��������� �ʴ´�. 
	// �⺻ �����ڸ� ����ϰ� ���� ���� �ǵ��� ���� �� ����. (������ ���ڸ� �޵���)
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
	// ������ �����ε�
	CMyOstream operator << (int _iData)
	{
		printf("%d", _iData);
		// �ڱ� �ڽ��� ��ȯ�ؾ� �����ڸ� �����ؼ� �� �� ����. 
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
		// �ڱ� �ڽ��� ��ȯ�ؾ� �����ڸ� �����ؼ� �� �� ����. 
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
	cout << "�ȳ�" << 10 << std::endl;
	wcout << L"�ȳ�" << 10;

	mycout << 10 << 20 << 30 << MyEndL;
	mycout << L"�ѱ�";
	

	// scanf
	int iInput = 0;
	cin >> iInput;

	int a = 0;
	mycout >> a;

	CTest::MemberFunc();
	MYSPACE::g_init = 0;
	// �ٸ� namespace�� ���������� �����Ͽ� ���� �̸����� �����ص� ���� ����.
	OTHERSPACE::g_init = 0;



	vector<int> vecInt;
	// ���� �迭�� push_front ��� ����(push front�ҰŸ� ���Ḯ��Ʈ�� ȿ����)
	vecInt.push_back(10);
	vecInt.push_back(20);
	vecInt[0] = 100;
	vecInt.at(1); // vecInt[1]
	vecInt.data(); // �������� �����ּ� ��ȯ
	vecInt.size(); // ������ ����
	vecInt.capacity(); // ���� �������� �������� ���� ��������

	// ���͸� ��ȸ�Ϸ���
	for (size_t i = 0; i< vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	// begin �Լ��� iterator�� ��ȯ�ϱ� ������ iterator�� �Ҵ� ����. 
	vector<int>::iterator veciter = vecInt.begin();
	*veciter = 1000;

	list<int> listInt;
	listInt.push_back(10);
	listInt.push_front(20);
	listInt.size();
	// ����Ʈ�� �ε��� ���� ���۷����� �������� ����. (���ӵ� �޸𸮰� �ƴ�.)

	vecInt.erase(veciter);
	


	// iterator(Inner Class)
	// vector, list � ���������� iterator�� �����Ǿ� �ִ�. 
	// ���� ������ �ٸ������� ����� ���忡���� ����ϰ� ��� ����. 
	list<int>::iterator iter = listInt.begin(); // iterator�� list�� ���� ��带 ����Ű���� ��. 
	// ������ ���� ������ ���� ���� * ������ �����ε�. ����Ű�� ����� ������ ���� �����ִ� ���� �ϵ��� �����Ǿ����� ��. 
	int iData = *iter;
	++iter; // ���� ������ �����ϱ�. 
	iData = *iter; 

	listInt.erase(iter);

	// listInt.end()�� ��+1�� �ǹ���. �׷��� �Ʒ� �������� ������ �����ͱ��� ��� ����. 
	for (iter = listInt.begin() ; iter != listInt.end(); ++iter)
	{
		cout << *iter << endl;
	}

	

	// iterator ���� �����غ���
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



	// Ŭ���� ������ �ڵ� �����Ǵ� �Լ�: ���Կ�����, ���� ������
	CTest t1;
	t1.m_i = 100;
		
	CTest t2;
	t1 = t2;

	CTest t3(t1); // CTest t3 = t1 �̶�� �ϸ� �����Ϸ��� ���� �����ڷ� ����. 


	// vector::erase

	vector<int> vecInt2;

	vecInt2.push_back(100);
	vecInt2.push_back(200);
	vecInt2.push_back(300);
	vecInt2.push_back(400);
	vecInt2.push_back(500);

	vector<int>::iterator veciter2 = vecInt2.begin();
	// vecInt2.erase(veciter2); -> �ٽ� �޾ƿ��� ������ ����� �� ���� iterator�� �ȴ�. 

	// int i = *veciter; -> �̹� ������ ���� ������ �ϹǷ� ���� �߻�. ���ϰ��� �޾ƿͼ� ����ؾ���. 
	// ������ �̷���� iterator�� ���̻� ����� �� ���ٰ� ��. 
	veciter2 = vecInt2.erase(veciter2); 
	int i = *veciter2;
	vecInt2.clear();

	// 1~10�� ���Ϳ� �Է�
	for (int i = 0; i < 10; ++i)
	{
		vecInt2.push_back(i + 1);
	}

	// ¦���� ����
	veciter2 = vecInt2.begin();
	for (; veciter2 != vecInt2.end();)
	{
		if (*veciter2 % 2 == 0)
		{
			// ����
			veciter2 = vecInt2.erase(veciter2); // ���� ���� ����Ű�� ��. 
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