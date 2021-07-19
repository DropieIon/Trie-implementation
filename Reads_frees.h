/* Ciubotaru Ion 312CB */

#include "AuxFunctions2.h"

void StergeDinArboreAutori(Node *radacina, char *autor, char *autor_copie, char *carte, short *trebuie_sters, short *afisare_eroare, FILE *out);
int StergeCheieDinArbore(Node *radacina, char *cheie, char *cheie_copie, short *afisare_eroare, FILE *out);
void EliberareCarti(Node *radacina);
void EliberareAutori(Node *radacina);
void PrelucrareProgram(FILE *in, FILE *out, size_t MAX, char *line, Node *radacina_carti, Node *radacina_autori);