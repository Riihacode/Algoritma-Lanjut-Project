//##################  KELOMPOK & DETAIL TUGAS  #######################
/*
Anggota = Ribhan Aulia Zulmi (NIM 123210038) -> kelompok 1 orang anggota
Tema    = Directory Management
Kelas   = Algoritma dan Pemrograman Lanjut IF-F
Kode Kelas = 20242
*/
//###################=  KELOMPOK & TEMA  #############################


//#######################  <CATATAN>  #################################
/*
1) Sumber referensi paling banyak menggunakan modul praktikum yang ketika
    diimplementasikan sedikit dimodifikasi (terutama untuk algoritma
    searching & algoritma sorting).

2) Detail Implementasi pada program ini dapat dilihat di line source code yang
   diberikan comment `FUNCTION RE-DECLARATION`

3) Rencana Lanjutan = 
    a) Revisi perbaikan source code:
       - Tidak ada
    
    b) Rencana pengembangan ekstensi (optional):
       - Membuat aplikasi Android (Framework NDK + JNI) berdasarkan konsep 
         manajemen direktori ini. Alasannya karena Android Studio IDE 
         mendukung penggunaan C++ juga.
       - Tujuannya untuk eksperimen native C++ tanpa mengakses storage 
         Android secara langsung.
       - Namun, fokus utama tetap pada penyelesaian project C++ sebagai prioritas.

    c) Source code pengembangan (jika diteruskan):
       - Link Github: https://github.com/Riihacode/Algoritma-Lanjut-Project.git     (Ada kendala akun diminta untuk request 2FA, mungkin link ini salah kecuali kalau ada commit changes)

4) Link Dokumentasi Projek Akhir
    https://drive.google.com/drive/folders/1sNteqa0RSvFEk3D-eNVDQX9JlSjGpDCS?usp=sharing

*/
//######################  </CATATAN>  ##################################



//#######################  IMPORT LIBRARY  ###########################
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdio>       // untuk menghapus file fisik
#include <iomanip>
#include <ctime>    

using namespace std;

//#######################  STRUCT  ###################################
struct Metadata {
    char createdAt[20];
    char modifiedAt[20];
    char accessedAt[20];
};

struct MyFile {
    char name[100];
    char extension[10];
    unsigned long long size;
    unsigned long long sizeOnDisk;
    Metadata meta;
};

struct Folder {
    char name[100];         // Menyimpan nama folder
    MyFile files[10];       // Array statis untuk menyimpan maksimal 10 file dalam folder ini
    int fileCount;          // Menyimpan jumlah file yang sedang aktif digunakan dalam array `files[]`.
    Folder *subfolders[10]; // Array pointer ke Folder lainnya → menciptakan struktur folder bertingkat (nested folder).
    int subfolderCount;     // Jumlah subfolder yang sedang digunakan pada array `subfolders[]`
    Metadata meta;
};

//#######################  VARIABLE GLOBAL  ##########################
Folder *rootFolders[10];    // kumpulan nama folder pada tingkat root
int rootFolderCount = 0;    // Menentukan berapa banyak folder root yang sedang aktif (jumlah yang terisi dalam rootFolders[]).

// Navigasi Folder
Folder *currentFolder = nullptr; // Menunjukkan posisi saat ini di dalam hirarki folder
Folder *parentStack[20];         // Menyimpan jejak folder sebelumnya untuk fitur “kembali”
int parentTop = -1;              // Menunjukkan indeks atas stack navigasi

// NOTE: fileSizeMap digunakan untuk keperluan requirement array 2D
unsigned long long fileSizeMap[10][10]; // array 2D mirror ukuran file

//####################  FUNCTION RE-DECLARATION  #####################
// Manipulasi Folder
void initializeSampleData();
void displayCurrentPath();
void displayRootFolders();
void displayCurrentFolderContents(Folder *folder, int depth); // Rekursif utama
void addSubfolderToCurrent();
void navigateIntoSubfolder();
void navigateBack();
void deleteSubfolderFromCurrent();

// Algoritma Searching
void menuSearching();
void seqNonSentinelBelumUrut();
void seqNonSentinelSudahUrut();
void seqSentinelBelumUrut();
void seqSentinelSudahUrut();
void binarySearchSudahUrut();

void seqNonSentinelBelumUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path);
void seqNonSentinelSudahUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path);
void seqSentinelBelumUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path);
void seqSentinelSudahUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path);
void binarySearchInFolder(Folder *folder, const string &target, bool &foundOverall, string path);

// Algoritma Sorting
void menuSorting();
void sortFilesInCurrentFolderWithBubbleSort();
void sortFilesInCurrentFolderWithInsertionSort();
void sortFilesInCurrentFolderWithSelectionSort();
void sortFilesInCurrentFolderWithShellSort();
void sortQuickSortFiles(MyFile files[], int first, int last);
void sortFilesInCurrentFolderWithQuickSort();

// File Operation
void menuFileOperation();
void createFileInCurrentFolder();
void readFileFromCurrentFolder();
void updateFileInCurrentFolder();
void deleteFileFromCurrent();
unsigned long long getFileSizeWithFstream(const string &filename);

