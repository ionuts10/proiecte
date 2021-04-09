#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMCERINTA 5

typedef struct Jucator Jucator;
typedef struct Echipa Echipa;
typedef struct Meci Meci;
typedef struct CoadaMeciuri CoadaMeciuri;


struct Jucator
{
    char *nume, *prenume;
    int xp;
};

struct Echipa
{
    char *nume;
    int nr_jucatori;
    float punctaj;
    Jucator *jucator;
    Echipa *urm;
};

struct Meci
{
    Echipa *echipa1;
    Echipa *echipa2;
    Meci *urm;
};

struct CoadaMeciuri
{
    Meci *inceput;
    Meci *sfarsit;
};

/*Crearea unei noi echipe*/
Echipa* adaugare_echipa()
{
    Echipa *echipa_noua;
    echipa_noua = (Echipa*)malloc(sizeof(Echipa));
    echipa_noua->urm = NULL;
    return echipa_noua;
}

/*Citirea din fisier a numelui unei echipe*/
char*  nume_echipa(FILE *fisier)
{
    char *nume;
    char litera, buffer[100];

    int count = 0;

    litera = fgetc(fisier);  //citirea primei litere
    while(litera != '\n')
    {
        buffer[count] = litera;
        count++;
        litera = fgetc(fisier);
    }
    buffer[count] = '\0';

    nume = (char*)malloc(sizeof(char) * (count + 1));
    strcpy(nume, buffer);

    return nume;
}

/*Citirea din fisier a numelui unui jucator*/
char* nume_jucator(FILE *fisier)
{
    char *nume;
    char litera, buffer[100];

    int count = 0;

    litera = fgetc(fisier);
    while(litera != ' ' && litera != '\n')
    {
        buffer[count] = litera;
        count++;
        litera = fgetc(fisier);
    }
    buffer[count] = '\0';

    nume = (char*)malloc(sizeof(char) * (count + 1));
    strcpy(nume, buffer);

    return nume;
}

/*Citirea din fisier a prenumelui unui jucator*/
char* prenume_jucator(FILE *fisier)
{
    char *prenume;
    char litera, buffer[100];

    int count = 0;

    litera = fgetc(fisier);
    while(litera != ' ' && litera != '\n')
    {
        buffer[count] = litera;
        count++;
        litera = fgetc(fisier);
    }
    buffer[count] = '\0';

    prenume = (char*)malloc(sizeof(char) * (count + 1));
    strcpy(prenume, buffer);

    return prenume;
}

/*Creez lista de echipe si returnez pointerul la primul element.*/
Echipa* creare_lista(FILE *fisier)
{
    Echipa *cap = NULL, *copie_echipa, *echipa_noua;
    if(fisier)
    {
        int nr_echipe, i, j;
        fscanf(fisier, "%d", &nr_echipe);

        // Crearea si citirea datelor primei echipe
        cap = adaugare_echipa();
        fscanf(fisier, "%d ", &cap->nr_jucatori);
        cap->nume = nume_echipa(fisier);
        cap->punctaj = 0;

        cap->jucator = (Jucator*)malloc(sizeof(Jucator) * cap->nr_jucatori);
        for(i = 0; i < cap->nr_jucatori; i++)
        {
            cap->jucator[i].nume = nume_jucator(fisier);
            cap->jucator[i].prenume = prenume_jucator(fisier);
            fscanf(fisier, "%d\n", &cap->jucator[i].xp);
            cap->punctaj += cap->jucator[i].xp;

        }
        cap->punctaj /= cap->nr_jucatori;

        // Citirea datelor celorlalte echipe si a jucatorilor acestora
        copie_echipa = cap;
        for(i = 2; i <= nr_echipe; i++)
        {
            echipa_noua = adaugare_echipa();
            fscanf(fisier, "%d ", &echipa_noua->nr_jucatori);
            echipa_noua->nume = nume_echipa(fisier);
            echipa_noua->punctaj = 0;

            echipa_noua->jucator = (Jucator*)malloc(sizeof(Jucator) * echipa_noua->nr_jucatori);
            for(j = 0; j < echipa_noua->nr_jucatori; j++)
            {
                echipa_noua->jucator[j].nume = nume_jucator(fisier);
                echipa_noua->jucator[j].prenume = prenume_jucator(fisier);
                fscanf(fisier, "%d\n", &echipa_noua->jucator[j].xp);
                echipa_noua->punctaj += echipa_noua->jucator[j].xp;
            }
            echipa_noua->punctaj /= echipa_noua->nr_jucatori;

            copie_echipa->urm = echipa_noua;
            copie_echipa = echipa_noua;
        }
    }
    return cap;
}

/*Afisarea recursiva a listei in fisierul de rezultate*/
void afisare_lista(Echipa *cap, FILE *fisier)
{
    if(cap != NULL)
    {
        fprintf(fisier, " %s\n", cap->nume);
        afisare_lista(cap->urm, fisier);
    }
}

