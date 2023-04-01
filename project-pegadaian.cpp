#include<iostream>
#include<iomanip>

using namespace std;
#define max 99
typedef struct{
    int no_antrian[max];
    int front=1; int rear=0;
}Queue_Nasabah;

typedef struct{
    string jenis_barang, nama_barang;
    long int nilai_barang, jumlah_pinjaman, sisa_angsuran, cicilan;
    int lama_cicilan;
}rec_gadai;

typedef struct{
    string nomor_id, nama, no_hp, alamat, status;
    long int total_angsuran;;
}rekap_nasabah;

typedef struct{
    string nomor_id, nama, no_hp, alamat;
    int kode_nasabah;
    rec_gadai barang_gadai;
}data_nasabah;

//array untuk nasabah pegadaian
typedef data_nasabah larik_nasabah[30];
larik_nasabah nasabah, nasabah1;
typedef rekap_nasabah larik_rekap[30];
larik_rekap rekap;
//deklarasi variabel
//variabel untuk antrian
Queue_Nasabah antri;

bool out=false;
int nom=100;
int n=0;
int m=0;

// variabel n : untuk nasabah
// variabel m : untuk rekapitulasi nasabah


bool is_Empty(Queue_Nasabah X){
    if(X.rear==0)return true; else return false;
}
bool is_full(Queue_Nasabah X){
    if(X.no_antrian[X.rear]==199)return true; else return false;
}

void hapus_atrian (Queue_Nasabah &X){
    //penggeser
    for(int i=1;i<=X.rear-1;i++)
        X.no_antrian[i]=X.no_antrian[i+1];
    //antrian
    X.rear--;
}

void PrintQ(Queue_Nasabah X){
    cout<<"Berikut adalah antrian Nasabah Pegadaian saat ini\n";
    cout<<"========================\n";
    cout<<"No.        Nomor Antrian\n";
    cout<<"========================\n";
    for (int i=X.front; i<=X.rear; i++){
        cout<<setw(3)<<i<<setw(18)<<"A-"<<X.no_antrian[i]<<endl;
        }
    cout<<"========================\n";
    cout<<"ada "<<X.rear<<" Antrian di tumpukan\n";
}

void PushQ(Queue_Nasabah &X){
    X.rear++;//menambah ruang di stack formulir,lalu masukan data yang baru
    cout<<"Masuk ke Antrian Pegadaian\n";
    nom++;
    X.no_antrian[X.rear]=nom;
    cout<<"Anda Berhasil masuk ke antrian A-" << nom << endl;
    cout<<"Anda berada diurutan ke "<<X.rear<<endl;
}

void cetak_nasabah(larik_nasabah Y){
    cout << "========================================== Data Detail Nasabah Pegadaian =============================================" <<endl;
    cout << "No. Kode Nasabah ID Pengenal Nasabah          Nama       Nama Barang   Cicilan   Sisa Cicilan  Sisa Total Pembayaran  " <<endl;
    cout << "======================================================================================================================" <<endl;
    for (int i=1;i<=n;i++){
        cout<<setw(3)<<i<<setw(10)<<"P-"<<Y[i].kode_nasabah<<setw(20)<<Y[i].nomor_id<<setw(14)<<Y[i].nama<<setw(18)<<Y[i].barang_gadai.nama_barang<<setw(10)<<Y[i].barang_gadai.cicilan<<setw(9)<<Y[i].barang_gadai.lama_cicilan<<" Bulan"<<setw(23)<<Y[i].barang_gadai.sisa_angsuran<<endl;
    }
    cout << "======================================================================================================================" <<endl;
    
}


