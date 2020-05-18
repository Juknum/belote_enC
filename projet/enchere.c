#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <math.h>
#include <time.h>

#include "./header/fonctions.h"

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

	int distributeur = encherisseur;

	printf("O--------------------------------------------------=-=--------------------------------------------------O\n");
	printf("§                                     o------------=-=------------o\n");
	printf("§ ♣  ♦  ♠  ♠  ♣  ♦  ♠  ♠  ♣  ♦  ♠  ♠  !      Phase d'Enchère      !  ♣  ♦  ♠  ♠  ♣  ♦  ♠  ♠  ♣  ♦  ♠  ♠ \n");
	printf("§                                     o-------------=-------------o\n");
	printf("§\n§\n§\n§\n");
	printf("O--------------------------------------------------=-=--------------------------------------------------O\n");

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

				printf("\n§ %s examine son jeu...\n\n",nom_joueur);

				// On affiche les cartes du joueur 
				printf("Vos cartes :");
				for(int i = 0; i < 8; i++){
					printf(" %s",dictionnaire(cartes_joueur[i]));
				}
				
				// Demande entre annoncer un contrat ou passer
				do{
					printf("\n\nSouhaitez-vous annoncer un contrat ou passer?\n1 | Contrat\n2 | Passer\n");
					//scanf("%d",&choix_annonce); // A ACTIVER
					choix_annonce = 2; // A DESACTIVER
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
								printf("Erreur switch couleur");
								break;
							}

						printf("\nChoix enregistré, annoncez vos points!");

						// Annonce des points: 
								
						printf("\n\nAnnoncez vos points:\nN | Classique - Entre 80 et 160 pts, par tranche de 10!\n1 | Capôt     - 250 pts -> gagner tout les plis\n2 | Générale  - 500 pts -> doit gagner tout les plis a vous seul\n");
						scanf("%d",&choix_points); // A ACTIVER

						switch(choix_points){
							case 1 :
								printf("\n%s annonce Capôt avec une couleur de %s",nom_joueur,atout);
								points = 250;
								break;
							case 2 :
								printf("\n%s annonce Générale avec une couleur de %s",nom_joueur,atout);
								points = 500;
								break;
							case 80 ... 160 : 
								printf("\n%s annonce une couleur de %s avec %d pts",nom_joueur,atout,choix_points);
								points = choix_points;

								strcpy(contrat, nom_joueur);
							break;
						}

						break;
					case 2:
						printf("\n§ %s a choisit de passer son tours!",nom_joueur);
						passe++;
						break;
					default:
						printf("Erreur switch annonce/passer joueur choix_annonce=%d",choix_annonce);
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
		}

		if(passe > 3){
			passe = 0;
			printf("\n\n");
			printf("--------------------------------------------------------------\n");
			printf("Personne n'a fait de contrat, on redistribue les cartes\n");
			
			ramasser(1,distributeur, nom_joueur, cartes_west, cartes_north, cartes_east, cartes_joueur);

			encherisseur = distributeur;
			printf("--------------------------------------------------------------\n");
		}
	}

	if(strcmp(atout,"undefined\0") != 0){passe = 0; printf("\n§---------§");}

	while(passe < 3 && strcmp(atout,"undefined\0") != 0){
		encherisseur++;

		if(encherisseur == 5){encherisseur = 1;}

		switch(encherisseur){
			case 1:
				printf("\n§ %s examine son jeu...",nom_joueur );
				passe++;
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