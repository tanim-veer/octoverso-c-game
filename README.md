# 🧩 OctoVerso

Projet étudiant – **BUT1 Informatique**
Réalisé par : **VEER Tanim**

---

## 🎯 Objectif

Jeu de lettres en console inspiré du jeu vidéo ci-dessous : deux joueurs piochent des lettres,
forment des mots sur un rail partagé et gagnent en plaçant un maximum de lettres.
Vidéo d'inspiration : https://www.youtube.com/watch?v=qYaOiUVmqj0

---

## 🎮 Règles

- Chaque joueur a un chevalet de 12 lettres, piochées dans un paquet de 97 tuiles (fréquences
  inspirées du Scrabble français).
- Le rail est **partagé** entre les deux joueurs : chaque tuile posée dessus a deux faces
  (recto/verso), et peut être ajoutée par la gauche ou par la droite.
- Chaque joueur commence par proposer un mot de 4 lettres, qui détermine qui joue en premier
  (le mot le plus petit alphabétiquement).
- À chaque tour, un joueur choisit une action :
  - `4` : proposer un mot de 4 lettres (posé sur la gauche du rail) ;
  - `2` : ajouter 2 lettres sur le rail, format `<direction> <2 lettres>` (ex : `D AB`) ;
  - `8` : proposer un mot de 8 lettres, l'« Octo Verso » (posé sur la droite du rail) ;
  - `a` : Octo Verso spécial, en piochant les lettres dans la main de l'adversaire ;
  - `e` : échanger une lettre de sa main contre une lettre piochée dans le paquet ;
  - `p` : passer son tour.
- Un mot n'est accepté que s'il est dans le dictionnaire (`ods4.txt`), que le joueur a bien les
  lettres en main, et qu'il n'a pas déjà été joué dans la partie.
- Après chaque tour, le joueur repioche pour revenir à 12 lettres tant que le paquet n'est pas vide.
- La partie se termine quand le paquet est vide et qu'un joueur n'a plus de lettres (ou que les
  deux joueurs passent coup sur coup une fois le paquet épuisé). Le joueur qui a le moins de
  lettres restantes en main gagne.

**Dictionnaire fourni :** `OctoVerso/ods4.txt` contient une liste de démonstration (une centaine
de mots français réels, 4 et 8 lettres), pas le dictionnaire officiel ODS4 complet — vous pouvez
la remplacer par une vraie liste ODS4/ODS8 pour un jeu plus complet.

---

## 🛠️ Technologies & Architecture

- **Langage :** C (100 %)
- **Outils :** Visual Studio (`OctoVerso.sln`) ou GCC/Clang, Git
- **Fichiers :** `main.c` (boucle de jeu), `joueur.c/h` (chevalet, mots), `rail.c/h` (rail
  partagé recto/verso), `paquet.c/h` (pioche de lettres)

---

## ▶️ Lancement rapide

```bash
git clone https://github.com/tanim-veer/octoverso-c-game.git
cd octoverso-c-game/OctoVerso
gcc -o octoverso main.c joueur.c rail.c paquet.c
./octoverso
```

Le fichier `ods4.txt` doit être dans le même dossier que l'exécutable au lancement.

---

## 🐛 Historique : bugs corrigés

Une revue de code a mis en évidence plusieurs bugs qui empêchaient le jeu de fonctionner, tous corrigés depuis :

- **Boucle infinie** : la condition de fin de partie utilisait `etatPartie`, une constante
  d'énumération figée à 0 (donc jamais égale à 1), au lieu d'un véritable état de jeu qui évolue.
- **Erreur de type** : plusieurs appels passaient un `Joueur*` à des fonctions attendant un
  `Rail*` (`ajouterLettreRailGauche`/`Droite`), ce qui interprétait la mémoire d'un joueur comme
  celle d'un rail.
- **Dépassements de tas (heap overflow)** :
  - le paquet de lettres était alloué pour 88 cases (`MAX_CARTES`) alors que la somme réelle des
    fréquences de lettres est de 97 — 9 lettres étaient donc écrites hors du tampon alloué ;
  - plusieurs fonctions du chevalet du joueur (`estVideMain`, `retirerLettreMain`,
    `afficherMainJoueur`, `verifMots`) parcouraient une taille fixe (12) alors que le tampon
    était réalloué dynamiquement à une taille plus petite ailleurs dans le code, provoquant des
    lectures/écritures hors bornes ;
  - `piocherLettreduPaquet` lisait la lettre à l'indice `reste` (un cran au-delà de la dernière
    lettre valide) avant de décrémenter, au lieu de décrémenter d'abord.
- **Jeu non fonctionnel** : la boucle principale n'appelait jamais aucune fonction de jeu (ni
  lecture des coups, ni fin de partie, ni distribution de nouvelles lettres) ; `verifMots`
  écrasait le mot proposé par le joueur avec les mots du dictionnaire pendant sa propre
  vérification ; `j->mot` n'était jamais renseigné alors qu'il servait à déterminer qui commence.

Le jeu a été complété pour être jouable de bout en bout (vraie boucle de tours, lecture des
coups, distribution continue de lettres, détection de fin de partie et annonce du gagnant).

---

## 📚 Limites connues / pistes d'amélioration

- Dictionnaire de démonstration (voir plus haut) plutôt que l'ODS4 officiel complet.
- Pas de système de score au sens Scrabble (valeur des lettres) : la victoire se base sur le
  nombre de lettres restantes en main.
- Le format de saisie du coup à 2 lettres (`<direction> <2 lettres>`) est une simplification :
  la mécanique exacte du jeu original (choix explicite recto/verso) n'était pas spécifiée dans le
  code de départ.
- Pas d'interface graphique (contrainte du projet : console uniquement).

---

## Auteur

Tanim Veer, étudiant en BUT Informatique (parcours Data & IA)

[GitHub](https://github.com/tanim-veer) · [Portfolio](https://tanim-veer.fr)
