import math

fact = []

def build_fact(n = 256):
    fact.append(1)
    for i in range(1, n+1):
        fact.append(fact[-1]*i)

build_fact()

uv = [(256,8), (256,7), (256,6), (256,5), (256,4), (256,3), (128,8), (128,7), (128,6), (128,5), (128,4), (128,3), (64,8), (64,7), (64,6), (64,5), (64,4), (64,3), (32,8), (32,7), (32,6), (32,5), (32,4), (16,8), (16,7), (16,6), (16,5), (16,4), (8,8), (8,7), (8,6), (8,5), (4,8), (4,7)]

for (u,v) in uv:
    print('u: ', u, ', v: ', v)
    
    vv = int(2**v)

    sm = 0
    idx = 0
    f = open("Sampling_Result_AES.txt", "r")
    lines = f.readlines()
    for line in lines:
        idx += 1
        if idx%65536 == 0:
            print('idx: ', idx)
        tmp = fact[u]
        a = [0]*vv
        
        for j in range(0,u):
            a[int(line.split()[j])%vv] += 1
        
        for j in range(0,vv):
            tmp //= fact[a[j]]
        sm += tmp
    f.close()
    print("fpp_AES: ", math.log2(sm)-v*u)
    
    sm = 0
    idx = 0
    f = open("Sampling_Result_ARIA.txt", "r")
    lines = f.readlines()
    for line in lines:
        idx += 1
        if idx%65536 == 0:
            print('idx: ', idx)
        tmp = fact[u]
        a = [0]*vv
        
        for j in range(0,u):
            a[int(line.split()[j])%vv] += 1
        
        for j in range(0,vv):
            tmp //= fact[a[j]]
        sm += tmp
    f.close()
    print("fpp_ARIA: ", math.log2(sm)-v*u)

fo.close()
