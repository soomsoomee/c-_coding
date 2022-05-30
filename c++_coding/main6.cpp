#include <iostream>

// ���� �迭
# include <vector>
// ������ ����Ʈ
# include <list>


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
	// ��ü ���� ȣ�� ����(���� ��� �Լ�)
	static void MemberFunc()
	{

	}
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

	list<int> listInt;
	listInt.push_back(10);
	listInt.push_front(20);
	listInt.size();
	// ����Ʈ�� �ε��� ���� ���۷����� �������� ����. (���ӵ� �޸𸮰� �ƴ�.)

	// iterator(Inner Class)
	list<int>::iterator iter = listInt.begin(); // iterator�� list�� ���� ��带 ����Ű���� ��. 
	// ������ ���� ������ ���� ���� * ������ �����ε�. ����Ű�� ����� ������ ���� �����ִ� ���� �ϵ��� �����Ǿ����� ��. 
	int iData = *iter;

	return 0;
}