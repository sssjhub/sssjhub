# 2024.1.15
* 安装gtest
```bash
[root@localhost src_test]# yum install gtest* 
```

* 安装gmock
```bash
[root@localhost src_test]# yum install gmock* 
```

* 编写测试用例my_test.cpp:
```
#include <gtest/gtest.h>

int add(int lhs, int rhs) { return lhs + rhs; }

int main(int argc, char const *argv[]) {

    EXPECT_EQ(add(1,1), 2); // PASS
    EXPECT_EQ(add(1,1), 1) << "FAILED: EXPECT: 2, but given 1";; // FAILDED

    return 0;
}
```

* 通过如下命令编译测试用例:
```bash
[root@localhost src_test]# g++ my_test.cpp -o test -I /usr/include/gtest -lgtest
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