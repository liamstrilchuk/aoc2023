#include <bits/stdc++.h>

using namespace std;

#define cardt vector<pair<vector<int>, vector<int>>>

cardt get_cards(vector<string>& lines) {
	cardt cards;
	for (string line : lines) {
		bool hit_colon = false, hit_pipe = false;
		string cur = "";
		pair<vector<int>, vector<int>> card;

		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ':') {
				hit_colon = true;
				continue;
			}

			if (line[i] == '|') {
				hit_pipe = true;
				continue;
			}

			if (hit_colon && isdigit(line[i])) {
				cur += line[i];
			}

			if (line[i] == ' ' || i == line.size() - 1) {
				if (cur.size() > 0) {
					if (hit_pipe) {
						card.second.push_back(stoi(cur));
					} else if (hit_colon) {
						card.first.push_back(stoi(cur));
					}
					cur = "";
				}
				continue;
			}
		}

		cards.push_back(card);
	}

	return cards;
}

int get_matches(pair<vector<int>, vector<int>> card) {
	int matches = 0;
	for (int i = 0; i < card.first.size(); i++) {
		for (int j = 0; j < card.second.size(); j++) {
			if (card.first[i] == card.second[j]) {
				matches++;
			}
		}
	}
	return matches;
}

int part1(cardt cards) {
	int points = 0;
	for (auto card : cards) {
		points += get_matches(card);
	}

	return points;
}

int part2(cardt cards) {
	vector<int> instances;

	for (auto card : cards) {
		instances.push_back(1);
	}

	for (int i = 0; i < cards.size(); i++) {
		int matches = get_matches(cards[i]);
		for (int j = i + 1; j < min((int) cards.size(), i + matches + 1); j++) {
			instances[j] += instances[i];
		}
	}

	int sum = 0;
	for (int i = 0; i < instances.size(); i++) {
		sum += instances[i];
	}
	return sum;
}

int main() {
	ifstream fin("day4.in");
	vector<string> lines;
	string line;

	while (getline(fin, line)) {
		lines.push_back(line);
	}

	cardt cards = get_cards(lines);

	cout << "Part 1: " << part1(cards) << endl;
	cout << "Part 2: " << part2(cards) << endl;
}