#include <bits/stdc++.h>

using namespace std;

struct Node{
	string name;
	string status; 
	int age;
	int bp; //bp = blood pressure
	Node *next, *prev;
	
};

struct QueueLinkedList{
    int pasienLansia = 0;
    int pasienBukanLansia = 0;
    int totalPasien = pasienLansia + pasienBukanLansia;
	int size = 0;
	Node *front, *front1, *rear, *rear1, *head, *head1;

	void init(){
		front = front1 = rear = rear1 = head = head1 = NULL;
	}

	bool is_empty_RuangAntre(){
		return (front == NULL && rear == NULL);
	}
	
	bool is_empty_RuangTunggu(){
		return (front1 == NULL && rear1 == NULL);
	}

    bool is_full_RuangAntre(){
        return totalPasien >= size;
    }

    bool is_full_lansia_RuangAntre(){
        return pasienLansia >= size;
    }

	void make_empty(){
		Node *p = front;
        for(int x; size != 0; x++){
            delete p;
            p = p->next;
            size--;
        }
        front = rear = NULL;
	}

	void set_size_RuangAntre(int x){
		size = x;
	}
	
	int get_size_RuangAntre(){
		return size;
	}

    void pasien_Increment(string status){
        if(status == "LANSIA"){
            pasienLansia++;
        }
        else{
            pasienBukanLansia++;
        }
        totalPasien = pasienLansia + pasienBukanLansia;
    }

    void pasien_Decrement(string status){
        if(status == "LANSIA"){
            pasienLansia--;
        }
        else{
            pasienBukanLansia--;
        }
        totalPasien = pasienLansia + pasienBukanLansia;
    }

    int get_totalPasien(){
        return totalPasien;
    }

    int get_PasienLansia(){
        return pasienLansia;
    }

    int get_PasienBukanLansia(){
        return pasienBukanLansia;
    }

	void enqueue_RuangAntre(string nama, int umur, int tensi, string status, int priority){
		Node *tmp = new Node;
		Node *helper = rear;
        Node *helper2 = front;
		tmp->name = nama;
		tmp->age = umur;
		tmp->bp = tensi;
		tmp->status = status;
		tmp->next = NULL;
		tmp->prev = NULL;
		if(is_empty_RuangAntre()){
			front = tmp;
			rear = tmp;
            pasien_Increment(status);
		}
        else if(is_full_RuangAntre()){
            if(is_full_lansia_RuangAntre()){
                if(priority == 1){
                    pasien_Increment(status);
                    enqueue_RuangTunggu(nama, umur, tensi, status, 1);
                }
                else{
                    pasien_Increment(status);
                    enqueue_RuangTunggu(nama, umur, tensi, status, 0);
                }
            }
            else{
                if(priority == 1){
                    if(helper2->status == "BUKAN_LANSIA"){
                        tmp->next = front;
                        tmp->prev = helper2;
                        front->prev = tmp;
                        front = tmp;
                        helper2->next = tmp;
                        pasien_Increment(status);
                        enqueue_RuangTunggu(helper->name, helper->age, helper->bp, helper->status, 0);
                        // Ganti Belakang
                        helper->next->prev = NULL;
                        rear = helper->next;
                        rear->prev == NULL;
                        delete helper;
                    }
                    else{
                        while(helper2 != NULL){
                            if(helper2->status == "BUKAN_LANSIA" && helper2 != rear){
                                tmp->next = helper2->next;
                                helper2->next->prev = tmp;
                                helper2->next = tmp;
                                tmp->prev = helper2;
                                pasien_Increment(status);
                                enqueue_RuangTunggu(helper->name, helper->age, helper->bp, helper->status, 0);
                                // Ganti Belakang
                                helper->next->prev = NULL;
                                rear = helper->next;
                                delete helper;
                                break;
                            }
                            else if(helper2->status == "BUKAN_LANSIA" && helper2 == rear){
                                tmp->next = helper2->next;
                                helper2->next->prev = tmp;
                                helper2->next = tmp;
                                pasien_Increment(status);
                                enqueue_RuangTunggu(helper->name, helper->age, helper->bp, helper->status, 0);
                                rear = tmp;
                                rear->prev = NULL;
                                delete helper;
                                break;
                            }
                            helper2 = helper2->prev;
                        }
                    }
                }
                else{
                    pasien_Increment(status);
                    enqueue_RuangTunggu(nama, umur, tensi, status, 0);
                }
            }
        }
        else if(priority == 1){
            if(helper2->status == "BUKAN_LANSIA"){
                helper2->next = tmp;
                tmp->prev = helper2;
                front = tmp;
                pasien_Increment(status);
            }
            else{
                while(helper2 != NULL){
                    if(helper2->status == "BUKAN_LANSIA"){
                        tmp->next = helper2->next;
                        helper2->next->prev = tmp;
                        helper2->next = tmp;
                        tmp->prev = helper2;
                        pasien_Increment(status);
                        break;
                    }
                    else if(helper2->prev == NULL){
                        tmp->next = helper2;
                        helper2->prev = tmp;
                        rear = tmp;
                        pasien_Increment(status);
                        break;
                    }
                    helper2 = helper2->prev;
                }
            }
        }
        else{
            tmp->next = rear;
            rear->prev = tmp;
            rear = tmp;
            pasien_Increment(status);
        }
	}        

