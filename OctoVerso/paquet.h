#pragma once
#include "joueur.h"
#include "time.h"

enum {
    NB_LETTRES_DISTINCTES = 21,
    // MAX_CARTES doit être la somme exacte des occurrences ci-dessous (9+1+2+3+14+1+1+5+7+1
    // +5+3+6+5+7+6+7+6+5+1+2 = 97) : c'est la taille réelle du paquet, utilisée pour allouer
    // son tampon. Une valeur trop petite ici provoquait un dépassement de tas (heap overflow)
    // dans initPaquet, qui remplissait bien plus de cases que le tampon n'en réservait.
    MAX_CARTES = 97,
};

typedef struct {
    int nombre;
    char lettre;
} Lettre;

typedef struct {
    char* chevalet;
    int reste;
} Paquet;

const static Lettre lettre[NB_LETTRES_DISTINCTES] = {
    {9, 'A'},
    {1, 'B'},
    {2, 'C'},
    {3, 'D'},
    {14,'E'},
    {1, 'F'},
    {1, 'G'},
    {5, 'H'},
    {7, 'I'},
    {1, 'J'},
    {5, 'L'},
    {3, 'M'},
    {6, 'N'},
    {5, 'O'},
    {7, 'P'},
    {6, 'Q'},
    {7, 'R'},
    {6, 'S'},
    {5, 'T'},
    {1, 'U'},
    {2, 'V'},
};

/**
 * @brief Initialise un paquet de lettres selon les fr�quences de chaque lettre.
 * @param[out] p L'adresse du paquet � initialiser.
 */
void initPaquet(Paquet* p);

/**
 * @brief M�lange les lettres dans le paquet de mani�re al�atoire.
 * @param[in,out] p Le paquet � m�langer.
 */
void melangerPaquet(Paquet* p);

/**
 * @brief Distribue des lettres aux joueurs � partir du paquet.
 * @param[in,out] p Le paquet de lettres.
 * @param[in,out] j Le joueur � qui distribuer les lettres.
 */
void distribuerPaquet(Paquet* p, Joueur* j);

/**
 * @brief D�termine quel joueur a le mot le plus faible.
 * @param[in] j1 Le premier joueur.
 * @param[in] j2 Le second joueur.
 * @return L'indice du joueur ayant le mot le plus faible (0 ou 1).
 */
int determinerPremierJoueur(Joueur* j1, Joueur* j2);

/**
 * @brief Affiche l'�tat actuel du paquet.
 * @param[in] p Le paquet � afficher.
 */
void afficherPaquet(Paquet* p);

/**
 * @brief Affiche la situation actuelle du jeu (mains des joueurs et rails).
 * @param[in] j1 Le premier joueur.
 * @param[in] j2 Le second joueur.
 * @param[in] r Le rail � afficher.
 */
void afficherSituation(Joueur* j1, Joueur* j2, Rail* r);

/**
 * @brief Pioche une lettre du paquet.
 * @param[in,out] p Le paquet � partir duquel la lettre est pioch�e.
 * @return La lettre pioch�e.
 * @pre Le paquet ne doit pas �tre vide.
 */
char piocherLettreduPaquet(Paquet* p);

/**
 * @brief Retire une lettre du paquet.
 * @param[in,out] p Le paquet � modifier.
 * @param[in] lettre La lettre � retirer.
 */
void retirerLettrePaquet(Paquet* p, char lettre);

/**
 * @brief V�rifie si le paquet est vide.
 * @param[in] p Le paquet � v�rifier.
 * @return 1 si le paquet est vide, 0 sinon.
 */
int estVidePaquet(Paquet* p);

/**
 * @brief Permet � un joueur d'�changer une lettre avec le paquet.
 * @param[in,out] j Le joueur qui �change une lettre.
 * @param[in,out] p Le paquet avec lequel le joueur �change.
 */
void echangeChevalet(Joueur* j, Paquet* p);
