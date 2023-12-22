#include <bits/stdc++.h>

using namespace std;

vector<int> get_ints(string line) {
	vector<int> arr;
	string cur;
	for (char c : line) {
		if (isdigit(c)) {
			cur += c;
		} else if (c == ' ' && cur.size() > 0) {
			arr.push_back(stoi(cur));
			cur = "";
		}
	}
	if (cur.size() > 0) {
		arr.push_back(stoi(cur));
	}
	return arr;
}

long int part1(vector<int>& times, vector<int>& distances) {
	long int product = 1;
	for (int r = 0; r < times.size(); r++) {
		int total = 0;
		for (int s = 0; s < times[r]; s++) {
			int distance = s * (times[r] - s);
			if (distance > distances[r]) {
				total += 1;
			}
		}
		product *= total;
	}
	return product;
}

long int part2(vector<int>& times, vector<int>& distances) {
	string combined_times = "", combined_distances = "";
	for (int i = 0; i < times.size(); i++) {
		combined_times += to_string(times[i]);
		combined_distances += to_string(distances[i]);
	}
	long int t = stol(combined_times), d = stol(combined_distances);
	int min, max;
	for (int i = 0; i < t; i++) {
		if (i * (t - i) > d) {
			min = i;
			break;
		}
	}
	for (int i = t; i > -1; i--) {
		if (i * (t - i) > d) {
			max = i;
			break;
		}
	}

	return max - min + 1;
}

int main() {
	ifstream fin("day6.in");
	string line;

	getline(fin, line);
	vector<int> times = get_ints(line);

	getline(fin, line);
	vector<int> distances = get_ints(line);

	cout << "Part 1: " << part1(times, distances) << endl;
	cout << "Part 2: " << part2(times, distances) << endl;
}