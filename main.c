/* 

AUTHOR: ELTON IGOR CUNHA PEREIRA
GOAL: LEARNING

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCR 50
#define MAX 200

typedef struct{
    int id;
    char product[MAX_DESCR + 1];
    double price;
    int quantity;
} product;

typedef struct products{

    product prd;
    struct products *nextProduct;

} products;


void readsFile(products *list){

    products *aux = list;

    product component;


    /*

    Tornar o nome dinamico, conforme o usuario quiser. 
    Após escolhido um nome, se for carregar novamente, 
    questionar se deseja carregar no mesmo arquivo ou em um novo.
    
    */


    FILE *ptArq;
    ptArq = fopen("arquivo.txt", "r");
    char lineOfArchiveText[300];
    char *sub;
    char *text;
    char values[6][50];
    if(ptArq == NULL){
        printf("\tA PROBLEM OCCURRED OPENING THE NON-EXISTING FILE OR FILE\n");
        return 0;
    }else{
        while (fgets(lineOfArchiveText, 300, ptArq) != NULL){
            lineOfArchiveText[strcspn(lineOfArchiveText, "\n")] = 0;
            text = strtok(lineOfArchiveText, ";");
            int i = 0;
            while(text != NULL){
                strcpy(values[i],text);
                text = strtok(NULL, ";");
                i++;
            }/* ORGANIZAR ESTA PARTE DO CÓDIGO */
            if(lineOfArchiveText != NULL){
                char price[10], quantity[10], id[10];
                strcpy(id, values[0]);
                component.id = atoi(id);
                strcpy(price, values[1]);
                component.price = atof(price);
                strcpy(component.product, values[2]);
                strcpy(quantity, values[3]);
                component.quantity = atoi(quantity);
                registerProduct(component, aux);
            }else{
                puts("LOADED PRODUCTS");
            }
        }
        /* TO_DO - IMPLEMENTAR ATRIBUIÇÃO OS DADOS A ESTRUTURA OU CRIAR UMA FUNÇÃO A PARTE QUE RECEBA A LINHA*/
    }
    fclose(ptArq);
}


products *allocatesNewProduct(product component){
    products *newProduct;

    newProduct = (products *)malloc(sizeof(products));
    if (newProduct != NULL)
    {
        newProduct->prd = component;
        newProduct->nextProduct = NULL;
    }
    else
    {
        printf("ERROR ALLOCATING MEMORY\n");
    }
    return newProduct;
}

void editProductId(product component, products *list, int id){

    products *aux;

    /* CABEÇA */
    aux = list;
    while (aux->nextProduct != NULL && aux->prd.id != id){
        aux = aux->nextProduct;
    }
    if(aux->prd.id == id){
        printf("DO YOU WANT EDIT WHAT PROPERTY? \n1 -> PRODUCT NAME\n2 -> QUANTITY OF PRODUCTS\n3 -> PRODUCT PRICE\n4 -> ADD PRODUCT QUANTITY\n10 -> RETURN\n");
        int ope = -1;
        scanf("%d", &ope);
        while(ope != 10){
            if(ope == 1){
                char newName[MAX_DESCR];
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("WHAT IS THE NEW PRODUCT NAME?\n");
                fflush(stdin);
                scanf("%[^\n]s", newName);
                strcpy(aux->prd.product, newName);
            }else if(ope == 2){
                int newQuantity;
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("QUANTITY PRODUCT IS: %d\n", aux->prd.quantity);
                printf("WHAT IS THE NEW PRODUCT QUANTITY?\n");
                scanf("%d", &newQuantity);
                aux->prd.quantity = newQuantity;
            }else if(ope == 3){
                double newPrice;
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("PRICE PRODUCT IS: %.2lf\n", aux->prd.price);
                printf("WHAT IS THE NEW PRODUCT PRICE?\n");
                scanf("%lf", &newPrice);
                aux->prd.price = newPrice;
            }else if(ope == 4){
                int newQuantityAdd;
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("QUANTITY PRODUCT IS: %d\n", aux->prd.quantity);
                printf("WHAT IS THE NEW PRODUCT ADD QUANTITY?\n");
                scanf("%d", &newQuantityAdd);
                aux->prd.quantity += newQuantityAdd;
            }
            printf("DO YOU WANT EDIT WHAT PROPERTY? \n1 -> PRODUCT NAME\n2 -> QUANTITY OF PRODUCTS\n3 -> PRODUCT PRICE\n4 -> ADD PRODUCT QUANTITY\n10 -> RETURN\n");
            scanf("%d", &ope);
        }
    }
}

