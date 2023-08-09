#include <bits/stdc++.h>
using namespace std;

class String
{
public:
/**
* BM83 字符串变形
* 描述：对对子串做一些变形，这个字符串中由空格隔开的单词反序，同时反转每个字符的大小写
* 要求：空间复杂度O(n) 时间复杂度O(n)
*
* 
* @param s string字符串 
* @param n int整型 
* @return string字符串
*/
string trans(string s, int n) {
    vector<string> vs;
    string tmp;
    for(int i = 0; i < n; ++ i) {
        char ch = s[i];
        if(ch == ' ') {
            vs.push_back(tmp);
            tmp.clear();
            continue;
        }
        if(ch >= 'a' && ch <= 'z') ch -= 32;
        else ch += 32;
        tmp.push_back(ch);
    }
    vs.push_back(tmp);
    reverse(vs.begin(), vs.end());
    string ans;
    for(int i = 0; i < vs.size(); ++ i) {
        ans += vs[i];
        if(i < vs.size() - 1) ans += " ";
    }
    return ans;
}
/**
 * BM84 最长公共前缀
 * 描述：给你一个大小为 n 的字符串数组 strs ，其中包含n个字符串 , 编写一个函数来查找字符串数组中的最长公共前缀，返回这个公共前缀。
 * 数据范围： 0 <= n <= 5e3 0 <= len(str[i]) <= 5e3
 * 要求：空间复杂度O(1) 时间复杂度O(n * len)
 *
 * 
 * @param strs string字符串vector 
 * @return string字符串
 */
string longestCommonPrefix(vector<string>& strs) {
    string ans;
    int len = 0;
    int n = strs.size();
    if(n == 0) return ans;
    while(true) {
        bool flag = true;
        if(len >= strs[0].size()) break;
        for(int i = 1; i < n; ++ i) {
            if(len >= strs[i].size() || strs[i][len] != strs[i - 1][len]) {
                flag = false;
                break;
            }
        }
        if(!flag) break;
        ans += strs[0][len];
        ++ len;
    }
    return ans;
}
/**
 * BM85 验证IP地址
 * 
 *
 * 验证IP地址
 * @param IP string字符串 一个IP地址字符串
 * @return string字符串
 */
string solve(string IP) {
    int n = IP.size();

    function<bool(string)> judge1;
    judge1 = [&](string s) {
        int n = s.size();
        if(n  && s[0] == '0') return false;
        int x = 0; 
        for(int i = 0; i < n; ++ i) {
            x = 10 * x + (s[i] - '0');
        }
        return x <= 255;
    };

    function<bool(string)> isIPv4;
    isIPv4 = [&](string s) {
        for(int i = 0; i < n; ++ i) {
            if(!isdigit(s[i]) && s[i] != '.') return false;
        }
        string str;
        for(int i = 0; i < n; ++ i) {
            if(s[i] == '.') {
                if(!judge1(str)) return false;
                str.clear();
            }
            else {
                str += s[i];
            }
        }
        return judge1(str);
    };

    function<bool(string)> isIPv6;
    isIPv6 = [&](string s) {
        vector<string> ip;
        string str;
        for(int i = 0; i < n; ++ i) {
            if(s[i] == '.') return false;
            if(s[i] == ':') {
                ip.push_back(str);
                str.clear();
            }
            else {
                str += s[i];
            }
        }
        ip.push_back(str);
        if(ip.size() != 8) return false;
        for(int i = 0; i < 8; ++ i) {
            if(ip[i].size() == 0 ||  ip[i].size() > 4) return false;
            for(int j = 0; j < ip[i].size(); ++ j) {
                char ch = ip[i][j];
                if(isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) continue;
                return false;
            }
        }
        return true;
    };

    if(isIPv4(IP)) {
        return "IPv4";
    }
    if(isIPv6(IP)) {
        return "IPv6";
    }
    return "Neither";
}
/**
 * BM86 大数加法
 * 描述：以字符串的形式读入两个数字，编写一个函数计算它们的和，以字符串形式返回。
 * 数据范围： s.len, t.len <= 1e5
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 * 计算两个数之和
 * @param s string字符串 表示第一个整数
 * @param t string字符串 表示第二个整数
 * @return string字符串
 */
string bigNumberAdd(string s, string t) {
    int n = s.size(); int m = t.size();
    if(n == 0) return t;
    if(m == 0) return s;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    if(n < m) {
        swap(n, m); swap(s, t);
    }
    int add = 0;
    string ans;
    int a, b;
    for(int i = 0; i < m; ++ i) {
        a = s[i] - '0'; b = t[i] - '0';
        add += (a + b);
        ans.push_back('0' + add % 10);
        add /= 10;
    }
    for(int i = m; i < n; ++ i) {
        add += (s[i] - '0');
        ans.push_back('0' +add % 10);
        add /= 10;
    }
    if(add) ans.push_back('0' + add);
    reverse(ans.begin(), ans.end());
    return ans;
}

/**
 * 大数取绝对值
 * 描述：以字符串的形式读入两个数字，表示两个正整数，编写一个函数计算它们的和，以字符串形式返回。
 * 数据范围： s.len, t.len <= 1e5
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 * 计算两个数绝对值
 * @param s string字符串 表示第一个整数
 * @param t string字符串 表示第二个整数
 * @return string字符串
 */
string bigNumberAbs(string s, string t) {
    int n = s.size(); 
    int m = t.size();
    if(n == 0) return t;
    if(m == 0) return s;
    int flag = 0;
    if(n > m) flag = 1;
    if(n < m) flag = -1;
    else {
        for(int i = 0; i < n; ++ i) {
            if(s[i] == t[i]) continue;
            if(s[i] > t[i]) {
                flag = 1; break;
            }
            if(s[i] < t[i]) {
                flag = -1; break;
            }
        }
    }
    if(flag == 0) return "0";
    if(flag < 0) {
        swap(n, m); swap(s, t);
    }
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    string ans;
    int add = 0;
    int a, b, x;
    for(int i = 0; i < m; ++ i) {
        a = s[i] - '0'; b = t[i] - '0';
        x = a - b - add;
        if(x < 0) {
            x += 10;
            add = 1;
        }
        else {
            add = 0;
        }
        ans.push_back('0' + x);
    }
    for(int i = m; i < n; ++ i) {
        x = s[i] - '0' - add;
        if(x < 0) {
            x += 10;
            add = 1;
        }
        else {
            add = 0;
        }
        ans.push_back('0' + x);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
};
int main()
{
    string s, t; cin >> s >> t;
    String sol;
    cout << sol.bigNumberAbs(s, t) << endl;

    return 0;
}
/*
172.16.254.1
2001:0db8:85a3:0:0:8A2E:0370:7334
256.256.256.256
*/