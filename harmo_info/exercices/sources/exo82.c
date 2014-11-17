#include <stdio.h>
#include <string.h>
FILE *file;
const int WORD_MAX_LENGTH=26;
const int WORD_MAX_NUMBER=338088;
typedef char Word[WORD_MAX_LENGTH];
Word dico[WORD_MAX_NUMBER];

int main() {
    char word[WORD_MAX_LENGTH];
    // ouverture du fichier : mettre a jour le chemin !
    file=fopen("/home/colin/module/a43/dico.txt","ro");
    if (!file) fprintf(stderr,"pb ouverture du fichier !");
    // affectation des mots du fichier au tableau
    int i;
    for(i = 0; i<WORD_MAX_NUMBER; i++) {
        fscanf(file, "%s",word);
        strcpy(dico[i],word);
        printf("%s\n", dico[i]);
    }

    return 0;
}
