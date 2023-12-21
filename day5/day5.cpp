#include <bits/stdc++.h>

using namespace std;

#define map_type map<string, vector<vector<long int>>>
#define range_type pair<long int, long int>

vector<string> split(string s, string d) {
	vector<string> res;
	size_t pos = 0;
	string token;
	while ((pos = s.find(d)) != std::string::npos) {
		token = s.substr(0, pos);
		res.push_back(token);
		s.erase(0, pos + d.length());
	}
	res.push_back(s);
	return res;
}

long int get_min(vector<long int>& seeds) {
	long int min = numeric_limits<long int>::max();

	for (long int seed : seeds) {
		if (seed < min) {
			min = seed;
		}
	}

	return min;
}

long int part1(map_type& seed_map, vector<string>& combinations, vector<long int> seeds) {
	for (string ctype : combinations) {
		vector<vector<long int>> cur = seed_map[ctype];
		for (int seed_index = 0; seed_index < seeds.size(); seed_index++) {
			for (vector<long int> range : cur) {
				if (seeds[seed_index] >= range[1] && seeds[seed_index] < range[1] + range[2]) {
					seeds[seed_index] = range[0] + seeds[seed_index] - range[1];
					break;
				}
			}
		}
	}

	return get_min(seeds);
}

long int part2(map_type& seed_map, vector<string>& combinations, vector<long int> seeds) {
	vector<range_type> ranges;

	for (int i = 0; i < seeds.size(); i += 2) {
		ranges.push_back({seeds[i], seeds[i] + seeds[i + 1] - 1});
	}

	for (string ctype : combinations) {
		vector<vector<long int>> cur = seed_map[ctype];
		for (int r = 0; r < ranges.size(); r++) {
			range_type range = ranges[r];
			for (vector<long int> replacement_range : cur) {
				pair<long int, long int> real_range = {replacement_range[1], replacement_range[1] + replacement_range[2] - 1};
				if ((real_range.first >= range.first && real_range.first <= range.second) ||
					(real_range.second >= range.first && real_range.second <= range.second) ||
					(real_range.first <= range.first && real_range.second >= range.second)) {
					long int range_min = max(range.first, real_range.first);
					long int range_max = min(range.second, real_range.second);
					long int range_change = replacement_range[1] - replacement_range[0];
					ranges[r] = {range_min - range_change, range_max - range_change};
					if (real_range.first > range.first) {
						ranges.push_back({range.first, real_range.first - 1});
					}
					if (real_range.second < range.second) {
						ranges.push_back({real_range.second + 1, range.second});
					}
					break;
				}
			}
		}
	}

	long int min = numeric_limits<long int>::max();
	for (range_type range : ranges) {
		if (range.first < min) {
			min = range.first;
		}
	}

	return min;
}

int main() {
	ifstream fin("day5.in");
	string line;
	vector<string> combinations;
	map_type seed_map;
	vector<long int> seeds;

	while (getline(fin, line)) {
		vector<string> cur = split(line, " ");
		if (cur.size() == 1) {
			continue;
		}
		if (cur[0] == "seeds:") {
			for (int i = 1; i < cur.size(); i++) {
				seeds.push_back(stol(cur[i]));
			}
			continue;
		}
		if (cur.size() == 2) {
			vector<string> names = split(cur[0], "-");
			combinations.push_back(names[2]);
			seed_map[names[2]] = {};
			continue;
		}
		vector<vector<long int>>* last = &seed_map[combinations[combinations.size() - 1]];
		last->push_back({});
		for (int i = 0; i < cur.size(); i++) {
			last->at(last->size() - 1).push_back(stol(cur[i]));
		}
	}

	cout << "Part 1: " << part1(seed_map, combinations, seeds) << endl;
	cout << "Part 2: " << part2(seed_map, combinations, seeds) << endl;
}