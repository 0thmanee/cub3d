#include <iostream>
using namespace std;

void solve()
{
	int n;
	cin >> n;
	char dr;
	for (int i = 0; i < n * 2; i++)
	{
		for (int j = 0; j < n * 2; j++)
		{
			if ((i / 2) % 2 == (j / 2) % 2)
				cout << '#';
			else
				cout << '.'; 
		}
		cout << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	while (n--)
		solve();
}
