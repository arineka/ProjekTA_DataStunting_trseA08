#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip> // untuk setw
using namespace std;

// Struktur data anak
struct Anak {
    string nama;
    int umur;
    float berat;
    float tinggi;
    string daerah;
    vector<string> makanan;
    string keseharian;
};

// Fungsi untuk cek gizi
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

// Fungsi deteksi stunting (sederhana: tinggi < standar)
bool deteksiStunting(float tinggi, int umur) {
    if (umur <= 5 && tinggi < 100) return true;
    if (umur <= 10 && tinggi < 130) return true;
    if (umur <= 15 && tinggi < 150) return true;
    return false;
}

// Fungsi rekomendasi makanan
vector<string> rekomendasiMakanan() {
    return {"telur", "ikan", "sayur hijau", "buah segar", "kacang", "susu"};
}

// Fungsi untuk tanggal pendampingan
string tanggalPendampingan() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int hari = ltm->tm_mday + 7; // pendampingan seminggu ke depan
    int bulan = 1 + ltm->tm_mon;
    int tahun = 1900 + ltm->tm_year;
    return to_string(hari) + "-" + to_string(bulan) + "-" + to_string(tahun);
}

int main() {
    int n;
    cout << "Masukkan jumlah anak yang ingin dipantau: ";
    cin >> n;
    cin.ignore();

    vector<Anak> dataAnak(n);

    // Input data
    for (int i = 0; i < n; i++) {
        cout << "\nData Anak ke-" << i+1 << endl;
        cout << "Nama: "; getline(cin, dataAnak[i].nama);
        cout << "Umur: "; cin >> dataAnak[i].umur;
        cout << "Berat badan (kg): "; cin >> dataAnak[i].berat;
        cout << "Tinggi badan (cm): "; cin >> dataAnak[i].tinggi;
        cin.ignore();
        cout << "Daerah: "; getline(cin, dataAnak[i].daerah);

        int jmlMakanan;
        cout << "Jumlah jenis makanan dikonsumsi seminggu: ";
        cin >> jmlMakanan;
        cin.ignore();
        for (int j = 0; j < jmlMakanan; j++) {
            string makanan;
            cout << "Makanan ke-" << j+1 << ": ";
            getline(cin, makanan);
            dataAnak[i].makanan.push_back(makanan);
        }

        cout << "Keseharian anak: ";
        getline(cin, dataAnak[i].keseharian);
    }

    // Header tabel
    cout << "\n====================================================================================================================\n";
    cout << setw(15) << left << "Nama"
         << setw(6)  << "Umur"
         << setw(8)  << "Berat"
         << setw(8)  << "Tinggi"
         << setw(15) << "Daerah"
         << setw(25) << "Status Gizi"
         << setw(25) << "Status Stunting"
         << setw(25) << "Pendampingan/Rekomendasi"
         << endl;
    cout << "====================================================================================================================\n";

    // Analisis per anak
    for (int i = 0; i < n; i++) {
        bool gizi = cekGizi(dataAnak[i].makanan);
        bool stunting = deteksiStunting(dataAnak[i].tinggi, dataAnak[i].umur);

        string statusGizi = gizi ? "TERPENUHI" : "BELUM TERPENUHI";
        string statusStunting, pendampingan;

        if (stunting) {
            statusStunting = "STUNTING";
            pendampingan = "Pendampingan: " + tanggalPendampingan();
        } else {
            statusStunting = "Sehat";
            pendampingan = "Keseharian diteruskan";
        }

        cout << setw(15) << left << dataAnak[i].nama
             << setw(6)  << dataAnak[i].umur
             << setw(8)  << dataAnak[i].berat
             << setw(8)  << dataAnak[i].tinggi
             << setw(15) << dataAnak[i].daerah
             << setw(25) << statusGizi
             << setw(25) << statusStunting
             << setw(25) << pendampingan
             << endl;
    }

    cout << "====================================================================================================================\n";

    return 0;
}