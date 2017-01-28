#include <bits/stdc++.h>

using namespace std;

int main () {
	vector<int> temp;
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(0);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	int a,b;
	a = b =1;
	printf("%d\n", accumulate(temp.begin(), temp.end(),0));
	printf("%d %d\n", a, b);
	return 0;
}