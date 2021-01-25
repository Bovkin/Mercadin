/* 

AUTHOR: ELTON IGOR CUNHA PEREIRA
GOAL: LEARNING

Header about Marcadin :)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

void menu(){
    printf("\tWELCOME THE MERCADIN\n");
    printf("\tCHOOSE AN OPTION\n");
    printf("\t1-REGISTER PRODUCT\n");
    printf("\t2-LIST PRODUCTS\n");
    printf("\t3-MANAGE PRODUCTS BY ID\n");
    printf("\t4-MANAGE PRODUCTS BY NAME\n");
    printf("\t10-EXIT\n\t");
}
void subMenuID(){
    printf("\tWELCOME THE MERCADIN\n");
    printf("\tCHOOSE AN OPTION\n");
    printf("\t1-SEARCH PRODUCT BY ID\n");
    printf("\t2-EDIT PRODUCT BY ID\n");
    printf("\t10-RETURN\n\t");
}
void subMenuName(){
    printf("\tWELCOME THE MERCADIN\n");
    printf("\tCHOOSE AN OPTION\n");
    printf("\t1-SEARCH PRODUCT BY NAME\n");
    printf("\t2-EDIT PRODUCT BY NAME\n");
    printf("\t10-RETURN\n\t");
}

int main(){

    products headOfList, *list;

    headOfList.nextProduct = NULL;

    list = &headOfList;

    product component;

    int choice = -1;
    int id = -1;
    char word[MAX_DESCR + 1];
    
    readsFile(list);


    /*

    COMEÇAR A DESMEMBRAR FUNÇÕES DO CÓDIGO EM HEADERS E ADICIONAR FUNÇÕES DE MENUS PARA REUTILIZAÇÃO DE CODIGO.

    */

    while(choice != 10){
        if(choice == 1){
            int option = -1;
            while(option != 2){
                printf("INSERT IN ORDER\nID | PRICE | QUANTITY | PRODUCT NAME:\n");

                scanf("%d", &(component.id));
                scanf("%lf", &(component.price));
                scanf("%d ", &(component.quantity));
                scanf("%[^\n]s", &(component.product));

                registerProduct(component, list);
                printf("WANT TO REGISTER ANY OTHER PRODUCTS?\n1 - REGISTER or 2 - NO REGISTER: ");
                scanf("%d", &option);
            }
        }else if(choice == 2){
            printList(list);
        }else if(choice == 3){
            system("clear||cls");
            int option = -1;           
            while(option != 10){
                subMenuID();
                scanf("%d", &option);
                
                if(option == 1){
                    printf("INSERT ID: ");
                    scanf("%d", &id);
                    printProductsById(list, id);
                    system("pause");
                    system("clear||cls");
                }else if(option == 2){
                    printf("INSERT ID: ");
                    scanf("%d", &id);
                    editProductId(component, list, id);
                }else if(option == 10){
                    system("clear||cls");
                }
            }
        }else if(choice == 4){
            system("clear||cls");
            int option = -1;       
            while(option != 10){
                subMenuName();
                scanf("%d", &option);
                
                if(option == 1){
                    printf("INSERT NAME: ");
                    fflush(stdin);
                    scanf("%[^\n]s", word);
                    printProductsByName(list, word);
                    system("pause");
                    system("clear||cls");
                }else if(option == 2){
                    printf("INSERT NAME: ");
                    fflush(stdin);
                    scanf("%[^\n]s", word);
                    editProductName(component, list, word);
                    system("pause");
                    system("clear||cls");
                }else if(option == 10){
                    system("clear||cls");
                }
            }
        }else if(choice == 10){
            return 0;
        }
        menu();
        scanf("%d", &choice);
    }
    saveProductsToFile(list);
    puts("GOING OUT...");

    return 0;
}