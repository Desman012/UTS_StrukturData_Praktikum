#include <iostream>
using namespace std;

// mendeklarasikan double linked list dengan nama variable Buku
struct Buku
{
    // anggota linked list
    string isbn, judul, tahun, penulis, jenis;
    int jumlah;
    Buku *next, *prev;
};

// mendefinisikan linked list buku dengan nama variable awalBuku dengan isi NULL
Buku *awalBuku = NULL;
// Membuat variable maksimal jenis buku yang ada
const int MAX_JENIS = 4;

// mendeklarasikan  struct dengan nama variable JenisBuku
struct JenisBuku
{
    // anggotanya
    string jenis, deskripsi;
} jenisBuku[MAX_JENIS]; // mendefinisikan struct menjadi array struct dengan nama varibale jenisBuku dengan panjang MAX_JENIS

// function untuk mengisi array struct jenisBuku dengan nama declareJenisBuku
void declareJenisBuku()
{
    jenisBuku[0] = {"Novel", "Novel adalah jenis buku yang berisi cerita dengan sedikit gambar."};
    jenisBuku[1] = {"Komik", "Komik adalah jenis buku yang terdiri dari gambar-gambar dan tulisan yang disusun menjadi sebuah cerita."};
    jenisBuku[2] = {"Sains", "Buku yang berisi pengetahuan akademis."};
    jenisBuku[3] = {"Kamus", "Buku yang berisi pengertian atau terjemahan kata asing."};
}

// membuat function untuk mengecek apakah ISBN ada yang duplikat tidak dengan mengembalikan nilai boolean
bool cekISBN(string isbn)
{
    Buku *cek = awalBuku;
    while (cek != NULL)
    {
        // apabila ISBN sudah ada maka akan mengembalikan nilai true
        if (cek->isbn == isbn)
        {
            return true;
        }
        cek = cek->next;
    }
    // apabila ISBN tidak ada maka akan mengembalikan nilai false
    return false;
}

// membuat function dengan return berupa linked list dengan parameter string isbn, dengan nama cariBuku
Buku *cariBuku(string isbn)
{
    Buku *sekarang = awalBuku;
    while (sekarang != NULL)
    {
        if (sekarang->isbn == isbn)
        {
            return sekarang;
        }
        sekarang = sekarang->next;
    }
    return NULL;
}

// membuat function untuk nge-print daftar jenis buku 
void listJenisBuku()
{
    cout << "\nNO.\tJenis Buku\t\tDeskripsi \n";
    cout << "========================================================================================================\n";
    for (int i = 0; i < MAX_JENIS; i++)
    {
        cout << i + 1 << ".\t" << jenisBuku[i].jenis << "\t\t" << jenisBuku[i].deskripsi << endl;
    }
}

// membuat function untuk nge-print daftar buku
void listBuku()
{
    Buku *sekarang = awalBuku;
    if (sekarang != NULL)
    {
        cout << "\n\nISBN\t\tJudul Buku\t\t\tNama Penulis\t\tJenis Buku\t\tTahun Terbit\tJumlah\n";
        cout << "====================================================================================================================\n";
        while (sekarang != NULL)
        {
            cout << sekarang->isbn << "\t\t" << sekarang->judul << "\t\t\t" << sekarang->penulis << "\t\t" << sekarang->jenis;
            cout << "\t\t\t" << sekarang->tahun << "\t\t" << sekarang->jumlah << endl;
            sekarang = sekarang->next;
        }
    }
    else
    {
        cout << "\n\nBelum ada data buku, silahkan masukan terlebih dahulu!";
    }
}

// membuat function untuk menampilkan list buku atau jenis buku, dengan paramater char pilihan
void tampil(char pilihan)
{
    char kembali;
    do
    {
        if (pilihan == 'b')
        {
            listBuku();
        }
        if (pilihan == 'j')
        {
            listJenisBuku();
        }
        cout << "\n\nKembali ke menu utama (y)? : ";
        cin >> kembali;
    } while (!(kembali == 'y' || kembali == 'Y'));
}

