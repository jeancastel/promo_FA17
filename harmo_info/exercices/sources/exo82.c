#include <stdio.h>
#include <string.h>
FILE *file;
const int WORD_MAX_LENGTH = 26;
const int WORD_MAX_NUMBER = 336531;

typedef char Word[26];
Word dico[338088];

int main() {
    int res = 0;
    int nb_pal = 0;

    char word[WORD_MAX_LENGTH];
    // ouverture du fichier : mettre a jour le chemin !
    file = fopen("sources/dico.txt","ro");
    if (!file) fprintf(stderr,"pb ouverture du fichier !");
    // affectation des mots du fichier au tableau
    int i;
    for(i = 0; i < WORD_MAX_NUMBER; i++) {
        fscanf(file, "%s",word);
        strcpy(dico[i],word);
    }
    for(i = 0; i < WORD_MAX_NUMBER; i++) {
        if(cherchepal(dico[i], strlen(dico[i])) == 1){
            nb_pal++;
            printf("%d : %s\n", nb_pal, dico[i]);
        }
    }

    printf("Nombre de palindrome : %d\n", nb_pal);
    return 0;
}

int cherchepal(char* mot, int taille_mot) {
    int i;
    int palindrome = 0;

    for(i = 0; i < taille_mot; i++) {
        if(mot[i] == mot[(taille_mot-1) - i]){
            palindrome = 1;
        }else {
            return 0;
        }
    }

    return 1;
}
