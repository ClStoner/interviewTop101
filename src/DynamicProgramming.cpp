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
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int ans = 0;
    int st = 0;
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(str1[i] == str2[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
            if(dp[i + 1][j + 1] > ans) {
                ans = dp[i + 1][j + 1];
                st = i - ans + 1;
            }
        }
    }
    return str1.substr(st, ans);
}
/**
 * BM67 不同路径的数目(一)
 * 描述：m*n的网格，左上角为起点，右下角为终点，机器人智能向右、向下移动，计算机器人从起点到终点不同的路径数目
 * 数据范围：0 < n, m < 100 且保证结果在 int 范围内
 * 要求：空间复杂度O(1) 时间复杂度O(min(n, m))
 * 结论：结果数组合数 ans = C(n + m - 2, n - 1)
 * 
 * @param m int整型 
 * @param n int整型 
 * @return int整型
 */
int uniquePaths(int m, int n) {
    int x =  m + n - 2;
    int y = n - 1;
    if(y < x - y) y = x - y;
    long long a = 1, b = 1;
    for(int i = y + 1, j = 1; i <= x && j <= x - y; ++ i, ++ j ) {
        a *= i; b *= j;
        long long g = __gcd(a, b);
        a /= g; b /= g;
    }
    return a / b; 
}
/**
 * BM68 矩阵的最小路径和
 * 描述：一个n*m的矩阵，从左上角开始每次只能向右或者向下走，最后到达右下角的位置，路径上所有的数字累加起来就是路径和，输出所有的路径中最小的路径和。
 * 数据范围: 1 < n, m < 500, 0 < matri[i][j] < 100
 * 要求：时间复杂度O(nm)
 * 
 * @param matrix int整型vector<vector<>> the matrix
 * @return int整型
 */
int minPathSum(vector<vector<int> >& matrix) {
    int n = matrix.size();
    if(n == 0) return 0;
    int m = matrix[0].size();
    if(m == 0) return 0;
    const int inf = 1e9;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));
    dp[0][0] = dp[0][1] = dp[1][0] = 0;
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            dp[i + 1][j + 1] = min(dp[i + 1][j], dp[i][j + 1]) + matrix[i][j];
            cout << dp[i + 1][j + 1] << " ";
        }
        cout << endl;
    }
    return dp[n][m];
}
/**
 * BM69 把数字翻译成字符串
 * 描述：有一种将字母编码成数字的方式：'a'->1, 'b->2', ... , 'z->26'，现在给一串数字，返回有多少种可能的译码结果
 * 数据范围：0 < n < 90  
 * 要求：时间复杂度O(n)
 * @param nums string字符串 数字串
 * @return int整型
 */
int solve(string s) {
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1; dp[1] = 1;
    if(n == 0 || (n == 1 && s[0] == '0')) return 0;
    for(int i = 1; i < n; ++ i) {
        if(s[i] == '0') {
            if(s[i - 1] != '1' && s[i - 1] != '2') return 0;
            dp[i + 1] += dp[i - 1];
            continue;
        }
        dp[i + 1] += dp[i];
        if(s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '0' && s[i] <= '6')) dp[i + 1] += dp[i - 1];
    }
    return dp[n];
}
/**
 * BM70 兑换零钱(一)
 * 描述：每个值代表一种面值的货币，每种面值的货币可以使用任意张，再给定一个m，代表要找的钱数，求组成aim的最少货币数。
 * 数据范围: 0 <= n <= 1e4 , 0 <= m <= 5e3
 * 要求：时间复杂度O(nm) 
 * 最少货币数
 * @param arr int整型vector the array
 * @param aim int整型 the target
 * @return int整型
 */
int minMoney(vector<int> a, int target) {
    int n = a.size();
    const int inf = 1e9;
    vector<int> dp(target + 1, inf);
    dp[0] = 0;
    for(int i = 0; i < n; ++ i) {
        for(int j = a[i]; j <= target; ++ j) {
            dp[j] = min(dp[j], dp[j - a[i]] + 1);
        }
    }
    if(dp[target] == inf) dp[target] = -1;
    return dp[target];
}
/**
 * BM71 最长上升子序列(一)
 * 描述：计算最长严格上升子序列的长度
 * 数据范围：0 <= n <= 1e3
 * 要求；空间复杂度O(n) 时间复杂度O(n^2)
 * @param arr int整型vector 给定的数组
 * @return int整型
 */
