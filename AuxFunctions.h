#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM_ALPHABET (68)
#define ALPHABET ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ")
typedef struct arbore
{
    void *info; 
    // folosit pentru a ii atribui ultimului nod
    // un pointer catre un alt arbore sau catre 
    // structura Carte
    short sfarsit;
    struct arbore *copii[DIM_ALPHABET];
    
}*Node , Cel;

typedef struct carte
{
    char titlu[50];
    char autor[50];
    int rating;
    int pagini;
}Carte;


void inserare_autor(Node radacina, char *autor, char *carte, Carte book);
void inserare_carte(Node radacina, char *carte, Carte book);
int PozitieCaracter(char c);
Node Alocare();
Carte search_book(Node radacina, char *titlu, short *rezultat);
short ArboreVid(Node radacina);
short Cine_E_Autorul(Node radacina, char *carte, char *autor);