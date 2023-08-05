#include <bits/stdc++.h>
using namespace std;

class BinarySearch
{
public:

/**
 * BM17 二分查找-I
 * 描述：实现无重复数字的升序数组的二分查找
 * 要求：空间复杂度O(1) 时间复杂度O(log n)
 * 
 * @param nums int整型vector 
 * @param target int整型 
 * @return int整型
 */
int search(vector<int>& nums, int target) {
    if(nums.size() == 0) return -1;
    int low = 0, high = nums.size();
    while(low < high) {
        int mid = (low + high) >> 1;
        if(nums[mid] == target) return mid;
        if(nums[mid] < target) low = mid + 1;
        else high = mid;
    }
    return -1;
}
/**
 * BM18 二维数组中的查找
 * 描述：n*m的二维数组，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。判断数组中是否存在目标整数
 * 空间复杂度O(1) 时间复杂度O(n + m)
 * 
 * @param target int整型 
 * @param array int整型vector<vector<>> 
 * @return bool布尔型
 */
bool Find(int target, vector<vector<int> >& array) {
    int n = array.size();
    if(n == 0) return false;
    int m = array[0].size();
    if(m == 0) return false;
    int i = 0, j = m - 1;
    while(i < n && j >= 0) {
        if(array[i][j] == target) return true;
        if(array[i][j] > target) -- j;
        else ++ i;
    }
    return false;
}
/**
 * BM19 寻找峰值
 * 描述：寻找数组中的峰值，多个峰值返回其中一个所在位置即可
 *      峰值元素满足严格大于左右相邻元素
 * 要求：空间复杂度O(1) 时间复杂度O(log n)
 * 
 *
 * @param nums int整型vector 
 * @return int整型
 */
int findPeakElement(vector<int>& a) {
    int n = a.size();
    if(n == 1) return 0;
    if(a[0] > a[1]) return 0;
    if(a[n - 1] > a[n - 2]) return n - 1;
    int low = 1, high = n - 1;
    while(low < high) {
        int mid = (low + high) >> 1;
        if(a[mid] > a[mid - 1] && a[mid] > a[mid + 1]) return mid;
        if(a[mid - 1] < a[mid + 1]) low = mid + 1;
        else high = mid;

    }
    return 0;
}
/**
 * BM20 数组中的逆序对
 * 描述：计算给定数组的逆序对，即满足a[i] > a[j] && i < j 的数组对
 * 要求：空间复杂第O(n) 时间复杂度O(n log n)
 *
 * 
 * @param nums int整型vector 
 * @return int整型
 */
int InversePairs(vector<int>& a) {
    const int mod = 1e9 + 7;
    int n = a.size();
    vector<int> b(n);
    int ans = 0;
    function<void(int, int, int)> merge;
    merge = [&](int left, int mid, int right) {
        int i = left, j = mid + 1;
        for(int k = left; k <= right; ++ k) {
            if(i <= mid && j <= right) {
                if(a[i] > a[j]) {
                    ans = (ans + mid - i + 1) % mod;
                    b[k] = a[j ++];
                }
                else b[k] = a[i ++];
            }
            else if(i > mid) {
                b[k] = a[j ++];
            }
            else if(j > mid) {
                b[k] = a[i ++];
            }
        }
        for(int k = left; k <= right; ++ k) {
            a[k] = b[k];
        }
    };
    function<void(int, int)> mergeSort;
    mergeSort = [&](int left, int right) {
        if(left >= right) return;
        int mid = (left + right) >> 1;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    };
    mergeSort(0, n - 1);
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
    }
    return ans;
}
/**
 * BM21 旋转数组的最小数字
 * 描述：非降序列，进行旋转，把一个数组最开始的若干个元素搬到数组的末尾，变成一个旋转数组，给定这样的旋转矩阵，求数组中的最小值
 * 空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param nums int整型vector 
 * @return int整型
 */
int minNumberInRotateArray(vector<int>& a) {
    int n = a.size();
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = (low + high) >> 1;
        cout << "low : " << low << " , mid : " << mid << " , high : " << high << endl;
        if(a[mid] < a[high]) high = mid;
        else if(a[mid] > a[high]) low = mid + 1;
        else -- high;
    }
    return a[low];
}
/**
 * BM22 比较版本号
 * 描述：比较版本号，比较规则：
 *       一. 比较版本号时，请按从左到右的顺序依次比较它们的修订号。比较修订号时，只需比较忽略任何前导零后的整数值。比如"0.1"和"0.01"的版本号是相等的
 *       二. 如果版本号没有指定某个下标处的修订号，则该修订号视为0。例如，"1.1"的版本号小于"1.1.1"。因为"1.1"的版本号相当于"1.1.0"，第3位修订号的下标为0，小于1
 *       三.  version1 > version2 返回1，如果 version1 < version2 返回-1，不然返回0.
 * @param version1 string字符串 
 * @param version2 string字符串 
 * @return int整型
 */
int compare(string version1, string version2) {
    auto preString = [](const string &s) -> vector<int> {
        vector<int> ans;
        int x = 0;
        bool flag = false;
        for(int i = 0; i < s.size(); ++ i) {
            // cout << "x : " << x <<endl;
            if(s[i] >= '1' && s[i] <= '9') {
                flag = true;
            }
            if(s[i] == '.') {
                if(flag) ans.push_back(x); x = 0;
                continue;
            }
            x = 10 * x + (s[i] - '0');
        }
        if(x) ans.push_back(x);
        return ans;
    };
    vector<int> a = preString(version1);
    vector<int> b = preString(version2);
    int n = a.size();
    int m = b.size();
    for(int i = 0; i < min(n, m); ++ i) {
        if(a[i] < b[i]) return -1;
        if(a[i] > b[i]) return 1;
    }
    if(n < m) {
        for(int i = n; i < m; ++ i) {
            if(b[i]) return -1;
        }
    }
    if(n > m) {
        for(int i = m; i < n; ++ i) {
            if(a[i]) return 1;
        }
    }
    return 0;
}
};

int main()
{


    return 0;
}