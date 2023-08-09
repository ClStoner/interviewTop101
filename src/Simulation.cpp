#include <bits/stdc++.h>
using namespace std;


class Simulation
{
public:
/**
 * BM97 旋转数组
 * 描述：一个数组A中存有 n 个整数，在不允许使用另外数组的前提下，将每个整数循环向右移 M（ M >=0）
 *      个位置，即将A中的数据由（A0 A1 ……AN-1 ）变换为（AN-M …… AN-1 A0 A1 ……AN-M-1 ）（最后 M 个数循环移至最前面的 M 个位置）
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 *
 * 旋转数组
 * @param n int整型 数组长度
 * @param m int整型 右移距离
 * @param a int整型vector 给定数组
 * @return int整型vector
 */
vector<int> solve(int n, int m, vector<int>& a) {
    m %= n;
    if(n == 1 || m == 0) return a;
    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin() + m);
    reverse(a.begin() + m, a.end());
    return a;
}
/**
 * BM98 螺旋矩阵
 * 描述：按螺旋的顺序返回矩阵中的所有元素。
 * 要求：空间复杂度O(nm) 时间复杂度O(nm)
 *
 * 
 * @param matrix int整型vector<vector<>> 
 * @return int整型vector
 */
vector<int> spiralOrder(vector<vector<int> >& matrix) {
    vector<int> ans;
    int n = matrix.size();
    if(n == 0) return ans;
    int m = matrix[0].size();
    if(m == 0) return ans;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int x = 0, y = 0;
    int op = 0;
    while(!vis[x][y]) {
        vis[x][y] = true;
        ans.push_back(matrix[x][y]);
        if(ans.size() == n * m) break;
        if(op == 0) { // 右
            if(y + 1 < m && !vis[x][y + 1]) ++ y;
            else ++ x, op = 1;
        }
        else if(op == 1) {//下
            if(x + 1 < n && !vis[x + 1][y]) ++ x;
            else -- y, op = 2;
        }
        else if(op == 2) {//左
            if(y - 1 >= 0 && !vis[x][y - 1]) -- y;
            else -- x, op = 3;
        }
        else {//上
            if(x - 1 >= 0 && !vis[x - 1][y]) -- x;
            else ++ y, op = 0;
        }
    }
    return ans;
}
};

int main()
{


    return 0;
}