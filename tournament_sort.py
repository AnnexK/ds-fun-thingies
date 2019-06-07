# "дырки" в дереве
from math import inf

def tournament_sort(A):
    arr_size = len(A)
    if arr_size <= 1: # отсортировано
        return A
    
    tree = [None for i in range(arr_size - 1)] + A
    # построение дерева
    for i in range (arr_size-2, -1, -1):
        tree[i] = min(tree[2*i+1], tree[2*i+2])

    for i in range(arr_size):
        # запись "победителя" в массив
        A[i] = tree[0]
        # поиск места для "дырки"
        j = 0
        while j < arr_size-1:
            j = 2*j+1 if tree[j] == tree[2*j+1] else 2*j+2
        # вставка "дырки" в нижний уровень
        tree[j] = inf
        # вставка соседей "победителя" на место победителя
        while j > 0:
            j = (j-1)//2
            tree[j] = min(tree[2*j+1], tree[2*j+2])

    return A
        
