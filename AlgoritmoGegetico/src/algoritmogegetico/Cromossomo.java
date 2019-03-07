
package algoritmogegetico;

public class Cromossomo{
    public String genes;
    public double avaliacao=0;
    
    Cromossomo(int tamanho){
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
    
     public String getGenes() {
        return genes;
    }

    public double getAvaliacao() {
        return avaliacao;
    }
      
    public float converteBooleano(int inicio, int fim){
        int i;
        float aux=0;
        String s = this.getGenes();
        for(i = inicio; i <= fim; ++i){
            aux*=2;
            
            if(s.substring(i,i+1).equals("1")) {
                aux += 1;
            }  
        }
        return aux;
    }
    
    public double calculaAvaliacao(){
        double x = this.converteBooleano(0, 21);
        double y = this.converteBooleano(22, 43);
        x = x*0.00004768372718899898-100;
        y = y*0.00004768372718899898-100;
        this.avaliacao = Math.abs(x*y*Math.sin(y*Math.PI/4));
        
        return this.avaliacao;
    }
    
    public Cromossomo crossoverUmPonto(Cromossomo segundoPai){
        String aux1;
        Cromossomo retorno=null;
        int pontoCorte = (new Double(java.lang.Math.random()*this.genes.length())).intValue();
        if(java.lang.Math.random()<0.5){
            aux1 = this.genes.substring(0, pontoCorte) + segundoPai.getGenes().substring(pontoCorte, segundoPai.getGenes().length());
        }else{
            aux1=segundoPai.getGenes().substring(0, pontoCorte) + this.genes.substring(pontoCorte, this.genes.length());
        }
        return retorno;
    }
    
    public void mutacao(double chance){
        int i;
        int tamanho=this.genes.length();
        String aux, inicio, fim;
        for(i=0; i<tamanho; i++){
            if(java.lang.Math.random()<chance){
                aux=this.genes.substring(i, i+1);
                if(aux.equals("1")){
                    aux="0";
                }else{
                    aux="1";
                }
                inicio=this.genes.substring(0, i);
                fim=this.genes.substring(i+1, tamanho);
                this.genes=inicio+aux+fim;
            }
        }
    }
    /*
    public String toString() {
        return("Cromossomo:"+this.genes+"\n Avaliacao:"+this.avaliacao);
    }
    */
    public boolean equals(Cromossomo outroElemento) {
            return(genes.equals(outroElemento.getGenes()));
    }
    
}

