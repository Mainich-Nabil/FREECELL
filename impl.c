#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>
#include"fonctions.h"


// Fonction pour v�rifier si deux cartes ont des conditions de d�placement valides
bool a_conditions_deplacement_valides(carte* carte1, carte* carte2) {
    bool couleur_depart = (carte1->symbole == 3 || carte1->symbole == 4);
    bool couleur_arrivee = (carte2->symbole == 3 || carte2->symbole == 4);

    return (carte1->number == carte2->number - 1) && (couleur_depart != couleur_arrivee);
}
//cette fonction est pour tester la possibilite dun mouvement vers un case serie
bool a_conditions_deplacement_valides_serie(carte *carte1 , carte* carte2){
     bool couleur_depart = (carte1->symbole == 3 || carte1->symbole == 4);
     bool couleur_arrivee = (carte2->symbole == 3 || carte2->symbole == 4);

     return (carte1->number == carte2->number +1) && (carte1->symbole == carte2->symbole) ;
}
//cette fonction pour tester les cases temporaire
bool a_conditions_deplacement_valides_temp(carte *carte1){
    return (carte1==NULL);
}

// Fonction pour v�rifier si une carte peut �tre d�plac�e d'une colonne � une autre
bool peut_deplacer_de_colonne_a_colonne(carte* de, carte* vers) {
    return a_conditions_deplacement_valides(de, vers);
}

// Fonction pour v�rifier si une carte peut �tre d�plac�e de la table � une s�rie ou un stockage temporaire
bool peut_deplacer_de_table_a_serie_ou_temp(carte* de_table, carte* vers_serie, carte* vers_temp) {
    return a_conditions_deplacement_valides_serie(de_table, vers_serie) || a_conditions_deplacement_valides_temp( vers_temp);
}

// Fonction pour v�rifier si une carte peut �tre d�plac�e du stockage temporaire � une s�rie
bool peut_deplacer_de_temp_a_serie(carte* de_temp, carte* vers_serie) {
    return a_conditions_deplacement_valides_serie(de_temp, vers_serie);
}

// Fonction pour v�rifier si le jeu est bloqu�
bool est_jeu_bloque() {
    int i, j;
    carte *temp1,*temp2;
    // V�rifier s'il existe un d�placement valide de colonne � colonne
    for (i = 0; i < 8; i++) {
         temp1=colonne[i];
         while(temp1->next!=NULL){
            temp1=temp1->next;
         }
        for (j = 0; j < 8; j++) {
            temp2=colonne[j];
            while(temp2->next!=NULL){
            temp2=temp2->next;
            if (i != j && peut_deplacer_de_colonne_a_colonne(temp1, temp2)) {
                return false;  // Il y a un d�placement valide, donc le jeu n'est pas bloqu�
            }
        }
    }

    // V�rifier si une carte peut �tre d�plac�e de la table � une s�rie ou un stockage temporaire
    for (i = 0; i < 8; i++)
        temp1=colonne[i];
        while(temp1->next!=NULL){
        temp1=temp1->next;
         }
        for (j = 0; j < 4; j++) {
            temp2=serie[j];
             while(temp2->next!=NULL){
             temp2=temp2->next;
         }
            if (peut_deplacer_de_table_a_serie_ou_temp(temp1, temp2, temp[j])) {
                return false;  // Il y a un d�placement valide, donc le jeu n'est pas bloqu�
            }
        }
    }

    // V�rifier si une carte peut �tre d�plac�e du stockage temporaire � une s�rie
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp2=serie[j];
            while(temp2->next!=NULL){
                temp2=temp2->next;
            }
            if (peut_deplacer_de_temp_a_serie(temp[i], temp2)) {
                return false;  // Il y a un d�placement valide, donc le jeu n'est pas bloqu�
            }
        }
    }

    // Si aucun d�placement valide n'est trouv�, le jeu est bloqu�
    return true;
}

