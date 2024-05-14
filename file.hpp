#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int distMoney(int money, int children) {
        if (money < children)
            return -1;
        int arr[children];
        fill(arr, arr + children, 1);
        money -= children;
        while (1)
        {
            int br = 0;
            // int is_8 = 0;
            for (int i = 0; i < children; i++)
            {
                if (arr[i] < 8 && money >= 8 - arr[i])
                {
                    int val = 8 - arr[i];
                    arr[i] += val;
                    money -= val;
                }
                else if (i == children - 1)
                {
                    if (arr[i] + money != 4)
                    {
                        arr[i] += money;
                        money = 0;
                    }
                    else
                    {
                        if (i == 0)
                            return -1;
                        else
                        {
                            arr[i] += money - 1;
                            arr[i - 1] += 1;
                        }
                    }
                }
                if (!money)
                {
                    br = 1;
                    break ;
                }
            }
            if (br)
                break ;
        }
		int res = 0;
		for (int i = 0; i < children; i++)
		{
			if (arr[i] == 8)
				res++;
		}
		return res;
    }
};