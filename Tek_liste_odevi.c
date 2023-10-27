#include <stdio.h>
#include <stdlib.h>                            
#include <time.h>
#include <string.h>

struct node {
    int Number;
    char Name[50];
    int age;
    struct node* next;
};

/*-------------------------------------------------------------------------------------------------------
 Soru 1: Klavyeden -1 girilinceye kadar, girilen tüm tek sayilari listenin basina, çift sayilari ise
listenin sonuna ekleyen fonksiyonu yaziniz.
--------------------------------------------------------------------------------------------------------*/
//listeye eleman ekleyen fonk.
struct node* Node_ekle(struct node* head, int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node)); //yeni bir dügüm olusturduk 
    newNode->Number = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else if (data % 2 != 0) { //Eger girilecek sayi tek ise listenin basina eklesin.
        newNode->next = head;
        head = newNode;
    } else { // girilecek sayi cift oldugu icin listenin sonuna eklesin.
        struct node* last = head;
        while (last->next != NULL)
            last = last->next;
        last->next = newNode;
    }

    return head; 
}

/*-------------------------------------------------------------------------------------------------------------------- 
SORU 2: Listeye rastgele üretilmis 100 sayi eklensin, girilen tüm sayilarini büyükten küçüge siralayan
ve ekrana basan c kodunu yaziniz....
-----------------------------------------------------------------------------------------------------------------------*/
struct node* Node_siralama(struct node* head, int newData) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));//yeni bir dügüm olusturduk 
    newNode->Number = newData;
    newNode->next = NULL;

    if (head == NULL || newData >= head->Number) {// Eger ilk dugum bos veya girilecek sayi mevcut sayýdan esit yada büyükse , liste basaina eklesin
        newNode->next = head;
        return newNode;
    } /* buyuk sayilar liste basaina ekliniyour...*/

    struct node* current = head;
    while (current->next != NULL && newData < current->next->Number) { // liste sonuna gidiyor ve kucuk sayilar yerlestiriliyor...
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}


void print(struct node *head) // yazdiran fonksyonun
{
    if(head == NULL)
        printf("The list is empty ,Unlucky!");
    else
    {
        while(head!=NULL)
        {
            printf(" %d--> ",head->Number);
            head = head->next;
        }
        printf("NULL"); /*   |data| --> |data| --> |data| --> NULL   su sekilde yazdirmak icin   */
    }
}
// bu fonksiyonu diger fonksiyonlar kullanabilmek icin yazdik
struct node* kayit_ekle(struct node* head) {
    struct node* ogrenci = (struct node*)malloc(sizeof(struct node));
    printf("Ogrenci numarasini giriniz:\n");
    printf("Numara: ");
    scanf("%d", &ogrenci->Number);
    printf("Ogrenci adini giriniz:\n");
    printf("Ad: ");
    scanf("%s", ogrenci->Name);
    printf("Ogrenci yasini giriniz:\n");
    printf("Yas: ");
    scanf("%d", &ogrenci->age);

    ogrenci->next = head; // Connect the new student to the previous head
    head = ogrenci; // Update the head to point to the new student

    printf("Kayit eklendi.\n");
    return head;
}


