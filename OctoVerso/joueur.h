#pragma once
#include "rail.h"

enum {
	CHEVALETS = 12,
	MOT4 = 5,
	LETTRE2 = 3,
	MOT8 = 9,
	etatPartie = 0,
};

typedef struct {
	char* chevalet;
	int reste;
	char mot[MOT4];
	Rail rail;
} Joueur;

/**
 * @brief Initialise un joueur avec un chevalet vide.
 * @param[out] j L'adresse du joueur à initialiser.
 * @pre La mémoire pour le chevalet sera allouée dynamiquement.
 */
void initJoueur(Joueur* j);

/**
 * @brief Propose un mot de 4 lettres à partir du chevalet du joueur.
 * @param[in] j Le joueur qui propose le mot.
 * @return 1 si le mot est valide, 0 sinon.
 * @pre Le mot proposé doit être composé de 4 lettres.
 */
int proposerMots4Lettres(Joueur* j);

/**
 * @brief Propose 2 lettres à placer sur les rails du joueur.
 * @param[in] j Le joueur qui propose les lettres.
 * @pre Le format d'entrée doit respecter une syntaxe attendue.
 */
void propose2Lettres(Joueur* j);

/**
 * @brief Vérifie si le mot proposé est valide selon un dictionnaire externe.
 * @param[in] j Le joueur qui propose le mot.
 * @return 1 si le mot est valide, 0 sinon.
 */
int verifMots(Joueur* j, char* mot);

/**
 * @brief Vérifie si un mot a déjà été joué par ce joueur.
 * @param[in] j Le joueur à vérifier.
 * @return 1 si le mot n'a pas été joué, 0 sinon.
 */
int verifMotDejaJouer(Joueur* j);

/**
 * @brief Affiche les lettres du chevalet du joueur.
 * @param[in] j Le joueur dont on affiche la main.
 */
void afficherMainJoueur(Joueur* j);

/**
 * @brief Retire une lettre du chevalet du joueur.
 * @param[in] j Le joueur dont la lettre sera retirée.
 * @param[in] lettre La lettre à retirer.
 */
void retirerLettreMain(Joueur* j, char lettre);

/**
 * @brief Ajoute une lettre au chevalet du joueur.
 * @param[in] j Le joueur qui reçoit la lettre.
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
 * @brief Permet à un joueur de proposer un mot de 8 lettres sur les rails.
 * @param[in] j Le joueur qui propose un mot de 8 lettres.
 * @pre Le mot proposé doit être de 8 lettres.
 */
void proposerOctoVerso(Joueur* j);

/**
 * @brief Permet à un joueur d'adversaire de proposer un mot de 8 lettres.
 * @param[in] j Le joueur proposant le mot.
 * @param[in] adversaire L'adversaire qui reçoit les lettres.
 * @pre Le mot proposé doit être de 8 lettres.
 */
void proposerOctoAdversaire(Joueur* j, Joueur* adversaire);