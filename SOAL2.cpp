#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;

map<char, vector<pair<char, int>>> graf;
map<char, string> namaKota = {
	{'A', "Ikan Bakar Pak Harry"},
	{'B', "Gudang Kaleng Bekas"},
	{'C', "Sushi Kucing Alya"},
	{'D', "Kedai IKLC"},
	{'E', "Pasar Ikan Tengah Malam"}
};

void DFS(char node, set<char>& visited) {
	visited.insert(node);
	cout << node;
	for (auto tetangga : graf[node]) {
		if (!visited.count(tetangga.first)) {
			cout << " -> ";
			DFS(tetangga.first, visited);
		}
	}
}

void BFS(char start, char goal) {
	queue<vector<char>> q;
	set<char> visited;
	q.push({start});
	visited.insert(start);

	while (!q.empty()) {
		vector<char> path = q.front();
		q.pop();
		char last = path.back();

		if (last == goal) {
			int totalJarak = 0;
			cout << "\nJALUR TERCEPAT PARUL (BFS):\n";

			for (int i = 0; i < path.size(); i++) {
				cout << namaKota[path[i]] << " (" << path[i] << ")\n";
				if (i < (int)path.size() - 1) {
					for (auto e : graf[path[i]]) {
						if (e.first == path[i + 1])
							cout << e.second << "m\n";
					}
				}
			}

			for (int i = 0; i < (int)path.size() - 1; i++) {
				for (auto e : graf[path[i]]) {
					if (e.first == path[i + 1])
						totalJarak += e.second;
				}
			}

			cout << "\nJalur terpendek: ";
			for (int i = 0; i < path.size(); i++) {
				cout << path[i];
				if (i < path.size() - 1) cout << " -> ";
			}
			cout << "\nTotal langkah: " << path.size() - 1 << " edge";
			cout << "\nTotal jarak: " << totalJarak << " meter\n";
			return;
		}

		for (auto tetangga : graf[last]) {
			if (!visited.count(tetangga.first)) {
				visited.insert(tetangga.first);
				vector<char> baru = path;
				baru.push_back(tetangga.first);
				q.push(baru);
			}
		}
	}
}

int main() {
	graf['A'] = {{'C', 2}, {'B', 5}};
	graf['B'] = {{'A', 5}, {'D', 4}};
	graf['C'] = {{'A', 2}, {'D', 1}};
	graf['D'] = {{'C', 1}, {'E', 3}, {'B', 4}}; // E dulu, baru B
	graf['E'] = {{'D', 3}};

	cout << "PENJELAJAHAN PARUL (DFS dari A):\n";
	set<char> visited;
	DFS('A', visited);
	cout << "\n";

	BFS('A', 'E');
}