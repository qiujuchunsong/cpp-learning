#include<numeric>//提供accumulate原型
#include<iostream>
#include<vector>
#include<algorithm>//提供fill_n(),sort(),copy(),count(),unique()原型
#include<iterator>//提供back_inserter原型
int main()
{
    using namespace std;
    vector <int> vec={1,2,5,6,78,9,1,13,143};
    vector <string> str={"Morning","Afternoon","Evening"};
    vector <string> words={"the ","quick ","red ","fox ","jumps ","over ","the ","slow ","red ","turtle "};
    vector <int> test;
    //fill_n(test.begin(),10,0);//该调用是一场灾难
    fill_n(back_inserter(test),10,0);//测试fill_n和back_inserter
    cout<<"After fill_n,test have:";
    for(int i:test)//打印测试结果
    cout<<i<<" ";
    auto b1=vec.begin();
    auto e1=vec.end();
    auto b2=str.begin();
    auto e2=str.end();//定义迭代器（多此一举）
    string str_sum=accumulate(b2,e2,string("Good"));//测试string的accumulate
    int c=count(b1,e1,1);//测试count
    int sum=accumulate(b1,e1,0);//测试int的accumulate
    cout<<endl<<"There are "<<c<<" '0' in vec"<<endl<<"The sum of whole vec is: "<<sum<<endl<<"After accumulate for string,str is: ";//打印结果
    for(char c:str_sum)//打印结果
    {
        cout<<c;       
    }
    cout<<endl;
    sort(words.begin(),words.end());//对words进行sort，后打印结果
    cout<<"After sort,words is:";
    for(string c:words)
    cout<<c;
    cout<<endl;
    auto end_unique=unique(words.begin(),words.end());//使用unique，后打印结果
    cout<<"After unique,words is:";
    for(string c:words)
    cout<<c;
    cout<<endl;
    words.erase(end_unique,words.end());//对unique后的words进行删除操作，因算法不能添加和删除容器内的元素
    cout<<"After we erased the repetitive elements of words,words is:";
    for(string c:words)
    cout<<c;
    return 0;
}
