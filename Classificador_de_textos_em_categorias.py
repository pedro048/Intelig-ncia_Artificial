'''
CLASSIFICAÇÃO DE TEXTO EM CATEGORIAS POR MEIO DO DATASET 20 NEWSGROUPS  
Esse dataset é utilizado popularmente, tem vários documentos divididos em várias categorias.
TfidfVectorizer é usado para converter os textos em uma matriz com valores numéricos, poque
a rede neural não entendenderia se as entradas fossem, simplismente, palavras. TfidfVectorizer
também é responsável por indicar a importância de uma palavra com base na quantidade de ocorrên-
cia dela 
'''

from sklearn.datasets import fetch_20newsgroups 
from sklearn.feature_extraction.text import TfidfVectorizer #converte os textos em números

# Classificador: Rede Neural Perceptron Multicamadas (MLP)

from sklearn.neural_network import MLPClassifier

# São adicionadas metricas para avaliar a eficiencia do modelo utilizado.

from sklearn import metrics 

# A matriz de confusão é responsável por indicar a quantidade de classificações corretas por categorias.

from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
%matplotlib inline

'''
Escolha das categorias que serão classificadas e o uso dos dados de treino (subset). A inicialização é feita de forma
aleatória para envitar que o treinamente não generalize
'''

#redução das categorias em politicas e automoveis - subset(subconjunto de dados escolhido), shuffle (embaralha os dados para evitar que o programa fique tendencioso) 
categories = ['talk.politics.misc', 'rec.autos']
twenty_train = fetch_20newsgroups(subset='train',categories=categories, shuffle=True, random_state=42)

# Informações sobre os dados. O treinamento é supervisionado, então cada dado tem como rótulo a sua categooria

# Nomes das categorias
print(twenty_train.target_names) #verifica os nomes das categorias escolhidas

# O scikit-learn carrega os rótulo como um array de inteiros....
twenty_train.target[:10] #visualiza as categorias dos 10 últimos pontos de dados do conjunto de treino

# Mas, é possível visualizar os nomes das categorias da seguinte forma
for t in twenty_train.target[:10]:
    print(twenty_train.target_names[t]) #ver os nomes
	
# Reduz a importância de palavras que aparecem com uma frequênciia muito elevada, como: artigos, preposições, ...

#Reducao da frequencia que uma palavra aparece no texto w = tf * log(N/df)
vectorizer = TfidfVectorizer()
X_train_tfidf_vectorize = vectorizer.fit_transform(twenty_train.data)

# Treinando o Classificador (MLP)

clf = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(70, ), random_state=1, verbose=True)
#passa os dados de treino e os rótulos de cada um 
clf.fit(X_train_tfidf_vectorize, twenty_train.target)

# Avalição da Performace da Rede (MLP)

#os dados que estão em test são desconhecidos pelo modelo
twenty_test = fetch_20newsgroups(subset='test', categories=categories, shuffle=True, random_state=42)
docs_test = twenty_test.data

vect_transform = vectorizer.transform(docs_test)
predicted = clf.predict(vect_transform)


print(metrics.classification_report(twenty_test.target, predicted,target_names=twenty_test.target_names))

print(clf.classes_) #ordem das classes

# Visualizar a Performace do Classificador

confusion_matrix = confusion_matrix(twenty_test.target, predicted)
print(confusion_matrix)

plt.matshow(confusion_matrix)
plt.title("Matriz de confusão")
plt.colorbar()
plt.ylabel("Classificações corretas")
plt.xlabel("Classificações obtidas")
plt.show()

# Predição em novos dados

#Dados novos em inglês
docs_new = [
    'Wednesday morning, the legal team had appeared to turn back toward more discreet lawyering, with the announcement that Washington trial lawyer Emmet Flood would join the team inside the White House.',
    'By the time Rolls-Royce unveiled its one-of-a-kind Serenity Phantom at the 2015 Geneva Motor Show.'
]

X_new_tfidf_vectorize = vectorizer.transform(docs_new)

predicted = clf.predict(X_new_tfidf_vectorize)

for doc, category in zip(docs_new, predicted):
    print('%r => %s' % (doc, twenty_train.target_names[category]))