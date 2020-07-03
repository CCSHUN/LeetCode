/*
    功能：两个有序vector合并，合并后仍然有序
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//合并,从小到大排序
void merge(vector<int>& dst, const vector<int>& left, const vector<int>& right)
{
    int left_size = left.size() - 1;
    int right_size = right.size() - 1;
    int dst_index = 0;
    int left_index = 0;
    int right_index = 0;

    while (left_index <= left_size && right_index <= right_size)
    {
        if (left[left_index] < right[right_index])
        {
            //dst[dst_index++] = left[left_index++]; 没有分配空间会段错误
            dst.emplace_back(left[left_index++]);
        }
        else 
        {
            //dst[dst_index++] = right[right_index++]; 没有分配空间会段错误
            dst.emplace_back(right[right_index++]);
        }
    }
    //判断哪个vector先结束
    if (left_size < left_index)
    {
        dst.insert(dst.end(), right.begin() + right_index, right.end());
    }
    else 
    {
        dst.insert(dst.end(), left.begin() + left_index, left.end());
    }
}

int main()
{
    vector<int> left{1, 2, 3};
    vector<int> right{2, 4, 5};

    vector<int> dst;
    merge(dst, left, right);
    cout<<"合并后:";
    for (const auto& i : dst)
    {
        cout<<i<<",";
    }
    cout<<endl;


	return 0;
}
