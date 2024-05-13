#include <iostream>
using namespace std;

int	is_binary(string n)
{
	for (int i = 0; i < n.size(); i++)
		if (n[i] != '0' && n[i] != '1')
			return (0);
	return (1);
}

void solve()
{
	string n;
	cin >> n;
	int bin_nbrs[] = {10, 11, 100, 101, 110, 111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111, 10000, 10001, 10010, 10011, 10100, 10101, 10110, 10111, 11000, 11001, 11010, 11011, 11100, 11101, 11110, 11111, 100000, 100001, 100010, 100011, 100100, 100101, 100110, 100111, 101000, 101001, 101010, 101011, 101100, 101101, 101110, 101111, 110000, 110001, 110010, 110011, 110100, 110101, 110110, 110111, 111000, 111001, 111010, 111011, 111100, 111101, 111110, 111111};
	if (is_binary(n))
	{
		cout << "YES\n";
		return ;
	}
	int nbr = atoi(n.c_str());
	while (nbr > 1)
	{
		int is_div = 0;
		for (int i = 0; i < 62; i++)
		{
			if (nbr % bin_nbrs[i] == 0)
			{
				nbr /= bin_nbrs[i];
				is_div = 1;
				break ;
			}
		}
		if (!is_div)
		{
			cout << "NO\n";
			return ;
		}
	}
	cout << "YES\n";
}

int main()
{
	int n;
	cin >> n;
	while (n--)
		solve();
}