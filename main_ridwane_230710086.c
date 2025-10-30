#include <stdio.h>
#include <stdlib.h>
int  sec ,choice ,array[15] = {0}; // Koltuklar�n durumu (0 = bo�, 1 = dolu). Global olarak bildiren bir dizi t�m koltuklar 0 olarak ba�lat�l�r.

//
typedef struct
{
   char ad[50];
   char soyad[50];
   unsigned long long kimlik;


} musteri;

void enter_information(){
   musteri information ;
   FILE *p;
   p=fopen("bilgikaydetme.txt","a");
   if(p==NULL){
   printf("dosya acilamadi");
   return ;
   }
    else{

    printf("Adiniz giriniz:");
    scanf("%s",information.ad);

    printf("Soyadiniz giriniz:");
    scanf("%s",information.soyad);

    printf("Kimlik giriniz:");
    scanf("%llu",&information.kimlik);



    fprintf(p,"Ad:%s\nSoyad:%s\nkimlik:%llu\nkoltuk_numarasi:%d\nkategori:%d\n",information.ad,information.soyad,information.kimlik,choice,sec);
    fprintf(p,"\n");
    }
    fclose(p);
    printf("\n*********Bilet Bilgileri*******\n");
    printf("Ad:%s\nSoyad:%s\nkimlik:%llu\nKoltuk_numarai:%d\nkategori:kategori %d\n",information.ad,information.soyad,information.kimlik,choice,sec);
    printf("**********************************\n");

}


//display fonksyon koltuklar durumu goster
void display_seat(int start ,int end){
    int i;
    printf("Koltuk durumasi:\n");
    for ( i = start; i < end; i++) {
        if (array[i] == 0)
            printf("Koltuk %d:Bos\n", i + 1);
        else
            printf("Koltuk %d:Dolu\n", i + 1);
    }
  printf("\n");

}


//bu fonksiyon dizideki koltuklar�n bilgilerini dosyadan g�ncellemenizi sa�lar
void charger_seat(const char *filename,int start ,int end,int *count) {

    FILE *v = fopen(filename,"r");
    int i;
    if (v == NULL) {
    // Dosya mevcut de�ilse t�m koltuklar�n bo� oldu�unu kabul ediliyor.
    //printf("Dosya acilamadi.\n");
        return ;
}
else{
    for ( i = start; i < end; i++) {
        fscanf(v,"%d",&array[i]); // koltuklar�n durumu dosyadan y�klenir ve her koltuk i�in dizide g�ncellenir
        if (array[i] == 1) { //Dolu koltuklar� sayiyoruz
            (*count)++;
             }
    }

    fclose(v);
}

}

//koltuk bilgilerini  dosyalarda kaydetmenizi sa�lar .bu fonksyon dosya yolunu parametre olarak al�r
void save_seat(const char *filenane,int start ,int end) {
    int i;
    FILE *file = fopen(filenane,"w");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }
    for (i = start; i < end; i++) {
        fprintf(file, "%d\n", array[i]); // Her koltu�u (0 veya 1) dosyaya kaydedin
    }
    fclose(file);
}

//Bu fonksiyon kullan�c�dan koltu�unu se�mesini ister. kullan�c�n�n ge�erli bir koltu�a girip girmedi�ini kontrol eder
// ve t�m koltuklar�n dolu olmas� durumunda fonksiyon kullan�c�ya tekrar men�ye geri getiriyor
void  input_seat(const char *filenane,int start,int end , int *count) {
    int c;
    if((*count) ==(end-start))
       // yani e�er *count==5
        {
       printf("Tum koltuklar dolu. Diger kategorilere yonlendiriliyorsunuz...\n");
        return ;
    }

        printf("-Lutfen bir koltuk numarasi seciniz (%d-%d) :\n",start+1,end);
        scanf("%d", &choice);

        // kullan�c�dan koltuk se�imini girmesini ister ve se�iminin ge�erlili�ini kontrol eder
    if(choice < start+1 || choice > end){
        printf("Gecersiz koltuk lutfen (%d-%d) arasinda bir koltuk seciniz . Tekrar deneyin..\n",start+1,end);
        return; //
        }
    else if(array[choice-1]==1)  {
        printf("Koltuk %d zaten reserve edildi tekrar deneyin\n",choice);
        return ;
    }

    else{
    array[choice - 1] = 1; // se�im ge�erliyse dizideki  1 kaydeliyor. dizida 0'dan ba�lad��� i�in -1 yapman�z gerekiyor
    }
    printf("Koltuk %d basariyla rezerve edildi.\n", choice);
    printf("Lutfen bilgilerinizi girin\n");
    printf("\n");
    save_seat(filenane, start, end); // Dosyadaki bilgileri g�ncellemek i�in �a�r�l�r
    enter_information(); // daha sonra kullan�c� bilgilerini girmek i�in �a�r�lar


}

int main() {
  int   s,p,k;
  s=0;
  p=0;
  k=0;

//Bilgileri g�ncellemek i�in ba�lang��ta koltuk durumunu y�kle
     charger_seat("vipkoltuk.txt",0,5,&s);
     charger_seat("birincikategorikoltuk.txt",5,10,&p);
     charger_seat("ikincikategorikoltuk.txt",10,15,&k);

//men�s� g�r�nt�lenir ve kullan�c�ya se�imlerini sorar
    while (1) {
    printf("\n*******Tiyatro bileti sistemi********\n");
    printf("Rezervasyon sistemimize Hos Geldiniz !!!!!!!\n");
    printf("1-VIP (1-5)\n");
    printf("2-Kategori 1  (6-10)\n");
    printf("3-Kategori 2 (11-15)\n");
    printf("4-cikis\n");
    printf("***************************************\n");

    printf("-Rezervasyon yapmak icin lutfen bir kategori seciniz:\n");

    scanf("%d",&sec);

    if(sec==4){
        printf("cikis yapiliyor iyi Gunler\n");
        break;

    }
    else{
    switch (sec){
    case 1:
        printf("VIP Kategori Secildi\n");
        display_seat(0,5);
        input_seat("vipkoltuk.txt",0,5,&s);
        break;
    case 2:
        printf("Kategori 1 Secildi\n");
        display_seat(5,10);
        input_seat("birincikategorikoltuk.txt",5,10,&p);

        break;
    case 3:
        printf("Kategori 2 Secildi\n");
        display_seat(10,15);
        input_seat("ikincikategorikoltuk.txt",10,15,&k);
        break;

    default:
        printf("Gecersiz bir secim yaptiniz. Tekrar deneyin.\n");


    }

    }
    }

    return 0;

}

