#include <bits/stdc++.h>
using namespace std;


class TwoPointer
{
public:
/**
 * BM87 合并两个有序的数组
 * 描述：给出一个有序的整数数组 A 和有序的整数数组 B ，请将数组 B 合并到数组 A 中，变成一个有序的升序数组
 * 数据范围：0 <= n, m <= 100 
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 */
void merge(int A[], int m, int B[], int n) {
    int* C = new int[n + m];
    int i = 0, j = 0;
    for(int k = 0; k < n + m; ++ k) {
        if(i < m && j < n) {
            if(A[i] <= B[j]) C[k] = A[i ++];
            else C[k] = B[j ++];
        }
        else {
            if(i >= m) C[k] = B[j ++];
            else C[k] = A[i ++];
        }
    }
    for(int k = 0; k < n + m; ++ k) {
        A[k] = C[k];
    }
    delete[] C;
}
/**
 * BM88 判断是否为回文字符串
 * 描述：给定一个长度为 n 的字符串，请编写一个函数判断该字符串是否回文。如果是回文请返回true，否则返回false。
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param str string字符串 待判断的字符串
 * @return bool布尔型
 */
bool judge(string str) {
    int n = str.size();
    for(int i = 0, j = n - 1; i <= j; ++ i, -- j) {
        if(str[i] != str[j]) return false;
    }
    return true;
}
/**
 * BM89 合并区间
 * 描述：给出一组区间，请合并所有重叠的区间。请保证合并后的区间按区间起点升序排列。
 * 数据范围：0 <= n <= 2e5
 * 
 * @param intervals Interval类vector 
 * @return Interval类vector
 */
struct Interval {
    int start;
    int end;
    Interval(int s, int e) : start(start), end(e) {}
};
vector<Interval> merge(vector<Interval>& intervals) {
    int n = intervals.size();
    vector<Interval> ans;
    if(n == 0 || n == 1) return intervals;
    sort(intervals.begin(), intervals.end(), [](const Interval& lhs, const Interval& rhs) -> bool{
        return lhs.start == rhs.start ? lhs.end < rhs.end : lhs.start < rhs.start;
    });
    Interval tmp = intervals[0];
    for(int i = 1; i < n; ++ i) {
        if(tmp.end >= intervals[i].start) {
            tmp.start = min(tmp.start, intervals[i].start);
            tmp.end = max(tmp.end, intervals[i].end);
        }
        else {
            ans.push_back(tmp);
            tmp = intervals[i];
        }
    }
    ans.push_back(tmp);
    return ans;
}
/**
 * BM90 最小覆盖子串
 * 描述：给出两个字符串 s 和 t，要求在 s 中找出最短的包含 t 中所有字符的连续子串。
 * 要求：时间复杂度O(n) 空间复杂度O(n)
 * 
 * @param S string字符串 
 * @param T string字符串 
 * @return string字符串
 */
string minWindow(string S, string T) {
    unordered_map<char, int> m;
    for(int i = 0; i < T.size(); ++ i) {
        m[T[i]] ++;
    }
    string ans;
    int l = 0, r = 0;
    int n = S.size();
    if(n == 0) return ans;
    if(m.find(S[0]) != m.end()) m[S[0]] --;
    while(l <= r && r < n) {
        bool judge = true;
        for(auto it : m) {
            if(it.second > 0) {
                judge = false; break;
            }
        }
        string tmp = S.substr(l, r - l + 1);
        if(!judge) {
            ++ r;
            if(m.find(S[r]) != m.end()) m[S[r]] --;
        }
        else {
            if(ans == "" || (tmp.size() < ans.size())) ans = tmp;
            if(m.find(S[l]) != m.end()) m[S[l]] ++;
            ++ l;
        }
    }
    return ans;
}
/*
XDOYEZODEYXNZ XYZ

*/
/**
 * BM91 反转字符串
 * 描述：给定字符串，输出该字符串反转后的字符串
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 *
 * 反转字符串
 * @param str string字符串 
 * @return string字符串
 */
string solve(string str) {
    int n = str.size();
    if(n == 0 || n == 1) return str;
    for(int l = 0, r = n - 1; l <= r; ++ l, -- r) {
        swap(str[l], str[r]);
    }
    return str;
}
/**
 * BM92 最长无重复子数组
 * 描述：返回arr的最长无重复元素子数组的长度，无重复指的是所有数字都不相同。
 * 数据范围：0 <= n <= 1e5, 0 <= a[i] <= 1e5
 * 
 * @param arr int整型vector the array
 * @return int整型
 */
int maxLength(vector<int>& arr) {
    int n = arr.size();
    if(n == 0 || n == 1) return n;
    unordered_map<int, int> m;
    int l = 0, r = 0;
    m[arr[0]] = 1;
    int ans = 1;
    while(l <= r && r < n) {
        if(r - l + 1 == m.size()) {
            ans = max(ans, r - l + 1);
            ++ r; 
            m[arr[r]] ++;
        }
        else {
            m[arr[l]] --;
            if(m[arr[l]] == 0) m.erase(arr[l]);
            ++ l;
        }
    }
    return ans;
}
/**
 * BM93 盛水最多的容器
 * 描述：给定一个数组height,每个数代表坐标轴中的一个点的高度，height[i]是在第i点的高度，请问，从中选2个高度与x轴组成的容器最多能容纳多少水
 *
 * 
 * @param height int整型vector 
 * @return int整型
 */
int maxArea(vector<int>& a) {
    int n = a.size();
    if(n <= 1) return 0;
    int l = 0, r = n - 1;
    long long ans = 0;
    while(l <= r) {
        ans = max(ans, 1ll * (r - l) * min(a[l], a[r]));
        if(a[l] < a[r]) ++ l;
        else if(a[l] > a[r]) -- r;
        else {
            ++ l; -- r;
        }
    }
    return ans;
}
/**
 * BM94 接雨水问题
 * 描述：给定一个整形数组arr，已知其中所有的值都是非负的，将这个数组看作一个柱子高度图，计算按此排列的柱子，下雨之后能接多少雨水。(数组以外的区域高度视为0)
 * 数据范围：0 <= n <= 2e5, 0 <= arr[i] <= 1e9， 返回结果保证满足 0 <= val <= 1e9
 * 要求： 时间复杂度O(n)
 * 
 * max water
 * @param arr int整型vector the array
 * @return long长整型
 */
long long maxWater(vector<int>& arr) {
    int n = arr.size();
    vector<int> lmax(n + 1, 0);
    vector<int> rmax(n + 1, 0);
    lmax[0] = 0; rmax[n] = 0;
    for(int i = 0; i < n; ++ i) {
        lmax[i + 1] = max(lmax[i], arr[i]);
    }
    for(int i = n - 1; i >= 0; i --) {
        rmax[i] = max(rmax[i + 1], arr[i]);
    }
    long long ans = 0;
    for(int i = 1; i < n - 1; ++ i) {
        int mx = min(lmax[i], rmax[i + 1]);
        if(arr[i] <= mx) {
            ans += mx - arr[i];
        }
    }
    return ans;
}
};
int main()
{
    cout << "Hello TwoPointer" << endl;
    return 0;
}