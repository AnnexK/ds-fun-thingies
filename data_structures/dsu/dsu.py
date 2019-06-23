class dsu:
    """Реализация структуры данных 'объединение-поиск' (disjoint-set union, DSU) с помощью хеш-таблиц"""
    def __init__(self):
        self.__lead = {}
        self.__rank = {}
        
    def append(self, elem):
        """Добавление нового элемента с созданием нового множества"""
        if (self.__lead.get(elem) is None): # если элемента нет в таблице
            self.__lead[elem] = elem
            self.__rank[elem] = 0

    def find(self, x):
        """Поиск представителя множества, содержащего x, с применением сжатия путей"""
        try:
            if self.__lead[x] != x:
                self.__lead[x] = self.find(self.__lead[x])
            return self.__lead[x]
        except KeyError as K:
            raise KeyError('Нет такого элемента: {}'.format(K.args[0]))

    def __link(self, x, y):
        """Присоединение одного множества к другому с использованием ранговой эвристики"""
        if self.__rank[x] > self.__rank[y]:
            self.__lead[y] = x
        else:
            self.__lead[x] = y
            if self.__rank[x] == self.__rank[y]:
                self.__rank[y] += 1
        
    def union(self, x, y):
        """Объединение множеств, содержащих элементы x и y"""
        try:
            self.__link(self.find(x), self.find(y))
        except KeyError as K:
            raise KeyError('Нет такого элемента: {}'.format(K.args[0]))

    def same(self, x, y):
        """Находятся ли x и y в одном множестве?"""
        try:
            return self.find(x) == self.find(y)
        except KeyError as K:
            raise KeyError('Нет такого элемента: {}'.format(K.args[0]))
