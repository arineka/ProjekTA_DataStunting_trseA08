#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CHILD = 30;
const int DAYS = 7;
const int MAX_FOOD = 10; // maksimal makanan per hari
const int FOOD_SLOTS = DAYS * MAX_FOOD; // supaya makanan per anak bisa disimpan dalam 2D

// Fungsi sederhana: ubah string ke huruf kecil
string toLowerSimple(string s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            s[i] = c + ('a' - 'A');
        }
    }
    return s;
}

// Fungsi sederhana: cek apakah key ada di s (manual substring), case-insensitive
bool containsKeyword(string s, string key) {
    s = toLowerSimple(s);
    key = toLowerSimple(key);
    int ls = s.length();
    int lk = key.length();
    if (lk == 0 || ls < lk) return false;
    for (int i = 0; i <= ls - lk; i++) {
        bool match = true;
        for (int j = 0; j < lk; j++) {
            if (s[i + j] != key[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

// Cek gizi sederhana dari makanan anak ke idx
// mengisi flags lewat reference
void cekGiziSimple(int idx,
                   string makanan[][FOOD_SLOTS],
                   int makananCount[][DAYS],
                   bool &hasProtein, bool &hasVitamin, bool &hasKarbo, bool &hasLemak) {
    hasProtein = false;
    hasVitamin = false;
    hasKarbo = false;
    hasLemak = false;

    for (int h = 0; h < DAYS; h++) {
        int jm = makananCount[idx][h];
        for (int f = 0; f < jm; f++) {
            // posisi di array 2D: day * MAX_FOOD + f
            string food = makanan[idx][h * MAX_FOOD + f];
            if (containsKeyword(food, "telur") || containsKeyword(food, "ikan") ||
                containsKeyword(food, "daging") || containsKeyword(food, "tempe") ||
                containsKeyword(food, "tahu")) {
                hasProtein = true;
            }
            if (containsKeyword(food, "sayur") || containsKeyword(food, "buah") ||
                containsKeyword(food, "wortel") || containsKeyword(food, "bayam") ||
                containsKeyword(food, "pisang")) {
                hasVitamin = true;
            }
            if (containsKeyword(food, "nasi") || containsKeyword(food, "roti") ||
                containsKeyword(food, "ubi") || containsKeyword(food, "kentang")) {
                hasKarbo = true;
            }
            if (containsKeyword(food, "minyak") || containsKeyword(food, "kacang") ||
                containsKeyword(food, "alpukat") || containsKeyword(food, "mentega")) {
                hasLemak = true;
            }
        }
    }
}

// Deteksi stunting sederhana
bool deteksiStunting(float tinggi, int umur) {
    if (umur <= 5 && tinggi < 100.0f) return true;
    if (umur <= 10 && tinggi < 130.0f) return true;
    if (umur <= 15 && tinggi < 150.0f) return true;
    return false;
}

// Buat string rekomendasi sederhana berdasarkan flags kekurangan
string buatRekomendasi(bool hasProtein, bool hasVitamin, bool hasKarbo, bool hasLemak) {
    string out = "";
    if (!hasProtein) {
        if (out != "") out += "; ";
        out += "Tambah Protein (telur/ikan/daging/tempe)";
    }
    if (!hasVitamin) {
        if (out != "") out += "; ";
        out += "Tambah Sayur/Buah";
    }
    if (!hasKarbo) {
        if (out != "") out += "; ";
        out += "Tambah Karbo (nasi/roti/ubi)";
    }
    if (!hasLemak) {
        if (out != "") out += "; ";
        out += "Tambah Lemak sehat (kacang/avokad)";
    }
    if (out == "") out = "-";
    return out;
}

int main() {
    string bulan;
    int minggu;
    cout << "Masukkan bulan pemantauan: ";
    getline(cin, bulan);

    cout << "Masukkan minggu ke-: ";
    while (!(cin >> minggu)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan angka untuk minggu: ";
    }
    cin.ignore(); // buang newline

    int n;
    cout << "Berapa anak yang akan diinput (max " << MAX_CHILD << ")? ";
    while (!(cin >> n) || n < 1 || n > MAX_CHILD) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan angka antara 1 dan " << MAX_CHILD << ": ";
    }
    cin.ignore();

    // Data anak: semua array 1D / 2D
    string nama[MAX_CHILD];
    int umur[MAX_CHILD];
    float berat[MAX_CHILD];
    float tinggi[MAX_CHILD];
    string daerah[MAX_CHILD];
    string keseharian[MAX_CHILD];

    // makanan disimpan di array 2D: child x FOOD_SLOTS (day*MAX_FOOD + index)
    string makanan[MAX_CHILD][FOOD_SLOTS];
    int makananCount[MAX_CHILD][DAYS];

    // inisialisasi makananCount = 0
    for (int i = 0; i < n; i++) {
        for (int d = 0; d < DAYS; d++) {
            makananCount[i][d] = 0;
        }
        // kosongkan semua slot makanan (bisa beri string kosong)
        for (int s = 0; s < FOOD_SLOTS; s++) {
            makanan[i][s] = "";
        }
    }

    // Input data anak
    for (int i = 0; i < n; i++) {
        cout << "\n=== Data Anak ke-" << (i + 1) << " ===\n";
        cout << "Nama: ";
        getline(cin, nama[i]);

        cout << "Umur (tahun): ";
        while (!(cin >> umur[i])) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan umur (angka): ";
        }
        cout << "Berat badan (kg): ";
        while (!(cin >> berat[i])) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan berat (angka): ";
        }
        cout << "Tinggi badan (cm): ";
        while (!(cin >> tinggi[i])) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan tinggi (angka): ";
        }
        cin.ignore();
        cout << "Daerah: ";
        getline(cin, daerah[i]);

        // input makanan 7 hari
        for (int h = 0; h < DAYS; h++) {
            cout << "Hari ke-" << (h + 1) << " - jumlah makanan (0.." << MAX_FOOD << "): ";
            int jm;
            while (!(cin >> jm) || jm < 0 || jm > MAX_FOOD) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Masukkan angka 0.." << MAX_FOOD << ": ";
            }
            makananCount[i][h] = jm;
            cin.ignore();
            for (int f = 0; f < jm; f++) {
                cout << "  Makanan ke-" << (f + 1) << ": ";
                string food;
                getline(cin, food);
                makanan[i][h * MAX_FOOD + f] = food;
            }
        }

        cout << "Keseharian singkat: ";
        getline(cin, keseharian[i]);
    }

    // Statistik dan hasil disimpan di array
    int deficiencyTotal[4] = {0, 0, 0, 0};       // Protein, Vitamin, Karbo, Lemak
    int deficiencyInStunted[4] = {0, 0, 0, 0};
    int totalStunting = 0;

    bool hasProteinArr[MAX_CHILD];
    bool hasVitaminArr[MAX_CHILD];
    bool hasKarboArr[MAX_CHILD];
    bool hasLemakArr[MAX_CHILD];
    bool isStuntingArr[MAX_CHILD];
    string rekomArr[MAX_CHILD];

    // Analisis tiap anak
    for (int i = 0; i < n; i++) {
        bool hasProtein, hasVitamin, hasKarbo, hasLemak;
        cekGiziSimple(i, makanan, makananCount, hasProtein, hasVitamin, hasKarbo, hasLemak);

        hasProteinArr[i] = hasProtein;
        hasVitaminArr[i] = hasVitamin;
        hasKarboArr[i] = hasKarbo;
        hasLemakArr[i] = hasLemak;

        bool st = deteksiStunting(tinggi[i], umur[i]);
        isStuntingArr[i] = st;
        if (st) totalStunting++;

        if (!hasProtein) deficiencyTotal[0]++;
        if (!hasVitamin) deficiencyTotal[1]++;
        if (!hasKarbo) deficiencyTotal[2]++;
        if (!hasLemak) deficiencyTotal[3]++;

        if (st) {
            if (!hasProtein) deficiencyInStunted[0]++;
            if (!hasVitamin) deficiencyInStunted[1]++;
            if (!hasKarbo) deficiencyInStunted[2]++;
            if (!hasLemak) deficiencyInStunted[3]++;
        }

        rekomArr[i] = buatRekomendasi(hasProtein, hasVitamin, hasKarbo, hasLemak);
    }

    // CETAK MUTASI (sekali di akhir)
    cout << "\n\n================= LAPORAN MUTASI ==================\n";
    cout << "Bulan: " << bulan << "    Minggu ke-" << minggu << "\n";
    cout << "Total anak: " << n << "    Kasus stunting: " << totalStunting << "\n";
    cout << "--------------------------------------------------\n";

    cout << left << setw(18) << "Nama"
         << setw(6) << "Umur"
         << setw(8) << "Berat"
         << setw(8) << "Tinggi"
         << setw(12) << "Daerah"
         << setw(12) << "Gizi"
         << setw(10) << "Stunt"
         << setw(30) << "Kekurangan"
         << setw(30) << "Rekomendasi"
         << "\n";
    cout << string(140, '-') << "\n";

    for (int i = 0; i < n; i++) {
        string kek = "";
        if (!hasProteinArr[i]) kek += "Protein";
        if (!hasVitaminArr[i]) { if (kek != "") kek += ", "; kek += "Vitamin"; }
        if (!hasKarboArr[i]) { if (kek != "") kek += ", "; kek += "Karbohidrat"; }
        if (!hasLemakArr[i]) { if (kek != "") kek += ", "; kek += "Lemak"; }
        if (kek == "") kek = "-";

        string statusGizi = (kek == "-") ? "TERPENUHI" : "BELUM";

        cout << left << setw(18) << nama[i]
             << setw(6)  << umur[i]
             << setw(8)  << berat[i]
             << setw(8)  << tinggi[i]
             << setw(12) << daerah[i]
             << setw(12) << statusGizi
             << setw(10) << (isStuntingArr[i] ? "STUNTING" : "Sehat")
             << setw(30) << kek
             << setw(30) << rekomArr[i]
             << "\n";
    }

    cout << string(140, '=') << "\n\n";

    // Ringkasan frekuensi kekurangan
    cout << "RINGKASAN KEKURANGAN (Total / Pada Stunting)\n";
    cout << left << setw(16) << "Kekurangan" << setw(12) << "Total" << setw(18) << "Dalam Stunting" << "\n";
    cout << string(50, '-') << "\n";
    string labels[4] = {"Protein", "Vitamin", "Karbohidrat", "Lemak"};
    for (int k = 0; k < 4; k++) {
        cout << left << setw(16) << labels[k]
             << setw(12) << deficiencyTotal[k]
             << setw(18) << deficiencyInStunted[k]
             << "\n";
    }
    cout << string(50, '=') << "\n";

    cout << "Untuk analisis medis gunakan standar WHO (z-score) dan pemeriksaan profesional.\n";

    return 0;
}