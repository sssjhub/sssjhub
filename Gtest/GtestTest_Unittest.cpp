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

// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:

// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "GtestTest.h"
#include <limits.h>
#include "gtest/gtest.h"

namespace {

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

// Tests Factorial().

// Tests factorial of negative numbers.
TEST(FactorialTest, Negative) {
  // This test is named "Negative", and belongs to the "FactorialTest"
  // test case.
  EXPECT_EQ(1, Factorial(-5));
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_GT(Factorial(-10), 0);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  // EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
 }

// Tests factorial of 0.
TEST(FactorialTest, Zero) { EXPECT_EQ(1, Factorial(0)); }

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
    EXPECT_EQ(1, Factorial(1));
    EXPECT_EQ(2, Factorial(2));
    EXPECT_EQ(6, Factorial(3));
    EXPECT_EQ(40320, Factorial(8));
}

// Tests IsPrime()

// Tests negative input.
TEST(IsPrimeTest, Negative) {
  // This test belongs to the IsPrimeTest test case.
   EXPECT_FALSE(IsPrime(-1));
   EXPECT_FALSE(IsPrime(-2));
   EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
   EXPECT_FALSE(IsPrime(0));
   EXPECT_FALSE(IsPrime(1));
   EXPECT_TRUE(IsPrime(2));
   EXPECT_TRUE(IsPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
   EXPECT_FALSE(IsPrime(4));
   EXPECT_TRUE(IsPrime(5));
   EXPECT_FALSE(IsPrime(6));
   EXPECT_TRUE(IsPrime(23));
}


// Tests getAuditValue()

class FileAuditTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 可能需要在每个测试前设置或清理环境
        // 比如创建临时文件夹和测试数据文件
        system("cp -rf /boot/grub2/grub.cfg  /boot/grub2/grub.cfg-audit=1");

        system("cp -rf /boot/grub2/grub.cfg  /boot/grub2/grub.cfg-audit=0");
        system("sed -i 's/audit=1/audit=0/g' /boot/grub2/grub.cfg-audit=0");

        system("cp -rf /boot/grub2/grub.cfg  /boot/grub2/grub.cfg-auditnull");
        system("sed -i '/vmlinuz.*x86_64/s/ audit=1//g' /boot/grub2/grub.cfg-auditnull");
    }

    void TearDown() override {
        // 在每个测试后进行清理工作
        // 如删除临时文件
        system("rm -rf /boot/grub2/grub.cfg-audit=1"); 
        system("rm -rf /boot/grub2/grub.cfg-audit=0");
        system("rm -rf /boot/grub2/grub.cfg-auditnull");
    }
};

// 测试当文件存在audit=1
TEST_F(FileAuditTest, ReturnsTrueForExistingAudit1) {
    const std::string testFilePath = "/boot/grub2/grub.cfg-audit=1";
    const std::string key1 = "vmlinuz";
    const std::string key2 = "x86_64";

    // 创建一个包含预期键值对的测试文件
    // 这里假设你有一个方法来填充文件内容
    //createTestFile(testFilePath, {{"key1", "value1"}, {"key2", "value2"}});

    bool result = getAuditValue(testFilePath, key1, key2);
    EXPECT_TRUE(result);  // 预期函数返回true
}

// 测试当文件存在audit=0   
TEST_F(FileAuditTest, ReturnsFalseForNonexistentAudit0) {
    const std::string testFilePath = "/boot/grub2/grub.cfg-audit=0";
    const std::string keyNotThere = "vmlinuz";
    const std::string anyValue = "x86_64";  

    //createTestFile(testFilePath, {{"key1", "value1"}});
    
    bool result = getAuditValue(testFilePath, keyNotThere, anyValue);
    EXPECT_FALSE(result);  // 预期函数返回false
}

// 测试当文件不存在audit参数 
TEST_F(FileAuditTest, ReturnsFalseForNonexistentAudit) {
    const std::string testFilePath = "/boot/grub2/grub.cfg-auditnull";
    const std::string matchingKey = "vmlinuz";
    const std::string matchingValue = "x86_64";

    //createTestFile(testFilePath, {{"matching_key", matchingValue}});

    bool result = getAuditValue(testFilePath, matchingKey, matchingValue);
     EXPECT_FALSE(result);  // 预期函数返回false
}

}  // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    // Runs all tests using Google Test.
    return RUN_ALL_TESTS();
 }