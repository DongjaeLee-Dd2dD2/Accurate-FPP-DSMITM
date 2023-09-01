import math

fact = []
fact.append(1)
for i in range(1,256+1):
    fact.append(fact[i-1]*i)

fo = open("False_Positive_Probability_ARIA.txt", "w")

ulist = [256, 128, 64, 32, 16, 8, 4, 2]
vlist = [256, 128, 64, 32, 16, 8, 4, 2]

for u in ulist:
    for v in vlist:
        print('u: ', u, ', v: ', v)
        fo.write('u: ' + str(u) + ', v: ' + str(v) + '\n')
        sm = 0
        idx = 0
        f = open("result.txt", "r")
        lines = f.readlines()
        for line in lines:
            idx += 1
            if idx%65536 == 0:
                print('idx: ', idx)
            tmp = fact[u]
            a = [0]*v
            
            for j in range(0,u):
                a[int(line.split()[j])%v] += 1
            
            for j in range(0,v):
                tmp //= fact[a[j]]
            sm += tmp
        f.close()
        print(sm)
        fo.write(str(sm) + '\n')
        print(math.log2(sm))
        fo.write(str(math.log2(sm)) + '\n')
        print(math.log2(sm)-math.log2(v)*u)
        fo.write(str(math.log2(sm)-math.log2(v)*u) + '\n')

fo.close()
