#include <iostream>
using namespace std;

void solve()
{
	string s;
	cin >> s;
	int h = atoi((s.substr(0, 2)).c_str());
	int m = atoi((s.substr(3, 2)).c_str());
	if (h && h <= 12)
	{
		cout << s;
		if (h == 12)
			cout << " PM" << endl;
		else
			cout << " AM" << endl;
		return ;
	}
	if (h == 0)
		h = 12;
	else
		h -= 12;
	if (h <= 9)
		cout << "0";
	cout << h << ":";
	if (m <= 9)
		cout << "0";
	cout << m;
	if (h == 12)
		cout << " AM" << endl;
	else cout << " PM" << endl;
}

int main()
{
	int n;
	cin >> n;
	while (n--)
		solve();
}