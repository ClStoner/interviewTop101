#include <bits/stdc++.h>
using namespace std;

class RecuBack
{
public:
/**
 * BM55 没有重复项数字的全排列
 * 空间复杂度O(n!) 时间复杂度O(n!)
 * 
 * @param num int整型vector 
 * @return int整型vector<vector<>>
*/
vector<vector<int> > permute(vector<int>& num) {
    int n = num.size();
    sort(num.begin(), num.end());
    function<void(vector<int>&, vector<int>&, vector<bool>&, vector<vector<int>>& ) > f;
    f = [&](vector<int>&a, vector<int>& tmp, vector<bool> &vis, vector<vector<int>>& ans) {
        if(tmp.size() == n) {
            ans.push_back(tmp);
            return;
        }
        for(int i = 0; i < n; ++ i) {
            if(vis[i]) continue;
            vis[i] = true;
            tmp.push_back(a[i]);
            f(a, tmp, vis, ans);
            vis[i] = false;
            tmp.pop_back();
        }
        
    };
    vector<int> tmp;
    vector<bool> vis(n, false);
    vector<vector<int>> ans;
    f(num, tmp, vis, ans);
    return ans;
}

/**
 * BM56 有重复项数字的全排列
 * 时间复杂度O(n!) 空间复杂度O(n!)
 * 
 * @param num int整型vector 
 * @return int整型vector<vector<>>
 */
vector<vector<int> > permuteUnique(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    function<void(vector<int>&, vector<bool>& )> f;
    f = [&](vector<int>&tmp, vector<bool>& vis) {
        if(tmp.size() == n) {
            res.push_back(tmp);
            return;
        }
        for(int i = 0; i < n; ++ i) {
            if(vis[i] || (i && nums[i] == nums[i - 1] && !vis[i - 1])) continue;
            vis[i] = true;
            tmp.push_back(nums[i]);
            f(tmp, vis);
            vis[i] = false;
            tmp.pop_back();
        }
    };
    vector<int> tmp;
    vector<bool> vis(n, false);
    f(tmp, vis);
    return res;
}
/**
 * BM57 岛屿数量
 * 岛屿数量，计算联通分块
 * 时间复杂度O(n*m)
 * 判断岛屿数量
 * @param grid char字符型vector<vector<>> 
 * @return int整型
 */

int solve(vector<vector<char> >& grid) {
    int ans = 0;
    int n = grid.size();
    if(n == 0) return ans;
    int m = grid[0].size();
    if(m == 0) return ans;
    function<bool(int, int)> judge;
    judge = [&](int x, int y) {
        if(x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '1') return true;
        return false;
    };
    function<void(int, int)> dfs;
    int nx[4] = {0, 0, 1, -1};
    int ny[4] = {1, -1, 0, 0};
    dfs = [&](int x, int y) {
        grid[x][y] = '0';
        for(int i = 0; i < 4; ++ i) {
            int xx = x + nx[i];
            int yy = y + ny[i];
            if(judge(xx, yy)) dfs(xx, yy);
        }
    };
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(grid[i][j] == '0') continue;
            dfs(i, j);
            ans ++;
        }
    }
    return ans;
}
/**
 * BM58 字符串的排列
 * 描述：字符串全排列
 * 要求：空间复杂度O(n) 时间复杂度O(n!)
 * @param str string字符串 
 * @return string字符串vector
 */
vector<string> Permutation(string str) {
    int n = str.size();
    sort(str.begin(), str.end());
    vector<string> res;
    function<void(string&, vector<bool>&)> f;
    f = [&](string& s, vector<bool>& vis) {
        if(s.size() == n) {
            res.push_back(s);
            return;
        }
        for(int i = 0; i < n; ++ i) {
            if(vis[i] || (i && str[i] == str[i - 1] && !vis[i - 1])) continue;
            vis[i] = true;
            s.push_back(str[i]);
            f(s, vis);
            s.pop_back();
            vis[i] = false;
        }
    };
    vector<bool> vis(n, false);
    string s;
    f(s, vis);
    return res;   
}
/**
 * BM59 N皇后问题
 * N皇后问题，N 皇后问题是指在 n * n 的棋盘上要摆 n 个皇后，
    要求：任何两个皇后不同行，不同列也不在同一条斜线上，
    求给一个整数 n ，返回 n 皇后的摆法数。
 * 时间复杂度O(n!)
 * 
 * @param n int整型 the n
 * @return int整型
 */
