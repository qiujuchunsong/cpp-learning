#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include <iostream>

// 最基础的 sales_data 类。
// 说明：拷贝构造函数/拷贝赋值运算符和运算符重载（如 operator+=、operator>>/<<）
// 由你自行实现；这里仅提供最小的成员和辅助函数。
class sales_data {
public:
    sales_data() = default;
    explicit sales_data(const std::string &s) : bookNo_(s) {}
    sales_data(const std::string &s, unsigned units, double price)
        : bookNo_(s), units_sold_(units), revenue_(units * price) {}

    // 如需自己实现拷贝函数，请在此处添加声明：
    // sales_data(const sales_data &other);
    // sales_data &operator=(const sales_data &other);

    std::string isbn() const { return bookNo_; }
    unsigned units_sold() const { return units_sold_; }
    double revenue() const { return revenue_; }
    double avg_price() const { return units_sold_ ? revenue_ / units_sold_ : 0.0; }

    // 将 rhs 合并到当前对象中（用于累加销售量/收入）
    void combine(const sales_data &rhs) {
        units_sold_ += rhs.units_sold_;
        revenue_ += rhs.revenue_;
    }

    // 条件选择函数，根据 check 函数的结果返回 bhs 或 chs(因为1hs报错(c++定义变量不能以数字或下划线开头),所以采用ahs，bhs，chs表示第一个，第二个，第三个参数)
    sales_data if_then_else(const sales_data &ahs, const sales_data &bhs, const sales_data &chs) {
        if(check_empty(ahs))
            return bhs;
        else
            return chs ;
    }

    // 便捷的 I/O 辅助函数（非运算符）。
    // 你可以基于这些函数实现 operator>> / operator<<。
    friend std::istream &operator>>(std::istream &is, sales_data &item) {
        double price = 0;
        if (is >> item.bookNo_ >> item.units_sold_ >> price) {
            item.revenue_ = item.units_sold_ * price;
        } else {
            item = sales_data(); // 读失败则重置
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const sales_data &item) {
        os << item.bookNo_ << ' ' << item.units_sold_ << ' ' << item.revenue_;
        return os;
    }

        /*
         关于 operator+ 与 operator+= 的实现建议（中文注释说明）：
         - 推荐习惯：实现成员形式的 operator+=（在原对象上就地修改），
             然后实现非成员的 operator+（通过拷贝 lhs 并调用 += 来返回新对象）。
         - 优点：operator+= 就地修改更高效；operator+ 只需一次拷贝（构造 lhs），
             再复用 operator+=，性能与异常安全性较好。
         - 反向实现（让 += 调用 +）虽然也可工作，但通常效率较差，因其会
             创建额外的临时对象并发生不必要的拷贝或赋值。
         - 流运算符（operator>> / operator<<）通常应实现为非成员函数，
             以保证左操作数为流时的对称性。
         - 比较运算应保持一致性：最好让 operator== 与基于 operator< 的等价判定一致。
        */

    // 推荐实现：将 operator+= 作为成员函数（就地修改），
    // operator+ 作为非成员函数，使用拷贝加上 += 来返回新对象。
    sales_data& operator+=(const sales_data &rhs) {
        combine(rhs);
        return *this;
    }

    friend sales_data operator+(sales_data lhs, const sales_data &rhs) {
        lhs += rhs; // reuse member operator+= for efficiency and correctness
        return lhs;
    }

    // -= 与 - 的实现：用于“撤销/退货”等场景
    // 实现策略（保守、安全）：当要减去的 units 或 revenue 超过当前值时，
    // 我们将对应字段钳位到 0（避免无符号下溢或负收入）。
    // 另一种策略是抛出异常或断言，这取决于业务需求；如果希望严格
    // 要求 rhs 不大于 lhs，请告知我，我可以改为抛出 std::runtime_error。
    sales_data& operator-=(const sales_data &rhs) {
        // 注意：这里没有检查 ISBN 是否相同，操作前最好确保作用在同一书目上
        if (rhs.units_sold_ > units_sold_) units_sold_ = 0;
        else units_sold_ -= rhs.units_sold_;

        if (rhs.revenue_ > revenue_) revenue_ = 0.0;
        else revenue_ -= rhs.revenue_;

        return *this;
    }

    friend sales_data operator-(sales_data lhs, const sales_data &rhs) {
        lhs -= rhs; // reuse operator-= for consistent semantics
        return lhs;
    }
    
    sales_data& operator++() {
        ++units_sold_;
        return *this;
    }
    
    sales_data operator++(int){
        sales_data temp =*this;
        ++*this;
        return temp;
    }

    sales_data& operator--() {
        if (units_sold_ > 0) --units_sold_;
        return *this;
    }

    sales_data operator--(int){
        sales_data temp =*this;
        --*this;
        return temp;
    }

    friend bool operator==(const sales_data &lhs, const sales_data &rhs) {
        return lhs.bookNo_ == rhs.bookNo_ && lhs.units_sold_ == rhs.units_sold_ && lhs.revenue_ == rhs.revenue_;
    }
    friend bool operator!=(const sales_data &lhs, const sales_data &rhs) {
        return !(lhs == rhs);
    }
    
    friend bool check_empty(const sales_data &hs){
        return hs.units_sold_ && hs.revenue_ && !hs.bookNo_.empty();
    }

private:
    std::string bookNo_;
    unsigned units_sold_ = 0;
    double revenue_ = 0.0;
};

#endif // SALES_DATA_H
