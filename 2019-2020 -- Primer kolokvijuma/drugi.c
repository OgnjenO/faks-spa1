#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define new(x) x=(Rec*)malloc(sizeof(Rec));
#define newString(x,y) x=(char*)malloc(y*sizeof(char));

typedef struct _rec
{
    char *kljuc;
    int broj;
    struct _rec *sl;
} Rec;

void Ispisi(Rec *glava)
{
    if(glava == NULL)
    {
        printf("Lista je prazna\n");
        return;
    }
    Rec *pom;
    pom = glava;
    printf("=========================\n");
    while(pom != NULL)
    {
        printf("%d - %s\n", pom->broj, pom->kljuc);
        pom = pom->sl;
    }
    printf("=========================\n");
    return;
}

Rec* Get(Rec *glava, char *kljuc)
{
    if(glava == NULL) return NULL;
    Rec *pom = glava;
    while(pom != NULL)
    {
        if(strcmp(pom->kljuc, kljuc) == 0)
        {
            return pom;
        }
        pom = pom->sl;
    }

    return NULL;
}

Rec* Set(Rec *glava, char *kljuc)
{
    Rec *nov;
    new(nov);
    newString(nov->kljuc, strlen(kljuc));
    strcpy(nov->kljuc, kljuc);
    nov->broj = 1;
    nov->sl = NULL;
    if(glava == NULL)
    {
        printf("Prazna lista => ubacam na prvo mesto\n");
        return nov;
    }
    Rec *pom;
    printf("Trazim ga u listi\n");
    pom = glava;
    if(strcmp(pom->kljuc, kljuc) == 0)
    {
        printf("Vec je u listi => uvecavam broj za 1\n");
        pom->broj++;
        return glava;
    }
    while(pom->sl != NULL)
    {
        if(strcmp(pom->sl->kljuc, kljuc) == 0)
        {
            printf("Vec je u listi => uvecavam broj za 1\n");
            pom->sl->broj++;
            return glava;
        }
        pom = pom->sl;
    }
    
    printf("Nema ga u listi => ubacam ga na pocetku\n");
    pom->sl = nov;
    return glava;
}

Rec* Form(Rec *glava)
{
    printf("Unesite N : ");
    int n;
    scanf("%d", &n);
    int i;
    char kljuc[100];
    for(i=0; i<n; i++)
    {
        printf("Unesite rec #%d : ", i+1);
        scanf("%s", kljuc);
        printf("Ubacam '%s'\n", kljuc);
        glava = Set(glava, kljuc);
    }
    return glava;
}

Rec* Izbaci(Rec *glava, int koliko)
{
    Rec *pom, *pom2;
    while(glava->broj == koliko)
    {
        pom = glava->sl;
        free(glava);
        glava = pom;
    }
    pom = glava;
    while(pom->sl != NULL)
    {
        if(pom->sl->broj == koliko)
        {
            pom2 = pom->sl->sl;
            free(pom->sl);
            pom->sl = pom2;
        }
        else 
        {
            pom = pom->sl;
        }
    }
    return glava;
}

int main()
{
    Rec *glava = NULL;
    glava = Form(glava);
    printf("Lista : \n");
    Ispisi(glava);
    glava = Izbaci(glava, 1);
    Ispisi(glava);
}