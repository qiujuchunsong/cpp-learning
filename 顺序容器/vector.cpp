#include <iostream>
#include <vector>
int main()
{
    using namespace std;
    vector <int> v{1,2,3,4,5,6,7};
    auto begin = v.begin();
    while(begin!=v.end())
    {
        ++begin;
        begin=v.insert(begin,103);
        ++begin;
    }
    for(int i:v)
    cout<<i<<" ";
    return 0;
}
