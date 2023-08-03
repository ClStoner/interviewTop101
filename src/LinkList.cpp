#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int _val) : val(_val), next(nullptr) {}
};

class List {
public:

/// 创建链表，以输入为0结束
ListNode* CreateList() {
    ListNode* head = new ListNode(0);
    ListNode* p = head;
    ListNode* q;
    int x;
    while(cin>>x && x) {
        q = new ListNode(x);
        p->next = q; p = p->next;
    }
    return head->next;
}
/// 打印链表
void print(ListNode* head) {
    ListNode* p = head;
    while(p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}
/**
 * BM1 反转链表
 * 描述：将整个链表进行反转，返回头结点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @return ListNode类
 */
ListNode* ReverseList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    // 循环的方式实现链表翻转
    ListNode* pre = nullptr;
    ListNode* cur = head;
    ListNode* nxt;
    while(cur) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
    // // 递归实现链表翻转
    // ListNode* nxt = head->next;
    // ListNode* newHead = ReverseList(nxt);
    // nxt->next = head; head->next = nullptr;
    // return newHead;
}
/**
 * BM2 链表内指定区间反转
 * 描述：将下标在区间[m,n]之间的链表进行反转，返回头结点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @param m int整型 
 * @param n int整型 
 * @return ListNode类
 */
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(head == nullptr || head->next == nullptr || m == n) return head;
    ListNode* newHead = new ListNode(-1);
    newHead->next = head;
    ListNode* cur = head;
    ListNode* pre = newHead;
    ListNode* nxt;
    for(int i = 1; i < m; ++ i) {
        pre = cur; cur = cur->next;
    }
    for(int i = m; i < n; ++ i) {
        nxt = cur->next;
        cur->next = nxt->next;
        nxt->next = pre->next;
        pre->next = nxt;
    }
    return newHead->next;
}
/**
 * BM3 链表中的节点每k个一组翻转
 * 描述：将链表节点每 k 个一组翻转，返回翻转后的链表，若链表节点个数不是 k 的倍数，则最后剩下的节点保持不变，返回反转后的头结点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @param k int整型 
 * @return ListNode类，
 */
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head == nullptr || head->next == nullptr || k == 1) return head;
    // 递归版本
    int id = 0;
    ListNode* cur = head;
    ListNode* nxt;
    while(cur) {
        id ++;
        if(id == k) break;
        cur = cur->next;
        nxt = cur->next;
    }
    if(id < k) return head;
    cur->next = nullptr;
    nxt = reverseKGroup(nxt, k);
    ListNode* newHead = ReverseList(head);
    head->next = nxt;
    return newHead;

    //// 非递归版本
    // int id = 0;
    // ListNode* newHead = new ListNode(-1);
    // newHead->next = head;
    // ListNode* pre = newHead;
    // ListNode* cur = head;
    // ListNode* nxt;
    
    // while(cur ) {
    //     ++ id;
    //     if(id == k) {
    //         cur->next = nullptr;
    //         pre->next = ReverseList(head);
    //         head->next = nxt;
    //         pre = head;
    //         head = nxt;
    //         cur = nxt;
    //         id = 0;
    //     }
    //     else {
    //         cur = cur->next;
    //         if(cur == nullptr) break;
    //         nxt = cur->next;
    //     }
    // }
    // return newHead->next; 
}
/**
 * BM4 合并两个排序的链表
 * 描述：合并两个递增链表，使得合并后的链表仍然是递增的，返回合并后链表的头结点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param pHead1 ListNode类 
 * @param pHead2 ListNode类 
 * @return ListNode类
 */
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
    // write code here
    ListNode* head = new ListNode(0);
    ListNode* cur = head;
    while(pHead1 && pHead2) {
        if(pHead1->val < pHead2->val) {
            cur->next = pHead1;
            pHead1 = pHead1->next;
        }
        else {
            cur->next = pHead2;
            pHead2 = pHead2->next;
        }
        cur = cur->next;
    }
    if(pHead2 == nullptr) cur->next = pHead1;
    if(pHead1 == nullptr) cur->next = pHead2;
    return head->next;
}
/**
 * BM5 合并k个已排序的链表
 * 描述：合并 k 个升序的链表并将结果作为一个升序的链表返回其头节点。
 * 要求：空间复杂度O(1) 时间复杂度O(n log k)
 * 
 * @param lists ListNode类vector 
 * @return ListNode类
 */
