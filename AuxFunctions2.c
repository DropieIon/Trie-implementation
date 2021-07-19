#include "AuxFunctions2.h"
void AfisLexicografica(Node radacina, char *carte_sau_autor, FILE *out)
{
    if(radacina != NULL && radacina->sfarsit == 1)
    {
        fprintf(out, "%s\n", carte_sau_autor);
        if(ArboreVid(radacina) == 1)
        {
            return;
        }
        
    }
    
    int i;
    for(i = 0; i < DIM_ALPHABET; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            char carte_sau_autor_copie[100];
            strcpy(carte_sau_autor_copie, carte_sau_autor);
            strncat(carte_sau_autor_copie, &ALPHABET[i], 1);
            AfisLexicografica(radacina->copii[i], carte_sau_autor_copie, out);
        }
    }
}

void AC3(Node radacina, char *carte_sau_autor, int *nr_afisari, FILE *out)
{
    // Functie afisare chei 3
    // Afiseaza primele 3 chei in ordine lexicografica
    if(*nr_afisari == 3)
    {
        return;
    }
    
    if(radacina != NULL && radacina->sfarsit == 1)
    {
        fprintf(out, "%s\n", carte_sau_autor);
        (*nr_afisari)++;
        if(ArboreVid(radacina) == 1)
        {
            return;
        }
        
    }
    
    int i;
    for(i = 0; i < DIM_ALPHABET; i++)
    {
        if(*nr_afisari == 3)
            break;
        if(radacina->copii[i] != NULL)
        {
            char carte_sau_autor_copie[50];
            strcpy(carte_sau_autor_copie, carte_sau_autor);
            strncat(carte_sau_autor_copie, &ALPHABET[i], 1);
            AC3(radacina->copii[i], carte_sau_autor_copie, nr_afisari, out);
        }
    }
}

void search_autocomplete(Node radacina, char *prefix, FILE *out, short c_sau_a)
{
    // varibila c_sau_a are rolul de a verifica daca
    // se doreste cautarea unui autor sau a unei carti
    // si ia valoarea 0 pentru carte si 1 pentru autor
    int lungime  = strlen(prefix), nivel, index;
    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(prefix[nivel]);
        if(!santinela->copii[index])
        {
            if(c_sau_a == 0)
            {
                fprintf(out, "No books have been found.\n");
            }
            else
            {
                fprintf(out, "No author has been found.\n");
            }
            return;
        }
        santinela = santinela->copii[index];
    }
    int nr_afisari = 0;
    AC3(santinela, prefix, &nr_afisari, out);
}

void list_author(Node radacina, char *autor, FILE *out)
{
    int lungime = strlen(autor), index, nivel;
    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(autor[nivel]);
        if(!santinela->copii[index])
        {
            fprintf(out, "The author %s isn't part of your recomandations.\n", autor);
            return;
        }
        santinela = santinela->copii[index];
    }
    if(santinela != NULL && santinela->sfarsit == 1)
    {
        char carte[100] = "";
        Node arbore_carti = *(Node *)santinela->info;
        AfisLexicografica(arbore_carti, carte, out);
    }
}

void search_by_author(Node radacina, char *autor, char *carte, FILE *out)
{
    int lungime = strlen(autor), index, nivel;
    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(autor[nivel]);
        if(!santinela->copii[index])
        {
            fprintf(out, "The author %s isn't part of your recomandations.\n", autor);
            return;
        }
        santinela = santinela->copii[index];
    }
    if(santinela != NULL && santinela->sfarsit == 1)
    {
        Node arbore_carti = *(Node *)santinela->info;
        short exista = 0;
        Carte book1 = search_book(arbore_carti, carte, &exista);
        if (exista == 0)
        {
            fprintf(out, "The book %s isn't present in your recomandations.\n", carte);
        }
        else
        {
            fprintf(out, "Recomandation info:: %s, %s, %d, %d\n",
            carte, book1.autor, book1.rating, book1.pagini);
        }
    }

}

void search_by_author_autocomplete(Node radacina, char *carte, char *autor, FILE *out)
{
    int lungime = strlen(autor), index, nivel;
    Node santinela = radacina;
    for(nivel = 0; nivel < lungime; nivel++)
    {
        index = PozitieCaracter(autor[nivel]);
        if(!santinela->copii[index])
        {
            fprintf(out, "The author %s isn't part of your recomandations.\n", autor);
            return;
        }
        santinela = santinela->copii[index];
    }
    if(santinela != NULL && santinela->sfarsit == 1)
    {
        carte[strlen(carte) - 1] = '\0';
        Node radacina_carti = *(Node *)santinela->info;
        search_autocomplete(radacina_carti, carte, out, 0);
    }
}