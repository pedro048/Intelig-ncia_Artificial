
package algoritmogegetico;

public class AlgoritmoGegetico{
    
    public static void main(String[] args) {
        Populacao p1 = new Populacao(3, 8, 4);
        System.out.println(p1.mostrar());
        System.out.println("\n");
        
        for(int i=0; i<p1.numGeracoes; i++){ //O numero de geracoes he o criterio de parada
            System.out.println("\nGeracao "+i+"\n");
            
            System.out.println(p1.mostraGeracao());
        }
        int i = p1.determinaMelhor();
        System.out.println("\n"+"Melhor individuo = "+p1.populacao.get(i).genes+" | Aptidao = "+p1.populacao.get(i).getAptidao()+"\n");
            
    }
    
}
