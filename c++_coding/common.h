#pragma once

// common.h 메모리에 고정됨. include로 다른 파일에 포함하더라도 복사 붙여넣기이기 때문에 서로 다른 변수이다. -> 모든 파일에서 통용되는 변수가 되는 것은 아님. 
static int g_iStatic = 0;
// 외부변수는 선언할 때 초기화 하면 안된다. 
extern int g_iExtern;