// Metadata
void getCurrentTimestamp(char waktu[]);
void showFileMetadata();
string getCurrentPathString();
string getFileFullPath(const MyFile &file);

// Array 2 Dimensi dengan rekursif
unsigned long long getTotalSizeOfFolderRecursive(Folder *folder) ;
void updateFileSizeMapForAllRootFolders();
void showTotalSizeFromFileSizeMap();

//#######################  FUNGSI UTAMA  ############################
int main() {
    initializeSampleData();
    currentFolder = nullptr;    // default ke root

    int choice;

    do {
        cout << "\n=== Lokasi Saat Ini: ";
        displayCurrentPath();
        cout << "\n====== Menu Folder & File ======" << endl;
        cout << "1. Tampilkan Folder & File Saat Ini\n";
        cout << "2. Masuk ke Subfolder\n";
        cout << "3. Kembali ke Folder Sebelumnya\n";
        cout << "4. Tambah Subfolder\n";
        cout << "5. Hapus Subfolder \n";
        cout << "6. Searching \n";
        cout << "7. Sorting \n";
        cout << "8. File Operation \n";
        cout << "9. Tampilkan Metadata File \n";
        cout << "10. Lihat Total Size Folder Root (termasuk nested) \n";
        cout << "11. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();
        cout << endl;

        switch (choice) {
            case 1: 
                if (currentFolder == nullptr) {
                    displayRootFolders(); 
                } else { 
                    displayCurrentFolderContents(currentFolder, 0); 
                }
                
                break;
            case 2: navigateIntoSubfolder(); break;
            case 3: navigateBack(); break;
            case 4: addSubfolderToCurrent(); break;
            case 5: deleteSubfolderFromCurrent(); break;
            case 6: menuSearching(); break;
            case 7: menuSorting(); break;
            case 8: menuFileOperation(); break;
            case 9: showFileMetadata(); break;
            case 10: showTotalSizeFromFileSizeMap(); break;
            case 11: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 11);

    return 0;
}

//#####################  BUSSINESS LOGIC CORE  ############################
// Menampilkan menu pilihan algoritma searching dan memanggil fungsi sesuai input user
void menuSearching() {
    cout << "\n=== Pilih Algoritma Searching ===" << endl;
    cout << "1. Sequential Non Sentinel (Belum Urut)\n";
    cout << "2. Sequential Non Sentinel (Sudah Urut)\n";
    cout << "3. Sequential dengan Sentinel (Belum Urut)\n";
    cout << "4. Sequential dengan Sentinel (Sudah Urut)\n";
    cout << "5. Binary Search (Sudah Urut)\n";
    cout << "Pilihan: ";
    int pilih;
    cin >> pilih;
    cin.ignore();
    cout << endl;

    switch (pilih) {
        case 1: seqNonSentinelBelumUrut(); break;
        case 2: seqNonSentinelSudahUrut(); break;
        case 3: seqSentinelBelumUrut(); break;
        case 4: seqSentinelSudahUrut(); break;
        case 5: binarySearchSudahUrut(); break;
        default: cout << "Pilihan tidak valid!\n";
    }
}

// Menu Sorting
void menuSorting() {
    cout << "\n=== Pilih Algoritma Sorting ===" << endl;
    cout << "1. Bubble Sort\n";
    cout << "2. Insertion Sort\n";
    cout << "3. Selection Sort\n";
    cout << "4. Shell Sort\n";
    cout << "5. Quick Sort\n";
    cout << "Pilihan: ";
    int pilih;
    cin >> pilih;
    cin.ignore();
    cout << endl;

    switch (pilih) {
        case 1: sortFilesInCurrentFolderWithBubbleSort(); break;
        case 2: sortFilesInCurrentFolderWithInsertionSort(); break;
        case 3: sortFilesInCurrentFolderWithSelectionSort(); break;
        case 4: sortFilesInCurrentFolderWithShellSort(); break;
        case 5: sortFilesInCurrentFolderWithQuickSort(); break;
        default: cout << "Pilihan tidak valid!\n";
    }
}

// menu File Operation
void menuFileOperation() {
    if (currentFolder == nullptr) {
        cout << "Silakan masuk ke folder terlebih dahulu.\n";
        return;
    }

    int choice;
    do {
        cout << "\n=== FILE OPERATION MENU ===\n";
        cout << "1. Buat file baru (Create)\n";
        cout << "2. Baca isi file (Read)\n";
        cout << "3. Perbarui file (Update)\n";
        cout << "4. Hapus file (Delete)\n";
        cout << "5. Kembali\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: createFileInCurrentFolder(); break;
            case 2: readFileFromCurrentFolder(); break;
            case 3: updateFileInCurrentFolder(); break;
            case 4: deleteFileFromCurrent(); break;
            case 5: return;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 5);
}

// Fungsi untuk mengisi data awal ke dalam sistem folder dan file secara otomatis.
// Data ini digunakan untuk simulasi program tanpa input manual satu per satu.
void initializeSampleData() {
    rootFolderCount = 3;
    const int fileCounts[] = {6, 9, 8}; // Jumlah folder utama (root)

    // Daftar nama folder
    const char* folderNames[] = {"folder 1", "folder 2", "folder 3"};
    
    // Array 2D nama file sesuai masing-masing folder
    const char* fileNames[][10] = {
        {"file 1", "nyoba cpp lewat notepad", "zoo", "testing file", "A", "backup_cmd_kali_linux" },
        {"pertemuan1_prak_algoritma", "index_web_notepad", "Rekomendasi Film 2023", "file random folder 2", "C", "A", "rekomendasi film 2025", "file-1-di-folder-2", "B"},
        {"sha256_tutorial_encryption_youtube", "d", "C", "computer quantum & machine learning", "langkah-langkah instalasi vs code", "hunting_", "E", "list wifi kampus"}
    };

    // Ukuran file dummy untuk tiap file
    const int fileSizes[][10] = {
        {10, 20, 100, 23, 50, 50},
        {15, 25, 55, 15, 25, 32, 35, 15, 5},
        {12, 55, 55, 12, 12, 12, 55, 12}
    };

    const char *extension = "txt";  // Semua file berekstensi txt

    for (int i = 0; i < rootFolderCount; i++) {
        rootFolders[i] = new Folder;    //Alokasi dinamis objek Folder menggunakan new, kemudian disimpan dalam array global rootFolders.
        Folder *folder = rootFolders[i];
        strcpy(folder->name, folderNames[i]);
        folder->fileCount = fileCounts[i];
        folder->subfolderCount = 0;

        // Membentuk nama file lengkap: nama + ekstensi
        for (int j = 0; j < folder->fileCount; j++) {
            MyFile &file = folder->files[j];
            strcpy(file.name, fileNames[i][j]); // menyalin isi string  (bertipe const char*) ke array karakter  (char[]).
            strcpy(file.extension, extension);

            // Isi dummy untuk file
            string fullFileName = string(file.name) + "." + file.extension;

            // Isi konten dummy
            string content = "Ini adalah konten dari file dummy: " + fullFileName + "\n";

            // Buat file fisik dengan konten dummy
            ofstream fout(fullFileName, ios::out | ios::trunc);
            if (fout.is_open()) {
                fout << content;
                fout.close();
            }

            // Ambil ukuran file dari disk menggunakan seek (untuk akurasi byte)
            ifstream fin(fullFileName, ios::binary | ios::ate);
            file.size = fin.tellg();  // Ukuran asli dalam byte
            file.sizeOnDisk = ((file.size + 4095) / 4096) * 4096; // Asumsi cluster 4KB
            fin.close();

            // Simpan ke fileSizeMap (array 2D untuk menampilkan seluruh isi size file yang ada di dalam tiap folder root)
            fileSizeMap[i][j] = file.size;

            // Inisialisasi metadata waktu (created, accessed, modified)
            getCurrentTimestamp(file.meta.createdAt);
            getCurrentTimestamp(file.meta.accessedAt);
            getCurrentTimestamp(file.meta.modifiedAt);
        }
    }

    // Posisi folder default di root
    currentFolder = nullptr;
    cout << "Inisialisasi sample data beserta file fisik & metadata selesai!\n";
}

// Menampilkan path folder saat ini dengan format seperti: /root/folder1/folder2
void displayCurrentPath() {
    cout << getCurrentPathString() << endl;
}

// Fungsi untuk membentuk string path dari stack navigasi (parentStack + currentFolder)
string getCurrentPathString() {
    string path = "/root";
    for (int i = 0; i <= parentTop; i++) {
        if (parentStack[i] != nullptr) {
            path += "/";
            path += parentStack[i]->name;
        }
    }
    if (currentFolder != nullptr) {
        path += "/";
        path += currentFolder->name;
    }
    return path;
}

// Menggabungkan path saat ini dengan nama dan ekstensi file → digunakan untuk metadata
string getFileFullPath(const MyFile &file) {
    return getCurrentPathString() + "/" + file.name + "." + file.extension;
}

// Menampilkan seluruh folder root beserta isinya (rekursif untuk subfolder)
void displayRootFolders() {
    if (rootFolderCount == 0) {
        cout << "Belum ada folder!\n";
        return;
    }
    for (int i = 0; i < rootFolderCount; i++) {
        cout << "Folder [" << i << "]: " << rootFolders[i]->name << endl;
        displayCurrentFolderContents(rootFolders[i], 1);
    }
}

// Menampilkan isi folder (file + subfolder), dengan indentasi sesuai kedalaman folder
void displayCurrentFolderContents(Folder *folder, int depth) {
    if (folder == nullptr) return;

    // Indentasi readibility sesuai level kedalaman folder
    for (int i = 0; i < depth; i++) { 
        cout << "  "; 
    }
    cout << "[FOLDER] " << folder->name << endl;

    // Tampilkan semua file dalam folder ini
    for (int j = 0; j < folder->fileCount; j++) {
        for (int i = 0; i < depth + 1; i++) { 
            cout << "  ";
        }

        cout << "- " << folder->files[j].name << endl;
    } 

    // Tampilkan subfolder secara rekursif
    for (int k = 0; k < folder->subfolderCount; k++) {
        displayCurrentFolderContents(folder->subfolders[k], depth + 1);
    }
}

// Menambahkan folder baru ke dalam currentFolder
void addSubfolderToCurrent() {
    // Jika user sedang di root
    if (currentFolder == nullptr) {
        if (rootFolderCount >= 10) {
            cout << "Jumlah folder maksimum di root telah tercapai!\n";
            return;
        }

        Folder *newFolder = new Folder;
        cout << "Masukkan nama folder (root): ";
        cin.getline(newFolder->name, 100);
        newFolder->fileCount = 0;
        newFolder->subfolderCount = 0;
        rootFolders[rootFolderCount++] = newFolder;

        cout << "Folder berhasil ditambahkan ke root!\n";
        return;
    }

    // Jika user berada di subfolder
    if (currentFolder->subfolderCount >= 10) {
        cout << "Subfolder penuh!\n";
        return;
    }

    Folder *newSub = new Folder;
    cout << "Masukkan nama subfolder: ";
    cin.getline(newSub->name, 100);
    newSub->fileCount = 0;
    newSub->subfolderCount = 0;
    currentFolder->subfolders[currentFolder->subfolderCount++] = newSub;

    cout << "Subfolder berhasil ditambahkan ke folder: " << currentFolder->name << endl;
}

// Masuk ke subfolder dari folder saat ini atau dari root
void navigateIntoSubfolder() {
    if (currentFolder == nullptr) {
        // Menampilkan folder mana yang ingin dimasuki pada root
        displayRootFolders();

        int index;
        cout << "Pilih index folder utama untuk masuk ke dalamnya: ";
        cin >> index;
        cin.ignore();

        if (index < 0 || index >= rootFolderCount) {
            cout << "Index tidak valid.\n";
            return;
        }

        // Reset stack saat mulai dari root
        parentTop = -1;
        currentFolder = rootFolders[index];

        cout << "Berhasil masuk ke folder: " << currentFolder->name << endl;
    } else {
        // Menampilkan folder mana yang ingin dimasuki pada subfolder
        if (currentFolder->subfolderCount == 0) {
            cout << "Tidak ada subfolder untuk dimasuki.\n";
            return;
        }

        for (int i = 0; i < currentFolder->subfolderCount; i++) {
            cout << "Subfolder [" << i << "]: " << currentFolder->subfolders[i]->name << endl;
        }

        int index;
        cout << "Pilih index subfolder: ";
        cin >> index;
        cin.ignore();

        if (index < 0 || index >= currentFolder->subfolderCount) {
            cout << "Index tidak valid.\n";
            return;
        }

        // Push current folder ke stack, lalu update currentFolder. Perubahan posisi direktori terjadi
        parentStack[++parentTop] = currentFolder;
        currentFolder = currentFolder->subfolders[index];   // folder saat ini akan diubah posisinya dengan menu pemilihan folder yang ditampilkan pada folder saat ini

        cout << "Berhasil masuk ke folder: " << currentFolder->name << endl;
    }
}

// Kembali ke folder sebelumnya menggunakan stack (LIFO)
void navigateBack() {
    if (parentTop == -1) {  // -1 ditetapkkan sebagai posisi root
        currentFolder = nullptr;
        cout << "Kembali ke root.\n";
        return;
    }
    currentFolder = parentStack[parentTop--];
    
    if (currentFolder == nullptr) {
        cout << "Kembali ke folder: root";
    } else {
        cout << "Kembali ke folder: " <<  currentFolder->name << endl;
    }
}

// Menghapus subfolder berdasarkan index dari currentFolder (atau root jika currentFolder = nullptr)
void deleteSubfolderFromCurrent() {
    Folder *target;
    if (currentFolder == nullptr) {
        target = nullptr;
    } else {
        target = currentFolder;
    }

    if (target == nullptr || target->subfolderCount == 0) {
        cout << "Tidak ada subfolder untuk dihapus.\n";
        return;
    }

    for (int i = 0; i < target->subfolderCount; i++) {
        cout << "[" << i << "] " << target->subfolders[i]->name << endl;
    }

    int index;
    cout << "Pilih index subfolder yang ingin dihapus: ";
    cin >> index;
    cin.ignore();

    if (index < 0 || index >= target->subfolderCount) {
        cout << "Index tidak valid.\n";
        return;
    }

    delete target->subfolders[index];

    // Geser subfolder untuk mengisi celah
    for (int i = index; i < target->subfolderCount - 1; i++) {
        target->subfolders[i] = target->subfolders[i + 1];
    }

    
    target->subfolderCount--;
    cout << "Subfolder berhasil dihapus.\n";
}

// Mencari semua file yang cocok di folder dan subfolder menggunakan sequential search tanpa sentinel pada data belum terurut
void seqNonSentinelBelumUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path) {
    if (folder == nullptr) return;

    int j = 0;

    while (j < folder->fileCount) {
        if (strcmp(folder->files[j].name, target.c_str()) == 0) {
            cout << "File \"" << target 
                 << "\" ditemukan di folder \"" 
                 << path << "/" << folder->name 
                 << "\" pada index ke-" << j << endl;

            foundOverall = true;
        }
        
        j++;
    }

    // Lanjut ke subfolder jika belum ketemu
    for (int i = 0; i < folder->subfolderCount; ++i) {
        seqNonSentinelBelumUrutInFolder(folder->subfolders[i], target, foundOverall, path + "/" + folder->name);
    }
}

void seqNonSentinelBelumUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < rootFolderCount; i++) {
        seqNonSentinelBelumUrutInFolder(rootFolders[i], target, foundOverall, "/root");
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

// Sequential search pada data yang sudah diurutkan. Proses dihentikan lebih awal jika elemen saat ini lebih besar dari target.
void seqNonSentinelSudahUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path) {
    if (!folder) return;

    int j = 0;

    while (
        j < folder->fileCount 
        && strcmp(folder->files[j].name, target.c_str()) <= 0
    ) {
        if (strcmp(folder->files[j].name, target.c_str()) == 0) {
            cout << "File \"" << target << "\" ditemukan di folder \"" 
                 << path << "/" << folder->name << "\" pada index ke-" << j << endl;
            
            foundOverall = true;
        } 
    
        j++;    
    }

    // Rekursi ke subfolder jika belum ditemukan
    for (int i = 0; i < folder->subfolderCount; ++i) {
        seqNonSentinelSudahUrutInFolder(folder->subfolders[i], target, foundOverall, path + "/" + folder->name);
    }
}

void seqNonSentinelSudahUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < rootFolderCount; ++i) {
        seqNonSentinelSudahUrutInFolder(rootFolders[i], target, foundOverall, "/root");
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

// Sequential search (belum urut) pakai sentinel untuk hentikan loop tanpa cek batas array. Hanya valid jika jumlah file saat ini < 10.
void seqSentinelBelumUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path) {
    if (!folder) return;

    int n = folder->fileCount;

    if (n >= 10) {
        cout << "Folder \"" << folder->name << "\" penuh, tidak bisa mencari dengan sentinel.\n";
        return;
    }

    // Simpan sentinel
    strcpy(folder->files[n].name, target.c_str());

    int j = 0;
    while (strcmp(folder->files[j].name, target.c_str()) != 0) {
        j++;
    }

    if (j < n) {
        cout << "File \"" << target << "\" ditemukan di folder \"" 
             << path << "/" << folder->name << "\" pada index ke-" << j << endl;
        foundOverall = true;
    }

    // Rekursi ke subfolder
    for (int i = 0; i < folder->subfolderCount; ++i) {
        seqSentinelBelumUrutInFolder(folder->subfolders[i], target, foundOverall, path + "/" + folder->name);
    }
}

void seqSentinelBelumUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < rootFolderCount; i++) {
        seqSentinelBelumUrutInFolder(rootFolders[i], target, foundOverall, "/root");
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

// Sentinel dipasang agar loop berhenti jika menemukan nilai lebih besar dari target, sesuai urutan data. Aman hanya jika fileCount < 10.
void seqSentinelSudahUrutInFolder(Folder *folder, const string &target, bool &foundOverall, string path) {
    if (!folder) return;

    int n = folder->fileCount;

    if (n >= 10) {
        cout << "Folder \"" << folder->name << "\" penuh, tidak bisa menggunakan sentinel.\n";
        return;
    }

    // Pasang sentinel
    strcpy(folder->files[n].name, target.c_str());

    int j = 0;

    while (strcmp(folder->files[j].name, target.c_str()) < 0) {
        j++;
    }

    if (j < n && strcmp(folder->files[j].name, target.c_str()) == 0) {
        cout << "File \"" << target << "\" ditemukan di folder \""
             << path << "/" << folder->name
             << "\" pada index ke-" << j << endl;
        foundOverall = true;
    }

    // Rekursi ke subfolder
    for (int i = 0; i < folder->subfolderCount; ++i) {
        seqSentinelSudahUrutInFolder(folder->subfolders[i], target, foundOverall, path + "/" + folder->name);
    }
}

void seqSentinelSudahUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < rootFolderCount; i++) {
        seqSentinelSudahUrutInFolder(rootFolders[i], target, foundOverall, "/root");
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

// Binary Search dilakukan hanya pada file di folder saat ini. Jika tidak ditemukan, pencarian dilanjutkan ke subfolder secara rekursif.
void binarySearchInFolder(Folder *folder, const string &target, bool &foundOverall, string path) {
    if (!folder) return;

    int kiri = 0;
    int kanan = folder->fileCount - 1;
    int tengah;

    while (kiri <= kanan) {
        tengah = (kiri + kanan) / 2;

        int cmp = strcmp(folder->files[tengah].name, target.c_str());

        if (cmp == 0) {
            cout << "File \"" << target << "\" ditemukan di folder \""
                 << path << "/" << folder->name
                 << "\" pada index ke-" << tengah << endl;
            
            foundOverall = true;
            break;
        } else if (cmp > 0) {
            kanan = tengah - 1;
        } else {
            kiri = tengah + 1;
        }
    }

    // Lanjut ke subfolder jika belum ditemukan
    for (int i = 0; i < folder->subfolderCount; ++i) {
        binarySearchInFolder(folder->subfolders[i], target, foundOverall, path + "/" + folder->name);
    }
}

void binarySearchSudahUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < rootFolderCount; ++i) {
        binarySearchInFolder(rootFolders[i], target, foundOverall, "/root");
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

// Bubble Sort: Tukar berulang elemen bersebelahan hingga urut (iterasi penuh).
void sortFilesInCurrentFolderWithBubbleSort() {
    if (!currentFolder || currentFolder->fileCount <= 1) {
        cout << "Folder kosong atau hanya memiliki satu file. Tidak perlu sorting.\n";
        return;
    }

    int n = currentFolder->fileCount;
    int i, j;
    MyFile temp;

    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (
                strcmp(
                    currentFolder->files[j].name
                    , currentFolder->files[j + 1].name
                ) > 0
            ) {
                temp = currentFolder->files[j];
                currentFolder->files[j] = currentFolder->files[j + 1];
                currentFolder->files[j + 1] = temp;
            }
        }
    }

    cout << "File di folder saat ini telah diurutkan (Bubble Sort).\n";
}

