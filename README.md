# Philosophers42
# README

Bienvenue dans ce dépôt contenant une implémentation du problème des **Philosophes** (aussi appelé **Dining Philosophers Problem**). Ce projet en C utilise des threads et des mutex pour gérer la synchronisation et éviter les conditions d’interblocage.

## Table des matières
1. [Aperçu du projet](#aperçu-du-projet)  
2. [Structure des fichiers](#structure-des-fichiers)  
3. [Compilation](#compilation)  
4. [Exécution](#exécution)  
5. [Exemple d’utilisation](#exemple-dutilisation)  
6. [Fonctionnement général](#fonctionnement-général)  
7. [Contact](#contact)

---

## Aperçu du projet

Le **problème des philosophes** consiste à modéliser un ensemble de philosophes assis autour d’une table, chacun disposant d’une fourchette à sa droite. Pour manger, un philosophe a besoin de prendre deux fourchettes (celles de droite et de gauche). L’implémentation doit veiller à ce que:

- Chaque philosophe puisse manger sans risquer de tomber dans un état d’interblocage général (deadlock).
- Le programme gère correctement les accès concurrents aux ressources partagées (fourchettes).
- Le programme surveille l’état de chaque philosophe afin de détecter s’il meurt de faim ou si tous ont suffisamment mangé.

Vous trouverez dans ce dépôt le code C gérant la création des threads, l’accès aux **forks**, les routines de chaque philosophe et un thread de **monitoring** pour surveiller l’état de la simulation.

---

## Structure des fichiers

Voici un aperçu des principaux fichiers et de leur rôle:

- **Makefile** : Script de compilation. Il contient les règles habituelles (`make`, `make clean`, `make fclean`, `make re`).
- **main.c** : Point d’entrée du programme. Il gère la récupération des arguments, l’initialisation des structures et le lancement de la simulation.
- **parsing.c** : Vérifie la validité des arguments, convertit les chaînes en entiers et initialise certaines valeurs de configuration. 
- **philo.h** : Fichier d’en-tête principal, déclare les structures (`t_philo`, `t_rules`) et les prototypes de fonctions. 
- **init.c** : Initialise les variables globales, les mutex, les tableaux de philosophes et de fourchettes.
- **routine.c** : Contient la routine de chaque philosophe : prendre les fourchettes, manger, dormir et penser.
- **thread.c** : Gère la création et la coordination des threads (philosophes et thread de monitoring).
- **check_monito.c** : Contient la logique de vérification de la mort d’un philosophe et de la fin de la simulation.
- **ft_utils.c** : Regroupe des fonctions utilitaires (affichage d’erreurs, fonction `ft_usleep`, etc.).

---

## Compilation

Assurez-vous d’avoir un compilateur C et **Make** installés. Pour compiler:

```bash
make
```

Cela génère un exécutable nommé `philo`.

Vous pouvez également utiliser:
- `make clean` : supprime les fichiers objets.
- `make fclean` : supprime les fichiers objets **et** l’exécutable.
- `make re` : exécute un `fclean` puis un `make` pour recompiler entièrement le projet.

---

## Exécution

L’exécutable s’appelle `philo`. Il nécessite **4** ou **5** arguments :

```bash
./philo nb_philos time_to_die time_to_eat time_to_sleep [min_meals]
```

- **nb_philos** : Nombre de philosophes (1 à 200).
- **time_to_die** : Temps (en millisecondes) avant qu’un philosophe ne meure s’il ne mange pas.
- **time_to_eat** : Temps (en millisecondes) nécessaire pour qu’un philosophe finisse de manger.
- **time_to_sleep** : Temps (en millisecondes) qu’un philosophe passe à dormir après avoir mangé.
- **min_meals** *(optionnel)* : Nombre de repas minimum qu’un philosophe doit prendre avant d’arrêter la simulation. S’il n’est pas spécifié, la simulation ne s’arrête qu’en cas de mort d’un philosophe.

Exemple d’erreurs gérées :  
- Si le nombre de philosophes est invalide (≤ 0 ou > 200).  
- Si l’un des temps (mourir, manger, dormir) est ≤ 0.

Pour plus de détails, référez-vous à la fonction `parsing_args` dans **parsing.c**. citeturn0file4

---

## Exemple d’utilisation

Si vous voulez lancer une simulation avec 5 philosophes, où chacun meurt au bout de 800 ms sans manger, met 200 ms à manger, 200 ms à dormir, et doit manger au moins 7 fois avant la fin:

```bash
./philo 5 800 200 200 7
```

Vous verrez alors défiler dans la console un log des actions de chaque philosophe (prise de fourchette, début de repas, sommeil, etc.). La simulation s’arrête quand tous les philosophes ont mangé 7 fois, ou si l’un d’eux meurt de faim avant.

---

## Fonctionnement général

1. **Initialisation**  
   - Le programme récupère les arguments et les vérifie.
   - Les structures nécessaires sont initialisées (tableau de philosophes, mutex pour chaque fourchette, locks pour sécuriser l’affichage et la vérification de la mort).

2. **Création de threads**  
   - Un thread par philosophe est créé, chacun exécutant la fonction `routine` (manger, dormir, penser).
   - Un thread “monitor” est lancé pour vérifier en continu l’état de chaque philosophe (mort, ou condition de fin).

3. **Boucle de vie d’un philosophe**  
   - Prendre la fourchette droite, puis la fourchette gauche (ou inversement, selon l’ordre défini).  
   - Manger pendant `time_to_eat` millisecondes.  
   - Relâcher les fourchettes.  
   - Dormir pendant `time_to_sleep` millisecondes.  
   - Penser en attendant de pouvoir reprendre les fourchettes.

4. **Fin de la simulation**  
   - La simulation prend fin si un philosophe meurt de faim (temps trop long sans manger) ou si tous les philosophes ont mangé `min_meals` fois.

---

## Contact

Pour toute question ou suggestion concernant ce projet, n’hésitez pas à me contacter via votre plateforme préférée ou à ouvrir une **Issue** sur ce dépôt GitHub.

Merci d’avoir lu ce README et bonne expérimentation avec le problème des philosophes !
