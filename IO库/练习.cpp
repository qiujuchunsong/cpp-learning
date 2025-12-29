#include <iostream>
#include <string>
#include <sstream>//提供istringstream原型
#include <vector>
using namespace std;
struct person_info//创建person_info结构，存储姓名和电话号码，电话号码使用vector数组存储
{
    string name;
    vector <string> phones;
};
int main()
{
    string line,word;//分别保存来自输入的一行和单词
    vector <person_info> people;//保存来自输入的数据
    while(getline(cin,line)&&line!="")
    {
        person_info info;
        std::istringstream record(line);//将记录绑定到刚输入的行
        record>>info.name;//读取名字
        while(record>>word)//读取电话号码
        {
            info.phones.push_back(word);
            people.push_back(info);
        }
    }
    for(auto c:people)//使用两个范围for循环分别打印名字和电话号码
    {
        cout<<c.name<<" ";
        for(auto p:c.phones)
        {
            cout<<p;
        }
        cout<<endl;
    }
    return 0;
}
