# Documentation Détaillée du Simple Shell

## Table des Matières
1. [Démarrage du Programme](#1-démarrage-du-programme)
2. [Affichage du Prompt](#2-affichage-du-prompt)
3. [Lecture de l'Entrée](#3-lecture-de-lentrée)
4. [Traitement de l'Entrée](#4-traitement-de-lentrée)
5. [Vérification des Commandes Builtin](#5-vérification-des-commandes-builtin)
6. [Recherche de la Commande](#6-recherche-de-la-commande)
7. [Exécution de la Commande](#7-exécution-de-la-commande)
8. [Gestion des Erreurs](#8-gestion-des-erreurs)
9. [Fonctions Utilitaires](#9-fonctions-utilitaires)
10. [Gestion du CD](#10-gestion-du-cd)
11. [Gestion de l'Environnement](#11-gestion-de-lenvironnement)

## 1. Démarrage du Programme
**Fichier**: `shell.c`
```c
int main(int argc, char *argv[], char **env)
```
- Point d'entrée du programme
- Vérifie le mode interactif avec `isatty()`
- Initialise la boucle principale du shell
- Gère les arguments et l'environnement

## 2. Affichage du Prompt
**Fichier**: `prompt.c`
```c
void print_prompt(void)
```
- Affiche "Shell$ " en mode interactif
- Utilise `write()` pour l'affichage
- Assure que le prompt est immédiatement visible avec `fflush()`

## 3. Lecture de l'Entrée
**Fichier**: `input.c`
```c
char *read_input(void)
```
- Utilise `getline()` pour lire l'entrée utilisateur
- Gère :
  * EOF (Ctrl+D)
  * Lignes vides
  * Retours à la ligne
- Retourne la ligne lue ou NULL en cas d'erreur

## 4. Traitement de l'Entrée
**Fichier**: `tokenize.c`
```c
int tokenize_input(char *input, char *args[])
void free_tokens(char **tokens, int count)
char *trim_token(char *token)
```
- Découpe la commande en tokens
- Nettoie les espaces superflus
- Limite le nombre d'arguments
- Gère la mémoire proprement

## 5. Vérification des Commandes Builtin
**Fichier**: `builtin_commands.c`
```c
int handle_builtin_commands(char **args, int num_args, char *input, char **env)
```
Gère les commandes internes :
- `exit` : Quitte le shell
- `cd` : Change le répertoire
- `env` : Affiche l'environnement

## 6. Recherche de la Commande
**Fichier**: `path.c`
```c
char *get_file_path(char *command, char **env)
char *search_path(char *command, char *path)
char *check_current_dir(char *command)
```
- Recherche la commande dans PATH
- Vérifie les permissions
- Construit le chemin complet

## 7. Exécution de la Commande
**Fichier**: `exec.c`
```c
int execute_command(char *input, char *argv[], char **env, char *program_name)
void execute_child(char *cmd_path, char **args, char **env)
```
- Crée un processus enfant avec `fork()`
- Exécute la commande avec `execve()`
- Attend la fin du processus enfant
- Gère le statut de retour

## 8. Gestion des Erreurs
**Fichier**: `print_error.c`
```c
void print_error(char *program_name, char *cmd, char *error_msg)
```
Messages d'erreur pour :
- Commande non trouvée
- Permission refusée
- Erreurs d'exécution

## 9. Fonctions Utilitaires
**Fichier**: `utils.c`
```c
int _strlen(char *str)
char *_strdup(char *str)
char *_strcpy(char *dest, char *src)
char *_strchr(const char *s, int c)
char *_memset(char *s, char b, unsigned int n)
```
- Manipulation de chaînes
- Gestion mémoire
- Fonctions auxiliaires

## 10. Gestion du CD
**Fichier**: `cd.c`
```c
void handle_cd(char **args, int num_args, char **env)
void update_oldpwd(const char *current_dir)
int save_current_dir(char *buf, size_t size)
```
Gère :
- Changement de répertoire
- Cas spéciaux (cd -, cd ~)
- Variables d'environnement PWD/OLDPWD

## 11. Gestion de l'Environnement
**Fichier**: `env.c`
```c
char *_getenv(const char *name, char **env)
void print_env(char **env)
```
- Accès aux variables d'environnement
- Affichage de l'environnement
- Modification des variables

## Flux d'Exécution

1. Le shell démarre
2. Boucle principale :
   - Affiche le prompt (si interactif)
   - Lit l'entrée utilisateur
   - Parse la commande
   - Vérifie si c'est une commande builtin
   - Si non, recherche et exécute la commande
   - Attend la fin de l'exécution
   - Retourne au début
3. Continue jusqu'à `exit` ou EOF

## Gestion des Ressources

- Libération correcte de la mémoire
- Fermeture des descripteurs de fichiers
- Attente des processus enfants
- Nettoyage avant la sortie

## Codes de Retour

- 0 : Succès
- 1 : Erreur générale
- 127 : Commande non trouvée
- 2 : Erreur de syntaxe
