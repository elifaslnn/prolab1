#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>

struct FilePaths{
    char paths[50][50];
};

struct FilePaths filepaths;
int sumtextfiles=0;


struct Etiketler{
    char parantezsiz[50][50];
    int counts[40];
};

struct Etiketler etiketler;
int sumtickets=0;


struct YetimEtiketler
{
    char parantezsiz[50][50];
    int counts[25];
};

struct YetimEtiketler yetimetiketler;
int sumyetimler=0;


struct  DuzEtiketler
{
    char parantezsiz[50][50];
    char paths[50][50];
    int counts[25];
};

struct DuzEtiketler duzetiketler;
int sumduzetiketler=0;


struct IstenenEtiketler
{
    char parantezsiz[50][50];
    int counts[25];
};

struct IstenenEtiketler istenenetiketler;
int sumistenenler;

void etiketleri_sinifla()
{
    //dosya yollarını ayıklayıp prolab\Universite\Bolumler\Bilgisayar Nuhendisligi.txt ---> Bilgisayar Muhendisligi
    char dosyayollariadlari[50][50];
    for (int i = 0; i < sumtextfiles ; i++){
        //son "/" adresi ve son "." adresi arası kalan kısmı ayıklayalım
        char temp_dosya_yolu[50];
        strcpy(temp_dosya_yolu,filepaths.paths[i]);
        //printf("temp %s",temp_dosya_yolu);
        char *p_ilk=strrchr(temp_dosya_yolu,'/');
        char *p_path=temp_dosya_yolu;
        int ilk_indis=p_ilk-p_path+1;//20
        //printf("ilk indis %d\n",ilk_indis);
        int toplamkarakter=strlen(temp_dosya_yolu);//50
        //printf("toplam karakter %d",toplamkarakter);
        char gecici_tutsun[50]={};//20-50-4 arası
        int indis=0;
        for (int j = ilk_indis  ; j < toplamkarakter-4 ; j++ )
        {
            //printf("%c",filepaths.paths[i][j]);
            gecici_tutsun[indis]=temp_dosya_yolu[j];
            indis++;
        }
        //gecici_tutsun[indis]='\0';
        char oylesine[50];
        strcpy(oylesine,gecici_tutsun);
        strcpy(dosyayollariadlari[i],oylesine);
    }
        //duplicate ve etiket sayıları
    int size=sumtickets;
    int k=0,n=1;
    int count[25]={};
    for(int q=0; q<size; q++){
        n=1;
        for(int w=q+1; w<size; w++){      
            if(strcmp(etiketler.parantezsiz[q],etiketler.parantezsiz[w])==0){
                for(k=w;k<size-1;k++){
                    strcpy(etiketler.parantezsiz[k],etiketler.parantezsiz[k+1]);
                }
            n++;
            size--;
            w--;
            }  
    count[q]= n;
    etiketler.counts[q]=n;
            } 
    }
    int tut=0;
    while (count[tut]!=0){
        tut++;
    }
    //duplicate olamayan yeni etiket listesi olustu ve eleman sayısı hesaplandı

    sumtickets=tut;

    //printf("son sumtickets %d\n",sumtickets);
    // for (size_t e = 0; e < sumtickets; e++)
    // {
    //     printf("________%d defa  %s gecmis \n",count[e],etiketler.parantezsiz[e]);
    // }
    
    //dosya yolları adları toplandı parantezsiz etiketlerle kontrol etme ve yeni structlara yerleştirme zamanı
    int temp1=0;
    int temp2=0;
    int temp3=0;
    for (int z = 0; z < sumtickets; z++) // etiketleri dosya yolları isimleri arasında tek tek döndürücez
    {
        for (int x = 0; x < sumtextfiles; x++)
        {
            if((strcmp(etiketler.parantezsiz[z] , dosyayollariadlari[x]))==0){ //etiket == txt adı ise duzetiket
                strcpy(duzetiketler.parantezsiz[temp1] , etiketler.parantezsiz[z]);
                duzetiketler.counts[temp1] = etiketler.counts[z];
                temp1++;
            }
        }  
    }
    sumduzetiketler=temp1;

    for ( int x = 0; x < sumtickets; x++)
    {
        int try1=0;
        for (int y = 0; y < sumtextfiles; y++)
        {
            if((strcmp(etiketler.parantezsiz[x] , dosyayollariadlari[y]))!=0){ 
                try1++;
            }
            if(try1==sumtextfiles  && strlen(etiketler.parantezsiz[x])>1){
                strcpy(yetimetiketler.parantezsiz[temp2] , etiketler.parantezsiz[x]);
                yetimetiketler.counts[temp2]=etiketler.counts[x];
                temp2++;
            }
        } 
    }
    sumyetimler=temp2;     

    for (int c = 0; c < sumtextfiles; c++)//istenilen etiket dosyası olup dosyalar arasında [[etiket]] formatında bulunmayan
    {
        int try=0;
        for (int v = 0; v < sumtickets; v++)
        {
            if((strcmp(dosyayollariadlari[c],etiketler.parantezsiz[v]))!=0){
                try++;
            }
            if(try==sumtickets && strlen(dosyayollariadlari[c])>3){
                strcpy(istenenetiketler.parantezsiz[temp3] , dosyayollariadlari[c]);
                temp3++;
            }
        }  
    }
    sumistenenler=temp3;   
}

