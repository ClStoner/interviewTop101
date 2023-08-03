#include <bits/stdc++.h>
using namespace std;

class DymanicProgramming
{
public:
/**
 * BM62 斐波那契数列
 * 描述：输出斐波那契数列第n项
 * 要求：空间复杂度O(1) 时间复杂度O(n) ，也存在时间复杂度为O(log n)的做法，即 矩阵快速幂
 * 
 * @param n int整型 
 * @return int整型
 */
int Fibonacci(int n) {
    if(n == 1 || n == 2) return 1;
    int fib0 = 1, fib1 = 1;
    int fib;
    for(int i = 3; i <= n; ++ i) {
        fib = fib0 + fib1;
        fib0 = fib1; fib1 = fib;
    }
    return fib;
}
/**
 * BM63 跳台阶
 * 描述：一只青蛙一次可以跳上1级台阶，也可以跳上2级，求该青蛙跳上一个 n 级的台阶总共有多少种跳法（就是斐波那契数列,f1=1, f2 = 2）
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param n int整型 
 * @return int整型
 */
int jumpFloor(int n) {
    if(n == 1) return 1;
    int fib0 = 1, fib1 = 1;
    int fib;
    for(int i = 2; i <= n; ++ i) {
        fib = fib0 + fib1;
        fib0 = fib1; fib1 = fib;
    }
    return fib;
}
/**
 * BM64 最小花费爬楼梯
 * 描述：给定一个整数数组cost,其中cost[i]是从楼梯第i个台阶向上爬需要支付的费用，下表从0开始，一旦你支付此费用，即可选择向上爬一个或者两个台阶。
 *      你可以选择下标0或者1的台阶开始，返回达到楼梯顶部的最低花费
 * 数据范围： 1 <= n <= 1e5 1 <= cost[i] <= 1e4
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 * @param cost int整型vector 
 * @return int整型
 */
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    if(n <= 2) return 0;
    vector<int>f(n + 1, 0);
    for(int i = 2; i <= n; ++ i) {
        f[i] = min(f[i - 2] + cost[i - 2], f[i - 1] + cost[i - 1]);
    }
    return f[n];
}
/**
 * BM65 最长公共子序列(二)
 * 描述：输出两个字符串的最长公共子序列，如果最长公共子序列为空，则返回"-1"
 * 数据范围：0 <= |str1|,|str2| <= 2000
 * 要求：空间复杂度O(nm) 时间复杂度O(nm)
 * 
 * @param s1 string字符串 the string
 * @param s2 string字符串 the string
 * @return string字符串
 */
string LCSII(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> path(n + 1, vector<int>(m + 1));
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(s1[i] == s2[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
                path[i + 1][j + 1] = 0;
            }
            else {
                if(dp[i + 1][j] > dp[i][j + 1]) {
                    dp[i + 1][j + 1] = dp[i + 1][j];
                    path[i + 1][j + 1] = 1;
                }
                else {
                    dp[i + 1][j + 1] = dp[i][j + 1];
                    path[i + 1][j + 1] = 2;
                }
            }
        }
    }   
    // 找路径
    if(dp[n][m] == 0) return "-1";
    string ans;
    int i = n - 1, j = m - 1;
    while(i >=0 && j >= 0) {
        if(path[i + 1][j + 1] == 0) {
            ans.push_back(s1[i]);
            -- i; -- j;
            continue;
        }
        if(path[i + 1][j + 1] == 1) -- j;
        else -- i;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
/**
 * BM66 最长公共子串
 * 描述：输出两个字符串的最长公共子串，数据保证最长公共子串存在且唯一
 * 数据范围：0 <= |str1|,|str2| <= 5000
 * 要求：空间复杂度O(nm) 时间复杂度O(nm)
 * 
 * @param str1 string字符串 the string
 * @param str2 string字符串 the string
 * @return string字符串
 */
string LCS(string str1, string str2) {
    
}


};

int main()
{
    cout << "Hello DynamicProgramming" << endl;
    int n; cin >> n;
    DymanicProgramming sol;
    cout << sol.Fibonacci(n) << endl;
    return 0;
}