void Gadai_barang(Queue_Nasabah &X, larik_nasabah &Y, larik_rekap &Z){
    int auto_kd=100;
    int pilih, pilih1;
    int pos=0, pos1=0;
    string input_id;
    double sukubunga,bunga;
    char next;
    long int input_pinjaman, max_pinjaman, sukupinjaman;
    cout<<"Selamat Datang A-" << X.no_antrian[X.front] << " di Pegadaian Silahkan Isi Data Diri Anda\n";

    cout<<"Masukkan ID Anda     : ";cin>>input_id;
    for(int j=1; j<=m ; j++){
        if(Z[j].nomor_id==input_id){
            pos=j;
            cout<<"ID Anda Telah Terdaftar dalam Perusahaan kami, silahkan lanjut ke layanan gadai barang"<<endl;
            cout<<"Apakah Lanjut atau tidak, Pilih (Y/T) : ";cin>>next;
            if (next=='Y'||next=='y'){
                n++;
                Y[n].nomor_id=Z[pos].nomor_id;
                Y[n].nama=Z[pos].nama;
                Y[n].alamat=Z[pos].alamat;
                Y[n].no_hp=Z[pos].no_hp;
                goto lanjut1;
            }
            else {
                out=false;
                goto keluar;
            }

        }
    }
    n++;
    m++;
    Y[n].nomor_id=input_id;
    Z[m].nomor_id=input_id;
    cout<<"Masukkan Nama        : ";cin>>Y[n].nama;
    Z[m].nama=Y[n].nama;
    cout<<"Masukkan Alamat      : ";cin>>Y[n].alamat;
    Z[m].alamat=Y[n].alamat;
    cout<<"Masukkan No HP       : ";cin>>Y[n].no_hp;
    Z[m].no_hp=Y[n].no_hp;

    lanjut1:
    for (int i=1;i<=n;i++){
        auto_kd=auto_kd+1;
        pos1=i;
        if (Y[pos1].kode_nasabah==auto_kd){
            cout<<""<<endl;
        }
        else {
            Y[pos1].kode_nasabah=auto_kd;
        }
    }
    cout<<"Kode Nasabah Anda    : P-" << Y[pos1].kode_nasabah <<endl;
    
    cout<<"======================================================\n";
    cout<<"Masukkan Jenis Barang Yang Ingin Digadaikan      : \n";
    cout<<"1. Elektronik\n";
    cout<<"2. Kendaraan\n";
    cout<<"3. Logam Mulia\n";
    cout<<"Pilih Jenis Barang (1-3) : ";cin>>pilih1;
    switch (pilih1){
        case 1 : Y[n].barang_gadai.jenis_barang = "ELEKTRONIK";
            break;
        case 2 : Y[n].barang_gadai.jenis_barang = "KENDARAAN";
            break;
        case 3 : Y[n].barang_gadai.jenis_barang = "LOGAM_MULIA";
            break;
        default:
            break;
    }
    cout<<"Masukkan Nama Barang Yang Ingin Digadaikan       : ";cin>>Y[n].barang_gadai.nama_barang;
    cout<<"Masukkan Nilai Barang                            : ";cin>>Y[n].barang_gadai.nilai_barang;
    
    if (Y[n].barang_gadai.nilai_barang<=5000000){
        max_pinjaman=Y[n].barang_gadai.nilai_barang*0.8;        
    }
    else if (Y[n].barang_gadai.nilai_barang>5000000 && Y[n].barang_gadai.nilai_barang<=10000000){
        max_pinjaman=Y[n].barang_gadai.nilai_barang*0.7;
    }
    else if (Y[n].barang_gadai.nilai_barang>10000000){
        max_pinjaman=Y[n].barang_gadai.nilai_barang*0.6;
    }
    cout<<"Maksimal Pinjaman yang bisa anda ajukan sebesar  : " << max_pinjaman << endl;
    ulang:
    cout<<"Ajukan Jumlah Pinjaman                           : ";cin>>input_pinjaman;
    if (input_pinjaman>max_pinjaman){
        cout << "Pengajuan Pinjaman anda terlalu besar!"<<endl;
        goto ulang;
    }
    Y[n].barang_gadai.jumlah_pinjaman=input_pinjaman;
    Z[m].total_angsuran=Z[m].total_angsuran+input_pinjaman;
    cout << "Besar Pengajuan Pinjaman anda diterima"<<endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    cout << "Pilih Lama Angsuran yang anda inginkan"<<endl;
    cout <<"1. 3 Bulan\n"; 
    cout <<"2. 6 Bulan\n"; 
    cout <<"3. 12 Bulan\n"; 
    cout <<"4. 24 Bulan\n";
    cout <<"5. 36 Bulan\n";
    cout <<"Pilih menu :";cin>>pilih;
    switch (pilih){
        case 1: Y[n].barang_gadai.lama_cicilan=3;break;
        case 2: Y[n].barang_gadai.lama_cicilan=6;break;
        case 3: Y[n].barang_gadai.lama_cicilan=12;break;
        case 4: Y[n].barang_gadai.lama_cicilan=24;break;
        case 5: Y[n].barang_gadai.lama_cicilan=36;break;
        default: break;
    }
    //RUMUS PINJAMAN

    //SUKU PINJAMAN DILUAR BUNGA
    sukupinjaman=Y[n].barang_gadai.jumlah_pinjaman/Y[n].barang_gadai.lama_cicilan;

    //MENENTUKAN SUKU BUNGA PERTAHUN 5%
    if (Y[n].barang_gadai.lama_cicilan<=12){
        sukubunga=0.05;
    }
    else if (Y[n].barang_gadai.lama_cicilan>12 && Y[n].barang_gadai.lama_cicilan<=24){
        sukubunga=0.1;
    }
    else if (Y[n].barang_gadai.lama_cicilan>24 && Y[n].barang_gadai.lama_cicilan<=36){
        sukubunga=0.15;
    }
    //PINJAMAN PERBULAN TERMASUK BUNGA DAN ADMIN
    bunga=((Y[n].barang_gadai.jumlah_pinjaman*sukubunga)/12);
    Y[n].barang_gadai.cicilan=sukupinjaman+bunga+50000;
    Y[n].barang_gadai.sisa_angsuran = Y[n].barang_gadai.cicilan*Y[n].barang_gadai.lama_cicilan;
    
    system("cls");
    cout<<"Barang yang digadai         : "<<Y[n].barang_gadai.nama_barang<<endl;
    cout<<"Pinjaman yang diajukan      : Rp."<<Y[n].barang_gadai.jumlah_pinjaman<<endl;
    cout<<"Detail Pinjaman >>>>>>>>>>>>>>"<<endl;
    cout<<"Pembayaran Pokok Perbulan   : Rp."<<sukupinjaman<<endl;
    cout<<"Bunga Pinjaman Perbulan     : Rp."<<bunga<<endl;
    cout<<"Administrasi Perbulan       : Rp.50000"<<endl;
    cout<<"Cicilan Anda Selama "<<Y[n].barang_gadai.lama_cicilan<<" Bulan, Sebesar Rp "<<Y[n].barang_gadai.cicilan<<"/Bulan"<<endl;
    hapus_atrian(antri);
    out = true;
    keluar:
    cout<<"Terimakasih"<<endl;
    //system("pause");
}