// Fonction pour afficher l'�tat du jeu
void afficher_etat_jeu() {
    int a = est_jeu_bloque();
    if (a == 1) {

          printf(" ________  _____ ______   ________  _______           ________  ___      ___ _______   ________         \n");
        printf("|\\   ____\\|\\   _ \\  _   \\|\\   __  \\|\\  ___ \\         |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\        \n");
        printf("\\ \\  \\___|\\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\   __/|        \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\       \n");
        printf(" \\ \\  \\  __\\ \\  \\\\|__| \\  \\ \\   __  \\ \\  \\_|/__       \\ \\  \\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\      \n");
        printf("  \\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\\\\  \\ \\    / /   \\ \\  \\_|\ \\ \\  \\\\  \\|     \n");
        printf("   \\ \\_______\\ \\__\\    \\ \\__\\ \\__\\ \\__\\ \\_______\\       \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\    \n");
        printf("    \\|_______|\\|__|     \\|__|\\|__|\\|__|\\|_______|        \\|_______|\\|__|/       \\|_______|\\|__|\\|__|   \n");

        printf("\nLa situation est bloqu�e\n");
        getchar();
        getchar();

    } else {
        printf("\nLa situation n'est pas bloqu�e, continuez :\n");
        getchar();
        getchar();
    }
}


void de_temp_a_serie() {

  // D�clarer des variables pour stocker les saisies de l'utilisateur
  int temp_position, positionserie;

  // Obtenir les saisies de l'utilisateur pour les positions temp et s�rie
  printf("\nEntrez les positions temp et s�rie\nExemple : 1 1\n-> ");
  scanf("%d %d", &temp_position, &positionserie);

  // V�rifier si la position temp s�lectionn�e n'est pas vide
  if (temp[temp_position-1] != NULL) {
    // Pointeur vers la carte dans la position temp s�lectionn�e
    carte *tempchez = temp[temp_position-1];

    // Pointeur vers la derni�re carte de la s�rie s�lectionn�e
    carte *T_serie = serie[positionserie-1];

    // Parcourir la s�rie s�lectionn�e pour trouver le dernier �l�ment
    if (T_serie != NULL) {
      while (T_serie->next != NULL) {
        T_serie = T_serie->next;
      }
    }

    // V�rifier si le num�ro de la carte temp correspond au num�ro attendu dans la s�rie
    if ((tempchez->number) == (serienumber[positionserie-1] + 1)) {

      // V�rifier si le symbole de la carte temp correspond au symbole attendu dans la s�rie
      if (tempchez->symbole == positionserie + 2) {

        // Ins�rer la carte temp dans la s�rie
        if (serie[positionserie-1] == NULL) {
          // Premi�re insertion
          serie[positionserie-1] = tempchez;
        } else {
          // Insertion � n'importe quelle position
          T_serie->next = tempchez;
          tempchez->next = NULL;
        }

        // Mettre � jour le tableau temp pour indiquer que la position s�lectionn�e est maintenant vide
        temp[temp_position-1] = NULL;

        // Incr�menter le dernier num�ro de carte dans la s�rie
        serienumber[positionserie-1] += 1;
      }
      else {
        // Afficher un message d'erreur pour des symboles incompatibles
        printf("\nLes symboles ne sont pas compatibles pour l'insertion. Veuillez r�essayer.");
        getchar(); // Pour capturer le caract�re de nouvelle ligne restant dans le tampon
      }
    }// fin si le num�ro n'est pas compatible
    else {
      // Afficher un message d'erreur pour des num�ros incompatibles
      printf("\nLes num�ros ne sont pas compatibles. Veuillez r�essayer.");
      getchar(); // Pour capturer le caract�re de nouvelle ligne restant dans le tampon
    }
  } else {
    // Afficher un message d'erreur pour une position temp vide
    printf("\nLa position temp s�lectionn�e est vide.");
    getchar(); // Pour capturer le caract�re de nouvelle ligne restant dans le tampon
  }// fin sinon temp vide
} // fin de_temp_a_serie



