#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>//提供bind原型
using namespace std;
using namespace placeholders;//使用定位符_n
bool check_size(const string &str,string::size_type sz)//比较字符串长度的函数，返回值为bool型
{return str.size()>=sz;}
string make_plural (size_t str,const string &word,const string &s)//判断字符串长度是否为一，决定使用word还是words
{
    return (str+1)?word+s:word;
}
void elimDups(vector<string> &words)//排序并删除重复元素
{
    sort(words.begin(),words.end());
    auto end_unique=unique(words.begin(),words.end());
    words.erase(end_unique,words.end());
}
void biggies(vector <string> &words,vector <string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(),words.end(),[](const string &a,const string &b){return a.size()<b.size();});//保留等长元素间的典序
    auto wc=find_if(words.begin(),words.end(),[sz](const string &words){return words.size()>=sz;});//查找满足长度大小的元素，记录其位置
    auto count=words.end()-wc;//计算满足条件元素数目
    cout<<count<<" "<<make_plural(count,"word","s")<<" of length "<<sz<<" or longer"<<endl;
    for_each(wc,words.end(),[](const string &s){cout<<s<<" ";});//打印
    cout<<endl;
}
int main()
{
   vector <string> str;
   string input;
   int i;
   //auto check3=bind(check_size,_1,3);//该语句等效于[sz](const string &words){return words.size()>=sz}
   cout<<"Enter your words for compare"<<endl;
   while(getline(cin,input) && !input.empty())//读取字符串，直至读取到空字符串
   {
    str.push_back(input);
   }
   cout<<"Enter a number,any word'length less than that number will be erased"<<endl;
   cin>>i;
   biggies(str,i);
   return 0;
   
}
