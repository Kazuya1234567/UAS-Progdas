#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Barang {
    int id;
    char nama[100];
    double harga;
    int stok;
};

Barang daftarBarang[1000];
int jumlahBarang = 0;
Barang BarangBaru;


void TambahBarang(){
    cout << "Tambahkan Barang Baru" << endl;
    cout << "ID Barang: ";
    cin >> BarangBaru.id;

    for (int i=0; i<jumlahBarang; i++){
        if (daftarBarang[i].id == BarangBaru.id) {
            cout << "Error: ID" << BarangBaru.id << "Sudah Ada!" << endl;
            return;
        }
    }

    cout << "Nama Barang: ";
    cin.ignore( );
    cin.getline(BarangBaru.nama, 100);

    cout << "Harga: ";
    cin >> BarangBaru.harga;

    cout << "Stok: ";
    cin >> BarangBaru.stok;

    daftarBarang[jumlahBarang]=BarangBaru;
    jumlahBarang++;
    cout << "Barang berhasil di tambahakan!" << endl;
}

void SimpanData(){
    ofstream file("data_barang.txt");

    file << jumlahBarang << endl;

    for (int i=0; i<jumlahBarang; i++){
        file << daftarBarang[i].id << endl;
        file << daftarBarang[i].nama << endl;
        file << daftarBarang[i].harga << endl;
        file << daftarBarang[i].stok << endl;
    }

    file.close();
}

void BacaData(){
    ifstream file ("data_barang.txt");

    file >> jumlahBarang;
    file.ignore();

    for (int i=0; i<jumlahBarang; i++){
        file >> daftarBarang[i].id;
        file.ignore();

        file.getline(daftarBarang[i].nama, 100);

        file >> daftarBarang[i].harga;
        file.ignore();

        file >> daftarBarang[i].stok;
        file.ignore(); 
    }
    file.close();
}

void cariBarang() {
    if (jumlahBarang == 0) {
        cout << "Database kosong!" << endl;
        return;
    }
    
    char kataKunci[50];
    cout << "--- CARI BARANG ---" << endl;
    cout << "Masukkan nama barang: ";
    cin.ignore();
    cin.getline(kataKunci, 50);
    
    if (strlen(kataKunci) == 0) {
        cout << "Error: Kata kunci tidak boleh kosong!" << endl;
        return;
    }
    
    bool ditemukan = false;
    
    cout << "--- HASIL PENCARIAN ---" << endl;
    
    for (int i = 0; i < jumlahBarang; i++) {
        if (strstr(daftarBarang[i].nama, kataKunci) != NULL) {
            cout << "ID: " << daftarBarang[i].id 
                 << " | Nama: " << daftarBarang[i].nama 
                 << " | Harga: Rp " << daftarBarang[i].harga 
                 << " | Stok: " << daftarBarang[i].stok << endl;
            ditemukan = true;
        }
    }
    
    if (!ditemukan) {
        cout << "Tidak ditemukan barang dengan nama '" << kataKunci << "'" << endl;
    }
}

void hapusBarang() {
    if (jumlahBarang == 0) {
        cout << "Database kosong!" << endl;
        return;
    }
    
    int idHapus;
    cout << "--- HAPUS BARANG ---" << endl;
    cout << "Masukkan ID barang yang akan dihapus: ";
    cin >> idHapus;
    
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == idHapus) {
            cout << "Barang ditemukan: " << daftarBarang[i].nama 
                 << " (Harga: " << daftarBarang[i].harga << ")" << endl;
            
            char konfirmasi;
            cout << "Yakin ingin menghapus? (y/n): ";
            cin >> konfirmasi;
            
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                for (int j = i; j < jumlahBarang - 1; j++) {
                    daftarBarang[j] = daftarBarang[j + 1];
                }
                
                jumlahBarang--;
                cout << "Barang berhasil dihapus!" << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
            return;
        }
    }
    cout << "Error: Barang dengan ID " << idHapus << " tidak ditemukan!" << endl;
}

void TampilkanSemuaBarang(){
    if (jumlahBarang == 0){
        cout << "Daftar harga kosong!" << endl;
        return;
    }

    cout << "=== Daftar Harga Barang ===" << endl;
    for (int i=0; i<jumlahBarang; i++){
        cout << "ID: " << daftarBarang[i].id
         << " |Nama: " << daftarBarang[i].nama
         << " | Harga: Rp " << daftarBarang[i].harga
         << " | Stok: " << daftarBarang[i].stok << endl;
    }
}

int main() {
    int pilihan;
    BacaData();

    do {
        cout << "===DAFTAR HARGA BARANG===" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Cari Barang" << endl;
        cout << "3. Hapus Barang" << endl;
        cout << "4. Tampilkan Semua Barang" << endl;
        cout << "5. Keluar" << endl;
        cout << " Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1){TambahBarang();} 
        else if (pilihan == 2){cariBarang();}
        else if (pilihan == 3){hapusBarang();}
        else if (pilihan == 4){TampilkanSemuaBarang();}
        else if (pilihan == 5){
            SimpanData(); 
            cout << "Keluar" << endl;}
        else {cout << "Pilihan Tidak Valid" << endl;}

    } while (pilihan !=5);
    
    return 0;
}