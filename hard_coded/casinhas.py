#primeira tentativa de algritmo genetico
#usando o metodo da roleta (ou das casinhas)
#a chance de um individuo transar eh diretamente proporcional a nota

import matplotlib.pyplot as plt
import numpy as np
from random import random

def gera_individuo():
    #gera um numero inteiro entre -50 e 50
    return int(random()*100)

def find_range(index,values):
    for i in range(len(values)):
            if(index<=values[i]):
                    return i
    return len(values)-1

def transa(individuos, notas):
    index_1=random()*sum(notas)
    index_1=find_range(index_1,notas)
    index_2=random()*sum(notas)
    index_2=find_range(index_2,notas)
    pai=individuos[index_1]
    mae=individuos[index_2]
    return (pai+mae)/2 + 2*random() -1

def avalia(x):
    return x*(100-x)

#--------------------------------------------------------------------------------
#variaveis

ind=[] #individuos
notas=[]
TamPop=4 #tamanho da populacao
qtde_geracoes=20 #quantidade de iteracoes
grafico_ind=[[] for i in range(TamPop)]
grafico_notas=[[] for i in range(TamPop)]

#inicia as populacoes
for i in range(TamPop):
    ind.append(gera_individuo())

#iteracoes do algoritmo
for j in range(qtde_geracoes):
    #avalia a viabilidade
    notas=[avalia(i) for i in ind]

    #salva os dados para plotar os graficos
    for i in range(TamPop):
        grafico_ind[i].append(ind[i])
        grafico_notas[i].append(notas[i])

    #escolhe o individuo mais viavel
    mx=0
    for i in range(1,TamPop):
        if(notas[i]>notas[mx]):
            mx=i
    mx=ind[mx]
    #gera os novos individuos, matando todos os antigos
    ind=[transa(ind,notas) for i in ind if i!=mx]
    ind.append(mx)

print(mx,avalia(mx))

#termina os dados do grafico
for i in range(TamPop):
    grafico_ind[i].append(ind[i])
    #eh necessario re-avaliar pq a ultima iteracao termina gerando individuos
    grafico_notas[i].append(avalia(ind[i]))


#processamento para plotar os graficos
t=np.arange(0,100)
y=avalia(t)

plt.subplot(321)
plt.plot(t,y,'k')
for i in range(qtde_geracoes):
    plt.plot([grafico_ind[0][i],grafico_ind[0][i]],[grafico_ind[0][i],grafico_notas[0][i]],'b--')
    plt.plot([grafico_ind[0][i],grafico_ind[0][i]],[grafico_notas[0][i],grafico_notas[0][i]],'b--')

plt.subplot(322)
plt.plot(t,y,'k')
for i in range(qtde_geracoes):
    plt.plot([grafico_ind[1][i],grafico_ind[1][i]],[grafico_ind[1][i],grafico_notas[1][i]],'b--')
    plt.plot([grafico_ind[1][i],grafico_ind[1][i]],[grafico_notas[1][i],grafico_notas[1][i]],'b--')

plt.subplot(323)
plt.plot(t,y,'k')
for i in range(qtde_geracoes):
    plt.plot([grafico_ind[2][i],grafico_ind[2][i]],[grafico_ind[2][i],grafico_notas[2][i]],'b--')
    plt.plot([grafico_ind[2][i],grafico_ind[2][i]],[grafico_notas[2][i],grafico_notas[2][i]],'b--')

plt.subplot(324)
plt.plot(t,y,'k')
for i in range(qtde_geracoes):
    plt.plot([grafico_ind[3][i],grafico_ind[3][i]],[grafico_ind[3][i],grafico_notas[3][i]],'b--')
    plt.plot([grafico_ind[3][i],grafico_ind[3][i]],[grafico_notas[3][i],grafico_notas[3][i]],'b--')

plt.subplot(313)
t=[i for i in range(qtde_geracoes+1)]
plt.plot(t,[50 for i in t],'k')
plt.plot(t,grafico_ind[0],'b--')
plt.plot(t,grafico_ind[1],'y--')
plt.plot(t,grafico_ind[2],'r--')
plt.plot(t,grafico_ind[3],'m--')

plt.savefig('casinhas')
plt.show()
