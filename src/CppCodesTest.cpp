// CppCodesTest.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include "PriorityQueueTest.h"
#include "FunctionBindTest.h"
#include "ReadViolationTest.h"
#include "MemoryConsumeBigTest.h"
#include "SizeOfTest.h"

#define RUN_TEST(_Test) _Test##Test::_Test##Test _Test##Tester;\
                        _Test##Tester.Execute();

int main(int argc, const char * argv[])
{
    RUN_TEST(SizeOf);

    RUN_TEST(PriorityQueue);

    RUN_TEST(FunctionBind);

    RUN_TEST(ReadViolation);

    RUN_TEST(MemoryConsumeBig);

    // 注意, 返回0表示成功运行, 否则返回非0都是会对应错误的
    return 0;
}

