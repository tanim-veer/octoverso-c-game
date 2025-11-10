# 🧩 OctoVerso

Projet étudiant – **BUT1 Informatique**  
Réalisé par : **VEER Tanim**

---

## 🎯 Objectif

L’objectif de ce projet est de **développer un jeu console en C** inspiré du jeu décrit dans cette vidéo : https://www.youtube.com/watch?v=qYaOiUVmqj0  
- Implémenter les règles du jeu : lettres à double sens, lettres communes, etc.  
- Interface texte simple pour jouer, proposer des mots, calculer scores.  
- Mise en œuvre d’algorithmes pour validation de mots et pertinence.

Le but est à la fois **pédagogique** (structuration du code, gestion des données, logique de jeu) et **applicatif** (un jeu fonctionnel à jouer sur console).

---

## 🚀 Démos / Captures
- `docs/screenshot-gameplay.png`
- `docs/screenshot-menu.png`
- `docs/screenshot-score.png`

---

## 🛠️ Technologies & Architecture

- **Langage :** C (100 %)  
- **Outils :** VS Code ou autre éditeur C, compilateur GCC/Clang, Git  
- **Versioning :** GitHub

---

## ▶️ Lancement rapide
- Prérequis : compilateur C (GCC ou Clang)  
- `git clone https://github.com/tanim-veer/OctoVerso.git`  
- `cd OctoVerso`  
- Compiler : `gcc -o OctoVerso main.c <autres_fichiers.c>`  
- Lancer : `./OctoVerso`

---

## ✅ Fonctionnalités clés
- Interface console textuelle : menu, jeu, score.  
- Validation de mots selon règles définies.  
- Gestion des lettres à double sens / motifs de jeu.  
- Affichage des résultats et score final.  
- Code modulaire : fonctions spécifiques pour menu, jeu, validation, score.

---

## 🔍 Points techniques intéressants
- Algorithme de vérification de mot efficace (tableau, recherche).  
- Gestion dynamique/la gestion mémoire si nécessaire (allocation, libération).  
- Interface console simplifiée mais claire.  
- Mise en place de tests manuels (et si possible automatisés) pour les cas de jeu.

---

## 📚 Notes
- Contraintes : console uniquement, interface simple, respect strict des règles du jeu.  
- Limites / améliorations futures : ajout graphique simple (SDL), mode deux joueurs, interface web, dictionnaire externe.
