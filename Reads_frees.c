#include "Reads_frees.h"

int DeleteKey(Node *root, char *cheie, char *cheie_copie, short *afisare_eroare, FILE *out)
{
     if (*root == NULL) {
        return 0;
    }

    if (*cheie)
    {
        int index = PozitieCaracter(cheie[0]);
        if(!(*root)->copii[index])
        {
            fprintf(out, "The book %s isn't present in your recomandations.\n", cheie_copie);
            return 0;
        }
        if (*root != NULL && (*root)->copii[index] != NULL &&
            DeleteKey(&((*root)->copii[index]), cheie + 1, cheie_copie, afisare_eroare, out) &&
            (*root)->sfarsit == 0)
        {

            // se intra in cazul in care ne aflam intr-un Node care nu se alfa la final
            // si se doreste stergerea acestuia
            if (ArboreVid(*root))
            {
                free(*root);
                (*root) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    
    if (*cheie == '\0' && (*root)->sfarsit)
    {
        if (ArboreVid(*root))
        {
            free((*root)->info);
            free(*root);
            (*root) = NULL;
            return 1;
        }
        else 
        {
            // marcam cartea ca nefiind parte din arbore
            free((*root)->info);
            (*root)->info = NULL;
            (*root)->sfarsit = 0;
            
            return 0;
        }
    }
    if(*cheie == '\0' && (*root)->sfarsit == 0)
    {
        // in cazul in care a fost stearsa deja dar se doreste stergerea ei din nou
        // Datorita faptului ca functia ar intra in acest if cat timp sirul de 
        // caractere "cheie" este null, avem nevoie de o variabila pe care o
        // trimitem ca parametru si care retine daca s-a afisat sau nu mesajul
        // Aceasta variabila ia valoarea 1 daca trebuie afisat mesajul, 0 in caz contrar

        if(*afisare_eroare == 1)
        {
            *afisare_eroare = 0; 
            fprintf(out, "The book %s isn't present in your recomandations.\n", cheie_copie);
        
        }
        return 0;
    }
 
    return 0;
}

void StergeDinArboreAutori(Node *root, char *autor, char *autor_copie, char *carte, short *trebuie_sters, short *afisare_eroare, FILE *out)
{
    if((*root)->sfarsit == 1)
    {
        Node *arbore_carti = (Node *)(*root)->info;
        char carte_copie[50];
        strcpy(carte_copie, carte);
        DeleteKey(arbore_carti, carte, carte_copie, afisare_eroare, out);
        if(ArboreVid(*arbore_carti) == 1)
        {
            free(*arbore_carti);
            *trebuie_sters = 1;
        }
        return;
    }
    if(*autor)
    {
        int index = PozitieCaracter(autor[0]);
        StergeDinArboreAutori(&((*root)->copii[index]), autor + 1, autor_copie, carte, trebuie_sters, afisare_eroare, out);
    }
    else
    {
        return;
    }
    
}

void EliberareCarti(Node *root)
{
    if(!*root)
    {
        return;
    }
    int i;
    for(i = 0; i < DIM_ALPHABET; i++)
    {
        if((*root)->copii[i])EliberareCarti(&((*root)->copii[i]));
    }
    if((*root)->sfarsit == 1)
    {
        free((*root)->info);
    }
    free(*root);
}

void EliberareAutori(Node *root)
{
    int i;
    for(i = 0; i < DIM_ALPHABET; i++)
    {
        if((*root)->copii[i])
        {
            EliberareAutori(&((*root)->copii[i]));
        }
    }
    if((*root)->sfarsit == 1)
    {
        Node *root_carti = (Node *)(*root)->info;
        EliberareCarti(root_carti);
        free((*root)->info);
    }
    free(*root);
}

void PrelucrareProgram(FILE *in, FILE *out, size_t MAX, char *line, Node *root_carti, Node *root_autori)
{
    char comanda[30];
    Carte book;
    char titlu[50];
    int i;
    while (!feof(in))
    {
        memset(line, 0, MAX + 1);
        getline(&line, &MAX, in);
        // eliminam caracterul "New line" de la sfarsitul sirului
        line[strcspn(line, "\n")] = 0;
        if(strlen(line) < 6)
        {
            break;
        }
        for(i = 0; line[i] != ' '; i++)
        {
            // ia comanda din linie
            comanda[i] = line[i];
        }
        comanda[i] = '\0';
        char *token = strtok(line + i +1, ":");
        if(strcmp(comanda, "add_book") == 0)
        {
            strcpy(book.titlu, token);
            token = strtok(NULL, ":");
            strcpy(book.autor, token);
            token = strtok(NULL, ":");
            book.rating = atoi(token);
            token = strtok(NULL, ":");
            book.pagini = atoi(token);
            inserare_autor(*root_autori, book.autor, book.titlu, book);
            inserare_carte(*root_carti, book.titlu, book);
        }
        else if(strcmp(comanda, "search_book") == 0)
        {
            strcpy(titlu, line + i +1);
            titlu[strlen(titlu)] = '\0';
            if(titlu[strlen(titlu) - 1] == '~')
            {
                // Testez cazul in care se doreste accesarea functiei de autocomplete
                titlu[strlen(titlu) - 1] = '\0';
                search_autocomplete(*root_carti, titlu, out, 0);
                continue;
            }
            short exista;
            Carte book1 = search_book(*root_carti, titlu, &exista);
            if(exista == 0)
            {
                fprintf(out, "The book %s isn't present in your recomandations.\n", titlu);
            }
            else
            {
                fprintf(out, "Recomandation info:: %s, %s, %d, %d\n", 
                titlu, book1.autor, book1.rating, book1.pagini);
            }

        }
        else if(strcmp(comanda, "list_author") == 0)
        {
            char autor[100];
            strcpy(autor, line + i + 1);
            autor[strlen(autor)] = '\0';
            if(autor[strlen(autor) - 1] == '~')
            {
                // Testez cazul in care se doreste accesarea functiei de autocomplete
                autor[strlen(autor) - 1] = '\0';
                search_autocomplete(*root_autori, autor, out, 1);
            }
            else
            {
                list_author(*root_autori, autor, out);
            }
            
           
        }
        else if(strcmp(comanda, "search_by_author") == 0)
        {
            char autor[100];
            strcpy(autor, token);
            char carte[50];
            if(autor[strlen(autor) - 1] == '~')
            {
                autor[strlen(autor) - 1] = '\0';
                search_autocomplete(*root_autori, autor, out, 1);
            }
            else
            {
                token = strtok(NULL, ":");
                strcpy(carte, token);
                if(carte[strlen(carte) - 1] == '~')
                {
                    search_by_author_autocomplete(*root_autori, carte, autor, out);
                }
                else
                {
                    search_by_author(*root_autori, autor, carte, out);
                }
                
            }
            
        }
        else if(strcmp(comanda, "delete_book") == 0)
        {
            char carte[50];
            strcpy(carte, line + i + 1);
            char carte_copie[50];
            strcpy(carte_copie, carte);
            char autor[50];
            short exista = Cine_E_Autorul(*root_carti, carte, autor);
            short afisare_eroare = 1;
            DeleteKey(root_carti, carte, carte_copie, &afisare_eroare, out);
            if(exista == 1)
            {
                char autor_copie[50];
                strcpy(autor_copie, autor);
                short trebuie_sters = 0;
                StergeDinArboreAutori(root_autori, autor, autor_copie, carte, &trebuie_sters, &afisare_eroare, out);
                if(trebuie_sters == 1)
                {
                    DeleteKey(root_autori, autor, autor_copie, &afisare_eroare, out);
                }
            }
        }
        

    }
}
