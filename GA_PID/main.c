#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#define ADPORTA 0
#define VEL_rpm_MAX_MOTOR 100.0 // velocidade em rpm
#define TAM 4 //quantidade de cromossomos
#define SETPOINT  5000.0 // velocidade em rpm
//#define VEL_rpm_INICIAL 5.00 // velocidade rpm inicial
/*
 * vp = velocidade em rpm
 * vm = velocidade angular
 */

//#define VEL  20.0 //simula a velocidade do motor em um dado momento


//float v=0;
float vel_rpm = 0.0;
float erro_ant = 0.0; //erro_dif = 0, erro_int = 0, dt= 0;


typedef struct individuo {
    float cromossomo[3];
    float spid; //receber pid
    float erroInd;

}INDIVIDUO;

int binario_decimal(int cromossomo[8])
{
    int soma=0, k = 7;

    for(int i=0; i<8; i++){
        soma += cromossomo[i] * pow(2,k);
        k--;
    }
    return soma;
}

void gerarBinario(int binario[8]){
    int i;
    for(i=0; i<8; i++){
        int aux = rand() % 2;
        binario[i] = aux;
    }

}

//void gerarPopulacao (INDIVIDUO populacao[TAM]){
void gerarPopulacao(INDIVIDUO populacao[TAM]){
	int i, j;
	int binario[8];
    //real = inferior + ((superior - inferior)/((pow(2,tamanhoBinario)-1)*vBinario))
    for (i=0; i<TAM; i++){
        for (j=0; j<3; j++){
            gerarBinario(binario);
            populacao[i].cromossomo[0] = 0.1 + (((10 - 0.1)/(pow(2,8)-1))*binario_decimal(binario));
            populacao[i].cromossomo[1] = (0.99/(pow(2,8)-1))*binario_decimal(binario);
            populacao[i].cromossomo[2] = (0.099/(pow(2,8)-1))*binario_decimal(binario);
        }
    }

}

//float altura, erro, erro_dif, erro_int, setpoint, kp, ki, kd, dt;

//float pid(float vel, float erro, float erro_dif, float erro_int, float setpoint, float kp, float ki, float kd, float dt){
/*
void velocidade(){
    int aux = rand() % 11;
    //float v = 0;
    if(aux < 8){
       v +=5;
    } else{
        if((v != 0) && (v>0))
            v -=5;
    }
    if(v >= 100){
        v = 0;
    }
    //printf("VELOCIDADE: %.2f", v);
    //printf("\n");
    //return v;
}
*/

float pid(float erro, float kp, float ki, float kd, clock_t tempo){
  //printf("TEMPO: %.2f",(float)tempo);
  //printf("\n");
  //erro = setpoint - vel;

  //system("pause");
  tempo = clock() - tempo;
  //printf("\ntempo2: %f \n", (float)tempo);
  //float dt = (float)tempo/CLOCKS_PER_SEC;
  float dt = 0.1;
  printf("dt: %f \n", dt);
  printf("\n erro: %f \n", erro);
  //printf("TEMPO: %.2f",(float)tempo);
  //printf("\n");
  float erro_dif = (erro - erro_ant)/dt;
  printf("\n erro_dif: %f \n", erro_dif);
  float erro_int = erro_int + erro_ant*dt;
  printf("\n erro_int: %f \n", erro_int);
  float saida = erro*kp + erro_dif*kd + erro_int*ki;

  printf("\n erro_ant: %f \n", erro_ant);
  erro_ant = erro;

  printf("\n saida do pid sem trucamento: %f \n", saida);
  if(saida > VEL_rpm_MAX_MOTOR){
    saida = VEL_rpm_MAX_MOTOR;
  }else if(saida < 0.0){
    saida = 0.0;
  }
  return saida;
}

//setar os parametros do pid
float chamarPID (INDIVIDUO crom, float erro, clock_t tempo){
    float kp, ki, kd;
    float aux;
    kp = crom.cromossomo[0];
    ki = crom.cromossomo[1];
    kd = crom.cromossomo[2];
    //kp = 2;
    //ki = 0.2;
    //kd = 0.02;
    //dt = rand () % 11;
    aux = pid(erro, kp, ki, kd, tempo); //Associa um valor de solucao do pid a cada cromossomo
    //printf("chamandoPID: %.2f", aux);
    //printf("\n");
    return aux;
}

float velocidade_rpm(float spid){
    float rpm = 60*spid;

    return rpm;
}

//calcula avaliacao
void fitneas(INDIVIDUO popul[TAM], clock_t tempo){

    int i;
    for(i=0; i<TAM; i++){
        //velocidade();
        printf("Vrpm: %.2f\n\n",vel_rpm);
        popul[i].erroInd = abs(SETPOINT - vel_rpm);
        popul[i].spid = chamarPID(popul[i], popul[i].erroInd, tempo);
        printf("\n solucao pid: %.2f\n\n",popul[i].spid);
        vel_rpm = velocidade_rpm(popul[i].spid);
        printf("\n vel rpm: %.2f\n\n",vel_rpm);

    }
}

