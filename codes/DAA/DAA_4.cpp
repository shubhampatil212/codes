#include <iostream>
#include <vector>
#include <algorithm>
// formula - v[i,w] = max{ v[i-1,w], v[i-1,w-w[i]] + p[i]}
using namespace std;    

int knapsack(int W, const vector<int>& wt, const vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }       
        }
    }

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> val(n), wt(n);
// 10 1
// 15 2
// 40 3
// 5
    cout << "Enter the values and weights of the items:\n";
    for (int i = 0; i < n; ++i) {
        cin >> val[i] >> wt[i];
    }

    cout << "Enter the knapsack capacity: ";
    cin >> W;

    int max_value = knapsack(W, wt, val, n);
    cout << "Maximum value: " << max_value << endl;

    return 0;
}