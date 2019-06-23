class SingleList:
    def __init__(self, data):
        self.data = data
        self.next = None

    def append(self, L):
        self.next = L
    
    def search(self, key):
        cur = self
        while cur is not None:
            if cur.data == key:
                break
            cur = cur.next
        return cur