// Insertion Sort: Sisipkan elemen ke posisi yang tepat di bagian array yang sudah urut.
void sortFilesInCurrentFolderWithInsertionSort() {
    if (!currentFolder || currentFolder->fileCount <= 1) {
        cout << "Folder kosong atau hanya memiliki satu file. Tidak perlu sorting.\n";
        return;
    }

    int n = currentFolder->fileCount;
    int i, j;
    MyFile temp;
    
    for (i = 1; i < n; i++) {
        temp = currentFolder->files[i];
        j = i - 1;
        while (
            j >= 0 
            && strcmp(currentFolder->files[j].name, temp.name) > 0
        ) {
            currentFolder->files[j + 1] = currentFolder->files[j];
            j = j - 1;
        }

        currentFolder->files[j + 1] = temp;
    }
    cout << "File di folder saat ini telah diurutkan (Insertion Sort).\n";
}

// Selection Sort: Pilih elemen terkecil dari sisa array dan tukar ke posisi saat ini.
void sortFilesInCurrentFolderWithSelectionSort() {
    if (!currentFolder || currentFolder->fileCount <= 1) {
        cout << "Folder kosong atau hanya memiliki satu file. Tidak perlu sorting.\n";
        return;
    }
    int n = currentFolder->fileCount;
    int current, j, minIndex;
    MyFile temp;
    for (current = 0; current < n - 1; current++) {
        minIndex = current;
        for (int j = current + 1; j < n; j++) {
            if (
                strcmp(
                    currentFolder->files[j].name
                    , currentFolder->files[minIndex].name) 
                < 0
            ) {
                minIndex = j;
            }
        }
        if (minIndex != current) {
            temp = currentFolder->files[current];
            currentFolder->files[current] = currentFolder->files[minIndex];
            currentFolder->files[minIndex] = temp;
        }
    }
    cout << "File di folder saat ini telah diurutkan (Selection Sort).\n";
}

