#include <bits/stdc++.h>
using namespace std;


class Hash
{
public:
/**
 * BM50 两数之和
 * 描述：给定数组，请在数组中找出两个加起来等于目标值的数的下标，返回的下标按升序排列
 * 数据范围：2 <= n <= 1e5,  -10 <= a[i] <= 1e9 , 0 <= target <= 1e9
 * 要求： 空间复杂度O(n) 时间复杂度O(n)
 * 
 * @param numbers int整型vector 
 * @param target int整型 
 * @return int整型vector
 */
vector<int> twoSum(vector<int>& numbers, int target) {
    unordered_map<int, int> m;
    int n = numbers.size();
    for(int i = 0; i < n; ++ i) {
        if(m.find(target - numbers[i]) != m.end()) {
            return vector<int>{m[target - numbers[i]], i + 1};
        }
        m[numbers[i]] = i + 1;
    }
    return vector<int>{};
}    
/**
 * BM51 数组中出现次数超过一半的数字（摩尔投票）
 * 描述：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字
 * 数据范围： 0 <= n <= 5e4
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 *
 * 
 * @param numbers int整型vector 
 * @return int整型
 */
int MoreThanHalfNum_Solution(vector<int>& numbers) {
    int n = numbers.size();
    int cand = 0;
    int cnt = 0;
    for(int i = 0; i < n; ++ i) {
        if(cnt == 0) {
            cand = numbers[i]; cnt = 1;
        }
        else {
            if(numbers[i] == cand) cnt ++;
            else cnt --;
        }
    }
    return cand;
}
/**
 * BM52 数组中只出现一次的两个数字
 * 描述：一个整型数组里除了两个数字只出现一次，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * 
 * @param nums int整型vector 
 * @return int整型vector
 */
vector<int> FindNumsAppearOnce(vector<int>& nums) {
    // write code here 
    int n = nums.size();
    int sum = 0;
    for(int i = 0; i < n; ++ i) {
        sum ^= nums[i];
    }
    int k = 1;
    while((k & sum) == 0) {
        k <<= 1;
    }
    int x = 0, y = 0;
    for(int i = 0; i < n; ++ i) {
        if((k & nums[i])) {
            x ^= nums[i];
        }
        else {
            y ^= nums[i];
        }
    }
    if(x > y) swap(x, y);
    return vector<int>{x, y};
}
/**
 * BM53 缺失的第一个正整数
 * 描述；给定一个无重复元素的整数数组nums，请你找出其中没有出现的最小的正整数
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param nums int整型vector 
 * @return int整型
 */
int minNumberDisappeared(vector<int>& a) {
    int n = a.size();
    for(int i = 0; i < n; ++ i) {
        if(a[i] <= 0) a[i] = n + 1;
    }
    for(int i = 0; i < n; ++ i) {
        if(a[i] >= n + 1) continue;
        a[abs(a[i]) - 1] = -(a[abs(a[i]) - 1]);
    }
    int ans = n + 1;
    for(int i = 0; i < n; ++ i) {
        if(a[i] > 0) {
            ans = i + 1; break;
        }
    }
    return ans;
}
/**
 * BM54 三数之和
 * 描述：给出一个有n个元素的数组S，S中是否有元素a,b,c满足a+b+c=0？找出数组S中所有满足条件的三元组。
 * 要求：空间复杂度O(n^2) 时间复杂度O(n^2)
 * @param num int整型vector 
 * @return int整型vector<vector<>>
 */
vector<vector<int> > threeSum(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> ans;
    if(n < 3) return ans;
    sort(a.begin(), a.end());
    for(int x = 0; x < n; ++ x) {
        if(x && a[x] == a[x - 1]) continue;
        int left = x + 1, right = n - 1;
        while(left < right) {
            int sum = a[x] + a[left] + a[right];
            if(sum == 0) {
                ans.push_back(vector<int>{a[x], a[left], a[right]});
                while(left < right && a[left] == a[left + 1]) ++ left;
                while(left < right && a[right] == a[right - 1]) -- right;
                ++ left; -- right;
            } 
            else if(sum < 0) {
                ++ left;
            }
            else {
               -- right;
            }
        }
    }
    return ans;
}
};

int main()
{

    return 0;
}