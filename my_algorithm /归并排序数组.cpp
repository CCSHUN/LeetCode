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

/*
    使用递归归并排序
*/
void sort_rec(vector<int>& dst, vector<int>& srcVt, int left, int right)
{
    int mid = (left + right) >> 1;
    if (left <= right)  //分割到2个元素的时候不再分割 
    {
        return merge(dst, sort_rec(dst, srcVt, left, mid),sort_rec(dst, srcVt, mid + 1, right)); 
    }
    else 
    {
        //return merge((srcVt.begin() + left,  srcVt.begin() + mid), 
        //(srcVt.begin() + mid + 1, srcVt.begin() + right));
    }
}

int main()
{
    vector<int> array{3, 1, 2};

    vector<int> dst;
    sort_rec(dst, array, 0, 2);
    cout<<"排序后:";
    for (const auto& i : dst)
    {
        cout<<i<<",";
    }
    cout<<endl;


	return 0;
}






