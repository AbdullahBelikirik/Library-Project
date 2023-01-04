#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct Ogrenci { char ogrID[9]; char ad[30]; char soyad[30]; int puan; struct Ogrenci *next; struct Ogrenci *prev;}Ogrenci;
typedef struct Yazar { int yazarID; char yazarAd[30]; char yazarSoyad[30]; struct Yazar *next;}Yazar;
typedef struct KitapOrnek { char EtiketNo[20]; char Durum[8]; struct KitapOrnek *next;}KitapOrnek;
typedef struct Kitap {char kitapAdi[30]; char ISBN[13]; struct Kitap *next; struct KitapOrnek *head;}Kitap;
typedef struct KitapYazar{ char ISBN[13]; int YazarID;}KitapYazar;
typedef struct Tarih{ int gun; int ay; int yil;}Tarih;
typedef struct KitapOdunc{ char EtiketNo[20]; char ogrID[9]; int islemTipi; struct Tarih islemTarihi;}KitapOdunc;

void okuYazarlar(Yazar* yazarHead);
void okuKitaplar(Kitap* kitapHead);
void okuOgrenciler(Ogrenci* ogrenciHead);
void okuKitapYazar(KitapYazar* kitapYazarArray, int* kitapYazarCount);
void okuKitapOdunc(KitapOdunc* kitapOduncArray, int* kitapOduncCount);
void oku(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount);
void yazarEkle(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead);
void yazarGuncelle(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead);
void yazarYazdir(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead);
void yazarGoruntule(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead);
void yazarSil(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead);
void yazarKaydet(Yazar* yazarHead);
void kitapEkle(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead);
void kitapGuncelle(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead);
void kitapGoruntule(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead);
void kitapYazdir(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead);
void raftaKitapYazdir(Kitap* kitapHead);
void teslimEdilmeyenKitaplar(KitapOdunc* kitapOduncArray, int* kitapOduncCount, struct tm *now);
void kitapYazarEsle(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead);
void kitapSil(Kitap* kitapHead);
void kitapKaydet(Kitap* kitapHead);
void kitapDurumGuncelle(Kitap* kitapHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount);
void ogrenciYazdir(Ogrenci* ogrenciHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount, Kitap* kitapHead);
void ogrenciEkle(Ogrenci* ogrenciHead);
void ogrenciGuncelle(Ogrenci* ogrenciHead);
void ogrenciGoruntule(Ogrenci* ogrenciHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount);
void ogrenciSil(Ogrenci* ogrenciHead);
void ogrenciKaydet(Ogrenci* ogrenciHead);
void kitapYazarKaydet(KitapYazar* kitapYazarArray, int* kitapYazarCount);
void kitapOduncKaydet(KitapOdunc* kitapOduncArray, int* kitapOduncCount);
void teslimEtmeyenOgrenciler(Ogrenci* ogrenciHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount);
void cezaliOgrenciler(Ogrenci* ogrenciHead);
void oduncAlma(Ogrenci* ogrenciHead, Kitap* kitapHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount, struct tm *now);
void teslimEtme(Ogrenci* ogrenciHead, Kitap* kitapHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount, struct tm *now);
void anaMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now);
void yazarMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now);
void kitapMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now);
void ogrenciMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now);
int tarihFarki(struct tm *time1, int gun, int ay, int yil);

int main(int argc, char *argv[]) {
	int kitapYazarCount, kitapOduncCount;	
	Yazar* yazarHead = (Yazar*) malloc(sizeof(Yazar)); 
	Kitap* kitapHead = (Kitap*) malloc(sizeof(Kitap));
	Ogrenci* ogrenciHead = (Ogrenci*) malloc(sizeof(Ogrenci));
	KitapYazar* kitapYazarArray = (KitapYazar*) malloc(20*sizeof(KitapYazar));
	KitapOdunc* kitapOduncArray = (KitapOdunc*) malloc(20*sizeof(KitapOdunc));	
	time_t now = time(NULL);
	struct tm *local_time = localtime(&now);
	
	oku(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, &kitapYazarCount, &kitapOduncCount);
	anaMenu(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, &kitapYazarCount, &kitapOduncCount, local_time);
	return 0;
}

void okuYazarlar(Yazar* yazarHead){
	char* buffer = (char*) malloc(1024*sizeof(char));
	char* token;
	FILE* fp = fopen("Yazarlar.csv", "r");
	int i;
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(!feof(fp)){
			Yazar* tmp = (Yazar*) malloc(sizeof(Yazar));
			yazarHead->next = tmp;
			
			fgets(buffer, 1024, fp);
			token = strtok(buffer, ",");
			
			while(token != NULL){
				i=0;
				tmp->yazarID = atoi(token);
            	token = strtok(NULL, ",");
				strcpy(tmp->yazarAd,token);
            	token = strtok(NULL, ",");
            	while(*(token+i) != '\n'){
            		i++;
				}
				*(token+i) = '\0';
            	strcpy(tmp->yazarSoyad,token);
            	token = strtok(NULL, ",");
        	}
        	yazarHead = yazarHead->next;
		}
		yazarHead->next = NULL;
	}
	fclose(fp);
}

void okuKitaplar(Kitap* kitapHead){
	char* buffer = (char*) malloc(1024*sizeof(char));
	char* token;
	int i, j, ornekSayisi;
	
	FILE* fp = fopen("Kitaplar.csv", "r");
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(!feof(fp)){
			Kitap* tmp = (Kitap*) malloc(sizeof(Kitap));
			KitapOrnek* tmpOrnekHead = (KitapOrnek*) malloc(sizeof(KitapOrnek));
			kitapHead->next = tmp;
			tmp->head = tmpOrnekHead; 
			
			fgets(buffer, 1024, fp);
			token = strtok(buffer, ",");
			
			while(token != NULL){
				strcpy(tmp->kitapAdi,token);
				token = strtok(NULL, ",");
				strcpy(tmp->ISBN,token);
            	token = strtok(NULL, ",");
            	ornekSayisi = atoi(token);
				token = strtok(NULL, ",");
				
            	for(i=0; i<ornekSayisi; i++){
            		KitapOrnek* tmpOrnek = (KitapOrnek*) malloc(sizeof(KitapOrnek));
					strcpy(tmpOrnek->EtiketNo,kitapHead->next->ISBN);
					tmpOrnek->EtiketNo[13] = '_';
					tmpOrnek->EtiketNo[14] = i +'0';
					tmpOrnek->EtiketNo[15] = '\0';
					strcpy(tmpOrnek->Durum,"Rafta");
					tmpOrnekHead->next = tmpOrnek;
					tmpOrnekHead = tmpOrnekHead->next;
				}
				tmpOrnekHead->next = NULL;
        	}
        	kitapHead = kitapHead->next;
		}
		kitapHead->next = NULL;
	}
	fclose(fp);
}

