#include <iostream>
#include <string>
using namespace std;

struct Anak {
    string nama;
    int umur;
    float berat;
    float tinggi;
    string daerah;
};

int main() {
    Anak data;
    cout << "Masukkan nama anak: ";
    getline(cin, data.nama);
    cout << "Umur: ";
    cin >> data.umur;
    cout << "Berat badan (kg): ";
    cin >> data.berat;
    cout << "Tinggi badan (cm): ";
    cin >> data.tinggi;
    cin.ignore();
    cout << "Daerah: ";
    getline(cin, data.daerah);

    cout << "\n=== Data Anak ===" << endl;
    cout << "Nama: " << data.nama << endl;
    cout << "Umur: " << data.umur << " tahun" << endl;
    cout << "Berat: " << data.berat << " kg" << endl;
    cout << "Tinggi: " << data.tinggi << " cm" << endl;
    cout << "Daerah: " << data.daerah << endl;

    return 0;
}