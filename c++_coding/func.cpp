#include "func.h"
#include "common.h"
#include <stdio.h>

int Add(int a, int b)
{
	printf("g_iStatic�� ���� %d\n", g_iStatic);
	printf("g_iExtern�� ���� %d\n", g_iExtern);
	return a + b;
}