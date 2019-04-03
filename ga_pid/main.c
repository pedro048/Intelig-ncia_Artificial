#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ADPORTA 0
#define VEL_MAX_MOTOR 100.0
#define TAM 4 //quantidade de cromossomos
#define SETPOINT  40.0
//#define VEL  20.0 //simula a velocidade do motor em um dado momento


//float VEL=0;
float erro = 0, erro_ant= 0, erro_dif = 0, erro_int = 0, dt= 0;


typedef struct individuo {
    float cromossomo[3];
    float spid; //receber pid
    float erroInd;

}INDIVIDUO;

//void gerarPopulacao (INDIVIDUO populacao[TAM]){
void gerarPopulacao(INDIVIDUO populacao[TAM]){
	int i, j;
    //RAND_MAX eh definido como 0x7fffffff
    for (i=0; i<TAM; i++){
        for (j=0; j<3; j++){
            populacao[i].cromossomo[j] = 100* ((float)rand()/RAND_MAX);
        }
    }
}

//float altura, erro, erro_dif, erro_int, setpoint, kp, ki, kd, dt;

//float pid(float vel, float erro, float erro_dif, float erro_int, float setpoint, float kp, float ki, float kd, float dt){

float velocidade(){
    int aux = rand() % 11;
    float v = 0;
    if(aux > 5){
       v +=20;
    }else{
        if(v != 0){
            v -=10;
        }
    }
    return v;
}

float pid(float vel, float setpoint, float kp, float ki, float kd, clock_t tempo){

  erro_ant = erro;
  erro = setpoint - vel;
  tempo = clock() - tempo;
  dt = (float)tempo/CLOCKS_PER_SEC;
  erro_dif = (erro - erro_ant)/dt;
  erro_int += erro_ant*dt;
  float saida = erro*kp + erro_dif*kd + erro_int*ki;
  if(saida > VEL_MAX_MOTOR){
    saida = VEL_MAX_MOTOR;
  }else if(saida < 0.0){
    saida = 0.0;
  }
  return saida;
}

//setar os parametros do pid
void chamarPID (INDIVIDUO crom, clock_t tempo, float veloc){
    float kp, ki, kd;
    kp = crom.cromossomo[0];
    ki = crom.cromossomo[1];
    kd = crom.cromossomo[2];
    //dt = rand () % 11;
	crom.spid = pid(veloc, SETPOINT, kp, ki, kd, tempo); //Associa um valor de solucao do pid a cada cromossomo
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
    float taxa_mutacao = 0.2;
    int indiv = rand() % TAM;
    int gen = rand() % 3;

    if(mut<=taxa_mutacao){
        popul[indiv].cromossomo[gen] = 100* ((float)rand()/RAND_MAX);
    }
}

//calcula avaliacao
void fitneas(INDIVIDUO popul[TAM], clock_t tempo){

	int i;
    for(i=0; i<TAM; i++){
        float auxVel = velocidade();
        popul[i].erroInd = SETPOINT - auxVel;
        chamarPID(popul[i], tempo,auxVel);
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

// FUNCIONAMENTO DAS EDOs !!!
/*
// W => velocidade (v.p. = variavel de processo)
//falta identificar Wkw
double eqDiferencialCorrente(double W, double Wkw){
//corrente
//return  (W - (Ia * Ra + Wkw + Va))/La;
   return (W - (4.6 * 1 + Wkw + 12))/0,5;
}


double Wn1, Wkwn1, Wn=valor_inicial, Wkwn=valor_inicial;
void euler_corrente(double Wn, double Wkwn){
   Wkwn1 = Wkwn + h*eqDiferencialCorrente(double Wn, double Wkwn)
   Wn1 = Wn + h;
   
   Wkwn = Wkwn1;
   Wn = Wn1;
}
   
// Iaki => Solucao do PID (corrente)
// W => velocidade (v.p.)
// falta identificar Tc !!!
double eqDiferencialVelocidade(double Iaki, double Tc, double W){
//velocidade
//return  (Iaki - (W * b + Tc + Tae))/J;
	return (Iaki - (W * 0,1 + Tc + Tae))/0,01;

}

double Iakin1, Tcn1, Wn1, Iakin=valor_inicial, Tcn=valor_inicial, Wn=valor_inicial;
void euler_vel(double Iakin, double Tcn, double Wn){
	Wn1 = Wn + h*eqDiferencialVelocidade(double Iakin, double Tcn, double Wn);
	Tcn1 = Tcn + h;
	Iakin1 = Iakin + h;

	Wn = Wn1;
	Tcn = Tcn1;
	Iakin = Iakin1;
}
*/

int main (){

    srand(time(NULL));
    clock_t tempo;
    tempo = clock();
    INDIVIDUO populacao[TAM];

    printf("Geracao Inicial:\n");
    gerarPopulacao(populacao);
	int i;/*
	for(i=0; i<TAM; i++){
		chamarPID(populacao[i], tempo);
	}
	*/
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
        /*
        int j;
        for(j=0; j<TAM; j++){
            chamarPID(populacao[j], tempo);
        }
        */
        //elitismo(populacao);
        fitneas(populacao,tempo);
        printf("Geracao %i:\n",cont);
        imprimir(populacao);

    }
    printf("\n\n\n\n");


  //TESTE DO CRUZAMENTO
    /*
     for(; indice<TAM; indice+=2){

            cruzamento(populacao,indice,indice+1);
            imprimir(populacao);
             printf("\n");
        }

    //populacao[3].erro = fitneas();
    */


    system("pause");
    return 0;
}