void etiketleri_bulurmusun()
{
    int count=0;
    for(size_t i=0; i<sumtextfiles;i++){
        FILE *fp=fopen(filepaths.paths[i],"r");

        char string[400];
        while (fgets(string, 400, fp) != NULL){
            int lenghtsatir=strlen(string);
            int i,j;
            
            //printf("%s\n",string);
            for(i = 0 ; i < lenghtsatir ; i++) {
                j=0;
                char parantezli[50];
                char parantezsiz[50];
                while(string[i]=='[' && string[i+1]== '[' && string[j+i]!=']' && string[i+j+1]!=']'){
                    j++;
                }
                if(j!=0){
                    int k,m=0;
                    for( k = i+2 ; k<j+i+1 ; k++){
                        parantezsiz[m]=string[k];
                        m++;
                    }
                    parantezsiz[m]='\0';
                    strcpy(etiketler.parantezsiz[count] , parantezsiz);
                    //printf("%d. %s\n",count,etiketler.parantezsiz[count]);
                    count++;
                }
            }

        }
        fclose(fp);
    }
    sumtickets=count;
}

void kelime_arama(char s[50])
{   
    for(int o=0; o<sumtextfiles; o++){ //dosya uzantılarını tek tek alıp dosyaları açıyoruz
        FILE *fp=fopen(filepaths.paths[o],"r");
        int satir_sayisi=0;
        char satir[200];
        while (fgets(satir, 200, fp) != NULL){//açılan dosyaları satır satır okuma
            int count=0;
            char *ptr=strstr(satir,s);

            satir_sayisi++;
            //printf("\n%d. satir: %s\n", satir_sayisi, satir);
            while(ptr!=NULL){
                count++;
                ptr=strstr(ptr+1,s);
            }
            if(count>=1){
                printf("\n%s\n",filepaths.paths[o]);
                printf("\n%d. satirda %d kere geciyor\n",satir_sayisi,count); 
                printf("\n%d. satir: %s\n", satir_sayisi,satir);
            }
        }
        fclose(fp);
    }
}

void dosyada_gezinme(char path[300])
{
    char path_2[300];
    struct dirent *entry;
    DIR *directory=opendir(path);
    char string[300];
    FILE *fp;

    if(directory==NULL){
    const char ch='.';
    char *ret;
    ret=strrchr(path,ch);
    const char *cp=".txt";

    if(strcmp(ret,cp)==0)
    {
        //printf("%s\n",path);
        strcpy((filepaths.paths[sumtextfiles]),path);
        sumtextfiles++;
        //printf("sumoftextfiles : %d\n",sumtextfiles);
        fp=fopen(path,"r");
        if(fp==NULL){
           printf("dosya yok\n");
        }else{
           //kelime_arama(fp,string,s);
           //printf("dosya var\n");
        } 
    }
    }else{
    while((entry=readdir(directory))!= NULL)
    {
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
        {
            strcpy(path_2,path);
            strcat(path_2,"/");
            strcat(path_2,entry->d_name);
            dosyada_gezinme(path_2);
        }
    }  
    closedir(directory);
   }
}

void output_olustur()
{
    FILE *fp1=fopen("output.txt","w");    
    int i=0;
    for( i=0;i<sumtickets;i++)
    {
    fprintf(fp1,"%d\t \t%s\n",etiketler.counts[i],etiketler.parantezsiz[i]); 
    }
    fprintf(fp1,"\nYetim Etiketler\n-------------\n");

    for(i=0;i<sumyetimler;i++)
    {
    fprintf(fp1,"%s\n",yetimetiketler.parantezsiz[i]);
    }
    fprintf(fp1,"\nİstenen Etiketler\n-------------\n");
    for(i=0;i<sumistenenler;i++)
    {
    fprintf(fp1,"%s\n",istenenetiketler.parantezsiz[i]);
    }

    fclose(fp1);
}

void dersdosyasiolustur(char uzanti[100], int derskodu, char isitiket[30] )
{
    FILE *fp=fopen(uzanti,"w");
        fprintf(fp,"Dersin Kodu : %d\nDersin Adı : %s\nDers İçeriği : ",derskodu,isitiket);
        fclose(fp);
        free(fp);
}

