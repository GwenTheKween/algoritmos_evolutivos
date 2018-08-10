#primeira tentativa de algritmo genetico
#usando o metodo do elitismo
#apelidado de "o melhor transa com todos"

import matplotlib.pyplot as plt
import numpy as np
from random import random

def gera_individuo():
    #gera um numero inteiro entre 0 e 200
    return int(random()*200)

def transa(pai,mae):
    filho=(pai+mae)/2
    diff=np.abs(pai-mae)
    return filho + 4*(random() - 0.5)

def avalia(x):
    return np.exp(-np.power(x-100,2.)/(2*np.power(20,2.)))

def ajeita_plot(ind,notas):
    y=[0,notas[0]]
    for i in range(1,len(notas)):
        y+=[notas[i-1],notas[i]]
    x=[]
    for i in ind:
	    x+=([i]*2)
    return x,y

#--------------------------------------------------------------------------------
#variaveis

ind=[] #individuos
notas=[]
TamPop=8 #tamanho da populacao
qtde_geracoes=200 #quantidade de iteracoes
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
    #gera os novos individuos, matando todos os antigos
    ind=[transa(ind[i],ind[mx]) for i in range(TamPop)]

print(ind[mx],avalia(ind[mx]))

#termina os dados do grafico
for i in range(TamPop):
    grafico_ind[i].append(ind[i])
    #eh necessario re-avaliar pq a ultima iteracao termina gerando individuos
    grafico_notas[i].append(avalia(ind[i]))


#processamento para plotar os graficos
t=np.linspace(0,200)
Y=avalia(t)



plt.subplot(321)
plt.plot(t,Y,'k')
x,y=ajeita_plot(grafico_ind[0],grafico_notas[0])
for i in range(qtde_geracoes):
    plt.plot(x,y,'b--')

plt.subplot(322)
plt.plot(t,Y,'k')
x,y=ajeita_plot(grafico_ind[1],grafico_notas[1])
for i in range(qtde_geracoes):
    plt.plot(x,y,'b--')

plt.subplot(323)
plt.plot(t,Y,'k')
x,y=ajeita_plot(grafico_ind[2],grafico_notas[2])
for i in range(qtde_geracoes):
    plt.plot(x,y,'b--')

plt.subplot(324)
plt.plot(t,Y,'k')
x,y=ajeita_plot(grafico_ind[3],grafico_notas[3])
for i in range(qtde_geracoes):
    plt.plot(x,y,'b--')

plt.subplot(313)
t=[i for i in range(qtde_geracoes+1)]
for individuo in grafico_ind:
    plt.plot(t,individuo,'--')

plt.savefig('dificil')

plt.show()
