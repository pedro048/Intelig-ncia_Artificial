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

tempo_entrega_pedido = ctrl.Antecedent(np.arange(0, 11, 1), 'tempo_entrega_pedido')

pedido_certo = ctrl.Antecedent(np.arange(0, 11, 1), 'pedido_certo')

temperatura_da_comida = ctrl.Antecedent(np.arange(0, 11, 1), 'temperatura_da_comida')

sabor = ctrl.Antecedent(np.arange(0, 11, 1), 'sabor')

# antecedentes relacionados com a estrutura do restaurante
estacionamento = ctrl.Antecedent(np.arange(0, 11, 1), 'estacionamento')

quantidade_de_mesas = ctrl.Antecedent(np.arange(0, 11, 1), 'quantidade_de_mesas')

temperatura_do_ambiente = ctrl.Antecedent(np.arange(0, 11, 1), 'temperatura_do_ambiente')

qualidade_atendimento.automf(3)
tempo_entrega_pedido.automf(3)
pedido_certo.automf(3)
temperatura_da_comida.automf(3)
sabor.automf(3)
estacionamento.automf(3)
quantidade_de_mesas.automf(3)
temperatura_do_ambiente.automf(3)


# consequente
# satisfação 0-10

satisfacao = ctrl.Consequent(np.arange(0, 11, 1), 'satisfacao')

satisfacao['baixa'] = fuzz.trimf(satisfacao.universe, [0, 0, 5])
satisfacao['indiferente'] = fuzz.trimf(satisfacao.universe, [3, 6, 8])
satisfacao['alta']         = fuzz.trimf(satisfacao.universe, [5, 7, 10])

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

# Definindo as regras de agregação
# satisfação baixa
regra1 = ctrl.Rule(qualidade_atendimento['poor'] & tempo_entrega_pedido['poor'] & pedido_certo['poor'] & temperatura_da_comida['poor'] & sabor['poor'] & estacionamento['poor'] & quantidade_de_mesas['poor'] & temperatura_do_ambiente['poor'], satisfacao['baixa'])
regra2 = ctrl.Rule(qualidade_atendimento['average'] & tempo_entrega_pedido['average'] & pedido_certo['good'] & temperatura_da_comida['good'] & sabor['average'] & estacionamento['poor'] & quantidade_de_mesas['average'] & temperatura_do_ambiente['poor'],satisfacao['baixa'])
regra3 = ctrl.Rule(qualidade_atendimento['poor'] & tempo_entrega_pedido['good'] & pedido_certo['good'] & temperatura_da_comida['good'] & sabor['average'] & estacionamento['average'] & quantidade_de_mesas['good'] & temperatura_do_ambiente['average'],satisfacao['baixa'])
# indiferente

regra4 = ctrl.Rule(qualidade_atendimento['average'] & tempo_entrega_pedido['average'] & pedido_certo['average'] & temperatura_da_comida['average'] & sabor['average'] & estacionamento['average'] & quantidade_de_mesas['average'] & temperatura_do_ambiente['average'],satisfacao['indiferente'])
regra5 = ctrl.Rule(qualidade_atendimento['average'] & tempo_entrega_pedido['good'] & pedido_certo['average'] & temperatura_da_comida['average'] & sabor['average'] & estacionamento['poor'] & quantidade_de_mesas['poor'] & temperatura_do_ambiente['average'],satisfacao['indiferente'])
regra6 = ctrl.Rule(qualidade_atendimento['average'] & tempo_entrega_pedido['average'] & pedido_certo['good'] & temperatura_da_comida['good'] & sabor['average'] & estacionamento['poor'] & quantidade_de_mesas['poor'] & temperatura_do_ambiente['average'],satisfacao['indiferente'])
# satisfação alta

regra7 = ctrl.Rule(qualidade_atendimento['good'] & tempo_entrega_pedido['good'] & pedido_certo['good'] & temperatura_da_comida['good'] & sabor['good'] & estacionamento['good'] & quantidade_de_mesas['good'] & temperatura_do_ambiente['good'],satisfacao['alta'])
regra8 = ctrl.Rule(qualidade_atendimento['good'] & tempo_entrega_pedido['average'] & pedido_certo['good'] & temperatura_da_comida['good'] & sabor['good'] & estacionamento['good'] & quantidade_de_mesas['good'] & temperatura_do_ambiente['good'],satisfacao['alta'])
regra9 = ctrl.Rule(qualidade_atendimento['good'] & tempo_entrega_pedido['good'] & pedido_certo['good'] & temperatura_da_comida['good'] & sabor['good'] & estacionamento['good'] & quantidade_de_mesas['average'] & temperatura_do_ambiente['good'],satisfacao['alta'])



satisfacao_tipping_ctrl = ctrl.ControlSystem([regra1, regra2, regra3, regra4, regra5, regra6, regra7, regra8, regra9])
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
  

