/* Objectifs : 
- Pouvoir générer un mdp avec le choix de la taille et un titre 
- Pouvoir enregistrer un mdp de son choix avec un titre 
- Stocker les mdp enregistré et pouvoir les afficher et les supprimer 
- Faire en sorte que ce soit une boucle infinie 
*/ 
 
#include <stdlib.h>   
#include <stdio.h>    
#include <string.h>  // Pour manipuler les chaînes de caractères 
#include <time.h>    // Pour la fonction srand() et time() 
 
// Cette fonction génère un mot de passe aléatoire 
void GenererUnMDP() 
{ 
    char nom[100];   // Pour stocker le nom du site ou de l'application 
    int longueur;    // Déclare la longueur du mdp 
 
    printf("Nom du site/app : "); 
    scanf_s("%s", nom, sizeof(nom)); // On demande de saisir le nom du site 
    printf("Entrez la longueur du mot de passe : "); 
    scanf("%d", &longueur);  // On demande la longueur du mdp 
 
    if (longueur <= 6) { 
        printf("La longueur doit %ctre sup%crieure a 6.\n", 136, 130);  // Si la longueur est trop courte, on affiche un message d'erreur 
        return;  // Et on quitte la fonction 
    } 
 
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*"; // Liste des caractères pour le mdp 
    char mdp[longueur + 1];  // Le mot de passe sera de cette taille 
 
    srand(time(NULL));  // Initialisation de la génération aléatoire 
 
    // Remplissage du mot de passe avec des caractères aléatoires 
    for (int i = 0; i < longueur; i++) { 
        mdp[i] = caracteres[rand() % (sizeof(caracteres) - 1)];  // Choisir un caractère au hasard 
    } 
 
    mdp[longueur] = '\0';  // On met un caractère de fin de chaîne pour que le mot de passe soit bien formé 
    printf("Mot de passe g%cn%cr%c : %s\n", 130,130,130, mdp);  // Affiche le mot de passe généré 
 
    // Enregistrement dans le fichier "GestionnaireDeMDP.txt" 
    FILE *fichier; 
    fopen_s(&fichier, "GestionnaireDeMDP.txt", "a");  // On ouvre le fichier en mode ajout 
    if (fichier != NULL) {  // Si l'ouverture réussie 
        fprintf(fichier, "\nNom : %s\n", nom);  // On écrit le nom du site 
        fprintf(fichier, "Mot de passe : %s\n", mdp);  // On écrit le mot de passe 
        fclose(fichier);  // Fermeture du fichier 
        printf("Mot de passe enregistre avec succ%cs!\n",138);  // Confirme l'enregistrement 
    } else { 
        printf("Erreur lors de l'ouverture du fichier : votre mdp n'a pas pu %ctre sauvegarde !\n",136);  // En cas d'erreur 
    } 
} 
 
// Cette fonction permet d'enregistrer un mot de passe que l'on a soi-même choisi 
void EnregistrerUnMDP() 
{ 
    char nom[100];  // Nom du site/app 
    char mdp[100];  // Le mot de passe à enregistrer 
    FILE *fichier;  // Le fichier où on va enregistrer les mdp 
 
    printf("Nom du site/app : "); 
    scanf_s("%s", nom, sizeof(nom));  // Demande à l'utilisateur le nom du site 
    printf("Mot de passe : "); 
    scanf_s("%s", mdp, sizeof(mdp));  // Demande le mot de passe 
 
    // Ouvre le fichier 
    fopen_s(&fichier, "GestionnaireDeMDP.txt", "a"); 
    if (fichier != NULL) {  // Si l'ouverture réussie 
        fprintf(fichier, "\nNom : %s\n", nom);  // Écrit le nom du site 
        fprintf(fichier, "Mot de passe : %s\n", mdp);  // Écrit le mot de passe 
        fclose(fichier);  // Ferme le fichier 
        printf("Mot de passe enregistr%c avec succ%cs !\n", 130, 138);  // Confirme l'enregistrement 
    } 
} 
 
// Cette fonction affiche tous les mots de passe enregistrés 
void AfficherMDP() 
{ 
    FILE *fichier;  // Le fichier à ouvrir 
    char ligne[256];  // Une ligne du fichier 
 
    fopen_s(&fichier, "GestionnaireDeMDP.txt", "r");  // Ouvre le fichier en lecture 
    if (fichier == NULL) {  // Si le fichier n'existe pas ou qu'il y a une erreur 
        printf("Aucun mot de passe enregistr%c. \n",130);  // On affiche un message d'erreur 
        return;  // Et on quitte la fonction 
    } 
 
    printf("\nContenu du gestionnaire de mot de passe : \n\n"); 
    // Affiche chaque ligne du fichier 
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { 
        printf("%s", ligne);  // Affiche les lignes 
    } 
    fclose(fichier);  // Ferme le fichier 
} 
 
