#include <iostream>

#include <map>
#include <set>

#include <string>

using std::cout;
using std::endl;


class CParent
{
protected:
		int    m_i;

public:
	void SetInt(int _a)
	{
		m_i = _a;
	}

	// �����Լ�: Ŭ������ �����Լ� ���̺� ��ϵ�. 
	virtual void Output()
	{
		cout << "Parent" << endl;
	}

public:
	CParent()
		: m_i(0)
	{
		cout << "�θ������" << endl;
	}
	CParent(int _a)
	{
		m_i = _a;
	}
	~CParent()
	{}
};

class CChild : public CParent
{
private:
	float    m_f;

public:
	void SetFloat(float _f)
	{
		m_f = _f;
		m_i = 0; // ��� �޾Ҿ �θ��� private�� ������ �� ����. 
	} 

	// ��ӹ��� �θ� Ŭ������ �Լ��� ������(�������̵�)��. 
	void Output()
	{
		cout << "Child" << endl;
	}

	void NewFunc()
	{
		cout << "new functoin" << endl;
	}

public:
	// �����ڴ� �ڽĺ��� ȣ���. �Լ� �ȿ��� �Լ��� ȣ���ϴ� ��ó��. 
	// �ڽ� �����ڿ� parent ������ ȣ���� ��� �ִ� ��. ���� �Ϸ� ���� != ȣ�� ���� 
	// �θ��� �⺻ ������ ���� Ư�� �����ڸ� ȣ���ϰ� ������ ��������� ������� 
	CChild()
		: CParent(1000)
		, m_f(0.f) // �ʱ�ȭ�� �� Ŭ���� ��� ���� ����Ǳ� ������ �θ� ��� ���� �ʱ�ȭ�� �θ� �����ڿ��� �̷������. 
	{
		m_i = 0;
		cout << "�ڽĻ�����" << endl;
	}

	~CChild()
	{
		// �θ� �Ҹ��ڸ� �ڵ����� ȣ����. 
		// �ڽĺ��� ȣ���ϰ� �����ϰ�, �θ� �Ҹ��ڸ� ȣ���ϰ� ������. 
	}
};


// ��ӹ��� ������� �޸𸮸� ����
class CChildChild : public CChild
{
private:
	long long m_ll;

};


int main()
{
	// ��ü���� ��� Ư¡
	// 1. ĸ��ȭ(���м�)
	// 2. ���
	// 3. ������
	// 4. �߻�ȭ

	// ���
	// �ڽ� or �θ� Ŭ������ ��� ���迡�� �ٸ� Ŭ������ ����� �ʱ�ȭ�� �� ����.
	// ������ ȣ�� ������ �ڽ� -> �θ�
	// ������ ����, �ʱ�ȭ ���� �θ� -> �ڽ�
	// �Ҹ��� ���� �� ȣ�� ����, �ڽ� -> �θ�
	// �������̵�(�����ε��� �ٸ�. �������̵��� ��Ӱ��迡�� ����)
	// : �θ� Ŭ������ ��� �Լ��� �ڽ��ʿ��� �����������ν�, �ڽ� Ŭ������ ������ ����� ȣ��ǵ��� �Ѵ�.

	
	CParent parent; // 4byte
	CChild child; // 8byte(parent �κе� ����)

	child.SetInt(10);

	// �������̵�
	parent.Output();
	child.Output();


	// ��� and ������
	// CParent* pParent = &child; // parent�� ��ӹ��� child�� parent�� child�� ���ӵ� �޸� ������ ������ ������ ���� ����. (��ġ�� ũ�� ��� ����)
	// CChild* pChild = &parent;

	// parent���κ��� �Ļ��Ǵ� ��� ���� �θ� �����͸� ���� �� �ִ�. 
	// parent �����ͷ� ���� �� CChild, CChildChild�ϼ� �ִ�. 

	CParent* pParent = nullptr;

	parent.Output();
	pParent = &parent;
	pParent->Output();

	child.Output();
	pParent = &child;
	pParent->Output(); // �����Լ� �������� �ʴ� ��� parent ��ü�� �Լ��� ȣ��ȴ�. 

	// ������, �����Լ�(virtual)
	// �θ� ������ Ÿ������, �θ� Ŭ�����κ��� �Ļ��Ǵ� �ڽ�Ŭ���� ��ü���� �ּҸ� ����ų �� ����.
	// ��� ��ü�� �θ� Ŭ���� Ÿ������ �ν��ϰ� �Ǳ� ������, ���� ��ü�� �������� �� �� ����.
	// virtual Ű���带 ���ؼ�, �� Ŭ������ �ڽŸ��� ������ �����Լ� ���̺��� ������ �ȴ�.
	// �� Ŭ������ ��ü���� �����Լ� ���̺� �����Ϳ��� �ش� Ŭ������ �´� ���̺��� ����Ű�� �ȴ�.
	// �� ���̺��� �ش� Ŭ������ �����Լ����� ��ϵǾ� �ִ�.

	// �ٿ�ĳ����
	// �θ� Ŭ�������� ������� ����, ���� �ڽ��ʿ����� �߰��� �Լ��� ȣ���ϰ� ���� ��
	// �ڽ� ������Ÿ������ �Ͻ������� ĳ�����ؼ� ȣ���Ѵ�.
	// ������ �߻��� �� �ֱ� ������ dynamic_cast�� �����ϰ� Ȯ���غ� �� �ִ�.
	// RTTI(Run Time Type Identification or Information)

	((CChild*)pParent)->NewFunc();
	// ĳ���� ������ ���� ����� �� �־ �� �����ϴ�. 
	CChild* pChild = dynamic_cast<CChild*>(pParent);
	if (nullptr != pChild)
	{
		pChild->NewFunc();
	}

	// �߻�ȭ
	// ���� ��ü�� ������ ������ Ŭ������ �ƴ�, ����� ���ؼ� �����ؾ��� ������ �����ϴ� ��� �������� ������� Ŭ����
	// virtual, =0 (1 �� �̻��� ���������Լ��� �����ϸ� �߻�Ŭ������ �ȴ�.)

	return 0;
}