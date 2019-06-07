#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();
void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  //randomSeed(analogRead(0));
  //Entradas
  FuzzyInput *luminosidade = new FuzzyInput(1); // primeira entrada
  FuzzySet *baixa = new FuzzySet(0, 120, 120, 200); 
  luminosidade->addFuzzySet(baixa);

  FuzzySet *media = new FuzzySet(80, 310, 310, 590);
  luminosidade->addFuzzySet(media);

  FuzzySet *alta = new FuzzySet(440, 700, 700, 1024);
  luminosidade->addFuzzySet(alta);

  fuzzy->addFuzzyInput(luminosidade);
  //Saidas
  FuzzyOutput *luz_lampada = new FuzzyOutput(1);
  FuzzySet *pouca = new FuzzySet(0, 20, 20, 60);
  luz_lampada->addFuzzySet(pouca);
  
  FuzzySet *intermediaria = new FuzzySet(40, 80, 80, 120);
  luz_lampada->addFuzzySet(intermediaria);
  
  FuzzySet *muita = new FuzzySet(90, 180, 180, 255);
  luz_lampada->addFuzzySet(muita);
  
  fuzzy->addFuzzyOutput(luz_lampada);
  //Regras de inferencia
  //IF luminosidade == baixa THEN luz_lampada == muita
  FuzzyRuleAntecedent *seLuminosidadeBaixa = new FuzzyRuleAntecedent();
  seLuminosidadeBaixa->joinSingle(baixa);
  FuzzyRuleConsequent *entaoLuzLampadaMuita = new FuzzyRuleConsequent();
  entaoLuzLampadaMuita->addOutput(muita);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, seLuminosidadeBaixa, entaoLuzLampadaMuita);
  fuzzy->addFuzzyRule(fuzzyRule01); 

  //IF luminosidade == media THEN luz_lampada == intermediaria
  FuzzyRuleAntecedent *seLuminosidadeMedia = new FuzzyRuleAntecedent();
  seLuminosidadeMedia->joinSingle(media);
  FuzzyRuleConsequent *entaoLuzLampadaIntermediaria = new FuzzyRuleConsequent();
  entaoLuzLampadaIntermediaria->addOutput(intermediaria);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, seLuminosidadeMedia, entaoLuzLampadaIntermediaria);
  fuzzy->addFuzzyRule(fuzzyRule02); 

  //IF luminosidade == alta THEN luz_lampada == pouca
  FuzzyRuleAntecedent *seLuminosidadeAlta = new FuzzyRuleAntecedent();
  seLuminosidadeAlta->joinSingle(alta);
  FuzzyRuleConsequent *entaoLuzLampadaPouca = new FuzzyRuleConsequent();
  entaoLuzLampadaPouca->addOutput(pouca);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, seLuminosidadeAlta, entaoLuzLampadaPouca);
  fuzzy->addFuzzyRule(fuzzyRule03); 
}

void loop() {

  // Lendo valor do ADC
  int input = analogRead(0); 
 
  Serial.println("\n\n\nEntrada: ");
  Serial.print("\t\t\tLuminosidade: ");
  Serial.println(input); 
  
  fuzzy->setInput(1, input);
 
  fuzzy->fuzzify(); // Fuzzyficação
  
  float output = fuzzy->defuzzify(1); // Defuzzyficação
 
  Serial.println("Resultado: ");
  Serial.print("\t\t\tLuz da Lampada: ");
  Serial.println(output);

  analogWrite(9, output); 
  
  delay(2000);
  
}
