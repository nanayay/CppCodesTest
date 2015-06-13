// CppCodesTest.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <atltime.h>

#include <functional>
#include <iostream>
#include <queue>
#include <vector>



namespace Common {
    class Test {
    protected:
        virtual bool prepare();
        virtual bool run() = 0;
        virtual bool shutdown();

    public:
        void Execute()
        {
            prepare();
            run();
            shutdown();
        }
    };
    bool Test::prepare()
    {
        return true;
    }

    bool Test::shutdown()
    {
        return true;
    }

    bool Test::run()
    {
        return true;
    }
}

namespace PriorityQueueTest
{
    class Task
    {
    private:
        unsigned int priority;

    public:
        explicit Task(unsigned int priority_) : priority(priority_) { }
        ~Task() { }
        Task(const Task& copy_) : priority(copy_.priority) { }
        Task operator=(const Task& assign_)
        {
            if (this != &assign_) {
                priority = assign_.priority;
            }
            return *this;
        }

        unsigned int getPriority() const { return priority; }
        bool operator<(const Task& rhs) const { return this->priority < rhs.priority; }
        bool operator>(const Task& rhs) const { return this->priority > rhs.priority; }
    };

    class TaskCmp
    {
    public:
        bool operator()(const Task& lhs, const Task& rhs) const
        {
            return lhs.getPriority() < rhs.getPriority();
        }
    };

    class PriorityQueueTest : public Common::Test
    {
    protected:
        virtual bool prepare()
        {
            return Common::Test::prepare();
        }

        virtual bool shutdown()
        {
            return Common::Test::shutdown();
        }

        virtual bool run()
        {
            std::cout << "less priority queue" << std::endl;
            std::priority_queue<Task> kernel;
            for (int i = 0; i < 100; i++) {
                kernel.push(Task(rand()));
            }

            while (!kernel.empty()) {
                std::cout << kernel.top().getPriority() << std::endl;
                kernel.pop();
            }

            for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 3, 2})
                kernel.push(Task(n));

            while (!kernel.empty())
            {
                std::cout << kernel.top().getPriority() << std::endl;
                kernel.pop();
            }

            std::cout << "greater priority queue" << std::endl;
            std::priority_queue<Task, std::vector<Task>, std::greater<Task>> gKernel;
            for (int i = 0; i < 100; i++) {
                gKernel.push(Task(rand()));
            }

            while (!gKernel.empty()) {
                std::cout << gKernel.top().getPriority() << std::endl;
                gKernel.pop();
            }

            for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 3, 2})
                gKernel.push(Task(n));

            while (!gKernel.empty())
            {
                std::cout << gKernel.top().getPriority() << std::endl;
                gKernel.pop();
            }

            std::cout << "Compare function object priority queue" << std::endl;
            std::priority_queue<Task, std::vector<Task>, TaskCmp> cKernel;
            for (int i = 0; i < 100; i++) {
                cKernel.push(Task(rand()));
            }

            while (!cKernel.empty()) {
                std::cout << cKernel.top().getPriority() << std::endl;
                cKernel.pop();
            }

            for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 3, 2})
                cKernel.push(Task(n));

            while (!cKernel.empty())
            {
                std::cout << cKernel.top().getPriority() << std::endl;
                cKernel.pop();
            }

            return true;
        }
    };
}

namespace FunctionBindTest
{
    class test
    {
    public:
        test(){};

        double tt(double input)
        {
            return input;
        };

        double tt(double i, float j)
        {
            return i + j;
        }
    };

    double fptr_test_Cstyle(test* object, double (test::*fptr)(double), double input)
    {
        return (object->*fptr)(input); // 注意, object->*fptr 周围必须要有(), 否则编译错误, 因为要先计算出函数指针, 然后再传入参数
        // 而且, 调用类成员函数指针, 必须要有一个类成员的实例才可以
    }

    double fptr_testfunc1(std::function<double(double)> func, double input)
    {
        return func(input);
    }

    double fptr_testfunc2(std::function<double(double, float)> func, double input1, float input2)
    {
        // 注意, 这边的function的模板参数是函数类型, double(double, float), 而不是函数指针, 如果写了double(*p)(double, float)会出错的
        // 通过function和bind, 就不需要显示的传入函数指针, 可以比较OOP的方式来进行调用
        return func(input1, input2);
    }

