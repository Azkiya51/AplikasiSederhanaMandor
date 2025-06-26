#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

// Tambahkan Rekomendasi

const int MAX = 100;

struct Proyek {
    string nama;
    float luas;
    int biaya;
};

Proyek daftar[MAX];
int jumlahProyek = 0;

float inputPositif(const string& label) {
    float x;
    cout << "Masukkan " << label << ": ";
    while (!(cin >> x) || x <= 0) {
        cout << "Input tidak valid. " << label << " harus lebih dari 0!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan " << label << ": ";
    }
    return x;
}

void tambahProyek() {
    if (jumlahProyek >= MAX) {
        cout << "Batas proyek telah tercapai.\n";
        return;
    }

    cin.ignore();
    cout << "Nama Proyek: ";
    getline(cin, daftar[jumlahProyek].nama);

    if (daftar[jumlahProyek].nama.empty()) {
        cout << "Nama proyek tidak boleh kosong!\n";
        return;
    }

    float panjang = inputPositif("panjang rumah (m)");
    float lebar = inputPositif("lebar rumah (m)");

    daftar[jumlahProyek].luas = panjang * lebar;
    daftar[jumlahProyek].biaya = static_cast<int>(daftar[jumlahProyek].luas * 1000000);

    cout << "Perkiraan Biaya: Rp" << daftar[jumlahProyek].biaya << endl;
    jumlahProyek++;
}
//Progres ke 2
void tampilProyek() {
    if (jumlahProyek == 0) {
        cout << "Belum ada data proyek.\n";
        return;
    }

    cout << "\n=== Daftar Proyek ===\n";
    for (int i = 0; i < jumlahProyek; i++) {
        cout << i + 1 << ". " << daftar[i].nama
             << " | Luas: " << daftar[i].luas
             << " m2 | Biaya: Rp" << daftar[i].biaya << endl;
    }
}

// Progres 3
void urutkanProyek() {
    for (int i = 0; i < jumlahProyek - 1; i++) {
        for (int j = 0; j < jumlahProyek - i - 1; j++) {
            if (daftar[j].biaya < daftar[j + 1].biaya) {
                swap(daftar[j], daftar[j + 1]);
            }
        }
    }
    cout << "Proyek diurutkan berdasarkan Dana terbesar.\n";
}

void cariProyek(const string& namaCari) {
    bool ketemu = false;
    for (int i = 0; i < jumlahProyek; i++) {
        if (daftar[i].nama == namaCari) {
            cout << "Proyek ditemukan: " << daftar[i].nama
                 << ", Luas: " << daftar[i].luas
                 << " m2, Biaya: Rp" << daftar[i].biaya << endl;
            ketemu = true;
            break;  
        }
    }
    if (!ketemu)
        cout << "Proyek tidak ditemukan.\n";
}

void simpanFile() {
    ofstream file("Data_Proyek.txt");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan.\n";
        return;
    }

    for (int i = 0; i < jumlahProyek; i++) {
        file << daftar[i].nama << "," << daftar[i].luas << "," << daftar[i].biaya << endl;
    }

    file.close();
    cout << "Data proyek disimpan ke 'Data_Proyek.txt'\n";
}

void tampilkanMatriksMaterial() {
    if (jumlahProyek == 0) {
        cout << "Belum ada proyek untuk dihitung materialnya.\n";
        return;
    }

    const char* material[3] = {"Semen (zak)", "Pasir (m3)", "Batu Bata (buah)"};
    float kebutuhanPerM2[3] = {10, 0.5f, 1000};

    cout << "\n=== Kebutuhan Material untuk Tiap Proyek ===\n";
    for (int i = 0; i < jumlahProyek; i++) {
        cout << i + 1 << ". " << daftar[i].nama << " (Luas: " << daftar[i].luas << " m2)\n";
        for (int j = 0; j < 3; j++) {
            float total = kebutuhanPerM2[j] * daftar[i].luas;
            cout << fixed << setprecision(2); 
            cout << "   - " << material[j] << ": " << total << endl;
        }
    }
}


//Progres Terakhir
void menu() {
    int pilihan;
    do {
        cout << "\n=== Menu Bangun Rumah ===\n";
        cout << "1. Tambah Proyek\n";
        cout << "2. Tampilkan Semua Proyek\n";
        cout << "3. Urutkan Proyek Berdasarkan Biaya\n";
        cout << "4. Cari Proyek Berdasarkan Nama\n";
        cout << "5. Simpan ke File\n";
        cout << "6. Tampilkan Matriks Material\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";

        cin >> pilihan;

        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Harap masukkan angka antara 0-6.\n";
            continue;
        }

       
        if (pilihan < 0 || pilihan > 6) {
            cout << "Pilihan tidak valid! Harap masukkan angka antara 0-6.\n";
            continue;
        }

        
        switch (pilihan) {
            case 1:
                tambahProyek();
                break;
            case 2:
                tampilProyek();
                break;
            case 3:
                urutkanProyek();
                break;
            case 4: {
                cin.ignore();
                string namaCari;
                cout << "Masukkan nama proyek yang dicari: ";
                getline(cin, namaCari);

                if (namaCari.empty()) {
                    cout << "Nama proyek tidak boleh kosong!\n";
                    break; 
                }

                cariProyek(namaCari);
                break;
}

            case 5:
                simpanFile();
                break;
            case 6:
                tampilkanMatriksMaterial();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
        }
    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}