ListNode* mergeKLists(vector<ListNode*>& lists) {
    int n = lists.size();
    function<ListNode*(int, int)> mergeK;
    mergeK = [&](int left, int right) {
        ListNode* newHead = nullptr;
        if(left > right) return newHead;
        if(left == right) return lists[left];
        int mid = (left + right) >>1;
        return Merge(mergeK(left, mid), mergeK(mid + 1, right));
    };
    return mergeK(0, n - 1);
}
/**
 * BM6 判断链表中是否有环
 * 描述：判断给定的链表中是否有环。如果有环则返回true，否则返回false。
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @return bool
 */
bool hasCycle(ListNode *head) {
    if(head == nullptr) return false;
    ListNode* fast = head;
    ListNode* low = head;
    while(fast && fast->next) {
        fast = fast->next->next;
        low = low->next;
        if(low == fast) return true;
    }
    return false;
}
/**
 * BM7 链表中环的入口结点
 * 描述：给定链表，若其中包含环，请找出该链表的环的入口结点，否则，返回null。
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param pHead ListNode类 
 * @return ListNode类 
 */
ListNode* EntryNodeOfLoop(ListNode* pHead) {
    ListNode* fast = pHead;
    ListNode* low = pHead;
    while(fast && fast->next) {
        fast = fast->next->next;
        low = low->next;
        if(low == fast) break;
    }
    if(fast == nullptr || fast->next == nullptr) return nullptr;
    fast = pHead;
    while(fast != low) {
        fast = fast->next;
        low = low->next;
    }
    return low;
}
/**
 * BM8 链表中倒数最后k个结点
 * 描述：返回该链表中倒数第k个节点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param pHead ListNode类 
 * @param k int整型 
 * @return ListNode类
 */
ListNode* FindKthToTail(ListNode* pHead, int k) {
    ListNode* fast = pHead;
    if(k <= 0) return nullptr;
    ListNode* low = nullptr;
    int id = 1;
    while(fast) {
        if(id == k) low = pHead;
        else if(id > k) low = low->next;
        fast = fast->next;
        ++ id;
    }
    return low;
}
/**
 * BM9 删除链表的倒数第n个节点
 * 描述：删除链表的倒数第 n 个节点并返回链表的头指针
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @param n int整型 
 * @return ListNode类
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(n == 0) return head;
    ListNode* fast = head;
    ListNode* low = nullptr;
    ListNode* pre = nullptr;
    if(head == nullptr) return head;
    int id = 1;
    while(fast) {
        if(id == n) low = head;
        else if(id > n) {
            pre = low; low = low->next;
        }
        fast = fast->next;
        ++ id;
    }
    if(low == nullptr) return head;
    if(pre == nullptr) return head->next;
    pre->next = low->next;
    delete low;
    return head;
}
/**
 * BM10 两个链表的第一个公共结点
 * 描述：两个无环的单向链表，找出它们的第一个公共结点，如果没有公共节点则返回空。
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param pHead1 ListNode类 
 * @param pHead2 ListNode类 
 * @return ListNode类
 */
ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
    ListNode *p1, *p2;
    p1 = pHead1;
    p2 = pHead2;
    while(p1 != p2) {
        p1 = (p1 == nullptr ? pHead2 : p1->next);
        p2 = (p2 == nullptr ? pHead1 : p2->next);
    }
    return p1;
}
/**
 * BM11 链表相加(二)
 * 描述：给定两个链表，链表每个节点的val值是0~9，请生成代表两个整数相加值的结果链表
 * 要求：空间复杂度O(n)，时间复杂度O(n)
 * 
 * @param head1 ListNode类 
 * @param head2 ListNode类 
 * @return ListNode类
 */
ListNode* addInList(ListNode* head1, ListNode* head2) {
    // write code here
    if(head1 == nullptr) return head2;
    if(head2 == nullptr) return head1;
    head1 = ReverseList(head1);
    head2 = ReverseList(head2);
    ListNode* node = nullptr;
    int add = 0;
    while(head1 && head2) {
        int x = head1->val + head2->val + add;
        add = x / 10; x = x % 10;
        ListNode* now = new ListNode(x);
        now->next = node;
        node = now;
        head1 = head1->next; head2 = head2->next;
    }
    ListNode* p = nullptr;
    if(head1 == nullptr) {
        p = head2;
    }
    else if(head2 == nullptr) {
        p = head1;
    }
    else p = nullptr;
    while(p) {
        int x = add + p->val;
        add = x / 10; x = x % 10;
        ListNode* now = new ListNode(x);
        now->next = node; node = now;
        p = p->next;
    }
    if(add) {
        ListNode* now = new ListNode(add);
        now->next = node; node = now;
    }
    return node;
}
/**
 * BM12 单链表的排序
 * 描述：给定一个节点数为n的无序单链表，对其按升序排序。
 * 要求：空间复杂度O(n) 时间复杂度O(n log n)
 * 
 * @param head ListNode类 the head node
 * @return ListNode类
 */
