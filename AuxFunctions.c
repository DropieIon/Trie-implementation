#include "AuxFunctions.h"

Node Alocare()
{
    Node aux = NULL;
    aux = (Node)malloc(sizeof(Cel));
    if(!aux)
    {
        printf("Nu s-a putut aloca memorie pentru noul nod.\n");
        return NULL;
    }
    
    int i;
    aux->sfarsit = 0;
    for(i = 0; i < DIM_ALPHABET; i++)
    {
        aux->copii[i] = NULL;
    }
    aux->info = NULL;
    return aux;
}

int PozitieCaracter(char c)
{
    if(c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    if(c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 26;
    }
    if(c >= '0' && c <= '9')
    {
        return c - '0' + 52;
    }
    int i;
    for(i = 61; i < DIM_ALPHABET; i++)
    {
        if(c == ALPHABET[i])
        {
            return i;
        }
    }
    return 1;
}

short ArboreVid(Node radacina)
{
    int i;
    if(radacina == NULL)
    {
        return 1;
    }
    for(i = 0; i < DIM_ALPHABET; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            return 0;
        }
    }
    return 1;
}

short Cine_E_Autorul(Node radacina, char *carte, char *autor)
{
    // primeste ca parametrii radacina arborelui de carti
    // intoarce 1 daca autorul exista si 0 in caz contrar
    int lungime = strlen(carte), index, nivel;
    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(carte[nivel]);
        if(!santinela->copii[index])
        {
            return 0;
        }
        santinela = santinela->copii[index];
    }
    if(!santinela->info)
    {
        return 0;
    }
    Carte book = *(Carte *)santinela->info;
    strcpy(autor, book.autor);
    return 1;
}

void inserare_carte(Node radacina, char *carte, Carte book)
{
    int nivel;
    int lungime = strlen(carte);
    int index;

    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(carte[nivel]);
        if(!santinela->copii[index])
        {
            santinela->copii[index] = Alocare();
        }
        santinela = santinela->copii[index];
    }
    santinela->sfarsit = 1;
    if(!santinela->info)
    {
        // cartea nu exista in arbore
        santinela->info = malloc(sizeof(Carte));
        memcpy(santinela->info, &book, sizeof(Carte));
    }
}

void inserare_autor(Node radacina, char *autor, char *carte, Carte book)
{
    int nivel;
    int lungime = strlen(autor);
    int index;
    short autorul_nu_exista = 0;

    Node santinela = radacina;

    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(autor[nivel]);
        if(!santinela->copii[index])
        {
            santinela->copii[index] = Alocare();
        }
        santinela = santinela->copii[index];
    }
    santinela->sfarsit = 1;
    Node santinela_carte;
    if(!santinela->info)
    {
        santinela->info = malloc(sizeof(Cel));
        santinela_carte = Alocare();
        autorul_nu_exista = 1;
    }
    else
    {
        santinela_carte = *(Node *)santinela->info;
    }
    
    inserare_carte(santinela_carte, carte, book);
    
    if(autorul_nu_exista == 1)
    {
        memcpy(santinela->info, &santinela_carte, sizeof(Cel));
    }
}

Carte search_book(Node radacina, char *titlu, short *rezultat)
{
    int lungime = strlen(titlu);
    int index;
    int nivel;
    Carte book;
    strcpy(book.titlu ,"Nu e aceasta!");
    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(titlu[nivel]);
        if(!santinela->copii[index])
        {
            *rezultat = 0;
            return book;
        }
        santinela = santinela->copii[index];
    }
    if(santinela != NULL && santinela->sfarsit == 1)
    {
        *rezultat = 1;
        book = *(Carte *)santinela->info;
        return book;
    }
    else 
    {
        *rezultat = 0;
        return book;
    }
    return book;
    
}