void editProductName(product component, products *list, char *name){

    products *aux;

    /* CABEÇA */
    aux = list;
    while (aux->nextProduct != NULL && strcmp(aux->prd.product, name) != 0){
        aux = aux->nextProduct;
    }
    if(strcmp(aux->prd.product, name) == 0){
        printf("DO YOU WANT EDIT WHAT PROPERTY? \n1 -> PRODUCT NAME\n2 -> QUANTITY OF PRODUCTS\n3 -> PRODUCT PRICE\n4 -> ADD PRODUCT QUANTITY\n10 -> RETURN\n");
        int ope = -1;
        scanf("%d", &ope);
        while(ope != 10){
            if(ope == 1){
                char newName[MAX_DESCR];
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("WHAT IS THE NEW PRODUCT NAME?\n");
                fflush(stdin);
                scanf("%[^\n]s", newName);
                strcpy(aux->prd.product, newName);
            }else if(ope == 2){
                int newQuantity;
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("QUANTITY PRODUCT IS: %d\n", aux->prd.quantity);
                printf("WHAT IS THE NEW PRODUCT QUANTITY?\n");
                scanf("%d", &newQuantity);
                aux->prd.quantity = newQuantity;
            }else if(ope == 3){
                double newPrice;
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("PRICE PRODUCT IS: %.2lf\n", aux->prd.price);
                printf("WHAT IS THE NEW PRODUCT PRICE?\n");
                scanf("%lf", &newPrice);
                aux->prd.price = newPrice;
            }else if(ope == 4){
                int newQuantityAdd;
                printf("NAME PRODUCT IS: %s\n", aux->prd.product);
                printf("QUANTITY PRODUCT IS: %d\n", aux->prd.quantity);
                printf("WHAT IS THE NEW PRODUCT ADD QUANTITY?\n");
                scanf("%d", &newQuantityAdd);
                aux->prd.quantity += newQuantityAdd;
            }
            printf("DO YOU WANT EDIT WHAT PROPERTY? \n1 -> PRODUCT NAME\n2 -> QUANTITY OF PRODUCTS\n3 -> PRODUCT PRICE\n4 -> ADD PRODUCT QUANTITY\n10 -> RETURN\n");
            scanf("%d", &ope);
        }
    }
}


void registerProduct(product component, products *list){
    products *newProduct, *aux;

    newProduct = allocatesNewProduct(component);
    /* PRIORIDADE */
    if (list->nextProduct == NULL){
        list->nextProduct = newProduct;
    }
    else{
        /* CABEÇA */
        aux = list;
        while (aux->nextProduct != NULL && aux->prd.id != newProduct->prd.id){
            aux = aux->nextProduct;
        }
        if(aux->prd.id == newProduct->prd.id){
            printf("DO YOU WANT TO ADD MORE PRODUCTS? \n1 -> YES or 2 -> NO\n");
            int ope = -1;
            scanf("%d", &ope);
            if(ope == 1){
                aux->prd.id = newProduct->prd.id;
                aux->prd.quantity += newProduct->prd.quantity;
            }else{
                printf("WE CANNOT REPLACE THE PRODUCT");
            }
        }else{
            /* INSERÇÃO */
            newProduct->nextProduct = aux->nextProduct;
            aux->nextProduct = newProduct;
        }
    }
}

void printList(products *list){
    products *aux = NULL;

    if(list->nextProduct != NULL){
        printf("ID | PRICE | QUANTITY | PRODUCT NAME:\n");
        for (aux = list->nextProduct; aux != NULL; aux = aux->nextProduct){
            printf("%02d | ", aux->prd.id);
            printf("%.2lf | ", aux->prd.price);
            printf("%02d | ", aux->prd.quantity);
            printf("%s\n", aux->prd.product);
        }
    }else{
        printf("NO REGISTERED PRODUCTS!\n");
    }
}

void printProductsById(products *list, int id){
    products *aux;

    aux = list;

    if(aux->nextProduct != NULL){
        while (aux->nextProduct != NULL && aux->prd.id != id){
            aux = aux->nextProduct;
        }
        if(aux->prd.id == id){
            printf("%02d |", aux->prd.id);
            printf(" %.2lf | ", aux->prd.price);
            printf("%s", aux->prd.product);
            printf(" | %02d\n", aux->prd.quantity);
        }else{
            printf("ID NOT EXISTS!\n");
        }
    }else{
        printf("NO PRODUCTS REGISTERED!\n");
    }
}


void printProductsByName(products *list, char *prod){
    products *aux;
    char *ptAux;

    aux = list;

    if(aux->nextProduct != NULL){
        while (aux->nextProduct != NULL && strcmp(aux->prd.product, prod) != 0){
            aux = aux->nextProduct;
        }
        if(strcmp(aux->prd.product, prod) == 0){
            printf("%02d |", aux->prd.id);
            printf(" %.2lf | ", aux->prd.price);
            printf("%s", aux->prd.product);
            printf(" | %02d\n", aux->prd.quantity);
        }else{
            printf("ID NOT EXISTS!\n");
        }
    }else{
        printf("NO PRODUCTS REGISTERED!\n");
    }
}

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

void saveProductsToFile(products *list){
	
	products *aux = NULL;

    FILE *archive;

    /*

    Tornar o nome dinamico, conforme o usuario quiser. 
    Após escolhido um nome, se for salvar novamente, 
    questionar se deseja salvar no mesmo arquivo ou em um novo.
    
    */

    archive = fopen("arquivo.txt", "w");

    if(archive == NULL){
        printf("OPENING ERROR OCCURRED\n");
    }else if(list->nextProduct != NULL){
        for (aux = list->nextProduct; aux != NULL; aux = aux->nextProduct){
            fprintf(archive, "%02d;%.2lf;%s;%02d;\n", aux->prd.id, aux->prd.price, aux->prd.product, aux->prd.quantity);
        }
        printf("SAVED SUCCESSFULLY!\n");
    }else{
        printf("NO PRODUCTS REGISTERED!\n");
    } 
    fclose(archive);
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