void de_table_a_table() {
    int position_depart, position_arrive;
    bool couleur_depart, couleur_arrive; // 1=rouge 0=noir

    // Saisir les positions de d�part et d'arriv�e
    printf("\nEntrer la ligne de d�part et la ligne d'arriv�e, ex : 1 1\n");
    scanf("%d %d", &position_depart, &position_arrive);

    // Pointeurs vers la colonne de d�part et d'arriv�e
    carte *colonne_D = colonne[position_depart - 1];
    carte *colonne_A = colonne[position_arrive - 1];
    carte *pos_D = NULL;
    carte *pos_A = NULL;

    // Assurer que la colonne de d�part n'est pas vide
    if (colonne[position_depart - 1] != NULL) {
        // Trouver le dernier �l�ment de la colonne de d�part
        while (colonne_D->next != NULL) {
            pos_D = colonne_D;
            colonne_D = colonne_D->next;
        }

        // Trouver le dernier �l�ment de la colonne d'arriv�e
        while (colonne_A->next != NULL) {
            pos_A = colonne_A;
            colonne_A = colonne_A->next;
        }

        // Si la colonne d'arriv�e est vide
        if (colonne_A == NULL) {
            colonne[position_arrive - 1] = colonne_D;
            pos_D->next = NULL;
            totalecolonne[position_arrive - 1]++;
        } else {
            // V�rifier la couleur de la colonne d'arriv�e
            if (colonne_A->symbole == 3 || colonne_A->symbole == 4)
                couleur_arrive = true; // Rouge
            else
                couleur_arrive = false; // Noir

            // V�rifier la couleur de la colonne de d�part
            if (colonne_D->symbole == 3 || colonne_D->symbole == 4)
                couleur_depart = true; // Rouge
            else
                couleur_depart = false; // Noir

            // V�rifier la compatibilit� des couleurs et des num�ros
            if ((colonne_D->number) == ((colonne_A->number) - 1)) {
                if (couleur_arrive != couleur_depart) {
                    colonne_A->next = colonne_D;
                    pos_D->next = NULL;
                    totalecolonne[position_arrive - 1]++;
                } else {
                    // Afficher un message d'erreur pour une incompatibilit� de couleur
                    printf("\nV�rifier la compatibilit� des couleurs.");
                    getchar();
                    getchar();
                }
            } else {
                // Afficher un message d'erreur pour une incompatibilit� de num�ro
                printf("\nV�rifier la compatibilit� des num�ros.");
                getchar();
                getchar();
            }
        }
    } else {
        // Afficher un message d'erreur pour une colonne de d�part vide
        printf("\nLa colonne de d�part est vide.");
        getchar();
        getchar();
    }
}



void cree_une_carte(int position, int number, char symbole) {
  // Cr�e une carte dans la liste dynamique "deck"

  // Pointeur vers le d�but de la liste "deck"
  carte *chez = deck;

  // Alloue de la m�moire pour une nouvelle carte
  carte *N_carte = (carte*)malloc(sizeof(carte));

  // Initialise les propri�t�s de la nouvelle carte
  N_carte->number = number;
  N_carte->symbole = symbole;

  if (position == 0) {
    // Si la position est 0, la nouvelle carte devient la premi�re dans la liste
    N_carte->next = deck;
    deck = N_carte;
  } else {
    // Sinon, ins�re la nouvelle carte � la position sp�cifi�e dans la liste

    // Variable pour it�rer � la position sp�cifi�e
    int i;

    // Parcours la liste jusqu'� la position pr�c�dant celle de l'insertion
    for (i = 0; i < position - 1; i++) {
      chez = chez->next;
    }

    // Ins�re la nouvelle carte entre la position pr�c�dente et suivante
    N_carte->next = chez->next;
    chez->next = N_carte;
  }
}




