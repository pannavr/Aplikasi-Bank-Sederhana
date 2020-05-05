#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include<time.h>

int pilihan,Norekeningm,pilihanhapus, saldoo;
char nama2[30],alamat2[20],hp2[20],id[16],sandi[16];
void password(char *);
void print();
void inputData();
void buatDatabase();
void menuUtama();
void hapusData();
void popHead();
void popMid(int age);
void hapusSatu();
void pushHead(int Norekening, int saldo, char name[], char Alamat[], char hp[]);
void popAll();
void welcome ();

void TambahSaldoNorekening(int Norekening);
void tambahsaldo();

void cariDataNorekening(int Norekening);
void cariDatanama(char nama[]);

void editData();
void editDataNorekening(int Norekening);
void editDatanama(char name[]);
void swap(struct human *a, human *b);

void urutDataNorekening(struct human *head);
void urutDatanama(struct human *head);
void urutDatahp(struct human *head);
void urutDataAlamat(struct human *head);
void urutData();

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(unsigned short color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void SYSTIME()
{
    int a;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

        printf ( "%s", asctime (timeinfo) );
}

struct human{
	int Norekening;
    int saldo;
	char name[30];
	char Alamat[30];
	char hp[30];
	human *next;
}*head, *tail, *current;

void pushTail(int Norekening, int saldo, char name[], char Alamat[], char hp []){
	current = (human*)malloc(sizeof(struct human));
	current->Norekening = Norekening;
	current->saldo = saldo;
	strcpy(current->name, name);
	strcpy(current->Alamat, Alamat);
	strcpy(current->hp, hp);

	if(head == NULL){
		head = tail = current;
	}
	else{
		tail->next = current;
		tail = current;
	}
	tail->next = NULL;
}

void popHead(){
    int i;
	current=head;
	if(head==NULL){
		printf("No data");
	}else if(head==tail){
		head=tail=NULL;
		free(current);
	}else{
		head=head->next;
		free(current);
	}
}

void popTail(){
	if(head==NULL){
		printf("No data");
	}else if(head==tail){
		head=tail=NULL;
		free(current);
	}else{
		human *temp=head;
		while(temp->next!=tail){
			temp=temp->next;
		}
		current=tail;
		tail=temp;
		free(current);
		tail->next=NULL;
	}
}

void popMidNorekening(int Norekening){
	if(head==NULL){
		printf("No data");
	}else if(head->Norekening==Norekening){
		popHead();
	}else if(tail->Norekening==Norekening){
		popTail();
	}else{
		human *temp=head;
		while(temp->next->Norekening!=Norekening && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		temp->next=temp->next->next;
		free(current);
	}
}

void popMidname(char name[]){
	if(head==NULL){
		printf("No data");
	}else if(strcmp(head->name,name)==0){
		popHead();
	}else if(strcmp(tail->name,name)==0){
		popTail();
	}else{
		human *temp=head;
		while(strcmp(temp->next->name,name)!=0 && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		temp->next=temp->next->next;
		free(current);
	}
}

void popAll(){
	while(head!=NULL){
		popHead();
	}
}

void print(){
    system("cls");
    int l = 1;
	current = head;
	 gotoxy(20, 0);
    printf(" ------------------DAFTAR DATA NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
	while(current != NULL){

printf("  \n");
		printf("\t\t\t\t Nomor \t\t:%d \n",l);
        printf("\t\t\t\t no. rekening\t:%i \n",current->Norekening);
		printf("\t\t\t\t Nama\t\t:%s \n",current->name);
		printf("\t\t\t\t Alamat\t\t:%s \n",current->Alamat);
		printf("\t\t\t\t No. HP\t\t:%s \n",current->hp);
		printf("\t\t\t\t Saldo \t\t:Rp. %i \n", current->saldo);
		current = current->next;
		l++;
	}
}

void inputData(){

        printf("\t\t\t\t\t Masukan No. rekening \t: ");
        scanf("%i",&Norekeningm);

        printf("\t\t\t\t\t Masukan Nama \t\t: ");
        scanf (" %[^\n]",&nama2);

        printf("\t\t\t\t\t Masukan Alamat \t: ");
        scanf(" %[^\n]",&alamat2);

        printf("\t\t\t\t\t No Handphone \t\t: ");
        scanf (" %[^\n]",&hp2);
        printf("\t\t\t\t\t Saldo \t\t\t: Rp. ");
        scanf(" %i",&saldoo);
        printf("\n");
        pushTail(Norekeningm,saldoo, nama2, alamat2, hp2);

        }

void buatDatabase(){
    system("cls");
    int ulang;
    gotoxy(30,0);
    printf(" --------------------INPUT DATA NASABAH-------------------");
    gotoxy(30, 1);
    printf("|__________________________________________________________|");
    gotoxy(33, 3);
    printf("Masukan Jumlah data Nasabah \t: ");
    scanf("%i",&ulang);
    while(ulang>0){
        ulang--;
        inputData();
    }
}

void hapusSatu(){
    int o,n;
    char name[30];
    system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------HAPUS DATA NASABAH------------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
        printf("1. Hapus Data Menurut No. rekening\n");
            gotoxy(35, 4);
        printf("2. Hapus Data Menurut NAMA\n");
            gotoxy(35, 5);
        printf("Masukan Pilihan\t: ");
        scanf("%i",&o);
        switch(o){
        case 1:
                    system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------HAPUS DATA NASABAH------------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
            printf("Masukan No. rekening\t: ");
            scanf("%i",&n);
            popMidNorekening(n);
              gotoxy(35, 3);
            printf("data dengan No. rekening %i telah dihapus \n\n",n);
            system("PAUSE");
        break;
        case 2:
                   system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------HAPUS DATA NASABAH------------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
            printf("Masukan NAMA\t: ");
            scanf(" %[^\n]",&name);
            popMidname(name);
               gotoxy(3, 4);
            printf("data dengan NAMA %s telah dihapus \n\n",name);
            system("PAUSE");
        break;
        }
}

void hapusData(){
    mbalikhapusdata :
    system("cls");
    gotoxy(30, 0);
    printf(" --------------------HAPUS DATA NASABAH-------------------");
    gotoxy(30, 1);
    printf("|__________________________________________________________|");
    gotoxy(50, 3);
    printf("1. Hapus Satu Data\n");
    gotoxy(50, 4);
    printf("2. Hapus semua Data\n");
    gotoxy(50, 5);
    printf("3. Hapus Data Pertama\n");
    gotoxy(50, 6);
    printf("4. Hapus Data Terakhir\n");
    gotoxy(50, 7);
    printf("5. Kembali Ke Menu\n\n");
    gotoxy(50, 8);
    printf("Masukkan pilihan : ");
    scanf("%i",&pilihanhapus);
    if (pilihanhapus == 1 || pilihanhapus ==2 || pilihanhapus == 3 || pilihanhapus ==4 || pilihanhapus == 5){
    }else{
        printf("Pilihan Yang anda Masukan Tidak ada!\n\n");
        system("PAUSE");
        goto mbalikhapusdata;
        }
    switch(pilihanhapus){
    case 1:
        hapusSatu();
    break;
    case 2:
        popAll();
        printf("Semua Data Telah Dihapus\n");
        system("PAUSE");
    break;
    case 3:
        popHead();
        printf("Data Pertama Telah Dihapus\n");
        system("PAUSE");
    break;
    case 4:
        popTail();
        printf("Data Terakhir Telah Dihapus\n");
        system("PAUSE");
    case 5:
        return;
    break;
    }
}

void editData(){
    system("cls");
    int z,x;
    char c[30];
    gotoxy(20, 0);
    printf(" ------------------UPDATE DATA NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
    printf("1. Edit Data Menurut dengan No. rekening\n");
     gotoxy(35, 4);
    printf("2. Edit Data Menurut dengan NAMA\n");
     gotoxy(35, 5);
    printf("3. Kembali Ke Menu\n\n");
     gotoxy(35, 6);
    printf("Masukan Pilihan\t: ");
    scanf("%i",&z);
    switch(z){
    case 1:
         system("@cls||clear");
           gotoxy(20, 0);
    printf(" ------------------UPDATE DATA NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(30, 3);
        printf("Masukan no. rekening Yang Ingin Diedit\t: ");
        scanf("%i",&x);
        editDataNorekening(x);
    break;
    case 2:
         system("@cls||clear");
           gotoxy(20, 0);
    printf(" ------------------UPDATE DATA NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
        printf("Masukan NAMA Yang Ingin Diedit\t: ");
        scanf(" %[^\n]",&c);
        editDatanama(c);
    break;
    case 3:
        return;
    break;
    }
}

void cariData(){
    system("cls");
    int q,w;
    char e[30];
       gotoxy(30, 0);
    printf(" -----------------MENCARI DATA NASABAH----------------");
    gotoxy(30, 1);
    printf("|______________________________________________________|");
       gotoxy(40, 3);
    printf("1. Cari Data Menurut no. rekening\n");
       gotoxy(40, 4);
    printf("2. Cari Data Menurut NAMA\n");
        gotoxy(40, 5);
    printf("3. Kembali Ke Menu\n");
        gotoxy(40, 6);
    printf("Masukan Pilihan\t: ");
    scanf("%i",&q);
    switch(q){
    case 1:
        printf("\nMasukan No. Rekening Yang Ingin Dicari\t: ");
        scanf("%i",&w);
        cariDataNorekening(w);
    break;
    case 2:
        printf("\nMasukan NAMA Yang Ingin DIcari\t: ");
        scanf(" %[^\n]",&e);
        cariDatanama(e);
    break;
    case 3:
        return;
    break;
    }
}

void cariDataNorekening(int Norekening){
    if(head==NULL){
		printf("No data");
	}else if(head->Norekening==Norekening){
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",head->Norekening);
        printf("\t\t\t\t\t\t Nama\t\t:%s \n",head->name);
        printf("\t\t\t\t\t\t Alamat\t\t:%s \n",head->Alamat);
        printf("\t\t\t\t\t\t No. HP\t\t:%s \n",head->hp);
        printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", head->saldo);
		system("PAUSE");
	}else if(tail->Norekening==Norekening){
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",tail->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",tail->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",tail->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",tail->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", tail->saldo);
		system("PAUSE");
	}else{
		human *temp=head;
		while(temp->next->Norekening!=Norekening && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",current->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",current->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",current->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",current->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", current->saldo);
		system("PAUSE");
	}}

void editDataNorekening(int Norekening){
    system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------EDIT DATA NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(35, 3);
	if(head==NULL){
		printf("No data");
	}else if(head->Norekening==Norekening){
	    printf("\n\t\t\t\t\tMasukkan Data no. rekening yang Baru  \t: ");scanf("%i",&Norekeningm);
	    printf("\t\t\t\t\tMasukkan Data Nama yang Baru          \t: ");scanf(" %[^\n]",&nama2);
	    printf("\t\t\t\t\tMasukkan Data Alamat yang Baru        \t: ");scanf(" %[^\n]",&alamat2);
	    printf("\t\t\t\t\tMasukkan Data No. HP yang Baru        \t: ");scanf(" %[^\n]",&hp2);
	    printf("\t\t\t\t\tMasukkan Data Saldo yang Baru         \t: Rp. ");scanf("%i", &saldoo);
	    head->Norekening=Norekeningm;
	    head->saldo =saldoo;
	    strcpy(head->name,nama2);
	    strcpy(head->Alamat,alamat2);
	    strcpy(head->hp,hp2);

	    printf("\n\n\t\t\t\t\tData Telah Berhasil Terupdate menjadi\t: \n\n");
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",head->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",head->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",head->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",head->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", head->saldo);
		system("PAUSE");
	}else if(tail->Norekening==Norekening){
		printf("\n\t\t\t\t\tMasukkan Data no. rekening yang Baru  \t: ");scanf("%i",&Norekeningm);
	    printf("\t\t\t\t\tMasukkan Data Nama yang Baru            \t: ");scanf(" %[^\n]",&nama2);
	    printf("\t\t\t\t\tMasukkan Data Alamat yang Baru          \t: ");scanf(" %[^\n]",&alamat2);
	    printf("\t\t\t\t\tMasukkan Data No. HP yang Baru          \t: ");scanf(" %[^\n]",&hp2);
	    printf("\t\t\t\t\tMasukkan Data Saldo yang Baru           \t: Rp. ");scanf("%i", &saldoo);
	    tail->Norekening=Norekeningm;
	    tail->saldo=saldoo;
	    strcpy(tail->name,nama2);
	    strcpy(tail->Alamat,alamat2);
	    strcpy(tail->hp,hp2);
	    printf("\n\n\t\t\t\t\tData Telah Berhasil Terupdate menjadi\t: \n\n");
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",tail->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",tail->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",tail->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",tail->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", tail->saldo);
		system("PAUSE");
	}else{
		human *temp=head;
		while(temp->next->Norekening!=Norekening && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		printf("\t\t\t\t\tMasukkan Data No. rekening yang Baru  \t: ");scanf("%i",&Norekeningm);
	    printf("\t\t\t\t\tMasukkan Data Nama yang Baru          \t: ");scanf(" %[^\n]",&nama2);
	    printf("\t\t\t\t\tMasukkan Data Alamat yang Baru        \t: ");scanf(" %[^\n]",&alamat2);
	    printf("\t\t\t\t\tMasukkan Data No. HP yang Baru        \t: ");scanf(" %[^\n]",&hp2);
	    printf("\t\t\t\t\tMasukkan Data Saldo Baru              \t:Rp. ");scanf("%i", &saldoo);
	    current->Norekening=Norekeningm;
	    current->saldo =saldoo;
	    strcpy(current->name,nama2);
	    strcpy(current->Alamat,alamat2);
	    strcpy(current->hp,hp2);
	    printf("\n\n\t\t\t\t\tData Telah Berhasil Terupdate menjadi\t: \n\n");
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",current->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",current->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",current->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",current->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", current->saldo);
		system("PAUSE");
	}}

void cariDatanama(char name[]){

    if(head==NULL){
		printf("No data");
	}else if(strcmp(head->name,name)==0){
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",head->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",head->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",head->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",head->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", head->saldo);
		system("PAUSE");
	}else if(strcmp(tail->name,name)==0){
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",tail->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",tail->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",tail->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",tail->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", tail->saldo);
		system("PAUSE");
	}else{
		human *temp=head;
		while(strcmp(temp->next->name,name)!=0 && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		printf("\t\t\t\t\t\t no. rekening\t:%i \n",current->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",current->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",current->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",current->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", current->saldo);
		system("PAUSE");
	}}

void editDatanama(char name[]){
    system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------UPDATE DATA NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");

	if(head==NULL){
		printf("No data");
	}else if(strcmp(head->name,name)==0){
        gotoxy(30, 3);
	    printf("Masukkan Data No. rekening yang Baru\t: ");scanf("%i",&Norekeningm);
	    gotoxy(30, 4);
	    printf("Masukkan Data Nama yang Baru        \t: ");scanf(" %[^\n]",&nama2);
	     gotoxy(30, 5);
	    printf("Masukkan Data Alamat yang Baru      \t: ");scanf(" %[^\n]",&alamat2);
	    gotoxy(30, 6);
	    printf("Masukkan Data Nomor No. HP yang Baru    \t: ");scanf(" %[^\n]",&hp2);
	    gotoxy(30, 7);
	    printf("Masukkan Data Saldo yang baru       \t: Rp. "); scanf("%i", &saldoo);

	    head->Norekening=Norekeningm;
	    current ->saldo = saldoo;
	    strcpy(head->name,nama2);
	    strcpy(head->Alamat,alamat2);
	    strcpy(head->hp,hp2);

	    printf("\n\t\t\tData Telah Berhasil Terupdate menjadi\t: ");
        printf("\t\t\t\t\t\t no. rekening\t:%i \n",head->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",head->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",head->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",head->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", head->saldo);
		system("PAUSE");
	}else if(strcmp(tail->name,name)==0){
	    gotoxy(30, 6);
		printf("\t\t\t\t\tMasukan Data No. rekening yang Baru\t: ");scanf("%i",&Norekeningm);
	    printf("\t\t\t\t\tMasukan Data Nama yang Baru        \t: ");scanf(" %[^\n]",&nama2);
	    printf("\t\t\t\t\tMasukan Data Alamat yang Baru      \t: ");scanf(" %[^\n]",&alamat2);
	    printf("\t\t\t\t\tMasukan Data No. HP yang Baru          \t: ");scanf(" %[^\n]",&hp2);
	    printf("\t\t\t\t\tMasukkan Data Saldo yang baru      \t : Rp. "); scanf("%i", &saldoo);

	    tail->Norekening=Norekeningm;
	    current ->saldo=saldoo;
	    strcpy(tail->name,nama2);
	    strcpy(tail->Alamat,alamat2);
	    strcpy(tail->hp,hp2);
	    printf("\t\t\t\t\tData Telah Berhasil Terupdate menjadi\t: \n\n");
		printf("\t\t\t\t\t no. rekening\t:%i \n",tail->Norekening);
		printf("\t\t\t\t\t Nama\t\t:%s \n",tail->name);
		printf("\t\t\t\t\t Alamat\t\t:%s \n",tail->Alamat);
		printf("\t\t\t\t\t No. HP\t\t:%s \n",tail->hp);
		printf("\t\t\t\t\t Saldo \t\t:Rp. %i \n", tail->saldo);
		system("PAUSE");
	}else{
		human *temp=head;
		while(strcmp(temp->next->name,name)!=0 && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		printf("\t\t\t\tMasukan Data No. rekening yang Baru\t: ");scanf("%i",&Norekeningm);
	    printf("\t\t\t\tMasukan Data Nama yang Baru\t: ");scanf(" %[^\n]",&nama2);
	    printf("\t\t\t\tMasukan Data Alamat yang Baru\t: ");scanf(" %[^\n]",&alamat2);
	    printf("\t\t\t\tMasukan Data No. HP yang Baru\t: ");scanf(" %[^\n]",&hp2);
	    printf("\t\t\t\tMasukan Data saldo yang Baru\t: ");scanf(" %i",&saldoo);
	    current->Norekening=Norekeningm;
	    current->saldo=saldoo;
	    strcpy(current->name,nama2);
	    strcpy(current->Alamat,alamat2);
	    strcpy(current->hp,hp2);
	    printf("\t\t\t\t\t\t no. rekening\t:%i \n",current->Norekening);
		printf("\t\t\t\t\t\t Nama\t\t:%s \n",current->name);
		printf("\t\t\t\t\t\t Alamat\t\t:%s \n",current->Alamat);
		printf("\t\t\t\t\t\t No. HP\t\t:%s \n",current->hp);
		printf("\t\t\t\t\t\t Saldo \t\t:Rp. %i \n", current->saldo);
		system("PAUSE");
	}}

void swap(struct human *a, human *b){
    int tempe;
    tempe = a->Norekening;
    a->Norekening = b->Norekening;
    b->Norekening = tempe;

     int tahu;
    tahu = a->saldo;
    a->saldo = b->saldo;
    b->saldo = tahu;

    char tempp[30];
    strcpy(tempp,a->name);
    strcpy(a->name,b->name);
    strcpy(b->name,tempp);

    strcpy(tempp,a->Alamat);
    strcpy(a->Alamat,b->Alamat);
    strcpy(b->Alamat,tempp);

    strcpy(tempp,a->hp);
    strcpy(a->hp,b->hp);
    strcpy(b->hp,tempp);
}

void urutDataNorekening(struct human *head){
    int swapped, i;
    struct human *ptr1;
    struct human *lptr = NULL;
    current = head;
    /* Checking for empty list */
    if (current == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = current;

        while (ptr1->next != lptr)
        {
            if (ptr1->Norekening > ptr1->next->Norekening)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void urutDatanama(struct human *head){
    int swapped, i;
    struct human *ptr1;
    struct human *lptr = NULL;
    current = head;
    /* Checking for empty list */
    if (current == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = current;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->name , ptr1->next->name)  > 0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void urutDatahp(struct human *head){
    int swapped, i;
    struct human *ptr1;
    struct human *lptr = NULL;
    current = head;
    /* Checking for empty list */
    if (current == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = current;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->hp , ptr1->next->hp)  > 0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void urutDataAlamat(struct human *head){
    int swapped, i;
    struct human *ptr1;
    struct human *lptr = NULL;
    current = head;
    /* Checking for empty list */
    if (current == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = current;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->Alamat , ptr1->next->Alamat)  > 0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void urutData(){
     system("@cls||clear");
    gotoxy(30, 0);
    printf(" ------------------UPDATE DATA NASABAH-----------------");
    gotoxy(30, 1);
    printf("|______________________________________________________|");
    int v;
        gotoxy(45,3);
    printf("1. Urutkan Berdasarkan Norekening\n");
        gotoxy(45,4);
    printf("2. Urutkan Berdasarkan NAMA\n");
        gotoxy(45,5);
    printf("3. Urutkan Berdasarkan Alamat\n");
        gotoxy(45,6);
    printf("4. Urutkan Berdasarkan hp\n");
        gotoxy(45,7);
    printf("5. Kembali Ke-Menu\n");
        gotoxy(45,8);
    printf("Masukan Pilihan\t: ");
    scanf("%i",&v);
    switch(v){
    case 1:
    urutDataNorekening(head);
    break;
    case 2:
    urutDatanama(head);
    break;
    case 3:
    urutDataAlamat(head);
    break;
    case 4:
    urutDatahp(head);
    break;
    case 5:
    return;
    break;
    }
}

void menuUtama(){
        system("cls");
gotoxy(30,4);
setColor(8);printf(" ==================================================");
gotoxy(30,5);
setColor(3);printf("|| NO |               MENU UTAMA                  ||");
gotoxy(30,6);
setColor(8);printf("||====|===========================================||");
gotoxy(30,7);
setColor(10);
printf("|| 1  | Buat Data Nasabah                         ||");
setColor(3);
gotoxy(30,8);
printf("|| 2  | Input Data Nasabah                        ||");
setColor(10);
gotoxy(30,9);
printf("|| 3  | Hapus Data Nasabah                        ||");
setColor(3);
gotoxy(30,10);
printf("|| 4  | Cari Data Nasabah                         ||");
setColor(10);
gotoxy(30,11);
printf("|| 5  | Update Data Nasabah                       ||");
gotoxy(30,12);
setColor(3);
printf("|| 6  | Urutkan Data Nasabah                      ||");
setColor(10);
gotoxy(30,13);
printf("|| 7  | Tambah Saldo Nasabah                      ||");
setColor(3);
gotoxy(30,14);
printf("|| 9  | lihat Data Nasabah                        ||");
setColor(10);
gotoxy(30,15);
printf("|| 0  | Keluar                                    ||");
setColor(3);
gotoxy(30,16);
setColor(8);printf("||____|___________________________________________||");
gotoxy(34, 17);
setColor(9);
printf("Masukkan Pilihan Anda : ");
        scanf("%i",&pilihan);
}

void password(char *banks) { //bintang untuk pw
    int key = 0, index = 0;
    do {
    key = getch();

    switch (key) {

        case 0:

        case 224:
			getch();
			break;

        case '\b':
			if (index > 0) {
                index = index - 1;
                banks[index] = 0;
                printf("\b \b");
            }
            break;

        default:
			if (key > 31 && key < 127) {
            banks[index] = key;
            index = index + 1;
        	printf("*");
            }
    }
    } while (key != 13);
}


int main(){
     welcome();
char salam [] = "    SELAMAT DATANG DI BANK ROOT    ";

     login:
system("cls");
 SYSTIME();

 setColor(279);
    gotoxy(27, 6);
   for(int hh=0; salam[hh]!=NULL; hh++){
    printf("%c ", salam[hh]);
    for(double cc=0; cc<=9999999; cc++){

    }
Sleep(10);
   }
     gotoxy(25, 8);
     setColor(245);
    for (int i = 0 ; i < 76 ; i++){
    printf("=");
    Sleep(5);}
    printf("\n");
     gotoxy(38,10);
    printf(" Masukan ID \t\t: ");
    scanf(" %[^\n]",&id);
    gotoxy(38,12);
    printf("Masukan Kata Sandi \t: ");
    password(sandi);
    gotoxy(25, 14);
       setColor(245);
    for (int i = 0 ; i < 76 ; i++){
    printf("=");
    Sleep(5);}
    gotoxy(48, 16);
       setColor(279);
    for (int i = 0 ; i < 10 ; i++){
    printf("::");
    Sleep(30);}
      for(int cp = 1; cp<=100; cp++){
                gotoxy(66, 16);
                setColor(245);
                 printf(" %d", cp);
            gotoxy(70, 16);
            printf("%%");
                Sleep(50);
            }

    if (strcmp(id,"guest")==0 && strcmp(sandi,"asdautoa")==0){
    cetak:

   do{
        setColor(3);
        menuUtama();
	switch(pilihan){
    case 1:
        if(head == NULL)    {
            buatDatabase();
            gotoxy(30,18);
            printf("Berhasil Menginputkan Data \n\n");
        }
        else {
            gotoxy(30,18);
            printf("Mohon Maaf Database Sudah Ada\n");
            system("PAUSE");
        }
    break;
    case 2:
        if(head == NULL) {
            gotoxy(30,18);
            printf("Anda Harus Membuat Database terlebih dahulu\n");
            system("PAUSE");
        }
        else {
            system("cls");
            inputData();
            gotoxy(30,18);
            printf("Berhasil Menginputkan Data \n\n");
            system("PAUSE");
        }
    break;
    case 3:
        hapusData();
    break;
    case 4:
        cariData();
    break;
    case 5:
        editData();
    break;
    case 6:
        urutData();
    break;
    case 7:
        tambahsaldo();
    break;
    case 9:
        print();
        printf("\n");
        system("PAUSE");
    break;
    case 0:
        exit(0);
        break;

	}
    }while(pilihan!=0);
    }else{
        gotoxy(39,18);
    printf("Maaf ID / Password yang anda masukan salah!!");
		getch();
		goto login;}
	return 0;
}

void tambahsaldo(){
    int x;
    system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------TAMBAH SALDO NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(20, 3);
        printf("Masukan no. rekening Yang Ingin Ditambah Saldonya\t: ");
        scanf("%i",&x);
        TambahSaldoNorekening(x);
}

void TambahSaldoNorekening(int Norekening){
	int tmbh = 0;
    system("@cls||clear");
    gotoxy(20, 0);
    printf(" ------------------TAMBAH SALDO NASABAH-----------------");
    gotoxy(20, 1);
    printf("|______________________________________________________|");
    gotoxy(20, 3);
	if(head==NULL){
		printf("Belum ada data!\n");
		system("pause");
	}else if(head->Norekening==Norekening){
	    printf("Masukkan Jumlah Saldo yang akan ditambahkan \t: Rp. ");scanf("%i", &tmbh);
	    head->saldo +=tmbh;
	    printf("\n\n\t\t\tSaldo Telah Berhasil Ditambahkan\t: \n\n");
		printf("\t\t\tNo. rekening\t:%i \n",head->Norekening);
		printf("\t\t\tNama\t\t:%s \n",head->name);
        printf("\t\t\tSaldo \t\t: Rp.%i \n", head->saldo);
		system("PAUSE");
	}else if(tail->Norekening==Norekening){
	    printf("Masukkan Jumlah Saldo yang akan ditambahkan \t: Rp. ");scanf("%i", &tmbh);
	    tail->saldo +=tmbh;
	    printf("\n\n\t\t\tSaldo Telah Berhasil Ditambahkan\t: \n\n");
		printf("\t\t\tNo. rekening\t:%i \n",tail->Norekening);
		printf("\t\t\tNama\t\t:%s \n",tail->name);
		 printf("\t\t\tSaldo \t\t: Rp. %i\n", tail->saldo);
		system("PAUSE");
	}else{
		human *temp=head;
		while(temp->next->Norekening!=Norekening && temp!=tail){
			temp=temp->next;
		}
		current=temp->next;
		printf("Masukkan Jumlah Saldo yang akan ditambahkan \t: Rp. ");scanf("%i", &tmbh);
	    current->saldo +=tmbh;
	    printf("\n\n\t\t\tSaldo Telah Berhasil Ditambahkan\t: \n\n");
		printf("\t\t\tNo. rekening\t:%i \n",current->Norekening);
		printf("\t\t\tNama\t\t:%s \n",current->name);
		printf("\t\t\tSaldo \t\t: Rp. %i\n", current->saldo);
		system("PAUSE");
	}
}
void welcome(){

	char l1[] = {" O       O    O O O O   O         O O O O   O O O O   O       O   O O O O         O O O O O   O O O O"};
	char l2[] = {" O   O   O    O         O         O         O     O   O O   O O   O                   O       O     O"};
	char l3[] = {" O  O O  O    O O O O   O         O         O     O   O  O O  O   O O O O             O       O     O"};
	char l4[] = {" O O   O O    O         O         O         O     O   O   O   O   O                   O       O     O"};
	char l5[] = {" O       O    O O O O   O O O O   O O O O   O O O O   O       O   O O O O             O       O O O O"};
	char l6[] = {"                                                                                                      "};
	char l7[] = {"       O O O O    O O O O   O O O O   O O O O O         O O O O      O O     O     O   O     O "};
	char l8[] = {"       O      O   O     O   O     O       O             O      O   O     O   O O   O   O    O  "};
	char l9[] = {"       O O O O    O     O   O     O       O             O O O O    O O O O   O  O  O   O O O   "};
   char l10[] = {"       O    O     O     O   O     O       O             O      O   O     O   O   O O   O    O  "};
   char l11[] = {"       O      O   O O O O   O O O O       O             O O O O    O     O   O     O   O     O "};

	int nilai;
	int lp=0;

	while(lp != 3){
        setColor(113);
        system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t%s",l1); Sleep(31);
		setColor(113); printf("\n\t%s",l2); Sleep(31);
		setColor(113); printf("\n\t%s",l3); Sleep (31);
		setColor(113); printf("\n\t%s",l4); Sleep (31);
		setColor(113); printf("\n\t%s",l5); Sleep (31);
		setColor(114); printf("\n\t%s",l6); Sleep (31);
		setColor(114); printf("\n\t%s",l7); Sleep (31);
		setColor(114); printf("\n\t%s",l8); Sleep (31);
		setColor(114); printf("\n\t%s",l9); Sleep (31);
		setColor(114); printf("\n\t%s",l10); Sleep (31);
		setColor(114); printf("\n\t%s",l11); Sleep (900);
		lp=lp+1;
	}
}
