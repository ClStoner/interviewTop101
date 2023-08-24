#include <bits/stdc++.h>
using namespace std;

class Greedy
{
public:
/**
 * BM95 分糖果问题
 * 描述：一群孩子做游戏，现在请你根据游戏得分来发糖果，要求如下：
 *      1. 每个孩子不管得分多少，起码分到一个糖果。
 *      2. 任意两个相邻的孩子之间，得分较多的孩子必须拿多一些糖果。(若相同则无此限制)
 * 数据范围： 1 <= n <= 1e5 1 <= a[i] <= 1000
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 * pick candy
 * @param arr int整型vector the array
 * @return int整型
 */
int candy(vector<int>& arr) {
    int n = arr.size();
    vector<int> num(n, 1);
    for(int i = 1; i < n; ++ i) {
        if(arr[i] > arr[i - 1]) num[i] = num[i - 1] + 1;
    }
    int res = num[n - 1];
    for(int i = n - 2; i >= 0; -- i) {
        if(arr[i] > arr[i + 1] && num[i] <= num[i + 1]) num[i] = num[i + 1] + 1;
        res += num[i];
    }
    return res; 
}
/**
 * BM96 主持人调度（二）
 * 描述：有 n 个活动即将举办，每个活动都有开始时间与活动的结束时间，第 i 个活动的开始时间是 starti ,
 *      第 i 个活动的结束时间是 endi ,举办某个活动就需要为该活动准备一个活动主持人。
 * 数据范围：1 <= n <= 1e5
 * 要求：空间复杂度O(n) 时间复杂度O(n log n)
 * 
 *
 * 计算成功举办活动需要多少名主持人
 * @param n int整型 有n个活动
 * @param startEnd int整型vector<vector<>> startEnd[i][0]用于表示第i个活动的开始时间，startEnd[i][1]表示第i个活动的结束时间
 * @return int整型
 */
int minmumNumberOfHost(int n, vector<vector<int> >& startEnd) {
    vector<int> start;
    vector<int> end;
    for(int i = 0; i < n; i++){
        start.push_back(startEnd[i][0]);
        end.push_back(startEnd[i][1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());
    int res = 0;
    int j = 0;
    for(int i = 0; i < n; i++){
        if(start[i] >= end[j]) 
            j++;  
        else
            res++;  
    }
    return res;
}


};

int main()
{

    return 0;
}