void generer_un_deck() {
  // G�n�re un jeu de cartes m�lang�

  int position;
  int i, j;

  // Parcours les symboles de 3 � 6 (3 repr�sente le tr�fle, 4 le carreau, 5 le c�ur, 6 le pique)
  for (i = 3; i <= 6; i++) {
    // Parcours les nombres de 1 � 13 pour chaque symbole
    for (j = 1; j <= 13; j++) {
      // G�n�re une position al�atoire pour ins�rer la carte dans le deck tout en la m�langeant
      position = rand() % (total + 1);

      // Appelle la fonction pour cr�er une carte et l'ins�re � la position g�n�r�e
      cree_une_carte(position, j, i);

      // Incr�mente le total de cartes dans le deck
      total++;
    }
  }
}


void distribue_la_table() {
  // Distribue les cartes sur la table

  carte *chez, *pos, *chez_colonne;
  int index, i;

  // Parcourt les 7 piles de la table
  for (index = 0; index < 7; index++) {
    // Distribue 6 cartes dans chaque pile
    for (i = 0; i < 8; i++) {
      // Distribue les 4 derni�res cartes dans les piles de la table
      if (index == 6 && i > 3)
        break;

      // Initialise les pointeurs pour la liste "deck" et la pile actuelle "colonne[i]"
      chez = deck;
      pos = deck;
      chez_colonne = colonne[i];

      // Trouve le dernier �l�ment dans la liste "deck"
      while (chez->next != NULL) {
        chez = chez->next;
      }

      // V�rifie s'il y a un �l�ment pr�c�dent � chez dans la liste "deck"
      if (pos->next != NULL) {
        // Trouve l'avant-dernier �l�ment, s'il existe
        while (pos->next != chez) {
          pos = pos->next;
        }
      }

      // D�connecte chez de la liste "deck"
      pos->next = NULL;

      // Ins�re la carte chez dans la pile actuelle "colonne[i]"
      if (colonne[i] == NULL) {
        // Cas 1 : Premi�re position de la pile
        colonne[i] = chez;
        chez->next = NULL;
      } else {
        // Cas 2 : Autres positions de la pile
        while (chez_colonne->next != NULL) {
          chez_colonne = chez_colonne->next;
        }
        chez_colonne->next = chez; // Met � jour les pointeurs d'index
        chez->next = NULL;
      }

      // Incr�mente le nombre total de cartes dans la pile "colonne[i]"
       totalecolonne = table;
       *(totalecolonne + i)+=1;
    }
  }
}


