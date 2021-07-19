#include "AuxFunctions.h"

void AfisLexicografica(Node radacina, char *carte_sau_autor, FILE *out);
void list_author(Node radacina, char *autor, FILE *out);
void search_autocomplete(Node radacina, char *prefix, FILE *out, short c_sau_a);
void AC3(Node radacina, char *carte_sau_autor, int *nr_afisari, FILE *out);
void search_by_author_autocomplete(Node radacina, char *carte, char *autor, FILE *out);
void search_by_author(Node radacina, char *autor, char *carte, FILE *out);
void FreeTree(Node *radacina);