// Cette fonction permet de supprimer un mot de passe choisi 
void SupprimerMDP() 
{ 
    char nomASupprimer[100];  // Le nom du site qu'on veut supprimer 
    char ligne[256];  // Pour lire les lignes du fichier 
    int trouve = 0;  // Indicateur pour savoir si on a trouvé le mot de passe 
 
    FILE *fichier; 
    fopen_s(&fichier, "GestionnaireDeMDP.txt", "r");  // Ouvre le fichier en lecture 
    if (fichier == NULL) {  // Si le fichier n'existe pas 
        printf("Erreur lors de l'ouverture du fichier.\n"); 
        return;  // Quitte la fonction 
    } 
 
    // Affiche tous les sites enregistrés 
    printf("Sites enregistr%cs :\n",130); 
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { 
        if (strncmp(ligne, "Nom : ", 6) == 0) {  // Si c'est une ligne contenant un nom de site 
            printf("%s", ligne + 6);  // Affiche juste le nom 
        } 
    } 
    fclose(fichier);  // Ferme le fichier 
 
    // Demande à l'utilisateur quel site il veut supprimer 
    printf("\nEntrez le nom du site/app dont vous voulez supprimer le mot de passe : "); 
    scanf_s("%s", nomASupprimer, sizeof(nomASupprimer));  // Saisie du nom 
 
    // Ouvre le fichier en lecture et un fichier temporaire en écriture 
    FILE *temp; 
    fopen_s(&fichier, "GestionnaireDeMDP.txt", "r"); 
    fopen_s(&temp, "temp.txt", "w"); 
    if (fichier == NULL || temp == NULL) { 
        printf("Erreur lors de l'ouverture du fichier.\n"); 
        return;  // Quitte la fonction en cas d'erreur 
    } 
 
    // Recherche et supprime le mot de passe  
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) { 
        if (strncmp(ligne, "Nom : ", 6) == 0 && strstr(ligne, nomASupprimer) != NULL) { 
            trouve = 1;  // Si le nom correspond, on le marque comme trouvé 
            fgets(ligne, sizeof(ligne), fichier);  // On saute la ligne contenant le mot de passe 
        } else { 
            fprintf(temp, "%s", ligne);  // Sinon, on garde la ligne 
        } 
    } 
 
    fclose(fichier); 
    fclose(temp); 
 
    if (trouve) {  // Si on a trouvé le mot de passe à supprimer 
        remove("GestionnaireDeMDP.txt");  // Supprime l'ancien fichier 
        rename("temp.txt", "GestionnaireDeMDP.txt");  // Renomme le fichier temporaire 
        printf("Le mot de passe pour '%s' a ete supprim%c avec succ%cs.\n", nomASupprimer, 130, 138); 
    } else { 
        remove("temp.txt");  // Si on n'a pas trouvé, on supprime le fichier temporaire 
        printf("Aucun mot de passe trouv%c pour '%s'.\n", 130, nomASupprimer); 
    } 
} 
 
// Cette fonction affiche le menu et gère le choix de l'utilisateur 
int accueil() 
{ 
    int choix = 0; 
 
    while (choix < 1 || choix > 4)  // Demande à l'utilisateur de faire un choix valide 
    { 
        printf("Gestionnaire de mots de passe :\n"); 
        printf("1 : G%cn%crer un nouveau mot de passe\n",130, 130); 
        printf("2 : Enregistrer un nouveau mot de passe\n"); 
        printf("3 : Afficher les mots de passe\n"); 
        printf("4 : Supprimer un mot de passe\n"); 
        printf("Votre choix ? "); 
        scanf("%d", &choix);  // Lecture du choix 
    } 
    return choix;  // Retourne le choix 
} 
 
int main(int argc, char *argv[]) 
{ 
    while (1)  // Boucle infinie pour répéter les actions 
    { 
        switch (accueil())  // Choix de l'utilisateur 
        { 
            case 1: 
                GenererUnMDP();  // Générer un mot de passe 
                break; 
            case 2: 
                EnregistrerUnMDP();  // Enregistrer un mot de passe 
                break; 
            case 3: 
                AfficherMDP();  // Afficher les mots de passe 
                break; 
            case 4: 
                SupprimerMDP();  // Supprimer un mot de passe 
                break; 
        } 
 
        // Attend que l'utilisateur appuie sur Entrée avant de revenir au menu 
        printf("\nAppuyez sur Entr%ce pour continuer...\n", 130); 
        getchar();  // Capture le retour à la ligne restant 
        getchar();  // Attends une autre entrée 
    } 
    return 0;  // Le programme se termine 
} 