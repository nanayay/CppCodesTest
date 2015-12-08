#pragma once

#include "Common.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdint>

namespace FileOperatorTest {
    class FileOperatorTest : public Common::Test
    {
        virtual bool run()
        {
            size_t l = 1024+80;
            uint8_t* p = new uint8_t[1024+80]();
            memset(p, 0, l);
            for (size_t i = 0; i< l; i++) {
                p[i] = static_cast<uint8_t>(i);
            }
            
            std::string filename("test.txt");
            
            std::ofstream ofs;
            ofs.open(filename);
            
            
            ofs.write(reinterpret_cast<char*>(p), l);
            ofs.close();

            std::ifstream ifs;
            ifs.open(filename);
            if (!ifs) {
                std::cout << "file: " << filename << " open failed" << std::endl;
                return false;
            }
            
            size_t dl = 0;
            ifs.seekg(0, ifs.end);
            dl = ifs.tellg();
            ifs.seekg(0, ifs.beg);
            
            uint8_t* dp = new uint8_t[dl]();
            memset(dp, 0, dl);
            
            uint8_t* dt = nullptr;
            dt = dp;
            
            while (ifs.read(reinterpret_cast<char*>(dp+ifs.gcount()/sizeof(dp[0])), 512)) {
                // todo, bug mind, just make it happen
            }
            
            if (l!=dl) {
                std::cout << "meet difference length! that should not be happen" << std::endl;
                return false;
            }
            
            for (size_t i = 0; i< dl; i++) {
                if (dp[i] != p[i])
                {
                    std::cout << "meet difference! that should not be happen" << std::endl;
                    return false;
                }
            }

            return true;
        }
    };
}