void etiket_dosyasi_islemleri()
{
    char input[25]={};
    printf("olusturmak istediginiz txt dosyasini giriniz : ");
    scanf("%s",input);
    char isim[20];
    char isitiket[25]={};
    strcpy(isim,input);
    strcat(isitiket,"[[");
    strcat(isitiket,isim);
    strcat(isitiket,"]]");
    strcat(isim,".txt");
        int i,j;
        char *tempdosyayolu;
        char uzanti[40]={};
        int derskodu=199;
        for(i=0;i<sumtextfiles;i++){
            char *ptr1=strstr(filepaths.paths[i],"Dersler");
            char *ptr2=strstr(filepaths.paths[i],"dersler");
            if(ptr1!=NULL || ptr2!=NULL){ //7
                //printf("%s\n",filepaths.paths[i]);
                strcpy(tempdosyayolu,filepaths.paths[i]);
                //printf("%s\n",tempdosyayolu);
                if(ptr1!=NULL){
                    char *ptr3=strstr(tempdosyayolu,"Dersler");
                    char yeniyul[40]={};
                    strcpy(yeniyul,tempdosyayolu);
                    int sinir=*ptr3-*tempdosyayolu;
                    //printf("sinir %d \n",sinir);
                    for ( j = 0; j <sinir-1 ; j++){
                        uzanti[j]=yeniyul[j];
                    }
                    strcat(uzanti,isim);
                    derskodu++;
                    //dersdosyasiolustur(uzanti,derskodu,isitiket);
                }
                if(ptr2!=NULL){
                    char *ptr4=strstr(tempdosyayolu,"Dersler");
                    char yeniyol[40]={};
                    strcpy(yeniyol,tempdosyayolu);
                    int sinir=*ptr4-*tempdosyayolu;
                    //printf("sinir %d \n",sinir);
                    for ( j = 0; j <sinir-1 ; j++){
                        uzanti[j]=yeniyol[j];
                    }
                    strcat(uzanti,isim);
                    derskodu++;
                    //dersdosyasiolustur(uzanti,derskodu,isitiket);
                }
            }
        }
        //printf(" %s\n",uzanti);
        //strcat(uzanti,isim);
        //printf("%s\n",uzanti);
        dersdosyasiolustur(uzanti,derskodu,isitiket);
}
    
void etiket_degissin()
{
    //eski ve yeni etiketleri al
    char eski[25]={};
    char temp[25]={};
    printf("degistirmek istediginiz etiket adini giriniz : ");
    scanf("%s",temp);
    strcat(eski,"[[");
    strcat(eski,temp);
    strcat(eski,"]]");

    char yeni[25]={};
    char temp1[25]={};
    printf("degistirmek istediginiz etiket adini giriniz : ");
    scanf("%s",temp1);
    strcat(yeni,"[[");
    strcat(yeni,temp1);
    strcat(yeni,"]]");
    char yenitxt[25];
    strcpy(yenitxt,temp1);
    strcat(yenitxt,".txt");
    // etiketin gectigi dosya yollarını tespit et
    int i;
    char tempdosyayolu[50];
    char *ptr1;
    for (i = 0; i < sumduzetiketler; i++){
        ptr1=strstr(duzetiketler.paths[i],temp);
        if(ptr1!=NULL){
            strcpy(tempdosyayolu,duzetiketler.paths[i]);
        }
    }
    // yeni etiket icin dosya oluştur eski etiketi oku
    FILE *eski_file=fopen(tempdosyayolu,"r");
    FILE *yeni_file=fopen(yenitxt,"w");

    // eski dosyayi  satir satir okumaya başla
    char satir[300];
    while(fgets(satir,300,eski_file)!=NULL)
    {
        yerlerini_degistir(satir,eski,yeni); // yer değiştirme işlemleri
        fputs(satir,yeni_file); // yer değiştirdikten sonra yenisine yerleştirme
    }
    fclose(eski_file);
    fclose(yeni_file);
    remove(tempdosyayolu);
    rename(yenitxt, tempdosyayolu);
}

void yerlerini_degistir(char *satir , const char *eski, const char *yeni)
{
    char *pozisyon;
    char tempsatir[300];
    int indis=0;
    int leneski;
    leneski=strlen(eski);
    // eski ve yeni etiket aynı olmamalı sonsuz döngüye girer
    if(strcmp(eski,yeni)==0){
        return;
    }
    while ((pozisyon=strstr(satir,eski)) != NULL)
    {
        strcpy(tempsatir,satir);// anlık satırın yedeği
        indis=pozisyon-satir;//anlık bulunan kelimenin indisi
        satir[indis] = '\0'; // yeni kelime ile string kaynaşır
        strcat(satir,yeni);// satrın kalan kelimeleri ile yeni kelimeleri işlenir
        strcat(satir,tempsatir + indis + leneski);
    }
}

