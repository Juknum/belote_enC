#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <math.h>
#include <time.h>

#include "./header/fonctions.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define BOLD  "\x1b[1m"
#define NBOLD ""RESET""WHT""

// Phase d'Enchère - CONTIENT DES VARIABLES A ACTIVER
void enchere(int encherisseur, char *nom_joueur, int *cartes_joueur, int *cartes_west, int *cartes_north, int *cartes_east){

	char atout[20];							// Choix de l'atout pour la partie
	char contrat[20];				 		// Personne qui annonce le contrat
	int points = 0; 						// Points a atteindre pour remporter le contrat annoncé
	int passe  = 0; 						// Nombre de fois qu'un joueur passe

	int choix_annonce = 0;					// variables concernant les choix du joueur
	int choix_atout   = 0; 
	int choix_couleur = 0; 
	int choix_points  = 0;

	int choix_surenchere = 0;
	int choix_couleur_surenchere = 0;
	int choix_points_surenchere = 0;

	int valid = 0;							// permet de savoir si la surenchere du joueur respecte les regles

	int distributeur = encherisseur;

	printf("O--------------------------------------------------=-=--------------------------------------------------O\n");
	printf("§                                     o------------=-=------------o\n");
	printf("§ ♣  "RED"♦"WHT"  ♠  "RED"♥"WHT"  ♣  "RED"♦"WHT"  ♠  "RED"♥"WHT"  ♣  "RED"♦"WHT"  ♠  "RED"♥"WHT"  !      "YEL"Phase d'Enchère"WHT"      !  ♣  "RED"♦"WHT"  ♠  "RED"♥"WHT"  ♣  "RED"♦"WHT"  ♠  "RED"♥"WHT"  ♣  "RED"♦"WHT"  ♠  "RED"♥"WHT"\n");
	printf("§                                     o-------------=-------------o\n");
	printf("§\n§\n§\n§\n");
	printf("O--------------------------------------------------=-=--------------------------------------------------O");

	strcpy(atout, "undefined\0");

	while( strcmp(atout,"undefined\0") == 0){
		encherisseur++;

		if(encherisseur == 5){encherisseur = 1;}		// On remet a 1 car après Est (=4), c'est joueur et joueur = 1;

		// DEBUG : Affiche les paramètres suivants : encherisseur & passe
		/*
		printf("\nencherisseur: %d",encherisseur);
		printf("\npasse       : %d",passe);
		printf("\n");
		*/

		switch(encherisseur){
			case 1:		// Joueur

				printf("\n§ "CYN"JEU :"WHT" %s examine son jeu...\n\n",nom_joueur);

				// On affiche les cartes du joueur 
				printf(YEL"Vos cartes :"WHT);
				for(int i = 0; i < 8; i++){
					printf(" %s",dictionnaire(cartes_joueur[i]));
				}
				
				// Demande entre annoncer un contrat ou passer
				do{
					printf(YEL"\n\nSouhaitez-vous annoncer un contrat ou passer?\n1 | Contrat\n2 | Passer\n");
					scanf("%d",&choix_annonce); // A ACTIVER
					//choix_annonce = 2; // A DESACTIVER
				}while(choix_annonce < 1 || choix_annonce > 2);
			
				switch(choix_annonce){
					case 1:
						do{
							printf("\nQuelles couleur?\n1 | Carreau\n2 | Coeur\n3 | Pique\n4 | Trèfle\n");
							scanf("%d",&choix_couleur); // A ACTIVER
						}while(choix_couleur < 1 || choix_couleur > 4);

						switch(choix_couleur){
							case 1:
								strcpy(atout,"Carreau\0");
								break;
							case 2:
								strcpy(atout,"Coeur\0");
								break;
							case 3:
								strcpy(atout,"Pique\0");
								break;
							case 4:
								strcpy(atout,"Trèfle\0");
								break;
							default:
								printf(RED"Erreur switch couleur"WHT);
								break;
							}

						printf("\nChoix enregistré, annoncez vos points!");

						// Annonce des points: 
								
						printf(WHT"§\n\n§ "YEL"Annoncez vos points:\nN | Classique - Entre 80 et 160 pts, par tranche de 10!\n1 | Capôt     - 250 pts -> gagner tout les plis\n2 | Générale  - 500 pts -> doit gagner tout les plis a vous seul\n");
						scanf("%d",&choix_points); // A ACTIVER
						printf(WHT);
						switch(choix_points){
							case 1 :
								printf("\n%s annonce "BOLD"Capôt"NBOLD" avec une couleur de "BOLD"%s"NBOLD,nom_joueur,atout);
								points = 250;
								strcpy(contrat, nom_joueur);
								break;
							case 2 :
								printf("\n%s annonce "BOLD"Générale"NBOLD" avec une couleur de "BOLD"%s"NBOLD,nom_joueur,atout);
								points = 500;
								strcpy(contrat, nom_joueur);
								break;
							case 80 ... 160 : 
								printf("\n%s annonce une couleur de "BOLD"%s"NBOLD" avec "BOLD"%d"NBOLD" pts",nom_joueur,atout,choix_points);
								points = choix_points;

								strcpy(contrat, nom_joueur);
							break;
						}

						break;
					case 2:
						printf(WHT"\n§ "CYN"JEU :"WHT" %s a choisit de passer son tours!",nom_joueur);
						passe++;
						break;
					default:
						printf(RED"Erreur switch annonce/passer joueur choix_annonce=%d"WHT,choix_annonce);
						break;
				}
				
				break;
			case 2:		// Ouest
				bot_enchere(cartes_west, "Ouest", atout, &points, &passe);
				break;
			case 3:		// Nord
				bot_enchere(cartes_north, "Nord", atout, &points, &passe);
				break;
			case 4:		// Est
				bot_enchere(cartes_east, "Est", atout, &points, &passe);
				break;
			default:
				printf(RED"Erreur switch(%d) dans while(atout=%s)"WHT,encherisseur,atout);
		}

		if(passe > 3){
			passe = 0;
			printf("\n\n");
			printf("§--------------------------------------------------------------\n");
			printf("§ "RED"Personne n'a fait de contrat, on redistribue les cartes\n"WHT);
			
			ramasser(1,distributeur, nom_joueur, cartes_west, cartes_north, cartes_east, cartes_joueur);

			encherisseur = distributeur;
			printf("§--------------------------------------------------------------\n");
		}
	}

	if(strcmp(atout,"undefined\0") != 0){passe = 0; printf("\n§ "CYN"JEU :"MAG" Phase de sur-enchère!"WHT);}

	while(passe < 3 && strcmp(atout,"undefined\0") != 0){
		encherisseur++;

		if(encherisseur == 5){encherisseur = 1;}

		switch(encherisseur){
			case 1:
				printf("\n§ "CYN"JEU :"WHT" %s examine son jeu...",nom_joueur );

				do{
					printf("\n§\n§ "YEL"Souhaitez-vous sur-encherir ou passer?\n"WHT"§"YEL" 1 | Sur-enchère\n"WHT"§"YEL" 2 | Passer\n");
					printf(WHT"\n§"YEL" Votre choix :");
					scanf("%d",&choix_surenchere); // A ACTIVER
					//choix_surenchere = 2; // A DESACTIVER
				}while(choix_surenchere < 1 || choix_surenchere > 2);

				switch(choix_surenchere){
					case 1:

						// Annonce des points: 
								
						printf(WHT"\n§\n§"YEL" Annoncez vos points:\n"WHT"§"YEL" N | Classique - Entre 80 et 160 pts, par tranche de 10!\n"WHT"§"YEL" 1 | Capôt     - 250 pts -> gagner tout les plis\n"WHT"§"YEL" 2 | Générale  - 500 pts -> doit gagner tout les plis a vous seul\n");
						printf(WHT"\n§"YEL" Votre choix :");
						scanf("%d",&choix_points_surenchere); // A ACTIVER
						
						switch(choix_points_surenchere){
							case 1:
								if(points >= 250){
									// Le joueur ne respecte pas la regle de surenchere
									printf(WHT"§"YEL" Vous devez annoncer plus que l'enchère précédente"WHT);
									valid = 0;
								}else{ valid = 1; points = 250;}

								break;
							case 2:
								if(points >= 500){
									// le joueur ne respecte pas les regles
									printf(WHT"§"YEL" Vous devez annoncer plus que l'enchère précédente"WHT);
									valid = 0;
									
								}else{ valid = 1; points = 500;}
								
								break;
							case 80 ... 160:
								if(points >= choix_points_surenchere){
									printf(WHT"§"YEL" Vous devez annoncer plus que l'enchère précédente"WHT);
									valid = 0;

								}else{ valid = 1; points = choix_points_surenchere;}

								break;
							default :
								printf(WHT"\n §"RED" Erreur"WHT": switch(%d) choix_points_surenchere",choix_points_surenchere);
								break;
						}

						if(valid == 1){
							do{
								printf("\n"WHT"§"YEL" Quelles couleur?\n"WHT"§"YEL" 1 | Carreau\n"WHT"§"YEL" 2 | Coeur\n"WHT"§"YEL" 3 | Pique\n"WHT"§"YEL" 4 | Trèfle\n");
								printf(WHT"\n§"YEL" Votre choix :");
								scanf("%d",&choix_couleur); // A ACTIVER
							}while(choix_couleur < 1 || choix_couleur > 4);

							switch(choix_couleur){
								case 1:
									strcpy(atout,"Carreau\0");
									break;
								case 2:
									strcpy(atout,"Coeur\0");
									break;
								case 3:
									strcpy(atout,"Pique\0");
									break;
								case 4:
									strcpy(atout,"Trèfle\0");
									break;
								default:
									printf(RED"Erreur switch couleur surenchere"WHT);
									break;
							}

							printf(WHT"\n§ "CYN"JEU :"WHT" %s sur-encherit avec une Couleur de "BOLD"%s"NBOLD" avec "BOLD"%d"NBOLD" pts!",nom_joueur,atout,points);
						}

						break;
					case 2:
						passe++;
						printf(WHT"\n§ "CYN"JEU :"WHT" %s a choisit de passer son tours!",nom_joueur);
						break;
					default:
						printf("\n§"RED"Erreur :"WHT" while(passe < 3 && atout == undefined) switch(%d)",choix_surenchere);
						break;
				}

				break;
			case 2:
				bot_surenchere(cartes_west, "Ouest", atout, &points, &passe);
				
				break;
			case 3:
				bot_surenchere(cartes_north, "Nord", atout, &points, &passe);
				
				break;
			case 4:
				bot_surenchere(cartes_east, "Est", atout, &points, &passe);
				
				break;
			default:
				printf("\n Erreur switch(%d) dans while(%d) < 3 && %s",encherisseur,passe,atout);
				passe = 4;
				break;
		}
	}

}