void okuOgrenciler(Ogrenci* ogrenciHead){
	char* buffer = (char*) malloc(1024*sizeof(char));
	char* token;
	ogrenciHead->prev = NULL;
	
	FILE* fp = fopen("Ogrenciler.csv", "r");
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(!feof(fp)){
			Ogrenci* tmp = (Ogrenci*) malloc(sizeof(Ogrenci));
			ogrenciHead->next = tmp;
			tmp->prev = ogrenciHead;
			
			fgets(buffer, 1024, fp);
			token = strtok(buffer, ",");
			
			while(token != NULL){
				strcpy(tmp->ogrID,token);
				token = strtok(NULL, ",");
				strcpy(tmp->ad,token);
				token = strtok(NULL, ",");
				strcpy(tmp->soyad,token);
				token = strtok(NULL, ",");
				tmp->puan = atoi(token);
				token = strtok(NULL, ",");
        	}
        	ogrenciHead = ogrenciHead->next;
		}
		ogrenciHead->next = NULL;
	}
	fclose(fp);
}

void okuKitapYazar(KitapYazar* kitapYazarArray, int* kitapYazarCount){
	char* buffer = (char*) malloc(1024*sizeof(char));
	char* token;
	int row = 1;
	
	FILE* fp = fopen("KitapYazar.csv", "r");
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(!feof(fp)){
			fgets(buffer, 1024, fp);
			token = strtok(buffer, ",");
			while(token != NULL){
				strcpy(kitapYazarArray[row-1].ISBN,token);
				token = strtok(NULL, ",");
            	kitapYazarArray[row-1].YazarID = atoi(token);
				token = strtok(NULL, ",");
        	}
        	row++;
		}		
	}
	fclose(fp);	
	*kitapYazarCount = row-1;
}

void okuKitapOdunc(KitapOdunc* kitapOduncArray, int* kitapOduncCount){
	char* buffer = (char*) malloc(1024*sizeof(char));
	char* token;
	int row = 1;
	char delimit[] = ",.";
	
	FILE* fp = fopen("KitapOdunc.csv", "r");
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(!feof(fp)){	
			fgets(buffer, 1024, fp);
			token = strtok(buffer, delimit);
			while(token != NULL){
				strcpy(kitapOduncArray[row-1].EtiketNo,token);
				token = strtok(NULL, delimit);
				strcpy(kitapOduncArray[row-1].ogrID,token);
				token = strtok(NULL, delimit);
				kitapOduncArray[row-1].islemTipi = atoi(token);
				token = strtok(NULL, delimit);	
				kitapOduncArray[row-1].islemTarihi.gun = atoi(token);
				token = strtok(NULL, delimit);
				kitapOduncArray[row-1].islemTarihi.ay = atoi(token);
				token = strtok(NULL, delimit);
				kitapOduncArray[row-1].islemTarihi.yil = atoi(token);
				token = strtok(NULL, delimit);
        	}
        	row++;
		}		
	}
	fclose(fp);	
	*kitapOduncCount = row-1;
}

void oku(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount){
	okuYazarlar(yazarHead);
	okuKitaplar(kitapHead);
	okuOgrenciler(ogrenciHead);
	okuKitapYazar(kitapYazarArray, kitapYazarCount);
	okuKitapOdunc(kitapOduncArray, kitapOduncCount);
	kitapDurumGuncelle(kitapHead, kitapOduncArray, kitapOduncCount);
}

void yazarEkle(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead){
	Yazar* tmp = (Yazar*) malloc(sizeof(Yazar));
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));

	tmp->next = NULL;
	while(yazarHead->next != NULL){
		yazarHead = yazarHead->next;
	}
	
	printf("Eklemek istediginiz yazarin adini giriniz : ");
	scanf("%s",ad);
	printf("Eklemek istediginiz yazarin soyadini giriniz : ");
	scanf("%s",soyad);
	
	strcpy(tmp->yazarAd,ad);
	strcpy(tmp->yazarSoyad,soyad);
	tmp->yazarID = (yazarHead->yazarID)+1;
	yazarHead->next = tmp;
}

void yazarGuncelle(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	char* kitapAdi = (char*) malloc(30*sizeof(char));
	char* isbn = (char*) malloc(13*sizeof(char));
	int ornekSayisi, isFind = 0, count, i;
	Yazar* tmpYazar = yazarHead;
	
	printf("Kitap eklemek istediginiz yazarin adini giriniz : ");
	scanf("%s",ad);
	printf("Kitap eklemek istediginiz yazarin soyadini giriniz : ");
	scanf("%s",soyad);
	printf("Eklemek istediginiz kitabin adini giriniz : ");
	scanf("%s",kitapAdi);
	printf("Eklemek istediginiz kitabin ISBN numarasini giriniz : ");
	scanf("%s",isbn);
	printf("Eklemek istediginiz kitabin ornek sayisini giriniz : ");
	scanf("%d",&ornekSayisi);	
	
	while((tmpYazar->next != NULL) && (isFind == 0)){
		if((strcmp(tmpYazar->next->yazarAd,ad) == 0) && (strcmp(tmpYazar->next->yazarSoyad,soyad) == 0)){
			isFind = 1;
		}
		else{
			tmpYazar = tmpYazar->next;
		}
	}
	if(isFind == 0){
		printf("\nGuncellemek istediginiz yazar kayitli degildir.");
	}
	else{
		Kitap* tmp = (Kitap*) malloc(sizeof(Kitap));
		KitapOrnek* tmpOrnekHead = (KitapOrnek*) malloc(sizeof(KitapOrnek));
		while(kitapHead->next != NULL){
			kitapHead = kitapHead->next;
		}
		
		kitapHead->next = tmp;
		tmp->next = '\0';
		
		count = *kitapYazarCount;
		count++;
		*kitapYazarCount = count;
		
		for(i=0; i<ornekSayisi; i++){
			KitapOrnek* tmpOrnek = (KitapOrnek*) malloc(sizeof(KitapOrnek));
			strcpy(tmpOrnek->Durum,"Rafta");
			strcpy(tmpOrnek->EtiketNo,isbn);
			tmpOrnek->EtiketNo[13] = '_';
			tmpOrnek->EtiketNo[14] = i +'0';
			tmpOrnek->EtiketNo[15] = '\0';
			tmpOrnekHead->next = tmpOrnek;
			tmpOrnekHead = tmpOrnekHead->next;
		}
		tmpOrnekHead->next = NULL;
		strcpy(tmp->kitapAdi,kitapAdi);
		strcpy(tmp->ISBN,isbn);
		kitapYazarArray = realloc(kitapYazarArray, count);
		strcpy(kitapYazarArray[count-1].ISBN,isbn);
		kitapYazarArray[count-1].YazarID = tmpYazar->next->yazarID;
	}		
}

