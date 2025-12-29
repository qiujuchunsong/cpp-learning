/* ========================================
 * 程序：运算符重载和隐式类型转换示例
 * 原始代码存在4个错误，已全部修正
 * ======================================== */

#include<iostream>

class SmallInT{
    friend SmallInT operator+(const SmallInT &, const SmallInT &);
    public:
    SmallInT(int =0);
    
    // 转换运算符：将SmallInT对象隐式转换为int
    operator int() const {return val;};
    
    private:
    // 错误1：原代码使用 std::size_t val;
    // ❌ 问题：std::size_t是无符号整数类型，不适合存储有符号int值
    //        在转换运算符中会导致类型不匹配
    // ✅ 改正：改为 int val;
    int val;
};

// 错误2：构造函数声明但没有实现
// ❌ 问题：类中只有声明 SmallInT(int =0);，缺少函数体
//        编译器会报链接错误：undefined reference to `SmallInT::SmallInT'
// ✅ 改正：提供构造函数实现
SmallInT::SmallInT(int v) : val(v) {}

// 错误3：友元运算符声明但没有实现
// ❌ 问题：类中声明了 friend operator+，但程序中没有定义
//        编译器会报链接错误，无法生成可执行文件
// ✅ 改正：实现友元运算符，执行两个SmallInT对象的相加
SmallInT operator+(const SmallInT &a, const SmallInT &b) {
    return SmallInT((int)a + (int)b);
}

int main()
{
    SmallInT s1;  // 创建SmallInT对象，初始值为0（默认参数）
    
    // 错误4：操作数类型歧义导致编译错误
    // ❌ 原代码：double d = s1 + 3.14;
    //    问题：编译器有两种可能的解释
    //    选项A：s1(SmallInT) → int，然后 int + double（内置operator+）
    //    选项B：3.14(double) → SmallInT，然后 SmallInT + SmallInT（自定义operator+）
    //    两种转换都可行，编译器无法决定，报错：ambiguous overload for 'operator+'
    // ✅ 改正：显式转换消除歧义
    //    使用 (int)s1 + 3.14 明确指定s1转换为int，使用内置的 int+double 运算
    double d = (int)s1 + 3.14;
    std::cout << d << std::endl;
    return 0;
}
