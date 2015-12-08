#pragma once

#include "Common.h"
#include <cstring>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <sys/types.h>
#include <sys/stat.h>
#endif

namespace ReadViolationTest
{
    class ReadViolationTest : public Common::Test
    {
    protected:
        virtual bool run()
        {
#if defined(_WIN32) || defined(_WIN64)
            const int NvGenericStringBufferMax = 4096;
            typedef char NvTk_String_t[NvGenericStringBufferMax];
            NvTk_String_t szFileDateTime;
            struct _stat buf;
            buf.st_mtime = -196296254;

#define ERROR_NOT_HAPPEN 0
            strcpy(szFileDateTime, "test"); // only for remve the compiler warning

#define ERROR_JUST_HAPPEN 1

#if ERROR_NOT_HAPPEN
                                            // ??st_mtime???, ??fileTime.Format?????, ????????
            CTime fileTime(buf.st_mtime);
            CString s = fileTime.Format(L"%Y/%m/%d %H:%M:%S");
#endif

#if ERROR_NOT_HAPPEN
            // ??st_mtime???, ??ctime()?????NULL [?ctime??????, ???_VALIDATE_RETURN_NOEXC()?(internal.h)??????, ????NULL], ??strcpy??read violation 0x00???
            strcpy(szFileDateTime, ctime(&buf.st_mtime));
#endif
#endif
            return true;
        }
    };
}