void bayar_angsuran(Queue_Nasabah &X, larik_nasabah &Y, larik_rekap &Z){
    string input_id;
    bool nyala=false;
    int input_kode,pilih,bayarbulan;
    int pos;
    long int nombayar,bayar;

    cetak_nasabah(nasabah);
    cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    cout<<"Selamat Datang A-" << X.no_antrian[X.front] << " di Layanan Pembayaran\n";
    ulang:
    cout<<"Masukkan ID Anda      : ";cin>>input_id;
    cout<<"Masukkan Kode Nasabah : P-";cin>>input_kode;
    for(int i=1; i<=n; i++){
        if (input_id==Y[i].nomor_id && input_kode==Y[i].kode_nasabah){
            pos=i;
            nyala = true;
            cout<<"Data Cocok, Silahkan Lanjut"<<endl;
        }
    }
    if (nyala==false) {
        cout<<"Data Tidak Cocok Silahkan Ulangi Kembali"<<endl;
        goto ulang;
    }
    //penggeser
    for(int i=1;i<=X.rear-1;i++)
        X.no_antrian[i]=X.no_antrian[i+1];
    //antrian
    X.rear--;
    cout<<"===================================="<<endl;
    cout<<"Menu Skema Pembayaran"<<endl;
    cout<<"1. Bayar untuk Bulan ini"<<endl;
    cout<<"2. Bayar Lunas"<<endl;
    cout<<"3. Bayar Terserah"<<endl;
    cout<<"Pilih Skema (1-3) : ";cin>>pilih;
    switch (pilih){
        case 1 :
            nombayar=Y[pos].barang_gadai.cicilan;
            bayarbulan=1; 
            break;
        case 2 :
            nombayar=Y[pos].barang_gadai.sisa_angsuran;
            bayarbulan=Y[pos].barang_gadai.lama_cicilan;
            break;
        case 3 :
            cout<<"Pembayaran untuk berapa bulan : ";cin>>bayarbulan;
            nombayar=Y[pos].barang_gadai.cicilan*bayarbulan;
        default:break;
    }
    cout<<"Pembayaran yang harus anda bayar adalah : Rp."<<nombayar<<endl;
    ulang1:
    cout<<">>>>>>>>>>>>"<<endl;
    cout<<"Lakukan Pembayaran : Rp.";cin>>bayar;

    if (bayar<nombayar){
        cout<<"Uang Anda tidak cukup, silakan lakukan pembayaran ulang"<<endl;
        goto ulang1;
    }
    else if(bayar>nombayar){
        cout<<"Anda memiliki kembalian uang sebesar : Rp."<<(bayar-nombayar)<<endl;
    }
    cout<<"Pembayaran Berhasil"<<endl;
    Y[pos].barang_gadai.sisa_angsuran=Y[pos].barang_gadai.sisa_angsuran-nombayar;
    Y[pos].barang_gadai.lama_cicilan=Y[pos].barang_gadai.lama_cicilan-bayarbulan;
    
    if (Y[pos].barang_gadai.sisa_angsuran==0){
        cout<<"Angsuran anda telah lunas, anda berhak mendapatkan kembali barang yang anda gadai"<<endl;
        
        for (int j=1;j<=m;j++){
            if (Z[j].nomor_id == Y[pos].nomor_id){               
                Z[j].status = "Lunas";  
            }
        }
        for(int l=pos; l<=(n-1); l++){
            Y[pos]=Y[pos+1];
            n--;
        }
    }
    out=true;
    cout<<"Terimakasih"<<endl;
}