void print() {
  char letter = 'a';

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

  WORD saved_attributes;

  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  system("cls");
  int i;
  for (i = 0; i < 4; i++) {
    printf("Temp %d: ", i + 1);
    if (temp[i] == NULL) {
      printf("[      ] ", i + 1);
    } else {
      if (temp[i]->symbole == 3 || temp[i]->symbole == 4)
        SetConsoleTextAttribute(hConsole, 0x74);
      else
        SetConsoleTextAttribute(hConsole, 0x70);
      if (temp[i]->number == 1)
        letter = 'A';
      if (temp[i]->number == 11)
        letter = 'J';
      if (temp[i]->number == 12)
        letter = 'Q';
      if (temp[i]->number == 13)
        letter = 'K';
      if (letter == 'a')
        printf("[%02d/%c]", temp[i]->number, temp[i]->symbole);
      else
        printf("[%c/ %c]", letter, temp[i]->symbole);
      letter = 'a';
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf(" ");
    }
  }
  printf("\n\n");
 carte *T_serie;
  for (i = 0; i < 4; i++) {
    T_serie = serie[i];
    if (T_serie == NULL) {
      printf("symbole %d-%c: [     ]", i + 1, i + 3);
    } else {
      printf("symbole %d-%c: ", i + 1, i + 3);
      while (T_serie != NULL) {
        if (T_serie->symbole == 3 || T_serie->symbole == 4)
          SetConsoleTextAttribute(hConsole, 0x74);
        else
          SetConsoleTextAttribute(hConsole, 0x70);
        if (T_serie->number == 1)
          letter = 'A';
        if (T_serie->number == 11)
          letter = 'J';
        if (T_serie->number == 12)
          letter = 'Q';
        if (T_serie->number == 13)
          letter = 'K';
        if (letter == 'a')
          printf("[%02d/%c]", T_serie->number, T_serie->symbole);
        else
          printf("[%c/ %c]", letter, T_serie->symbole);
        letter = 'a';
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");
        T_serie = T_serie->next;
      }
    }
    printf("\n");
  }
  printf("\n");
 carte *T_table;
  for (i = 0; i < 8; i++) {
    T_table = colonne[i];
    if (T_table == NULL) {
      printf("Table %d: [    ]", i + 1);
    } else {
      printf("Table %d: ", i + 1);
      while (T_table != NULL) {
        if (T_table->symbole == 3 || T_table->symbole == 4)
          SetConsoleTextAttribute(hConsole, 0x74);
        else
          SetConsoleTextAttribute(hConsole, 0x70);
        if (T_table->number == 1)
          letter = 'A';
        if (T_table->number == 11)
          letter = 'J';
        if (T_table->number == 12)
          letter = 'Q';
        if (T_table->number == 13)
          letter = 'K';
        if (letter == 'a')
          printf("[%02d/%c]", T_table->number, T_table->symbole);
        else
          printf("[%c/ %c]", letter, T_table->symbole);
        letter = 'a';
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ");
        T_table = T_table->next;
      }
    }
    printf("\n");
  }
  printf("\n");
}

void initializeVariables() {
  // Initialise les variables

  deck = NULL; // Initialise la liste "deck" � NULL

  int i;

  // Initialise les piles de la table et les compteurs associ�s
  for (i = 0; i < 8; i++) {
    colonne[i] = NULL; // Initialise chaque pile de la table � NULL
    totalecolonne[i] = 0; // Initialise le compteur du nombre total de cartes dans chaque pile � 0

    // Si l'indice est inf�rieur � 4, initialise �galement les piles "serie", "temp" et les compteurs associ�s
    if (i < 4) {
      serie[i] = NULL; // Initialise chaque pile "serie" � NULL
      temp[i] = NULL; // Initialise chaque pile "temp" � NULL
      serienumber[i] = 0; // Initialise le compteur du nombre total de cartes dans chaque pile "serie" � 0
    }
  }
}


void de_table_a_serie() { // d�place une carte de la table vers les piles de symboles

  int position_colonne, positionserie;
  printf("\nEntrez la position de la colonne et le symbole\nExemple : 1 1\n-> ");
  scanf("%d %d", &position_colonne, &positionserie);

  // Pointeurs pour la colonne de la table, la position de la table, et la pile de symboles
 carte *T_table = colonne[position_colonne-1];
 carte *tablepos = NULL;
 carte *T_serie = serie[positionserie-1];

  // Trouve le dernier �l�ment de la pile de symboles
  if (T_serie != NULL) {
    while (T_serie->next != NULL) {
      T_serie = T_serie->next;
    }
  }

  // Trouve la position avant-derni�re et derni�re de la colonne de la table
  while (T_table->next != NULL) {
    tablepos = T_table;
    T_table = T_table->next;
  }

  // V�rifie les conditions de nombre et de symbole
  if ((T_table->number) == (serienumber[positionserie-1] + 1)) {
    if (T_table->symbole == positionserie + 2) {

      // Ins�re la carte dans la pile de symboles
      if (serie[positionserie-1] == NULL) {
        serie[positionserie-1] = T_table; // premi�re insertion
      } else {
        T_serie->next = T_table; // insertion quelconque
      }

      // V�rifie s'il faut laisser la colonne de la table vide ou non
      if (tablepos == NULL) {
        T_serie = colonne[position_colonne-1];
        colonne[position_colonne-1] = NULL;
      } else {
        T_serie = T_table;
        tablepos->next = NULL;
      }

      // Met � jour le compteur du nombre total de cartes dans la pile de symboles
      serienumber[positionserie-1] += 1;

    } // fin si le symbole de la table est �gal � la pile de symboles
    else {
      printf("\nV�rifiez les symboles \n");
      getchar();
      getchar();
    } // fin sinon, symbole diff�rent
  } // fin si le nombre est dans l'ordre
  else {
    printf("\nV�rifiez la compatibilit� des nombres\nAPPUYEZ SUR ENTER POUR CONTINUER.");
    getchar();
    getchar();
  }
} // fin de_table_a_serie

