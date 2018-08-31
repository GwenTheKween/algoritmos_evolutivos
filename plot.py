#!/usr/bin/python3

import matplotlib.pyplot as plt
import sys

def plot(column,files):
	for f_name in files:
		with open(f_name) as f:
			data=[]
			for line in f:
				data.append([float(x) for x in line.split()[column[0]:column[1]+1]])
			x=[int(k[0]) for k in data]
			y=[[] for i in range(len(data[0])-1)]
			for i in data:
				i=i[1:]
				for j in range(len(i)):
					y[j].append(i[j])
			print(x,y,sep='\n')
			for i in y:
				plt.plot(x,i)
			plt.savefig(f_name+"_grafico.png")
			plt.clf()

def main():
	if(len(sys.argv)<2):
		print("usage: {0} n-m <files>".format(sys.argv[0]))
		print("where n is the starting column (used as the x axis) and m is the last column to be plotted")
		print("and <files> is the name of the files to be ploted (each in a different graph)")
		print("if multiple files, -s indicate to keep all graph in the same image, but different subplots")
		return
	columns=[int(x) for x in sys.argv[1].split('-')]
	files=sys.argv[2:]
	plot(columns,files)

main()
