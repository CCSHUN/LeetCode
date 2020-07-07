#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
    最大堆
*/
void adjust(vector<int>& array, int len, int index) {
    int max_index = index;
    int left_index = index * 2 + 1;
    int right_index = index * 2 + 2;
    
    if (left_index < len && array[max_index] < array[left_index]) {
        max_index = left_index;
    }
    if (right_index < len && array[max_index] < array[right_index]) { //
        max_index = right_index;
    }   
    if (max_index != index) {
        swap(array[index], array[max_index]);
        adjust(array, len, max_index);
    }
}

void MakeMaxHeap(vector<int>& array, int len) {
    //int len = array.size();
    for (int i = (len - 1) / 2 ; i >= 0; i--) {
        adjust(array, len, i);
    }
}

void SortHeap(vector<int>& array) {
    int len = array.size();
    MakeMaxHeap(array, len); //建最大堆
    //堆排序
    for (int i = (len - 1); i >= 0; i--) {
        swap(array[i], array[0]);
        adjust(array, i, 0);
    }
}

int main()
{
    //vector<int> array{2, 4, 3, 7, 5, 8}; 
    vector<int> array{2, 3, 1, 5}; 
    SortHeap(array);
    
    for (int i = 0; i < array.size(); i++) {
        cout<<array[i]<<",";
    }
    cout<<endl;

	return 0;
}