void cetak_rekap(larik_rekap Z){
    cout << "======================== Data Rekapitulasi Nasabah====================" <<endl;
    cout << "No. ID Pengenal Nasabah          Nama      Total Peminjaman   Status  " <<endl;
    cout << "======================================================================" <<endl;
    for (int i=1;i<=m;i++){
        cout<<setw(3)<<i<<setw(20)<<Z[i].nomor_id<<setw(14)<<Z[i].nama<<setw(22)<<Z[i].total_angsuran<<setw(9)<<Z[i].status<<endl;
    }
    cout << "======================================================================================================================" <<endl;

}

void filtering_jenbarang(larik_nasabah &Y){
    int pilihan;
    string tamp_jenbarang;
    bool ada=false;
    cout<<"Filtering Berdasarkan Jenis Barangnya"<<endl; 
    cout<<"1. Elektronik\n"; 
    cout<<"2. Kendaraan\n"; 
    cout<<"3. Logam Mulia\n";
    cout<<"Pilih Layanan (1-3) : ";
    cin>>pilihan;
    switch (pilihan){
            case 1 : tamp_jenbarang = "ELEKTRONIK";
            break;
            case 2 : tamp_jenbarang = "KENDARAAN";
            break;
            case 3 : tamp_jenbarang = "LOGAM_MULIA";
            break;
            default:
            break;
    }
    cout << "================================ Data Detail Nasabah Pegadaian Berdasarkan Jenis Barang ==============================" <<endl;
    cout << "Jenis Barang : " << tamp_jenbarang <<endl;
    cout << "======================================================================================================================" <<endl;    
    cout << "No. Kode Nasabah ID Pengenal Nasabah          Nama       Nama Barang   Cicilan   Sisa Cicilan  Sisa Total Pembayaran  " <<endl;
    cout << "======================================================================================================================" <<endl;
    for (int i=1 ; i<=n ; i++){
        if(Y[i].barang_gadai.jenis_barang==tamp_jenbarang){
            ada=true;
            cout<<setw(3)<<i<<setw(10)<<"P-"<<Y[i].kode_nasabah<<setw(20)<<Y[i].nomor_id<<setw(14)<<Y[i].nama<<setw(18)<<Y[i].barang_gadai.nama_barang<<setw(10)<<Y[i].barang_gadai.cicilan<<setw(9)<<Y[i].barang_gadai.lama_cicilan<<" Bulan"<<setw(23)<<Y[i].barang_gadai.sisa_angsuran<<endl;
        }
    }
    if(ada=false){
        cout<<"Jenis Barang tidak ditemukan"<<endl;
    }
}

