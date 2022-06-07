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

// ���ڿ�Ŭ����
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
		wcscpy_s(szName, _pName); //���ڿ� �����Լ�
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
	// Ʈ��, �׷���
	// �׷���: node, edge�� �̷���� �ڷᱸ��
	// Ʈ��: ��ȸ�� �� ���� �׷���. ���� ���� ǥ���� ����.
	// ����Ʈ�� : �ڽ��� ������ 2�� ����(��Ģ)
	
	// Ʈ�� ���� ����
	// level: ����
	// root node: �θ� �������� �ʴ� ���(����� ���)
	// leaf node: �ڽ��� �������� �ʴ� ���(������ ���)

	// ��������Ʈ��: �ڽ��� ��� ä��� ����Ʈ�� -> �ַ� �迭�� ����
	// �ε����� k��� �ϸ�, 2k+1, 2k+2�� �ڽ����� ������. (�ݴ�� �θ��嵵 ���� ���� ���� ã�� �� ����)


	// ����Ž��Ʈ��: Ž���� ���� ����Ʈ��(binary search tree)
	// ����Ž��: Ž�� ��� ���ڸ� ������� ���� �������� ������ Ž���ذ��� ���
	// 1. �����Ͱ� ���ĵǾ� �־�� �Ѵ�.
	// 2. �ذ��ؾ� �Ǵ� �������� ũ�⸦ �������� ������鼭 Ž���Ѵ�. 
	// �־��� ��� log2N (�迭�� ��� �־��� N: ���� �������� �ִ� ���)
	// ����Ž��Ʈ���� ����Ž���� ���� ������ �߰��� �� ���� �����ʹ� ���ʿ�, �� ū �����ʹ� �����ʿ� �����Ѵ�.(����)
	// ������ �Է� �� ��Ƚ���� O(logN) (vector�� list�� O(1))) -> ������ �Է½� ����� �� ũ���� Ž���� �� ����

	// Ʈ���� ��ȸ: ����Ž��Ʈ���� ������ȸ�� ������ �� �����Ͱ� ���ĵ� ����
	// ��ȸ ��� �� �켱����. �켱���� ���� �湮. 
	// ������ȸ(in order): �����ڽ�-�θ�-�������ڽ� -> ����Ž��Ʈ���� iterator
	// ������ȸ(pre order): �θ�-�����ڽ�-�������ڽ� 
	// ������ȸ(post order): �����ڽ�-�������ڽ�-�θ�

	// �����Ͱ� ���������� �ԷµǴ� ��� ����Ž��Ʈ�� ����. �������� �� ����. ���ݾ� �پ��� ȿ�� ����.
	// ����Ž��Ʈ�� �뷱�� �������� Ž���� ȿ����. 
	// �����δ� self balanced�� ���� ����� �߰��ؼ� ���. (red black binary search tree)


	// =====���======
	// ����Ž��
	// 1. ���ĵǾ� �ִ� �����Ϳ� ���� ����
	

	// ����Ž��Ʈ��
	// 1. ����Ž���� ����� �� �ְ� ��ȵ� ����Ʈ��
	// 2. ������ �Է½� O(log(N)) ȿ��(self balance ��ɱ��� ���ԵǸ� �� ��������)
	// 3. Ž�� ȿ���� O(log(N))
	// 4. Ʈ���� ����� �뷱���� �������� ������ ����ε� �˻� ȿ���� ������ �ʴ´�. - �ڰ����� ��� �ʿ�(AVL, Red/Black)

	setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");

	set<int> setInt; // Ž���� ���� red black tree container��� �����ϸ� ��.

	setInt.insert(100); // �����ʹ� �����Ҵ��� ���� ���޸𸮿� �����ϰ� ��ü�� root node�� ����Ű�� ������ ��.
	setInt.insert(50);
	setInt.insert(150);

	// map�� �� ���� �����
	// ù���� ���ڰ� key�� �ڷ���, �ι�° ���ڰ� ��忡 ���ϴ� ���� �ڷ���. (Ž�� �ÿ��� key�� ã��.)
	// ���� ��� �л� ������ �����Ѵٰ� �� ��, �л� �̸��� key��, �л����� ��ü�� value�� ����� �� ����.
	map<const wchar_t*, tStdInfo> mapData;
	tStdInfo info1(L"ȫ�浿", 18, MAN);
	tStdInfo info2(L"������", 25, WOMAN);

	// make_pair: pair�� ����� �Լ�
	mapData.insert(make_pair(L"ȫ�浿", info1));
	mapData.insert(make_pair(L"������", info2));

	// find ����� �������� �ʴ� ��� iterator�� end iterator
	map<const wchar_t*, tStdInfo>::iterator mapiter;
	mapiter = mapData.find(L"ȫ�浿"); // return�� pair�� ����Ű�� iterator ����
	// const wchar_t*�� key�� �����߱� ������ ���ڿ� ��ü�� �ƴ϶� ���ڿ��� �ּҷ� ã�� ��.
	// wchar_t szFind[20] = L"������"; ��� ������ �޾Ƽ� mapData.find(szFind);�ϸ� �ּҰ� �޶� ã�� ����. 
	// ���ڿ��� ���Ϸ��� ���ڿ� Ŭ������ �־����. 

	

	// ã�� ���ߴ�.
	if (mapiter == mapData.end())
	{
		wcout << L"�����͸� ã�� �� ����" << endl;
	}
	else
	{
		(*mapiter).first;
		(*mapiter).second;
		// ������ �����ε��� ���� �����Ǿ�����.
		wcout << L"�̸�" << mapiter->second.szName << endl;
		wcout << L"����" << mapiter->second.age << endl;
		wcout << L"����" ;


		if (MAN == mapiter->second.gender)
		{
			wcout << L"����" << endl;
		}
	    else if (WOMAN == mapiter->second.gender)
		{
			wcout << L"����" << endl;
		}
		else
		{
			wcout << L"�� �� ����" << endl;
		}
	
	}

	map<wstring, tStdInfo> mapStdInfo;

	wstring str;
	// �ּҰ� �ƴ϶� ��ü������ ���ڸ� �����Ѵ�.(�����迭�� �����ϰ� �����͸� ������ ��. vector<wchar_t>)
	str = L"abcde";
	str += L"addstr";
	// c������ ������ �� ���� ����ǥ, ���ڿ��� �� ū ����ǥ ���
	str[1] = L'c'; // �б� ���� �޸� ������ �ƴϹǷ� ���� ����

	wstring str2;

	if (str == str2) //������ �����ε�. ��Һ񱳵� ����. -> key�� ����ϸ� Ž�� ����
	{

	}

	// ���� ���� ���� Ŭ������ key�� ����Ϸ��� ��Һ񱳸� ���� ������ �����ε��� �����Ǿ� �־����. 
	map<MyClass, tStdInfo> mapMyClassStdInfo;


	return 0;
}