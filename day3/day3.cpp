#include <bits/stdc++.h>

using namespace std;

void make_gear(map<pair<int, int>, pair<int, int>>& gears, int y, int x, int num) {
	if (gears.find({y, x}) == gears.end()) {
		gears[{y, x}] = {0, 1};
	}
	gears[{y, x}].first += 1;
	gears[{y, x}].second *= num;
}

int part1(vector<string>& lines) {
	int sum = 0;
	for (int y = 0; y < lines.size(); y++) {
		string current_num = "";
		for (int x = 0; x < lines[y].size(); x++) {
			if (isdigit(lines[y][x])) {
				current_num += lines[y][x];
			}

			if ((!isdigit(lines[y][x]) || x == lines[y].size() - 1) && current_num.size() > 0) {
				if (x == lines[y].size() - 1 && isdigit(lines[y][x])) {
					x++;
				}
				bool has_symbol = false;
				for (int x1 = x - current_num.size() - 1; x1 < x + 1; x1++) {
					if (x1 < 0 || x1 >= lines[y].size()) {
						continue;
					}
					if ((y > 0 && lines[y - 1][x1] != '.') || (y < lines.size() - 1 && lines[y + 1][x1] != '.')) {
						has_symbol = true;
						break;
					}
				}
				if ((x - ((int) current_num.size()) - 1 >= 0 && lines[y][x - current_num.size() - 1] != '.') ||
					(x <= lines[y].size() - 1 && lines[y][x] != '.')) {
					has_symbol = true;
				}
				if (has_symbol) {
					sum += stoi(current_num);
				}
				current_num = "";
			}
		}
	}

	return sum;
}

int part2(vector<string>& lines) {
	map<pair<int, int>, pair<int, int>> gears;
	for (int y = 0; y < lines.size(); y++) {
		string current_num = "";
		for (int x = 0; x < lines[y].size(); x++) {
			if (isdigit(lines[y][x])) {
				current_num += lines[y][x];
			}

			if ((!isdigit(lines[y][x]) || x == lines[y].size() - 1) && current_num.size() > 0) {
				if (x == lines[y].size() - 1 && isdigit(lines[y][x])) {
					x++;
				}
				for (int x1 = x - current_num.size() - 1; x1 < x + 1; x1++) {
					if (x1 < 0 || x1 >= lines[y].size()) {
						continue;
					}
					if (y > 0 && lines[y - 1][x1] == '*') {
						make_gear(gears, y - 1, x1, stoi(current_num));
					}
					if (y < lines.size() - 1 && lines[y + 1][x1] == '*') {
						make_gear(gears, y + 1, x1, stoi(current_num));
					}
				}

				if (x - ((int) current_num.size()) - 1 >= 0 && lines[y][x - current_num.size() - 1] == '*') {
					make_gear(gears, y, x - current_num.size() - 1, stoi(current_num));
				}

				if (x <= lines[y].size() - 1 && lines[y][x] == '*') {
					make_gear(gears, y, x, stoi(current_num));
				}

				current_num = "";
			}
		}
	}

	int sum = 0;

	for (auto gear : gears) {
		if (gear.second.first != 2) {
			continue;
		}
		sum += gear.second.second;
	}

	return sum;
}

int main() {
	ifstream fin("day3.in");

	vector<string> lines;
	string line;

	while (getline(fin, line)) {
		lines.push_back(line);
	}

	cout << "Part 1: " << part1(lines) << endl;
	cout << "Part 2: " << part2(lines) << endl;
}