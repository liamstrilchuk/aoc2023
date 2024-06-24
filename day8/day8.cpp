#include <bits/stdc++.h>

using namespace std;
typedef map<string, pair<string, string>> rules_t;

int part1(string directions, rules_t& rules) {
	int steps = 0;
	string current = "AAA";

	while (current != "ZZZ") {
		string prev = current;
		char dir = directions[steps % directions.size()];
		current = dir == 'L' ? rules[current].first : rules[current].second;
		steps++;
	}

	return steps;
}

long long int part2(string directions, rules_t& rules) {
	int steps = 0;
	vector<string> current_nodes;
	vector<int> repeats;

	for (auto elem : rules) {
		if (elem.first[2] == 'A') {
			current_nodes.push_back(elem.first);
			repeats.push_back(0);
		}
	}

	for (int i = 0; i < current_nodes.size(); i++) {
		string current = current_nodes[i];
		int steps = 0;

		while (current[2] != 'Z') {
			char dir = directions[steps % directions.size()];
			current = dir == 'L' ? rules[current].first : rules[current].second;
			steps++;
		}

		repeats[i] = steps;
	}

	long long int mul = 1;

	for (int i = 0; i < current_nodes.size(); i++) {
		mul = lcm(mul, repeats[i]);
	}

	return mul;
}

int main() {
	ifstream fin("day8.in");
	string line;
	string directions;
	rules_t rules;

	while (getline(fin, line)) {
		if (line.size() == 0) {
			continue;
		}
		if (line.size() < 4 || line[3] != ' ') {
			directions = line;
			continue;
		}

		rules[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
	}

	cout << "Part 1: " << part1(directions, rules) << endl;
	cout << "Part 2: " << part2(directions, rules) << endl;
}