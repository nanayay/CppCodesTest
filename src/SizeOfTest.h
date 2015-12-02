#pragma once

#include "Common.h"
#include <iostream>

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
