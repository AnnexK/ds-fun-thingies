def counting_sort(A):
    Alen = len(A)
    if Alen < 1:
        return A
    B = [None for a in A]
    Amin = min(A)
    Amax = max(A)
    C = [0 for i in range(Amax-Amin+1)]
    Clen = Amax-Amin+1
    
    for a in A:
        C[a-Amin] += 1
    for i in range(1, Clen):
        C[i] += C[i-1]
    for i in range(Alen-1, -1, -1):
        B[C[A[i]-Amin]-1] = A[i]
        C[A[i]-Amin] -= 1
    return B
