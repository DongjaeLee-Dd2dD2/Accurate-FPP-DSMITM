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

uv = [(256,8), (256,7), (256,6), (256,5), (256,4), (256,3), (128,8), (128,7), (128,6), (128,5), (128,4), (128,3), (64,8), (64,7), (64,6), (64,5), (64,4), (64,3), (32,8), (32,7), (32,6), (32,5), (32,4), (16,8), (16,7), (16,6), (16,5), (16,4), (8,8), (8,7), (8,6), (8,5), (4,8), (4,7)]

build_fact()

print("Table 5. Toy experiment results")
for (u,v) in uv:
    print('u: ', u, ', v: ', v)
    
    ###### Our Method ######
    print("Approx[1]: ", Delta(1, int(2**20), u, v))
    vv = int(2**v)

    ###### Exhaustive Calculation ######
    #### AES ####
    # Step 1: Initiallize P_fp with 0.
    P_fp = 0
    f = open("Sampling_Result_AES.txt", "r")
    lines = f.readlines()
    for line in lines:
        tmp = fact[u]
        
        # Step 2-(a): Transform to (u,v)-multiset
        a = [0]*vv
        
        for j in range(0,u):
            a[int(line.split()[j])%vv] += 1
        
        # Step 2-(b): Add the number of (u,v)-sequences that are associated with m
        for j in range(0,vv):
            tmp //= fact[a[j]]
        P_fp += tmp
    f.close()
    
    # Step 3: Divide P_fp with |S_{u,v}|
    print("fpp_AES: ", math.log2(P_fp)-v*u)
    
    #### ARIA ####
    P_fp = 0
    f = open("Sampling_Result_ARIA.txt", "r")
    lines = f.readlines()
    for line in lines:
        tmp = fact[u]
        a = [0]*vv
        
        for j in range(0,u):
            a[int(line.split()[j])%vv] += 1
        
        for j in range(0,vv):
            tmp //= fact[a[j]]
        P_fp += tmp
    f.close()
    print("fpp_ARIA: ", math.log2(P_fp)-v*u, "\n")
