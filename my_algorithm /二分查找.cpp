#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
	使用stl算法
*/
bool isSearch_stl(const vector<int>& srcVt, int val)
{
  	bool isFound = std::binary_search(srcVt.begin(), srcVt.end(), val);
  	if (isFound)
  	{
  		cout<<"Found..."<<endl;
  	}
  	else
  	{
  		cout<<"Not Found..."<<endl;
  	}

  	return isFound;
}

/*
	使用循环二分查找
*/
bool isSearch_cycle(const vector<int>& srcVt, int val)
{
	int hign = srcVt.size() - 1;
	int mid = hign >> 1;
	int low = 0;

	bool isFound = false;
	while(low <= hign)
	{
		if (val == srcVt[mid])
		{
			isFound = true;
			break;
		}
		else if (val > srcVt[mid])
		{
			low = mid + 1;
			mid = (hign + low) >> 1;
		}
		else
		{
			hign = mid + 1;
			mid = (hign + low) >> 1;
		}
	}

	if (isFound)
  	{
  		cout<<"Found..."<<endl;
  	}
  	else
  	{
  		cout<<"Not Found..."<<endl;
  	}

  	return isFound;
}


/*
	递归实现
*/
bool isSearch_rec(const vector<int>& srcVt, int low, int hign, int val)
{
	int mid = (low + hign) >> 1;
	if (low <= hign)
	{
		if (val == srcVt[mid])
		{
			cout<<"Found..."<<endl;
			return true;
		}
		else if (val > srcVt[mid])
		{
			low = mid + 1;
			return isSearch_rec(srcVt, low, hign, val);
		}
		else
		{
			hign = mid + 1;
			return isSearch_rec(srcVt, low, hign, val);
		}
	}
	else
	{
		cout<<"Not Found..."<<endl;
		return false;
	}
}

int main()
{
	int myints[] = {1,2,3,4,5,4,3,2,1};
  	std::vector<int> v(myints,myints+9);                         // 1 2 3 4 5 4 3 2 1

  	// using stl
  	std::sort(v.begin(), v.end());
  	isSearch_stl(v, 6);
  	isSearch_stl(v, 3);

  	//using cycle seach
  	isSearch_cycle(v, 6);
  	isSearch_cycle(v, 3);

  	//using rec
  	int low = 0;
  	int hign = 8;
  	isSearch_rec(v, low, hign, 6);
	isSearch_rec(v, low, hign, 3);

	return 0;
}