// Shell Sort: Versi efisien Insertion Sort dengan gap variatif untuk percepat urutan.
void sortFilesInCurrentFolderWithShellSort() {
    if (!currentFolder || currentFolder->fileCount <= 1) {
        cout << "Folder kosong atau hanya memiliki satu file. Tidak perlu sorting.\n";
        return;
    }
    int n = currentFolder->fileCount;
    int gap, i, j;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; ++i) {
            MyFile temp = currentFolder->files[i];
            int j;
            for (
                j = i; 
                j >= gap && strcmp(currentFolder->files[j - gap].name, temp.name) > 0; 
                j -= gap
            ) {
                currentFolder->files[j] = currentFolder->files[j - gap];
            }
            currentFolder->files[j] = temp;
        }
    }
    cout << "File di folder saat ini telah diurutkan (Shell Sort).\n";
}

//========================  QUICK SORT PAKAI 2 FUNCTION (DI BAWAH INI) ============================
// Quick Sort: Bagi dan urutkan elemen dengan pivot secara rekursif (divide & conquer).
// Fungsi Quick Sort untuk file berdasarkan nama
void sortQuickSortFiles(MyFile files[], int first, int last) {
    int low, high;
    MyFile temp;
    char pivot[100];

    low = first;
    high = last;
    strcpy(pivot, files[(first + last) / 2].name);

    do {
        while (strcmp(files[low].name, pivot) < 0)  { low++;    }
        while (strcmp(files[high].name, pivot) > 0) { high--;   }

        if (low <= high) {
            temp = files[low];
            files[low] = files[high];
            files[high] = temp;
            low++;
            high--;
        }
    } while (low <= high);

    if (first < high)   { sortQuickSortFiles(files, first, high);   }
    if (low < last)     { sortQuickSortFiles(files, low, last);     }
}