int LIS(vector<int>& arr) {
    int n = arr.size();
    if(n == 0) return 0;
    vector<int> dp(n, 1);
    int ans = 1;
    for(int i = 1; i < n; ++ i) {
        for(int j = 0; j < i; ++ j) {
            if(arr[i] > arr[j]) dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}
/**
 * BM72 连续子数组的最大和
 * 描述;求所有子数组的和的最大值
 * 数据范围： 1 <= n <= 2e5, -100 <= a[i] <= 100
 * 要求：空间复杂度O(1) 时间复杂度(n)
 * 
 * @param array int整型vector 
 * @return int整型
 */
int FindGreatestSumOfSubArray(vector<int>& a) {
    int n = a.size();
    int ans = a[0], f = 0;
    for(int i = 0; i < n; ++ i) {
        if(f < 0) f = a[i];
        else f += a[i];
        ans = max(ans, f);
    }
    return ans;
} 
/**
 * BM74 数字字符串转化成IP地址
 * 描述：现在有一个只包含数字的字符串，将该字符串转化成IP地址的形式，返回所有可能的情况。
 * 数据范围：字符串长度 0 <= n <= 12
 * 要求：空间复杂度O(n!) 时间复杂度O(n!)
 * 
 * @param s string字符串 
 * @return string字符串vector
 */
vector<string> restoreIpAddresses(string s) {
    int n = s.size();
    vector<string> ans;
    function<bool(string)> judge;
    judge = [&](string str) {
        if(str[0] == '0') {
            return str.size() == 1;
        }
        int x = 0;
        for(int i = 0; i < str.size(); ++ i) {
            x = 10 * x + (str[i] - '0');
        }
        return x <= 255;
    };

    function<void(int, vector<string>&)> f;
    f = [&](int st, vector<string>& tmp) {
        if(tmp.size() == 4) {
            if(st == n ) {
                string str;
                for(int i = 0; i < 4; ++ i) {
                    str += tmp[i];
                    if(i < 3) str += '.';
                }
                ans.push_back(str);
            }
            return;
        }
        for(int i = st; i < n; ++ i) {
            string str = s.substr(st, i - st + 1);
            if(!judge(str)) break;
            tmp.push_back(str);
            f(i + 1, tmp);
            tmp.pop_back();
        }
    };
    vector<string> tmp;
    f(0, tmp);
    return ans;
}
/**
 * BM73 最长回文子串
 * 描述：计算其中最长回文子串的长度
 * 数据范围：1 <= n <= 1e3
 * 要求：空间复杂度O(1) 时间复杂度O(n^2) 
 * 进阶：空间复杂度O(n) 时间复杂度O(n)
 * 
 * @param s string字符串 
 * @return int整型
 */
int getLongestPalindrome(string s) {
    int n = s.size();
    int ans = 1;
    for(int i = 0; i < n; ++ i) {
        for(int j = 1; i - j >= 0 && i + j < n; ++ j) {
            if(s[i - j] != s[i + j]) break;
            ans = max(ans, 2 * j + 1);
        }
    }
    for(int i = 0; i < n; ++ i) {
        for(int l = i, r = i + 1; l >= 0 && r < n; --l, ++ r) {
            if(s[l] != s[r]) break;
            ans = max(ans, r - l + 1);
        }
    }
    return ans;
}

/**
 * BM75 编辑距离(一)
 * 描述：请你算出将 str1 转为 str2 的最少操作数。你可以对字符串进行3种操作：
 *      1.插入一个字符
 *      2.删除一个字符
 *      3.修改一个字符。
 * 数据范围： 1 <= n,m <= 1e3,保证字符串中只出现小写英文字母
 * 要求：空间复杂度O(nm) 时间复杂度O(nm)
 *
 * 
 * @param str1 string字符串 
 * @param str2 string字符串 
 * @return int整型
 */
int editDistance(string str1, string str2) {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1000));
    for(int i = 0; i <= n; ++ i) dp[i][0] = i;
    for(int j = 0; j <= m; ++ j) dp[0][j] = j;

    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(str1[i] == str2[j]) {
                dp[i + 1][j + 1] = dp[i][j];
            }
            else {
                dp[i + 1][j + 1] = min(min(dp[i + 1][j], dp[i][j + 1]), dp[i][j]) +1;
            }
        }
    }
    return dp[n][m];
}
/**
 * BM76 正则表达式匹配
 * 描述：请实现一个函数用来匹配包括'.'和'*'的正则表达式。
 *      1.模式中的字符'.'表示任意一个字符
 *      2.模式中的字符'*'表示它前面的字符可以出现任意次（包含0次）。
 * 数据范围：
 *      1.str 只包含从 a-z 的小写字母。
 *      2.pattern 只包含从 a-z 的小写字母以及字符 . 和 *，无连续的 '*'。
 *      3. 0 <= str.size, pattern.size <= 26      
 *       
 * @param str string字符串 
 * @param pattern string字符串 
 * @return bool布尔型
 */
