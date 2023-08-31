import math

fact = []

def build_fact(n = 256):
    fact.append(1)
    for i in range(1, n+1):
        fact.append(fact[-1]*i)

def A(i, j, k, l):
    if i == 1:
        ret = fact[l]//fact[j]
        ret = int(ret**k)
        return ret
    
    dp = [[0 for _ in range(j+1)] for __ in range(i+1)]
    for y in range(0, j+1):
        dp[1][y] = int((fact[l]//fact[y])**k)
        
    for x in range(2, i+1):
        for y in range(0, j+1):
            dp[x][y] = 0
            for z in range(0, y+1):
                dp[x][y] += dp[x-1][z]//(int(fact[y-z]**k))
    
    return dp[i][j]

def Delta(x, N, u, v):
    term1 = 1 # binom(N, x)
    for i in range(1, x+1):
        term1 *= (N+1-i)
    for i in range(1, x+1):
        term1 //= i
    term1 = math.log2(term1)
    
    term2 = -u * v * (x+1) # 2^(-uv(x+1))
    
    term3 = math.log2(A(int(2**v), u, x+1, u))
    
    return term1+term2+term3

build_fact()

print("Table 3. Comparison of Delta_1 and Delta_2 according to u and v.")
uv = [(256, 8), (256, 7), (256, 6), (256, 5), (128, 8), (128, 7), (128, 6), (64, 8), (64, 7), (64, 6), (32, 8), (32, 7), (16, 8)]
for (u,v) in uv:
    print("u: ", u, ", v: ", v, ", Delta_1: 2^", Delta(1, int(2**80), u, v), ", Delta_2: 2^", Delta(2, int(2**80), u, v))
    
print("\nTable 4. (2^{-2uv} \\cdot A_{2^v, u, 2, u}) according to u and v.")
for u in [256, 128, 64, 32, 16, 8, 4, 2]:
    for v in [8, 7, 6, 5, 4, 3, 2, 1]:
        print("u: ", u, ", v: ", v, ", (2^{-2uv} \\cdot A_{2^v, u, 2, u}): 2^", math.log2(A(int(2**v), u, 2, u))-2*u*v)
