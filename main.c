#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_MANCHES 10
#define NUM_COULEURS 6

enum Couleur {
    Rouge = 1,
    Bleu,
    Vert,
    Jaune,
    Orange,
    Violet
};

// Fonction generer_combi qui va créer un tableau combinaison et ajouter 4 nombres aléatoires entre 1 et 6.

void generer_combi(int *combinaison)
{
    bool deja_pris[NUM_COULEURS] = {false};
    int i, couleur;
    for (i = 0; i < 4; i++)
    {
        do {
            couleur = rand() % NUM_COULEURS + 1;
        } while (deja_pris[couleur - 1]);
        deja_pris[couleur - 1] = true;
        combinaison[i] = couleur;
    }
}

// Fonction afficher qui va afficher la combinaison de couleur avec des lettres pour les couleurs.

void afficher(int *combinaison)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        switch (combinaison[i])
        {
            case Rouge:
                printf("R ");
                break;
            case Bleu:
                printf("B ");
                break;
            case Vert:
                printf("V ");
                break;
            case Jaune:
                printf("J ");
                break;
            case Orange:
                printf("O ");
                break;
            case Violet:
                printf("I ");
                break;
        }
    }
}

// Fonction saisir qui va demander à l'utilisateur de saisir une combinaison de 4 couleurs.

void saisir(int *proposition)
{
    int i;
    enum Couleur couleur;
    for (i = 0; i < 4; i++)
    {
        printf("Saisir une couleur (R, B, V, J, O, I) : ");
        scanf_s("%d", &couleur);
        proposition[i] = couleur;
    }
}

// Fonction comparer qui va comparer la combinaison et la proposition de l'utilisateur.

void comparer(int *combinaison, int *proposition, int *resultat)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (combinaison[i] == proposition[i])
        {
            resultat[i] = 1;
        }
        else
        {
            resultat[i] = 0;
        }
    }
}

// Fonction afficher_resultat qui va afficher le résultat de la comparaison.
void rangement(int *combinaison, int *proposition, int *resultat) {
    int i, j;
    int bien_places = 0, mal_places = 0;
    bool combinaison_utilisee[4] = {false};

    // Trouver les valeurs bien placées
    for (i = 0; i < 4; i++) {
        if (combinaison[i] == proposition[i]) {
            bien_places++;
            resultat[i] = 1;
            combinaison_utilisee[i] = true;
        }
    }

    // Trouver les valeurs mal placées
    for (i = 0; i < 4; i++) {
        if (!combinaison_utilisee[i]) {
            for (j = 0; j < 4; j++) {
                if (i != j && !combinaison_utilisee[j] && combinaison[i] == proposition[j]) {
                    mal_places++;
                    combinaison_utilisee[j] = true;
                    break;
                }
            }
        }
    }

    // Afficher le résultat
    if (bien_places > 0) {
        printf("%d - B ", bien_places);
    }
    if (mal_places > 0) {
        printf("%d - M ", mal_places);
    }
    if (bien_places == 0 && mal_places == 0) {
        printf("0 ");
    }
}

// Fonction main qui va appeler les fonctions précédentes.
int main()
{
    srand(time(NULL));
    int combinaison[4];
    int proposition[4];
    int resultat[4];
    int i;
    int gagne = 0;
    const int manche = 10; // Constante pour le nombre de manches
    generer_combi(combinaison);
    for (i = 0; i < manche; i++)
    {
        saisir(proposition);
        comparer(combinaison, proposition, resultat);
        rangement(combinaison, proposition, resultat);
        if (resultat[0] == 1 && resultat[1] == 1 && resultat[2] == 1 && resultat[3] == 1)
        {
            printf("Vous avez gagné !");
            gagne = 1;
            break;
        }
    }
    if (gagne == 0)
    {
        printf("Vous avez perdu ! La combinaison était : ");
        afficher(combinaison);
    }
    system("pause");
    return 0;
}
