
---

# Compteur d'occurrences par processus et threads

Ce programme en C génère un tableau d'entiers aléatoires et crée plusieurs processus pour compter le nombre d'occurrences de chaque numéro de processus dans le tableau. Chaque processus utilise des threads pour paralléliser le calcul.

## Utilisation

1. Clonez le dépôt depuis GitHub :

```
git clone https://github.com/SergeNoah000/thread-usage-in-c.git
```

2. Placez-vous dans le dossier `thread-usage-in-c` avec: 
```
cd thread-usage-in-c

```
3. Compilez le programme en exécutant la commande suivante dans le répertoire du dépôt :

```
gcc -pthread -o runner process_threads_natifs.c
```

3. Exécutez le programme en spécifiant le nombre de processus à créer :

```
./runner
```

4. Suivez les instructions pour entrer le nombre de processus souhaité.

5. Les résultats seront enregistrés dans des fichiers portant le nom "process_X_thread_result.txt", où X est le numéro du processus.

## Fonctionnement

- Le programme commence par générer un tableau d'entiers aléatoires entre 0 et n-1, où n est le nombre de processus spécifié par l'utilisateur.

- Ensuite, il crée n processus enfants, chacun étant responsable du traitement d'une partie du tableau.

- Chaque processus crée plusieurs threads pour paralléliser le calcul. Chaque thread compte le nombre d'occurrences du numéro du processus dans sa portion du tableau.

- Les résultats de chaque thread sont écrits dans un fichier spécifique, avec chaque thread ajoutant ses résultats à la fin du fichier correspondant à son processus.

- Une fois tous les threads terminés, le programme principal se termine.
 
- Vous avez avec vous un exemple des fichiers générés pour un n=20
---

