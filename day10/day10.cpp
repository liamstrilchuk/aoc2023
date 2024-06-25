#include <bits/stdc++.h>

using namespace std;

map<char, pair<pair<int, int>, pair<int, int>>> tiles = {
	{'|', make_pair(make_pair(0, -1), make_pair(0, 1))},
	{'-', make_pair(make_pair(-1, 0), make_pair(1, 0))},
	{'L', make_pair(make_pair(0, -1), make_pair(1, 0))},
	{'J', make_pair(make_pair(0, -1), make_pair(-1, 0))},
	{'7', make_pair(make_pair(0, 1), make_pair(-1, 0))},
	{'F', make_pair(make_pair(0, 1), make_pair(1, 0))}
};

int hash_pos(vector<vector<char>>& grid, int x, int y) {
	return x + grid[0].size() * y;
}

pair<int, int> unhash(vector<vector<char>>& grid, int hash) {
	return make_pair(hash % grid[0].size(), floor(hash / grid[0].size()));
}

bool is_in_grid(vector<vector<char>>& grid, pair<int, int> pos) {
	return pos.first >= 0 && pos.second >= 0 && pos.first < grid[0].size() && pos.second < grid.size();
}

vector<pair<int, int>> get_neighbours(vector<vector<char>>& grid, int x, int y) {
	if (!is_in_grid(grid, make_pair(x, y)) || !tiles.count(grid[y][x])) {
		return {};
	}

	auto p1 = make_pair(tiles[grid[y][x]].first.first + x, tiles[grid[y][x]].first.second + y);
	auto p2 = make_pair(tiles[grid[y][x]].second.first + x, tiles[grid[y][x]].second.second + y);

	vector<pair<int, int>> pos;

	if (is_in_grid(grid, p1)) {
		pos.push_back(p1);
	}

	if (is_in_grid(grid, p2)) {
		pos.push_back(p2);
	}

	return pos;
}

set<int> find_path(vector<vector<char>>& grid, int start_x, int start_y) {
	vector<pair<int, int>> init_neighbours = { make_pair(0, -1), make_pair(0, 1), make_pair(1, 0), make_pair(-1, 0) };
	set<int> explored = { hash_pos(grid, start_x, start_y) };
	int current, next;
	bool should_cont = true;
	
	for (auto p : init_neighbours) {
		auto ns = get_neighbours(grid, start_x + p.first, start_y + p.second);
		for (int i = 0; i < ns.size(); i++) {
			if (ns[i].first == start_x && ns[i].second == start_y) {
				current = hash_pos(grid, start_x + p.first, start_y + p.second);
				explored.insert(current);
				should_cont = false;
				next = hash_pos(grid, ns[1 - i].first, ns[1 - i].second);
			}
		}

		if (!should_cont) {
			break;
		}
	}

	while (true) {
		current = next;
		explored.insert(current);

		for (auto n : get_neighbours(grid, unhash(grid, current).first, unhash(grid, current).second)) {
			if (!explored.count(hash_pos(grid, n.first, n.second))) {
				next = hash_pos(grid, n.first, n.second);
			}
		}

		if (next == current) {
			break;
		}
	}

	return explored;
}

int part1(vector<vector<char>>& grid, int ax, int ay) {
	return find_path(grid, ax, ay).size() / 2;
}

int part2(vector<vector<char>>& grid, int ax, int ay) {
	auto path = find_path(grid, ax, ay);
	map<int, vector<int>> rows;

	for (int hashed : path) {
		if (!rows.count(unhash(grid, hashed).second)) {
			rows[unhash(grid, hashed).second] = {};
		}

		rows[unhash(grid, hashed).second].push_back(unhash(grid, hashed).first);
	}

	int total = 0;

	for (auto row : rows) {
		vector<int> pipes = row.second;
		sort(pipes.begin(), pipes.end());
		bool in = false;
		int in_between = 0, start;
		char last_symbol = 0;

		for (int i = 0; i < pipes.size(); i++) {
			char symbol = grid[row.first][pipes[i]];
			in_between++;

			if (symbol == '|') {
				if (in) {
					total += pipes[i] - start - in_between;
				} else {
					start = pipes[i];
				}
				in = !in;
				in_between = 0;
			} else if (symbol == 'L' || symbol == 'J' || symbol == '7' || symbol == 'F') {
				if (!last_symbol) {
					last_symbol = symbol;
				} else {
					if ((last_symbol == 'L' && symbol == 'J') || (last_symbol == 'F' && symbol == '7')) {
						last_symbol = 0;
						continue;
					} else {
						if (in) {
							total += pipes[i] - start - in_between;
						} else {
							start = pipes[i];
						}
						in = !in;
						last_symbol = 0;
						in_between = 0;
					}
				}
			}
		}
	}

	return total;
}

int main() {
	ifstream fin("day10.in");
	string line;

	vector<vector<char>> grid;
	int ax = 0, ay = 0;

	while (getline(fin, line)) {
		grid.push_back({});

		for (int i = 0; i < line.length(); i++) {
			grid[grid.size() - 1].push_back(line[i]);

			if (line[i] == 'S') {
				ax = grid[grid.size() - 1].size() - 1;
				ay = grid.size() - 1;
			}
		}
	}

	grid[ay][ax] = '|';

	cout << "Part 1: " << part1(grid, ax, ay) << endl;
	cout << "Part 2: " << part2(grid, ax, ay) << endl;
}