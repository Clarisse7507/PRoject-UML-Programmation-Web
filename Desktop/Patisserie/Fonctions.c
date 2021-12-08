//
// Created by vigna on 04/10/2021.
//

#include "Fonctions.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

Element_str* create_gout(char gout[] ){
    Element_str* nouv_gout;
    nouv_gout = (Element_str*)malloc(sizeof (Element_str));
    strcpy ((char*)nouv_gout->texte,(char*)gout);
    nouv_gout->next = NULL;
    return nouv_gout;

}

File_Commandes* f_commandes()
{
    File_Commandes * nouvelle_commande = malloc(sizeof(File_Commandes)*10);
    nouvelle_commande-> COMMANDE = NULL;
    return nouvelle_commande;
}

File_Degustation* f_degustation ()
{
    File_Degustation * gatgat = malloc(sizeof(File_Degustation));
    gatgat-> gat_com = NULL;
    return gatgat;
}



Element_str* initialiser_gouts(){
    Element_str* l_gouts = NULL;
    l_gouts = create_gout("Chocolat");
    l_gouts->next=create_gout("Vanille");
    l_gouts->next->next=create_gout("Fraise");
    l_gouts->next->next->next=create_gout("Abricot");
    l_gouts->next->next->next->next=create_gout("Pomme");
    l_gouts->next->next->next->next->next=create_gout("Banane");
    l_gouts->next->next->next->next->next->next=create_gout("Myrtille");
    return l_gouts;
}