void sortFilesInCurrentFolderWithQuickSort() {
    if (!currentFolder || currentFolder->fileCount <= 1) {
        cout << "Folder kosong atau hanya memiliki satu file. Tidak perlu sorting.\n";
        return;
    }
    sortQuickSortFiles(currentFolder->files, 0, currentFolder->fileCount - 1);
    cout << "File di folder saat ini telah diurutkan (Quick Sort).\n";
}
//========================  QUICK SORT PAKAI 2 FUNCTION (DI ATAS INI) ============================

// Membuat file baru di folder saat ini dan menulis isi awal ke disk.
void createFileInCurrentFolder() {
    if (currentFolder->fileCount >= 10) {
        cout << "Folder penuh, tidak bisa menambah file lagi.\n";
        return;
    }

    MyFile &file = currentFolder->files[currentFolder->fileCount];
    cout << "Nama file (tanpa ekstensi): ";
    cin.getline(file.name, 100);
    cout << "Ekstensi file (kosongkan untuk default .txt): ";
    cin.getline(file.extension, 10);
    
    // Jika user tidak mengisi ekstensi, fallback ke txt
    if (strlen(file.extension) == 0) {
        strcpy(file.extension, "txt");
    }

    string fileName = string(file.name) + "." + file.extension;
    ofstream fout;
    fout.open(fileName, ios::out | ios::trunc);
    if (!fout.is_open()) {
        cout << "Gagal membuat file.\n";
        return;
    }

    cout << "Masukkan konten file:\n";
    string content;
    getline(cin, content);
    fout << content;
    fout.close();

    file.size = getFileSizeWithFstream(fileName); 
    file.sizeOnDisk = ((file.size + 4095) / 4096) * 4096;

    getCurrentTimestamp(file.meta.createdAt);

    // Kosongkan modified/accessed untuk awal
    strcpy(file.meta.modifiedAt, "-");
    strcpy(file.meta.accessedAt, "-");

    currentFolder->fileCount++;

    cout << "File berhasil dibuat: " << fileName << "\n";
    cout << "Ukuran (asli): " << file.size << " byte\n";
    cout << "Ukuran (disk): " << file.sizeOnDisk << " byte\n";

    cout << "File berhasil dibuat: " << fileName << "\n";
}

// Membaca dan menampilkan isi file dari folder aktif menggunakan fstream.
void readFileFromCurrentFolder() {
    if (currentFolder->fileCount == 0) {
        cout << "Tidak ada file untuk dibaca.\n";
        return;
    }

    // Tampilkan daftar file
    for (int i = 0; i < currentFolder->fileCount; ++i) {
        cout << "[" << i << "] " << currentFolder->files[i].name << "." << currentFolder->files[i].extension << endl;
    }

    int index;
    cout << "Pilih index file: ";
    cin >> index;
    cin.ignore();

    // Validasi index
    if (index < 0 || index >= currentFolder->fileCount) {
        cout << "Index tidak valid.\n";
        return;
    }

    MyFile &file = currentFolder->files[index];
    string fileName = string(file.name) + "." + file.extension;

    // Buka file menggunakan fstream dan mode ios::in (READ)
    fstream fin;
    fin.open(fileName, ios::in);

    if (!fin.is_open()) {
        cout << "Gagal membuka file: " << fileName << "\n";
        return;
    }

    cout << "\n=== Isi File: " << fileName << " ===\n";
    string line;
    while (getline(fin, line)) {
        cout << line << '\n';
    }

    fin.close();

    getCurrentTimestamp(file.meta.accessedAt);
}

// Mengganti seluruh isi file yang dipilih dan perbarui metadata "modifiedAt".
void updateFileInCurrentFolder() {
    if (currentFolder->fileCount == 0) {
        cout << "Tidak ada file untuk diperbarui.\n";
        return;
    }

    // Tampilkan daftar file
    for (int i = 0; i < currentFolder->fileCount; ++i) {
        cout << "[" << i << "] " << currentFolder->files[i].name
             << "." << currentFolder->files[i].extension << endl;
    }

    int index;
    cout << "Pilih index file yang ingin diperbarui: ";
    cin >> index;
    cin.ignore();

    // Validasi index
    if (index < 0 || index >= currentFolder->fileCount) {
        cout << "Index tidak valid.\n";
        return;
    }

    MyFile &file = currentFolder->files[index];
    string fileName = string(file.name) + "." + file.extension;

    // Buka file dengan mode w+ (tulis + baca + hapus isi lama)
    fstream fout;
    fout.open(fileName, ios::in | ios::out | ios::trunc);
    if (!fout.is_open()) {
        cout << "Gagal membuka file untuk diperbarui.\n";
        return;
    }

    cout << "\nMasukkan isi baru file (menimpa seluruh isi sebelumnya):\n";
    string newContent;
    getline(cin, newContent);

    
    // Tulis ke file
    fout << newContent;
    fout.close();

    // Hitung ukuran file secara aktual
    file.size = getFileSizeWithFstream(fileName);
    file.sizeOnDisk = ((file.size + 4095) / 4096) * 4096;

    getCurrentTimestamp(file.meta.modifiedAt);

    cout << "File berhasil diperbarui: " << fileName << endl;
}

