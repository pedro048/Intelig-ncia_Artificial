
package algoritmogegetico;

import java.util.ArrayList;
import java.util.Iterator;

public class Populacao{
    public ArrayList<Cromossomo> populacao;
    public ArrayList<Cromossomo> novaPopulacao;
    public double somaAvaliacoes;
    public double chanceMutacao;
    public int numGeracoes;
    
    Populacao(int tamPopulacao, int tamCromossomo, int numero_geracoes){
        int i;
        populacao = new ArrayList<>();
        numGeracoes=numero_geracoes;
        this.chanceMutacao=0.005;
        for(i=0; i<tamPopulacao; i++){
            this.populacao.add(new Cromossomo(tamCromossomo));
        }
    }
    public String mostrarPopulacao(){
        String s = "Populacao: ";
        Iterator<Cromossomo> it = populacao.iterator();
        while(it.hasNext()){
            s = s + it.next().genes.toString() + ", ";
        }
        return s;
    }
    
    public void avaliaTodos(){
        int i;
        Cromossomo aux;
        for(i=0; i<this.populacao.size(); ++i){
            aux = (Cromossomo)this.populacao.get(i);
            aux.calculaAvaliacao();
        }
        this.somaAvaliacoes = calculaSomaAvaliacoes();
    }
    
    public double calculaSomaAvaliacoes(){
        int i;
        this.somaAvaliacoes = 0;
        for(i=0; i<populacao.size(); ++i){
            this.somaAvaliacoes += ((Cromossomo)populacao.get(i)).getAvaliacao();
        }
        return this.somaAvaliacoes;
    }
    
    public int roleta(){ //metodo de selecao
        int i;
        double aux = 0;
        calculaSomaAvaliacoes();
        double limite = Math.random()*this.somaAvaliacoes;
        for(i=0; ((i<this.populacao.size()) && (aux<limite)); ++i){
            aux += ((Cromossomo)populacao.get(i)).getAvaliacao();
        }
        i--;
        return i;
    }
    
    public void geracao(){
       novaPopulacao = new ArrayList<>();
       Cromossomo pai1, pai2, filho;
       int i;
       for(i=0; i<this.populacao.size(); ++i){
           pai1 = (Cromossomo)populacao.get(this.roleta());
           pai2 = (Cromossomo)populacao.get(this.roleta());
           filho = pai1.crossoverUmPonto(pai2);
           filho.mutacao(this.chanceMutacao);
           novaPopulacao.add(filho);
       }
    }
    
    public void moduloPopulacao(){ //responsavel por substituir os pais pelos filhos
        populacao.clear();
        populacao.addAll(novaPopulacao);
    }
    
    public int determinaMelhor() {
	int i,ind_melhor=0;
	Cromossomo aux;
	this.avaliaTodos();
	double aval_melhor=((Cromossomo)this.populacao.get(0)).getAvaliacao();
	for(i=1;i<this.populacao.size();++i) {
		aux=(Cromossomo)this.populacao.get(i);		
		if (aux.getAvaliacao()>aval_melhor) {
		   aval_melhor=aux.getAvaliacao();
		   ind_melhor=i;
		}
	}
	return(ind_melhor);
   }
    
}
