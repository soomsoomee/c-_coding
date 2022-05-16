// 전처리기: #으로 시작하는 구문으로 컴파일 과정에서 가장 먼저 실행하는 것. 
// 16진법으로 나타내는 경우-> 규칙성을 가지고 표현할 수 있어서 좋음.
#define HUNGRY 0x001
#define THIRSTY 0x002
#define TIRED 0x004
#define FIRE 0x008

#define COLD 0x010
#define POISON 0x020

#define COLD1 0x100
#define POISON2 0x200
#define POISON3 0x400
#define POISON4 0x800

#include <stdio.h>

// 내가 지정한 구문을 특정 숫자로 치환한다. -> HUNGRY를 1로 바꾼다. 
// 장점: 가독성(구문과 연결되는 숫자를 외울 필요가 없음), 유지 보수의 편리성(구문에 대응하는 숫자 바꾸기 편리)

// 함수
int Add(int left, int right)
{
	return left + right;
}

int Factorial(int _iNum)
{	
	int iValue = 1;
	for (int j = 0; j < _iNum - 1; ++j)
	{
		iValue *= (j + 2);
	}
	return iValue;
}

// 재귀함수
// 함수가 끝나기 전에 자기 자신을 호출하므로 동일한 함수가 스택으로 계속 쌓인다. -> 계속 쌓이면 stack overflow error 발생
// 함수를 종료하기 위해서는 탈출 조건이 필요함. 
// 가독성, 구현의 용이 but 성능이 떨어질 수 있음. 

int Factorial_recursive(int _iNum)
{	
	if (1 == _iNum)
	{
		return 1;
	}
	return _iNum * Factorial_recursive(_iNum - 1);

}

// 피보나치 수열
// 1 1 2 3 5 8 13
int Fibonacci(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}

	int iPrev1 = 1;
	int iPrev2 = 1;
	int iValue = 0;

	for (int i = 0; i < _iNum - 2; ++i)
	{
		iValue = iPrev1 + iPrev2;
		iPrev1 = iPrev2;
		iPrev2 = iValue;
	}

	return iValue;
}

int Fibonacci_recursive(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}
	
	return Fibonacci_recursive(_iNum - 1) + Fibonacci_recursive(_iNum - 2);
}


