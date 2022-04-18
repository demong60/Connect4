import matplotlib.pyplot as plt
import numpy as np

def ReadData():
    n = int(input())
    list = []
    for i in range(n):
        line = input()
        list.append(line.split())

    move_list = []
    node_list = []
    time_list = []
    
    for line in list:
        move_list.append(line[0])
        node_list.append(float(line[1]))
        time_list.append(float(line[2]))
    return move_list, node_list, time_list

def SimplePlot():
    move_list, node_list, time_list = ReadData()

    y = node_list

    plt.scatter(move_list, y, label="Min Max", color='orange')
    plt.xticks(move_list, labels=move_list)
    #plt.ylabel("Tempo (Milissegundos)")
    plt.ylabel("Nodes em Memória")
    plt.xlabel("Número da jogada")

    plt.title("Min Max Alpha-Beta Pruning")
    plt.legend(loc='center right')

    for xs, ys in zip(move_list, y):
        plt.annotate(format(ys, '.0E'),  # this is the text
                     (xs, ys),  # these are the coordinates to position the label
                     textcoords="offset points",  # how to position the text
                     xytext=(0, 10),  # distance from text to points (x,y)
                     ha='center')  # horizontal alignment can be left, right or center

    plt.savefig("Node_List_MinMax_MaxDepth.svg", bbox_inches='tight')

SimplePlot()