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

qualidade_atendimento['ruim'] = fuzz.trapmf(qualidade_atendimento.universe, [0, 0, 4])
qualidade_atendimento['bom'] = fuzz.trimf(qualidade_atendimento.universe, [2, 4, 6])
qualidade_atendimento['otimo'] = fuzz.trapmf(qualidade_atendimento.universe, [4, 8, 10])

# ---------------------------------------------------------------------------------------
tempo_entrega_pedido = ctrl.Antecedent(np.arange(0, 11, 1), 'tempo_entrega_pedido')

tempo_entrega_pedido['longo'] = fuzz.trapmf(tempo_entrega_pedido.universe, [0, 2, 4])
tempo_entrega_pedido['um pouco demorado'] = fuzz.trimf(tempo_entrega_pedido.universe, [3, 5, 6])
tempo_entrega_pedido['rapido'] = fuzz.trapmf(tempo_entrega_pedido.universe, [4, 9, 10])
# ---------------------------------------------------------------------------------------
'''
pedido_certo = ctrl.Antecedent(np.arange(0, 11, 1), 'pedido_certo')

pedido_certo['totalmente diferente'] = fuzz.trapmf(pedido_certo.universe, [0, 0, 3])
pedido_certo['um pouco diferente'] = fuzz.trimf(pedido_certo.universe, [2, 5, 6])
pedido_certo['igual'] = fuzz.trapmf(pedido_certo.universe, [4, 8, 10])
# ---------------------------------------------------------------------------------------
'''

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

satisfacao['baixa'] = fuzz.trapmf(satisfacao.universe, [0, 0, 5])
satisfacao['indiferente'] = fuzz.trimf(satisfacao.universe, [3, 6, 8])
satisfacao['alta']         = fuzz.trapmf(satisfacao.universe, [5, 7, 10])

# qualidade do atendimento
qualidade_atendimento.view()
# tempo de entrega do pedido
tempo_entrega_pedido.view()
'''
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
'''

# Definindo as regras de agregação
# satisfação baixa
regra1 = ctrl.Rule(qualidade_atendimento['ruim'] | tempo_entrega_pedido['um pouco demorado'], satisfacao['baixa'])

# indiferente

regra2 = ctrl.Rule(qualidade_atendimento['bom'] & tempo_entrega_pedido['rapido'], satisfacao['indiferente'] )

# satisfação alta

regra3 = ctrl.Rule(qualidade_atendimento['otimo'] | tempo_entrega_pedido['um pouco demorado'], satisfacao['alta'])




satisfacao_tipping_ctrl = ctrl.ControlSystem([regra1, regra2, regra3])
satisfacao_tipping = ctrl.ControlSystemSimulation(satisfacao_tipping_ctrl)

def grau_de_satisfacao(satisfacao):
    if satisfacao <= 4:
        return "Satisfacao baixa"
    elif (satisfacao > 4)  & (satisfacao <= 8):
        return "Não esta satisfeito nem insatisfeito, indiferente"
    elif (satisfacao > 8):
        return "Satisfacao alta"
		
# Testes

# teste 1: 

satisfacao_tipping.input['qualidade_atendimento'] = 5.0
satisfacao_tipping.input['tempo_entrega_pedido'] = 2.0
satisfacao_tipping.compute()

print(satisfacao_tipping.output['satisfacao'])
print(grau_de_satisfacao(satisfacao_tipping.output['satisfacao']))
satisfacao.view(sim=satisfacao_tipping)

# teste 2: 

satisfacao_tipping.input['qualidade_atendimento'] = 8.0
satisfacao_tipping.input['tempo_entrega_pedido'] = 7.0
satisfacao_tipping.compute()

print(satisfacao_tipping.output['satisfacao'])
print(grau_de_satisfacao(satisfacao_tipping.output['satisfacao']))
satisfacao.view(sim=satisfacao_tipping)

# teste 3: 

satisfacao_tipping.input['qualidade_atendimento'] = 10.0
satisfacao_tipping.input['tempo_entrega_pedido'] = 3.0
satisfacao_tipping.compute()

print(satisfacao_tipping.output['satisfacao'])
print(grau_de_satisfacao(satisfacao_tipping.output['satisfacao']))
satisfacao.view(sim=satisfacao_tipping)
  

