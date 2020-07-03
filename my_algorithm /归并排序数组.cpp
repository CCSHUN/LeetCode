#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//合并,从小到大排序
void merge(vector<int>& src, int left, int mid, int right)
{
    int left_index = left;
    int right_index = mid + 1;
    
    vector<int> help;

    while (left_index <= mid && right_index <= right)   //eg: ((1->3)->(2->4)) to 1->2->3->4 
    {
        if (src[left_index] < src[right_index])
        {
            //help[left_index++] = src[left_index]; 这种做法会段错误
            help.emplace_back(src[left_index++]);
        }
        else 
        {
            help.emplace_back(src[right_index++]);
        }   
    }
    //判断左右哪个没有遍历完
    if (left_index > mid)
    {
        help.insert(help.end(), src.begin() + right_index, src.begin() + right + 1); //疑问为什么要 +1
    }
    else
    {
        help.insert(help.end(), src.begin() + left_index, src.begin() + mid + 1);   //疑问为什么要 +1
    }
    //交换help和 src的内容
    //src.swap(help); 不能这样做，会清空原来已经归并的元素
    for (const auto& i : help)
    {
       src[left++] = i; 
    }
}

/*
    使用递归归并排序
*/
void sort_rec(vector<int>& srcVt, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) >> 1;
        sort_rec(srcVt, left, mid);
        sort_rec(srcVt, mid + 1, right);
        merge(srcVt, left, mid, right);
    }
    
}

/*
    使用迭代归并排序
*/
void sort_cycle(vector<int>& srcVt, int left, int right)
{
    int len = srcVt.size();
    if (1 >= len)
    {
        return;
    }
    else
    {
        for (int i = 1; i < len; i <<= 1)
        {
            for (int j = 0; j < len; j++)
            {
                int left = j;
                if ((j + 2*i) >= len)
                {
                    right = len - 1;
                }
                else
                {
                    right = j + 2*i;
                }
                int mid = (right + left) >> 1;
                merge(srcVt, left, mid, right);
            }
        }
    }
    
}

int main()
{
    vector<int> array{1, 3, 7, 2, 4, 8, 10, 11, 15, 7};

    //sort_rec(array, 0, 9);
    sort_cycle(array, 0, 9);
    cout<<"合并后:";
    for (const auto& i : array)
    {
        cout<<i<<",";
    }
    cout<<endl;

	return 0;
}






