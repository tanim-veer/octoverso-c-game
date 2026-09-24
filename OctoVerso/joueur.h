#pragma once
#include "rail.h"

enum {
	CHEVALETS = 12,        // lettres distribuées à chaque joueur en début de partie
	CAPACITE_MAIN = 80,    // une main grossit (tuiles reçues, pioches) : au plus 88 tuiles - 8 sur le rail
	MOT4 = 5,
	MOT_MAX = TAILLE_RAIL + 1,
};

typedef struct {
	char* chevalet;        // CAPACITE_MAIN cases, ' ' = case vide
	int reste;             // nombre de lettres en main
	char mot[MOT4];        // mot d'ouverture
} Joueur;

/**
 * @brief Initialise un joueur avec une main vide.
 * @param[out] j Le joueur à initialiser.
 */
void initJoueur(Joueur* j);

/**
 * @brief Libère la mémoire de la main du joueur.
 * @param[in,out] j Le joueur.
 */
void libererJoueur(Joueur* j);

/**
 * @brief Vérifie que toutes les lettres de `mot` sont dans la main (chaque tuile ne sert qu'une fois).
 * @return 1 si le joueur possède toutes les lettres, 0 sinon.
 */
int mainContientMot(const Joueur* j, const char* mot);

/**
 * @brief Joue le mot d'ouverture (4 lettres de la main, présent dans le dictionnaire).
 * @param[in,out] j Le joueur.
 * @param[in] saisie Le mot saisi (majuscules ou minuscules).
 * @return 1 si le mot est accepté, 0 sinon.
 */
int jouerMotOuverture(Joueur* j, const char* saisie);

/**
 * @brief Joue un coup "R (AB)CDE" ou "R CDE(AB)" (R ou V selon la face du rail).
 * Les lettres entre parenthèses viennent de la main et entrent dans le rail par ce bord ; les
 * autres doivent correspondre au bord de la face. Les tuiles poussées hors du rail sont défaussées.
 * @param[in,out] j Le joueur.
 * @param[in,out] rail Le rail.
 * @param[in] coup Le coup saisi.
 * @return 0 si le coup est refusé, 1 s'il est joué, 2 si c'est un Octo Verso (mot de 8 lettres).
 */
int jouerCoup(Joueur* j, Rail* rail, const char* coup);

/**
 * @brief Vérifie que le mot figure dans le dictionnaire ods4.txt.
 * @return 1 si le mot existe, 0 sinon.
 */
int verifMots(const char* mot);

/**
 * @brief Vérifie qu'un mot n'a pas déjà été joué, et l'enregistre comme joué.
 * @return 1 si le mot est nouveau, 0 s'il a déjà été joué.
 */
int verifMotDejaJouer(const char* mot);

/**
 * @brief Affiche les lettres de la main, triées par ordre alphabétique.
 */
void afficherMainJoueur(const Joueur* j);

/**
 * @brief Retire une occurrence d'une lettre de la main.
 */
void retirerLettreMain(Joueur* j, char lettre);

/**
 * @brief Ajoute une lettre dans la première case libre de la main.
 */
void ajouterLettreMain(Joueur* j, char lettre);

/**
 * @brief Vérifie si la main du joueur est vide.
 * @return 1 si la main est vide, 0 sinon.
 */
int estVideMain(const Joueur* j);
