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
/**
 * BM99 顺时针旋转矩阵
 * 描述：有一个NxN整数矩阵，请编写一个算法，将矩阵顺时针旋转90度。返回旋转后的矩阵
 * 要求：空间复杂度O(1) 时间复杂度O(n^2) 
 *
 * 
 * @param mat int整型vector<vector<>> 
 * @param n int整型 
 * @return int整型vector<vector<>>
 */
vector<vector<int> > rotateMatrix(vector<vector<int> >& mat, int n) {
    for(int i = 0; i < n; ++ i) {
        for(int j = 0; j < i; ++ j) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    for(int i = 0; i < n; ++ i) {
        for(int l = 0, r = n - 1; l <= r; ++ l, -- r) {
            swap(mat[i][l], mat[i][r]);
        }
    }
    return mat;
}
};

class Solution {
    list<pair<int, int>> dlist;//双向链表
    unordered_map<int, list<pair<int, int>>::iterator> map;
    int cap;
    
    //用链表存，链表头部是最近使用的，尾部是最后使用的，如果要删去，就直接把尾部删去就好
public:
    Solution(int capacity){
         cap=capacity;
    }
    
    //key就变得最常用了
    int get(int key) {
        if(map.count(key))
        {
            //把这个放在头部，所以需要个tmp存着，然后删掉这个位置，再放到头部
            auto tmp=*map[key];
            dlist.erase(map[key]);
            //map.erase(key);
            dlist.push_front(tmp);//把它放在最前面
            map[key]=dlist.begin();
            //return tmp.second;
            return dlist.front().second;
        }
        return -1;
    }
    
    void set(int key, int value){
         if(map.count(key))//如果存在
         {
             dlist.erase(map[key]);//放在头部
             //map.erase(key);
         }
        else if(cap==dlist.size())
        {
            //先删掉末尾的
            auto tmp=dlist.back();
            map.erase(tmp.first);
            dlist.pop_back();
        }
        dlist.push_front(pair<int, int>(key, value));
        map[key]=dlist.begin();//第一个迭代器
    }
};
class Solution {
public:
    //用list模拟双向链表，双向链表中数组第0位为频率，第1位为key，第2位为val
    //频率到双向链表的哈希表
    unordered_map<int, list<vector<int> > > freq_mp; 
    //key到双向链表节点的哈希表
    unordered_map<int, list<vector<int> > ::iterator> mp;
    //记录当前最小频次
    int min_freq = 0; 
    //记录缓存剩余容量
    int size = 0; 
    
    vector<int> LFU(vector<vector<int> >& operators, int k) {
        //记录输出
        vector<int> res; 
        size = k; 
        //遍历所有操作
        for(int i = 0; i < operators.size(); i++){
            auto op = operators[i];
            if(op[0] == 1)
                //set操作
                set(op[1], op[2]);
            else
                //get操作
                res.push_back(get(op[1]));
        }
        return res;
    }
    
    //调用函数时更新频率或者val值
    void update(list<vector<int> >::iterator iter, int key, int value) { 
        //找到频率
        int freq = (*iter)[0];
        //原频率中删除该节点
        freq_mp[freq].erase(iter); 
        //哈希表中该频率已无节点，直接删除
        if(freq_mp[freq].empty()){ 
            freq_mp.erase(freq);
            //若当前频率为最小，最小频率加1
            if(min_freq == freq) 
                min_freq++;
        }
        //插入频率加一的双向链表表头，链表中对应：freq key value
        freq_mp[freq + 1].push_front({freq + 1, key, value}); 
        mp[key] = freq_mp[freq + 1].begin(); 
    }
    
    //set操作函数
    void set(int key, int value) {
        //在哈希表中找到key值
        auto it = mp.find(key); 
        if(it != mp.end())
            //若是哈希表中有，则更新值与频率
            update(it->second, key, value);
        else{ 
            //哈希表中没有，即链表中没有
            if(size == 0){
                //满容量取频率最低且最早的删掉
                int oldkey = freq_mp[min_freq].back()[1]; 
                //频率哈希表中删除
                freq_mp[min_freq].pop_back(); 
                if(freq_mp[min_freq].empty()) 
                    freq_mp.erase(min_freq); 
                //链表哈希表中删除
                mp.erase(oldkey); 
            }
            //若有空闲则直接加入，容量减1
            else 
                size--; 
            //最小频率置为1
            min_freq = 1; 
            //在频率为1的双向链表表头插入该键
            freq_mp[1].push_front({1, key, value}); 
            //哈希表key值指向链表中该位置
            mp[key] = freq_mp[1].begin(); 
        }
    }
    
    //get操作函数
    int get(int key) {
        int res = -1;
        //查找哈希表
        auto it = mp.find(key);
        if(it != mp.end()){ 
            auto iter = it->second; 
            //根据哈希表直接获取值
            res = (*iter)[2];
            //更新频率 
            update(iter, key, res); 
        }
        return res;
    }
};



int main()
{


    return 0;
}