/*------------------------------------------------------------------------------------------------------------------------
SORU 3: ogrenci numarasi, isim ve yasi sakli tutuldugu, listedeki tüm dügümleri Dolasan,
ögrenci bilgilerinin tümünü ekrana yazan ve sayan fonksiyonu yaziniz
OUTPUT: 1- Saliha 27 201
 		2- Ece 19 203
---------------------------------------------------------------------------------------------------------------------------*/
void OgrenciDolas(struct node* head) {
    int count = 1; //listede en az 1 ogrenci olmalidir
    struct node* current = head;

    while (current != NULL) {
        printf("%d - %s %d %d\n", count, current->Name, current->age, current->Number); //tum kayitlari yazdirir ve count artiri
        current = current->next; //diger nodeler gider...
        count++;
    }
}
/*-----------------------------------------------------------------------------------
SORU 4 : Listede ögrenci adina göre kayit arama yapan fonksiyonu yaziniz.
----------------------------------------------------------------------------------- */
void ada_gore_ara(struct node *head, char* Name) {

    if (head == NULL) {
        printf("Kayit bulunamadi.\n");
        return;
    }

    struct node* temp = head;
    int bulundu = 0;
    while (temp != NULL) {
        if (strcmp(temp->Name, Name) == 0) { //strcmp fonksiyonu iki ifadeyi karsilastirir. iki ifade ayni ise sonuc sifirdir
            OgrenciDolas(temp);// Koþul saglaniyorsa ogrencinin bilgilerini gosterecek
            bulundu = 1;
        }
        temp = temp->next;
    }
    if (!bulundu) // bastan degeri 0 attik ,,,,,bulundu ==0 ise istedigimiz isimi bulamadik...
        printf("Verilen isme sahip kayit bulunamadi.\n");
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------
 SORU 5 : Listede aranan ögrenci adinin yer aldigi düðümden bir sonraki dügümü silen fonksiyonu yaziniz
--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void OgrenciSil(struct node** head, const char* arananIsim) {
    struct node *current = *head;
    struct node *onceki = NULL;

    while (current != NULL) {
        if (strcmp(current->Name, arananIsim) == 0) {// Aranan isim bulundu, bu dügümü listeden çikar
            
            if (onceki == NULL) {
                // ilk dügümü silme
                *head = current->next;
            } else {
                // Orta veya son düðümü silme
                onceki->next = current->next;
            }
            free(current);
            return; // islem tamamlandi 
        }

        onceki = current;
        current = current->next;
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------
 SORU 6  : Listede en uzun ismin oldugu kaydi yazdiran fonksiyonu yaziniz.
Cikti : listedeki en uzun isim : Abdurrahmangazi
Uzunluk : 15 
---------------------------------------------------------------------------------------------------------------------------------------------*/

void En_Uzun_isim_bul(struct node* head) {
    struct node* current = head;
    struct node* enUzunIsimli = NULL; // En uzun isim tutmak icin tanimladik

    while (current != NULL) {

        if (enUzunIsimli == NULL || strlen(current->Name) > strlen(enUzunIsimli->Name)) { //"iki ismin karakter sayisini karsilastiriyor."
            enUzunIsimli = current;
        }
        current = current->next;
    }

    if (enUzunIsimli != NULL) {
        printf("Listedeki en uzun isim: %s\n", enUzunIsimli->Name);
        printf("Uzunluk: %d\n", (int)strlen(enUzunIsimli->Name));
    } else {
        printf("Listede herhangi bir ogrenci bulunamadi.\n");
    }
}





int main() {
    struct node* head = NULL;
    struct node *temp =head;
    int choice, data,i;
    char arananIsim[50];

    srand(time(NULL)); //rastgele sayilar icin

    do {
        printf("\n**** Kullanci Menusu ****\n");
        printf("1. Tek sayilari listenin basina ekle, cift sayilari listenin sonuna ekle\n");
        printf("2. Rastgele 100 sayi ekleyip buyukten kucuge sirala ve listele\n");
        printf("3. yine ogrenci kayidi ekle\n");
        printf("4. Ogrenci bilgilerini liste ve say\n");
        printf("5. Ogrenci arama\n");
        printf("6. Ogrenci silme\n");
        printf("7. En uzun ismi bul\n");
        printf("8. Exit\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Listeye eklemek istediginiz sayiyi girin (cikis icin -1 girin): ");
                while (1) {
                    scanf("%d", &data);
                    if (data == -1)
                        break;
                    head = Node_ekle(head, data);
                }  print(head);// tek bagli liste yazdiran fonksiyonu
                break;
            case 2:
                for ( i = 0; i <= 20; i++) {
                    int newData = rand() % 100; //0 ile 99  rastgele sayilar
                    head = Node_siralama(head, newData);
                }
                print(head);
                break;
                
			case 3:
				head = kayit_ekle(head);
				break;
            case 4:
                OgrenciDolas(head);
                break;
            case 5:
                printf("Aranan Ogrenci adini girin: ");
                scanf("%s", arananIsim);
                ada_gore_ara(head, arananIsim);
                break;
            case 6:
                printf("Silmek istediginiz Ogrenci adini girin: ");
                scanf("%s", arananIsim);
                OgrenciSil(&head, arananIsim);
                break;
            case 7:
                En_Uzun_isim_bul(head);
                break;
            case 8:
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
    } while (choice != 8);

    // Bellegi temizle
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