void searching_nasabah (larik_nasabah &Y){
    int no_rec=0;
    cetak_nasabah(nasabah);
	ulang:
	cout<<"Masukkan no record yang akan dicek : ";cin>>no_rec;
	if((no_rec<1)||(no_rec>n)){
		cout<<"Nomor record tidak valid, ulangi !\n";goto ulang;}
	else{
		cout<<"isi record nomor"<<no_rec<<endl;
		cout<<"Nama Nasabah  : "<<Y[n].nama<<endl;
		cout<<"ID Nasabah    : "<<Y[n].nomor_id<<endl;
		cout<<"No HP Nasabah : "<<Y[n].no_hp<<endl;
		cout<<"Alamat Nasabah: "<<Y[n].alamat<<endl;
		cout<<"Kode Nasabah  : "<<Y[n].kode_nasabah<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        cout<<"Jenis Barang Yang Digadai Sekarang   : "<<Y[n].barang_gadai.jenis_barang<<endl;
        cout<<"Nama Barang Yang Digadaikan Sekarang : "<<Y[n].barang_gadai.nama_barang<<endl;
        cout<<"Nilai Barang Yang Digadaikan         : "<<Y[n].barang_gadai.nilai_barang<<endl;
        cout<<"Jumlah Pinjaman                      : "<<Y[n].barang_gadai.jumlah_pinjaman<<endl;
        cout<<"Sisa Angsuran                        : "<<Y[n].barang_gadai.sisa_angsuran<<endl;
        cout<<"Cicilan                              : "<<Y[n].barang_gadai.cicilan<<endl;
        cout<<"Lama Cicilan                         : "<<Y[n].barang_gadai.lama_cicilan<<" Bulan"<<endl;
		}
}

void filtering_lamacil(larik_nasabah &Y){
    int pilihan;
    string tamp_lamacil;
    int ren_awal, ren_akhir;
    bool ada=false;
    cout<<"Filtering Berdasarkan Lama Cicilan"<<endl; 
    cout<<"1. 1-3 Bulan\n"; 
    cout<<"2. 4-6 Bulan\n"; 
    cout<<"3. 7-12 Bulan\n";
    cout<<"4. 13-24 Bulan\n";
    cout<<"5. 25-36 Bulan\n";
    cout<<"Pilih Layanan (1-5) : ";
    cin>>pilihan;
    switch (pilihan){
            case 1 : tamp_lamacil = "1-3 Bulan";
                     ren_awal =1;
                     ren_akhir=3;
            break;
            case 2 : tamp_lamacil = "4-6 Bulan";
                     ren_awal =4;
                     ren_akhir=6;
            break;
            case 3 : tamp_lamacil = "7-12 Bulan";
                     ren_awal =7;
                     ren_akhir=12;
            break;
            case 4 : tamp_lamacil = "13-24 Bulan";
                     ren_awal =13;
                     ren_akhir=24;
            break;
            case 5 : tamp_lamacil = "25-36 Bulan";
                     ren_awal =25;
                     ren_akhir=36;
            break;
            default:
            break;
    }
    cout << "================================ Data Detail Nasabah Pegadaian Berdasarkan Jenis Barang ==============================" <<endl;
    cout << "Jenis Barang : " << tamp_lamacil <<endl;
    cout << "======================================================================================================================" <<endl;    
    cout << "No. Kode Nasabah ID Pengenal Nasabah          Nama       Nama Barang   Cicilan   Sisa Cicilan  Sisa Total Pembayaran  " <<endl;
    cout << "======================================================================================================================" <<endl;
    for (int i=1 ; i<=n ; i++){
        if(Y[i].barang_gadai.lama_cicilan >= ren_awal && Y[i].barang_gadai.lama_cicilan <= ren_akhir ){
            ada=true;
            cout<<setw(3)<<i<<setw(10)<<"P-"<<Y[i].kode_nasabah<<setw(20)<<Y[i].nomor_id<<setw(14)<<Y[i].nama<<setw(18)<<Y[i].barang_gadai.nama_barang<<setw(10)<<Y[i].barang_gadai.cicilan<<setw(9)<<Y[i].barang_gadai.lama_cicilan<<" Bulan"<<setw(23)<<Y[i].barang_gadai.sisa_angsuran<<endl;
        }
    }
    if(ada=false){
        cout<<"Rentang Lama Cicilan tidak ditemukan"<<endl;
    }
}

void sorting_ascending(larik_nasabah &Y){
    data_nasabah dummy;
	for(int i=1;i<=n;i++) nasabah1[i]=Y[i];
	for(int i=1;i<=n;i++){
        for(int j=1;j<=(n-i);j++){
            if(nasabah1[j].barang_gadai.sisa_angsuran > nasabah1[j+1].barang_gadai.sisa_angsuran){
                dummy=nasabah1[j];
                nasabah1[j]=nasabah1[j+1];
                nasabah1[j+1]=dummy;
            }
        }
    }
    cout<<"Data sebelum diurutkan berdasarkan sisa jumlah cicilan :"<<endl;
    cetak_nasabah(nasabah);
    cout<<"Data sesudah diurutkan berdasarkan sisa jumlah cicilan :"<<endl;
    cetak_nasabah(nasabah1);
}

