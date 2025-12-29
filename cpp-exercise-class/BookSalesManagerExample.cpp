#include "sales_data.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<sales_data> sales_records;
    std::size_t goal_length;
    std::cout << "Enter goal length for sales records: ";
    std::cin >> goal_length;

    // 如果没有手动填充数据，这里先加入一些示例记录用于测试
    if (sales_records.empty()) {
        sales_records.push_back(sales_data("9780132350884", 2, 35.0));  // 13
        sales_records.push_back(sales_data("1234567890", 1, 10.0));     // 10
        sales_records.push_back(sales_data("abcd", 3, 5.0));            // 4
        sales_records.push_back(sales_data("6729", 4, 50.0));           // 4
    }

    // 原始写法：std::for_each 会对每个元素调用 lambda，并返回该函数对象的最终副本
    auto goal_isbn_length = std::for_each(sales_records.begin(), sales_records.end(),
        [goal_length](const sales_data &item) {
            return item.isbn().length() == goal_length;
        });

    // 直接用返回的函数对象再测试某个元素
    if (!sales_records.empty()) {
        bool match0 = goal_isbn_length(sales_records[0]);
        std::cout << "First record ISBN='" << sales_records[0].isbn() << "' matches? " << std::boolalpha << match0 << '\n';
    }

    // 更实用的校验：使用 std::count_if 统计匹配的数量
    auto count = std::count_if(sales_records.begin(), sales_records.end(),
        [goal_length](const sales_data &item) { return item.isbn().length() == goal_length; });
    std::cout << "Number of records with ISBN length " << goal_length << " = " << count << '\n';
    // 构造与读取示例
    sales_data a("978-0132350884", 2, 35.0);
    sales_data b;

    std::istringstream in("978-0132350884 3 35.0");
    operator>>(in, b); // 使用 read 而不是 operator>>（你可以之后实现 operator>>）

    // 累加
    a.combine(b);

    // 输出（你可以实现 operator<< 基于 print）
    operator<<(std::cout, a) << std::endl;

    return 0;
}
