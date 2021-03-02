/*
Nama : Reyhan Naufal Hayyan
NIM : 185150307111017
Kelas : Algoritma dan Struktur Data TKOM - B 
Tugas : Worksheet 1
Origin : https://github.com/rheyhannh/algorithm-data-structure
*/

#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

struct ListNode {
    string username;
    string nama;
    ListNode *next;
};

struct SingleLinkedList{;
    // Fungsi Inisialiasi, Destroy dan Exit
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
        ListNode *temp;
        temp = new ListNode;
        temp->username = username;
        temp->nama = nama;
        if(is_empty()){
            tail = temp;
            tail->next = NULL;
        }
        else {
            temp->next = head;
        }
        head = temp;
        size++;
    }

    void add_last(string username, string nama){
        ListNode *temp;
        temp = new ListNode;
        temp->username = username;
        temp->nama = nama;
        temp->next = NULL;
        if(is_empty()){
            head = temp;
        }
        else {
            tail->next = temp;
        }
        tail = temp;
        size++;
    }

    // Fungsi Penyisipan
    void insert_after(string username_after, string username, string nama){
        ListNode *temp;
        ListNode *before= head; 
        temp = new ListNode;
        temp->username = username;
        temp->nama = nama;
        // Mencegah bug jika linked list masih kosong
        if(is_empty()){
            cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Pertama karena Linked List Kosong" << endl;
            add_first(username, nama);
        }
        else{
            while(before->username != username_after || before == NULL){
                before = before->next;
            }
            if(before == tail){
                cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Akhir karena Username '" << username_after << "'" << " merupakan Data Terakhir" << endl;
                add_last(username, nama);
            }
            else{
                temp->next = before->next;
                before->next = temp;
                cout << "\nBerhasil menambahkan Data dengan Username '" << temp->username << "'" << " setelah Data '" << before->username << "'" << endl;
                size++;     
            }
        }  
    }

    void insert_before(string username_before, string username, string nama){
        ListNode *temp;
        ListNode *before= head; 
        temp = new ListNode;
        temp->username = username;
        temp->nama = nama;
        // Mencegah bug jika linked list masih kosong
        if(is_empty()){
            cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Pertama karena Linked List Kosong" << endl;
            add_first(username, nama);
        }
        else{
            if(before->username == username_before){
                cout << "\nOtomatis memasukkan Data dengan Username '" << temp->username << "'" << " Pada Urutan Pertama karena Username '" << username_before << "'" << " merupakan Data Pertama" << endl;
                add_first(username, nama);
            }
            else{
                while(before->next->username != username_before){
                    before = before->next;
                }
                temp->next = before->next;
                before->next = temp;
                cout << "\nBerhasil menambahkan Data dengan Username '" << temp->username << "'" << " sebelum Data '" << before->username << "'" << endl;
                size++;  
            }
        } 
    }

    // Fungsi Penghapusan
    void remove_by_index(int index){
        ListNode *temp = head;
        ListNode *before = head;
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
                temp = temp->next;
                counter ++;
            }
            while(before->next != temp && counter != 0){
                before = before->next;
            }
            if(temp == head){
                remove_first();
            }
            else if(temp == tail){
                remove_last();
            }
            else{
                temp = before->next;
                before->next = before->next->next;
                temp->next = NULL;
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                size--;
                print_all();  
            }
        }
    }

    void remove_by_username(string username){
        ListNode *temp = head;
        ListNode *before = head;
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        else if((temp == head) && (temp->username == username)){
            remove_first();  
        }
        else{
            while(before->next->username != username){
                before = before->next;
            }
            if(before->next == tail){
                remove_last();
            }
            else if(before->next->username == username){
                temp = before->next;
                before->next = before->next->next;
                temp->next = NULL;
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                size--;
                print_all();  
            }
            else{
                cout << "\nData Tidak Ditemukan" << endl;
            }
        }
    }

    void remove_first(){
        ListNode *temp = head;
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        else{
            head = temp->next;
            temp->next = NULL;
            cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
            delete temp;
            size--;
        }
    }

    void remove_last(){
        ListNode *before = head;
        ListNode *temp = head->next;
        string reference = head->username;
        if(is_empty()){
            cout << "\nLinked List Kosong" << endl;
        }
        else{
            while(temp->next != NULL){
                temp = temp->next;
                before = before->next;
            }
            if(before->username == head->username){
                head = tail = before;
                before->next = NULL;
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                size--;
            }
            else{
                tail = before;
                cout << "\nBerhasil menghapus Data dengan Username '" << temp->username << "'" << endl;
                delete temp;
                before->next = NULL;
                size--;
            }
        }
    }

    // Fungsi Cetak
    void print_all(){
       if(is_empty()){
           cout << "\nLinked List Kosong" << endl;
       }
       else{
            cout << "\n______Single Linked List [Data User Forum]______ " << endl;
            cout << "______________[TOTAL DATA = " << get_size() << "]______________" << endl;
            ListNode *temp = head;
            int index = 0;
            while(temp != NULL){
                cout << "[" << index << "]" << " Username : " << temp->username << " | Nama : " <<temp->nama << endl;
                temp = temp->next;
                index++;
            }
       }
    }

    void print_by_index(int index){
        ListNode *temp = head;
        int counter = 0;
        // Mencegah bug saat linked list masih kosong
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
    SingleLinkedList starts;
    starts.init();
}

