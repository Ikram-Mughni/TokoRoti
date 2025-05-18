#include <iostream>
#include <cstring>
using namespace std;

void garis()
{
    cout << "=================================\n";
}

void garis2()
{
    cout << "---------------------------------\n";
}

struct Queue
{
    char nama[30];
    int jenisRoti[10];
    int jumlahRoti[10];
    int banyakPesanan;
    float totalHarga;
    Queue *next;
};

struct stackHistory
{
    char nama[30];
    int jenisRoti[10];
    int jumlahRoti[10];
    int banyakPesanan;
    float totalHarga;
    stackHistory *next;
};

Queue *depan, *belakang;

stackHistory *topHistory = nullptr;
stackHistory *awalHistory = nullptr;

void buatQueue()
{
    depan = belakang = nullptr;
}

bool queueKosong()
{
    return depan == nullptr;
}

float hargaPerKode(int kode)
{
    if (kode == 110)
        return 8000;
    else if (kode == 111)
        return 9000;
    else if (kode == 112)
        return 10000;
    else if (kode == 113)
        return 9500;
    else if (kode == 114)
        return 7000;
    else if (kode == 115)
        return 8000;
    else if (kode == 116)
        return 7500;
    else if (kode == 117)
        return 7500;
    else if (kode == 118)
        return 8000;
    else if (kode == 119)
        return 11000;
    else if (kode == 120)
        return 14000;
    else
        return 0;
}

void enqueueAmbilAntreanTokoRoti()
{
    Queue *baru = new Queue;
    baru->banyakPesanan = 0;
    baru->totalHarga = 0;

    cout << "==== Ambil Antrean ====\n\n";
    cin.ignore();
    cout << "Masukkan nama pelanggan: ";
    cin.getline(baru->nama, 30);

    char lagi;
    do
    {
        if (baru->banyakPesanan >= 10)
        {
            cout << "Maksimal 10 jenis roti per pelanggan.\n";
            break;
        }

        int pilihJenisRoti, jumlah;
        cout << "\n=== Pilih Jenis Roti ===\n";
        cout << "110. Cokelat (Rp8000)\n";
        cout << "111. Keju (Rp9000)\n";
        cout << "112. Sosis (Rp10000)\n";
        cout << "113. Pisang (Rp9500)\n";
        cout << "114. Tawar (Rp7000)\n";
        cout << "115. Taro (Rp8000)\n";
        cout << "116. Strawbery (Rp7500)\n";
        cout << "117. Bluberry (Rp7500)\n";
        cout << "118. Srikaya (Rp8000)\n";
        cout << "119. Abon (Rp11000)\n";
        cout << "120. Croissant (Rp14000)\n";
        garis();
        cout << "Masukkan kode roti      : ";
        cin >> pilihJenisRoti;

        float hargaSatuan = hargaPerKode(pilihJenisRoti);
        if (hargaSatuan == 0)
        {
            cout << "Kode roti tidak valid!\n";
            continue;
        }

        cout << "Masukkan jumlah roti    : ";
        cin >> jumlah;
        if (jumlah <= 0)
        {
            cout << "Jumlah harus positif!\n";
            continue;
        }

        baru->jenisRoti[baru->banyakPesanan] = pilihJenisRoti;
        baru->jumlahRoti[baru->banyakPesanan] = jumlah;
        baru->totalHarga += hargaSatuan * jumlah;
        baru->banyakPesanan++;

        garis();
        cout << "Pesanan roti berhasil ditambahkan.\n";

        cout << "Mau pesan roti lain? (y/n): ";
        cin >> lagi;

    } while (lagi == 'y' || lagi == 'Y');

    baru->next = nullptr;
    if (depan == nullptr)
    {
        depan = belakang = baru;
    }
    else
    {
        belakang->next = baru;
        belakang = baru;
    }

    garis();
    cout << "\nTotal harga semua roti: Rp" << baru->totalHarga << endl;
    cout << "Pesanan sudah masuk antrean.\n";
}

void pushHistory(const Queue *data)
{
    stackHistory *baru = new stackHistory;
    strcpy(baru->nama, data->nama);
    baru->banyakPesanan = data->banyakPesanan;
    baru->totalHarga = data->totalHarga;

    for (int i = 0; i < data->banyakPesanan; i++)
    {
        baru->jenisRoti[i] = data->jenisRoti[i];
        baru->jumlahRoti[i] = data->jumlahRoti[i];
    }

    baru->next = nullptr;

    if (awalHistory == nullptr)
    {
        awalHistory = topHistory = baru;
    }
    else
    {
        topHistory->next = baru;
        topHistory = baru;
    }
}

