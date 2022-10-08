#include <stdio.h>
#include <stdlib.h>
//#include <file.h>
#include <string.h>

#define DOSYA_YOLU "bil_muh/bilgisayar_muh_giris/bilmuh.txt"

int main()
{
    FILE *fp;
    char buf[100];

    fp = fopen(DOSYA_YOLU, "r");
    if (fp == NULL)
        printf("dosya yok");
    else
    {
        int satir_sayisi=0;
        while (fgets(buf, 100, fp) != NULL)
        {
            satir_sayisi++;
            printf("%d. satir: \"%s\"\n", satir_sayisi, buf);
        }
    }
}