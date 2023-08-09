#include <bits/stdc++.h>
using namespace std;

class Heap{
public:

/**
 * BM46 最小的K个数
 *
 * 
 * @param input int整型vector 
 * @param k int整型 
 * @return int整型vector
 */
vector<int> GetLeastNumbers_Solution(vector<int>& input, int k) {
    int n = input.size();
    vector<int> ans;
    if(k == 0) return ans;
    if(k >= n) return input;
    priority_queue<int> q;
    for(int i = 0; i < n; ++ i) {
        if(q.size() < k) {
            q.push(input[i]); continue;
        } 
        int x = q.top();
        if(input[i] < x) {
            q.pop(); q.push(input[i]);
        }
    }

    while(!q.empty()) {
        ans.push_back(q.top()); q.pop();
    }
    return ans;
}
/**
 * BM47 寻找第K大
 * 描述：有一个整数数组，请你根据快速排序的思路，找出数组中第 k 大的数。
 * 要求：空间复杂度O(1) 时间复杂度O(n log n)
 * 
 * @param a int整型vector 
 * @param n int整型 
 * @param K int整型 
 * @return int整型
 */
int findKth(vector<int>& input, int n, int K) {
    int* a = const_cast<int*>(input.data());
    function<int(int*, int, int, int)> f;
    f = [&](int* a, int low, int high, int K) {
        if(low + 1 >= high & low == K) return a[low];
        int pivot = a[high - 1];
        int i = low, j = low, k = high;
        while(i < k) {
            if(a[i] < pivot) swap(a[i ++], a[j ++]);
            else if(a[i] > pivot) swap(a[i], a[-- k]);
            else ++ i;
        }
        if(K < j) return f(a, low, j, K);
        if(K >= k) return f(a, k, high, K);
        else return a[j];
    };
    return f(a, 0, n, n - K);
}
};
/**
 * BM48 数据流中的中位数
 * 描述：我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。
 * 要求：空间复杂度O(n) 时间复杂度O(log n)
*/
class TopHeap{
public:
void Insert(int num) {
    if(size == 0 || num <= qmax.top()) qmax.push(num);
    else qmin.push(num);
    ++ size;
    maintain();
}
double GetMedian() { 
    if(size & 1) return qmax.top();
    else return (1.0 * qmin.top() + 1.0 * qmax.top()) / 2.0;
}
private:
void maintain() {
    while(qmax.size() > (size + 1) / 2) {
        int x = qmax.top(); qmax.pop();

        qmin.push(x);
    }
    while(qmin.size() > size / 2) {
        int x = qmin.top(); qmin.pop();
        qmax.push(x);
    }
}
priority_queue<int> qmax; //大根堆， 维护前 n / 2 小的数
priority_queue<int, vector<int>, greater<int>> qmin; //小根堆 维护后 n / 2小的数
int size = 0;
};


