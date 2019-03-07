
package BuscaIterativa;

import java.util.ArrayList;
import java.util.Iterator;

public class No<T, P> {
    
    private T dados;
    private Integer h;
    private ArrayList<No> filhos;
    private ArrayList<Integer> custo;
    private ArrayList<Integer> f_avaliacao;
    
     No() {
        dados = null;
        h = null;
        filhos = new ArrayList<>();
        custo = new ArrayList<>();
        f_avaliacao = new ArrayList<>();
    }
     No(T dados, Integer h) {
        this.dados = dados;
        this.h = h;
        filhos = new ArrayList<>();
        custo = new ArrayList<>();
        f_avaliacao = new ArrayList<>();
    }
    public void addFilho(No filho, Integer custo) {
        filhos.add(filho);
        this.custo.add(custo);
        f_avaliacao.add(filho.getHeuristica() + custo);
        
    }
    public void addFilho(T dados, Integer h, Integer custo) {
        No<T, P> filho = new No<>(dados, h);
        filhos.add(filho);
        this.custo.add(custo);
    }
    public boolean temFilhos() {
        return !filhos.isEmpty();
    }
    public String toString() {
        String s = "Pai: " + dados.toString() + " | h = " + h.toString();

        Iterator<No> it = filhos.iterator();
        if (temFilhos()) {
            s = s + " -> Filhos: ";
            do {
                s = s + it.next().dados.toString() + ", ";
            } while (it.hasNext());
            s = s + " g = " + custo.toString() + ", " + " f = " + f_avaliacao.toString(); 
        } else{
            s = s + " -> sem filhos.";
        }
      return s;  
    }
    
    No getFilho(T dados) {
        Iterator<No> it = filhos.iterator();
        No filho;
        while (it.hasNext()) {
            filho = it.next();
            if (dados == filho.dados) {
                return filho;
            }
        }
        return null;
    }
    
    public T getDados() {
        return dados;
    }
    public ArrayList<No> getFilhos() {
        return filhos;
    }
    public Integer getHeuristica() {
        return h;
    }
    public ArrayList<Integer> getF_avalicao(){
        return f_avaliacao;
    }
    public ArrayList<Integer> getCusto(){
        return custo;
    }
    public void setDados(T dados) {
        this.dados = dados;
    }
    public void setHeuristica(Integer h) {
        this.h = h;
    }
    
}
