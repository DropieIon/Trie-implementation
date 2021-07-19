#include "Reads_frees.h"

int main(int argc, char **argv)
{
    Node root_authors = Alocare();
    Node root_books = Alocare();
    if(argc != 3)
    {
        printf("Usage:\n \t -> main file_input file_output\n");
        return 1;
    }
    char *fisier_in = argv[1];
    char *fisier_out = argv[2];
    FILE *in = fopen(fisier_in, "r");
    FILE *out = fopen(fisier_out, "w");
    size_t MAX = 100;
    
    
    char *line;
    line = (char *)malloc(sizeof(char)* (MAX + 1));
    memset(line, 0, MAX + 1);
    PrelucrareProgram(in, out, MAX, line, &root_books, & root_authors);
    
    free(line);
    EliberareAutori(&root_authors);
    EliberareCarti(&root_books);
    fclose(in);
    fclose(out);
    return 0;
}