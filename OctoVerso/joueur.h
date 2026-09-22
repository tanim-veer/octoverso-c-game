#pragma once
#include "rail.h"

enum {
	CHEVALETS = 12,
	MOT4 = 5,
	LETTRE2 = 3,
	MOT8 = 9,
};

typedef struct {
	char* chevalet;
	int reste;
	char mot[MOT4];
} Joueur;

/**
 * @brief Initialise un joueur avec un chevalet de taille fixe (CHEVALETS cases), vide.
 * @param[out] j L'adresse du joueur à initialiser.
 */
void initJoueur(Joueur* j);

/**
 * @brief Vérifie que toutes les lettres de `mot` sont bien disponibles dans le chevalet du joueur.
 * @param[in] j Le joueur dont on vérifie le chevalet.
 * @param[in] mot Le mot à vérifier.
 * @return 1 si toutes les lettres sont disponibles, 0 sinon.
 */
int mainContientMot(Joueur* j, const char* mot);

/**
 * @brief Propose un mot de 4 lettres à partir du chevalet du joueur et le pose sur le rail partagé.
 * @param[in] j Le joueur qui propose le mot.
 * @param[in,out] rail Le rail partagé sur lequel poser le mot.
 * @return 1 si le mot est valide et a été joué, 0 sinon.
 */
int proposerMots4Lettres(Joueur* j, Rail* rail);

/**
 * @brief Propose 2 lettres à ajouter sur le rail partagé.
 * @param[in] j Le joueur qui propose les lettres.
 * @param[in,out] rail Le rail partagé sur lequel ajouter les lettres.
 * @pre Entrée attendue au format "<direction> <2 lettres>" (direction : G ou D).
 * @return 1 si les lettres ont été posées, 0 si le coup a été refusé.
 */
int propose2Lettres(Joueur* j, Rail* rail);

/**
 * @brief Vérifie si le mot proposé est valide selon le dictionnaire externe (ods4.txt)
 * et n'a pas déjà été joué durant la partie.
 * @param[in] j Le joueur qui propose le mot.
 * @param[in] mot Le mot à vérifier.
 * @return 1 si le mot est valide, 0 sinon.
 */
int verifMots(Joueur* j, char* mot);

/**
 * @brief Vérifie si un mot a déjà été joué durant la partie.
 * @param[in] j Le joueur qui propose le mot (non utilisé pour la vérification, gardé pour cohérence d'API).
 * @param[in] mot Le mot à vérifier.
 * @return 1 si le mot n'a pas déjà été joué, 0 sinon.
 */
int verifMotDejaJouer(Joueur* j, const char* mot);

/**
 * @brief Affiche les lettres du chevalet du joueur, triées par ordre alphabétique.
 * @param[in] j Le joueur dont on affiche la main.
 */
void afficherMainJoueur(Joueur* j);

/**
 * @brief Retire une occurrence d'une lettre du chevalet du joueur.
 * @param[in,out] j Le joueur dont la lettre sera retirée.
 * @param[in] lettre La lettre à retirer.
 */
void retirerLettreMain(Joueur* j, char lettre);

/**
 * @brief Ajoute une lettre dans la première case libre du chevalet du joueur.
 * @param[in,out] j Le joueur qui reçoit la lettre.
 * @param[in] lettre La lettre à ajouter.
 */
void ajouterLettreMain(Joueur* j, char lettre);

/**
 * @brief Vérifie si la main du joueur est vide.
 * @param[in] j Le joueur à vérifier.
 * @return 1 si la main est vide, 0 sinon.
 */
int estVideMain(Joueur* j);

/**
 * @brief Permet à un joueur de proposer un mot de 8 lettres (Octo Verso) sur le rail partagé.
 * @param[in] j Le joueur qui propose le mot.
 * @param[in,out] rail Le rail partagé sur lequel poser le mot.
 * @return 1 si le mot a été posé, 0 si le coup a été refusé.
 */
int proposerOctoVerso(Joueur* j, Rail* rail);

/**
 * @brief Variante de l'Octo Verso : le joueur pose un mot de 8 lettres en piochant les
 * lettres depuis la main de son adversaire plutôt que la sienne.
 * @param[in] j Le joueur qui propose le mot.
 * @param[in,out] adversaire L'adversaire dont la main est utilisée.
 * @param[in,out] rail Le rail partagé sur lequel poser le mot.
 * @return 1 si le mot a été posé, 0 si le coup a été refusé.
 */
int proposerOctoAdversaire(Joueur* j, Joueur* adversaire, Rail* rail);
