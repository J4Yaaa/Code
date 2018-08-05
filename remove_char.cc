// 输入两个字符串,从第一个字符串中删除第二个字符串中所有字符
// 如: "They are students" 和 "aeiou"
// 删除以后: "They r stdnts"

#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
#include <vector>

// void remove_char_of_str2(string& str1,const string& str2)
// {
//     string::iterator itb = str1.begin();
//     string::iterator ite = str1.end();
//     size_t str2_size = str2.size();
//     for(size_t i = 0; i < str2_size; ++i)
//     {
//         while(itb != ite)
//         {
//             string::iterator it = find(itb,ite,str2[i]);
//             if(it != str1.end())
//             {
//                 str1.erase(it);
//             }
//             itb = it;
//         }
//     }
// }

void remove_char_of_str2(string& str1,const string& str2)
{
    vector<int> v(256,0);
    size_t s1 = str1.size();
    size_t s2 = str2.size();
    string res;
    for(size_t i = 0; i < s2; ++i)
    {
        v[str2[i]] = 1;
    }
    for(size_t i = 0; i < s1; ++i)
    {
        if(v[str1[i]] == 0)
        {
            res += str1[i];
        }
    }
    cout<<res<<endl;
}

int main()
{
    string str1,str2;
    while(getline(cin,str1) && getline(cin,str2))
    {
        remove_char_of_str2(str1,str2);
    }
    return 0;
}