    class FunctionBindTest : public Common::Test
    {
    protected:
        virtual bool run()
        {
            test t;

            // 普通调用方式, 调用double tt(double)函数
            std::cout << t.tt(3) << std::endl;

            // 通过c的函数指针方式调用类的成员函数, 需要预先传入类的实例, 通过类的实例来调用函数指针
            //      注意, 传入的类函数指针的定义, 需要加上&test::tt, 而不能仅仅使用tt, 这个和c的函数指针不一样
            std::cout << fptr_test_Cstyle(&t, &test::tt, 4) << std::endl;

            // 下面的语句会编译出错, 因为这边要转换的是函数指针, 而上面定义function<>的时候, 是指定函数类型才用的function<double(double)>的, 函数类型和函数指针类型是不一样的
            // cout << fptr_testfunc1(std::bind(static_cast<double(double)>(&test::tt), t, std::placeholders::_1), 4) << endl;

            // 通过bind来绑定对应的类实例, 以及对应的参数到类的函数指针上去
            // 调用double tt(double)函数
            //      注意, bind的第一个参数是类的函数指针, 如果对应的类成员函数有重载, 那么需要显式转换到期望调用的重载类型上去
            //      注意, placeholders::_1用来作为bind的函数和类之间的参数占位符, 表示有几个参数
            std::cout << fptr_testfunc1(std::bind(static_cast<double(test::*)(double)>(&test::tt), t, std::placeholders::_1), 5) << std::endl;

            // 普通调用方式, 调用double tt(double, float)
            std::cout << t.tt(6, 7) << std::endl;

            // 通过bind来绑定对应的类实例, 以及对应的参数到类的函数指针上去
            // 调用double tt(double, float)函数
            //      注意, 这边的static_cast强制转换到期望的重载函数的指针类型上去
            std::cout << fptr_testfunc2(std::bind(static_cast<double(test::*)(double, float)>(&test::tt), t, std::placeholders::_1, std::placeholders::_2), 8, 9) << std::endl;

            return true;
        }
    };
}

namespace SizeOfTest
{
    size_t foo1(char* t)
    {
        return sizeof(t);
    }

    size_t foo2(char t[])
    {
        return sizeof(static_cast<char*>(t));
    }

    class SizeOfTest : public Common::Test
    {
    protected:
        virtual bool run()
        {
            char* x = new char[100];
            size_t xx = sizeof(x); // xx == 8[64bit] or 4[32bit]
            size_t xxx = foo1(x); // xxx == 8 or 4
            size_t xxxx = foo2(x); // xxxx == 8 or 4
            delete[] x;
            std::cout << xx << xxx << xxxx << std::endl;

            char y[100];
            size_t yy = sizeof(y); // yy == 100
            size_t yyy = foo1(y); // yyy == 8 or 4
            size_t yyyy = foo2(y); // yyyy == 8 or 4
            std::cout << yy << yyy << yyyy << std::endl;

            return true;
        }
    };
}

namespace ReadViolationTest
{
    class ReadViolationTest : public Common::Test
    {
    protected:
        virtual bool run()
        {
            const int NvGenericStringBufferMax = 4096;
            typedef char NvTk_String_t[NvGenericStringBufferMax];
            NvTk_String_t szFileDateTime;
            struct _stat buf;
            buf.st_mtime = -196296254;

#define ERROR_NOT_HAPPEN 0
            strcpy(szFileDateTime, "test"); // only for remve the compiler warning

#define ERROR_JUST_HAPPEN 1

#if ERROR_NOT_HAPPEN
            // 因为st_mtime为负数, 那么fileTime.Format会检查其值, 然后直接抛出异常
            CTime fileTime(buf.st_mtime);
            CString s = fileTime.Format(L"%Y/%m/%d %H:%M:%S");
#endif

#if ERROR_NOT_HAPPEN
            // 因为st_mtime为负数, 那么ctime()会直接返回NULL [在ctime调用的过程中, 会使用_VALIDATE_RETURN_NOEXC()宏(internal.h)检查其值非负, 否则返回NULL], 然后strcpy抛出read violation 0x00的错误
            strcpy(szFileDateTime, ctime(&buf.st_mtime));
#endif
            return true;
        }
    };
}

namespace MemoryConsumeBigTest
{
    class MemoryConsumeBigTest : public Common::Test
    {
    protected:
        virtual bool run()
        {
            // Test for LargAddressAware
            const unsigned int array_size = 1024 * 4; // total memory cost: array_size * item_size
            const unsigned int item_size = 1024 * 1024;

            char* t[array_size];

            // draw a sin wave like memory cost diagram in taskmgr
            for (unsigned int i = 0; i < array_size; i++)
            {
                t[i] = new char[item_size]; // each item has 1Mb memory
                for (size_t j = 0; j < item_size; j++)
                {
                    const char v = 'a';
                    memcpy(t[i] + j, &v, 1);
                }
            }
            for (unsigned int i = 0; i < array_size; i++)
            {
                for (unsigned int j = 0; j < item_size; j++)
                {
                    const char v = 'b';
                    memcpy(t[i] + j, &v, 1);
                }
                delete[] t[i];
            }

            for (unsigned int i = 0; i < array_size; i++)
            {
                t[i] = new char[item_size]; // each item has 1Mb memory
                for (size_t j = 0; j < item_size; j++)
                {
                    const char v = 'a';
                    memcpy(t[i] + j, &v, 1);
                }
            }
            for (unsigned int i = 0; i < array_size; i++)
            {
                for (unsigned int j = 0; j < item_size; j++)
                {
                    const char v = 'b';
                    memcpy(t[i] + j, &v, 1);
                }
                delete[] t[i];
            }

            getchar();
            return true;
        }
    };
}

int main(int argc, const char * argv[])
{
    SizeOfTest::SizeOfTest sot;
    sot.Execute();

    PriorityQueueTest::PriorityQueueTest pqt;
    pqt.Execute();

    FunctionBindTest::FunctionBindTest fbt;
    fbt.Execute();

    ReadViolationTest::ReadViolationTest rvt;
    rvt.Execute();

    MemoryConsumeBigTest::MemoryConsumeBigTest mcbt;
    mcbt.Execute();

    // 注意, 返回0表示成功运行, 否则返回非0都是会对应错误的
    return 0;
}

