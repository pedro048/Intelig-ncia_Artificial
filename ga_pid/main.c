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
#define SETPOINT = 40.0
#define VEL = 20.0 //simula a velocidade do motor em um dado momento


typedef struct individuo {
    float cromossomo[3];
    float spid; //receber pid
    float erroInd;

}INDIVIDUO;

//void gerarPopulacao (INDIVIDUO populacao[TAM]){
void gerarPopulacao(){
	/*
    int i=0, j=0;
    float min = 0.10, max = 30;
	*/
	int i;
	int j;
	INDIVIDUO populacao[TAM];
    for (i=0; i<TAM; i++){
        for (j=0; j<3; j++){
            populacao[i].cromossomo[j] = (float)(rand()%40);
        }
    }
}


//float altura, erro, erro_dif, erro_int, setpoint, kp, ki, kd, dt;

//float pid(float vel, float erro, float erro_dif, float erro_int, float setpoint, float kp, float ki, float kd, float dt){
float pid(float vel, float setpoint, float kp, float ki, float kd, float dt){
  float erro_ant = erro;
  erro = setpoint - vel;
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
void chamarPID (INDIVIDUO crom){
    //float altura, erro, erro_dif, erro_int, setpoint, kp, ki, kd, dt;
    kp = crom.cromossomo[0];
    ki = crom.cromossomo[1];
    kd = crom.cromossomo[2];
	
	crom.spid = pid(VEL, SETPOINT, kp, ki, kd); //Associa um valor de solucao do pid a cada cromossomo	
}

//troca um dos tres bits do pai com algum dos tres da mae
//void cruzamento (INDIVIDUO populacao[TAM], int i_pai, int i_mae){
	
void cruzamento (INDIVIDUO populacao[TAM]){ // A polpulacao passada tem a apenas os cromossomos aptos para o cruzamento
    int indice1 = rand() % 3;
	int indice2 = rand() % 3;
	int indice3 = rand() % 3;
	int indice4 = rand() % 3;
	
    float aux1,aux2,aux3,aux4;

    aux1 = populacao[0].cromossomo[indice1];
	
    do{
        indice2 = rand() % 3;
    }while(indice1 == indice2);
    aux2 = populacao[1].cromossomo[indice2];

    populacao[0].cromossomo[indice1] = aux2;
    populacao[1].cromossomo[indice2] = aux1;
	
	aux3 = populacao[2].cromossomo[indice3];
	
    do{
        indice4 = rand() % 3;
    }while(indice3 == indice4);
    aux4 = populacao[3].cromossomo[indice4];

    populacao[2].cromossomo[indice3] = aux4;
    populacao[3].cromossomo[indice4] = aux3;
	
	// A populacao anterior he substituida pelos filhos

}


void mutacao(int populacao[][3], int tam){
    int mut = rand() % 101;
    int taxa_mutacao = 20;
    //int i;
    if(mut<=taxa_mutacao){

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



int main (){
    //srand(time(NULL));
    INDIVIDUO populacao[TAM];

    populacao[0].cromossomo[0] = 2.56; //kp
    populacao[0].cromossomo[1] = 3.67; //ki
    populacao[0].cromossomo[2] = 4.24; //kd
   // populacao[0].erro = fitneas();


    populacao[1].cromossomo[0] = 5.23; //kp
    populacao[1].cromossomo[1] = 6.78; //ki
    populacao[1].cromossomo[2] = 1.56; //kd
    //populacao[1].erro = fitneas();


    populacao[2].cromossomo[0] = 4.78; //kp
    populacao[2].cromossomo[1] = 6.23; //ki
    populacao[2].cromossomo[2] = 1.34; //kd
    //populacao[2].erro = fitneas();


    populacao[3].cromossomo[0] = 1.43; //kp
    populacao[3].cromossomo[1] = 5.43; //ki
    populacao[3].cromossomo[2] = 4.43; //kd

    //gerarPopulacao(populacao);
    //populacao[3].erro = fitneas();
    fitneas(populacao);

    int qtd_geracoes = 10, indice = 0, cont = 0;
    imprimir(populacao);
    do{
        indice++;
        cont++;
        selecao(populacao);
        for(; indice<TAM; indice+=2){

            cruzamento(populacao,indice,indice+1);
        }
        fitneas(populacao);
        imprimir(populacao);

    } while(cont <= qtd_geracoes);
    /*
    //TESTE DO CRUZAMENTO
    imprimir(populacao);
    printf("\n");
    cruzamento (populacao,0,1);
    imprimir(populacao);
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
