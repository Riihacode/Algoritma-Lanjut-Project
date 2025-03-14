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

2) Detail Implementasi pada program ini:
    a. addFolder(), addFileToFolder(), generateInputData(), 

3) Ketika menggunakan menu sorting (MENU UTAMA nomor 6) itu hasil 
dari operasi di dalamnya masih mempengaruhi ke MENU UTAMA nomor 2

4) Function generateData() masih statis dan belum dinamis (ketika digu-
nakan itu belum dapat menambah )

5) Array 2D belum benar-benar digunakan, di sini hanya ada implementasi
yang menyerupai Array 2D. Contohnya seperti di bawah ini, yaitu:
    for (int i = 0; i < folderCount; i++) {
        cout << "Folder: " << folders[i].name << endl;
        for (int j = 0; j < folders[i].fileCount; j++) {
            cout << "- " << folders[i].files[j].name << " (" << folders[i].files[j].size << " KB)" << endl;
        }
    }

6) Rencana Lanjutan = 
    a) Rencana perbaikan kode:
       - Mengimplementasikan array 2D secara penuh (jika memungkinkan).
       - Mempelajari penggunaan pointer & rekursif untuk folder bertingkat (nested folder).
    
    b) Rencana pengembangan ekstensi (optional):
       - Membuat aplikasi Android (Framework NDK + JNI) berdasarkan konsep 
         manajemen direktori ini. Alasannya karena Android Studio IDE 
         mendukung penggunaan C++ juga.
       - Tujuannya untuk eksperimen native C++ tanpa mengakses storage 
         Android secara langsung.
       - Namun, fokus utama tetap pada penyelesaian project C++ sebagai prioritas.

    c) Source code pengembangan (jika diteruskan):
       - Link Github: 

*/
//######################  </CATATAN>  ##################################



//#######################  IMPORT LIBRARY  ###########################
#include <iostream>
#include <string>
using namespace std;

//#######################  STRUCT  ###################################
struct File {
    string name;
    int size;
};

struct Folder {
    string name;
    File files[10];
    int fileCount;
};

//#######################  VARIABLE GLOBAL  ##########################
Folder folders[10];
int folderCount = 0;

//####################  FUNCTION RE-DECLARATION  #####################
// Input Struct dan A
void addFolder();
void addFileToFolder();
void generateInputData();
void showAllFolders();
void searchFile();
void sortFilesInFolderWithBubbleSort();
void saveDataToFile();
void loadDataFromFile();
void menuSearching();
void seqNonSentinelBelumUrut();
void seqNonSentinelSudahUrut();
void seqSentinelBelumUrut();
void seqSentinelSudahUrut();
void binarySearchSudahUrut();
void showFolderRecursive(int index);
void sortFilesInFolderWithInsertionSort();
void sortFilesInFolderWithSelectionSort();
void sortFilesInFolderWithShellSort();
void sortQuickSortFiles(File files[], int first, int last);
void sortFilesInFolderWithQuickSort();
void menuSorting();

//#######################  FUNGSI UTAMA  ############################
int main() {
    int choice;

    do {
        cout << "\n====== Menu Folder & File ======" << endl;
        cout << "1. Generate Tambah Folder & File (Input Struct & Array 2D) \n";
        cout << "2. Tambah Folder (Input Struct & Array 2D)\n";
        cout << "3. Tambah File ke Folder (Input Struct & Array 2D) \n";
        cout << "4. Tampilkan Semua Folder dan File (Loop Struct & Array 2D) \n";
        cout << "5. Cari File (Searching)\n";
        cout << "6. Urutkan File dalam Folder (Sorting) \n";
        cout << "7. Tampilkan Folder dan File (Recursive) \n";
        cout << "8. Keluar \n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore(); // Agar getline tidak bermasalah
        cout << endl;

        switch (choice) {
            case 1: generateInputData();                    break;
            case 2: addFolder();                        break;
            case 3: addFileToFolder();                  break;
            case 4: showAllFolders();                   break;
            case 5: menuSearching();                    break;
            case 6: menuSorting();                      break;
            case 7: showFolderRecursive(0);             break;
            case 8: cout << "Keluar dari program.\n";   break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 8);
    
    return 0;
}

//#####################  BUSSINESS LOGIC CORE  ############################
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
        case 1: sortFilesInFolderWithBubbleSort(); break;
        case 2: sortFilesInFolderWithInsertionSort(); break;
        case 3: sortFilesInFolderWithSelectionSort(); break;
        case 4: sortFilesInFolderWithShellSort(); break;
        case 5: sortFilesInFolderWithQuickSort(); break;
        default: cout << "Pilihan tidak valid!\n";
    }
}

