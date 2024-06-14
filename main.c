#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>
#include"fonctions.h"
#include"impl.c"



int main(int argc, char **argv) {


    printf(" ________  _________  ________  ________  _________        ________  ________  _____ ______   _______      \n");
    printf("|\\   ____\\|\\___   ___\\\\   __  \\|\\   __  \\|\\___   ___\\     |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     \n");
    printf("\\ \\  \\___|\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_|     \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    \n");
    printf(" \\ \\_____  \\   \\ \\  \\ \\ \\   __  \\ \\   _  _\\   \\ \\  \\       \\ \\  \\  __\\ \\   __  \\ \\  \\|__| \\  \\ \\  \\_|/__  \n");
    printf("  \\|____|\\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\\\  \\|   \\ \\  \\       \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\ \\ \n");
    printf("    ____\\_\\  \\   \\ \\__\\ \\ \\__\\ \\__\\ \\__\\\\ _\\    \\ \\__\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\\n");
    printf("   |\\_________\\   \\|__|  \\|__|\\|__|\\|__|\\|__|    \\|__|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|\n");
    printf("   \\|_________|                                                                                             \n");
    printf("                                                                                                            \n");
    printf("                                                                                                            \n");

    printf("ENTRER pour jouer le jeu  :");
    getchar();




    system("color 20");
    int choice = 0;
    srand(time(NULL));
    generer_un_deck();
    distribue_la_table();

    while (choice != 8) {
        if (is_the_game_win()) {
            reantliser_le_jeu();
            return 0;
        }

        print();
        printf("\t\tles mouvement possible sont :\n");
        printf("Table->Table\t Table->Suit\t Temp->Table\t Temp->suit\t Table->Temp\n");
        //printf("*********************menu des options posiibles*********************\n");
        printf("*            1- de Table a symbole                                    *\n");
        printf("*            2- de Table a Temp                              *\n");
        printf("*            3- de Temp a Table                              *\n");
        printf("*            4- de Temp a Symbole                            *\n");
        printf("*            5- Table to Table                               *\n");
        printf("*            6- tester si le jeu est blocker                 *\n");
        printf("*            7-  Exit                                        *\n");
        //printf("********************************************************************\n");
        printf("Choose: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                de_table_a_serie();
                break;
            case 2:
               de_table_a_temp();
                break;
            case 3:
                de_temp_a_table();
                break;
            case 4:
                de_temp_a_serie();
                break;
            case 5:
                de_table_a_table();
                break;
            case 7:
                system("cls");
                reantliser_le_jeu();
                return 0;
                break;
            case 6:
                afficher_etat_jeu();
                break;
            default:
                printf("\nInvalid option (enter)\n");
                getchar();
                break;
        }
    }

    return 0;
}
