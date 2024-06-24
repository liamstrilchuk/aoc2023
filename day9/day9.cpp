#include <bits/stdc++.h>

using namespace std;

vector<int> deriviate(vector<int> list) {
	vector<int> der;

	for (int i = 1; i < list.size(); i++) {
		der.push_back(list[i] - list[i - 1]);
	}

	return der;
}

vector<vector<int>> get_differences(vector<int>& list) {
	vector<vector<int>> differences;
	differences.push_back(list);

	while (true) {
		vector<int> new_diff = deriviate(differences[differences.size() - 1]);

		bool all_zeroes = true;
		for (int i : new_diff) {
			if (i != 0) {
				all_zeroes = false;
				break;
			}
		}

		if (all_zeroes) {
			break;
		}

		differences.push_back(new_diff);
	}

	return differences;
}

long long int part1(vector<vector<int>>& histories) {
	long long int sum = 0;

	for (auto& list : histories) {
		auto differences = get_differences(list);

		for (int i = differences.size() - 1; i > -1; i--) {
			if (i == differences.size() - 1) {
				differences[i].push_back(differences[i][0]);
				continue;
			}

			differences[i].push_back(differences[i][differences[i].size() - 1] + differences[i + 1][differences[i + 1].size() - 1]);
		}

		sum += differences[0][differences[0].size() - 1];
	}

	return sum;
}

long long int part2(vector<vector<int>>& histories) {
	long long int sum = 0;

	for (auto& list : histories) {
		auto differences = get_differences(list);

		for (int i = differences.size() - 1; i > -1; i--) {
			if (i == differences.size() - 1) {
				differences[i].insert(differences[i].begin(), differences[i][0]);
				continue;
			}

			differences[i].insert(differences[i].begin(), differences[i][0] - differences[i + 1][0]);
		}

		sum += differences[0][0];
	}

	return sum;
}

int main() {
	ifstream fin("day9.in");
	string line;

	vector<vector<int>> histories;

	while (getline(fin, line)) {
		istringstream is(line);
		int n;
		histories.push_back({});
		while (is >> n) {
			histories[histories.size() - 1].push_back(n);
		}
	}
	
	cout << "Part 1: " << part1(histories) << endl;
	cout << "Part 2: " << part2(histories) << endl;
}