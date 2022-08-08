#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no {
    char nome[30];
    int populacao;
    float areaTotal;
    struct no* esq;
    struct no* dir;
}noArv;

noArv *abb_cria(void){
    return NULL;
}

void abb_imprime(noArv* raiz){
    if(raiz != NULL){
        printf("nome da cidade: %s, populacao: %d, area total: %.2f\n", raiz->nome, raiz->populacao, raiz->areaTotal);
        abb_imprime(raiz->esq);
        abb_imprime(raiz->dir);
    }
}

void abb_imprimeDeterminadaPopulacao(noArv* raiz, int populacao){
    if(raiz != NULL){
        abb_imprimeDeterminadaPopulacao(raiz->esq, populacao);
        if(raiz->populacao > populacao){
            printf("nome da cidade: %s, populacao: %d, area total: %.2fKm2\n", raiz->nome, raiz->populacao, raiz->areaTotal);
        }
        abb_imprimeDeterminadaPopulacao(raiz->dir, populacao);
    }
}

void abb_imprimeOrdemAlfabetica(noArv* raiz){
    if(raiz != NULL){
        abb_imprimeOrdemAlfabetica(raiz->esq);
        printf("nome da cidade: %s, populacao: %d, area total: %.2fKm2\n", raiz->nome, raiz->populacao, raiz->areaTotal);
        abb_imprimeOrdemAlfabetica(raiz->dir);
    }
}

noArv* abb_insere(noArv* raiz, char nome[30]){
    if(raiz == NULL){
        raiz = (noArv *) malloc (sizeof(noArv));
        strcpy(raiz->nome, nome);
        printf("Digite a populacao da cidade: ");
        scanf("%d", &raiz->populacao);
        printf("Digite a area total: ");
        scanf("%f", &raiz->areaTotal);
        raiz->esq = raiz->dir = NULL;
    }

    else if(strcmp(nome, raiz->nome) < 0){
        raiz->esq = abb_insere(raiz->esq, nome);
    }

    else if(strcmp(nome, raiz->nome) > 0){
        raiz->dir = abb_insere(raiz->dir, nome);
    }
    return raiz;
}

void abb_DensidadeDemograficaCidades(noArv *raiz){
    if(raiz != NULL){
        printf("Densidade demografica de %s: %.2f\n", raiz->nome, raiz->populacao/raiz->areaTotal);
        abb_DensidadeDemograficaCidades(raiz->esq);
        abb_DensidadeDemograficaCidades(raiz->dir);
    }
}

int abb_totalMunicipios(noArv * a){
    int esq, dir;

    if(a == NULL){
        return 0;
    }
    esq = abb_totalMunicipios(a->esq);
    dir = abb_totalMunicipios(a->dir);

    return (esq+dir+1);
}

float abb_somatorioArea(noArv *raiz){
    float total1, total2;

    if(raiz == NULL){
        return 0;
    }
    total1 = abb_somatorioArea(raiz->esq);
    total2 = abb_somatorioArea(raiz->dir);

    return (total1 + total2 + raiz->areaTotal);

}

void abb_maiorPop(noArv *raiz, int *x, char *nome){

    if(raiz == NULL){
        return 0;
    }

    if(raiz->populacao > *x){
        *x = raiz->populacao;
        strcpy(nome, raiz->nome);
    }

    abb_maiorPop(raiz->esq, x, nome);
    abb_maiorPop(raiz->dir, x, nome);

}



int main()
{
    noArv *raiz;
    raiz = abb_cria();
    int *x, opcao, populacaoCorte;
    char nome[30], nomeMaior[30];
    x=0;


    do{
        printf("\n1.Inserer municipio, 2.Contar o numero de municipios, 3.Mostrar municipios com uma determinada populacao,\n4.Mostrar densidade demografica dos municipios, 5.Mostrar somatorio da area em Km2, 6.Mostrar cidades em ordem \nalfabetica, 7.Mostrar cidade com maior populacao, 0.Encerrar: ");
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            printf("Digite o nome do municipio: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]%*c", &nome);
            raiz = abb_insere(raiz, nome);
            break;
        case 2:
            printf("\nQuantidade de municipios: %d\n", abb_totalMunicipios(raiz));
            break;
        case 3:
            printf("Digite um valor de corte para populacao: ");
            scanf("%d", &populacaoCorte);
            abb_imprimeDeterminadaPopulacao(raiz, populacaoCorte);
            break;
        case 4:
            abb_DensidadeDemograficaCidades(raiz);
            break;
        case 5:
            printf("\nSomatorio das areas de todos os municipios: %.2fKm2\n", abb_somatorioArea(raiz));
            break;
        case 6:
            printf("\nCidades em ordem alfabetica.\n");
            abb_imprimeOrdemAlfabetica(raiz);
            break;
        case 7:
            abb_maiorPop(raiz, &x, nomeMaior);
            printf("\n%s e a cidade com maior populacao.\n", nomeMaior);
            break;
        }

    }while(opcao != 0);




    return 0;
}
