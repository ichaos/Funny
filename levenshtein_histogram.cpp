/*
 * check if a string is within a given levenshtein distance to any string in a dictionary
 * credit: Leo Polovets
 * see more on quora: https://www.quora.com/Algorithms/Which-is-the-best-programming-algorithm-that-you-have-ever-created
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

int levenshtein_distance(string a, string b) {
	int m = a.size();
	int n = b.size();

	int dp[m + 1][n + 1];

	for (int i = 0; i <= m; i++) {
		dp[i][0] = i;
	}

	for (int i = 0; i <= n; i++) {
		dp[0][i] = i;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			dp[i + 1][j + 1] = dp[i][j] + (a[i] == b[j]) ? 0 : 1; 
			dp[i + 1][j + 1] = min(dp[i][j + 1] + 1, dp[i + 1][j + 1]);
			dp[i + 1][j + 1] = min(dp[i + 1][j] + 1, dp[i + 1][j + 1]);
		}
	}
	return dp[m][n];
}

void str_to_histogram(string s, int *hisA, int n) {
	for (int i = 0; i < n; i++)
		hisA[i] = 0;

	for (int i = 0; i < s.size(); i++) {
		hisA[s[i] % n]++;
	}
}

int levenshtein_histogram(string a, vector<string> &dict, int d) {
	int hisA[64 / 4];
	str_to_histogram(a, hisA);
	int m = a.size();
	int hisT[64 / 4];
	for (int i = 0; i < dict.size(); i++) {
		str_to_histogram(dict[i], hisT);
		int lowerbound = abs(m - dict[i].size());
		for (int j = 0; j < 16; j++) {
			lowerbound += abs(hisT[j] - hisA[j]);
		}
		lowerbound /= 2;
		if (lowerbound <= d) {
			lowerbound = levenshtein_distance(a, dict[i]);
			if (lowerbound <= d) return 1;
		}
	}
	return 0;
}