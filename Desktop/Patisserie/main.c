#include <stdio.h>
#include "cmake-build-debug/Fonctions.h"


int main() {
    //Créons notre file de commandes
    File_Commandes* Les_Commandes=f_commandes();

    //Ensuite on créer la file de dégustation
    File_Degustation* Les_Degustations= f_degustation();

    //On créer la liste de gouts

    printf("Bonjour bienvenue à la patisserie milles-files passer votre commande. \n");
    int stop_gateau=0;
    int nb_commandes=0;
    while((stop_gateau==0)||(nb_commandes<10)) {
        nb_commandes++;
        int nb_etages;
        char gouts_client[50];
        //Le client passe sa commande
        printf("Combien d'etages voulez-vous pour votre gateau ?\n");
        scanf("%d", &nb_etages);
        printf("Voici les gouts:\n Chocolat:'C'\n Vanille:'V'\n Fraise:'F'\n Abricot:'A'\n Pomme:'P'\n Banane:'B'\n Myrtille:'M'\n");
        for (int i = 0; i < nb_etages; i++) {
            printf("Donnez-nous un gout que vous voulez.\n ");
            scanf("%s", &gouts_client[i]);// Le client entre ses gouts un par un
        }
        //On enregistre sa commande
        passer_commande(gouts_client, Les_Commandes);
        printf("Votre commande a ete prise en compte elle est en cours de traitement\n");
        Element_str *commande_de_gouts = traiter_commande(Les_Commandes);




        //Maintenant que la commande est traitée il faut construire le gateau
        Gateau *nouveau_gateau = creer_gateau(Les_Commandes->COMMANDE);
        nouveau_gateau->commande = commande_de_gouts;
        Element_str* liste_de_gouts;
        construire_gateau(nouveau_gateau, liste_de_gouts);

        //Le gateau est construit il faut maintenant le livrer
        livrer(nouveau_gateau, Les_Degustations);
        printf("Voulez-vous refaire une commande? (0 pour oui et 1 pour non\n");
        scanf("%d",&stop_gateau);
    }

    // Il faut maintenant passer à la dégustation
    while(pas_de_gateau(Les_Degustations)==1) {
        printf("Votre gateau est pret vous pouvez maintenant le déguster.\n");
        int nb_parts;
        printf("Combien de parts voulez-vous?\n");
        scanf("%d", &nb_parts);
        degustation(Les_Degustations,nb_parts);
    }
    printf("Et voilà-vous avez tout mangé");

    return 0;
}
