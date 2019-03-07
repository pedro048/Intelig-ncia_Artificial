
package BuscaIterativa;

import java.util.Iterator;

public class Arvore<T, P> {
     private final No<T, P>  raiz;
     public String objetivo;
     public int nivel;
     public int limite;
    
    Arvore(No n, String obj){
        raiz = n;
        objetivo = obj;
        limite = 0;
        nivel = 0;
    }
    
    public void buscaA_estrela(){
        //NÃO ESTÁ COMPLETO
    }
    private void caminhoA_estrela(No<T, P> n, String obj){
        if(obj == n.getDados()){
            System.out.println("Pai: " + obj + " = " + "Objetivo");
            System.exit(0);
        }
        System.out.println(n.toString());
        Iterator<No> it = n.getFilhos().iterator();
        
    }
    
    public void buscaIterativa(){
        System.out.println("BUSCA EM PROFUNDIDADE ITERATIVA");
        System.out.println("\n");
         caminhoIterativo(raiz, objetivo, limite);
    }
    
    private void caminhoIterativo(No<T, P> n, String obj, int lim){
        System.out.println("Nivel: " + nivel);
        if(obj == n.getDados()){
            
            System.out.println("Pai: " + obj + " = " + "Objetivo");
            System.out.println("\n");
            System.out.println("Limite: " + lim);
            System.out.println("\n");
            System.exit(0);
        }
        if(nivel == lim){
            System.out.println(n.toString());
            System.out.println("\n");
            System.out.println("Limite: " + lim);
            System.out.println("\n");
            lim++;
            nivel=0;
            caminhoIterativo(raiz, obj, lim);
        }
        System.out.println(n.toString()); 
        Iterator<No> it = n.getFilhos().iterator();
        while(it.hasNext()){
            nivel++;
            caminhoIterativo(it.next(), obj, lim); 
        }  
    }  
    public static void main(String[] args) {
       
        //crianção dos Nos
        No<String, Integer> n1 = new No<>("Arad", 366); // (nome do No, heuristica)
        No<String, Integer> n2 = new No<>("Timisoara", 329);
        No<String, Integer> n3 = new No<>("Sibiu", 253);
        No<String, Integer> n4 = new No<>("Zerind", 374);
        No<String, Integer> n5 = new No<>("Lugoj", 244);
        No<String, Integer> n6 = new No<>("Rimnicu Vilcea", 193);
        No<String, Integer> n7 = new No<>("Fagaras", 178);
        No<String, Integer> n8 = new No<>("Oradea", 380);
        
        No<String, Integer> n9 = new No<>("Mehadia", 241);
        No<String, Integer> n10 = new No<>("Dobreta", 242);
        No<String, Integer> n11 = new No<>("Craiova", 160);
        //estruturando a arvore (No Filho, custo do pai ao filho)
        n1.addFilho(n2, 118);
        n1.addFilho(n3, 140);
        n1.addFilho(n4, 75);
        
        n2.addFilho(n5, 111);
        
        n3.addFilho(n6, 80);
        n3.addFilho(n7, 99);
        
        n4.addFilho(n8, 71);
        
        n5.addFilho(n9, 70);
        
        n9.addFilho(n10, 75);
        
        n10.addFilho(n11, 120);
        
        //(Inicio, Objetivo)
        Arvore<String, Integer> arvoreBusca = new Arvore<>(n1, "Fagaras");
        
        arvoreBusca.buscaIterativa();    
    }  
}