// Menghapus file secara fisik dari disk dan hapus entry-nya dari array.
void deleteFileFromCurrent() {
    if (currentFolder->fileCount == 0) {
        cout << "Tidak ada file untuk dihapus.\n";
        return;
    }

    // Tampilkan file yang tersedia
    for (int i = 0; i < currentFolder->fileCount; i++) {
        cout << "[" << i << "] " << currentFolder->files[i].name << "." << currentFolder->files[i].extension << endl;
    }

    int index;
    cout << "Pilih index file yang ingin dihapus: ";
    cin >> index;
    cin.ignore();

    if (index < 0 || index >= currentFolder->fileCount) {
        cout << "Index tidak valid.\n";
        return;
    }

    MyFile &file = currentFolder->files[index];
    string fileName = string(file.name) + "." + file.extension;

    // Hapus file dari disk
    if (remove(fileName.c_str()) != 0) {
        cout << "Gagal menghapus file fisik: " << fileName << "\n";
    } else {
        cout << "File fisik dihapus: " << fileName << "\n";
    }

    // Hapus dari struct array
    for (int i = index; i < currentFolder->fileCount - 1; i++) {
        currentFolder->files[i] = currentFolder->files[i + 1];
    }
    currentFolder->fileCount--;

    cout << "File berhasil dihapus dari sistem.\n";
}

// Mengembalikan ukuran byte file dengan seek ke akhir (accurate file size).
unsigned long long getFileSizeWithFstream(const string &filename) {
    ifstream in(filename, ios::binary | ios::ate); // buka dan langsung lompat ke akhir
    if (!in.is_open()) return 0;

    return in.tellg(); // posisi akhir = ukuran file
}

// Mengisi string timestamp dengan waktu lokal saat ini (format yyyy-mm-dd hh:mm).
void getCurrentTimestamp(char waktu[]) {
    time_t now = time(0);                 // ambil waktu sekarang
    tm *ltm = localtime(&now);            // konversi ke format lokal
    strftime(waktu, 20, "%Y-%m-%d %H:%M", ltm); // format ke string
}

// Menampilkan metadata lengkap file (nama, ukuran, waktu dibuat/akses/modifikasi).
void showFileMetadata() {
    if (currentFolder == nullptr || currentFolder->fileCount == 0) {
        cout << "Tidak ada file di folder ini.\n";
        return;
    }

    for (int i = 0; i < currentFolder->fileCount; ++i) {
        cout << "[" << i << "] " << currentFolder->files[i].name
             << "." << currentFolder->files[i].extension << endl;
    }

    int index;
    cout << "Pilih index file: ";
    cin >> index;
    cin.ignore();

    if (index < 0 || index >= currentFolder->fileCount) {
        cout << "Index tidak valid.\n";
        return;
    }

    MyFile &file = currentFolder->files[index];

    cout << "\n==== METADATA FILE ====\n";
    cout << "Nama File    : " << file.name << "." << file.extension << endl;
    cout << "Lokasi File  : " << getFileFullPath(file) << endl;
    cout << "Ukuran       : " << file.size << " B"
         << " / " << fixed << setprecision(2)
         << (file.size / 1024.0) << " KB" << endl;
    cout << "Size on Disk : " << file.sizeOnDisk << " B"
         << " / " << (file.sizeOnDisk / 1024.0) << " KB" << endl;
    cout << "Created At   : " << file.meta.createdAt << endl;
    cout << "Modified At  : " << file.meta.modifiedAt << endl;
    cout << "Accessed At  : " << file.meta.accessedAt << endl;
    
}

// Menghitung total ukuran file (termasuk nested subfolder) secara rekursif. Untuk pengisian fileSizeMap pada root
unsigned long long getTotalSizeOfFolderRecursive(Folder *folder) {
    if (!folder) return 0;

    unsigned long long total = 0;

    // Tambahkan semua file di folder saat ini
    for (int i = 0; i < folder->fileCount; ++i) {
        total += folder->files[i].size;
    }

    // Tambahkan file di seluruh subfolder
    for (int i = 0; i < folder->subfolderCount; ++i) {
        total += getTotalSizeOfFolderRecursive(folder->subfolders[i]);
    }

    return total;
}

// Memperbarui fileSizeMap[][] dengan total ukuran file tiap root folder.
void updateFileSizeMapForAllRootFolders() {
    for (int i = 0; i < rootFolderCount; ++i) {
        fileSizeMap[i][0] = getTotalSizeOfFolderRecursive(rootFolders[i]);
    }
}

// Menampilkan total ukuran file dari tiap folder root menggunakan fileSizeMap[][].
void showTotalSizeFromFileSizeMap() {
    updateFileSizeMapForAllRootFolders();

    cout << "\n=== Total Size Semua File per Folder Root (disimpan di fileSizeMap[i][0]) ===\n";
    for (int i = 0; i < rootFolderCount; ++i) {
        cout << "Folder [" << i << "] " << rootFolders[i]->name
             << " - Total Size (termasuk nested): "
             << fixed << setprecision(2)
             << (fileSizeMap[i][0] / 1024.0) << " KB\n";
    }
}