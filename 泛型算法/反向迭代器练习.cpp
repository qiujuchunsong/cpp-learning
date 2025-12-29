//使用反向迭代器
#include<iostream>
#include<iterator>
#include<vector>
#include<algorithm>
int main()
{
    using namespace std;
    vector<string> str;
    string input;
    while(getline(cin,input) && !input.empty())
    {
        str.push_back(input);
    }
    for(auto r_iter=str.crbegin();r_iter!=str.crend();++r_iter)
    cout<<*r_iter<<" ";
    return 0;
}
