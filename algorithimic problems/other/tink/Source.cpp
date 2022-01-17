//Есть матрица NxN, состоящая из 0 и 1,
// и отражающая расположения кораблей на поле для морского боя.

// 1. Кораблей может быть любое количество
// 2. Размер кораблей — от 1х1 до 1хN
// 3. Корабли никак не соприкасаются друг с другом. 
// 4. Корабли располагаются горизонтально и вертикально

// Необходимо подсчитать количество кораблей.



//Есть скобочное выражение с разными видами скобок {}, (), [], <>. 
//Проверить, что оно правильное. Других символов, кроме скобок, быть не может. 

// ([{}]) -> true
// ([[}]) -> false

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool check(const string& v)
{
    stack<char> s;

    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        if (*it == '(' || *it == '[' || *it == '{')
        {
            s.push(*it);
        }
        else
        {
            if (s.empty()) return false;
            char c = s.top();
            s.pop();
            switch (*it)
            {
            case ']':
                if (c != '[') return false;
                break;
            case ')':
                if (c != '(') return false;
                break;
            case '}':
                if (c != '{') return false;
                break;
            }
        }
    }
    return true;
}

// 1, 0, 0, 1,
// 0, 0, 0, 0,
// 1, 0, 1, 1,
// 1, 0, 0, 0
// 3
int count(const std::vector<std::vector<char>>& v)
{
    int count_ = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
        {
            if (v[i][j] == '0') continue;

            if (i == 0 && (j == 0 || v[i][j - 1] == '0'))
            {
                ++count_;
                continue;
            }

            if (j == 0 && (i == 0 || v[i - 1][j] == '0'))
            {
                ++count_;
                continue;
            }

            if (v[i - 1][j] == '0' && v[i][j - 1] == '0')
            {
                ++count_;
                continue;
            }
            /*
            if (i == 0 || (v[i-1][j] == '0' && v[i][j-1] == '0') || ((j == 0 && v[i-1][v.size()-1] == '0') || (j > 0 && v[i][j-1] == '0')))
            {
              ++count_;
            }
            */
        }
    }
    return count_;
}


int main() {
    vector<vector<char>> v{
                            {'0','0','0','0'},
                            {'0','0','0','0'},
                            {'0','0','0','0'},
                            {'1','1','1','1'}
    };

    cout << count(v) << endl;
    //  string s("()()()((()))");
     // cout << check(s) <<endl;
    cout << "Hello";
    return 0;
}
