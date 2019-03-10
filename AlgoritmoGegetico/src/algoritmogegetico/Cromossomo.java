
package algoritmogegetico;

public class Cromossomo {
    public String genes;
    public double aptidao;
    
    Cromossomo(int tamanho){ //construtor usado para a populacao inicial
        this.aptidao=0;
        int i;
        this.genes="";
        for(i=0; i<tamanho; i++){
            if(java.lang.Math.random()<0.5){ //Gerando os genes de forma aleatoria
                this.genes=this.genes+"0";
            }else{
                this.genes=this.genes+"1";
            }
        }
    }
    
    Cromossomo(String pai1, String pai2, Double chance){ //construtor de filhos usando crossover e mutacao
        //crossover
        String aux1, aux2, fim1, fim2;
        String auxMutacao, fimMutacao;
        int tamanho = pai1.length();
        
        aux1 = pai1.substring(0, ((tamanho)/2));
        fim1 = pai1.substring(((tamanho)/2), tamanho);
        
        aux2 = pai2.substring(0, ((tamanho)/2));
        fim2 = pai2.substring(((tamanho)/2), tamanho);
        
        if(java.lang.Math.random()<0.5){
            this.genes = aux1+fim2;
        }else{
            this.genes = aux2+fim1;
        }
        //mutacao
        int tamMutacao=this.genes.length();
        
        if(java.lang.Math.random()<chance){
            auxMutacao=this.genes.substring(0);
            fimMutacao=this.genes.substring(1, tamMutacao-1);
            if(auxMutacao.equals("1")){
                 auxMutacao="0";
                    
            }else{
                 auxMutacao="1";
            }
            this.genes=auxMutacao+fimMutacao;
        }
        
    }
    
    public String getGenes() {
        return genes;
    }

    public void setGenes(String genes) {
        this.genes = genes;
    }

    public double getAptidao() {
        return aptidao;
    }
    
    public int booleanoParaInteiro(int inicio, int fim){
        String s = this.getGenes();
        String parte = s.substring(inicio, fim);
        int num = Integer.parseInt(parte, 2);
        
        return num;
    }
    
    public double calculaAvaliacao(){
        int x = this.booleanoParaInteiro(0, 4);
        int y = this.booleanoParaInteiro(4, 8);
        /*
        x = x*0.00004768372718899898-100;
        y = y*0.00004768372718899898-100;
        */
          this.aptidao = Math.abs(x*y*Math.sin(y*Math.PI/4));
        //this.aptidao = x+y;
        
        return this.aptidao;
    }
    
}

