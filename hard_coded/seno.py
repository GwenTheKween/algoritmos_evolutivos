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
    if(pai is mae): #evita auto transa
	    return mae
    filho=(pai+mae)/2
    diff=np.abs(pai-mae)
    return filho + 4*(random() - 1)

def avalia(x):
    return x*(x-200)*np.sin(0.2*x)

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
qtde_geracoes=20 #quantidade de iteracoes
grafico_ind=[[] for i in range(TamPop)]
grafico_notas=[[] for i in range(TamPop)]
grafico_media=[]
grafico_melhor=[]

#inicia as populacoes
for i in range(TamPop):
    ind.append(gera_individuo())
c=''
#flag=True
flag=False
#iteracoes do algoritmo
for j in range(qtde_geracoes):
    #avalia a viabilidade
    notas=[avalia(i) for i in ind]

    #salva os dados para plotar os graficos
    for i in range(TamPop):
        grafico_ind[i].append(ind[i])
        grafico_notas[i].append(notas[i])

    grafico_media.append(sum(notas)/TamPop)
    #escolhe o individuo mais viavel
    mx=0
    for i in range(1,TamPop):
        if(notas[i]>notas[mx]):
            mx=i
    grafico_melhor.append(notas[mx])
    #gera os novos individuos, matando todos os antigos
    ind=[transa(ind[i],ind[mx]) for i in range(TamPop)]
    if(flag):
    	#processamento para plotar os graficos
        t=np.linspace(0,200,1000)
        Y=avalia(t)


        plt.subplot(221)
        plt.plot(t,Y,'k')
        x,y=ajeita_plot(grafico_ind[0],grafico_notas[0])
        for i in range(qtde_geracoes):
            plt.plot(x,y,'b--')

        plt.subplot(222)
        plt.plot(t,Y,'k')
        x,y=ajeita_plot(grafico_ind[1],grafico_notas[1])
        for i in range(qtde_geracoes):
            plt.plot(x,y,'b--')
        plt.subplot(223)
        plt.plot(t,Y,'k')
        x,y=ajeita_plot(grafico_ind[2],grafico_notas[2])
        for i in range(qtde_geracoes):
            plt.plot(x,y,'b--')

        plt.subplot(224)
        plt.plot(t,Y,'k')
        x,y=ajeita_plot(grafico_ind[3],grafico_notas[3])
        for i in range(qtde_geracoes):
            plt.plot(x,y,'b--')

        plt.show()
        c=input()
        if(c=='q'):
            flag=False

print(ind[mx],avalia(ind[mx]))

grafico_media.append(sum(notas)/TamPop)
grafico_melhor.append(max(notas))

#termina os dados do grafico
for i in range(TamPop):
    grafico_ind[i].append(ind[i])
    #eh necessario re-avaliar pq a ultima iteracao termina gerando individuos
    grafico_notas[i].append(avalia(ind[i]))


#processamento para plotar os graficos
t=np.linspace(0,200,1000)
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

#plt.savefig('seno')

plt.show()

plt.subplot(111)
plt.plot(t,grafico_media,'b',label='media')
plt.plot(t,grafico_melhor,'r',label='melhor')
plt.show()