int main()
{
	// 자료형 (크기 단위, byte) -> 정수와 실수는 메모리를 활용하는 방식이 다르다.
	// 실수 표현방식은 정밀도에 의존한다. 따라서 double 자료형이 float보다 더 아래의 소수점까지 정확하게 표현이 가능하다.  
	// 4와 4.0의 비트 값이 다름. 따라서 섞여있을 때 무엇을 기준으로 할지 정해야함. -> 형변환 과정이 추가됨. 

	// 정수형: char(1), short(2), int(4), long(4), long long(8)
	// 실수형: float(4), double(8) -> 부동소수점(지수파트, 가수파트로 나눠쓴다.) 	

	int i = 0;

	// 8bit으로는 총 2**8 (=256) 가지의 경우를 표현할 수 있다. 따라서 1byte로 0 이상 정수만 표현하면 0부터 255까지 나타낼 수 있다. 
	// 0이상의 정수만 표현하는 경우 unsigned 추가. c는 0부터 255까지 나타낼 수 있다.
	unsigned char c = 0;

	// 대입 연산자
	// c = 256는 저장되지 않음. 0으로 들어온다. 아홉번째 1이 들어오지 않기 때문이다. 
	// c = -1 넣으면 255로 보인다. 에러가 나지 않음. 

	c = 0;
	c = 255;

	// char = signed char : 음수, 양수 모두 표현 가능
	// 1byte로 -128 ~ -1,  0 ~ 127 표현 가능 (블록이 8개 있으면 제일 앞에 블록이 0인 경우를 양수, 1인 경우를 음수에 대응시킴. 이 비트를 MSB;most significant bit라고 한다.)
	// msb가 0일 때는 양수, 1일 때는 음수를 표현한다.
	// 컴퓨터가 음수를 표현하는 방식: 뺄셈은 음수의 합이라고 본다. 따라서 10이랑 더해서 0이 되는 상태가 -10이라고 본다. 
	// 마찬가지로 00000001과 더해서 0이 되는 11111111이 -1이다. c1=255라고 하면 -1이 저장된다. 
	// c = 255, c1 = 255일 때 두 변수의 비트 상태는 동일하다. 동일한 메모리 공간에 똑같이 데이터가 채워져있더라도 관점(=자료형)에 따라 값이 다르게 해석된다. 

	char c1 = 0;

	// 2byte는 2**16 경우의 수를 나타낼 수 있다. 비트가 16개 이므로. (-3만 ~ 3만)
	// 적절한 만큼의 메모리를 가지도록 자료형을 설정하는 것이 중요하다. 

	// 정수는 정수끼리, 실수는 실수끼리 연산하되, 두 표현방식의 피 연산자가 연산될 경우 명시적으로 변환하자.
	float f = 10.2415f + float(20);

	// 실수를 상수로 적을 경우 소수점 뒤에 f를 붙이면 float 자료형으로, f를 붙이지 않으면 double 자료형으로 간주한다.
	// 0.1f, 0.1;
	
	// 연산자(operater)
	// 대입 연산자, =
	// 산술 연산자
	// +, -, *, /, %(모듈러스, 나머지)
	// ++, -- (증감연산자) -> 한 단계 증가/감소 -> 꼭 1로 변화하는 것은 아님. 대입 안해도 메모리 값 자체가 변함. 
	int data = 10 + 10;
	data += 20;

	// 나누기: 피연산자가 정수인지, 실수인지에 따라 다름.
	// 실수 나눗셈에서는 나머지가 존재하지 않음. 나머지 연산은 피연산자가 정수인 경우만 사용 가능.

	data = 10 / 3; // 3
	data = 10 % 3; // 1
	// 10. % 3.은 컴파일 에러 발생

	// int data이므로 3.이 3으로 변환됨.(경고 메시지) -> 명확하게 정수로 변환하기.
	data = (int)( 10. / 3.);

	data = 0;
	// 전위, 후위 상관 없는 경우 전위로 쓰는 것이 좋다. 
	++data; // (전위)
	data++; // (후위)
	data--;

	int a;
	data = 0;
	a = 10;
	data = a++; // 후위 연산자로 사용하는 경우 연산자 순위는 가장 마지막이다. data=10. data에 a를 넣고 증가. 전위라면 data=11. 

	// 논리 연산자
	// !(역, 반대로), &&(곱, AND), ||(합, OR)
	// 참(true), 거짓(false)
	// 참 : 0이 아닌 값, 주로 1 (10을 줘도 true인데 true를 1로 본다.)
	// 거짓: 0

	true;
	false;
	
	// bool 자료형: 0 or 1 (1byte), 참과 거짓만 다루는 자료형. 
	bool truefalse = false;
	bool IsTrue = 100; // IsTrue = 1

	IsTrue = true;
	IsTrue = !IsTrue; // IsTrue = false

	int iTrue = 100;
	iTrue = !iTrue; // iTrue = 0
	
	iTrue = 100 && 200; // iTrue => true => 1
	iTrue = 0 && 200; // iTrue => false => 0

	iTrue = 0 || 100; // iTrue => true => 1


	// 비교 연산자
	// ==, !=, <, >, <=, >=
	// 참, 거짓


	//구문
	// if, else
	data = 0;
	if (0 && 200) // false => 아래 구문이 수행됨. 
	{
		data = 100;
	}

	if (data == 100)
	{
		// if가 참인 경우 수행
	}
	else if (data == 101)
	{
		// if가 거짓인 경우 수행 + 조건 검사
	}
	else
	{

	};

	// switch case : if문과 유사하게 조건을 만족하는 경우에 실행됨. 
	// if는 복잡한 조건이 있을 때 더 유용하고, switch는 가독성이 좋은 편
	switch(10)
	{
		case 10:
			break;
		case 20:
		case 30: 
			// break 안걸리면 뒤에 있는 것까지 실행된다. 해당 조건만 실행하려면 break 놓치면 안된다. 
			// 의도적으로 break 안 거는 경우도 있다. -> 여러 조건에 대해 공통적으로 똑같은 일을 하는 경우(if문으로 치면 || 조건)
			break;
		default:
			break;
	}
	
	// 삼항연산자: 코드를 꼭 줄여야 되는 이유가 아니면 굳이 쓸 필요는 없는 듯?? 
	// :?
	int iTest = 20;
	// 20인 경우 100을 넣고 아닌 경우 200을 넣는다. 
	iTest == 20 ? iTest = 100 : iTest = 200;


	// 비트연산자: 비트 단위로 연산이 이루어질 때 사용되는 연산자
	// 쉬프트 <<, >> : 비트를 민다. 
	unsigned char byte = 1;
	// 비트를 왼쪽으로 한 칸 민다.(00000001 -> 00000010) 그러면 2^1 = 2가 된다. 
	byte << 1; 
	byte <<= 1; // 바로 대입하기(2^n 배수)
	byte >>= 1; // (2^n으로 나눈 몫) -> 나누기랑 다르다. 그냥 민다고 생각하면 된다. (만약에 홀수면 가장 오른쪽 숫자가 애초에 1이니까 사라지는 것)
	
	
	// 비트 곱(&), 합(|), xor(^), 반전(~) -> 비트 자리수 짝을 맞춰서 진행하는 연산
	// &: 같은 자리수끼리 비교해서 둘 다 1일때만 1이고 나머지 경우에는 0
	// | 자리수끼리 비교해서 둘 중 하나라도 1이면 1
	// ~: 각 자리수의 비트를 반전시키는 것
	// ^: 같은 자리수끼리 비교해서 같으면 0, 다르면 1
	
	// 게임에서 활용되는 예시(여러개의 상태를 관리할 때 좋음)
	// 전처리기가 가장 먼저 실행되므로 1로 바뀐상태에서 코드가 실행된다. int니까 32bit
	// 32개의 비트를 가지고 특정 상태를 나타내고자 한다.(부상, 배고픔 등등) -> 겹치지 않는 자리가 필요하다.-> 총 32개의 상태를 한 번에 나타낼 수 있다.
	// 예를 들어서 1, 2, 3칸을 hungry, thirsty, tired로 사용한다. -> 비트 연산을 통해 상태를 넣어줄 수 있음. 
	unsigned int isSTATUS = 0;
	isSTATUS |= HUNGRY;
	isSTATUS |= THIRSTY;

	// 지정한 자리에만 1이 있는지 확인하는 것 (1, 1인 것만 확인하는 것)
	if (isSTATUS & THIRSTY)
	{
		
	}

	// 특정 자리 비트 제거(조건 계산할 필요 없음) -> 없으면 없는대로 0이고 1이었던 것도 0으로 된다. 
	isSTATUS &= ~THIRSTY; 

	// 변수
	// 1. 지역변수 
	// 2. 전역변수 
	// 3. 정적변수
	// 4. 외부변수

	// 지역변수
	// 괄호 안에 선언된 변수(함수, 지역)69+-
	{
		// 변수명 규칙: 이름이 겹치는 경우 같은 지역에 있는 변수의 우선 순위가 높다. 
		int iName = 100;
		iName;
	}

	// 함수
	data = Add(10, 20);

	// 반복문
	// for()
		//for (/*반복자 초기화*/;/*반복자 조건체크*/;/*반복자 변경*/)
		//{

		//}

	for (int i = 0; i < 6; ++i)
	{

		if (i % 2 == 1)
		{
			continue;
		}

		printf("Output i : %d \n", i);
	}

	// while()
	int ii = 0;
	while (ii < 2)
	{
		printf("Output Test\n");
		ii++;
		break;
	}


	// 콘솔
	// printf
	printf("abcd %f \n", 2.13f);
	// scanf : 콘솔창으로 부터 입력을 받음. 
	int iInput = 0;
	scanf_s("%d", &iInput);

	// 함수가 사용하는 메모리 영역 : 스택 메모리 영역
	// nested function의 실행 순서는 선입후출의 stack과 비슷하다.
	// 예를 들어, main 함수 호출하면 main 함수 안에서 호출하는 add가 실행 될 때 메모리 생겼다가 실행 완료 후 사라진다.
	// 함수 안에 지역 변수를 설정할 수 있는 이유는 함수마다 메모리 공간이 다르기 때문이다. 
	// 여러번 add를 호출하면 호출 할 때 마다 메모리 잡히고 실행 완료되면 함수 스택 사라진다.
	// 함수와 함수간의 return값은 레지스터 메모리에 넣어두었다가 전달하는 방식

	int iValue = Factorial(4);
	iValue = Factorial_recursive(4);

	iValue = Fibonacci(7);
	iValue = Fibonacci_recursive(7);


	return 0;
}