int pas_de_commande ( File_Commandes * f_commandes){
    if(f_commandes -> COMMANDE == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void ajouter_commande_fin_liste(Element_str** nv_commande, char commande[50]){
    Element_str* temp;
    Element_str* nouv_el;
    nouv_el= create_gout(commande);
    if (*nv_commande==NULL){
        *nv_commande=nouv_el;
    }
    else{
        temp=*nv_commande;
        while(temp->next !=NULL){
            temp=temp->next;
        }
        temp->next=nouv_el;
    }
}

void passer_commande(char commande[50], File_Commandes* f_commandes ){
    int cpt=0;
    //on compte de commandes déjà dans la liste
    while((f_commandes->COMMANDE->next!=NULL) && (cpt<9)){
        f_commandes->COMMANDE =f_commandes->COMMANDE->next;
        cpt++;
    }
    //Si la file est pleine on ne peut rien prendre
    if (cpt>=9){
        printf("Impossible de prendre des commandes pour le moment. Revenez plus tard.\n");
    }
    else {
        Element_str* nv_commande = NULL;
        // On ajoute l'élément à la fin de la liste
        ajouter_commande_fin_liste(&nv_commande, commande);
        //Maintenant on l'ajoute à la fin de la file de commande
        if (pas_de_commande(f_commandes) == 1) {
            f_commandes->COMMANDE = nv_commande;
        } else {
            Element_str *temp = f_commandes->COMMANDE;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nv_commande;
        }
    }
}

void supprimer_commande(File_Commandes* f_commande){
    if (pas_de_commande(f_commande) == 1){
        f_commande= NULL;
    }
    else{
        Element_str* old = f_commande->COMMANDE;
        f_commande->COMMANDE = f_commande->COMMANDE->next;
        free(old);
    }
}

Element_str* creation_liste_commande( char commande[50]){
    Element_str* liste_commande=NULL;
    int i=0;
    while(commande[i]=='\0'){
        if (commande[i]=='C'){
            ajouter_commande_fin_liste(&liste_commande,"C");
        }
        if (commande[i]=='V'){
            ajouter_commande_fin_liste(&liste_commande,"V");
        }
        if (commande[i]=='F'){
            ajouter_commande_fin_liste(&liste_commande,"F");
        }
        if (commande[i]=='A'){
            ajouter_commande_fin_liste(&liste_commande,"A");
        }
        if (commande[i]=='P'){
            ajouter_commande_fin_liste(&liste_commande,"P");
        }
        if (commande[i]=='B'){
            ajouter_commande_fin_liste(&liste_commande,"B");
        }
        if (commande[i]=='M'){
            ajouter_commande_fin_liste(&liste_commande,"M");
        }
    }
    return liste_commande;

}



Element_str* traiter_commande(File_Commandes* f_commandes){
    // On supprime la première valeur de la file
    if (pas_de_commande(f_commandes)==1){
        return NULL;
    }
    else{
        Element_str* res=NULL;
        res= creation_liste_commande(f_commandes->COMMANDE->texte);// On convertit la chaine de caractère en liste chainée
        Element_str* temp= f_commandes->COMMANDE->next;
        Element_str* old = f_commandes->COMMANDE;
        f_commandes->COMMANDE=temp;// on récupère la première valeur
        f_commandes->COMMANDE= f_commandes->COMMANDE->next;// Et on la supprime de la file
        free(old);// on libère l'espace
        return res;
    }

}


Pile_Gouts* creer_pile_de_gouts(){
    Pile_Gouts * nouv_gout= (Pile_Gouts*)malloc(sizeof(Pile_Gouts));
    nouv_gout->gout =NULL;
    return nouv_gout;
}


Gateau* creer_gateau(Element_str* commande){
    //on créer un nouveau gateau pour le client
    Gateau* gateau_a_faire= (Gateau*)malloc(sizeof (Gateau));
    gateau_a_faire->commande = commande;
    // On ajoute les gouts au gateau
    gateau_a_faire->p_gouts = creer_pile_de_gouts();
    return gateau_a_faire;
}

void empile_gouts(Gateau* gout, char texte[50]){
    Gateau* nouv_el = malloc(sizeof(Gateau));
    nouv_el-> commande = texte;
    nouv_el->commande->next = gout->commande;
    gout->commande = nouv_el;
}

void construire_gateau(Gateau* gateau, Element_str* l_gouts){
    // On construit un element du gateau
    Element_str* temp;
    Element_str* temp_2;
    temp = l_gouts;
    temp_2=gateau->commande;
    while(gateau->commande !=NULL){
        temp=temp->next;
    }
    empile_gouts(&gateau->p_gouts->gout, temp->texte);
    temp=l_gouts;
    temp_2=temp_2->next;
}




int pas_de_gateau ( File_Degustation * f_degustation){
    if(f_degustation -> gat_com == NULL){
        return 1;
    }
    else{
        return 0;
    }
}






void livrer(Gateau* gateau, File_Degustation* f_degustation){
    // On ajoute le gateau qui vient d'être créé à la fin de la liste des livraison
    Element_gtx* nv_gateau =(Element_gtx*)malloc(sizeof (Element_gtx));
    nv_gateau->GATEAU = gateau;
    nv_gateau->next=f_degustation->gat_com;
    f_degustation->gat_com= nv_gateau;
    nv_gateau->GATEAU->commande=NULL;
}




void degustation(File_Degustation* f_degustation, int nb_parts){
    // On vérifie d'abord qu'il y ai bien un gateau
    if (pas_de_gateau(f_degustation)==1){
        f_degustation=NULL;
    }
    // Si il y a un gateau on l'enlève de la file de dégustation
    else{
        Element_gtx* res=(Element_gtx*)malloc(sizeof(Element_gtx));
        res=f_degustation->gat_com->GATEAU; //  /!\ On n'est pa sur de cette ligne
        Element_gtx* old = f_degustation->gat_com;
        f_degustation->gat_com= f_degustation->gat_com->GATEAU;
        free(old);
    }
    // Maintenant on dépile le gateau pour que l'utilisateur puisse manger son gateau étage par étage
    int reponse=1;
    while (nb_parts!=0 || reponse==1){
        printf("Voulez-vous manger une part de gateau? (Tapez 1 pour oui et 0 pour non):");
        scanf("%d",&reponse);
        if (reponse==1){
            nb_parts--;
        }
        printf("Il vous reste %d parts",nb_parts);
    }
}



