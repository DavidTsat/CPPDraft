#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {

public:
    string multiply(string n1, string n2) {
        int l = 0;
        string res;
        if (n1.size() > n2.size()) n1.swap(n2);

        for (int j = n2.size() - 1; j >= 0; --j)
        {
            int s = 0;
            string s_i;
            for (int i = n1.size() - 1; i >= 0; --i)
            {
                int i1 = n1[i] - '0'; // move
                int j2 = n2[j] - '0'; // fixed

                int c = i1 * j2;

                int r = s + c;
                if (i == 0)
                {
                    if (r > 0)
                    {
                        while (r)
                        {
                            int rr = r % 10;
                            //v_i.push_back(rr);
                            s_i = char('0' + rr) + s_i;
                            r /= 10;
                        }
                    }

                    else
                    {
                        s_i = '0';
                    }

                    continue;
                }
                if (r >= 10)
                {
                    s_i = char('0' + r % 10) + s_i;
                    s = r / 10;
                }
                else
                {
                    s_i = char('0' + r) + s_i;
                    if (s) s = 0;
                }
            }
            if (res.empty())
            {
                res = s_i;
            }
            else
            {
                s = 0;
                int p = s_i.size() - 1;

                int res_i = res.size() - n2.size() + j;


                for (int i = s_i.size() - 1; i >= 0; --i)
                {
                    if (res_i >= 0)
                    {
                        int s_int = res[res_i] - '0';
                        int res_int = s_i[i] - '0';
                        int ccc = s + s_int + res_int;
                        if (ccc >= 10)
                        {
                            res[res_i] = '0' + ccc % 10;
                            if (s == 0) ++s;
                        }
                        else
                        {
                            if (s > 0) s = 0;
                            res[res_i] = '0' + ccc;
                        }
                    }
                    else
                    {
                        string s_b = "";
                        for (int ii = i; ii >= 0; --ii)
                        {
                            int s_int = s_i[ii] - '0';
                            int ccc = s_int + s;
                            if (ccc >= 10)
                            {
                                s_b = char('0' + ccc % 10) + s_b;
                               
                                if (s == 0) ++s;
                            }
                            else
                            {
                                if (s > 0) --s;
                                s_b = char('0' + ccc) + s_b;
                            }
                        }
                        res = s_b + res;
                        break;
                    }
                    --res_i;
                }
                if (s > 0) res = char('0' + s) + res;
            }

        }


        if (res.size() > 1 && res[0] == '0')
        {
            int i = res.size() - 1;
            while (res[i] == '0' && i > 0) --i;
            res = res.substr(0, i + 1);
        }
        return res;
    }
};

int main()
{
    Solution s;
    string s1 = "123";
    string s2 = "4567";
    string s3 = "0";
    string s4 = "123456789";
    string s5 = "987654321";
    string s6 = "408"; //"5" - "2040"
    string s7 = "61";
    string s8 = "186";
    string s9 = "17039";
    string s10 =  "7218";
    cout << s.multiply(s1, s2) << endl;
    cout << "121932631112635269" << endl;
    cout << "122987502" << endl;
    return 0;
}