/**
 * BM43 包含min函数的栈
 * 描述：定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的 min 函数，输入操作时保证 pop、top 和 min 函数操作时，栈中一定有元素。
 * 要求：空间复杂度O(n) 栈的各个操作都是O(1)
 * 
*/
class Stack {
public:
void push(int val) {
    stack1.push(val);
    if(stack2.empty()) stack2.push(val);
    else {
        int x = stack2.top();
        if(x > val) x = val;
        
        stack2.push(x);
    }
}
void pop() {
    stack1.pop(); stack2.pop();
}
int top() {
    return stack1.top();
}
int min() {
    return stack2.top();
}
/**
 * BM44 有效括号序列
 * 描述:判断给出的字符串是否是合法的括号序列
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 *
 * 
 * @param s string字符串 
 * @return bool布尔型
 */
bool isValid(string s) {
    int n = s.size();
    stack<int> st;
    map<char, int> m;
    m['('] = 0; m[')'] = 1; m['['] = 2; m[']'] = 3;  m['{'] = 4; m['}'] = 5; 
    for(int i = 0; i < n; ++ i) {
        int x = m[s[i]];
        if(x & 1) { // 右括号
            if(st.empty()) return false;
            if(st.top() == (x ^ 1)) st.pop();
            else return false;
        }
        else {
            st.push(x);
        }
    }
    return st.size() == 0;
}
/**
 * BM49 表达式求值
 * 描述：请写一个整数计算器，支持加减乘三种运算和括号。
 * 返回表达式的值
 * @param s string字符串 待计算的表达式
 * @return int整型
 */
int solve(string s) {
    unordered_map<char, int> mp;
    mp['('] = -1; mp['+'] = 0; mp['-'] = 0; mp['*'] = 1; mp[')'] = 2;
    int n = s.size();
    stack<int> num;
    stack<char> op;
    auto oper = [](int a, int b, char op) -> int { // 完成加、减、乘算数运算符运算
        if(op == '+') return a + b;
        else if(op == '-') return a - b;
        else return a * b;
    };
    auto cmp = [&mp](char a, char b) -> int { // 比较运算符优先级
        if(mp[a] == mp[b]) return 0;
        if(mp[a] > mp[b]) return 1;
        return -1;
    };
    int x = 0;
    num.push(x); //避免第一个数是负数
    for(int i = 0; i < n; ++ i) {
       if(isdigit(s[i])) {
            x = 10 * x + (s[i] - '0');
            if(i == n - 1 || !isdigit(s[i +1])) {
                num.push(x);
                x = 0;
            }
            continue;
        } 
        if(op.empty() || s[i] == '(') op.push(s[i]);
        else  if(s[i] == ')') {
            while(!op.empty()) {
                int c = op.top(); op.pop();
                if(c == '(') break;
                int a = num.top(); num.pop();
                int b = num.top(); num.pop();
                num.push(oper(b, a, c));
            }
        }
        else {
            while(!op.empty() && cmp(op.top(), s[i]) >= 0) {
                int c = op.top(); op.pop();
                int a = num.top(); num.pop();
                int b = num.top(); num.pop();
                num.push(oper(b, a, c));
            }
            op.push(s[i]);
        }
    }
    while(!op.empty()) {
        int c = op.top(); op.pop();
        int a = num.top(); num.pop();
        int b = num.top(); num.pop();
        num.push(oper(b, a, c));
    }
    return num.top();
}

private:
    stack<int> stack1;
    stack<int> stack2;
};
/*
* BM42 用两个栈实现队列
* 描述：两个栈实现队列
* 要求：空间复杂度O(n), 插入删除都是O(1)
*/
class Queue {
public:
void push(int node) {
    stack1.push(node);
}
int pop() {
    if(stack2.empty()) {
        while(!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }
    int x = stack2.top(); stack2.pop();
    return x;
}

/**
 * BM45 滑动窗口的最大值
 * 描述：给定一个长度为 n 的数组 num 和滑动窗口的大小 size ，找出所有滑动窗口里数值的最大值
 * 要求：空间复杂度O(n) 时间复杂度O(n)
 * 
 * 经典的单调队列
 * @param num int整型vector 
 * @param size int整型 
 * @return int整型vector
 */
vector<int> maxInWindows(vector<int>& a, int size) {
    int n = a.size();
    int q[100010];
    int front = 0, tail = 0;
    vector<int> ans;
    if(size == 0) return ans;
    for(int i = 0; i < n; ++ i) {
        while(front != tail && a[i] >= a[q[tail - 1]]) -- tail;
        q[tail ++] = i;
        if(i < size - 1) continue;
        while(i - q[front] >= size) ++ front;
        ans.push_back(a[q[front]]);
    }
    return ans;
}
private:
    stack<int> stack1;
    stack<int> stack2;  
};

int main()
{
    int n; cin >> n;
    
    TopHeap sol;
    for(int i = 0; i < n; ++ i) {
        int x; cin >> x;
        sol.Insert(x);
        cout << "med " << sol.GetMedian() << endl;
    }

    return 0;
}