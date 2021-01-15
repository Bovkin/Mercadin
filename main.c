#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCR 50
#define MAX 200

typedef struct{
    int id;
    char produto[MAX_DESCR + 1];
    double preco;
    int quantidade;
} produto;

typedef struct produtos{

    produto prd;
    struct produtos *nextProduto;

} produtos;


void readsFile(produtos *lista){

    produtos *aux = lista;

    produto componente;

    FILE *ptArq;
    ptArq = fopen("arquivo.txt", "r");
    char linha[300];
    char *sub;
    char *texto;
    char valores[6][50];
    if(ptArq == NULL){
        printf("\tOCORREU UM PROBLEMA AO ABRIR O ARQUIVO OU ARQUIVO INEXISTENTE\n");
        return 0;
    }else{
        while (fgets(linha, 300, ptArq) != NULL){
            linha[strcspn(linha, "\n")] = 0;
            texto = strtok(linha, ";");
            int i = 0;
            while(texto != NULL){
                strcpy(valores[i],texto);
                texto = strtok(NULL, ";");
                i++;
            }/* ORGANIZAR ESTA PARTE DO CÓDIGO */
            if(linha != NULL){
                char preco[10], quantidade[10], id[10];
                strcpy(id, valores[0]);
                componente.id = atoi(id);
                strcpy(preco, valores[1]);
                componente.preco = atof(preco);
                strcpy(componente.produto, valores[2]);
                strcpy(quantidade, valores[0]);
                componente.quantidade = atoi(quantidade);
                registerProduct(componente, aux);
            }else{
                puts("PRODUTOS CARREGADOS");
            }
        }
        /* TO_DO - IMPLEMENTAR ATRIBUIÇÃO OS DADOS A ESTRUTURA OU CRIAR UMA FUNÇÃO A PARTE QUE RECEBA A LINHA*/
    }
    fclose(ptArq);
}


produtos *allocatesNewProduct(produto componente){
    produtos *novoProduto;

    novoProduto = (produtos *)malloc(sizeof(produtos));
    if (novoProduto != NULL)
    {
        novoProduto->prd = componente;
        novoProduto->nextProduto = NULL;
    }
    else
    {
        printf("ERRO AO ALOCAR MEMORIA\n");
    }
    return novoProduto;
}


void registerProduct(produto componente, produtos *lista){
    produtos *novoProduto, *aux;

    novoProduto = allocatesNewProduct(componente);
    /* PRIORIDADE */
    if (lista->nextProduto == NULL){
        lista->nextProduto = novoProduto;
    }
    else{
        /* CABEÇA */
        aux = lista;
        while (aux->nextProduto != NULL && aux->prd.id != novoProduto->prd.id){
            aux = aux->nextProduto;
        }
        if(aux->prd.id == novoProduto->prd.id){
            printf("Deseja adicionar mais produtos? \n1 -> SIM ou 2 -> NAO\n");
            int ope = -1;
            scanf("%d", &ope);
            if(ope == 1){
                aux->prd.id = novoProduto->prd.id;
                aux->prd.quantidade += novoProduto->prd.quantidade;
            }else{
                printf("NAO PODEMOS SUBSTITUIR O PRODUTO");
            }
            
        }else{
            /* INSERÇÃO */
            novoProduto->nextProduto = aux->nextProduto;
            aux->nextProduto = novoProduto;
        }
    }
}

void printList(produtos *lista){
    produtos *aux = NULL;

    if(lista->nextProduto != NULL){
        for (aux = lista->nextProduto; aux != NULL; aux = aux->nextProduto){
            printf("%02d |", aux->prd.id);
            printf(" %.2lf |", aux->prd.preco);
            printf("%s", aux->prd.produto);
            printf(" | %02d\n", aux->prd.quantidade);
        }
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    }
}

void printProductsById(produtos *lista, int id){
    produtos *aux;

    aux = lista;

    if(aux->nextProduto != NULL){
        while (aux->nextProduto != NULL && aux->prd.id != id){
            aux = aux->nextProduto;
        }
        if(aux->prd.id == id){
            printf("%02d |", aux->prd.id);
            printf(" %.2lf |", aux->prd.preco);
            printf("%s", aux->prd.produto);
            printf(" | %02d\n", aux->prd.quantidade);
        }else{
            printf("ID NAO ENCONTRADO!\n");
        }
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    }
}