void de_table_a_temp() { // d�place une carte de la table vers l'une des piles temporaires
  int position_colonne, temp_position;
  printf("\nEntrez la position de la colonne et la pile temporaire\nExemple : 1 1\n-> ");
  scanf("%d %d", &position_colonne, &temp_position);

  // Condition pour v�rifier si la pile temporaire est vide
  if (temp[temp_position-1] == NULL) {
    // Condition pour v�rifier si la colonne de la table a un �l�ment
    if (colonne[position_colonne-1] != NULL) {
     carte *T_table = colonne[position_colonne-1];
     carte *tablepos = NULL;

      // Traverse la position de la table
      while (T_table->next != NULL) {
        tablepos = T_table;
        T_table = T_table->next;
      }

      // V�rifie si la table deviendra vide
      if (tablepos == NULL) {
        temp[temp_position-1] = colonne[position_colonne-1];
        colonne[position_colonne-1] = NULL;
      } else {
        temp[temp_position-1] = T_table;
        tablepos->next = NULL;
      }
    } else {
      printf("\nLa table %d est vide. APPUYEZ SUR ENTER POUR CONTINUER.", position_colonne);
      getchar();
      getchar();

    }
  } else {
    printf("\nTemp %d est occup�e. APPUYEZ SUR ENTER POUR CONTINUER.", temp_position);
    getchar();
    getchar();

  }
} // fin de_table_a_temp

void de_temp_a_table() {
  int position_colonne, temp_position;
  bool tempColor, tableColor; // 1=rouge, 0=noir
  printf("\nEntrez le num�ro de la pile temporaire et celui de la colonne de la table\nExemple : 1 1\n-> ");
  scanf("%d %d", &temp_position, &position_colonne);

  carte *T_table = colonne[position_colonne-1];

  // V�rifie si la pile temporaire n'est pas vide
  if (temp[temp_position-1] != NULL) {
    // V�rifie si la colonne de la table est vide
    if (colonne[position_colonne-1] == NULL) {
      colonne[position_colonne-1] = temp[temp_position-1];
      temp[temp_position-1] = NULL;
    } else {
      // Traverse la colonne de la table pour trouver le dernier �l�ment
      while (T_table->next != NULL) {
        T_table = T_table->next;
      }

      // Si la colonne de la table est vide, ajoute l'�l�ment de la pile temporaire
      if (T_table == NULL) {
        T_table = temp[temp_position-1];
        temp[temp_position-1] = NULL;
      } else {
        // V�rifie la couleur de la carte dans la colonne de la table
        if ((T_table->symbole == 3) || (T_table->symbole == 4))
          tableColor = true;
        else
          tableColor = false;

        // V�rifie la couleur de la carte dans la pile temporaire
        if ((temp[temp_position-1]->symbole == 3) || (temp[temp_position-1]->symbole == 4))
          tempColor = true;
        else
          tempColor = false;

        // V�rifie la compatibilit� des couleurs
        if ((tempColor != tableColor)) {
          // V�rifie si le num�ro de la carte dans la pile temporaire est correct
          if ((temp[temp_position-1]->number == (T_table->number) - 1)) {
            // Met � jour les pointeurs si les conditions de couleur et de num�ro sont satisfaites
            T_table->next = temp[temp_position-1];
            temp[temp_position-1] = NULL;
          } else {
            printf("\nV�rifiez la compatibilit� des nombres !\nAPPUYEZ SUR ENTR�E POUR CONTINUER.");
            getchar();

          }
        } else {
          printf("\nV�rifiez la compatibilit� des couleurs !\nAPPUYEZ SUR ENTR�E POUR CONTINUER.");
          getchar();
          getchar();

        }
      }
    }
  } else {
    printf("\nPile temporaire vide ! APPUYEZ SUR ENTR�E POUR CONTINUER.");
    getchar();
    getchar();

  }
} // fin de_temp_a_table