// membuat function untuk menambah list buku ke dalam linkedlist
void tambahBuku(){
    string isbn;
    char lanjut;
    do{
        Buku *baru = new Buku();
        cout << "\nMasukkan Nomor ISBN : ";
        cin >> isbn;
        if (cekISBN(isbn)){
            do{
                cout << "\nISBN sudah ada, tidak boleh duplikat!\n";
                cout << "\n99.\tLanjut\n00.\tKembali menu utama\n";
                cout << "==========================================\n";
                cout << "Pilih (00/99) : ";
                cin >> isbn;
            } while (!(isbn == "00" || isbn == "99"));
            if (isbn == "00"){
                return;
            }
            delete baru;
            continue;
        }
        baru->isbn = isbn;
        cout << "Masukkan Judul Buku : ";
        cin.ignore();
        getline(cin, baru->judul);
        cout << "Masukkan Nama Penulis : ";
        getline(cin, baru->penulis);
        cout << "Masukkan Tahun Terbit Buku : ";
        cin >> baru->tahun;
        cout << "Pilih Jenis Buku :\n";
        listJenisBuku();
        int pilihan;
        cout << "\nPilih nomor jenis buku: ";
        cin >> pilihan;
        if (pilihan >= 1 && pilihan <= MAX_JENIS){
            baru->jenis = jenisBuku[pilihan - 1].jenis;
        }
        else{
            cout << "\n\nNomor jenis buku tidak valid!\n";
            delete baru;
            continue;
        }
        cout << "Masukkan Jumlah Buku : ";
        cin >> baru->jumlah;
        baru->next = NULL;
        if (awalBuku == NULL){
            awalBuku = baru;
        }
        else{
            Buku *temp = awalBuku;
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->next = baru;
            baru->prev = temp;
        }
        cout << "Tambah Buku lagi (y/n)? : ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
}

// function untuk mengubah data buku
void ubahBuku()
{
    string isbn;
    listBuku();
    cout << "===========================================================================================================\n";
    cout << "00.\tKembali ke menu utama\n";
    cout << "\n\nMasukkan nomor ISBN/menu kembali : ";
    cin >> isbn;
    if (isbn == "00")
    {
        return;
    }
    Buku *dapatBuku = cariBuku(isbn);
    if (dapatBuku == NULL)
    {
        do
        {
            cout << "\n\nTidak ada buku dengan Nomor ISBN tersebut!\n";
            cout << "\nKembali ke menu utama (y)? : ";
            cin >> isbn;
        } while (!(isbn == "Y" || isbn == "y"));
        return;
    }
    cout << "\nMasukkan Judul Buku Baru : ";
    cin.ignore();
    getline(cin, dapatBuku->judul);
    cout << "Masukkan Nama Penulis Baru : ";
    getline(cin, dapatBuku->penulis);
    cout << "Masukkan Tahun Terbit Buku Baru : ";
    cin >> dapatBuku->tahun;
    cout << "Masukkan Jumlah Buku Baru : ";
    cin >> dapatBuku->jumlah;
}

// function untuk menghapus data buku
void hapusBuku(){
    string isbn;
    cout << "\nMasukkan ISBN Buku yang ingin dihapus : ";
    cin >> isbn;
    Buku *dapatBuku = cariBuku(isbn);
    if (dapatBuku == NULL){
        do{
            cout << "\n\nISBN yang anda masukan salah!\n";
            cout << "\nKembali ke menu utama (y)? : ";
            cin >> isbn;
        } while (!(isbn == "Y" || isbn == "y"));
        return;
    }
    if (dapatBuku->prev == NULL){
        awalBuku = dapatBuku->next;
    }
    else{
        dapatBuku->prev->next = dapatBuku->next;
    }
    if (dapatBuku->next != NULL){
        dapatBuku->next->prev = dapatBuku->prev;
    }
    delete dapatBuku;
    do{
        cout << "\n\nBuku dengan ISBN " << isbn << " telah dihapus.";
        cout << "\nKembali ke menu utama (y)? : ";
        cin >> isbn;
    } while (!(isbn == "Y" || isbn == "y"));
}

// program utama
int main()
{
    declareJenisBuku();
    char pilihan;
    while (true)
    {
        cout << "\n\nMenu Program :\n";
        cout << "----------------------------\n";
        cout << "a. Input Data Buku\n";
        cout << "b. Tampil Daftar Buku\n";
        cout << "c. Ubah Data Buku\n";
        cout << "d. Hapus Data Buku\n";
        cout << "e. Info Jenis Buku\n";
        cout << "f. Keluar program\n";
        cout << "Pilih (a/b/c/d/e/f) : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 'a':
            tambahBuku();
            break;
        case 'b':
            tampil('b');
            break;
        case 'c':
            ubahBuku();
            break;
        case 'd':
            hapusBuku();
            break;
        case 'e':
            tampil('j');
            break;
        case 'f':
            cout << "\n============ Program Berhenti ===========\n";
            return 0;
        default:
            cout << "\n\nPilihan tidak valid, silahkan pilih menu yang ada.\n";
        }
    }
}
