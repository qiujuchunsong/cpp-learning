#include <iostream>
#include <string>
#include <vector>
class Quote{
public:
    Quote() = default;//默认构造函数
    Quote(const std::string &book,double sales_price)
        :bookNo(book),price(sales_price) {}
    std::string isbn() const {return bookNo;}
    virtual double net_price(std::size_t n) const {return n * price;}//virtual表明该函数可以被派生类重写
    virtual ~Quote() = default;//虚析构函数
    //基类都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此
    virtual void debug() const{
        std::cout << "bookNo: " << bookNo << " price: " << price << std::endl;
    }
private:
    std::string bookNo;
protected:
    double price = 0.0;
};
class Disc_quote : public Quote{
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book,double price,std::size_t qty, double disc)
    :Quote(book,price),quantity(qty),discount(disc) {}
    double net_price(std::size_t cnt) const = 0;//纯虚函数
protected:
    std::size_t quantity = 0;
    double discount = 0.0;        
};
class Bulk_quote : public Disc_quote{//访问说明符可选，默认是private继承
public:
    Bulk_quote() = default;//默认构造函数
    Bulk_quote(const std::string& book,double p,std::size_t qty,double disc)
        :Disc_quote(book,p,qty,disc) {}//首先初始化基类部分(使用基类的构造函数)
        //然后按声明顺序初始化派生类成员(使用派生类的初始化列表--min_qty()和discount()更高效)
    double net_price(std::size_t cnt) const override{
        if(cnt >= min_qty){
            return cnt * (1-discount) * price;
        }
        else{
            return cnt * price;
        }
    };//override表明该函数重写了基类的虚函数
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n){
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl; // "<<" 两边应有空格
    return ret;
}
int main(){
    Quote base("10086",50);
    print_total(std::cout,base,10);
    Bulk_quote derived("10010",50,5,0.2);
    print_total(std::cout,derived,10);
    return 0;
}
//2025.12.29
//学习了C++中的类继承与多态(虚函数，抽象基类，访问控制与继承)

/* ==================== 今日学习要点总结 ==================== */

// 1. final 和 override
//    - 推荐同时使用：final override（获得类型安全检查）
//    - final隐含重写，但override提供编译器验证防止拼写错误

// 2. 抽象基类
//    - 含有纯虚函数(= 0)的类，不能实例化
//    - 作用：强制派生类实现接口、统一多态接口、表达设计意图

// 3. protected 成员访问规则
//    - 派生类可以直接访问自己继承的 protected 成员 ✓
//    - 派生类不能通过基类对象访问其 protected 成员 ✗

// 4. 三种继承方式
//    - public 继承：保持原访问权限（is-a关系，最常用）
//    - protected 继承：public降为protected（限制接口但保留继承链）
//    - private 继承：全部降为private（has-a实现方式）

// 5. is-a vs has-a
//    - is-a：类型归属关系，用 public 继承实现（Dog is-a Animal）
//    - has-a：组合关系，用成员变量实现（Car has-a Engine）

// 6. using 声明在继承中的用法
//    - 解决名字隐藏：using Base::func; 引入基类同名函数的所有重载
//    - 改变访问权限：将 protected/private 成员提升为 public

// 7. 成员访问说明符 vs 派生访问说明符
//    - 成员访问说明符：public/protected/private，控制类成员的访问权限
//    - 派生访问说明符：: public/protected/private，控制继承方式
//    - struct 默认 public，class 默认 private

// 8. 派生类可以替换基类（里氏替换原则）
//    - 基类指针/引用可以指向派生类对象
//    - 前提：派生类满足基类契约，不违反基类不变量
//    - 应用：多态容器、策略模式、依赖注入

// 9. 内存保证
//    - 派生类成员数量 ≥ 基类成员数量（永远不会更少）
//    - 派生类对象包含完整的基类子对象
//    - 这是类型安全和向上转换的内存基础

/* ========================================================== */
