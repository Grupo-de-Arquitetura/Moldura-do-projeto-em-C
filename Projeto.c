#include <stdio.h>
#include <stdlib.h>



//                   Estrutura dos dados utilizados

typedef struct {
    char nome[51];
} morador;

typedef struct {
    char tipo;
    char modelo[21];
    char cor[11];
} veiculo;

typedef struct {
    char unsigned numeroDoApartamento;
    char numeroDeMoradores;
    char numeroDeCarros;
    char numeroDeMotos;
    char numeroDeVeiculos;
    morador moradores[5];
    veiculo veiculos[2];
} apartamento;

typedef struct {
    char unsigned numeroDeApartamentosOcupados;
    apartamento apartamentos[41];
} condominio;
















//                  FUnções auxiliares para debugging

void carregarApartamentos(condominio *cond) {

    char andar = 10;
    char numero = 1;
    char aux;

    cond -> apartamentos[0].numeroDoApartamento = 0;

    for (int i = 1; i <= 40; i++) {
        aux = andar + numero;
        cond -> apartamentos[i].numeroDoApartamento = aux;
        cond -> apartamentos[i].numeroDeMoradores = 0;
        cond -> apartamentos[i].numeroDeVeiculos = 0;
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

void digitarString(char *string){
    char i = 0;

    while(string[i] != '\0'){
        printf("%c", string[i]);
        i++;
    }
}

void digitarApartamento(apartamento *apto) {

    printf("\n\nNumero do Apartamento: %i\n", apto -> numeroDoApartamento);
    

    printf("Moradores: \n");


    for (int j = 0; j < 5; j++) {
        if (j < apto -> numeroDeMoradores) {
            printf("    ");
            digitarString(apto -> moradores[j].nome);
            printf("\n");
        } else {
            printf("    NIL\n");
        }
    }

    printf("Veiculos: \n");

    for (int j = 0; j < 2; j++) {
        if (apto -> numeroDeCarros > 0) {
            if (j < apto -> numeroDeCarros) {
                printf("    Carro %i:", j+1);
                printf("\n          ");
                digitarString( apto -> veiculos[j].modelo);
                printf("\n          ");
                digitarString( apto -> veiculos[j].cor);
                printf("\n");
            }else {
                printf("    NIL\n");
            }
        } else {
            if (j < apto -> numeroDeMotos) {
                printf("    Moto %i:", j+1);
                printf("\n          ");
                digitarString( apto -> veiculos[j].modelo);
                printf("\n          ");
                digitarString( apto -> veiculos[j].cor);
                printf("\n");

            }else {
                printf("    NIL\n");
            }
        }
    }
}















//              Buscar informações dos Apartamentos

void infoGeral(condominio *cond) {
    for (int i = 1; i <= 40; i++) {
        digitarApartamento(&cond -> apartamentos[i]);
    }
}

apartamento *buscarApartamento(condominio *cond, char unsigned aptoNum) {
    char finalizar = 0;
    char comeco = 1;
    char final = 40;
    char media;

    printf("\n\nBusca: \n\n");

    while (finalizar == 0) {
        media = (comeco + final)/2;

        printf("Inicio: %i, Final: %i, Media %i\n", comeco, final, media);
        if (comeco+1 == final) {
            if (cond -> apartamentos[comeco].numeroDoApartamento == aptoNum) {
                return &cond -> apartamentos[comeco];
            }
            if (cond -> apartamentos[final].numeroDoApartamento == aptoNum) {
                return &cond -> apartamentos[final];
            }
            return &cond -> apartamentos[0];
        }
        if (cond -> apartamentos[media].numeroDoApartamento == aptoNum) {
            return &cond -> apartamentos[media];
        }
        if (cond -> apartamentos[media].numeroDoApartamento > aptoNum) {
            final = media;
        }
        if (cond -> apartamentos[media].numeroDoApartamento < aptoNum) {
            comeco = media;
        }

    }
}

void infoApartamento(condominio *cond, char unsigned aptoNum) {
    apartamento *apto = buscarApartamento(cond, aptoNum);
    if (apto -> numeroDoApartamento == 0) {
        printf("\nNumero do apartamento invalido");
    } else {
        digitarApartamento(apto);
    }
}








//                Registrar Moradores e Veiculos nos apartamentos

void *copiarString(char *destino, char *origem, char tamanho) {
    char *retorno = destino;
    char i = 0;
    while (origem[i] != '\0' || i < tamanho) {
        destino[i] = origem[i];
        i++;
    }

    retorno[i] = '\0';

    return retorno;
}

void registrarMorador(char *nome,condominio *cond, char unsigned numeroDoApartamento) {
    apartamento *apto = buscarApartamento(cond, numeroDoApartamento);
    if(apto -> numeroDeMoradores == 5){
        printf("Operacao invalida, o apartamento esta cheio");
    } else{
        copiarString(apto -> moradores[apto -> numeroDeMoradores].nome, nome, 50);
        
        if(apto -> numeroDeMoradores == 0){
            cond -> numeroDeApartamentosOcupados++;
        }
        apto -> numeroDeMoradores++;
    }
}

void registrarVeiculo(char tipo, char *modelo, char *cor, condominio *cond, char unsigned numApto){
    apartamento *apto = buscarApartamento(cond, numApto);
    

    if(tipo != 'c' && tipo != 'm'){
        printf("Operacao invalida, tipo de veiculo não existente. ");
    } else if(apto -> numeroDeCarros > 0 || apto -> numeroDeMotos > 1){
        printf("Operacao invalida, numero de veiculos excedido. \n");
    } else if (tipo == 'c' && apto -> numeroDeMotos > 0){
        printf("Operacao invalida, numero de veiculos excedido. \n");
    } else {

        copiarString(apto -> veiculos[apto -> numeroDeVeiculos].modelo, modelo, 20);
        copiarString(apto -> veiculos[apto -> numeroDeVeiculos].cor, cor, 10);
        apto -> veiculos[apto -> numeroDeVeiculos].tipo = tipo;
        
        apto -> numeroDeVeiculos++;
        if(tipo == 'c'){
            apto -> numeroDeCarros++;
        } else{
            apto -> numeroDeMotos++;
        }

        printf("\n\n Veiculos: %i, Carros: %i, Motos: %i \n\n", apto -> numeroDeVeiculos, apto -> numeroDeCarros, apto -> numeroDeMotos);
    }
}












//                    Remoção de Moradores e Veiculos e limpeza total dos apartamentos

char compararString(char *string1, char *string2){
    char i = 0;
    char retorno;

    while(i > -1){
        retorno = string1[i] - string2[i];
        if(retorno == 0 && string1[i] != '\0' && string2[i] != '\0'){
            i++;
        } else{
            return retorno;
        }
    }
}

void limparApartamento(condominio *cond, char unsigned aptoNum){
    apartamento *apto = buscarApartamento(cond, aptoNum);

    if(apto -> numeroDoApartamento == 0){
        printf("Operacao invalida, nao existe apartamento com este numero");
    }else{
        apto -> numeroDeMoradores = 0;
        apto -> numeroDeVeiculos = 0;
        apto -> numeroDeCarros = 0;
        apto -> numeroDeMotos = 0;

        cond -> numeroDeApartamentosOcupados--;
    }
}

char compararString(char *string1, char *string2);

void removerMorador(char *nome, condominio *cond, char aptoNum){
    apartamento *apto = buscarApartamento(cond, aptoNum);
    char verificado = 0;
    
    for(int i = 0; i < apto -> numeroDeMoradores; i++){
        verificado = compararString(nome, apto -> moradores[i].nome);
        if( verificado == 0){

            if(apto -> numeroDeMoradores == 1){
                limparApartamento(cond, aptoNum);
            } else {

                for(int j = i; j < apto -> numeroDeMoradores; j++){
                    apto -> moradores[j] = apto -> moradores[j+1];
                }

                apto -> numeroDeMoradores--;
            }
             
             i = apto -> numeroDeMoradores;
        }
    }

    if(verificado != 0){
        printf("Operacao invalida, não existe morador com este nome neste apartamento");
    }
}

void removerVeiculo(char tipo, char *modelo, char *cor, condominio *cond, char aptoNum){
    apartamento *apto = buscarApartamento(cond, aptoNum);

    if(apto -> numeroDeMoradores == 0){
        printf("Operação invalida, este apartamento nao esta ocupado");
    } else{

        char verificado1;
        char verificado2;
        char verificado3;

        for(int i = 0; i < apto -> numeroDeVeiculos; i++){
            verificado1 = (apto -> veiculos[i].tipo - tipo);
            verificado2 = compararString(apto -> veiculos[i].modelo, modelo);
            verificado3 = compararString(apto -> veiculos[i].cor, cor);

            if(verificado1 == 0 && verificado2 == 0 && verificado3 == 0){
                for(int j = i; j < apto -> numeroDeVeiculos; j++){
                    apto -> veiculos[j] = apto -> veiculos[j+1];
                }

                apto -> numeroDeVeiculos--;
                i = apto -> numeroDeVeiculos;
            }
        }

        if(verificado1 != 0 || verificado2 != 0 || verificado3 != 0){
        printf("Operacao invalida, nao existe nenhum veiculo com estas especificacoes neste apartamento");
        }
    }
}








//                    Gerenciamento de apartamentos


void relatorioApartamentosOcupados(condominio *cond){
    char aux = cond -> numeroDeApartamentosOcupados;
    printf("\nApartamentos ocupados: %i \nApartamentos desocupados: %i", aux, 40-aux);
}






//                    Main teste

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

    registrarMorador("Antonio", &cond,  11);
    registrarMorador("Luiz Felipe",&cond, 21);
    registrarMorador("Gabriel Henrique", &cond, 31);
    registrarMorador("Daniel Feitosa", &cond, 41);
    registrarMorador("Samara Aciolly", &cond, 51);
    registrarMorador("Danilo de Padua", &cond, 61);

    // registrarVeiculo('m', "MT-10", "Verde", &cond, 11);

    // registrarVeiculo('m', "Honda CB1000RR", "Azul", &cond, 11);

    infoApartamento(&cond, 11);
    infoApartamento(&cond, 21);
    infoApartamento(&cond, 31);
    infoApartamento(&cond, 41);
    infoApartamento(&cond, 51);
    infoApartamento(&cond, 61);

    // removerMorador("Daniel Feitosa", &cond, 11);
    // removerVeiculo('m', "MT-10", "Verde", &cond, 11);

    relatorioApartamentosOcupados(&cond);

    // printf("Resultado: %i", compararStrings("Rodrizo", "Rodri"));
}