//判断皇后是否符合条件
bool isValid(vector<int> &pos, int row, int col){ 
    //遍历所有已经记录的行
    for(int i = 0; i < row; i++){ 
        //不能同行同列同一斜线
        if(row == i || col == pos[i] || abs(row - i) == abs(col - pos[i])) 
            return false;
    }
    return true;
}

//递归查找皇后种类
void recursion(int n, int row, vector<int> & pos, int &res){ 
    //完成全部行都选择了位置
    if(row == n){ 
        res++; 
        return;
    }
    //遍历所有列
    for(int i = 0; i < n; i++){ 
        //检查该位置是否符合条件
        if(isValid(pos, row, i)){ 
            //加入位置
            pos[row] = i; 
            //递归继续查找
            recursion(n, row + 1, pos, res); 
        }
    }
}

int Nqueen(int n) {
    int res = 0;
    //下标为行号，元素为列号，记录皇后位置
    vector<int> pos(n, 0); 
    //递归
    recursion(n, 0, pos, res); 
    return res;
}

/**
 * BM60 括号生成
 * 描述：给出n对括号，请编写一个函数来生成所有的由n对括号组成的合法组合
 * 要求：空间复杂度O(n) 时间复杂度O(2^n)
 *
 * 
 * @param n int整型 
 * @return string字符串vector
 */
vector<string> generateParenthesis(int n) {
    vector<string> ans;
    function<bool(string)> judge;
    judge = [&](string s) {
        stack<char> st;
        for(int i = 0; i < s.size(); ++ i) {
            if(s[i] == '(') st.push(s[i]);
            else {
                if(st.empty()) return false;
                st.pop();
            }
        }
        return st.empty();
    };

    function<void(string&, int, int)> f;
    f = [&](string& s, int left, int right) {
        // cout << "left : " << left << " , right : " << right << "  ,s : " << s << endl;
        if(left == 0 && right == 0){
            if(judge(s)) {
                ans.push_back(s);
            }
            return;
        } 

        if(left) {
            s.push_back('(');
            f(s, left - 1, right);
            s.pop_back();
        }
        if(right) {
            s.push_back(')');
            f(s, left, right - 1);
            s.pop_back();
        }

    };
    string s;
    f(s, n, n);
    return ans;
}
 /**
 * BM61 矩阵最长递增路径
 * 描述：给定一个 n 行 m 列矩阵 matrix ，矩阵内所有数均为非负整数。 你需要在矩阵中找到一条最长路径，使这条路径上的元素是递增的。并输出这条最长路径的长度。
 * 数据范围： 1 <= n, m <= 1000 0 <= a[i][j] <= 1000
 * 要求：空间复杂度O(nm) 时间复杂度O(nm)
 * 
 * 递增路径的最大长度
 * @param matrix int整型vector<vector<>> 描述矩阵的每个数
 * @return int整型
 */
int solve(vector<vector<int> >& matrix) {
    int ans = 0;
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 1));

    int nx[4] = {1, -1, 0, 0};
    int ny[4] = {0, 0, 1, -1};
    function<void(int, int)> dfs;
    dfs = [&](int x, int y) {
        // cout << "x : " << x << " , y : " << y << " , dp : " << dp[x][y] << endl;
        ans = max(ans, dp[x][y]);
        for(int i = 0; i < 4; ++ i) {
            int xx = x + nx[i];
            int yy = y + ny[i];
            // cout << "xx : " << xx << " , yy : " << yy << endl;
            if(xx >= 0 && xx < n && yy >= 0 && yy < m && matrix[xx][yy] > matrix[x][y] && dp[x][y] + 1 > dp[xx][yy]) {
                dp[xx][yy] = dp[x][y] + 1;
                dfs(xx, yy);
            }
        }
    };
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < m; ++ j) {
            if(dp[i][j] == 1) dfs(i, j);
        }
    }
    return ans;
}

};

int main()
{   
    cout << "hello RecuBack" << endl;
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i <n; ++ i) {
        for(int j = 0; j < m; ++ j) cin >> a[i][j];
    }
    RecuBack sol;
    cout << sol.solve(a) << endl;

    return 0;
}
/*
3 3
1 2 3
4 5 6
7 8 9

*/