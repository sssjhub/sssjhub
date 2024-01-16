# 2024.1.15
* 安装gtest
```bash
[root@localhost ~]# yum install gtest* 
```

* 安装gmock
```bash
[root@localhost ~]# yum install gmock* 
```

* 断言
```
Fatal assertion(致命断言)           Nonfatal assertion(非致命断言)           Verifies(验证)
ASSERT_TRUE(condition);             EXPECT_TRUE(condition);                 condition is true
ASSERT_FALSE(condition);            EXPECT_FALSE(condition);                condition is false
ASSERT_EQ(val1,val2);               EXPECT_EQ(val1,val2);                   val1 == val2
ASSERT_NE(val1,val2);               EXPECT_NE(val1,val2);                   val1 != val2
ASSERT_LT(val1,val2);               EXPECT_LT(val1,val2);                   val1 < val2
ASSERT_LE(val1,val2);               EXPECT_LE(val1,val2);                   val1 <= val2
ASSERT_GT(val1,val2);               EXPECT_GT(val1,val2);                   val1 > val2
ASSERT_GE(val1,val2);               EXPECT_GE(val1,val2);                   val1 >= val2
        
ASSERT_STREQ(str1,str2);            EXPECT_STREQ(str1,_str_2);              验证两个C字符串具有相同内容
ASSERT_STRNE(str1,str2);            EXPECT_STRNE(str1,str2);                验证两个C字符串具有不同内容
ASSERT_STRCASEEQ(str1,str2);        EXPECT_STRCASEEQ(str1,str2);            验证两个C字符串具有相同内容（忽略大小写）
ASSERT_STRCASENE(str1,str2);        EXPECT_STRCASENE(str1,str2);            验证两个C字符串具有不同内容（忽略大小写）
```

* 测试宏
1.TEST() 这个宏用于定义一个具体的测试用例。TestCaseName 是测试套件的名称，TestName 是测试用例的名称。在这个宏内部编写实际的测试逻辑:
```bash
TEST(TestCaseName, TestName) {
    // 测试代码实现
}
```

2.TEST_F() 宏用于定义基于类的测试，允许你在测试之间共享数据和设置共享的setUp/tearDown方法。这里的MyTest是自定义的测试fixture类名，它继承自::testing::Test：
```bash
class MyTest : public ::testing::Test {
  protected:
    void SetUp() override { /* 设置环境 */ }
    void TearDown() override { /* 清理环境 */ }
};

TEST_F(MyTest, TestName) {
    // 测试代码实现
}

```

3.TYPED_TEST_CASE() 和 TYPED_TEST()这两个宏用于参数化测试，可以为同一个测试逻辑提供多种类型的数据输入：
```bash
typedef ::testing::Types<int, double> MyTypes;

TYPED_TEST_CASE(MyTestFixture, MyTypes);

TYPED_TEST(MyTestFixture, TestWithType) {
    // 使用TypeParam类型的测试代码
}

```

3.INSTANTIATE_TEST_SUITE_P()这个宏与参数化测试相关联，用于实例化带有特定参数值的测试fixture：
```bash
INSTANTIATE_TEST_SUITE_P(
    ParameterizedTestFixtureInstantiation,  // 名称前缀
    MyTestFixture,                          // 参数化的测试fixture类
    ::testing::Values(1, 2, 3));            // 提供参数值列表

```

* 主函数
```bash
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    // Runs all tests using Google Test.
    return RUN_ALL_TESTS();
 }
```

* 编译运行
```bash
[root@localhost ~]# g++ GtestTest.cpp GtestTest_Unittest.cpp  -o GtestTest_Unittest  -I /usr/include/gtest -lgtest
[root@localhost ~]# ./GtestTest_Unittest
[==========] Running 9 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 3 tests from FactorialTest
[ RUN      ] FactorialTest.Negative
[       OK ] FactorialTest.Negative (0 ms)
[ RUN      ] FactorialTest.Zero
[       OK ] FactorialTest.Zero (0 ms)
[ RUN      ] FactorialTest.Positive
[       OK ] FactorialTest.Positive (0 ms)
[----------] 3 tests from FactorialTest (0 ms total)

[----------] 3 tests from IsPrimeTest
[ RUN      ] IsPrimeTest.Negative
[       OK ] IsPrimeTest.Negative (0 ms)
[ RUN      ] IsPrimeTest.Trivial
[       OK ] IsPrimeTest.Trivial (0 ms)
[ RUN      ] IsPrimeTest.Positive
[       OK ] IsPrimeTest.Positive (0 ms)
[----------] 3 tests from IsPrimeTest (0 ms total)

[----------] 3 tests from FileAuditTest
[ RUN      ] FileAuditTest.ReturnsTrueForExistingAudit1
[       OK ] FileAuditTest.ReturnsTrueForExistingAudit1 (11 ms)
[ RUN      ] FileAuditTest.ReturnsFalseForNonexistentAudit0
[       OK ] FileAuditTest.ReturnsFalseForNonexistentAudit0 (18 ms)
[ RUN      ] FileAuditTest.ReturnsFalseForNonexistentAudit
[       OK ] FileAuditTest.ReturnsFalseForNonexistentAudit (12 ms)
[----------] 3 tests from FileAuditTest (41 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 3 test cases ran. (41 ms total)
[  PASSED  ] 9 tests.

```