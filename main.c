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


void readsFile(products *lista){

    products *aux = lista;

    product componente;

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
                componente.id = atoi(id);
                strcpy(price, values[1]);
                componente.price = atof(price);
                strcpy(componente.product, values[2]);
                strcpy(quantity, values[3]);
                componente.quantity = atoi(quantity);
                registerProduct(componente, aux);
            }else{
                puts("LOADED PRODUCTS");
            }
        }
        /* TO_DO - IMPLEMENTAR ATRIBUIÇÃO OS DADOS A ESTRUTURA OU CRIAR UMA FUNÇÃO A PARTE QUE RECEBA A LINHA*/
    }
    fclose(ptArq);
}


products *allocatesNewProduct(product componente){
    products *novoProduct;

    novoProduct = (products *)malloc(sizeof(products));
    if (novoProduct != NULL)
    {
        novoProduct->prd = componente;
        novoProduct->nextProduct = NULL;
    }
    else
    {
        printf("ERROR ALLOCATING MEMORY\n");
    }
    return novoProduct;
}


void registerProduct(product componente, products *lista){
    products *novoProduct, *aux;

    novoProduct = allocatesNewProduct(componente);
    /* PRIORIDADE */
    if (lista->nextProduct == NULL){
        lista->nextProduct = novoProduct;
    }
    else{
        /* CABEÇA */
        aux = lista;
        while (aux->nextProduct != NULL && aux->prd.id != novoProduct->prd.id){
            aux = aux->nextProduct;
        }
        if(aux->prd.id == novoProduct->prd.id){
            printf("DO YOU WANT TO ADD MORE PRODUCTS? \n1 -> YES or 2 -> NO\n");
            int ope = -1;
            scanf("%d", &ope);
            if(ope == 1){
                aux->prd.id = novoProduct->prd.id;
                aux->prd.quantity += novoProduct->prd.quantity;
            }else{
                printf("WE CANNOT REPLACE THE PRODUCT");
            }
            
        }else{
            /* INSERÇÃO */
            novoProduct->nextProduct = aux->nextProduct;
            aux->nextProduct = novoProduct;
        }
    }
}

void printList(products *lista){
    products *aux = NULL;

    if(lista->nextProduct != NULL){
        printf("ID | PRICE | QUANTITY | PRODUCT NAME:\n");
        for (aux = lista->nextProduct; aux != NULL; aux = aux->nextProduct){
            printf("%02d | ", aux->prd.id);
            printf("%.2lf | ", aux->prd.price);
            printf("%02d | ", aux->prd.quantity);
            printf("%s\n", aux->prd.product);
        }
    }else{
        printf("NO REGISTERED PRODUCTS!\n");
    }
}

void printProductsById(products *lista, int id){
    products *aux;

    aux = lista;

    if(aux->nextProduct != NULL){
        while (aux->nextProduct != NULL && aux->prd.id != id){
            aux = aux->nextProduct;
        }
        if(aux->prd.id == id){
            printf("%02d |", aux->prd.id);
            printf(" %.2lf |", aux->prd.price);
            printf("%s", aux->prd.product);
            printf(" | %02d\n", aux->prd.quantity);
        }else{
            printf("ID NOT EXISTS!\n");
        }
    }else{
        printf("NO PRODUCTS REGISTERED!\n");
    }
}


void printProductsByName(products *lista, char *prod){
    products *aux;

    char *ptAux;

    aux = lista;

    if(aux->nextProduct != NULL){
        while (aux->nextProduct != NULL){
            ptAux = strstr(aux->nextProduct->prd.product, prod);
            if(ptAux != NULL){
                printf("%02d", aux->nextProduct->prd.id);
                printf(" %.2lf", aux->nextProduct->prd.price);
                printf(" %s", aux->nextProduct->prd.product);
                printf(" %d\n", aux->nextProduct->prd.quantity);
                aux = aux->nextProduct;
            }else if(aux == NULL){
                printf("PRODUCT NOT EXISTS\n");
                aux = aux->nextProduct;
            }
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
void subMenuNome(){
    printf("\tWELCOME THE MERCADIN\n");
    printf("\tCHOOSE AN OPTION\n");
    printf("\t1-SEARCH PRODUCT BY NAME\n");
    printf("\t2-EDIT PRODUCT BY NAME\n");
    printf("\t10-RETURN\n\t");
}

void saveProductsToFile(products *lista){
	
	products *aux = NULL;

    FILE *arquivo;

    arquivo = fopen("arquivo.txt", "w");

    if(arquivo == NULL){
        printf("OPENING ERROR OCCURRED\n");
    }else if(lista->nextProduct != NULL){
        for (aux = lista->nextProduct; aux != NULL; aux = aux->nextProduct){
            fprintf(arquivo, "%02d;%.2lf;%s;%02d;\n", aux->prd.id, aux->prd.price, aux->prd.product, aux->prd.quantity);
        }
        printf("SAVED SUCCESSFULLY!\n");
    }else{
        printf("NO PRODUCTS REGISTERED!\n");
    } 
    fclose(arquivo);
}


int main(){

    products cabeca, *lista;

    cabeca.nextProduct = NULL;

    lista = &cabeca;

    product componente;

    int escolha = -1;
    int id = -1;
    char palavra[MAX_DESCR + 1];
    
    readsFile(lista);

    while(escolha != 10){
        if(escolha == 1){
            int opcao = -1;
            while(opcao != 2){
                printf("INSERT IN ORDER\nID | PRICE | QUANTITY | PRODUCT NAME:\n");
                
                scanf("%d", &(componente.id));
                scanf("%lf", &(componente.price));
                scanf("%d", &(componente.quantity));
                scanf("%[^\n]s", &(componente.product));
                
                registerProduct(componente, lista);
                printf("WANT TO REGISTER ANY OTHER PRODUCTS?\n1 - REGISTER ou 2 - NO REGISTER: ");
                scanf("%d", &opcao);
            }
        }else if(escolha == 2){
            printList(lista);
        }else if(escolha == 3){
            system("clear||cls");
            int opcao = -1;           
            while(opcao != 10){
                subMenuID();
                printf("CHOOSE AN OPTION: ");
                scanf("%d", &opcao);
                
                if(opcao == 1){
                    printf("INSERT ID: ");
                    scanf("%d", &id);
                    printProductsById(lista, id);
                    system("pause");
                    system("clear||cls");
                }else if(opcao == 10){
                    system("clear||cls");
                }
            }
            
        }else if(escolha == 4){
            int opcao = -1;
            fflush(stdin);
            printf("INSERT PRODUCT NAME: ");
            scanf("%[^\n]s", palavra);
            printProductsByName(lista, palavra);
            
            while(opcao != 10){
                subMenuNome();
                puts("DO YOU WANT TO SEARCH OR EDIT?\n1-SEARCH ou 2-EDIT\n");
                scanf("%d", &opcao);
            }
        }else if(escolha == 10){
            return 0;
        }
        menu();
        scanf("%d", &escolha);
    }
    saveProductsToFile(lista);
    puts("GOING OUT...");

    return 0;
}