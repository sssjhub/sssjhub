// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.

#include "GtestTest.h"
#include <string>

// Returns n! (the factorial of n).  For negative n, n! is defined to be 1.
int Factorial(int n) {
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }

  return result;
}

// Returns true if and only if n is a prime number.
bool IsPrime(int n) {
  // Trivial case 1: small numbers
  if (n <= 1) return false;

  // Trivial case 2: even numbers
  if (n % 2 == 0) return n == 2;

  // Now, we have that n is odd and n >= 3.

  // Try to divide n by every odd number i, starting from 3
  for (int i = 3;; i += 2) {
    // We only have to try i up to the square root of n
    if (i > n / i) break;

    // Now, we have i <= n/i < n.
    // If n is divisible by i, n is not prime.
    if (n % i == 0) return false;
  }

  // n has no integer factor in the range (1, n), and thus is prime.
  return true;
}

bool getAuditValue(std::string filePath, std::string key1, std::string key2)
{
    FILE* fd = fopen(filePath.c_str(), "r");
    if (NULL == fd) 
    {
        return 0;
    }

    bool bAudit0 = true;
    bool bAudit1 = false;
    char buf[4096] = {0};
    while(fgets(buf, 4096, fd) != NULL) 
    {
        std::string strLine = buf;
        if(strLine[0] == '#')
        {
            continue;
        }

        if (strLine.find("vmlinuz") != strLine.npos && strLine.find(key2) != strLine.npos) 
        {
            std::string strtmp;
            size_t pos_audit = strLine.find("audit");
            if (pos_audit != std::string::npos)
            {
                // 获取audit=后配置参数
                size_t pos_space = strLine.find_first_of(" ", pos_audit + 6);
                size_t pos_n = strLine.find_first_of("\n", pos_audit + 6);
                if (pos_space != std::string::npos) 
                {
                    strtmp = strLine.substr(pos_audit + 6, pos_space - pos_audit - 6);
                    if(strtmp == "1")                
                    {
                       bAudit1 = true;
                    }
                    else if (strtmp == "")
                    {
                         bAudit1 = true;
                    }
                    else
                    {
                        bAudit0 = false;
                    }
                } 
                else if (pos_n != std::string::npos)
                {
                    strtmp = strLine.substr(pos_audit + 6, pos_n - pos_audit - 6);
                    if (strtmp == "1")                
                    {
                       bAudit1 = true;
                    }
                    else if (strtmp == "")
                    {
                        bAudit1 = true;
                    }
                    else
                    {
                        bAudit0 = false;
                    }
                } 
                else // 存在audit无space、\n
                {
                    continue;
                }
            }
            else // 不存在audit参数
            {
                bAudit0 = false; 
                continue;     
            }
        }
        else
        {
            continue;
        }
    }
    fclose(fd);

    if(bAudit1 && bAudit0)
    {
        return true;
    }
    else
    {
        return false;
    }
}