ListNode* sortInList(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* left = head;
    ListNode* right = head->next->next;
    while(right && right->next) {
        left = left->next;
        right = right->next->next;
    }
    right = left->next;
    left->next = nullptr;
    function<ListNode*(ListNode*, ListNode*)> f;
    f = [&](ListNode* head1, ListNode* head2) {
        ListNode* head = new ListNode(-1);
        ListNode* cur = head;
        while(head1 && head2) {
            if(head1->val < head2->val) {
                cur->next = head1;
                head1 = head1->next;
            }
            else {
                cur->next = head2;
                head2 = head2->next;
            }
            cur = cur->next;
        }
        if(!head1) cur->next = head2;
        if(!head2) cur->next = head1;
        return head->next;
    };
    return f(sortInList(head), sortInList(right));
}
/**
 * BM13 判断一个链表是否为回文结构
 * 描述：给定链表，请判断该链表是否为回文结构
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 the head
 * @return bool布尔型
 */
bool isPail(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return true;
    if(head->next->next == nullptr) return head->val == head->next->val;
    ListNode* low = head;
    ListNode* fast = head;
    while(true) {
        low = low->next;
        fast = fast->next;
        if(fast == nullptr) { // 奇数
            low = low->next;
            break;
        }   
        fast = fast->next;
        if(fast == nullptr) break; // 偶数
    }
    ListNode* rhead = ReverseList(low);
    low = head; fast = rhead;
    while(fast) {
        if(low->val != fast->val) return false;
        low = low->next;
        fast = fast->next;
    }
    return true;
}
/**
 * BM14 链表的奇偶重排
 * 描述：给定单链表，将链表的奇数位节点和偶数位节点分别放在一起，重排后输出
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @return ListNode类
 */
ListNode* oddEvenList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* odd = new ListNode(-1);
    ListNode* even = new ListNode(-1);
    ListNode* cur = head;
    ListNode* nxt;
    ListNode* cur_odd = odd;
    ListNode* cur_even = even;
    int id = 1;
    while(cur) {
        nxt = cur->next;
        cur->next = nullptr;
        if(id) {// 奇数
            cur_odd->next = cur;
            cur_odd = cur_odd->next;
        }
        else { //偶数
            cur_even->next = cur;
            cur_even = cur_even->next;
        }
        cur = nxt; id ^= 1;
    }
    cur_odd->next = even->next;
    return odd->next;
}
/**
 * BM15 删除有序链表中重复的元素-I
 * 描述：给定非递减单链表， 删除链表中的重复元素，使链表中的所有元素都只出现一次，返回头结点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类 
 * @return ListNode类
 */
ListNode* deleteDuplicatesI(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* cur = head;
    ListNode* tmp;
    while(cur && cur->next) {
        if(cur->val == cur->next->val) {
            tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        }
        else cur = cur->next;
    }
    return head;
}
/**
 * BM16 删除有序链表中重复的元素-II
 * 描述：给定非递减单链表， 删除链表中所有重复元素，只保留原链表中只出现一次的元素，返回头结点
 * 要求：空间复杂度O(1) 时间复杂度O(n)
 * 
 * @param head ListNode类   
 * @return ListNode类
 */
ListNode* deleteDuplicatesII(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* newHead = new ListNode(-1);
    newHead->next = head;
    ListNode* pre = newHead;
    ListNode* cur = head;
    ListNode* tmp;
    while(cur && cur->next) {
        if(cur->val != cur->next->val) {
            pre = cur; cur = cur->next;
            continue;
        }
        while(cur->next && cur->val == cur->next->val) {
            tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        }
        tmp = cur->next;
        pre->next = tmp;
        delete cur;
        cur = tmp;
    }
    return newHead->next;
}
};
int main()
{
    cout << "Hello LinkList" << endl;
    return 0;
}