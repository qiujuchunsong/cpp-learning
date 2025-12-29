// 屏幕类实现文件 - 提供二维字符屏幕的模拟，支持字符设置和清空操作
#include<iostream>
#include<string>
using namespace std;

// Screen类：模拟二维字符屏幕，管理屏幕上的字符显示
class screen {
public:
    // 定义位置类型为字符串大小类型
    typedef std::string::size_type pos;
    
    // 声明clear为友元函数，允许其访问私有成员
    friend void clear(screen::pos row, screen::pos col, screen &s);
    
    // 默认构造函数
    screen()=default;
    
    // 带参构造函数，初始化屏幕高度、宽度和所有字符
    // @param ht: 屏幕高度（行数）
    // @param wd: 屏幕宽度（每行字符数）
    // @param c: 初始化字符
    screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd,c) {}
    
    // 获取当前光标位置的字符
    // @return: 当前光标位置的字符
    char get() const { return contents[cursor]; }
    
    // 获取指定位置(ht, wd)的字符
    // @param ht: 行号
    // @param wd: 列号
    // @return: 指定位置的字符
    char get(pos ht, pos wd) const { 
        pos row = ht * width;  // 计算行起始位置
        return contents[row + wd];  // 计算总偏移量并返回字符
    }
    
    // 移动光标到指定位置
    // @param r: 目标行号
    // @param c: 目标列号
    // @return: 屏幕对象的引用，支持链式调用
    screen &move(pos r, pos c) { 
        pos row = r * width;  // 计算行起始位置
        cursor = row + c;  // 计算总偏移量并设置光标位置
        return *this;  // 返回自身引用支持链式调用
    }
    
    // 在当前光标位置设置字符
    // @param c: 要设置的字符
    // @return: 屏幕对象的引用，支持链式调用
    screen &set(char c) { 
        contents[cursor] = c;  // 在光标位置设置字符
        return *this;  // 返回自身引用支持链式调用
    }
    
    // 显示屏幕内容到输出流
    // @param os: 输出流对象
    // @return: 屏幕对象的引用，支持链式调用
    screen display(std::ostream &os) { 
        int i = 0;
        for(char c : contents) {  // 遍历所有字符
            os << c;  // 输出字符
            i++;
            if(i % width == 0)  // 每行结束时输出换行
                os << endl;
        }
        return *this;  // 返回自身引用支持链式调用
    }
    
private:
    pos cursor;  // 当前光标位置
    pos height = 0;  // 屏幕高度
    pos width = 0;   // 屏幕宽度
    std::string contents;  // 存储屏幕内容的一维字符串
};

// 清空屏幕上指定位置的字符（将其设为空格）
// @param row: 要清空的行号
// @param col: 要清空的列号
// @param s: 要操作的屏幕对象引用
void clear(screen::pos row, screen::pos col, screen &s) {
    // 检查坐标是否有效
    if(row < s.height && col < s.width) {
        // 计算一维索引并清空指定位置（将字符设为空格）
        s.contents[row * s.width + col] = ' ';
    }
}

// 主函数：演示屏幕类的使用
int main() {
    int i, j;  // 用于存储用户输入的行列坐标
    
    // 创建一个5x5的屏幕，初始字符为'X'
    screen my_screen(5, 5, 'X');
    
    // 提示用户输入要设置为'Y'的位置
    cout << "Enter the position you want to set:" << endl;
    cin >> i >> j;
    
    // 将指定位置设置为'Y'（注意数组索引从0开始，所以减1）
    my_screen.move(screen::pos(i-1), screen::pos(j-1)).set('Y');
    
    // 显示屏幕内容
    my_screen.display(cout);
    cout << endl;
    
    // 使用get函数获取并显示指定位置的字符
    cout << "Enter a position to get the character:" << endl;
    cin >> i >> j;
    // 检查坐标有效性并获取字符
    if(i > 0 && i <= 5 && j > 0 && j <= 5) {
        char ch = my_screen.get(screen::pos(i-1), screen::pos(j-1));
        cout << "The character at position (" << i << "," << j << ") is: '" << ch << "'" << endl;
    } else {
        cout << "Invalid position!" << endl;
    }
    cout << endl;
    
    // 提示用户输入要清空的位置
    cout << "Enter the position you want to clear:" << endl;
    cin >> i >> j;
    
    // 清空指定位置的字符
    clear(screen::pos(i-1), screen::pos(j-1), my_screen);
    
    // 显示清空后的屏幕内容
    my_screen.display(cout);
    cout << endl;
    
    return 0;  // 程序正常结束
}
