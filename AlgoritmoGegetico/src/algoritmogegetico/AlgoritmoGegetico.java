
package algoritmogegetico;

public class AlgoritmoGegetico{
    
    public static void main(String[] args) {
        /*
        Cromossomo e1 = new Cromossomo(4);
        System.out.println("cromossomo 1: "+e1.genes);
        Cromossomo e2 = new Cromossomo(4);
        System.out.println("cromossomo 2: "+e2.genes);
        */
        
       
        Populacao p1 = new Populacao(4, 8, 6); //(tamanho da populacao, tamanho do cromossomo, numero de geracoes)
        //System.out.println(p1.mostrarPopulacao());
        int i;	
	for (i=0;i<p1.numGeracoes;++i) {
		System.out.println("Geracao "+i+"\n");
                
		p1.avaliaTodos();
		p1.geracao();
                p1.moduloPopulacao();
   
	}
        
	i=p1.determinaMelhor();
	System.out.println(p1.populacao.get(i).genes);
               
           
    }
    
}
