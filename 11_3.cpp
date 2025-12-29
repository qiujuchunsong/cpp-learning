#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
int main()
{
    map<string,size_t> word_count;
    string word;
    while(getline(cin,word) && !word.empty())
    ++word_count[word];
    for(const auto&w:word_count)
    {
      cout<<w.first<<" occurs "<<w.second<<((w.second>1)?" times":" time")<<endl;
    }
    if(word_count.at("a"))
    cout<<"we have a !"<<endl;
    map<int,int> m={{3,0},{5,1},{5,2},{5,3},{7,0}};
    cout<<m.lower_bound(5)->second<<" "<<m.upper_bound(5)->second<<endl;
    return 0;
}