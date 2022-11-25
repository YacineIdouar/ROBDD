
def decomposition(number):
    l = []
    while number != 0 :
        l.append(number % 2 == 1)
        number = number // 2
    return l




def completion(l,length):
    if len(l) >= length:
        return l[:length]

    while len(l) < length :
        l.append(False)
    return l


def table(x,n):
    return completion(decomposition(x),n)


def hash_luka(a,b,c,n,m):
    return a + b * m + c * m * n

class TreeException  (Exception):
    def __init__(self, s):
        super().__init__(s)




