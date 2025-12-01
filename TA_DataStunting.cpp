#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Struktur data anak
struct Anak {
    string nama;
    int umur;
    float berat;
    float tinggi;
    string daerah;
    vector<string> makanan; // daftar makanan seminggu
};

// Fungsi cek gizi
bool cekGizi(const vector<string>& makanan) {
    bool protein = false, vitamin = false, karbo = false, lemak = false;
    for (auto& m : makanan) {
        if (m == "telur" || m == "daging" || m == "ikan") protein = true;
        if (m == "sayur" || m == "buah") vitamin = true;
        if (m == "nasi" || m == "roti") karbo = true;
        if (m == "minyak" || m == "kacang") lemak = true;
    }
    return (protein && vitamin && karbo && lemak);
}

// Fungsi deteksi stunting
bool deteksiStunting(float tinggi, int umur) {
    if (umur <= 5 && tinggi < 100) return true;
    if (umur <= 10 && tinggi < 130) return true;
    if (umur <= 15 && tinggi < 150) return true;
    return false;
}

int main() {
    Anak anak1;

    // Input data sederhana
    cout << "Nama: "; getline(cin, anak1.nama);
    cout << "Umur: "; cin >> anak1.umur;
    cout << "Berat badan (kg): "; cin >> anak1.berat;
    cout << "Tinggi badan (cm): "; cin >> anak1.tinggi;
    cin.ignore();
    cout << "Daerah: "; getline(cin, anak1.daerah);

    int jmlMakanan;
    cout << "Jumlah jenis makanan dikonsumsi seminggu: ";
    cin >> jmlMakanan;
    cin.ignore();
    for (int i = 0; i < jmlMakanan; i++) {
        string makanan;
        cout << "Makanan ke-" << i+1 << ": ";
        getline(cin, makanan);
        anak1.makanan.push_back(makanan);
    }

    // Tampilkan data inputan
    cout << "\n=== Data Anak ===" << endl;
    cout << "Nama: " << anak1.nama << endl;
    cout << "Umur: " << anak1.umur << " tahun" << endl;
    cout << "Berat: " << anak1.berat << " kg" << endl;
    cout << "Tinggi: " << anak1.tinggi << " cm" << endl;
    cout << "Daerah: " << anak1.daerah << endl;

    cout << "Makanan seminggu: ";
    for (auto& m : anak1.makanan) cout << m << ", ";
    cout << endl;

    // Analisis gizi
    bool gizi = cekGizi(anak1.makanan);
    cout << "Status Gizi: " << (gizi ? "TERPENUHI" : "BELUM TERPENUHI") << endl;

    // Analisis stunting
    bool stunting = deteksiStunting(anak1.tinggi, anak1.umur);
    cout << "Status Stunting: " << (stunting ? "STUNTING" : "Sehat") << endl;

    return 0;
}