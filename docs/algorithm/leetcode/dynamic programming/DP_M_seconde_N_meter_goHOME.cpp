#include<bits/stdc++.h>
#define inf  100
using namespace std;

typedef long long ll;
int main()
{
	int m, n;
	//vector<vector<int> >dp(1000,)
	//int dp[100001][10001];
	vector< vector<int> > dp(1001, vector<int>(1001, 0));
	cin >> n >> m;
	int cost[10001];
	for (int i = 1; i <= m; i++)
		cin >> cost[i];
	dp[1][1] = cost[1]/3;
	dp[1][2] = cost[1] / 2;
	dp[1][3] = cost[1];
	for (int i = 4; i <= n; i++)
		dp[1][i] = inf;
	for (int i = 1; i <= m; i++)//second
	{
		dp[0][i] =inf;
	}
	

	for(int i=2;i<=m;i++)//second
		for (int j = 1; j <= n; j++)//distance
		{
			vector<int> v;
			v.push_back(dp[i - 1][j]);
			if (j - 1 >= 0)
				v.push_back(dp[i - 1][j - 1] + cost[i] / 3);
			if (j - 2 >= 0)
				v.push_back(dp[i - 1][j - 2] + cost[i] / 2);
			if (j - 3 >= 0)
				v.push_back(dp[i - 1][j - 3] + cost[i]);
			
			sort(v.begin(), v.end());
			dp[i][j] = v[0];
		}
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}
	system("pause");
	/*
	5 5
10000 2 3 4 10000*/
	return 0;
}