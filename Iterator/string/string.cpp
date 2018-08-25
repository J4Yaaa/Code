#include <iostream>
using namespace std;
#include <string>

void PrintString(string& s)
{
    string::iterator its = s.begin();
    while(its != s.end())
    {
        cout<<*its<<" ";
        ++its;
    }
    cout<<endl;
}

int main()
{
    string s("hello world");
    PrintString(s);

    s.push_back('!');
    s.append("aaaaaaa");
    s += "good";
    PrintString(s);

    size_t pos = pos = s.find('!');
    if(pos != string::npos)//npos表示不存在的字符，不能与npos即找到了
    {
        s.erase(pos);//默认从 pos 删至结尾,缺省 npos，即至结尾
        /* s.erase(pos,8);//可指定长度 */
    }
    PrintString(s);

    //获取c形式字符串
    const char* p = s.c_str();
    cout<<p<<endl;

    return 0;
}
