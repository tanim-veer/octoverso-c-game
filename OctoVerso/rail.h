#pragma once

enum {
    TAILLE_RAIL = 8,
};

// Rail de 8 tuiles double face. Seul le recto est stocké : retourner le rail inverse l'ordre
// de lecture, donc le verso est le recto lu de droite à gauche.
typedef struct {
    char recto[TAILLE_RAIL + 1];
} Rail;

/**
 * @brief Forme le rail à partir des deux mots d'ouverture (4 lettres chacun).
 * @param[out] r Le rail à initialiser.
 * @param[in] gauche Le mot placé à gauche.
 * @param[in] droite Le mot placé à droite.
 */
void initRail(Rail* r, const char* gauche, const char* droite);

/**
 * @brief Lit une face du rail.
 * @param[in] r Le rail.
 * @param[in] face 'R' pour le recto, 'V' pour le verso.
 * @param[out] sortie Tampon d'au moins TAILLE_RAIL + 1 caractères.
 */
void lireFace(const Rail* r, char face, char* sortie);

/**
 * @brief Affiche le recto et le verso du rail.
 * @param[in] r Le rail à afficher.
 */
void afficherRail(const Rail* r);

/**
 * @brief Fait entrer des lettres par un bord d'une face : autant de tuiles sortent par le bord opposé.
 * @param[in,out] r Le rail.
 * @param[in] face 'R' ou 'V'.
 * @param[in] aGauche 1 pour faire entrer les lettres par la gauche de la face, 0 par la droite.
 * @param[in] lettres Les lettres à faire entrer (entre 1 et TAILLE_RAIL).
 * @param[out] expulsees Reçoit les tuiles sorties du rail (tampon d'au moins TAILLE_RAIL + 1).
 */
void glisserSurRail(Rail* r, char face, int aGauche, const char* lettres, char* expulsees);
