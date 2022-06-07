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

	// 가상함수: 클래스의 가상함수 테이블에 등록됨. 
	virtual void Output()
	{
		cout << "Parent" << endl;
	}

public:
	CParent()
		: m_i(0)
	{
		cout << "부모생성자" << endl;
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
		m_i = 0; // 상속 받았어도 부모의 private는 접근할 수 없다. 
	} 

	// 상속받은 부모 클래스의 함수를 재정의(오버라이딩)함. 
	void Output()
	{
		cout << "Child" << endl;
	}

	void NewFunc()
	{
		cout << "new functoin" << endl;
	}

public:
	// 생성자는 자식부터 호출됨. 함수 안에서 함수를 호출하는 것처럼. 
	// 자식 생성자에 parent 생성자 호출이 들어 있는 것. 실행 완료 순서 != 호출 순서 
	// 부모의 기본 생성자 말고 특정 생성자를 호출하고 싶으면 명시적으로 적어야함 
	CChild()
		: CParent(1000)
		, m_f(0.f) // 초기화는 각 클래스 멤버 별로 진행되기 때문에 부모 멤버 변수 초기화는 부모 생성자에서 이루어진다. 
	{
		m_i = 0;
		cout << "자식생성자" << endl;
	}

	~CChild()
	{
		// 부모 소멸자를 자동으로 호출함. 
		// 자식부터 호출하고 실행하고, 부모 소멸자를 호출하고 실행함. 
	}
};


// 상속받은 순서대로 메모리를 구성
class CChildChild : public CChild
{
private:
	long long m_ll;

};


int main()
{
	// 객체지향 언어 특징
	// 1. 캡슐화(은닉성)
	// 2. 상속
	// 3. 다형성
	// 4. 추상화

	// 상속
	// 자식 or 부모 클래스는 상속 관계에서 다른 클래스의 멤버를 초기화할 수 없다.
	// 생성자 호출 순서는 자식 -> 부모
	// 생성자 실행, 초기화 순서 부모 -> 자식
	// 소멸자 실행 및 호출 순서, 자식 -> 부모
	// 오버라이딩(오버로딩과 다름. 오버라이딩은 상속관계에만 적용)
	// : 부모 클래스의 멤버 함수를 자식쪽에서 재정의함으로써, 자식 클래스에 구현된 기능이 호출되도록 한다.

	
	CParent parent; // 4byte
	CChild child; // 8byte(parent 부분도 포함)

	child.SetInt(10);

	// 오버라이딩
	parent.Output();
	child.Output();


	// 상속 and 포인터
	// CParent* pParent = &child; // parent를 상속받은 child는 parent와 child를 연속된 메모리 공간에 가지기 때문에 문제 없다. (위치와 크기 모두 동일)
	// CChild* pChild = &parent;

	// parent으로부터 파생되는 모든 것은 부모 포인터를 받을 수 있다. 
	// parent 포인터로 갔을 때 CChild, CChildChild일수 있다. 

	CParent* pParent = nullptr;

	parent.Output();
	pParent = &parent;
	pParent->Output();

	child.Output();
	pParent = &child;
	pParent->Output(); // 가상함수 설정하지 않는 경우 parent 객체의 함수가 호출된다. 

	// 다형성, 가상함수(virtual)
	// 부모 포인터 타입으로, 부모 클래스로부터 파생되는 자식클래스 객체들의 주소를 가리킬 수 없다.
	// 모든 객체를 부모 클래스 타입으로 인식하게 되기 때문에, 실제 객체가 무엇인지 알 수 없다.
	// virtual 키워드를 통해서, 각 클래스는 자신만의 고유한 가상함수 테이블을 가지게 된다.
	// 각 클래스의 객체들은 가상함수 테이블 포인터에서 해당 클래스에 맞는 테이블을 가리키게 된다.
	// 그 테이블에는 해당 클래스의 가상함수들이 등록되어 있다.

	// 다운캐스팅
	// 부모 클래스에서 선언되지 않은, 오직 자식쪽에서만 추가된 함수를 호출하고 싶을 때
	// 자식 포인터타입으로 일시적으로 캐스팅해서 호출한다.
	// 문제가 발생할 수 있기 때문에 dynamic_cast로 안전하게 확인해볼 수 있다.
	// RTTI(Run Time Type Identification or Information)

	((CChild*)pParent)->NewFunc();
	// 캐스팅 실패할 때를 대비할 수 있어서 더 안전하다. 
	CChild* pChild = dynamic_cast<CChild*>(pParent);
	if (nullptr != pChild)
	{
		pChild->NewFunc();
	}

	// 추상화
	// 실제 객체를 생성할 목적의 클래스가 아닌, 상속을 통해서 구현해야할 내용을 전달하는 상속 목적으로 만들어진 클래스
	// virtual, =0 (1 개 이상의 순수가상함수를 포함하면 추상클래스가 된다.)

	return 0;
}