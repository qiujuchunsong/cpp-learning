//使用list成员函数版本的sort和unique
#include<list>
#include<iostream>
#include<algorithm>
int main()
{
    using namespace std;
    list <string> s_list={"a","man","called","spiderman","is","a","fail","man"};
    s_list.sort();
    for(const auto& c:s_list)
    cout<<c<<" ";
    cout<<endl;
    s_list.unique();
    for(const auto& c:s_list)
    cout<<c<<" ";
    return 0;

}