void printProductsByName(produtos *lista, char *prod){
    produtos *aux;

    char *ptAux;

    aux = lista;

    if(aux->nextProduto != NULL){
        while (aux->nextProduto != NULL){
            ptAux = strstr(aux->nextProduto->prd.produto, prod);
            if(ptAux != NULL){
                printf("%02d", aux->nextProduto->prd.id);
                printf(" %.2lf", aux->nextProduto->prd.preco);
                printf(" %s", aux->nextProduto->prd.produto);
                printf(" %d\n", aux->nextProduto->prd.quantidade);
                aux = aux->nextProduto;
            }else if(aux == NULL){
                printf("PRODUTO NAO ENCONTRADO!\n");
                aux = aux->nextProduto;
            }
        }
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    }
}

void menu(){
    printf("\tBEM-VINDO AO MERCADIN\n");
    printf("\tESCOLHA UMA OPCAO\n");
    printf("\t1-CADASTRAR PRODUTO\n");
    printf("\t2-LISTAR PRODUTOS\n");
    printf("\t3-GERENCIAR PRODUTOS POR ID\n");
    printf("\t4-GERENCIAR PRODUTOS POR NOME\n");
    printf("\t10-SAIR\n\t");
}
void subMenuID(){
    printf("\tBEM-VINDO AO MERCADIN\n");
    printf("\tESCOLHA UMA OPCAO\n");
    printf("\t1-PROCURAR PRODUTO POR ID\n");
    printf("\t2-EDITAR PRODUTO POR ID\n");
    printf("\t10-VOLTAR\n\t");
}
void subMenuNome(){
    printf("\tBEM-VINDO AO MERCADIN\n");
    printf("\tESCOLHA UMA OPCAO\n");
    printf("\t1-PROCURAR PRODUTO POR NOME\n");
    printf("\t2-EDITAR PRODUTO POR NOME\n");
    printf("\t10-VOLTAR\n\t");
}

void saveProductsToFile(produtos *lista){
	
	produtos *aux = NULL;

    FILE *arquivo;

    arquivo = fopen("arquivo.txt", "w");

    if(arquivo == NULL){
        printf("OCORREU UM ERRO NA ABERTURA\n");
    }else if(lista->nextProduto != NULL){
        for (aux = lista->nextProduto; aux != NULL; aux = aux->nextProduto){
            fprintf(arquivo, "%02d;%.2lf;%s;%02d;\n", aux->prd.id, aux->prd.preco, aux->prd.produto, aux->prd.quantidade);
        }
        printf("SALVO COM SUCESSO!\n");
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    } 
    fclose(arquivo);
}


int main(){

    produtos cabeca, *lista;

    cabeca.nextProduto = NULL;

    lista = &cabeca;

    produto componente;

    int escolha = -1;
    int id = -1;
    char palavra[MAX_DESCR + 1];
    
    readsFile(lista);

    while(escolha != 10){
        if(escolha == 1){
            int opcao = -1;
            while(opcao != 2){
                printf("Insira ID | PRECO | QUANTIDADE | PRODUTO:\n");
                
                scanf("%d", &(componente.id));
                scanf("%lf", &(componente.preco));
                scanf("%d", &(componente.quantidade));
                scanf("%[^\n]s", &(componente.produto));
                
                registerProduct(componente, lista);
                printf("DESEJA CADASTRAR MAIS ALGUM PRODUTO?\n1 - CADASTRAR ou 2 - NAO CADASTRAR: ");
                scanf("%d", &opcao);
            }
        }else if(escolha == 2){
            printList(lista);
        }else if(escolha == 3){
            system("clear||cls");
            int opcao = -1;           
            while(opcao != 10){
                subMenuID();
                printf("ESCOLHA UMA OPCAO: ");
                scanf("%d", &opcao);
                
                if(opcao == 1){
                    printf("INSIRA O ID: ");
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
            printf("INSIRA O NOME DO PRODUTO: ");
            scanf("%[^\n]s", palavra);
            printProductsByName(lista, palavra);
            
            while(opcao != 10){
                subMenuNome();
                puts("DESEJA PROCURAR OU EDITAR?\n1-PROCURAR ou 2-EDITAR\n");
                scanf("%d", &opcao);
            }
        }else if(escolha == 10){
            return 0;
        }
        menu();
        scanf("%d", &escolha);
    }
    saveProductsToFile(lista);
    puts("SAINDO...");

    return 0;
}