void yazarYazdir(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead){
	int i;
	Kitap* tmp;
	while(yazarHead->next != NULL){
		printf("\nID : %d, ad : %s, soyad : %s\nKitaplari : ",yazarHead->next->yazarID,yazarHead->next->yazarAd,yazarHead->next->yazarSoyad);
		for(i=0; i<*kitapYazarCount;i++){ 
			if(kitapYazarArray[i].YazarID == yazarHead->next->yazarID){
				tmp = kitapHead;
				while(tmp->next != NULL){
					if(strcmp(kitapYazarArray[i].ISBN,tmp->next->ISBN) == 0){
						printf("isbn : %s ad : %s\n",tmp->next->ISBN,tmp->next->kitapAdi);	
					}
					tmp = tmp->next;
				}
			}
		}
		yazarHead = yazarHead->next;
	}
}

void yazarGoruntule(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	int isFind = 0, i;
	Kitap* tmp = kitapHead;
	
	printf("Bilgisini goruntulemek istediginiz yazarin adini giriniz : ");
	scanf("%s",ad);
	printf("Bilgisini goruntulemek istediginiz yazarin soyadini giriniz : ");
	scanf("%s",soyad);
	
	while((yazarHead->next != NULL) && (isFind == 0)){
		if((strcmp(yazarHead->next->yazarAd,ad) == 0) && (strcmp(yazarHead->next->yazarSoyad,soyad) == 0)){
			isFind = 1;
		}
		else{
			yazarHead = yazarHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Goruntulemek istediginiz yazar bulunamadi.");
	}
	
	else{
		printf("\nID : %d, ad : %s, soyad : %s\nKitaplari : ",yazarHead->next->yazarID,yazarHead->next->yazarAd,yazarHead->next->yazarSoyad);
		for(i=0; i<*kitapYazarCount;i++){
			printf("\n%d %d",kitapYazarArray[i].YazarID,yazarHead->next->yazarID);
			if(kitapYazarArray[i].YazarID == yazarHead->next->yazarID){
				while(tmp->next != NULL){
					if(strcmp(kitapYazarArray[i].ISBN,tmp->next->ISBN) == 0){
						printf("isbn : %s ad : %s\n",tmp->next->ISBN,tmp->next->kitapAdi);	
					}
					tmp = tmp->next;
				}
			}
		}
	}	
}

void yazarSil(Yazar* yazarHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Kitap* kitapHead){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	int id, isFind = 0, i;
	
	printf("Silmek istediginiz yazarin adini giriniz : ");
	scanf("%s",ad);
	printf("Silmek istediginiz yazarin soyadini giriniz : ");
	scanf("%s",soyad);
	
	while((yazarHead->next != NULL) && (isFind == 0)){
		if((strcmp(yazarHead->next->yazarAd,ad) == 0) && (strcmp(yazarHead->next->yazarSoyad,soyad) == 0)){
			isFind = 1;
			printf("\n%s %s isimli yazar silinmistir.\n",yazarHead->next->yazarAd,yazarHead->next->yazarSoyad);
			id = yazarHead->next->yazarID;
		}
		else{
			yazarHead = yazarHead->next;
		}
	}
	if(isFind == 0){
		printf("\nSilmek istediginiz yazar kayitli degildir.");
	}
	else{
		free(yazarHead->next);
		yazarHead->next = yazarHead->next->next;
	}
	
	for(i=0; i<*kitapYazarCount; i++){
		if(id == kitapYazarArray[i].YazarID){
			kitapYazarArray[i].YazarID = -1;
		}
	}
}

void yazarKaydet(Yazar* yazarHead){
	FILE* fp = fopen("Yazarlar.csv", "w");
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(yazarHead->next != NULL){
			if(yazarHead->next->next != NULL){
				fprintf(fp,"%d,%s,%s\n",yazarHead->next->yazarID,yazarHead->next->yazarAd,yazarHead->next->yazarSoyad);
        	}
        	else{
        		fprintf(fp,"%d,%s,%s",yazarHead->next->yazarID,yazarHead->next->yazarAd,yazarHead->next->yazarSoyad);
			}
			yazarHead = yazarHead->next;
			}
		}
	fclose(fp);
}

