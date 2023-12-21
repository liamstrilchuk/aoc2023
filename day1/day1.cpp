#include <bits/stdc++.h>

using namespace std;

int part1(vector<string>& lines) {
	int sum = 0;
	for (string line : lines) {
		string cur;
		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line[i])) {
				cur += line[i];
				break;
			}
		}

		for (int i = line.size() - 1; i > -1; i--) {
			if (isdigit(line[i])) {
				cur += line[i];
				break;
			}
		}

		sum += stoi(cur);
	}
	return sum;
}

int part2(vector<string>& lines) {
	int sum = 0;
	map<string, int> words = {{"nine", 9}, {"eight", 8}, {"seven", 7}, {"six", 6}, {"five", 5}, {"four", 4}, {"three", 3}, {"two", 2}, {"one", 1}};

	for (string line : lines) {
		string cur;
		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line[i])) {
				cur += line[i];
				break;
			}

			bool to_break = false;
			for (auto word : words) {
				if (line.substr(i, word.first.size()) == word.first) {
					cur += to_string(word.second);
					to_break = true;
					break;
				}
			}
			if (to_break) {
				break;
			}
		}

		for (int i = line.size() - 1; i > -1; i--) {
			if (isdigit(line[i])) {
				cur += line[i];
				break;
			}

			bool to_break = false;
			for (auto word : words) {
				if (line.substr(i, word.first.size()) == word.first) {
					cur += to_string(word.second);
					to_break = true;
					break;
				}
			}
			if (to_break) {
				break;
			}
		}

		sum += stoi(cur);
	}

	return sum;
}

int main() {
	ifstream fin("day1.in");

	vector<string> lines;
	string line;
	while (fin >> line) {
		lines.push_back(line);
	}

	cout << "Part 1: " << part1(lines) << endl;
	cout << "Part 2: " << part2(lines) << endl;
}
