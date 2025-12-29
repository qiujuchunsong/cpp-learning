#include <iostream>
#include <vector>
int main()
{
    using namespace std;
    int i=0;//创建一个循环变量
    vector <int> ivec;
    ivec.reserve(30);//要求为ivec预留至少30个int的内存空间
    auto first_b=ivec.begin(),first_e=ivec.end();//定义两个迭代器，指向一开始的begin和end
    cout<<&first_b<<" "<<&first_e<<" ivec: size:"<<ivec.size()
        <<" ivec capacity:"<<ivec.capacity()<<endl;//打印ivec此时的size和capacity，迭代器对应的地址
    for(vector<int>::size_type ix=0;ix!=24;ix++)//输入24个值
    {
        ivec.push_back(ix);
    }
    auto second_b=ivec.begin();//构建迭代器，指向插入24个元素后的ivec的begin
    cout<<&second_b<<" ivec: size:"<<ivec.size()
        <<" ivec capacity:"<<ivec.capacity()<<endl;//打印ivec此时的size和capacity，迭代器对应的地址
    while(ivec.size()!=ivec.capacity())//填满ivec
         ivec.push_back(0);
    auto third_b=ivec.begin();//构建迭代器，指向填满后的ivec的begin
    cout<<&third_b<<" ivec: size:"<<ivec.size()
        <<" ivec capacity:"<<ivec.capacity()<<endl;//打印ivec此时的size和capacity，迭代器对应的地址
    ivec.push_back(1);//ivec满之后再插入元素
    auto fourth_b=ivec.begin();//构建迭代器，指向“搬新家”的ivec的begin
    cout<<&fourth_b<<" ivec: size:"<<ivec.size()
        <<" ivec capacity:"<<ivec.capacity()<<endl;//打印ivec此时的size和capacity，迭代器对应的地址
    while(i!=3)//一个循环，使ivec的内存空间翻4倍
    {
        ivec.push_back(0);
        if(ivec.size()==ivec.capacity())
        {
            ivec.reserve(ivec.capacity());
            i++;
        }
    }
    auto fifth_b=ivec.begin(),last_e=ivec.end();//构建一组迭代器，指向多次扩容后的ivec的begin和end
     cout<<&fifth_b<<" "<<&last_e<<" ivec: size:"<<ivec.size()
        <<" ivec capacity:"<<ivec.capacity()<<endl;//打印ivec此时的size和capacity，迭代器对应的地址
    return 0;
}