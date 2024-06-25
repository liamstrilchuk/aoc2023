#include <bits/stdc++.h>

using namespace std;

long long int expand_and_total(vector<vector<int>> grid, int factor) {
	vector<pair<int, int>> galaxies;

	for (int y = 0; y < grid.size(); y++) {
		for (int x = 0; x < grid[y].size(); x++) {
			if (grid[y][x] == 1) {
				galaxies.push_back(make_pair(x, y));
			}
		}
	}

	vector<pair<int, int>> galaxies_copy = galaxies;

	for (int y = 0; y < grid.size(); y++) {
		int sum = 0;
		for (int elem : grid[y]) {
			sum += elem;
		}
		if (!sum) {
			for (int i = 0; i < galaxies.size(); i++) {
				if (galaxies_copy[i].second > y) {
					galaxies[i].second += factor - 1;
				}
			}
		}
	}

	for (int x = 0; x < grid[0].size(); x++) {
		int sum = 0;
		for (int y = 0; y < grid.size(); y++) {
			sum += grid[y][x];
		}
		if (!sum) {
			for (int i = 0; i < galaxies.size(); i++) {
				if (galaxies_copy[i].first > x) {
					galaxies[i].first += factor - 1;
				}
			}
		}
	}

	long long int total = 0;

	for (int g = 0; g < galaxies.size(); g++) {
		for (int g2 = g + 1; g2 < galaxies.size(); g2++) {
			long long int dist = abs(galaxies[g].first - galaxies[g2].first) + abs(galaxies[g].second - galaxies[g2].second);
			total += dist;
		}
	}

	return total;
}

long long int part1(vector<vector<int>> grid) {
	return expand_and_total(grid, 2);
}

long long int part2(vector<vector<int>> grid) {
	return expand_and_total(grid, 1000000);
}

int main() {
	ifstream fin("day11.in");
	string line;

	vector<vector<int>> grid;

	while (getline(fin, line)) {
		grid.push_back({});

		for (char c : line) {
			grid[grid.size() - 1].push_back(c == '.' ? 0 : 1);
		}
	}

	cout << "Part 1: " << part1(grid) << endl;
	cout << "Part 2: " << part2(grid) << endl;
}