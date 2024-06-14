#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
//les variables externes
typedef struct elem {
  int number;
  char symbole;
  struct elem *next;
} carte;

 carte *colonne[8];
 carte *serie[4];
 carte *temp[4];
 carte *deck;

int total = 0;
int *serienumber;
int *totalecolonne;
int table[8];




//les prototypes des fonctions


// Fonctions de vérification des conditions de déplacement
bool a_conditions_deplacement_valides(carte* carte1, carte* carte2);
bool a_conditions_deplacement_valides_serie(carte* carte1, carte* carte2);
bool a_conditions_deplacement_valides_temp(carte* carte1);
bool peut_deplacer_de_colonne_a_colonne(carte* de, carte* vers);
bool peut_deplacer_de_table_a_serie_ou_temp(carte* de_table, carte* vers_serie, carte* vers_temp);
bool peut_deplacer_de_temp_a_serie(carte* de_temp, carte* vers_serie);
bool est_jeu_bloque();

// Fonctions d'affichage
void afficher_etat_jeu();
void print();

// Fonctions d'initialisation
void initializeVariables();
void cree_une_carte(int position, int number, char symbole);
void generer_un_deck();
void distribue_la_table();

// Fonctions de mouvement des cartes
void de_table_a_serie();
void de_table_a_temp();
void de_temp_a_table();
void de_temp_a_serie();
void de_table_a_table();

// Fonction de réinitialisation du jeu
void reantliser_le_jeu();

// Fonction de vérification de la victoire
bool is_the_game_win();


#endif // FONCTIONS_H_INCLUDED