// Tambah Folder
void addFolder() {
    if (folderCount >= 10) {
        cout << "Jumlah folder maksimum tercapai!\n";
        return;
    }

    cout << "Masukkan nama folder: ";
    getline(
        cin, 
        folders[folderCount].name
    );
    folders[folderCount].fileCount = 0;
    folderCount++;
    cout << "Folder berhasil ditambahkan!\n";
}

// Tambah File ke Folder
void addFileToFolder() {
    showAllFolders();
    int index;
    cout << "Pilih index folder: ";
    cin >> index;
    cin.ignore();

    if (index < 0 || index >= folderCount) {
        cout << "Index folder tidak valid!\n";
        return;
    }

    if (folders[index].fileCount >= 10) {
        cout << "Folder penuh, tidak bisa menambah file lagi!\n";
        return;
    }

    cout << "Masukkan nama file: ";
    getline(
        cin, 
        folders[index]
        .files[folders[index].fileCount]
        .name
    );
    cout << "Masukkan ukuran file (KB): ";
    cin >> 
        folders[index]
        .files[folders[index].fileCount]
        .size;
    folders[index].fileCount++;
    cout << "File berhasil ditambahkan!\n";
}

// Fungsi otomatis input data folder dan file
void generateInputData() {
    // Tentukan jumlah folder
    folderCount = 3;

    // Folder 1
    folders[0].name = "folder 1";
    folders[0].fileCount = 6;
    folders[0].files[0] = {"file 1", 10};
    folders[0].files[1] = {"nyoba cpp lewat notepad", 20};
    folders[0].files[2] = {"zoo", 100};
    folders[0].files[3] = {"testing file", 23};
    folders[0].files[4] = {"backup_cmd_kali_linux", 50};
    folders[0].files[5] = {"A", 50};

    // Folder 2
    folders[1].name = "folder 2";
    folders[1].fileCount = 9;
    folders[1].files[0] = {"pertemuan1_prak_algoritma", 15};
    folders[1].files[1] = {"index_web_notepad", 25};
    folders[1].files[2] = {"C", 55};
    folders[1].files[3] = {"Rekomendasi Film 2025", 15};
    folders[1].files[4] = {"file random folder 2", 25};
    folders[1].files[5] = {"A", 32};
    folders[1].files[6] = {"rekomendasi film 2025", 35};
    folders[1].files[7] = {"file-1-di-folder-2", 15};
    folders[1].files[8] = {"B", 5};

    // Folder 3
    folders[2].name = "folder 3";
    folders[2].fileCount = 8;
    folders[2].files[0] = {"sha256_tutorial_encryption_youtube", 12};
    folders[2].files[1] = {"d", 55};
    folders[2].files[2] = {"C", 55};
    folders[2].files[3] = {"computer quantum & machine learning", 12};
    folders[2].files[4] = {"langkah-langkah instalasi vs code", 12};
    folders[2].files[5] = {"hunting_", 12};
    folders[2].files[6] = {"E", 55};
    folders[2].files[7] = {"list wifi kampus", 12};

    cout << "Data folder dan file otomatis berhasil dimasukkan!\n";
}

// Tampilkan Semua Folder dan File
void showAllFolders() {
    if (folderCount == 0) {
        cout << "Belum ada folder!\n";
        return;
    }
    
    for (int i = 0; i < folderCount; i++) {
        cout << "Folder [" << i << "]: " << folders[i].name << endl;
        for (int j = 0; j < folders[i].fileCount; j++) {
            cout << "  - "  << folders[i].files[j].name 
                 << " ("    << folders[i].files[j].size << " KB)" 
                 << endl;
        }
    }
}

// Cari File (Sequential Search non sentinel - data belum urut)
void searchFile() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool found = false;
    for (int i = 0; i < folderCount; i++) {
        for (int j = 0; j < folders[i].fileCount; j++) {
            if (folders[i].files[j].name == target) {
                cout << "File ditemukan di folder: " 
                     << folders[i].name 
                     << endl;

                found = true;
            }
        }
    }

    if (!found) {
        cout << "File tidak ditemukan.\n";
    }
}

void seqNonSentinelBelumUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(
        cin, 
        target
    );

    bool foundOverall = false;

    for (int i = 0; i < folderCount; i++) {
        bool found = false;
        int j = 0;
        
        while (
            (j < folders[i].fileCount) 
            && (!found)
        ) {
            if (folders[i].files[j].name == target) {
                found = true;
            }
            else {
                j++;
            } 
        }

        if (found) {
            cout << "File \"" << target 
                 << "\" ditemukan di folder \"" << folders[i].name 
                 << "\" pada index ke-" << j 
                 << endl;
                 
            foundOverall = true;
        }
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

void seqNonSentinelSudahUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < folderCount; i++) {
        bool found = false;
        int j = 0;

        while (
            (j < folders[i].fileCount) 
            && (!found) 
            && (target >= folders[i].files[j].name)
        ) {
            if (folders[i].files[j].name == target) {
                found = true;
            } else {
                j++;
            }
        }

        if (found) {
            cout << "File \"" << target 
                 << "\" ditemukan di folder \"" << folders[i].name 
                 << "\" pada index ke-" << j 
                 << endl;

            foundOverall = true;
        }
    }
    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

void seqSentinelBelumUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(cin, target);

    bool foundOverall = false;

    for (int i = 0; i < folderCount; i++) {
        int n = folders[i].fileCount;
        folders[i].files[n].name = target; // Sentinel
        int j = 0;

        while (folders[i].files[j].name != target) {
            j++;
        }

        if (j < n) {
            cout << "File \"" << target 
                 << "\" ditemukan di folder \"" << folders[i].name 
                 << "\" pada index ke-" << j 
                 << endl;
                 
            foundOverall = true;
        }
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

void seqSentinelSudahUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(
        cin, 
        target
    );

    bool foundOverall = false;

    for (int i = 0; i < folderCount; i++) {
        int n = folders[i].fileCount;
        folders[i].files[n].name = target; // Sentinel
        int j = 0;

        while (
            folders[i].files[j].name 
            < target
        ) {
            j++;
        }
        
        
        if (
            j < n 
            && folders[i].files[j].name == target
        ) {
            cout << "File \"" << target 
                 << "\" ditemukan di folder \"" << folders[i].name 
                 << "\" pada index ke-" << j 
                 << endl;

            foundOverall = true;
        }
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

void binarySearchSudahUrut() {
    cout << "Masukkan nama file yang dicari: ";
    string target;
    getline(
        cin, 
        target
    );

    bool foundOverall = false;

    for (int i = 0; i < folderCount; i++) {
        int kiri = 0, kanan = folders[i].fileCount - 1;
        bool found = false;
        int tengah;

        while (
            kiri <= kanan 
            && !found
        ) {
            tengah = (kiri + kanan) / 2;
            if (folders[i].files[tengah].name == target) {
                found = true;
            } else if (target < folders[i].files[tengah].name) {
                kanan = tengah - 1;
            } else {
                kiri = tengah + 1;
            }
        }

        if (found) {
            cout << "File \"" << target 
                 << "\" ditemukan di folder \"" << folders[i].name 
                 << "\" pada index ke-" << tengah 
                 << endl;

            foundOverall = true;
        }
    }

    if (!foundOverall) {
        cout << "File \"" << target << "\" tidak ditemukan.\n";
    }
}

// Sorting File dalam Folder (Bubble Sort)
// Sorting File dalam Folder (Bubble Sort)
void sortFilesInFolderWithBubbleSort() {
    showAllFolders();

    int index;
    cout << "Pilih index folder yang ingin diurutkan: ";
    cin >> index;

    if (index < 0 || index >= folderCount) {
        cout << "Index folder tidak valid!\n";
        return;
    }

    int n = folders[index].fileCount;
    int i, j;
    File temp;

    cout << "\nData sebelum diurutkan:\n";
    for (i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }

    // Bubble Sort Proses
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (folders[index].files[j].name > folders[index].files[j + 1].name) {
                temp = folders[index].files[j];
                folders[index].files[j] = folders[index].files[j + 1];
                folders[index].files[j + 1] = temp;
            }
        }
    }

    cout << "\nData setelah diurutkan:\n";
    for (i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }
}


// Fungsi rekursif untuk menampilkan semua folder dan file
void showFolderRecursive(int index) {
    if (index >= folderCount) return; // Basis: jika index melebihi jumlah folder, stop rekursi

    // Proses menampilkan folder
    cout << "Folder [" << index << "]: " << folders[index].name << endl;

    // Menampilkan semua file dalam folder tersebut
    for (int j = 0; j < folders[index].fileCount; j++) {
        cout << "  - " << folders[index].files[j].name 
             << " (" << folders[index].files[j].size << " KB)" 
             << endl;
    }

    // Rekurens: lanjut ke folder berikutnya
    showFolderRecursive(index + 1);
}