void cruzamento (INDIVIDUO populacao[TAM], int i_pai, int i_mae){
    int indice1 = rand() % 3, indice2;
    float aux1,aux2;

    aux1 = populacao[i_pai].cromossomo[indice1];
    do{
        indice2 = rand() % 3;
    }while(indice1 == indice2);
    aux2 = populacao[i_mae].cromossomo[indice2];

    populacao[i_pai].cromossomo[indice1] = aux2;
    populacao[i_mae].cromossomo[indice2] = aux1;

}

void mutacao(INDIVIDUO popul[TAM]){
    float mut = rand()/RAND_MAX;
    float taxa_mutacao = 0.02;
    int indiv = rand() % TAM;
    int gen = rand() % 3;

    if(mut<=taxa_mutacao){
        popul[indiv].cromossomo[gen] = 100* ((float)rand()/RAND_MAX);
    }
}

//seleciona o individuo com o menor erro
void selecao (INDIVIDUO populacao[TAM]){
    int numTorneio = 0, i,k=0;
    int indice1 = rand() % 3, indice2 = rand() % 3;
    INDIVIDUO ganhador[TAM];
    while (numTorneio < 4) {
        numTorneio++;
        if (populacao[indice1].erroInd < populacao[indice2].erroInd){
            ganhador[k] = populacao[indice1];
            k++;
        }
        else {
            ganhador[k] = populacao[indice2];
            k++;
        }
    }
    for (i=0; i<TAM; i++){
        populacao[i] = ganhador[i]; /*A populacao eh substituida pelos cromossomos aptos para o cruzamento
									  Enviar essa populacao de aptos para o cruzamento
									*/
    }
}

void imprimir(INDIVIDUO populacao[TAM]){
    int i,j;
    for (i=0; i<TAM; i++){
        for(j=0; j<3; j++){
            printf("%.2f   ", populacao[i].cromossomo[j]);
        }
        printf("\n");
    }
    printf("\n");

}
void elitismo(INDIVIDUO populacao[TAM]){
    INDIVIDUO melhor, pior;
    int j,k;
    for(j=0; j<TAM-1; j++){
        if(populacao[j].erroInd < populacao[j+1].erroInd){
            melhor = populacao[j];
        } else{
            pior = populacao[j];
        }
    }
    for(k=0; k<TAM; k++){
        if(populacao[k].erroInd == pior.erroInd){
            populacao[k] = melhor;
        }
    }

}

void mostraMelhor(INDIVIDUO populacao[TAM]){
    INDIVIDUO melhor;
    int j,i;

    for(j=0; j<TAM-1; j++){
        if(populacao[j].erroInd < populacao[j+1].erroInd){
            for(i=0; i<3; i++){
                melhor.cromossomo[i] = populacao[j].cromossomo[i];
            }
        }
    }
    printf("Melhor Individuo: ");
    for(i=0; i<3; i++){
        printf("%.2f  ",melhor.cromossomo[i]);
    }
    printf("\n");
}



int main (){

    srand(time(NULL));
    clock_t tempo;
    tempo = clock();
    INDIVIDUO populacao[TAM];

    printf("Geracao Inicial:\n");
    //printf("tempo1: %f \n ", (float)tempo);
    gerarPopulacao(populacao);
	int i;

    fitneas(populacao,tempo);
    imprimir(populacao);
    printf("\n");

    //for(i=0; i<TAM; i++){
    //    printf("PIDs: %.2f\n\n",populacao[i].spid);
    //}

    for(i=0; i<TAM; i+=2){
            cruzamento(populacao,i,i+1);
    }
    mutacao(populacao);
    fitneas(populacao,tempo);
    //selecao(populacao);
    //imprimir(populacao);

    /*
     for(i=0; i<TAM; i++){
        printf("FITNEAS: %.2f\n\n",populacao[i].erroInd);
    }
    */
    /*
    srand(time(NULL));
    clock_t tempo;
    tempo = clock();
    INDIVIDUO populacao[TAM];

    printf("Geracao Inicial:\n");
    gerarPopulacao(populacao);
	int i;
    fitneas(populacao,tempo);
    imprimir(populacao);

    printf("\n");

    int qtd_geracoes= 20, cont=0;
    while(cont < qtd_geracoes){
        cont++;
        selecao(populacao);

        for(i=0; i<TAM; i+=2){
            cruzamento(populacao,i,i+1);
        }

        mutacao(populacao);

        //elitismo(populacao);
        fitneas(populacao,tempo);
        printf("Geracao %i:\n",cont);
        imprimir(populacao);

    }

    */

    system("pause");
    return 0;
}