/*Determinarea numarului cel mai apropiat de numarul de echipe care este si putere a lui 2*/
int determinare_nr(int nr_echipe)
{
    int nr_cautat = 1;
    while((nr_cautat * 2) <= nr_echipe)
    {
        nr_cautat *= 2;
    }
    return nr_cautat;
}

/*Functie pentru numararea echipelor dintr-o lista*/
int numarare_echipe(Echipa *cap)
{
    int nr_echipe = 0;
    Echipa *p;
    p = cap;
    for(p = cap; p != NULL; p = p->urm, nr_echipe++);
    return nr_echipe;
}

/*Functie pentru determinarea punctajului minim dintr-o lista*/
float punctaj_minim(Echipa *cap)
{
    Echipa *copie = cap;
    float minim = copie->punctaj;

    while(copie->urm != NULL)
    {
        copie = copie->urm;
        if(copie->punctaj < minim)
        {
            minim = copie->punctaj;
        }
    }
    return minim;
}

void eliberare_memorie(Echipa *echipa)
{
    int i;

    for(i = 0; i < echipa->nr_jucatori; i++)
    {
        free(echipa->jucator[i].nume);
        free(echipa->jucator[i].prenume);
    }
    free(echipa->jucator);
    free(echipa->nume);
    free(echipa);
}

/*Functie pentru eliminare a elementului succesor dintr-o lista*/
void eliminare_succesor(Echipa *predecesor)
{
    Echipa *succesor = predecesor->urm;

    predecesor->urm = succesor->urm;
    eliberare_memorie(succesor);
}

/* Fucntie pentru inversarea listei */
void reverse(Echipa **cap)
{
    Echipa *current = *cap;
    Echipa *prev = NULL, *next = NULL;

    while (current != NULL)
    {
        next = current->urm;
        current->urm = prev;
        prev = current;
        current = next;
    }
    *cap = prev;
}




/*Functie pentru eliminarea echipelor astfel incat numarul acestora sa ajunga
la valoarea determinata de functia determinare_nr*/
void selectionare_echipe(Echipa **cap)
{
    Echipa *index = *cap, *aux;
    Echipa *predecesor = NULL;
    int nr_echipe = numarare_echipe(*cap);
    int nr_nou = determinare_nr(nr_echipe);
    float minim = punctaj_minim(*cap);

    while(nr_nou != nr_echipe)
    {
        minim = punctaj_minim(*cap);

        if(index == NULL)
        {
            predecesor = NULL;
            index = *cap;
        }

        if((*cap)->punctaj == minim)
        {
            aux = *cap;
            *cap = (*cap)->urm;
            eliberare_memorie(aux);
            predecesor = NULL;
            index = *cap;
            nr_echipe--;
        }
        else if(index->punctaj == minim)
        {
            eliminare_succesor(predecesor);   
            index = predecesor->urm;   
            nr_echipe--;
        }
        else
        {
            predecesor = index;
            index = index->urm;
        }   
    }
}



CoadaMeciuri* initializare_coada()
{
    CoadaMeciuri *coada;
    coada = (CoadaMeciuri*)malloc(sizeof(CoadaMeciuri));
    if(coada)
    {
        coada->inceput = coada->sfarsit = NULL;
        return coada;
    }
    return NULL;
}

void enQueue(CoadaMeciuri *coada, Echipa *e1, Echipa *e2)
{
    Meci *meci_nou;

    meci_nou = (Meci*)malloc(sizeof(Meci));
    meci_nou->echipa1 = e1;
    meci_nou->echipa2 = e2;
    meci_nou->urm = NULL;

    if(coada->sfarsit == NULL)
    {
        coada->sfarsit = meci_nou;
    }
    else
    {
        (coada->sfarsit)->urm = meci_nou;
        (coada->sfarsit) = meci_nou;
    }
    if(coada->inceput == NULL)
    {
        coada->inceput = coada->sfarsit;
    }
}


void creare_coada(CoadaMeciuri *coada, Echipa *cap, FILE *fisier)
{
    while(cap != NULL)
    {
        enQueue(coada, cap, cap->urm);
        cap = cap->urm->urm;
    }
}

int is_queue_empty(CoadaMeciuri *coada)
{
    return (coada->inceput == NULL);
}

void deQueue(CoadaMeciuri *coada, Echipa **e1, Echipa **e2)
{
    Meci *meci;

    if(!is_queue_empty(coada))
    {
        meci = coada->inceput;
        *e1 = meci->echipa1;
        *e2 = meci->echipa2;
        coada->inceput = coada->inceput->urm;
        free(meci);
    }
}


void afisare_coada(Meci *meci, FILE *fisier)
{
    if(meci != NULL)
    {
        fprintf(fisier, " %-24s --  %24s\n", meci->echipa1->nume, meci->echipa2->nume);
        afisare_coada(meci->urm, fisier);
    }
   
}