// Sorting File dalam Folder (Straight Insertion Sort)
void sortFilesInFolderWithInsertionSort() {
    showAllFolders();

    int index;
    cout << "Pilih index folder yang ingin diurutkan: ";
    cin >> index;

    if (index < 0 || index >= folderCount) {
        cout << "Index folder tidak valid!\n";
        return;
    }

    int n = folders[index].fileCount;
    int i, j;
    File Temp;

    cout << "\nData sebelum diurutkan:\n";
    for (i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }

    // Straight Insertion Sort
    for (i = 1; i < n; i++) {
        Temp = folders[index].files[i];
        j = i - 1;
        while ((j >= 0) && (Temp.name < folders[index].files[j].name)) {
            folders[index].files[j + 1] = folders[index].files[j];
            j = j - 1;
        }
        folders[index].files[j + 1] = Temp;
    }

    cout << "\nData setelah diurutkan:\n";
    for (i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }
}

// Sorting File dalam Folder (Selection Sort)
void sortFilesInFolderWithSelectionSort() {
    showAllFolders();

    int index;
    cout << "Pilih index folder yang ingin diurutkan: ";
    cin >> index;

    if (index < 0 || index >= folderCount) {
        cout << "Index folder tidak valid!\n";
        return;
    }

    int n = folders[index].fileCount;
    int current, j, minIndex;
    File temp;

    cout << "\nData sebelum diurutkan:\n";
    for (int i = 0; i < n; i++) {
        cout << folders[index].files[i].name << " (" << folders[index].files[i].size << " KB)\n";
    }

    // Selection Sort
    for (current = 0; current < n - 1; current++) {
        minIndex = current;
        for (j = current + 1; j < n; j++) {
            if (folders[index].files[j].name < folders[index].files[minIndex].name) {
                minIndex = j;
            }
        }
        // Tukar data
        temp = folders[index].files[current];
        folders[index].files[current] = folders[index].files[minIndex];
        folders[index].files[minIndex] = temp;
    }

    cout << "\nData setelah diurutkan:\n";
    for (int i = 0; i < n; i++) {
        cout << folders[index].files[i].name << " (" << folders[index].files[i].size << " KB)\n";
    }
}

// Sorting File dalam Folder (Shell Sort)
void sortFilesInFolderWithShellSort() {
    showAllFolders();

    int index;
    cout << "Pilih index folder yang ingin diurutkan: ";
    cin >> index;

    if (index < 0 || index >= folderCount) {
        cout << "Index folder tidak valid!\n";
        return;
    }

    int n = folders[index].fileCount;
    int gap, i, j;
    File temp;

    cout << "\nData sebelum diurutkan:\n";
    for (i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }

    // Shell Sort
    for (gap = n / 2; gap > 0; gap /= 2) { // Mulai gap dari n/2, dikurangi setengah-setengah
        for (i = gap; i < n; i++) {
            temp = folders[index].files[i];
            for (j = i; j >= gap && folders[index].files[j - gap].name > temp.name; j -= gap) {
                folders[index].files[j] = folders[index].files[j - gap];
            }
            folders[index].files[j] = temp;
        }
    }

    cout << "\nData setelah diurutkan:\n";
    for (i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }
}


//========================  QUICK SORT PAKAI 2 FUNCTION (DI BAWAH INI) ============================
// Fungsi Quick Sort untuk file berdasarkan nama
void sortQuickSortFiles(File files[], int first, int last) {
    int low, high;
    File temp;
    string pivot;

    low = first;
    high = last;
    pivot = files[(first + last) / 2].name; // Pivot berdasarkan nama file

    do {
        while (files[low].name < pivot) low++;
        while (files[high].name > pivot) high--;

        if (low <= high) {
            temp = files[low];
            files[low] = files[high];
            files[high] = temp;
            low++;
            high--;
        }
    } while (low <= high);

    if (first < high) sortQuickSortFiles(files, first, high);
    if (low < last) sortQuickSortFiles(files, low, last);
}

// Fungsi untuk memanggil quick sort pada folder tertentu
void sortFilesInFolderWithQuickSort() {
    showAllFolders();

    int index;
    cout << "Pilih index folder yang ingin diurutkan: ";
    cin >> index;

    if (index < 0 || index >= folderCount) {
        cout << "Index folder tidak valid!\n";
        return;
    }

    int n = folders[index].fileCount;

    cout << "\nData sebelum diurutkan:\n";
    for (int i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }

    // Quick sort
    sortQuickSortFiles(folders[index].files, 0, n - 1);

    cout << "\nData setelah diurutkan:\n";
    for (int i = 0; i < n; i++) {
        cout << "  - "  << folders[index].files[i].name 
             << " ("    << folders[index].files[i].size << " KB)" 
             << endl;
    }
}
//========================  QUICK SORT PAKAI 2 FUNCTION (DI ATAS INI) ============================