//
// Created by vigna on 04/10/2021.
//

#ifndef PROJET_GATEAUX_FONCTIONS_H
#define PROJET_GATEAUX_FONCTIONS_H

#endif //PROJET_GATEAUX_FONCTIONS_H



typedef struct Element_str{
    char texte[50];
    struct Element_str* next;
}Element_str;

typedef struct Gateau{
    struct Element_str* commande;
    struct Pile_Gouts* p_gouts;
}Gateau;

typedef struct File_Commandes{
    struct Element_str* COMMANDE;
    //struct Element_str* next;
}File_Commandes;

typedef struct Pile_Gouts{
    struct Element_str* gout;
}Pile_Gouts;

typedef struct Element_gtx{
    struct Gateau* GATEAU;
    struct Element_gtx* next;
}Element_gtx;

typedef struct File_Degustation{
    struct Element_gtx* gat_com;
}File_Degustation;

Element_str* create_gout(char gout[] );
File_Commandes* f_commandes();
File_Degustation* f_degustation ();
Element_str* initialiser_gouts();
int pas_de_commande ( File_Commandes * f_commandes);
void passer_commande( char commande[50], File_Commandes* f_commandes );
void supprimer_commande(File_Commandes* f_commande);
Element_str* traiter_commande(File_Commandes* f_commandes);
Gateau* creer_gateau(Element_str* commande);
void construire_gateau(Gateau* gateau, Element_str* l_gouts);
int pas_de_gateau ( File_Degustation * f_degustation);
void livrer(Gateau* gateau, File_Degustation* f_degustation);
int pas_detage (Pile_Gouts* gouts_gateau);
void degustation(File_Degustation* f_degustation, int nb_parts);
void ajouter_commande_fin_liste(Element_str** nv_commande, char commande[50]);
Element_str* creation_liste_commande( char commande[50]);
Pile_Gouts* creer_pile_de_gouts();
void empile_gouts(Gateau* gout, char texte[50]);

## test branch patisserie_2