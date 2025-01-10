#pragma once

enum {
    TAILLE_RAIL = 8,
};

typedef struct {
    char* recto;
    char* verso;
    int size_recto;
    int size_verso;
    int capacite_recto;
    int capacite_verso;
} Rail;

/**
 * @brief Agrandit la taille d'un rail si nécessaire.
 * @param[in,out] rail Le rail à agrandir.
 * @param[in,out] size La taille actuelle du rail.
 * @param[in,out] capacite La capacité actuelle du rail.
 * @pre Le rail peut être agrandi si nécessaire.
 */
void augmenterTailleRail(char** rail, int* size, int* capacite);

/**
 * @brief Initialise un rail avec une taille et une capacité données.
 * @param[out] r L'adresse du rail à initialiser.
 */
void initRail(Rail* r);

/**
 * @brief Compare deux caractères pour un tri alphabétique.
 * @param[in] a Premier caractère à comparer.
 * @param[in] b Deuxième caractère à comparer.
 * @return Valeur entière indiquant l'ordre des caractères.
 */
int comparer(const void* a, const void* b);

/**
 * @brief Affiche les lettres du rail recto du joueur.
 * @param[in] r Le rail à afficher.
 */
void afficherRailRecto(Rail* r);

/**
 * @brief Affiche les lettres du rail verso du joueur.
 * @param[in] r Le rail à afficher.
 */
void afficherRailVerso(Rail* r);

/**
 * @brief Ajoute une lettre sur le rail gauche (recto ou verso).
 * @param[in,out] r Le rail auquel ajouter la lettre.
 * @param[in] lettre La lettre à ajouter.
 */
void ajouterLettreRailGauche(Rail* r, char lettre);

/**
 * @brief Ajoute une lettre sur le rail droit (recto ou verso).
 * @param[in,out] r Le rail auquel ajouter la lettre.
 * @param[in] lettre La lettre à ajouter.
 */
void ajouterLettreRailDroite(Rail* r, char lettre);

/**
 * @brief Retire une lettre du rail gauche (recto ou verso).
 * @param[in,out] r Le rail duquel retirer la lettre.
 * @param[in] lettre La lettre à retirer.
 */
void retirerLettreRailGauche(Rail* r, char lettre);

/**
 * @brief Retire une lettre du rail droit (recto ou verso).
 * @param[in,out] r Le rail duquel retirer la lettre.
 * @param[in] lettre La lettre à retirer.
 */
void retirerLettreRailDroite(Rail* r, char lettre);

/**
 * @brief Vide le contenu des rails (recto et verso).
 * @param[in,out] r Le rail à vider.
 */
void viderRail(Rail* r);

/**
 * @brief Vérifie si les rails (recto et verso) sont pleins.
 * @param[in] r Le rail à vérifier.
 * @return 1 si les rails sont pleins, 0 sinon.
 */
int estPlein(Rail* r);