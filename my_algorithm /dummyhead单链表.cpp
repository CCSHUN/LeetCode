/*
    单链表的基本操作
    1.插入、删除、分割，合并，排序(这里用归并排序)
    注意：dummyhead不要用堆空间，容易内存泄漏，面试题如果有手写代码如果你用堆空间100%面试官会diss你
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

struct ListNode{
    ListNode* next;
    int val;
};

class dummySigleList final
{
public:
    dummySigleList();
    dummySigleList(ListNode* node);
    void insert(int pos, int val);
    void insert(int pos, const dummySigleList* list);
    void erase(int pos);
    void show();
    ListNode* cut(ListNode* left, int n); // 切断链表  不改变原来链表结构
    ListNode* merge(ListNode* l1, ListNode* l2); //合并排序好的两个链表
    ListNode* sort_rec(ListNode* list);    //归并排序(递归法) ,从小到大排序
    void sort_cyc();   //归并排序(迭代法),从小到大排序
    void reverse();//反转链表，这里采用就地反转,不断地将链表下一个节点头插
    ListNode* getRealHead();
private:
    ListNode dummyHead_;
};

dummySigleList::dummySigleList()
{
    dummyHead_.next = nullptr;
    dummyHead_.val = -1;
}

dummySigleList::dummySigleList(ListNode* node)
{
    dummyHead_.next = node;
    dummyHead_.val = -1;
}

ListNode* dummySigleList::getRealHead()
{
    return dummyHead_.next;
}

void dummySigleList::insert(int pos, int val)
{
    auto prev = &dummyHead_;
    auto temp = (ListNode *)malloc(sizeof(ListNode));
    assert(nullptr != temp);
    temp->val = val;
    temp->next = nullptr;

    for (int i = 0; i < pos && prev->next != nullptr; i++)
    {
        prev = prev->next;
    }

    temp->next = prev->next;
    prev->next = temp;
}

void dummySigleList::erase(int pos)
{
    auto prev = &dummyHead_;

    for (int i = 0; i < pos && prev->next != nullptr; i++)
    {
        prev = prev->next;
    }

    if (nullptr != prev->next)
    {
        prev->next = prev->next->next;
    }
}

void dummySigleList::show()
{
    auto cur = dummyHead_.next;

    while(cur)
    {
        cout<<cur->val<<",";
        cur = cur->next;
    }
    cout<<endl;
}

void dummySigleList::reverse()
{
    auto cur = dummyHead_.next;
    ListNode* temp = nullptr;

    while(cur->next) //不断头插
    {
        temp = cur->next->next;
        cur->next->next = dummyHead_.next;
        dummyHead_.next = cur->next;
        cur->next = temp;
    }
}

ListNode* dummySigleList::cut(ListNode* left, int n) //断链
{   
    ListNode* cur = left;
    while (--n && cur)
    {
        cur = cur->next;
    }
    if (!cur) //这里没有dummyhead，需要加此判断
    {
        return nullptr;
    }
    ListNode *temp = cur->next;
    cur->next = nullptr; //左链表
    return temp; //右链表
}

ListNode* dummySigleList::merge(ListNode* l1, ListNode* l2) //接链
{
    ListNode dummyHead;
    dummyHead.val = -1;
    dummyHead.next = nullptr;
    auto p = &dummyHead;

    while (l1 && l2) 
    {
        if (l1->val < l2->val) 
        {
            p->next = l1;
            //p = l1;
            l1 = l1->next;       
        } 
        else 
        {
            p->next = l2;
            //p = l2;
            l2 = l2->next;
        }
        p = p->next; 
    }
    p->next = l1 ? l1 : l2;
    return dummyHead.next;
}

ListNode* dummySigleList::sort_rec(ListNode* list)
{
    if (!list->next || !list)
    {
        return list;
    }
    ListNode* slow = list;
    ListNode* fast = list;
    ListNode* pmid = nullptr;

    while (fast && fast->next) //快慢指针求中值
    {
        pmid = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pmid->next = nullptr;
    
    return merge(sort_rec(list), sort_rec(slow));
}

void dummySigleList::sort_cyc()
{
    int len = 0;
    ListNode* cur = dummyHead_.next;
    while (cur) //求链表的长度
    {
        len++;
        cur = cur->next;
    }

    for (int size = 1; size < len; size <<= 1)
    {
        auto cur = dummyHead_.next;
        auto tail = &dummyHead_;
        while (cur)
        {
            ListNode* left_list = cur;
            ListNode* right_list = cut(left_list, size);//左边链表
            cur = cut(right_list, size); //右边链表
            tail->next = merge(left_list, right_list);//cut 之后链表是断开的，这里需要拼接会tail
            while (tail->next) // 拼接后需要保持 tail 为尾部
            {
                tail = tail->next;
            }
        }
    }
}


int main()
{
    dummySigleList list;
    list.insert(0, 1);
    list.insert(0, 2);
    list.insert(0, 3);
    list.insert(0, 4);
    list.show();  //4,3,2,1,
    
    list.reverse();
    list.show();//1,2,3,4,
    
    list.erase(3);
    list.show();  //1,2,3
    
    ListNode* cur = list.cut(list.getRealHead(), 2); //返回右链表指针
    while(cur)
    {
        cout<<cur->val<<",";
        cur = cur->next;
    }
    cout<<endl;  //3,

    dummySigleList list1;
    list1.insert(0, 1);
    list1.insert(0, 3);
    list1.insert(0, 2);
    list1.insert(0, 4);
    //list1.sort_cyc();
    //list1.show(); //1,2,3,4

    list1.sort_rec(list1.getRealHead()); //bugs
    list1.show();
	return 0;
}






