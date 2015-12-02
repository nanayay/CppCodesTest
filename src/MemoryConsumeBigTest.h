#pragma once

#include "Common.h"
#include <string>

namespace MemoryConsumeBigTest
{
    class MemoryConsumeBigTest : public Common::Test
    {
    protected:
        virtual bool run()
        {
            // Test for LargAddressAware
            const unsigned int array_size = 1024 * 2; // total memory cost: array_size * item_size
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