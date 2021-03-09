/*
Nama : Reyhan Naufal Hayyan
NIM : 185150307111017
Kelas : Algoritma dan Struktur Data TKOM - B 
Tugas : Worksheet 2
Origin : https://github.com/rheyhannh/algorithm-data-structure
*/

#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

struct ListNode {
    string username;
    string nama;
    ListNode *next, *prev;
};

struct DoubleLinkedList{;
    // Fungsi Inisialiasi dan Destroy
    ListNode *head, *tail;
    int size = 0;

    void init(){
        make_empty();
    }

    void destroy(){
        make_empty();
    }

    // Fungsi Penambahan
    void add_first(string username, string nama){
        ListNode *temp = new ListNode;
        temp->username = username;
        temp->nama = nama;
        temp->next = NULL;
        temp->prev = NULL;
        if(is_empty()){
            tail = temp;
        }
        else{
            temp->next = head;
            head->prev = temp;
        }
        head = temp;
        size++;
    }

    void add_last(string username, string nama){
        ListNode *temp = new ListNode;
        temp->username = username;
        temp->nama = nama;
        temp->next = NULL;
        temp->prev = NULL;
        if(is_empty()){
            head = temp;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
        }
        tail = temp;
        size++;
    }

    // Fungsi Penyisipan
    void insert_after(string username_after, string username, string nama){
        ListNode *temp = new ListNode;
        ListNode *helper = head;
        temp->username = username;
        temp->nama = nama;
        temp->next = NULL;
        temp->prev = NULL;
        if(is_empty()){
            cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Pertama karena Linked List Kosong" << endl;
            add_first(username, nama);
        }
        else{
            while(helper != NULL){
                if(helper->username == username_after){
                    if(helper == tail){
                        cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Akhir karena Username '" << username_after << "'" << " merupakan Data Terakhir" << endl;
                        add_last(username, nama);
                    }
                    else{
                        cout << "\nBerhasil menambahkan Data dengan Username '" << temp->username << "'" << " setelah Data '" << username_after << "'" << endl;
                        temp->prev = helper;
                        temp->next = helper->next;
                        helper->next->prev = temp;
                        helper->next = temp;
                        size++;
                    }
                }
                helper = helper->next;
            }
        }
    }

    void insert_before(string username_before, string username, string nama){
        ListNode *temp = new ListNode;
        ListNode *helper = head;
        temp->username = username;
        temp->nama = nama;
        temp->next = NULL;
        temp->prev = NULL;
        if(is_empty()){
            cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Pertama karena Linked List Kosong" << endl;
            add_first(username, nama);
        }
        else{
            if(helper->username == username_before){
                cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Pertama karena Username '" << username_before << "'" << " merupakan Data Pertama" << endl;
                add_first(username, nama);
            }
            else{
                while(helper != NULL){
                    if(helper->username == username_before){
                        temp->prev = helper->prev;
                        temp->next = helper;
                        helper->prev->next = temp;
                        helper->prev = temp;
                        size++;
                        break;
                    }
                    helper = helper->next;
                }
            }
        }
    }

    // Fungsi Penghapusan
    void remove_first(){
        ListNode *temp = head;
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        else{
            if(head == tail){
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                head = tail = NULL;
            }
            else{
                head->next->prev = NULL;
                head = temp->next;
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
            }
            size--;
        }
    }

    void remove_last(){
        ListNode *temp = tail;
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        else{
            if(tail == head){
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                head = tail = NULL;
            }
            else{
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                tail->prev->next = NULL;
                tail = temp->prev;
                delete temp;
            }
            size--;
        }
    }

    void remove_by_index(int index){
        ListNode *temp = head;
        ListNode *prev = NULL;
        ListNode *after;
        int counter = 0;
        // Mencegah bug saat linked list masih kosong
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        // Mencegah bug saat index lebih besar dari jumlah data atau index bernilai negatif
        else if(index > size - 1 || index < 0){
            cout << "\nIndex yang ingin diHapus tidak Valid atau tidak ada." << endl;
            cout << "Perlu diIngat bahwa Data Linked List berjumlah " << get_size() << " dan Index dimulai dari 0 !" << endl;
        }
        else{
            while(counter != index){
                prev = temp;
                temp = temp->next;
                after = temp->next;
                counter ++;
            }
            if(temp == head){
                remove_first();
            }
            else if(temp == tail){
                remove_last();
            }
            else{
                prev->next = temp->next;
                after->prev = temp->prev;
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                size--;
            }
        }
    }

