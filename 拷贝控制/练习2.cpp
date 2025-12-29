#include <iostream>
#include <string>
#include <new>
class HasPtr_1{
    friend void swap(HasPtr_1 &,HasPtr_1 &);
    private:
        std::string *ps;
        int i;
    public: 
        // 构造函数：在堆上分配一个新的 std::string 并以 s 初始化，
        // i 初始化为 0
        HasPtr_1(const std::string &s= std::string()):
        ps(new std::string(s)),i(0){}

        // 析构函数：释放 ps 指向的内存，避免内存泄漏
        ~HasPtr_1(){delete ps;}

        // 拷贝构造（深拷贝）：为新对象分配一份独立的字符串副本，
        // 这样每个对象拥有自己的内存，避免双重释放问题
        HasPtr_1(const HasPtr_1 &rhs):
        ps(new std::string(*rhs.ps)),i(rhs.i){}

        // 拷贝赋值运算符：采用先分配再释放的策略（强异常安全），
        // 先申请新内存（可能抛出异常），申请成功后再删除旧内存并替换，
        // 这样在分配失败时原对象保持不变，并能正确处理自赋值
        HasPtr_1& operator=(const HasPtr_1 &rhs){
            auto newp=new std::string(*rhs.ps);
            delete ps;
            ps=newp;
            i=rhs.i;
            return *this;
        };
};
inline 
void swap(HasPtr_1 &lhs,HasPtr_1 &rhs){
    using std::swap;
    swap(lhs.ps,rhs.ps);
    swap(lhs.i,rhs.i);
}
class HasPtr_2{
    private:
    std::string *ps;
    int i;
    std::size_t *use;
    public:
    HasPtr_2(const std::string &s=std::string()):
    ps(new std::string(s)),i(0),use(new std::size_t(1)){}
    ~HasPtr_2(){
        if(--*use==0)
        {delete ps; delete use;}
    }
    HasPtr_2(const HasPtr_2 &rhs):ps(rhs.ps),i(rhs.i),use(rhs.use){
        ++*use;
    }
    HasPtr_2& operator=(const HasPtr_2 &rhs){
        ++*rhs.use;//如果use不是指针类型，则这里不能对use进行++操作，可能会导致未定义行为
        if(--*use==0)
        {delete ps; delete use;};
        ps=rhs.ps;
        i=rhs.i;
        use=rhs.use;
        return *this;
    }
};
