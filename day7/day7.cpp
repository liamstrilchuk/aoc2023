#include <bits/stdc++.h>

using namespace std;

int hand_type(map<int, int> counts) {
	if (counts[5] == 1) { return 6; }
	if (counts[4] == 1) { return 5; }
	if (counts[3] == 1 && counts[2] == 1) { return 4; }
	if (counts[3] == 1 && counts[1] == 2) { return 3; }
	if (counts[2] == 2 && counts[1] == 1) { return 2; }
	if (counts[2] == 1 && counts[1] == 3) { return 1; }

	return 0;
}

map<int, int> get_hand_counts(string hand) {
	map<char, int> chars;

	for (char c : hand) {
		if (chars.find(c) == chars.end()) {
			chars[c] = 0;
		}
		chars[c]++;
	}

	map<int, int> counts = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};

	for (auto it = chars.begin(); it != chars.end(); it++) {
		if (counts.find(it->second) == counts.end()) {
			counts[it->second] = 0;
		}
		counts[it->second]++;
	}
	
	return counts;
}

int get_hand_strength(string hand, bool jokers_are_wild) {
	if (!jokers_are_wild) {
		return hand_type(get_hand_counts(hand));
	}

	vector<char> cards_to_replace = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'T',
									 'Q', 'K', 'A'};
	
	int max_strength = 0;
	for (char c : cards_to_replace) {
		string temp = hand;
		replace(temp.begin(), temp.end(), 'J', c);
		max_strength = max(max_strength, hand_type(get_hand_counts(temp)));
	}
	return max_strength;
}

struct sort_hands {
	map<char, int> card_strengths;
	bool jokers_are_wild;

	bool operator()(pair<string, int> a, pair<string, int> b) {
		int as = get_hand_strength(a.first, jokers_are_wild), bs = get_hand_strength(b.first, jokers_are_wild);
		if (as != bs) {
			return as < bs;
		}
		for (int c = 0; c < 5; c++) {
			if (card_strengths[a.first[c]] != card_strengths[b.first[c]]) {
				return card_strengths[a.first[c]] < card_strengths[b.first[c]];
			}
		}
		return false;
	}
};

int part1(vector<pair<string, int>> hands) {
	map<char, int> card_strengths = {{'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
									 {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10},
									 {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};

	sort(hands.begin(), hands.end(), sort_hands({card_strengths, false}));
	int total = 0;

	for (int i = 0; i < hands.size(); i++) {
		total += hands[i].second * (i + 1);
	}

	return total;
}

int part2(vector<pair<string, int>> hands) {
	map<char, int> card_strengths = {{'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
									 {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10},
									 {'J', 0}, {'Q', 12}, {'K', 13}, {'A', 14}};

	sort(hands.begin(), hands.end(), sort_hands({card_strengths, true}));
	int total = 0;

	for (int i = 0; i < hands.size(); i++) {
		total += hands[i].second * (i + 1);
	}

	return total;
}

int main() {
	ifstream fin("day7.in");
	vector<pair<string, int>> hands;
	string line;

	while (getline(fin, line)) {
		hands.push_back({
			line.substr(0, 5),
			stoi(line.substr(6, line.size() - 6))
		});
	}

	cout << "Part 1: " << part1(hands) << endl;
	cout << "Part 2: " << part2(hands) << endl;
}