# Gestion des lignes de Métro à Berlin

Ce projet vise à gérer les déplacements des Métros sur 3 lignes différentes reliant 6 stations de métro sous-sol à Berlin : A, B, C, D, E, F.

## Description du Problème

Les lignes de Métro sont les suivantes :
- MR1 : relie la station A à la station D.
- MR2 : relie la station F à la station A.
- MR3 : relie la station E à la station B.

Contraintes à prendre en compte :
- Plusieurs Métros peuvent partir simultanément de A.
- Plusieurs Métros peuvent partir simultanément de F.
- Plusieurs Métros peuvent partir simultanément de E.
- À un instant donné, chaque segment de ligne de Métro (segments AB, BC, CD, BF et EC) ne peut être utilisé que par un seul Métro.
- Chaque Métro prend 6 minutes pour occuper un segment.

## Objectifs du Projet

1. **Développement en POSIX :** Chaque Métro sera modélisé par un thread pour gérer les déplacements simultanés tout en respectant les contraintes énoncées.

2. **Simulations avec exclusion mutuelle :** Des simulations seront présentées pour illustrer la gestion de l'exclusion mutuelle des Métros sur les segments de ligne, démontrant ainsi le respect des contraintes imposées.

## Implémentation du Projet

Le projet implémentera un système de gestion des threads POSIX pour représenter chaque Métro et une logique d'exclusion mutuelle pour garantir qu'un seul Métro peut occuper un segment de ligne à la fois.

## Structure du Projet

- `Projet.c` : Fichier principal contenant le code de gestion des threads et de l'exclusion mutuelle.
- `Makefile` : Fichier pour la compilation et l'exécution du programme.
- `README.md` : Ce fichier décrivant le projet, ses objectifs et son implémentation.
