#include <bits/stdc++.h>

using namespace std;

vector<pair<string, int>> get_matches(string line) {
	vector<pair<string, int>> matches;
	regex r ("\\d+ [a-z]+");

	smatch m;
	regex_token_iterator<string::iterator> it(line.begin(), line.end(), r);
	regex_token_iterator<string::iterator> end;

	while (it != end) {
		string cur = *it;
		int num = stoi(cur.substr(0, cur.find(" ")));
		string color = cur.substr(cur.find(" ") + 1);

		matches.push_back({color, num});
		it++;
	}

	return matches;
}

int part1(vector<string>& lines) {
	map<string, int> maxes = {{"red", 12}, {"green", 13}, {"blue", 14}};
	int sum = 0;

	for (int i = 0; i < lines.size(); i++) {
		vector<pair<string, int>> matches = get_matches(lines[i]);

		bool possible = true;
		for (int j = 0; j < matches.size(); j++) {
			if (matches[j].second > maxes[matches[j].first]) {
				possible = false;
				break;
			}
		}

		if (possible) {
			sum += i + 1;
		}
	}

	return sum;
}

int part2(vector<string>& lines) {
	int sum = 0;

	for (string line : lines) {
		vector<pair<string, int>> matches = get_matches(line);
		map<string, int> maxes = {{"red", 0}, {"green", 0}, {"blue", 0}};

		for (auto match : matches) {
			maxes[match.first] = max(maxes[match.first], match.second);
		}

		sum += maxes["red"] * maxes["green"] * maxes["blue"];
	}

	return sum;
}

int main() {
	ifstream fin("day2.in");

	vector<string> lines;
	string line;

	while (getline(fin, line)) {
		lines.push_back(line);
	}

	cout << "Part 1: " << part1(lines) << endl;
	cout << "Part 2: " << part2(lines) << endl;
}