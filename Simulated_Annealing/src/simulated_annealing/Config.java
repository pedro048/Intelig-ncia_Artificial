
package simulated_annealing;

import java.util.ArrayList;

public class Config {
    ArrayList<Double> vizinhos;
    
    Config(){
        vizinhos = new ArrayList<>();
    }
    public Double funcao_objetivo(Double x){ 
        Double f = (1.00/10000.00)*((x+10.00)*(x+6.00)*(x+5.00)*(x+1.00)*(x-7.00)*(x-10.00)); 
        return f;
    }
    public Double resfriamento(Double T){
        Double a=0.88;
        return a*T;
    } 
    public ArrayList<Double> vizinhos(Double x){ 
        vizinhos.add(x-1.00);
        vizinhos.add(x+1.00);
        return vizinhos;
    }
}
