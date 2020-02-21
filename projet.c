#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour liste historique du solde et des transactions:
typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

// Initialisation de la liste d'entiers:


Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));


    element->nombre = 0;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

// Structure pour liste historique des opérations, du type de paiement, des commentaires:
typedef struct Information Information;
struct Information
{
	char *valeur;
	struct Information *suivant;
};

typedef struct ListeInfo ListeInfo;
struct ListeInfo
{
	Information *premier;
};

// Initialisation de la liste de char:

ListeInfo *initialisationBis()
{
	ListeInfo *listeInfo = malloc(sizeof(*listeInfo));
	Information *information = malloc(sizeof(*information));

	information->valeur = "-";
	information->suivant = NULL;
	listeInfo->premier = information;

	return listeInfo;

}

void listeSolde(Liste *liste, int nvNombre)
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    nouveau->nombre = nvNombre;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void listeTransaction(Liste *liste, int nvNombre)
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    nouveau->nombre = nvNombre;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void listeOperation(ListeInfo *liste, char *nvInfo)
{
	Information *nouvelle=malloc(sizeof(*nouvelle));
	nouvelle->valeur = nvInfo;

	nouvelle->suivant = liste->premier;
	liste->premier = nouvelle;
}

void listePaiement(ListeInfo *liste, char *nvInfo)
{
	Information *nouvelle=malloc(sizeof(*nouvelle));
	nouvelle->valeur = nvInfo;

	nouvelle->suivant = liste->premier;
	liste->premier = nouvelle;
}

void listeCommentaire(ListeInfo *liste, char *nvInfo)
{
	Information *nouvelle=malloc(sizeof(*nouvelle));
	nouvelle->valeur = nvInfo;

	nouvelle->suivant = liste->premier;
	liste->premier = nouvelle;
}

void afficherHistorique(Liste *solde, Liste *transaction, ListeInfo *operation, ListeInfo *paiement, ListeInfo *commentaire, int acc)
{
    Element *actuel_solde = solde->premier;
    Element *actuel_transaction = transaction->premier;
    Information *actuel_operation = operation->premier;
    Information *actuel_paiement = paiement->premier;
    Information *actuel_commentaire = commentaire->premier;

    while (actuel_solde != NULL)
    {
        printf("Solde: %d euros\n", actuel_solde->nombre);
        actuel_solde = actuel_solde->suivant;
        printf("Transaction: %d euros\n", actuel_transaction->nombre);
        actuel_transaction = actuel_transaction->suivant;
        printf("Opération: %s\n", actuel_operation->valeur);
        actuel_operation = actuel_operation->suivant;
        printf("Type de paiement: %s\n", actuel_paiement->valeur);
        actuel_paiement = actuel_paiement->suivant;
        printf("Commentaire: %s\n", actuel_commentaire->valeur);
        actuel_commentaire = actuel_commentaire->suivant;
        printf("\n");
    }
}

void afficherlast(Liste *liste, Element *last){
	printf("Votre solde est actuellement de: ");
	printf("%d euros \n",last->nombre );
}

int debiter(Liste *solde, Element *ancien, Liste *transaction, ListeInfo *paiement, ListeInfo *commentaire){
	int debit;
	int choix;
	char *com = malloc(sizeof(*com));

	printf("Veuillez entrer le montant de votre débit: ");
	scanf("%d",&debit);

	if (ancien->nombre- debit < 0)
	{
		printf("Refus, solde insuffisant (solde : %d euros)\n",ancien->nombre);
		return 0;
	}

	listeTransaction(transaction,debit);

	int nouveau;
	nouveau= ancien->nombre- debit;
	listeSolde(solde,nouveau);

	printf("Quel moyen de paiement?: \n");
	printf("1. Virement bancaire\n");
	printf("2. Carte bancaire\n");

	scanf("%d",&choix);

	while(choix != 1 && choix != 2){
		printf("Ce choix est impossible (tapez 1 ou 2)\n");
		scanf("%d",&choix);
	}

	if (choix==1){
		listePaiement(paiement,"Virement bancaire");
	}
	else if (choix==2){
		listePaiement(paiement,"Carte bancaire");
	}


	printf("Voulez-vous ajouter un commentaire?: \n");
	printf("1. Oui\n");
	printf("2. Non\n");
	scanf("%d", &choix);

	while(choix != 1 && choix != 2){
		printf("Ce choix est impossible (tapez 1 ou 2)\n");
		scanf("%d",&choix);
	}

	if (choix==1)
	{
	printf("Entrez un commentaire:\n"); 
	scanf("%s", com);
	listeCommentaire(commentaire, com);
	}

	if (choix==2)
	{
		char *vide = malloc(sizeof(*vide));


		listeCommentaire(commentaire, "-");
	}
	
}

