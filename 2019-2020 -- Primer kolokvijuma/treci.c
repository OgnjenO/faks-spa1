#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define newKorisnik(x) x=(Korisnik*)malloc(sizeof(Korisnik));
#define newKorisnici(x,y) x=(Korisnik*)malloc(y*sizeof(Korisnik));
#define newPar(x) x=(Par*)malloc(sizeof(Par));
#define newParovi(x,y) x=(Par*)malloc(y*sizeof(Par));
#define newString(x,y) x=(char*)malloc(y*sizeof(char));
#define new(a, b, c, d) a=(b)malloc(c*sizeof(d))

typedef struct _korisnik
{
    char *ime;
    int broj;
    char *grupe[100];
} Korisnik;

typedef struct _par
{
    char *ime;
    char *grupa;
} Par;

void IspisiParove(Par *parovi, int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("#%d - %s  --  %s\n", i+1, parovi[i].ime, parovi[i].grupa);
    }
}

void IspisiKorisnike(Korisnik *korisnici, int n)
{
    printf("=========================\n");
    int i,j;
    for(i=0; i<n; i++)
    {
        printf("-------------------------\n");
        printf("#%d\n", i+1);
        printf("Ime : %s\n", korisnici[i].ime);
        printf("Broj grupa : %d\n", korisnici[i].broj);
        printf("Grupe : \n");
        for(j=0; j<korisnici[i].broj; j++)
        {
            printf("\t%s\n", korisnici[i].grupe[j]);
        }
    }
    printf("=========================\n");
}

Par* UnosKorisnika(int *broj)
{
    FILE *fin;
    fin = fopen("IMIVibe.txt", "r");
    int n;
    fscanf(fin, "%d", &n);
    Par *parovi;
    newParovi(parovi, n);
    int i;
    char ime[100];
    char grupa[100];
    fgets(ime, 100, fin); // Preskace \n koji se nalazi nakon prvog broja u fajlu
    for(int i=0; i<n; i++)
    {
        fgets(ime, 100, fin);
        strtok(ime, "\n"); // Brise \n sa kraja
        fgets(grupa, 100, fin);
        strtok(grupa, "\n"); // Brise \n sa kraja
        printf("Ubacam %s - %s\n", ime, grupa);
        newString(parovi[i].ime, strlen(ime));
        strcpy(parovi[i].ime, ime);
        newString(parovi[i].grupa, strlen(grupa));
        strcpy(parovi[i].grupa, grupa);
    }
    fclose(fin);
    *broj = n;
    return parovi;
}

Korisnik* Transform(Par *parovi, int brparova, int *brkorisnika)
{
    Korisnik *korisnici;
    newKorisnici(korisnici, brparova);
    int i,j,n;
    n = 0;
    for(int i=0; i<brparova; i++)
    {
        printf("\nUbacam %s - %s\n", parovi[i].ime, parovi[i].grupa);
        printf("Proveravam da li je korisnik sa imenom '%s' vec u listi\n", parovi[i].ime);
        for(j=0; j<n; j++)
        {
            if(strcmp(korisnici[j].ime, parovi[i].ime) == 0)
            {
                printf("Vec je u listi => Ubacam grupu u listu grupa\n");
                newString(korisnici[j].grupe[korisnici[j].broj], strlen(parovi[i].grupa));
                strcpy(korisnici[j].grupe[korisnici[j].broj], parovi[i].grupa);
                korisnici[j].broj++;
                break;
            }
        }
        if(j==n)
        {
            printf("Nije u list => Ubacam ga u listu i dodajem mu grupu\n");
            newString(korisnici[j].ime, strlen(parovi[i].ime));
            strcpy(korisnici[j].ime, parovi[i].ime);
            korisnici[j].broj = 0;
            newString(korisnici[j].grupe[korisnici[j].broj], strlen(parovi[i].grupa));
            strcpy(korisnici[j].grupe[korisnici[j].broj], parovi[i].grupa);
            korisnici[j].broj++;
            n++;
        }
    }

    *brkorisnika = n;
    return korisnici;
}

int main()
{
    Par *parovi;
    int brparova;
    parovi = UnosKorisnika(&brparova);
    IspisiParove(parovi, brparova);

    Korisnik *korisnici;
    int brkorisnika;
    korisnici = Transform(parovi, brparova, &brkorisnika);
    IspisiKorisnike(korisnici, brkorisnika);
}