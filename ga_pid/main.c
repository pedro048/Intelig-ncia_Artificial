#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <stdbool.h>
//#include <util/delay.h>

#define ADPORTA 0
#define VEL_MAX_MOTOR 100.0
#define TAM 4 //quantidade de cromossomos
#define SETPOINT  40.0
#define VEL  20.0 //simula a velocidade do motor em um dado momento

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
void chamarPID (INDIVIDUO crom, clock_t tempo){
    float kp, ki, kd, dt;
    kp = crom.cromossomo[0];
    ki = crom.cromossomo[1];
    kd = crom.cromossomo[2];
    //dt = rand () % 11;

	crom.spid = pid(VEL, SETPOINT, kp, ki, kd, tempo); //Associa um valor de solucao do pid a cada cromossomo
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
void fitneas(INDIVIDUO popul[TAM]){

	int i;
    for(i=0; i<TAM; i++){
        popul[i].erroInd = SETPOINT - VEL;
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
        populacao[i] = ganhador[i]; /*A populacao he substituida pelos cromossomos aptos para o cruzamento
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

int main (){
	
    srand(time(NULL));
    clock_t tempo;
    tempo = clock();
    INDIVIDUO populacao[TAM];

    printf("Geracao Inicial:\n");
    gerarPopulacao(populacao);
	int i;
	for(i=0; i<TAM; i++){
		chamarPID(populacao[i], tempo);
	}
    fitneas(populacao);
    imprimir(populacao);
    printf("\n");

    int qtd_geracoes=5, i=0, cont=0;
    while(cont < qtd_geracoes){
        cont++;
        selecao(populacao);

        //ALGO ESTA INTERFERINDO NESTE FOR E FAZENDO AS GERACOES FICAREM ERRADAS
        for(; i<TAM; i+=2){
            cruzamento(populacao,i,i+1);
        }

        mutacao(populacao);
	int j;
	for(j=0; j<TAM; j++){
		chamarPID(populacao[j], tempo);
	}
        fitneas(populacao);
        printf("Geracao %i:\n",cont);
        imprimir(populacao);

    }
    printf("\n\n\n\n");
    /*
    //CAPTURA O VALOR DOS SEGUNDOS DO RELOGIO DO COMPUTADOR
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);
    printf("Tempo em segundos: %i", *local);
    */


  //TESTE DO CRUZAMENTO
    /*
     for(; indice<TAM; indice+=2){

            cruzamento(populacao,indice,indice+1);
            imprimir(populacao);
             printf("\n");
        }

    //populacao[3].erro = fitneas();
    */
     /*
      kp=1.0;
      ki=0.2;
      kd=0.02;
      setpoint = ALTURA_TANQUE/2.0;
      dt = 0.1;
      erro = 0.0;


     //We will be using OCR1A as our PWM output which is the
     //same pin as PB1.

    DDRB |= 0b00000010;


    TCCR1A |= _BV(COM1A1) | _BV(WGM10);
    TCCR1B |= _BV(CS10) | _BV(WGM12);

    ADCSRA |= _BV(ADEN) | (1<<ADPS0) | (1<<ADPS1);;

    ADMUX &= 0xf0;
    ADMUX |= ADPORTA;

    for(;;) {

      ADCSRA |= _BV(ADSC);
      while(!(ADCSRA & _BV(ADIF)));


        altura = ADC/315.0 * ALTURA_TANQUE;

        OCR1A = floor( pid()/ALTURA_TANQUE *250u);


    _delay_ms(100);
}
*/
    system("pause");
    return 0;
}