void dequeueLayaniPembeliTokoRoti()
{
    if (queueKosong())
    {
        cout << "Tidak ada antrean yang harus dilayani.\n";
    }
    else
    {
        Queue *hapus = depan;
        cout << "\nMelayani pelanggan: " << hapus->nama << endl;
        garis2();
        cout << "Pesanan:\n";
        for (int i = 0; i < hapus->banyakPesanan; i++)
        {
            int kode = hapus->jenisRoti[i];
            int jumlah = hapus->jumlahRoti[i];
            float harga = hargaPerKode(kode);
            float subtotal = harga * jumlah;

            cout << "- Kode Roti: " << kode;
            cout << "| Jumlah: " << jumlah;
            cout << "| Subtotal: Rp" << subtotal << endl;
        }
        garis2();
        cout << "Total yang harus dibayar: Rp" << hapus->totalHarga << endl;
        garis();

        pushHistory(hapus);

        depan = depan->next;
        delete hapus;

        if (depan == nullptr)
        {
            belakang = nullptr;
        }

        cout << "\nPelanggan selesai dilayani.\n";
    }
}

void tampilkanPesananTokoRoti()
{
    if (queueKosong())
    {
        cout << "Antrean kosong.\n";
        return;
    }

    Queue *baca = depan;
    int antreanKe = 1;

    while (baca != nullptr)
    {
        cout << "Antrean ke-" << antreanKe << ":\n";
        cout << "Nama Pelanggan: " << baca->nama << endl;
        garis2();
        cout << "Daftar Roti:\n";
        for (int i = 0; i < baca->banyakPesanan; i++)
        {
            int kode = baca->jenisRoti[i];
            int jumlah = baca->jumlahRoti[i];
            float subtotal = hargaPerKode(kode) * jumlah;

            cout << "- Kode: " << kode;
            cout << "| Jumlah: " << jumlah;
            cout << "| Subtotal: Rp" << subtotal << endl;
        }
        cout << "Total Harga: Rp" << baca->totalHarga << endl;
        garis();
        cout << endl;

        baca = baca->next;
        antreanKe++;
    }
}

void popBatalkanPesananPalingAkhirAntrean()
{
    if (queueKosong())
    {
        cout << "Tidak ada pesanan yang bisa dibatalkan.\n";
        return;
    }

    Queue *bantu, *hapus;

    if (depan == belakang)
    {
        hapus = depan;
        cout << "\nPesanan atas nama " << hapus->nama << " telah dibatalkan.\n";
        delete hapus;
        depan = belakang = nullptr;
    }
    else
    {
        bantu = depan;
        while (bantu->next != belakang)
        {
            bantu = bantu->next;
        }
        hapus = belakang;
        cout << "\nPesanan atas nama " << hapus->nama << " telah dibatalkan.\n";
        delete hapus;
        belakang = bantu;
        belakang->next = nullptr;
    }
}

void tampilkanHistoryPesananTokoRoti()
{
    if (awalHistory == nullptr)
    {
        cout << "History pesanan kosong.\n";
        return;
    }

    stackHistory *baca = awalHistory;
    int nomor = 1;
    while (baca != nullptr)
    {
        cout << "\nHistory ke-" << nomor << ":\n";
        cout << "Nama Pelanggan: " << baca->nama << endl;
        garis2();
        cout << "Daftar Roti:\n";
        for (int i = 0; i < baca->banyakPesanan; i++)
        {
            int kode = baca->jenisRoti[i];
            int jumlah = baca->jumlahRoti[i];
            float subtotal = hargaPerKode(kode) * jumlah;

            cout << "- Kode: " << kode;
            cout << "| Jumlah: " << jumlah;
            cout << "| Subtotal: Rp" << subtotal << endl;
        }
        cout << "Total Harga: Rp" << baca->totalHarga << endl;
        garis();
        baca = baca->next;
        nomor++;
    }
}

int main()
{
    buatQueue();
    int menu;

    do
    {
        system("cls");
        cout << "\n===== Toko Roti Manis Lezat =====\n";
        cout << "1. Ambil Antrean\n";
        cout << "2. Layani Pembeli\n";
        cout << "3. Tampilkan Pesanan\n";
        cout << "4. Batalkan Pesanan\n";
        cout << "5. Tampilkan History Pesanan\n";
        cout << "0. Keluar Program\n\n";
        cout << "Pilih: ";
        cin >> menu;

        switch (menu)
        {
        case 1:
            system("cls");
            enqueueAmbilAntreanTokoRoti();
            system("pause");
            break;

        case 2:
            system("cls");
            dequeueLayaniPembeliTokoRoti();
            system("pause");
            break;

        case 3:
            system("cls");
            tampilkanPesananTokoRoti();
            system("pause");
            break;

        case 4:
            system("cls");
            popBatalkanPesananPalingAkhirAntrean();
            system("pause");
            break;

        case 5:
            system("cls");
            tampilkanHistoryPesananTokoRoti();
            system("pause");
            break;

        case 0:
            cout << "Keluar program Toko Roti Manis Lezat, terimakasih :)\n";
            break;

        default:
            system("cls");
            cout << "Menu tidak valid.\n";
            system("pause");
            break;
        }
    } while (menu != 0);

    return 0;
}