bool match(string str, string pattern) {
    int n = str.size();
    int m = pattern.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    // for(int j = 0; j < m; ++ j) dp[0][j] = true;
    dp[0][0] = true;
    if(m >= 2) {
        if(pattern[0] == '.' && pattern[1] == '*')  dp[0][2] = true;
    }
 
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(str[i] == pattern[j] || pattern[j] == '.') {
                dp[i + 1][j + 1] = dp[i +1][j + 1] | dp[i][j];
            }
            else if(j && pattern[j] == '*') {
                char ch = pattern[j - 1];
                dp[i + 1][j + 1] = dp[i + 1][j + 1] | dp[i + 1][j - 1];
                for(int k = i; k >= 0; -- k) {
                    if(str[k] != ch && ch != '.') break;
                    dp[i + 1][j + 1] = (dp[i + 1][j + 1] | dp[k][j - 1]);
                }
            }
        }
    }
    return dp[n][m];
}
/**
 * BM77 最长的括号子串
 * 描述：长度为n仅包含字符 '(' 和 ')' 的字符串，计算最长的格式正确的括号子串的长度.
 * 数据范围：0 <= n <= 5e5
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 * @param s string字符串 
 * @return int整型
 */
int longestValidParentheses(string s) {
    int n = s.size();
    if(n <= 1) return 0;
    int ans = 0;
    int start = -1;
    stack<int> st;
    for(int i = 0; i < n; ++ i) {
        if(s[i] == '(') st.push(i);
        else {
            if(st.empty()) start = i;
            else {
                st.pop();
                if(!st.empty()) ans = max(ans, i - st.top());
                else ans = max(ans, i - start);
            }
        }
    }
    return ans;
}
/**
 * BM78 打家劫舍(一)
 * 描述：每个房间都存有一定的现金，为了防止被发现，你不能偷相邻的两家，即，如果偷了第一家，就不能再偷第二家；如果偷了第二家，那么就不能偷第一家和第三家。请你计算在不被发现的前提下最多的偷窃金额
 * 数据范围： 1 <= n <= 2e5, 1 <= num[i] <= 5e3
 * 空间复杂度O(n) 时间复杂度O(n) 空间可以压缩至O(1)
 * 
 * @param nums int整型vector 
 * @return int整型
 */
int robI(vector<int>& nums) {
    int n = nums.size();
    int f0 = 0, f1 =  0;
    int f;
    for(int i = 0; i < n; ++ i) {
        f = max(f0, f1 + nums[i]);
        f1 = f0; f0 = f;
    }
    return f;
}
/**
 * BM79 打家劫舍(二)
 * 描述：每个房间都存有一定的现金，为了防止被发现，你不能偷相邻的两家，即，如果偷了第一家，就不能再偷第二家；如果偷了第二家，那么就不能偷第一家和第三家，并且第一家和最后一家是连着的。请你计算在不被发现的前提下最多的偷窃金额
 * 数据范围： 1 <= n <= 2e5, 1 <= num[i] <= 5e3
 * 空间复杂度O(n) 时间复杂度O(n) 
 * 
 * @param nums int整型vector 
 * @return int整型
 */
int robII(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    int f0 = 0, f1 =  0;
    int f;
    for(int i = 1; i < n; ++ i) {
        f = max(f0, f1 + nums[i]);
        f1 = f0; f0 = f;
    }
    ans = f;
    f0 = 0; f1 = 0;
     for(int i = 0; i < n - 1; ++ i) {
        f = max(f0, f1 + nums[i]);
        f1 = f0; f0 = f;
    }
    ans = max(ans, f);
    return ans;
}
/**
 * BM80 买卖股票的最好时机(一)
 * 描述：一次买入，一次卖出，计算最大获利
 * 数据范围： 0 <= 0 <= 1e5, 0 <= val <= 1e4
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param prices int整型vector 
 * @return int整型
 */
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int ans = 0;
    int m = 1e5;
    for(auto x : prices) {
        ans = max(ans, x - m);
        m = min(x, m);
    }
    return ans;
}
/**
 * BM81 买卖股票的最好时机(二)
 * 描述：可以多次买卖股票，但在下次购买之前必须卖出之前股票
 * 数据范围： 1 <= 0 <= 1e5, 0 <= val <= 1e4
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 计算最大收益
 * @param prices int整型vector 股票每一天的价格
 * @return int整型
 */
int maxProfitII(vector<int>& prices) {
    int n = prices.size();
    int ans = 0, m = prices[0];
    for(int i = 1; i < n; ++ i) {
        if(prices[i] < prices[i - 1]) {
            ans += (prices[i - 1] - m);
            m = prices[i];
        }
    }
    ans += prices[n - 1] - m;
    return ans;   
}
/**
 * BM82 买卖股票的最好时机(三)
 * 描述：对多两次买卖股票，但在下次购买之前必须卖出之前股票
 * 数据范围： 1 <= 0 <= 1e5, 0 <= val <= 1e4
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 两次交易所能获得的最大收益
 * @param prices int整型vector 股票每一天的价格
 * @return int整型
 */
int maxProfitIII(vector<int>& prices) {
    int n = prices.size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(5, -100000));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for(int i = 1; i < n; ++ i) {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
        dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
        dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
    }
    return max(dp[n - 1][2], dp[n - 1][4]);
}
};

int main()
{
    cout << "Hello DynamicProgramming" << endl;
    // int n; cin >> n;
    DymanicProgramming sol;
    string str; cin >> str;
    // string pattern; cin >> pattern;

    cout << sol.longestValidParentheses(str) << endl;
    return 0;
}