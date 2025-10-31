#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct Pasien {
	string nama;
	string jenis;
	int umur;
	int darurat;
	int urutanDatang;
};

class PriorityQueueDynamic {
private:
	vector<Pasien> data;

public:
	void enqueue(const Pasien& p) {
		data.push_back(p);
	}

	bool empty() const {
		return data.empty();
	}

	int index_next() const {
		if (data.empty()) return -1;
		int idx = 0;
		for (int i = 1; i < static_cast<int>(data.size()); ++i) {
			if (data[i].darurat > data[idx].darurat) idx = i;
			else if (data[i].darurat == data[idx].darurat
			         && data[i].urutanDatang < data[idx].urutanDatang)
				idx = i;
		}
		return idx;
	}

	Pasien dequeue_by_priority() {
		int idx = index_next();
		Pasien result = data[idx];
		data.erase(data.begin() + idx);
		return result;
	}
};

int main() {
	cout << "ANTREAN IKLC PAWS & CLAWS\n";
	int n;
	cout << "Masukkan jumlah pasien: ";
	while (!(cin >> n) || n <= 0) {
		cout << "Input tidak valid. Masukkan angka > 0: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	PriorityQueueDynamic pq;
	for (int i = 0; i < n; ++i) {
		Pasien p;
		cout << "\nPasien " << i + 1 << ":\n";
		cout << "Nama hewan: ";
		getline(cin, p.nama);
		if (p.nama.empty()) {
			--i;
			continue;
		}

		cout << "Jenis hewan: ";
		getline(cin, p.jenis);

		cout << "Umur (tahun): ";
		while (!(cin >> p.umur) || p.umur < 0) {
			cout << "Umur tidak valid. Masukkan angka (>=0): ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		cout << "Tingkat darurat (1-5): ";
		while (!(cin >> p.darurat) || p.darurat < 1 || p.darurat > 5) {
			cout << "Masukkan angka antar 1 sampai 5: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		p.urutanDatang = i;
		pq.enqueue(p);
	}

	cout << "DAFTAR PENANGANAN (berdasarkan prioritas)\n";
	int nomor = 1;
	while (!pq.empty()) {
		Pasien next = pq.dequeue_by_priority();
		cout << nomor++ << ". " << next.nama << " (" << next.umur << " tahun)"
		     << " - Darurat " << next.darurat << " - Jenis: " << next.jenis << '\n';
	}

	return 0;
}
