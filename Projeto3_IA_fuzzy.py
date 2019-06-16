''' 
Projeto da 3º unidade de IA
Tema: Aplicação da lógica fuzzy para avaliar a satisfação de clientes com restaurantes
'''
import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
import matplotlib.pyplot as plt
%matplotlib inline

# definição de antecedentes e consequentes

# antecedentes relacionados com a comida
qualidade_atendimento = ctrl.Antecedent(np.arange(0, 11, 1), 'qualidade_atendimento')

qualidade_atendimento['ruim'] = fuzz.trimf(qualidade_atendimento.universe, [0, 0, 4])
qualidade_atendimento['bom'] = fuzz.trimf(qualidade_atendimento.universe, [2, 4, 6])
qualidade_atendimento['otimo'] = fuzz.trimf(qualidade_atendimento.universe, [4, 8, 10])

# ---------------------------------------------------------------------------------------
tempo_entrega_pedido = ctrl.Antecedent(np.arange(0, 11, 1), 'tempo_entrega_pedido')

tempo_entrega_pedido['longo'] = fuzz.trimf(tempo_entrega_pedido.universe, [0, 2, 4])
tempo_entrega_pedido['um pouco demorado'] = fuzz.trimf(tempo_entrega_pedido.universe, [3, 5, 6])
tempo_entrega_pedido['rapido'] = fuzz.trimf(tempo_entrega_pedido.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
pedido_certo = ctrl.Antecedent(np.arange(0, 11, 1), 'pedido_certo')

pedido_certo['totalmente diferente'] = fuzz.trimf(pedido_certo.universe, [0, 2, 4])
pedido_certo['um pouco diferente'] = fuzz.trimf(pedido_certo.universe, [3, 5, 6])
pedido_certo['igual'] = fuzz.trimf(pedido_certo.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
temperatura_da_comida = ctrl.Antecedent(np.arange(0, 11, 1), 'temperatura_da_comida')

temperatura_da_comida['muito diferente da certa'] = fuzz.trimf(temperatura_da_comida.universe, [0, 2, 4])
temperatura_da_comida['um pouco diferente'] = fuzz.trimf(temperatura_da_comida.universe, [3, 5, 6])
temperatura_da_comida['correta'] = fuzz.trimf(temperatura_da_comida.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
sabor = ctrl.Antecedent(np.arange(0, 11, 1), 'sabor')

sabor['ruim'] = fuzz.trimf(sabor.universe, [0, 2, 4])
sabor['bom'] = fuzz.trimf(sabor.universe, [3, 5, 6])
sabor['otimo'] = fuzz.trimf(sabor.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------

# antecedentes relacionados com a estrutura do restaurante
estacionamento = ctrl.Antecedent(np.arange(0, 11, 1), 'estacionamento')

estacionamento['muito pequeno ou nao tem'] = fuzz.trimf(estacionamento.universe, [0, 2, 4])
estacionamento['mais ou menos confortavel'] = fuzz.trimf(estacionamento.universe, [3, 5, 6])
estacionamento['confortavel'] = fuzz.trimf(estacionamento.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
quantidade_de_mesas = ctrl.Antecedent(np.arange(0, 11, 1), 'quantidade_de_mesas')

quantidade_de_mesas['pequena'] = fuzz.trimf(quantidade_de_mesas.universe, [0, 2, 4])
quantidade_de_mesas['media'] = fuzz.trimf(quantidade_de_mesas.universe, [3, 5, 6])
quantidade_de_mesas['grande'] = fuzz.trimf(quantidade_de_mesas.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
temperatura_do_ambiente = ctrl.Antecedent(np.arange(0, 11, 1), 'temperatura_do_ambiente')

temperatura_do_ambiente['muito diferente da agradavel'] = fuzz.trimf(temperatura_do_ambiente.universe, [0, 2, 4])
temperatura_do_ambiente['um pouco desconfortavel'] = fuzz.trimf(temperatura_do_ambiente.universe, [3, 5, 6])
temperatura_do_ambiente['agradavel'] = fuzz.trimf(temperatura_do_ambiente.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
'''
qualidade_atendimento.automf(3)
tempo_entrega_pedido.automf(3)
pedido_certo.automf(3)
temperatura_da_comida.automf(3)
sabor.automf(3)
estacionamento.automf(3)
quantidade_de_mesas.automf(3)
temperatura_do_ambiente.automf(3)
'''
# consequente
# satisfação 0-10

satisfacao = ctrl.Consequent(np.arange(0, 11, 1), 'satisfacao')

satisfacao['baixa'] = fuzz.trimf(satisfacao.universe, [0, 0, 3])
satisfacao['indiferente'] = fuzz.trimf(satisfacao.universe, [2, 4, 6])
satisfacao['alta']         = fuzz.trimf(satisfacao.universe, [5, 7, 8])
satisfacao['muito alta'] = fuzz.trimf(satisfacao.universe, [7, 9,10])

# qualidade do atendimento
qualidade_atendimento.view()
# tempo de entrega do pedido
tempo_entrega_pedido.view()
# pedido certo
pedido_certo.view()
# temperatura da comida 
temperatura_da_comida.view()
# sabor da comida
sabor.view()
# estacionamento
estacionamento.view()
# quantidade de mesas
quantidade_de_mesas.view()
# temperatura do ambiente
temperatura_do_ambiente.view()

# Definindo as regras
# satisfação baixa
regra1 = ctrl.Rule(qualidade_atendimento['ruim'] & tempo_entrega_pedido['longo'] & pedido_certo['totalmente diferente'] & temperatura_da_comida['muito diferente da certa'] & sabor['ruim'] & estacionamento['muito pequeno ou nao tem'] & quantidade_de_mesas['pequena'] & temperatura_do_ambiente['muito diferente da agradavel'], satisfacao['baixa'])

# indiferente


# satisfação alta


# satisfação muito alta


satisfacao_tipping_ctrl = ctrl.ControlSystem([rule1, rule2, rule3, rule4, rule5, rule6, rule7])
satisfacao_tipping = ctrl.ControlSystemSimulation(satisfacao_tipping_ctrl)

def grau_de_satisfacao(satisfacao):
    if satisfacao <= 3:
        return "Satisfacao baixa"
    elif (satisfacao > 3)  & (satisfacao <= 6):
        return "Não esta satisfeito nem insatisfeito, indiferente"
    elif (satisfacao > 6) & (satisfacao <= 8):
        return "Satisfacao alta"
    elif (satisfacao > 8):
        return "satisfacao muito alta"
		
# Testes

# teste 1: 

satisfacao_tipping.input['qualidade_atendimento'] = 5.0
satisfacao_tipping.input['tempo_entrega_pedido'] = 2.0
satisfacao_tipping.input['pedido_certo'] = 10.0
satisfacao_tipping.input['temperatura_da_comida'] = 6.0
satisfacao_tipping.input['sabor'] = 8.0
satisfacao_tipping.input['estacionamento'] = 9.0
satisfacao_tipping.input['quantidade_de_mesas'] = 4.0
satisfacao_tipping.input['temperatura_do_ambiente'] = 9.0
satisfacao_tipping.compute()

print(satisfacao_tipping.output['satisfacao'])
print(grau_de_satisfacao(satisfacao_tipping.output['satisfacao']))
satisfacao.view(sim=satisfacao_tipping)

# teste 2: 

satisfacao_tipping.input['qualidade_atendimento'] = 8.0
satisfacao_tipping.input['tempo_entrega_pedido'] = 7.0
satisfacao_tipping.input['pedido_certo'] = 10.0
satisfacao_tipping.input['temperatura_da_comida'] = 9.0
satisfacao_tipping.input['sabor'] = 6.0
satisfacao_tipping.input['estacionamento'] = 7.0
satisfacao_tipping.input['quantidade_de_mesas'] = 9.0
satisfacao_tipping.input['temperatura_do_ambiente'] = 8.0
satisfacao_tipping.compute()

print(satisfacao_tipping.output['satisfacao'])
print(grau_de_satisfacao(satisfacao_tipping.output['satisfacao']))
satisfacao.view(sim=satisfacao_tipping)

# teste 3: 

satisfacao_tipping.input['qualidade_atendimento'] = 10.0
satisfacao_tipping.input['tempo_entrega_pedido'] = 3.0
satisfacao_tipping.input['pedido_certo'] = 7.0
satisfacao_tipping.input['temperatura_da_comida'] = 8.0
satisfacao_tipping.input['sabor'] = 7.0
satisfacao_tipping.input['estacionamento'] = 1.0
satisfacao_tipping.input['quantidade_de_mesas'] = 5.0
satisfacao_tipping.input['temperatura_do_ambiente'] = 4.0
satisfacao_tipping.compute()

print(satisfacao_tipping.output['satisfacao'])
print(grau_de_satisfacao(satisfacao_tipping.output['satisfacao']))
satisfacao.view(sim=satisfacao_tipping)
  

