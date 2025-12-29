#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
using namespace std;
class StrBlob{
public:
   typedef std::vector<std::string> ::size_type size_type;
   StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
   StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}
   size_type size() const {return data->size();}
   bool empty() const {return data->empty();}
   void push_back(const std::string &t) {data->push_back(t);}
   void pop_back() {
       check(0, "pop_back on empty StrBlob");
       data->pop_back();
   }
   std::string& front() {
       check(0, "front on empty StrBlob");
       return data->front();
   }
   std::string& back() {
       check(0, "back on empty StrBlob");
       return data->back();
   }
   
private:
   std::shared_ptr<std::vector<std::string>> data;
   void check(size_type i, const std::string &msg) {
       if (i >= data->size()) {
           throw std::out_of_range(msg);
       }
   }
};

int main() {
    StrBlob blob1;
    blob1.push_back("Hello");
    blob1.push_back("World");
    
    StrBlob blob2 = {"C++", "Programming", "Language"};
    
    cout << "Blob1 size: " << blob1.size() << endl;
    cout << "Blob1 front: " << blob1.front() << endl;
    cout << "Blob1 back: " << blob1.back() << endl;
    
    cout << "Blob2 size: " << blob2.size() << endl;
    cout << "Blob2 front: " << blob2.front() << endl;
    cout << "Blob2 back: " << blob2.back() << endl;
    
    blob1.pop_back();
    cout << "After pop_back, blob1 size: " << blob1.size() << endl;
    
    return 0;
}