	void enqueue_RuangTunggu(string nama, int umur, int tensi, string status, int priority){
        Node *tmp = new Node;
		Node *helper = front1;
		tmp->name = nama;
		tmp->age = umur;
		tmp->bp = tensi;
		tmp->status = status;
		tmp->next = NULL;
		tmp->prev = NULL;
        if(is_empty_RuangTunggu()){
            front1 = tmp;
            rear1 = tmp;
        }
        else if(priority == 1){
            if(helper->status == "BUKAN_LANSIA"){
                helper->next = tmp;
                tmp->prev = helper;
                front1 = tmp;
            }
            else{
                while(helper != NULL){
                    if(helper->status == "BUKAN_LANSIA"){
                        tmp->next = helper->next;
                        helper->next->prev = tmp;
                        helper->next = tmp;
                        tmp->prev = helper;
                        break;
                    }
                    else if(helper->prev == NULL){
                        tmp->next = helper;
                        helper->prev = tmp;
                        rear1 = tmp;
                        break;
                    }
                    helper = helper->prev;
                }
            }
        }
        else{
            tmp->next = rear1;
            rear1->prev = tmp;
            rear1 = tmp;
        }
	}

    void dequeue(){
        // isi
    }
	void skip(){
		// isi
	}

	void print_Antre(string nama, string status){
		cout << "ANTRE " << nama << " " << status;
		if(totalPasien > size){
			cout << " TUNGGU " << nama;
		}
		cout << endl;
	}

    void print_Tolak(string nama, string status){
        cout << "TOLAK " << nama << " " << status << " TENSI_TIDAKBOLEH_DIVAKSIN" << endl;
    }

	void print_DaftarAntre(){
		Node *tmp = front;
		cout << "DAFTAR_ANTRE ";
		while(tmp != NULL){
			cout << tmp->name << "^" << tmp->status << "^" << tmp->bp << " ";
			tmp=tmp->prev;
		}
		cout<<endl;
 	}

 	void print_DaftarTunggu(){
		Node *tmp = front1;
		cout << "DAFTAR_TUNGGU ";
		while(tmp != NULL){
			cout << tmp->name << "^" << tmp->status << "^" << tmp->bp << " ";
			tmp=tmp->prev;
		}
		cout<<endl;
 	}

