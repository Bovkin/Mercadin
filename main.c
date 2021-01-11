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


void leArquivo(produtos *lista){

    produtos *aux = lista;

    produto componente;

    FILE *ptArq;
    ptArq = fopen("arquivo.txt", "r");
    char linha[300];
    char *sub;
    char *texto;
    char valores[6][50];
    if(ptArq == NULL){
        printf("Ocorreu um problema ao abrir o arquivo.\n");
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
            }
            if(linha != NULL){
                char preco[10], quantidade[10], id[10];
                strcpy(id, valores[0]);
                componente.id = atoi(id);
                strcpy(preco, valores[1]);
                componente.preco = atof(preco);
                strcpy(componente.produto, valores[2]);
                strcpy(quantidade, valores[0]);
                componente.quantidade = atoi(quantidade);
                cadastraProcesso(componente, aux);
            }else{
                puts("PRODUTOS CARREGADOS");
            }
        }
        
        /* IMPLEMENTAR ATRIBUIÇÃO OS DADOS A ESTRUTURA OU CRIAR UMA FUNÇÃO A PARTE QUE RECEBA A LINHA*/
    }
    fclose(ptArq);
}


produtos *alocaNovoProduto(produto componente){
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


void cadastraProcesso(produto componente, produtos *lista){
    produtos *novoProduto, *aux;

    novoProduto = alocaNovoProduto(componente);
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

void imprimeLista(produtos *lista){
    produtos *aux = NULL;

    if(lista->nextProduto != NULL){
        for (aux = lista->nextProduto; aux != NULL; aux = aux->nextProduto){
            printf("%02d", aux->prd.id);
            printf(" %.2lf", aux->prd.preco);
            printf(" %s", aux->prd.produto);
            printf(" %d\n", aux->prd.quantidade);
        }
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    }
}

void imprimeProdutoId(produtos *lista, int id){
    produtos *aux;

    aux = lista;

    if(aux->nextProduto != NULL){
        while (aux->nextProduto != NULL && aux->prd.id != id){
            aux = aux->nextProduto;
        }
        if(aux->prd.id == id){
            printf("%02d", aux->prd.id);
            printf(" %.2lf", aux->prd.preco);
            printf(" %s", aux->prd.produto);
            printf(" %d\n", aux->prd.quantidade);
        }else{
            printf("ID NAO ENCONTRADO!\n");
        }
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    }
}


void imprimeProdutoNome(produtos *lista, char *prod){
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
    printf("\t3-PROCURAR PRODUTO POR ID\n");
    printf("\t4-PROCURAR PRODUTO POR NOME\n");
    printf("\t5- \n");
    printf("\t10-SAIR\n\t");
}

void salvaProdutosArquivo(produtos *lista){
	
	produtos *aux = NULL;

    FILE *arquivo;

    arquivo = fopen("arquivo.txt", "aw");

    if(arquivo == NULL){
        printf("OCORREU UM ERRO NA ABERTURA\n");
    }else if(lista->nextProduto != NULL){
        for (aux = lista->nextProduto; aux != NULL; aux = aux->nextProduto){
            fprintf(arquivo, "%02d;%.2lf;%s;%02d;\n", aux->prd.id, aux->prd.preco, aux->prd.produto, aux->prd.quantidade);
        }
    }else{
        printf("NENHUM PRODUTO CADASTRADO!\n");
    }
    printf("SALVO COM SUCESSO!\n");
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

    while(escolha != 10){
        if(escolha == 1){
            puts("Insira ID | PRECO | QUANTIDADE | PRODUTO");
            
            scanf("%d", &(componente.id));
            scanf("%lf", &(componente.preco));
            scanf("%d", &(componente.quantidade));
            scanf("%[^\n]s", &(componente.produto));
            
            cadastraProcesso(componente, lista);
        }else if(escolha == 2){
            imprimeLista(lista);
        }else if(escolha == 3){
            puts("Insira o ID a procurar");
            scanf("%d", &id);
            imprimeProdutoId(lista, id);
        }else if(escolha == 4){
            fflush(stdin);
            puts("Insira o Produto a procurar");
            scanf("%[^\n]s", palavra);
            imprimeProdutoNome(lista, palavra);
        }else if(escolha == 5){
            leArquivo(lista);
        }else if(escolha == 10){
            return 0;
        }
        menu();
        scanf("%d", &escolha);
    }
    salvaProdutosArquivo(lista);
    puts("SAINDO...");

    return 0;
}