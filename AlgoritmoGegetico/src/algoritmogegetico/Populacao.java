
package algoritmogegetico;

import java.util.ArrayList;
//import java.util.Iterator;

public class Populacao {
    public ArrayList<Cromossomo> populacao;
    public ArrayList<Cromossomo> novaPopulacao;
    public double somaAvaliacoes;
    public double chanceMutacao;
    public int numGeracoes;
    
    Populacao(int tamPopulacao, int tamCromossomo, int numero_geracoes){
        int i;
        populacao = new ArrayList<>();
        novaPopulacao = new ArrayList<>();
        numGeracoes=numero_geracoes;
        this.chanceMutacao=0.005;
        this.somaAvaliacoes=0;
        for(i=0; i<tamPopulacao; i++){
            this.populacao.add(new Cromossomo(tamCromossomo));
        }
    }
    public String mostrar(){
        String s = "Populacao Inicial: ";
        /*
        Iterator<Cromossomo> it = populacao.iterator();
        while(it.hasNext()){
            s = s + it.next().genes + ", ";
        }
        */
        for(int i=0; i<populacao.size(); i++){
            s = s +"e"+ i + " = " + populacao.get(i).genes + " | aptidao = " + populacao.get(i).calculaAvaliacao() + ", ";
        }
        
        System.out.println("Soma das aptidões = "+this.calculaSomaAvaliacoes());
        System.out.println("\n");
        System.out.println("Valor da roleta = "+this.roleta());
        return s;
    }
    
    public String mostraGeracao(){
        this.geracao();
        this.trocaPaisPorFilhos();
        String s = "";
        for(int i=0; i<populacao.size(); i++){
           s = s +"e"+ i + " = " + populacao.get(i).genes + " | aptidao = " + populacao.get(i).calculaAvaliacao() + ", ";
        }
        return s;
    }
    
    public void avaliaTodos(){
        int i;
        Cromossomo aux;
        for(i=0; i<this.populacao.size(); i++){
            aux = this.populacao.get(i);
            aux.calculaAvaliacao();
        }
        //this.somaAvaliacoes = calculaSomaAvaliacoes();
    }
    
    public double calculaSomaAvaliacoes(){
        int i;
        //this.somaAvaliacoes = 0;
        this.avaliaTodos();
        for(i=0; i<populacao.size(); i++){
            this.somaAvaliacoes += (populacao.get(i)).getAptidao();
        }
        return this.somaAvaliacoes;
    }
    
    public int roleta(){ //metodo de selecao
        int i;
        double aux = 0;
        this.calculaSomaAvaliacoes();
        double limite = Math.random()*this.somaAvaliacoes;
        for(i=0; ((i<this.populacao.size()) && (aux<limite)); ++i){
            aux += (populacao.get(i)).getAptidao();
        }
        i--;
        return i;
    }
    
    public void geracao(){
       Cromossomo pai1, pai2;
       
       while(novaPopulacao.size()<populacao.size()){
           pai1 = populacao.get(this.roleta());
           pai2 = populacao.get(this.roleta());
    
           novaPopulacao.add(new Cromossomo(pai1.genes, pai2.genes, this.chanceMutacao));
       }
    }
    
    public void trocaPaisPorFilhos(){ // A cada geracao todos os pais sao substituidos pelos filhos
        populacao.clear();
        populacao.addAll(novaPopulacao);
        novaPopulacao.clear();
    }
    
    public int determinaMelhor() {
	int i,ind_melhor=0;
	Cromossomo aux;
	this.avaliaTodos();
	double aval_melhor=(this.populacao.get(0)).getAptidao();
	for(i=1;i<this.populacao.size();i++) {
		aux=this.populacao.get(i);		
		if (aux.getAptidao()>aval_melhor) {
		   aval_melhor=aux.getAptidao();
		   ind_melhor=i;
		}
	}
	return(ind_melhor);
   }
    
}
