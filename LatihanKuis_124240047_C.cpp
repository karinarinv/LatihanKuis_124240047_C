//Nama : putri karina tumanggor
//NIM : 124240047
//KELAS : PRAKTIKUM Algorima dan struktur data SI - C

//buffer lama 

#include <iostream>
#include <iomanip> //setw, setfill, dkk
#include <algorithm> //sorting kurang ajar
#include <cstring> //strcmp yg lebih kurang ajar
using namespace std;

int jumlahInput;

struct penduduk {
    char nik[20];
    char nama[50];
    char alamat[100];
    char jenis_kelamin[10];
};

penduduk pdk[1000];

void tambahData() {
    FILE *file = fopen("data_penduduk.dat", "ab");
    if (file == NULL) {
        cout << "gagal membuka file" << endl;
        return;
    }

    cout << "Mau menambahkan berapa data? : ";
    cin >> jumlahInput;
    cin.ignore();
    
    for (int i = 0; i < jumlahInput; i++) {
        cout << "Data penduduk ke-" << i + 1 << endl;
        cout << "NIK: ";
        cin.getline(pdk[i].nik, sizeof(pdk[i].nik));
        cout << "Nama: ";
        cin.getline(pdk[i].nama, sizeof(pdk[i].nama));
        cout << "Alamat: ";
        cin.getline(pdk[i].alamat, sizeof(pdk[i].alamat));
        cout << "Jenis Kelamin: ";
        cin.getline(pdk[i].jenis_kelamin, sizeof(pdk[i].jenis_kelamin));
        cout << " " << endl;
        fwrite(&pdk[i], sizeof(penduduk), 1, file);
    }
    
    fclose(file);
    cout << "Data berhasil ditambahkan!" << endl;
}

void tampilkanData() {
    FILE *file = fopen("data_penduduk.dat", "rb");
    if (file == NULL) {
        cout << "buat dulu datanya mr/mrs. user" << endl;
        return;
    }
    int jumlahPenduduk = 0;
    while (fread(&pdk[jumlahPenduduk], sizeof(penduduk), 1, file)) {
        jumlahPenduduk++;
    }
    fclose(file);

    sort(pdk, pdk + jumlahPenduduk, [](const penduduk &a, const penduduk &b) {
        return strcmp(a.nik, b.nik) < 0; //strcmp(a.nik, b.nik) < 0 membandingkan dua string NIK karakter per karakter. (sy gk kuat lagi pls )
    });

    cout << endl << "Daftar Penduduk:" << endl;
    cout << setfill('=') << setw(64) << "" << setfill(' ') << endl;
    cout << setw(15) << left << "NIK" << "|" << setw(15) << "NAMA" << "|" << setw(15) << "ALAMAT" << "|"  << setw(15) << "JENIS KELAMIN" << "|" << endl;
    cout << setfill('=') << setw(64) << "" << setfill(' ') << endl;
    for (int i = 0; i < jumlahPenduduk; i++) {cout << setw(15) << left << pdk[i].nik << "|"  << setw(15) << pdk[i].nama << "|" << setw(15) << pdk[i].alamat << "|" << setw(15) << pdk[i].jenis_kelamin << "|"  << endl;
    cout << setfill('=') << setw(64) << "" << setfill(' ') << endl;
    }
}

void cariData() { //searhing pake sequential search karena lebih singkat, ubur ubur ikan lele, asik bre.
    FILE *file = fopen("data_penduduk.dat", "rb");
    if (file == NULL) {
        cout << "buat dulu datanya ya" << endl;
        return;
    }

    char cari[20];
    cout << "Masukkan NIK yang dicari: "; cin.ignore();
    cin.getline(cari, sizeof(cari));

    penduduk duk; //ternyata ga bisa global, harus local ㅋㅋㅋㅋㅋㅋㅋㅋㅋ 
    bool ditemukan = false;

    while (fread(&duk, sizeof(penduduk), 1, file)) {
        if (strcmp(duk.nik, cari) == 0) {
            cout << "Data ditemukan cuy!" << endl;
            cout << setfill('=') << setw(40) << "" << setfill(' ') << endl;
            cout << "NIK           : " << duk.nik << endl;
            cout << "Nama          : " << duk.nama << endl;
            cout << "Alamat        : " << duk.alamat << endl;
            cout << "Jenis Kelamin : " << duk.jenis_kelamin << endl;
            cout << setfill('=') << setw(40) << "" << setfill(' ') << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Belum terdaftar bes, daftar dulu ya ㅋㅋㅋㅋㅋㅋㅋㅋㅋ" << endl;
    }

    fclose(file);  // one two three close the door 
}

//update of continuing this algorithm task, 00:51 = this close to smash this laptop ㅋㅋㅋㅋㅋㅋㅋㅋㅋ
void editData() {
    FILE *file = fopen("data_penduduk.dat", "rb+"); //ngebuka file mode baca dan tulis secara biner (thank you ppt pak herry)
    if (file == NULL) {
        cout << "buat dulu data kamu" << endl;
        return;
    }

    char edit[20];
    cout << "Masukkan NIK yang akan diedit: "; cin >> edit;
    cin.ignore();

    penduduk pen;
    bool ditemukan = false;

    while (fread(&pen, sizeof(penduduk), 1, file)) {
        if (strcmp(pen.nik, edit) == 0) {

            cout << "Data Ditemukan" << endl;
            cout << "NIK                  : " << pen.nik << endl;
            cout << "Nama                 : " << pen.nama << endl;
            cout << "Alamat               : " << pen.alamat << endl;
            cout << "Jenis Kelamin        : " << pen.jenis_kelamin << endl;

            cout << "Masukkan alamat baru : "; cin.getline(pen.alamat, sizeof(pen.alamat));

            fseek(file, -(long int)sizeof(penduduk), SEEK_CUR); //digunakan biar mundur satu posisi sebesar ukuran struct penduduk
            fwrite(&pen, sizeof(penduduk), 1, file); 
            cout << "cek update-an nya bes";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "datanya mana mas/mba" << endl;
    }

    fclose(file); //fclose(jadwaltidur)
}

void hapusData() {
    FILE *file = fopen("data_penduduk.dat", "rb");
    if (file == NULL) {
        cout << "masukkin dulu datanya ya" << endl;
        return;
    }

    char hapus[20];
    cout << "Masukkan NIK : "; cin.ignore();
    cin.getline(hapus, sizeof(hapus));

    FILE *imut = fopen("imut.dat", "wb"); 
    penduduk ndu;
    bool ditemukan = false;

    while (fread(&ndu, sizeof(penduduk), 1, file)) {
        if (strcmp(ndu.nik, hapus) != 0) {
            fwrite(&ndu, sizeof(penduduk), 1, imut);
        } else {
            ditemukan = true;
        }
    }

    fclose(file);
    fclose(imut);

    remove("data_penduduk.dat");
    rename("imut.dat", "data_penduduk.dat");

    if (ditemukan) {
        cout << "data telah dihapus" << endl;
    } else {
        cout << "get out" << endl;
    }
}

void keluar(){
    exit(0);
}



int main() {
    int pilihan;
    do {
        cout << "MENU KEPENDUDUKAN :" << endl;
        cout << "1. Tambah Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Edit Data\n";
        cout << "5. Hapus Data\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
            tambahData(); 
            break;

            case 2: 
            tampilkanData(); 
            break;

            case 3:
            cariData();
            break;

            case 4:
            editData();
            break;

            case 5:
            hapusData();
            break;

            case 6:
            keluar();
            break;
            default: 
            cout << "menunya hanya 6 loh :(" << endl;
        }
    } while (pilihan != 6);
    return 0;
}