void sorting_descending(larik_nasabah &Y){
    data_nasabah dummy;
	for(int i=1;i<=n;i++) nasabah1[i]=Y[i];
	for(int i=1;i<=n;i++){
        for(int j=1;j<=(n-i);j++){
            if(nasabah1[j].barang_gadai.sisa_angsuran < nasabah1[j+1].barang_gadai.sisa_angsuran){
                dummy=nasabah1[j];
                nasabah1[j]=nasabah1[j+1];
                nasabah1[j+1]=dummy;
            }
        }
    }
    cout<<"Data sebelum diurutkan berdasarkan sisa jumlah cicilan :"<<endl;
    cetak_nasabah(nasabah);
    cout<<"Data sesudah diurutkan berdasarkan sisa jumlah cicilan :"<<endl;
    cetak_nasabah(nasabah1);
}


int main () {
	int pilih=0;
    int layanan=0;
    int filtering=0;
    int sorting=0;
    do{
    system("cls");
     cout<<"Pilih Menu Layanan Pegadaian"<<endl; 
     cout<<"1. Informasi antrian di Pegadaian saat ini\n"; 
     cout<<"2. Masuk Antrian Nasabah\n"; 
     cout<<"3. Layanan Nasabah\n"; 
     cout<<"4. Cetak Nasabah Aktif \n";
     cout<<"5. Searching Data Nasabah \n";
     cout<<"6. Filtering Nasabah Aktif \n";
     cout<<"7. Sorting Berdasarkan Nominal Harga Gadai\n";
     cout<<"8. Rekapitulasi Nasabah\n";
     cout<<"0. Selesai\n";
     cout<<"Pilih menu :";cin>>pilih;
     switch (pilih){
        case 1: if (is_Empty(antri))cout<<"Tumpukan formulir kosong\n";
                else PrintQ(antri);
                break;
        case 2: if (is_full(antri))cout<<"tumpukan formulir sudah penuh\n";
                else PushQ(antri);
                break;
        case 3: 
                do{ 
                    cout<<"Menu Layanan\n";
                    cout<<"1. Gadai Barang\n";
                    cout<<"2. Bayar Angsuran\n";
                    cout<<"0. Keluar\n";
                    cout<<"Pilih Layanan (1-2) : ";
                    cin>>layanan;
                    switch (layanan){
                        case 1 :
                            if (is_Empty(antri))cout<<"tumpukan formulir kosong\n";
                            else Gadai_barang(antri,nasabah,rekap);
                            break;
                        case 2 :
                            if (is_Empty(antri))cout<<"tumpukan formulir kosong\n";
                            else bayar_angsuran(antri,nasabah,rekap);
                            break;
                        case 0 : out=true; hapus_atrian (antri);
                        break;                    
                        default: cout<<"salah pilih menu\n";
                    }
                }while(out!=true);
                break;
        case 4: cetak_nasabah(nasabah);
                break;
        case 5: searching_nasabah(nasabah);
                break;
        case 6: cout<<"Menu Filtering\n";
                cout<<"1. Berdasarkan Jenis Barang\n";
                cout<<"2. Berdasarkan Lama Cicilan yang tersisa\n";
                cout<<"Pilih Layanan (1-2) : ";
                cin>>filtering;
                switch (filtering){
                    case 1 :
                        if (is_Empty(antri))cout<<"tumpukan formulir kosong\n";
                        else filtering_jenbarang(nasabah);
                        break;
                    case 2 :
                        if (is_Empty(antri))cout<<"tumpukan formulir kosong\n";
                        else filtering_lamacil(nasabah);
                        break;
                    default: cout<<"salah pilih menu\n";
                }
                break;
        case 7: cout<<"Menu Sorting\n";
                cout<<"1. Ascending (Terkecil-Terbesar)\n";
                cout<<"2. Descending (Terbesar-Terkecil)\n";
                cout<<"Pilih Layanan (1-2) : ";
                cin>>sorting;
                switch (sorting){
                    case 1 :
                        if (is_Empty(antri))cout<<"tumpukan formulir kosong\n";
                        else sorting_ascending(nasabah);
                        break;
                    case 2 :
                        if (is_Empty(antri))cout<<"tumpukan formulir kosong\n";
                        else sorting_descending(nasabah);
                        break;
                    default:
                        break;
                }
                break;
        case 8: cetak_rekap(rekap);
                break;
       case 0: cout<<"Terimakasih\n";break;
       default: cout<<"salah pilih menu\n";
        }
        system("pause");
    }while(pilih!=0);
}