void reantliser_le_jeu() { // parcourt tous les tableaux et matrices et lib�re tout
  carte *chez; // pointeur pour parcourir et lib�rer les cartes

  // Lib�re les piles temp
  for (int i = 0; i < 4; i++) {
    free(temp[i]);
  }

  // Lib�re les piles symbole
  for (int i = 0; i < 4; i++) {
    chez = serie[i];
    while (chez->next != NULL) {
      chez = serie[i];
      serie[i] = serie[i]->next;
      free(chez);
    }
    free(serie[i]);
  }

  // Lib�re les colonnes de la table
  for (int i = 0; i < 8; i++) {
    chez = colonne[i];
    while (chez->next != NULL) {
      chez = colonne[i];
      colonne[i] = colonne[i]->next;
      free(chez);
    }
    free(colonne[i]);
  }
} // fin reantliser_le_jeu

bool is_the_game_win() {
  bool is_win = true; // Initialise la variable de victoire � vrai par d�faut
  carte *symbole; // Pointeur pour parcourir les piles symbole

  // V�rifie les piles symbole
  for (int i = 0; i < 4; i++) {
    symbole = serie[i];

    if (symbole != NULL) {
      while (symbole->next != NULL) {
        symbole = symbole->next;
      }

      if (symbole->number != 13) { // V�rifie si les symboles sont complets (jusqu'� 13)
        is_win = false;
      }
    } else {
      is_win = false; // V�rifie s'il y a au moins un �l�ment dans chaque pile symbole
    }
  }

  if (is_win) { // Affiche l'�cran de victoire si les symboles sont complets
    system("cls"); // Efface l'�cran
    printf("                                                  $$\\                 $$\\ $$\\ $$\\ \n");
    printf("                                                  \\__|                $$ |$$ |$$ |\n");
    printf("$$\\   $$\\  $$$$$$\\  $$\\   $$\\       $$\\  $$\\  $$\\ $$\\ $$$$$$$\\        $$ |$$ |$$ |\n");
    printf("$$ |  $$ |$$  __$$\\ $$ |  $$ |      $$ | $$ | $$ |$$ |$$  __$$\\       $$ |$$ |$$ |\n");
    printf("$$ |  $$ |$$ /  $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |$$ |  $$ |      \\__|\\__|\\__|\n");
    printf("$$ |  $$ |$$ |  $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |$$ |  $$ |                  \n");
    printf("\\$$$$$$$ |\\$$$$$$  |\\$$$$$$  |      \\$$$$$\\$$$$  |$$ |$$ |  $$ |      $$\\ $$\\ $$\\ \n");
    printf(" \\____$$ | \\______/  \\______/        \\_____\\____/ \\__|\\__|  \\__|      \\__|\\__|\\__|\n");
    printf("$$\\   $$ |                                                                        \n");
    printf("\\$$$$$$  |                                                                        \n");
    printf(" \\______/                                                                         \n");

    getchar();
    getchar();

    reantliser_le_jeu(); // R�initialise le jeu
    return true; // Indique que le jeu est gagn�
  } else {
    return false; // Indique que le jeu n'est pas encore gagn�
  }
}