    void remove_by_username(string username){
        int toogle = 0;
        ListNode *temp = head;
        ListNode *prev = NULL;
        ListNode *after;
        while(temp != NULL || toogle == 0){
            // kondisi while dengan OR toogle agar jika linked sudah dihapus tidak perlu mencari sampai akhir
            if(temp->username == username){
                if(prev == NULL){
                    remove_first();
                    break;
                }
                else if(temp == tail){
                    remove_last();
                    break;
                }
                else{
                    prev->next = temp->next;
                    after->prev = temp->prev;
                    cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                    delete temp;
                    size--;
                    break;
                }
            toogle = 1;
            }
            else if(temp->next == NULL){
                cout << "\nUsername '" << username << "'" << " tidak dapat ditemukkan, proses penghapusan gagal!" << endl;
                break;
            }
        prev = temp;
        temp = temp->next;
        after = temp->next;
        }
    }

    // Fungsi Cetak
    // Menggunakan void karena tidak ada return.
    void get(int index){
        ListNode *temp = head;
        int counter = 0;
        cout << "\nMencari Data pada index ke " << index << " dengan fungsi GET" << endl;
        if(is_empty()){
            cout << "\nLinked List Masih Kosong" << endl;
        }
        else if(index > size - 1 || index < 0){
            // Saat Index yang diminta sesuai dengan data yang tersedia, dan saat Index yang diminta bernilai negatif
            cout << "\nIndex yang dimasukkan tidak Valid." << endl;
            cout << "Data pada linked hanya berjumlah " << get_size() << " dan index dimulai dari 0!" << endl;
        }
        else{
            while(temp != NULL){
                if(counter == index){
                    cout << "\nBerikut ini adalah data pada index ke-" << index << endl;
                    cout << "[" << index << "]" << " Username : " << temp->username << " | Nama : " <<temp->nama << endl;
                }
                temp = temp->next;
                counter++;      
            }
        }
    }

    int index_Of(string x){
        ListNode *temp = head;
        int counter = 0;
        cout << "\nMencari Username '" << x << "'" << " dengan index_Of" << endl;
        if(is_empty()){
            cout << "\nLinked List Masih Kosong" << endl;
        }
        else{
            while(temp != NULL){
                if(temp->username == x){
                    cout << "\nUsername '" << x << "'" << " terletak pada index ke-" << counter << endl;
                    return counter; // return nilai index saat ditemukkan
                }
                temp = temp->next;
                counter++;      
            }
        }
    cout << "\nUsername '" << x << "'" << " tidak dapat ditemukkan" << endl;
    return -1; // return -1 saat tidak ditemukkan
    }

    
    void print_to_tail(){
        ListNode *temp = head;
        // Cek Kosong/Tidak
        if(is_empty()){
            cout << "\nLinked List Masih Kosong" << endl;
        }
        else{
            cout << "\n______Single Linked List [Data User Forum]______ " << endl;
            cout << "______________[TOTAL DATA = " << get_size() << "]______________" << endl;
            int index = 0;
            while(temp != NULL){
                cout << "[" << index << "]" << " Username : " << temp->username << " | Nama : " <<temp->nama << endl;
                temp = temp->next;
                index++;
            }           
        }
    }

    void print_to_head(){
        ListNode *temp = tail;
        // Cek Kosong/Tidak
        if(is_empty()){
            cout << "\nLinked List Masih Kosong" << endl;
        }
        else{
            cout << "\n______Single Linked List [Data User Forum]______ " << endl;
            cout << "______________[TOTAL DATA = " << get_size() << "]______________" << endl;
            int index = 0;
            while(temp != NULL){
                cout << "[" << index << "]" << " Username : " << temp->username << " | Nama : " <<temp->nama << endl;
                temp = temp->prev;
                index++;
            }
        }
    }

    void print_by_index(int index){
        ListNode *temp = head;
        int counter = 0;
        // Cek Kosong/Tidak
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        // Mencegah bug saat index lebih besar dari jumlah data atau index bernilai negatif
        else if(index > size - 1 || index < 0){
            cout << "\nIndex yang diminta tidak Valid atau tidak ada." << endl;
            cout << "Perlu diIngat bahwa Data Linked List berjumlah " << get_size() << " dan Index dimulai dari 0 !" << endl;
        }
        else{
            while(counter != index){
                temp = temp->next;
                counter ++;
            }
            cout << "\n[" << index << "]" << " Username : " << temp->username << " | Nama : " <<temp->nama << endl;
        }
    }

    // Fungsi Operasi
    int get_size(){
        return size;
    }

    bool is_empty(){
        return size == 0;
    } 

    void make_empty(){
        // Membuat Kosong dari Depan / Head
        ListNode *temp = head;
        for(int x; size != 0; x++){
            delete temp;
            temp = temp->next;
            size--;
        }
        head = tail = NULL;
    }
};

int main(){
    DoubleLinkedList starts;
    starts.init();
    starts.destroy();
}