    void InputOutputHandler(string inputs){
        int xyz = 0; // Variabel untuk loop memasukan setiap kata pada input ke setiap array (dipisah)
        int USIA; // Variabel untuk dipass melalui parameter fungsi
        int TENSI; // Variabel untuk dipass melalui parameter fungsi
        int N; // Variabel untuk dipass melalui parameter fungsi
        int priority;
		string inputPerKata[4]; // Array yang menyimpan setiap kata (contoh -> array[0]: BARU, array[1]: Yana, dan seterusnya)
        for(int zyx = 0; zyx < 4; zyx++){ // Inisialisasi array default berisi "Kosong"
            	inputPerKata[zyx] = "KOSONG";
        }
        string NAMA_PENERIMA_VAKSIN; // Variabel untuk dipass melalui parameter fungsi
        string PERINTAH; // Variabel untuk cek perintah (contoh: BARU, UKURAN, dan lain lain)
        string status;
		// Simpan setiap kata pada input ke Array.
        istringstream iss(inputs);
        string kata;
        while(iss >> kata) { // Mengisi input awal user ke array setiap kata
            	inputPerKata[xyz] = kata;
            	xyz++;
        }
        PERINTAH = inputPerKata[0]; // Mengisi perintah dari nilai elemen pertama inputPerKata
        // Seleksi kondisi input tertentu.
        if(PERINTAH == "BARU"){
            	if(inputPerKata[1] == "KOSONG" || inputPerKata[2] == "KOSONG" || inputPerKata[3] == "KOSONG"){
                	// Exit saat input BARU dimasukkan tanpa diikuti nama pasien/usia/tensi
                	exit(0);
            	}
            	else{
                	NAMA_PENERIMA_VAKSIN = inputPerKata[1];
                	USIA = stoi(inputPerKata[2]);
                	TENSI = stoi(inputPerKata[3]);
                	// cout << "Masukin " << NAMA_PENERIMA_VAKSIN << " " << USIA << " " << TENSI << endl; // Contoh output aja
                	// Perlu Pengecekan Tensi dan Umur lalu Panggil Fungsi Enqueue(NAMA_PENERIMA_VAKSIN, USIA, TENSI)
					if(USIA>=60){
						status = "LANSIA";
						priority = 1;
					} else{
						status = "BUKAN_LANSIA";
						priority = 0;
					}	
					if (TENSI < 180){
						enqueue_RuangAntre(NAMA_PENERIMA_VAKSIN, USIA, TENSI, status, priority);
						print_Antre(NAMA_PENERIMA_VAKSIN, status);
					} else {
						print_Tolak(NAMA_PENERIMA_VAKSIN, status);			
					}
            	}
        }

        else if(PERINTAH == "UKURAN"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input UKURAN dimasukkan tanpa diikuti variabel ukuran (N)
                	exit(0);
            	}
            	else{
                	N = stoi(inputPerKata[1]); // Casting String ke Integer (Butuh C++ Versi 11 atau Lebih)
                	cout << "UKURAN MENJADI " << N << endl; // Contoh output aja
                	// Panggil Fungsi Pengganti Ukuran Ruang Antre Sebesar N (Parameter : N)
            	}
        }
        else if(PERINTAH == "SELESAI"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input SELESAI dimasukkan tanpa diikuti variabel jumlah pasien selesai (N)
                	exit(0);
            	}
            	else{
                	N = stoi(inputPerKata[1]); // Casting String ke Integer (Butuh C++ Versi 11 atau Lebih)
                	cout << "SELESAI " << N << " ORANG" << endl; // Contoh output aja
                	// Panggil Fungsi Untuk Menghapus (Selesai Vaksin) N Orang Dari Antrian (Parameter : N)
            	}
        }
        else if(PERINTAH == "SELESAI_NAMA"){
            	if(inputPerKata[1] == "KOSONG"){
                // Exit saat input SELESAI_NAMA dimasukkan tanpa diikuti nama pasien (NAMA_PENERIMA_VAKSIN)
                exit(0);
            	}
            	else{
                	NAMA_PENERIMA_VAKSIN = inputPerKata[1];
                	cout << "SELESAI " << NAMA_PENERIMA_VAKSIN << endl; // Contoh output aja
                	// Panggil Fungsi Untuk Menghapus (Selesai Vaksin) dengan Nama Orang Dari Antrian (Parameter : NAMA_PENERIMA_VAKSIN)
            	}
        }
        else if(PERINTAH == "SKIP"){
            	if(inputPerKata[1] == "KOSONG"){
                	// Exit saat input SELESAI_NAMA dimasukkan tanpa diikuti nama pasien (NAMA_PENERIMA_VAKSIN)
                	exit(0);
            	}
            	else{
                	NAMA_PENERIMA_VAKSIN = inputPerKata[1];
                	cout << "SKIP " << NAMA_PENERIMA_VAKSIN << endl; // Contoh output aja
                	// Panggil Fungsi Untuk Memindahkan Pasien Berdasarkan Nama dari Ruang Antre ke Ruang Tunggu (Parameter : NAMA_PENERIMA_VAKSIN)
            	}
		}
		else if(PERINTAH == "STATUS"){
            	// cout << "STATUS ANTRE DAN TUNGGU" << endl; // Contoh output aja
            	// Panggil Fungsi Untuk Mencetak/Melihat Pasien di Ruang Antre dan Ruang Tunggu
				print_DaftarAntre();
				print_DaftarTunggu();
                // cout << "\nPasien Lansia : " << get_PasienLansia();
                // cout << "Pasien Non Lansia : " << get_PasienBukanLansia() << endl;
                // cout << "Total Pasien : " << get_totalPasien() << endl;
                // cout << endl;
        }
        else{
            	// Exit Saat perintah tidak ada yang cocok
            	exit(0);
        }
    }
};

int main(int argc, char** argv) {
	QueueLinkedList qll;
	int ukuran;
	// Perlu Inisiasilasi Awal Ukuran Ruang Antre Variabel (M) dengan Batas 1 =< M =< 1000
	// cin >> ukuran;
	// cin.ignore();
	qll.set_size_RuangAntre(10);
	qll.init();
	int x = 0;
    	string inputs; // Variabel yang dimasukan user pertama kali (contoh: BARU Yana 55 22)
    	string inputFix[10000]; // Menyimpan input pada Array agar dapat input secara banyak lalu output (testcase sampai 10000)
    	while(getline(cin,inputs)){
        	inputFix[x] = inputs;
        	x++;
        	if(inputs.empty()){
            	break;
        	}
    	}
    	for(int xy = 0; xy < x; xy++){
        	qll.InputOutputHandler(inputFix[xy]);
    	}
        // Perlu Penghapusan Object/Instance atau Membebaskan Memori
	return 0;
}
