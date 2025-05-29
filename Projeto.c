#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char nome[50];
} morador;

typedef struct {
    char tipo;
    char modelo[20];
    char cor[10];
} veiculo;

typedef struct {
    char unsigned numeroDoApartamento;
    char numeroDeMoradores;
    char numeroDeCarros;
    char numeroDeMotos;
    morador morador[5];
    veiculo veiculos[2];
} apartamento;

typedef struct {
    apartamento apartamentos[41];
} condominio;


void *copiarString(char *origem, char *destino) {
    char *retorno = *destino;

    while (*origem != "\O") {
        *origem = *destino;
        *origem++;
        *destino++;
    }

    return retorno;
}

void carregarApartamentos(condominio *cond) {

    char andar = 10;
    char numero = 1;
    char aux;

    cond -> apartamentos[0].numeroDoApartamento = 0;
    cond -> apartamentos[0].numeroDeMoradores = 0;
    cond -> apartamentos[0].numeroDeCarros = 0;
    cond -> apartamentos[0].numeroDeMotos = 0;

    for (int i = 1; i <= 40; i++) {
        aux = andar + numero;
        cond -> apartamentos[i].numeroDoApartamento = aux;
        cond -> apartamentos[i].numeroDeMoradores = 0;
        cond -> apartamentos[i].numeroDeCarros = 0;
        cond -> apartamentos[i].numeroDeMotos = 0;

        if(numero == 4) {
            numero = 1;
            andar += 10;
        }

        numero++;
    }

    printf("\n\n");
}

void digitarApartamento(apartamento *apto) {

    printf("\nNumero do Apartamento: %i\n", apto -> numeroDoApartamento);
    

    printf("Moradores: \n");


    for (int j = 0; j < 5; j++) {
        if (j < apto -> numeroDeMoradores) {
            printf("    %p\n", &apto -> morador[j].nome);
        } else {
            printf("    NIL\n");
        }
    }

    printf("Veiculos: \n");

    for (int j = 0; j < 2; j++) {
        if (apto -> numeroDeCarros > 0) {
            if (j < apto -> numeroDeCarros) {
                printf("    Carro: %p, %p\n", apto -> veiculos[j].modelo, apto -> veiculos[j].cor);
            }else {
                printf("    NIL\n");
            }
        } else {
            if (j < apto -> numeroDeMotos) {
                printf("    Moto: %p, %p\n", apto -> veiculos[j].modelo, apto -> veiculos[j].cor);
            }else {
                printf("    NIL\n");
            }
        }
    }
}

void infoGeral(condominio *cond) {
    for (int i = 1; i <= 40; i++) {
        digitarApartamento(&cond -> apartamentos[i]);
    }
}

apartamento *buscarApartamento(condominio *cond, char unsigned numero) {
    char finalizar = 0;
    char comeco = 1;
    char final = 40;
    char media;

    while (finalizar == 0) {
        media = (comeco + final)/2;

        if (comeco+1 == final) {
            if (cond -> apartamentos[comeco].numeroDoApartamento == numero) {
                return &cond -> apartamentos[comeco];
            }
            if (cond -> apartamentos[final].numeroDoApartamento == numero) {
                return &cond -> apartamentos[final];
            }
            return &cond -> apartamentos[0];
        }
        if (cond -> apartamentos[media].numeroDoApartamento == numero) {
            return &cond -> apartamentos[media];
        }
        if (cond -> apartamentos[media].numeroDoApartamento > numero) {
            final = media;
        }
        if (cond -> apartamentos[media].numeroDoApartamento < numero) {
            comeco = media;
        }

    }
}

void infoApartamento(condominio *cond, char unsigned numero) {
    apartamento *apto = buscarApartamento(cond, numero);
    if (apto -> numeroDoApartamento == 0) {
        printf("\nNumero do apartamento invalido");
    } else {
        digitarApartamento(apto);
    }
}

void registrarMorador(char *nome,condominio *cond, char unsigned numeroDoApartamento) {
    apartamento *apto = buscarApartamento(cond, numeroDoApartamento);
    if(apto -> numeroDeMoradores == 5){
        printf("Operacao invalida, o apartamento esta cheio");
    } else{
        copiarString(nome, &apto -> morador[apto -> numeroDeMoradores]);
        apto -> numeroDeMoradores++;
    }
}



int main() {
    condominio cond;
    carregarApartamentos(&cond);

    // for (int i = 0; i < 40; i++) {
    //     if (i%4 == 0) {
    //         printf("\n");
    //     }
    //     printf("%i, ", condominio.apartamentos[i].numeroDoApartamento);
    // }

    // infoGeral(&cond);

    // infoApartamento(&cond, 134);

    registrarMorador("Danilo de Padua", &cond,  11);
    infoApartamento(&cond, 12);
}