void crediter(Liste *solde, Element *ancien, Liste *transaction, ListeInfo *paiement, ListeInfo *commentaire){
	int credit;
	int choix;
	char *com = malloc(sizeof(*com));

	printf("Veuillez entrer le montant de votre crédit: ");
	scanf("%d",&credit);
	listeTransaction(transaction,credit);

	int nouveau;
	nouveau= credit+ ancien->nombre;
	listeSolde(solde,nouveau);

	printf("Quel moyen de paiement?: \n");
	printf("1. Virement bancaire\n");
	printf("2. Carte bancaire\n");

	scanf("%d",&choix);

	while(choix != 1 && choix != 2){
		printf("Ce choix est impossible (tapez 1 ou 2)\n");
		scanf("%d",&choix);
	}

	if (choix==1){
		listePaiement(paiement,"Virement bancaire");
	}
	else if (choix==2){
		listePaiement(paiement,"Carte bancaire");
	}


	printf("Voulez-vous ajouter un commentaire?: \n");
	printf("1. Oui\n");
	printf("2. Non\n");
	scanf("%d", &choix);

	while(choix != 1 && choix != 2){
		printf("Ce choix est impossible (tapez 1 ou 2)\n");
		scanf("%d",&choix);
	}

	if (choix==1)
	{
	printf("Entrez un commentaire:\n"); 
	scanf("%s", com);
	listeCommentaire(commentaire, com);
	}

	if (choix==0)
	{
		listeCommentaire(commentaire, "-");
	}

	
}


void choice(Liste *solde, Element *last, Liste *transaction, ListeInfo *operation, ListeInfo *paiement, ListeInfo *commentaire, int acc){
	int choice;
   	printf("Que souhaitez-vous faire?\n");
   	printf("\n");
	printf("1. Consulter votre solde\n");
	printf("2. Faire un débit\n");
	printf("3. Faire un crédit\n");
	printf("4. Consulter votre historique\n");
	printf("5. Quitter\n");
	printf("\n");
	printf("Séléctionnez votre choix: ");
	scanf ("%d", &choice); 
	printf("\n");

	if (choice==1)
	{
		afficherlast(solde,last);
	}
	else if (choice==2)
	{
		acc++;
		debiter(solde, last,transaction, paiement, commentaire);
		listeOperation(operation,"Débit (-)");
	}
	else if (choice==3)
	{
		acc++;
		crediter(solde, last, transaction, paiement, commentaire);
		listeOperation(operation,"Credit (+)");

	}
	else if (choice==4)
	{
		afficherHistorique(solde, transaction, operation, paiement, commentaire, acc);
	}

	else if (choice==5){
		exit(EXIT_SUCCESS);
	}
	else 
		printf("Ce choix est impossible (tapez 1,2,3,4 ou 5)\n");
}



int main()
{
    Liste *solde = initialisation();
    Liste *transaction = initialisation();
    ListeInfo *operation = initialisationBis();
    ListeInfo *paiement = initialisationBis();
    ListeInfo *commentaire = initialisationBis();
    int acc; 

    printf("Bonjour, ");
	choice(solde, solde->premier, transaction, operation, paiement, commentaire, acc);
	printf("que souhaitez-vous faire maintenant?\n");
	printf("\n");
	printf("1. Revoir le menu\n");
	printf("2. Quitter\n");
	int boucle;
	scanf("%d",&boucle);
	if (boucle == 0){
		exit(EXIT_SUCCESS);
	}
	while (boucle==1){
		choice(solde, solde->premier, transaction, operation, paiement, commentaire, acc);
		printf("que souhaitez-vous faire maintenant?\n");
		printf("\n");
		printf("1. Revoir le menu\n");
		printf("2. Quitter\n");
		int boucle;
		scanf("%d",&boucle);
		if (boucle == 0){
		exit(EXIT_SUCCESS);
	}
	}

}