void kitapEkle(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead){
	char* kitapAdi = (char*) malloc(30*sizeof(char));
	char* isbn = (char*) malloc(13*sizeof(char));
	int ornekSayisi, id, i, count;
	Kitap* tmp = (Kitap*) malloc(sizeof(Kitap));
	KitapOrnek* tmpOrnekHead = (KitapOrnek*) malloc(sizeof(KitapOrnek));
	count = *kitapYazarCount;
	count++;
	*kitapYazarCount = count;
	
	printf("Eklemek istediginiz kitabin adini giriniz : ");
	scanf("%[^\n]",kitapAdi);
	printf("Eklemek istediginiz kitabin ISBN numarasini giriniz : ");
	scanf("%s",isbn);
	printf("Eklemek istediginiz kitabin ornek sayisini giriniz : ");
	scanf("%d",&ornekSayisi);
	printf("Eklemek istediginiz kitabin yazar ID'sini giriniz : ");
	scanf("%d",&id);
	
	while(kitapHead->next != NULL){
		kitapHead = kitapHead->next;
	}
	
	kitapHead->next = tmp;
	strcpy(tmp->kitapAdi,kitapAdi);
	strcpy(tmp->ISBN,isbn);
	
	tmp->head = tmpOrnekHead;
	
	for(i=0; i<ornekSayisi; i++){
		KitapOrnek* tmpOrnek = (KitapOrnek*) malloc(sizeof(KitapOrnek));
		strcpy(tmpOrnek->Durum,"Rafta");
		strcpy(tmpOrnek->EtiketNo,kitapHead->next->ISBN);
		tmpOrnek->EtiketNo[13] = '_';
		tmpOrnek->EtiketNo[14] = i +'0';
		tmpOrnek->EtiketNo[15] = '\0';
		tmpOrnekHead->next = tmpOrnek;
		tmpOrnekHead = tmpOrnekHead->next;
		printf("%s",tmpOrnekHead->EtiketNo);
	}
	tmpOrnekHead->next = NULL;
	
	kitapYazarArray = realloc(kitapYazarArray, count);
	strcpy(kitapYazarArray[count-1].ISBN,isbn);
	kitapYazarArray[count-1].YazarID = id;
}

void kitapGuncelle(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead){
	char* kitapAdi = (char*) malloc(30*sizeof(char));
	char* isbn = (char*) malloc(13*sizeof(char));
	int secim, isFind = 0;
	
	printf("Guncellemek istediginiz kitabin adini giriniz : ");
	scanf("%[^\n]",kitapAdi);
	printf("Guncellemek istediginiz kitabin ISBN numarasini giriniz : ");
	scanf("%s",isbn);
	
	while((kitapHead->next != NULL) && (isFind == 0)){
		if(strcmp(kitapHead->next->kitapAdi,kitapAdi) == 0){
			isFind = 1;
		}
		else{
			kitapHead = kitapHead->next;
		}
	}
	if(isFind == 0){
		printf("\nGuncellemek istediginiz kitap kayitli degildir.\n\n");
	}
	else{
		
	}
}

void kitapGoruntule(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead){
	char* kitapAdi = (char*) malloc(sizeof(char)*30);
	int isFind = 0, i;
	Yazar* tmp = yazarHead;
	
	printf("Goruntulemek istediginiz kitabin adini giriniz : ");
	scanf("%[^\n]s",kitapAdi);
	
	while((kitapHead->next != NULL) && (isFind == 0)){
		if(strcmp(kitapHead->next->kitapAdi,kitapAdi) == 0){
			isFind = 1;
		}
		else{
			kitapHead = kitapHead->next;
		}
	}
	if(isFind == 0){
		printf("\nGoruntulemek istediginiz kitap kayitli degildir.\n\n");
	}
	else{
		printf("ISBN : %s Kitap Adi : %s\nYazarlari : ",kitapHead->next->ISBN,kitapHead->next->kitapAdi);
		for(i=0; i<*kitapYazarCount; i++){
			if(strcmp(kitapYazarArray[i].ISBN,kitapHead->next->ISBN) == 0){
				tmp = yazarHead;
				while(tmp->next != NULL){
					if(kitapYazarArray[i].YazarID == tmp->next->yazarID){
						printf("adi : %s soyadi : %s ID : %d\n",tmp->next->yazarAd,tmp->next->yazarSoyad,tmp->next->yazarID);
					}
					tmp = tmp->next;
				}
			}
		}
	}
}

void kitapYazdir(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead){
	int i;
	while(kitapHead->next != NULL){
		Yazar* tmp = yazarHead;
		printf("ISBN : %s Kitap Adi : %s\nYazarlari : ",kitapHead->next->ISBN,kitapHead->next->kitapAdi);
		for(i=0; i<*kitapYazarCount; i++){
			if(strcmp(kitapYazarArray[i].ISBN,kitapHead->next->ISBN) == 0){
				tmp = yazarHead;
				while(tmp->next != NULL){
					if(kitapYazarArray[i].YazarID == tmp->next->yazarID){
						printf("adi : %s soyadi : %s ID : %d\n",tmp->next->yazarAd,tmp->next->yazarSoyad,tmp->next->yazarID);
					}
					tmp = tmp->next;
				}
			}
		}
		printf("\nOrnekleri : ");
		while(kitapHead->next->head->next != NULL){
			printf("Etiket no : %s, durum : %s\n",kitapHead->next->head->next->EtiketNo,kitapHead->next->head->next->Durum);
			kitapHead->next->head = kitapHead->next->head->next;
		}
		printf("\n");
		kitapHead = kitapHead->next;
	}
}

void raftaKitapYazdir(Kitap* kitapHead){
	int isAny;
	
	while(kitapHead->next != NULL){
		isAny = 0;
		while((kitapHead->next->head->next != NULL) && (isAny == 0) ){
			if(strcmp("Rafta",kitapHead->next->head->next->Durum) == 0){
				isAny = 1;
			}
			else{
				kitapHead->next->head = kitapHead->next->head->next;
			}
		}
		printf("ISBN : %s Kitap Adi : %s\n",kitapHead->next->ISBN,kitapHead->next->kitapAdi);	
		printf("\nOrnekleri : ");
			
		while(kitapHead->next->head->next != NULL){
			if(strcmp("Rafta",kitapHead->next->head->next->Durum) == 0){
				printf("Etiket no : %s\n",kitapHead->next->head->next->EtiketNo);
			}
			kitapHead->next->head = kitapHead->next->head->next;
		}
		printf("\n");
		kitapHead = kitapHead->next;
	}
}

