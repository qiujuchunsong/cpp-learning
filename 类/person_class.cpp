// 文件名: 7.1_person class.cpp
// 功能: 定义并实现一个简单的person类，演示类的基本概念、友元函数和对象的使用

#include<iostream>
#include<string>
using namespace std;
class person
{
    // 声明readdetail为友元函数，使其可以访问类的私有成员
    friend void readdetail(person &p, const string &name, const string &address);
    string name;
    string address;
    public: 
    // 带参构造函数
    // 功能：初始化person对象的name和address成员变量
    // 参数：
    //   prog_name - 要设置的人名
    //   prog_address - 要设置的地址
    person(string prog_name, string prog_address){
        name = prog_name;
        address = prog_address;
    }
    person() = default;
    
    // 成员函数，返回包含name和address的详细信息字符串
    string detail(){
        return name + " " + address;
    }
};

// 友元函数的实现，用于读取外部数据并设置person对象的私有成员
// 参数: 
//   - p: person类的引用，要修改的对象
//   - name: 要设置的姓名
//   - address: 要设置的地址
void readdetail(person &p, const string &name, const string &address){
    p.name = name;
    p.address = address;
}

int main()
{
    string name, add;
    
    // 创建两个person对象：一个使用默认构造函数，一个使用带参构造函数
    person NO_1;              // 默认构造函数创建的对象，name和address为空
    person NO_2("YEAH", "HPU");  // 带参构造函数创建的对象，初始化name为YEAH，address为HPU
    
    // 提示用户输入姓名和地址
    cout << "Enter your name and address please: ";
    cin >> name >> add;       // 读取用户输入
    
    // 调用友元函数设置第一个对象的成员变量
    readdetail(NO_1, name, add);
    
    // 输出两个对象的详细信息
    cout << NO_1.detail() << endl;  // 输出第一个对象（用户输入）的信息
    cout << NO_2.detail() << endl;  // 输出第二个对象（初始化值）的信息
    
    return 0;  // 程序正常结束
}

