// 引入必要的头文件
#include <iostream>    // 标准输入输出流
#include <memory>      // 智能指针
#include <vector>      // 向量容器

// employee类：表示员工，包含姓名和编号信息
class employee{
public:
    // 构造函数：初始化员工姓名，并分配员工编号
    employee(const std::string name):name(name){
        /* 注意：这里修改的是静态成员变量 */
        number = origin_number++;  // 静态成员变量的修改会影响整个类的所有对象
    }
    
    // 拷贝构造函数：复制员工姓名（编号不复制，保持原样）
    employee(const employee& e):name(e.name){}
    
    // 拷贝赋值运算符：复制员工姓名和编号
    employee& operator=(const employee& e){
        name=e.name;
        number=e.number;
        return *this;
    }
    
    // 打印函数：输出员工姓名和编号
    void print()const {std::cout<<name<<" "<<number<<std::endl;}
    
private:
    std::string name;          // 员工姓名
    /* 重要提醒：static成员变量 */
    static int number;         // 静态成员变量：所有对象共享，存储当前员工编号
    static int origin_number;  // 静态成员变量：所有对象共享，存储起始编号
    /* static成员变量注意事项：
     * 1. 静态成员不属于任何对象，而是属于整个类
     * 2. 必须在类外进行定义和初始化
     * 3. 可以通过类名直接访问（employee::number）
     * 4. 改变一个对象的静态成员会影响所有对象 */
};

// hasptr类：演示自定义拷贝控制操作，包含动态分配的字符串指针
class hasptr{
public :
    // 构造函数：初始化动态分配的字符串和整数
    hasptr(const std::string &s=std::string()):
    ps(new std::string(s)),i(0){}
    
    // 析构函数：释放动态分配的内存
    ~hasptr(){delete ps;}
    
    // 拷贝构造函数：执行深拷贝
    hasptr(const hasptr &rhs):
    ps(new std::string(*rhs.ps)), i(rhs.i) {}

    // 拷贝赋值运算符：执行深拷贝，处理自赋值情况
    hasptr& operator=(const hasptr &rhs) {
        // 创建新的副本再替换，处理自赋值情况
        std::string *new_ps = new std::string(*rhs.ps);
        delete ps;  // 释放旧资源
        ps = new_ps;
        i = rhs.i;
        return *this;
    }
    
    // 打印函数：输出存储的字符串内容
    void print()const {std::cout<<*ps<<std::endl;}
    
private:
    std::string *ps;  // 指向动态分配字符串的指针
    int i;            // 整数成员
};

// X结构体：演示默认构造、拷贝构造、析构和拷贝赋值运算符的调用
struct X{
    int i=0;  // 成员变量，默认初始化为0
    
    // 默认构造函数
    X(){std::cout<<"X()"<<std::endl;}
    
    // 拷贝构造函数
    X(const X&){std::cout<<"X(const X&)"<<std::endl;}
    
    // 析构函数
    ~X(){std::cout<<"~X()"<<std::endl;}
    
    // 拷贝赋值运算符
    X& operator=(const X&){std::cout<<"operator=(const X&)"<<std::endl; return *this;}
};

/* 重要：静态成员变量必须在类外初始化！ */
// 初始化employee类的静态成员变量 - 这是必须的，否则会导致链接错误
int employee::number = 0;         // 初始化当前员工编号为0
int employee::origin_number = 201412;  // 初始化起始编号为201412
/* 静态成员变量初始化规则：
 * 1. 必须在类外进行，类内只能声明
 * 2. 初始化格式：类型 类名::成员名 = 值;
 * 3. 初始化位置通常在源文件中，而非头文件
 * 4. 静态成员变量的生命周期贯穿整个程序 */

// 主函数：测试各个类的功能
int main()
{
    // 测试employee类的功能
    std::cout << "Testing employee class: " << std::endl;
    
    // 1. 测试构造函数
    employee e1("sean");
    std::cout << "Created employee e1: ";
    e1.print();
    
    // 2. 测试拷贝构造函数
    employee e2(e1);
    std::cout << "Copy constructed e2: ";
    e2.print();
    
    // 3. 创建另一个员工，测试编号递增功能
    employee e3("ben");
    std::cout << "Created employee e3: ";
    e3.print();
    
    // 4. 测试拷贝赋值运算符
    employee e4("darrell");
    std::cout << "Created employee e4: ";
    e4.print();
    
    e4 = e1;
    std::cout << "After e4 = e1: ";
    e4.print();
    
    // 再测试一个员工，验证编号序列
    employee e5("watson");
    std::cout << "Created employee e5: ";
    e5.print();
    
    std::cout << "Testing completed" << std::endl;
    
    // 以下是X结构体和hasptr类的测试代码
    X x1;                                      // 创建X对象，调用默认构造函数
    X x2=x1;                                   // 拷贝初始化，调用拷贝构造函数
    X* x3 = &x1;                               // 创建指向x1的裸指针（不调用构造函数）
    std::shared_ptr<X> x4 = std::make_shared<X>(x1);  // 创建共享指针指向X对象的拷贝
    std::vector<X> x5(2,x1);                   // 创建包含2个x1拷贝的vector
    
    hasptr h0("hello world >.<");              // 创建hasptr对象
    hasptr h1("hello");                        // 创建hasptr对象
    hasptr h2=h1;                              // 拷贝初始化，调用拷贝构造函数
    hasptr h3("world");                        // 创建hasptr对象
    
    h2.print();                                // 打印h2的内容
    h3.print();                                // 打印h3的内容
    h1=h0;                                     // 拷贝赋值，调用拷贝赋值运算符
    h1.print();                                // 打印h1的内容
    
    return 0;  // 程序正常结束
}