void etiketlerinyolari()
{
    int i,j;
    char temptut[50];
    for(i=0; i< sumtextfiles; i++){
        for ( j = 0; j < sumduzetiketler ; j++){
            char *ptr1=strstr(filepaths.paths[i],duzetiketler.parantezsiz[j]);
            if(ptr1!=NULL){
                strcpy(duzetiketler.paths[j] ,filepaths.paths[i]);
            }
        }
    }
}

void yazdir()
{
}

int arayuz()
{
    printf("+____________________________________+\n");
    printf("     PROLAB 1 - Proje 1     \n\nDokuwiki\nHangi islemi yapmak istersiniz?\n");
    printf("1)Arama yapmak  icin 1 giriniz\n");
    printf("2)output.txt yazdirmak icin 2 giriniz\n");
    printf("3)guncelleme ekleme cikarmam icin 3 giriniz\n");
    printf("4)programi sonlandirmak icin 4 giriniz\n");
    printf("secim : ");
    int secim;
    scanf("%d",&secim);
    return secim;
}

int main()
{
    setlocale(LC_ALL,"Turkish");
    char path[10]=".";
    dosyada_gezinme(path); 
    etiketleri_bulurmusun();
    etiketleri_sinifla();
    output_olustur();
    etiketlerinyolari();
    while (1)
    {
        int secim;
        int k;
        secim=arayuz();
        printf("secim %d\n",secim);
        if (secim==1){ // arama yapmak buradan etiket mi kelime mi sorgusu yapılsın
           printf("\nYETIM ETIKETLER\n");
            for (k = 0; k < sumyetimler ; k++)
            {
                printf("%d) %s \n",k+1,yetimetiketler.parantezsiz[k]);
            }
            printf("\nISTENEN ETIKETLER\n");
            for ( k = 0; k < sumistenenler; k++)
            {
                printf("%d) %s\n",k+1,istenenetiketler.parantezsiz[k]);
            }
            printf("-------------------------\n");
            int hangisi;
            printf("\nKelime aramak icin 1 etiket aramak icin 2 giriniz :");
            scanf("%d",&hangisi);
            char arama[25];
            if(hangisi==1){
                printf("aradiginiz kelimeyi giriniz : ");
                scanf("%s",arama);
                kelime_arama(arama);
            }
            else if(hangisi==2){
                printf("aradiginiz etiketi giriniz : ");
                scanf("%s",arama);
                char aramatiket[30]={};
                strcat(aramatiket,"[[");
                strcat(aramatiket,arama);
                strcat(aramatiket,"]]");
                printf("aramatiket %s\n",aramatiket);
                kelime_arama(aramatiket);
            }
            
        }
        else if(secim==2){ //output.txt yazdıralım ( etiketler ve sayıları )
            printf("\nOUTPUT.TXT YAZDIRILDI GUNCELLENDI\n");
            output_olustur();
        }
        else if (secim==3){ // güncelleme kısmı henüz nasıl olacak bilmiyorum
            printf("Etiket adi degistirmek ve etikete ait txt adini degistirmek icin 1 giriniz\n");
            printf("Yetim etikete txt dosyasi olusturmak icin 2 giriniz\n ");
            printf("secim : ");
            int hangisi;
            scanf("%d",&hangisi);
            if (hangisi==1){ // etiketin dosya yolunu bul rename() system() falan kullan ve kelime arama ile tum txtlerden değiştir 
                for (int i = 0; i < sumduzetiketler ; i++)//txtlerden değiştirdikten sonra guncelle her şeyi
                {
                    printf("%d) %s\n",i+1,duzetiketler.parantezsiz[i]);
                }
                printf("\n");
                etiket_degissin();
            }
            else if (hangisi==2)//inputa uygun txt dosyası yarat güncelle fonksiyonlarla
            {
                for (int i = 0; i < sumyetimler ; i++)
                {
                    printf("%d) %s\n",i+1,yetimetiketler.parantezsiz[i]);
                }
                printf("\n");
                etiket_dosyasi_islemleri();
                dosyada_gezinme(path); 
                etiketleri_bulurmusun();
                etiketleri_sinifla();
                output_olustur();
            }
        }
        else if (secim==4){ //prpgramı sonladıralım
            break;
        }
        else{ // invalid input
            printf("\ntekrar giris yapiniz !!\n");
        }
    }    
}

//YAPILACAKLAR KELİME ARAMA EKLENSİN - DOSYAYA YAZDIRMA YAPSIN - ARAYÜZ YAPILSIN

// GÜNCELLEME YAPSIN