void kitapYazarEsle(Kitap* kitapHead, KitapYazar* kitapYazarArray, int* kitapYazarCount, Yazar* yazarHead){
	char* kitapAdi = (char*) malloc(30*sizeof(char));
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	int isFind = 0, count;
	
	printf("Eslemek istediginiz kitabin adini giriniz : ");
	scanf("%[^\n]",kitapAdi);
	
	while((kitapHead->next != NULL) && (isFind == 0)){
		if(strcmp(kitapHead->next->kitapAdi,kitapAdi) == 0){
			isFind = 1;
		}
		else{
			kitapHead = kitapHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Eslemek istediginiz kitap bulunamadi.");
	}
			
	else{
		isFind = 0;
		printf("\nEslemek istediginiz yazarin adini giriniz : ");
		scanf("%s",ad);
		printf("Eslemek istediginiz yazarin soyadini giriniz : ");
		scanf("%s",soyad);
		printf("\n\n");
	
		while((yazarHead->next != NULL) && (isFind == 0)){
			if((strcmp(yazarHead->next->yazarAd,ad) == 0) && (strcmp(yazarHead->next->yazarSoyad,soyad) == 0)){
				isFind = 1;
			}
			else{
				yazarHead = yazarHead->next;
			}
		}
	
		if(isFind == 0){
			printf("Eslemek istediginiz yazar bulunamadi.");
		}
		else{
			count = *kitapYazarCount;
			count++;
			*kitapYazarCount = count;
	
			kitapYazarArray = realloc(kitapYazarArray, count);
			strcpy(kitapYazarArray[count-1].ISBN,kitapHead->next->ISBN);
			kitapYazarArray[count-1].YazarID = yazarHead->next->yazarID;
		}
	}
}

void kitapSil(Kitap* kitapHead){
	char* kitapAdi = (char*) malloc(sizeof(char)*30);
	int isFind = 0;
	
	printf("Silmek istediginiz kitabin adini giriniz : ");
	scanf("%[^\n]",kitapAdi);
	
	while((kitapHead->next != NULL) && (isFind == 0)){
		if(strcmp(kitapHead->next->kitapAdi,kitapAdi) == 0){
			isFind = 1;
			printf("\n%s numarali %s isimli kitap silinmistir.\n\n",kitapHead->next->ISBN,kitapHead->next->kitapAdi);
		}
		else{
			kitapHead = kitapHead->next;
		}
	}
	if(isFind == 0){
		printf("\nSilmek istediginiz kitap kayitli degildir.\n\n");
	}
	else{
		free(kitapHead->next);
		kitapHead->next = kitapHead->next->next;
	}
}

void kitapKaydet(Kitap* kitapHead){
	int i;
	FILE* fp = fopen("Kitaplar.csv", "w");
	
	if(!fp){
        printf("Can't open file\n");
	}
	else{
		while(kitapHead->next != NULL){
			i = 0;
			while(kitapHead->next->head->next != NULL){
				i++;
				kitapHead->next->head = kitapHead->next->head->next;
			}
			
			if(kitapHead->next->next != NULL){
				fprintf(fp,"%s,%s,%d\n",kitapHead->next->kitapAdi,kitapHead->next->ISBN,i);
        	}
        	else{
        		fprintf(fp,"%s,%s,%d",kitapHead->next->kitapAdi,kitapHead->next->ISBN,i);
			}
			kitapHead = kitapHead->next;
			}
		}
	fclose(fp);
}

void ogrenciYazdir(Ogrenci* ogrenciHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount, Kitap* kitapHead){
	while(ogrenciHead->next != NULL){
		printf("ID : %s Ad : %s Soyad : %s Puan : %d\n",ogrenciHead->next->ogrID,ogrenciHead->next->ad,ogrenciHead->next->soyad,ogrenciHead->next->puan);
		ogrenciHead = ogrenciHead->next;
	}
}

void ogrenciEkle(Ogrenci* ogrenciHead){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	int id;
	Ogrenci* tmp = (Ogrenci*) malloc(sizeof(Ogrenci));
	
	while(ogrenciHead->next != NULL){
		ogrenciHead = ogrenciHead->next;
	}
	printf("Eklemek istediginiz ogrencinin adini giriniz : ");
	scanf("%s",ad);
	printf("Eklemek istediginiz ogrencinin soyadini giriniz : ");
	scanf("%s",soyad);
	tmp->prev = ogrenciHead->next;
	ogrenciHead->next = tmp;
	tmp->next = NULL;
	id = atoi(ogrenciHead->ogrID)+1;
	itoa(id,tmp->ogrID,10);
	strcpy(tmp->ad,ad);
	strcpy(tmp->soyad,soyad);	
	tmp->puan = 100;
}

void ogrenciGuncelle(Ogrenci* ogrenciHead){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	char* id = (char*) malloc(9*sizeof(char));
	int isFind = 0, puan;
	Ogrenci* tmp = ogrenciHead;
	
	printf("Guncellemek istediginiz ogrencinin adini giriniz : ");
	scanf("%s",ad);
	printf("Guncellemek istediginiz ogrencinin soyadini giriniz : ");
	scanf("%s",soyad);
	
	while((ogrenciHead->next != NULL) && (isFind == 0)){
		if((strcmp(ogrenciHead->next->ad,ad)==0) && (strcmp(ogrenciHead->next->soyad,soyad)==0)){
			isFind = 1;
		}
		else{
			ogrenciHead = ogrenciHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Girdiginiz ogrenci bulunamadý");
	}
	
	else{
		printf("Ogrencinin guncel adini giriniz : ");
		scanf("%s",ad);
		printf("Ogrencinin guncel soyadini giriniz : ");
		scanf("%s",soyad);
		printf("Ogrencinin guncel ID'sini giriniz : ");
		scanf("%s",id);
		printf("Ogrencinin guncel puanini giriniz : ");
		scanf("%d",&puan);
		
		strcpy(ogrenciHead->next->ad,ad);
		strcpy(ogrenciHead->next->soyad,soyad);
		strcpy(ogrenciHead->ogrID,id);
		ogrenciHead->puan = puan;
		
	}
}

void ogrenciGoruntule(Ogrenci* ogrenciHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount){
	char* id = (char*) malloc(9*sizeof(char));
	int isFind = 0, i;
	
	printf("Bilgilerini goruntulemek istediginiz ogrencinin ID'sini giriniz : ");
	scanf("%s",id);
	
	while((ogrenciHead->next != NULL) && (isFind == 0)){
		if(strcmp(id,ogrenciHead->next->ogrID)){
			isFind = 1;
		}
		else{
			ogrenciHead = ogrenciHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Girdiginiz ogrenci bulunamadi.");
	}
	
	else{
		printf("ID : %s Ad : %s Soyad : %s Puan : %d\nIslemler",ogrenciHead->next->ogrID,ogrenciHead->next->ad,ogrenciHead->next->soyad,ogrenciHead->next->puan);
		for(i=0; i<*kitapOduncCount; i++){
			if(strcmp(kitapOduncArray[i].ogrID,ogrenciHead->next->ogrID) == 0){
				printf("\nEtiket No : %s Ýslem Tarihi : %d.%d.%d Islem Tipi : ",kitapOduncArray[i].EtiketNo,kitapOduncArray[i].islemTarihi.gun,kitapOduncArray[i].islemTarihi.ay,kitapOduncArray[i].islemTarihi.yil);
				if(kitapOduncArray[i].islemTipi == 0){
					printf("Odunc alindi");
				}
				else if(kitapOduncArray[i].islemTipi == 1){
					printf("Teslim edildi");
				}
			}
		}
	}
}

void ogrenciSil(Ogrenci* ogrenciHead){
	int isFind = 0;
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	
	printf("Silmek istediginiz ogrencinin adini giriniz : ");
	scanf("%s",ad);
	printf("Silmek istediginiz ogrencinin soyadini giriniz : ");
	scanf("%s",soyad);
	
	while((ogrenciHead->next != NULL) && (isFind == 0)){
		if((strcmp(ogrenciHead->next->ad,ad)==0) && (strcmp(ogrenciHead->next->soyad,soyad)==0)){
			isFind = 1;
		}
		else{
			ogrenciHead = ogrenciHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Girdiginiz ogrenci bulunamadi.");
	}
	else{
		ogrenciHead->next = ogrenciHead->next->next;
	}
}

void ogrenciKaydet(Ogrenci* ogrenciHead){
	FILE* fp = fopen("Ogrenciler.csv", "w");
	
	while(ogrenciHead->next != NULL){
		if(ogrenciHead->next->next != NULL){
			fprintf(fp,"%s,%s,%s,%d\n",ogrenciHead->next->ogrID,ogrenciHead->next->ad,ogrenciHead->next->soyad,ogrenciHead->next->puan);
		}
		else{
			fprintf(fp,"%s,%s,%s,%d",ogrenciHead->next->ogrID,ogrenciHead->next->ad,ogrenciHead->next->soyad,ogrenciHead->next->puan);
		}
		ogrenciHead = ogrenciHead->next;
	}
}

void kitapYazarKaydet(KitapYazar* kitapYazarArray, int* kitapYazarCount){
	int i;
	FILE* fp = fopen("KitapYazar.csv", "w");
	
	for(i=0; i<*kitapYazarCount; i++){
		if(i != kitapYazarCount-1){
			fprintf(fp,"%s,%d\n",kitapYazarArray[i].ISBN,kitapYazarArray[i].YazarID);
		}
		else{
			fprintf(fp,"%s,%d",kitapYazarArray[i].ISBN,kitapYazarArray[i].YazarID);
		}
	}	
}

void kitapOduncKaydet(KitapOdunc* kitapOduncArray, int* kitapOduncCount){
	int i;
	FILE* fp = fopen("KitapYazar.csv", "w");
	
	for(i=0; i<*kitapOduncCount; i++){
		if(i != kitapOduncCount-1){
			fprintf(fp,"%s,%s,%d,%d.%d.%d\n",kitapOduncArray[i].EtiketNo,kitapOduncArray[i].ogrID,kitapOduncArray[i].islemTipi,kitapOduncArray[i].islemTarihi.gun,kitapOduncArray[i].islemTarihi.ay,kitapOduncArray[i].islemTarihi.yil);
		}
		else{
			fprintf(fp,"%s,%s,%d,%d.%d.%d",kitapOduncArray[i].EtiketNo,kitapOduncArray[i].ogrID,kitapOduncArray[i].islemTipi,kitapOduncArray[i].islemTarihi.gun,kitapOduncArray[i].islemTarihi.ay,kitapOduncArray[i].islemTarihi.yil);
		}
	}
}

void kitapDurumGuncelle(Kitap* kitapHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount){
	int i, isFind = 0;
	Kitap* tmp;
	KitapOrnek* tmpOrn;
	for(i=0; i<*kitapOduncCount; i++){
		tmp = kitapHead;
		while((isFind == 0) && (tmp->next != NULL)){
			tmpOrn = tmp->next->head;
			while(tmpOrn->next != NULL){
				if(strcmp(kitapOduncArray[i].EtiketNo,tmpOrn->next->EtiketNo) == 0){
					if(kitapOduncArray[i].islemTipi == 0){
						strcpy(tmpOrn->next->Durum,kitapOduncArray[i].ogrID);
					}
				}
				tmpOrn = tmpOrn->next;
			}
			tmp = tmp->next;
		}
	}
}

void oduncAlma(Ogrenci* ogrenciHead, Kitap* kitapHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount, struct tm *now){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	char* kitapAdi = (char*) malloc(30*sizeof(char));
	int isFind = 0, isAny = 0, row = *kitapOduncCount;
	
	printf("Kitap odunc almak istediginiz ogrencinin adini giriniz : ");
	scanf("%s",ad);
	printf("Kitap odunc almak istediginiz ogrencinin soyadini giriniz : ");
	scanf("%s",soyad);
	
	while((ogrenciHead->next != NULL) && (isFind == 0)){
		if((strcmp(ogrenciHead->next->ad,ad)==0) && (strcmp(ogrenciHead->next->soyad,soyad)==0)){
			isFind = 1;
		}
		else{
			ogrenciHead = ogrenciHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Girdiginiz ogrenci bulunamadi.");
	}
	else if(ogrenciHead->next->puan<0){
		printf("Girdiginiz ogrencinin puani kitap almak icin yeterli degildir.");
	}
	else{
		isFind = 0;
		printf("Odunc almak istediginiz kitabin adini giriniz : ");
		scanf("%[^\n]",kitapAdi);
		
		while((kitapHead->next != NULL) && (isFind == 0)){
			if(strcmp(kitapHead->next->kitapAdi,kitapAdi) == 0){
				isFind = 1;
			}
			else{
				kitapHead = kitapHead->next;
			}
		}
		if(isFind == 0){
		printf("Odunc almak istediginiz kitap bulunamadi.");
		}
		else{
			row++;
			kitapOduncArray = realloc(kitapOduncArray,row);
			*kitapOduncCount = row;
			strcpy(kitapOduncArray[row-1].EtiketNo,kitapHead->next->head->next->EtiketNo);
			kitapOduncArray[row-1].islemTarihi.gun = now->tm_mday;
			kitapOduncArray[row-1].islemTarihi.ay = now->tm_mon;
			kitapOduncArray[row-1].islemTarihi.yil = now->tm_year;
			kitapOduncArray[row-1].islemTipi = 0;
		}
	}
}

void teslimEtme(Ogrenci* ogrenciHead, Kitap* kitapHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount, struct tm *now){
	char* ad = (char*) malloc(30*sizeof(char));
	char* soyad = (char*) malloc(30*sizeof(char));
	char* kitapAdi = (char*) malloc(30*sizeof(char));
	int isFind = 0, isAny = 0, row = *kitapOduncCount;
	
	printf("Kitap teslim etmek istediginiz ogrencinin adini giriniz : ");
	scanf("%s",ad);
	printf("Kitap teslim etmek istediginiz ogrencinin soyadini giriniz : ");
	scanf("%s",soyad);
	
	while((ogrenciHead->next != NULL) && (isFind == 0)){
		if((strcmp(ogrenciHead->next->ad,ad)==0) && (strcmp(ogrenciHead->next->soyad,soyad)==0)){
			isFind = 1;
		}
		else{
			ogrenciHead = ogrenciHead->next;
		}
	}
	
	if(isFind == 0){
		printf("Girdiginiz ogrenci bulunamadi.");
	}
	else{
		isFind = 0;
		printf("Odunc almak istediginiz kitabin adini giriniz : ");
		scanf("%[^\n]",kitapAdi);
		
		while((kitapHead->next != NULL) && (isFind == 0)){
			if(strcmp(kitapHead->next->kitapAdi,kitapAdi) == 0){
				isFind = 1;
			}
			else{
				kitapHead = kitapHead->next;
			}
		}
		if(isFind == 0){
		printf("Teslim etmek istediginiz kitap bulunamadi.");
		}
		else{
			row++;
			kitapOduncArray = realloc(kitapOduncArray,row);
			*kitapOduncCount = row;
			strcpy(kitapOduncArray[row-1].EtiketNo,kitapHead->next->head->next->EtiketNo);
			kitapOduncArray[row-1].islemTarihi.gun = now->tm_mday;
			kitapOduncArray[row-1].islemTarihi.ay = now->tm_mon;
			kitapOduncArray[row-1].islemTarihi.yil = now->tm_year;
			kitapOduncArray[row-1].islemTipi = 1;
		}
	}
}

void anaMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now){
	system("CLS");
	int secim;
	void (*menuler[])(Yazar*, Kitap*, Ogrenci*, KitapYazar*, KitapOdunc*, int*, int*, struct tm*) = {ogrenciMenu,kitapMenu,yazarMenu};
	
	printf("******KUTUPHANE ISLEMLERI******\n\n1 - Ogrenci Islemleri\n2 - Kitap Islemleri\n3 - Yazar Islemleri\n0 - Uygulamayi Kapat\n\nSecmek istediginiz islemin numarasini giriniz : ");
	scanf("%d",&secim);
	if(secim == 1){
		(*menuler[0])(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, kitapYazarCount, kitapOduncCount, now);
	}
	if(secim == 2){
		(*menuler[1])(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, kitapYazarCount, kitapOduncCount, now);
	}
	if(secim == 3){
		(*menuler[2])(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, kitapYazarCount, kitapOduncCount, now);
	}
}

void yazarMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now){
	system("CLS");
	int secim;
	void (*yazarIslemleri[])(Yazar*, KitapYazar*, int*, Kitap*) = {yazarEkle,yazarSil,yazarGuncelle,yazarGoruntule,yazarYazdir};
	
	printf("******YAZAR ISLEMLERI******\n\n1 - Yazar Ekle\n2 - Yazar Sil\n3 - Yazar Guncelle\n4 - Yazar Bilgisi Goruntule\n5 - Tum Yazarlari Yazdir\n0 - Bir Ust Menuye Don\n\nSecmek istediginiz islemin numarasini giriniz : ");
	scanf("%d",&secim);
	
	if(secim == 1){
		(*yazarIslemleri[0])(yazarHead, kitapYazarArray, kitapYazarCount, kitapHead);
		yazarKaydet(yazarHead);
	}
	if(secim == 2){
		(*yazarIslemleri[1])(yazarHead, kitapYazarArray, kitapYazarCount, kitapHead);
		yazarKaydet(yazarHead);
	}
	if(secim == 3){
		(*yazarIslemleri[2])(yazarHead, kitapYazarArray, kitapYazarCount, kitapHead);
		yazarKaydet(yazarHead);
		kitapYazarKaydet(kitapYazarArray,kitapYazarCount);
		kitapKaydet(kitapHead);
	}
	if(secim == 4){
		(*yazarIslemleri[3])(yazarHead, kitapYazarArray, kitapYazarCount, kitapHead);
	}
	if(secim == 5){
		(*yazarIslemleri[4])(yazarHead, kitapYazarArray, kitapYazarCount, kitapHead);
	}
	if(secim == 0){
		anaMenu(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, kitapYazarCount, kitapOduncCount, now);
	}
}

void kitapMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now){
	system("CLS");
	int secim;
	void (*kitapYazarIslemleri[])(Kitap*, KitapYazar*, int*, Yazar*) = {kitapEkle,kitapGuncelle,kitapGoruntule,kitapYazdir,kitapYazarEsle};
	void (*kitapIslemleri[])(Kitap*) = {kitapSil,raftaKitapYazdir};
		
	
	printf("******KITAP ISLEMLERI******\n\n1 - Kitap Ekle\n2 - Kitap Sil\n3 - Kitap Guncelle\n4 - Kitap Bilgisi Goruntule\n5 - Tum Kitaplari Yazdir\n6 - Raftaki Kitaplari Yazdir\n7 - Kitap-Yazar Eslestir\n8 - Zamaninda Teslim Edilmeyen Kitaplari Listele\n0 - Bir Ust Menuye Don\n\nSecmek istediginiz islemin numarasini giriniz : ");
	scanf("%d",&secim);
	
	if(secim == 1){
		(*kitapYazarIslemleri[0])(kitapHead, kitapYazarArray, kitapYazarCount, yazarHead);
		kitapKaydet(kitapHead);
	}
	if(secim == 2){
		(*kitapIslemleri[0])(kitapHead);
		kitapKaydet(kitapHead);
	}
	if(secim == 3){
		(*kitapYazarIslemleri[1])(kitapHead, kitapYazarArray, kitapYazarCount, yazarHead);
		yazarKaydet(yazarHead);
		kitapYazarKaydet(kitapYazarArray,kitapYazarCount);
		kitapKaydet(kitapHead);
	}
	if(secim == 4){
		(*kitapYazarIslemleri[2])(kitapHead, kitapYazarArray, kitapYazarCount, yazarHead);
	}
	if(secim == 5){
		(*kitapYazarIslemleri[3])(kitapHead, kitapYazarArray, kitapYazarCount, yazarHead);
	}
	if(secim == 6){
		(*kitapIslemleri[1])(kitapHead);
	}
	if(secim == 7){
		(*kitapYazarIslemleri[4])(kitapHead, kitapYazarArray, kitapYazarCount, yazarHead);
		yazarKaydet(yazarHead);
		kitapYazarKaydet(kitapYazarArray,kitapYazarCount);
		kitapKaydet(kitapHead);
	}
	if(secim == 8){
		teslimEdilmeyenKitaplar(kitapOduncArray, kitapOduncCount, now);
	}
	if(secim == 0){
		anaMenu(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, kitapYazarCount, kitapOduncCount, now);
	}
}

void ogrenciMenu(Yazar* yazarHead, Kitap* kitapHead, Ogrenci* ogrenciHead, KitapYazar* kitapYazarArray, KitapOdunc* kitapOduncArray, int* kitapYazarCount, int* kitapOduncCount, struct tm *now){
	system("CLS");
	int secim;
	void (*ogrenciIslemleri[])(Ogrenci*) = {ogrenciEkle,ogrenciSil,ogrenciGuncelle,cezaliOgrenciler};
	
	printf("******OGRENCI ISLEMLERI******\n\n1 - Ogrenci Ekle\n2 - Ogrenci Sil\n3 - Ogrenci Guncelle\n4 - Ogrenci Goruntule\n5 - Kitap Teslim Etmemis Ogrencileri Goruntule\n6 - Cezali Ogrencileri Listele\n7 - Tum Ogrencileri Yazdir\n8 - Kitap Odunc Alma\n9 - Kitap Teslim Etme\n0 - Bir Ust Menuye Don\n\nSecmek istediginiz islemin numarasini giriniz : ");
	scanf("%d",&secim);
	
	if(secim == 1){
		(*ogrenciIslemleri[0])(ogrenciHead);
		ogrenciKaydet(ogrenciHead);
	}
	if(secim == 2){
		(*ogrenciIslemleri[1])(ogrenciHead);
		ogrenciKaydet(ogrenciHead);
	}
	if(secim == 3){
		(*ogrenciIslemleri[2])(ogrenciHead);
		ogrenciKaydet(ogrenciHead);
	}
	if(secim == 4){
		ogrenciGoruntule(ogrenciHead, kitapOduncArray, kitapOduncCount);
	}
	if(secim == 5){
		teslimEtmeyenOgrenciler(ogrenciHead, kitapOduncArray, kitapOduncCount);
	}
	if(secim == 6){
		(*ogrenciIslemleri[3])(ogrenciHead);
	}
	if(secim == 7){
		ogrenciYazdir(ogrenciHead, kitapOduncArray, kitapOduncCount, kitapHead);
	}
	if(secim == 8){
		oduncAlma(ogrenciHead, kitapHead, kitapOduncArray, kitapOduncCount, now);
		kitapOduncKaydet(kitapOduncArray,kitapOduncCount);
	}
	if(secim == 9){
		teslimEtme(ogrenciHead, kitapHead, kitapOduncArray, kitapOduncCount, now);
		kitapOduncKaydet(kitapOduncArray,kitapOduncCount);
	}
	if(secim == 0){
		anaMenu(yazarHead, kitapHead, ogrenciHead, kitapYazarArray, kitapOduncArray, kitapYazarCount, kitapOduncCount, now);
	}
}

int tarihFarki(struct tm *time1, int gun, int ay, int yil){
	struct tm time2;
	time2.tm_year = yil - 1900;
    time2.tm_mon = ay - 1;
    time2.tm_mday = gun;
    time2.tm_hour = 17;
    time2.tm_min = 0;
    time2.tm_sec = 0;
    time_t t2 = mktime(&time2);
	time_t t1 = mktime(time1);
	
	double diff = difftime(t1, t2);
	
	if(diff > 1209600){
		return 1;
	}
	else{
		return 0;
	}
}

void teslimEdilmeyenKitaplar(KitapOdunc* kitapOduncArray, int* kitapOduncCount, struct tm* now){
	int i;
	for(i=0; i<*kitapOduncCount; i++){
		if(kitapOduncArray[i].islemTipi == 0){
			if(tarihFarki(now, kitapOduncArray[i].islemTarihi.gun, kitapOduncArray[i].islemTarihi.ay, kitapOduncArray[i].islemTarihi.yil) == 1){
				printf("Etiket no : %s\n",kitapOduncArray[i].EtiketNo);
			}
		}
	}
}

void teslimEtmeyenOgrenciler(Ogrenci* ogrenciHead, KitapOdunc* kitapOduncArray, int* kitapOduncCount){
	int i;
	Ogrenci* tmp;
	for(i=0; i<*kitapOduncCount; i++){
		tmp = ogrenciHead;
		if(kitapOduncArray[i].islemTipi == 0){
			while(tmp->next != NULL){			
				if(strcmp(tmp->next->ogrID,kitapOduncArray[i].ogrID) == 0){
					printf("ID : %s Ad : %s Soyad : %s Puan : %d\n",tmp->next->ogrID,tmp->next->ad,tmp->next->soyad,tmp->next->puan);
				}
				tmp = tmp->next;				
			}
		}
	}
}

void cezaliOgrenciler(Ogrenci* ogrenciHead){
	while(ogrenciHead->next != NULL){
		if(ogrenciHead->next->puan<0){
			printf("ID : %s Ad : %s Soyad : %s Puan : %d\n",ogrenciHead->next->ogrID,ogrenciHead->next->ad,ogrenciHead->next->soyad,ogrenciHead->next->puan);
		}
		ogrenciHead = ogrenciHead->next;
	}
}