void stergere_coada(CoadaMeciuri *coada)
{
    Meci *temp;
    while(!is_queue_empty(coada))
    {
        temp = coada->inceput;
        coada->inceput = (coada->inceput)->urm;
        free(temp);
    }
    free(coada);
}

void push(Echipa **varf, Echipa *echipa)
{
    Echipa *echipa_noua = (Echipa*)malloc(sizeof(Echipa));

    echipa_noua->nume = echipa->nume;
    echipa_noua->nr_jucatori = echipa->nr_jucatori;
    echipa_noua->punctaj = echipa->punctaj;
    echipa_noua->jucator = echipa->jucator;

    echipa_noua->urm = *varf;
    *varf = echipa_noua;
}

int is_stack_empty(Echipa *varf)
{
    return varf == NULL;
}

Echipa* pop(Echipa **varf)
{
    if(is_stack_empty(*varf))
        return NULL;

    Echipa *temp = *varf;

    *varf = (*varf)->urm;
    return temp;
}


void stergere_stiva(Echipa **varf)
{
    Echipa *temp;
    while((*varf) != NULL)
    {
        temp = *varf;
        *varf = (*varf)->urm;
        free(temp);
    }
}

void jucare_meciuri(CoadaMeciuri *coada, Echipa **varf1, Echipa **varf2, FILE *fisier)
{
    if(!is_queue_empty(coada))
    {
        afisare_coada(coada->inceput, fisier);

        Echipa *e1, *e2;
        int nr_meciuri = 0;

        while(!is_queue_empty(coada))
        {
            deQueue(coada, &e1, &e2);
            if(e1->punctaj >= e2->punctaj)
            {
                e1->punctaj = e1->punctaj + 1;
                push(varf1, e1);
                push(varf2, e2);
            }
            else
            {
                e2->punctaj = e2->punctaj + 1;
                push(varf1, e2);
                push(varf2, e1);
            }
           
        }
        while(!is_stack_empty(*varf1))
        {
            e1 = pop(varf1);
            e2 = pop(varf1);

            nr_meciuri++;

            fprintf(fisier, " %-24s --- %.2f\n", e1->nume, e1->punctaj);
            fprintf(fisier, " %-24s --- %.2f\n", e2->nume, e2->punctaj);

            enQueue(coada, e1, e2);
        }
        stergere_stiva(varf1);
        stergere_stiva(varf2);
        if(nr_meciuri == 1)
        {
            fprintf(fisier, " %-24s --  %24s\n", e1->nume, e2->nume);
            if(e1->punctaj >= e2->punctaj)
            {
                e1->punctaj = e1->punctaj + 1;
                fprintf(fisier, " %-24s --- %.2f\n", e1->nume, e1->punctaj);

            }
            else
            {
                e2->punctaj = e2->punctaj + 1;
                fprintf(fisier, " %-24s --- %.2f\n", e2->nume, e2->punctaj);
            }
        }
        else
        {
            jucare_meciuri(coada, varf1, varf2, fisier);
        }
    }
}

int main(int argc, char *argv[])
{
    // Initializare fisiere
    FILE *fisier_cerinta, *fisier_date, *fisier_rezultate;
    fisier_cerinta = fopen(argv[1], "rt");
    fisier_date = fopen(argv[2], "rt");
    fisier_rezultate = fopen(argv[3], "wt");
    int i;


    // Citire cerinta
    int *cerinta = (int*)malloc(sizeof(int) * (DIMCERINTA+1));

    for(i = 1; i <= DIMCERINTA; i++)
    {
        fscanf(fisier_cerinta, "%d", &cerinta[i]);
    }


    // Rezolvare cerinta
    //Echipa *cap_echipe = inversare_lista(creare_lista(fisier_date));
    Echipa *cap_echipe = creare_lista(fisier_date);
    reverse(&cap_echipe);

    CoadaMeciuri *coada_meciuri = initializare_coada();
    Echipa *varf_stiva_castigatori = NULL, *varf_stiva_invinsi = NULL;

    for(i = 1; i <= DIMCERINTA; i++)
    {
        if(i == 2)
        {
            if(cerinta[i] == 0)
            {
                afisare_lista(cap_echipe, fisier_rezultate);
            }
            else
            {
                selectionare_echipe(&cap_echipe);
                afisare_lista(cap_echipe, fisier_rezultate);
            }
        }
        else if(i == 3)
        {
            if(cerinta[i] == 1)
            {
                creare_coada(coada_meciuri, cap_echipe, fisier_rezultate);
                jucare_meciuri(coada_meciuri, &varf_stiva_castigatori, &varf_stiva_invinsi, fisier_rezultate);
            }
        }
        else if(i == 4)
        {
            if(cerinta[i] == 1)
            {
                ;
            }
        }
        else if(i == 5)
        {
            if(cerinta[i] == 1)
            {
                ;
            }
        }
    }


    // Inchidere fisiere si eliberare memorie
    free(cerinta);
    fclose(fisier_cerinta);
    fclose(fisier_date);
    fclose(fisier_rezultate);
   
    return 0;
}