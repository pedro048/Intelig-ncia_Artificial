
package simulated_annealing;

import java.util.Random;

public class Simulated_Annealing {
 
    public static void main(String[] args) {
        
        Config c = new Config();
        Double dE;
        Double vizinho;
        Double T=1000.00;
        Double x=-4.8;
        Double melhorX=x;
        
        
        while(T>0.1){
            
            for(int i=0; i<1; i++){
                vizinho = c.vizinhos(x).get(i);
                dE=c.funcao_objetivo(vizinho)-c.funcao_objetivo(x);
                
                if(( c.funcao_objetivo(vizinho) < c.funcao_objetivo(x) ) || ( java.lang.Math.random() < java.lang.Math.exp((-dE)/T)) ){
                    x=vizinho;
                }
            }
            T = c.resfriamento(T);
            if(c.funcao_objetivo(x)<c.funcao_objetivo(melhorX)){
                melhorX=x;
            } 
        }
        
        System.out.println(melhorX);
      
    } 
} 
       
    
    

