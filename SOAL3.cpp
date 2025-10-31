#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Node {
    string judul;
    int tahun;
    int rating; 
    Node* next;
    Node(const string& j, int t, int r) : judul(j), tahun(t), rating(r), next(nullptr) {}
};

class FilmList {
private:
    Node* head;
public:
    FilmList(): head(nullptr) {}
    ~FilmList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void insertFront(const string& j, int t, int r) {
        Node* n = new Node(j,t,r);
        n->next = head;
        head = n;
    }

    void insertBack(const string& j, int t, int r) {
        Node* n = new Node(j,t,r);
        if (!head) head = n;
        else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = n;
        }
    }

    bool insertAfter(const string& target, const string& j, int t, int r) {
        Node* cur = head;
        while (cur && cur->judul != target) cur = cur->next;
        if (!cur) return false;
        Node* n = new Node(j,t,r);
        n->next = cur->next;
        cur->next = n;
        return true;
    }

    bool deleteByTitle(const string& target) {
        if (!head) return false;
        if (head->judul == target) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return true;
        }
        Node* cur = head;
        while (cur->next && cur->next->judul != target) cur = cur->next;
        if (!cur->next) return false;
        Node* toDel = cur->next;
        cur->next = toDel->next;
        delete toDel;
        return true;
    }

    void traverseAndPrint() const {
        Node* cur = head;
        int cnt = 0;
        while (cur) {
            cout << cur->judul << " (" << cur->tahun << ") - " << cur->rating << '\n';
            cur = cur->next;
            ++cnt;
        }
        cout << "\nTotal film tersisa: " << cnt << "\n";
    }
};

int main() {
    cout << "KOLEKSI FILM HARRY\n";
    FilmList list;
    cout << "Masukkan jumlah film awal: ";
    int n;
    while (!(cin >> n) || n < 0) {
        cout << "Input tidak valid. Masukkan angka >= 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; ++i) {
        string judul;
        int tahun, rating;
        cout << "\nFilm " << i + 1 << ":\nJudul: ";
        getline(cin, judul);
        if (judul.empty()) { --i; continue; }

        cout << "Tahun: ";
        while (!(cin >> tahun)) {
            cout << "Masukkan tahun yang valid: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Rating (1-10): ";
        while (!(cin >> rating) || rating < 1 || rating > 10) {
            cout << "Masukkan rating antara 1 sampai 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        list.insertBack(judul, tahun, rating);
    }

    char pilih;
    cout << "\nApakah ingin menghapus film yang sudah ditonton? (y/n): ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (pilih == 'y' || pilih == 'Y') {
        string target;
        cout << "Masukkan judul film yang sudah ditonton: ";
        getline(cin, target);
        if (list.deleteByTitle(target)) {
            cout << "Film \"" << target << "\" berhasil dihapus.\n";
        } else {
            cout << "Film tidak ditemukan: \"" << target << "\"\n";
        }
    }

    cout << "\nDaftar Film:\n";
    list.traverseAndPrint();

    return 0;
}
