#!/usr/bin/python3.5
# -*-coding:Utf-8 -*

def deloche(values,proba):
    l = len(values)
    if l in [0,1]:
        return l
    results = [0]*l
    for i in range(l):
        low = deloche(values[0:i],proba[0:i])*sum(proba[0:i])/sum(proba)
        high = deloche(values[i+1:l],proba[i+1:l])*sum(proba[i+1:l])/sum(proba)
        results[i] = 1 + low + high
    return min(results)

def carre(values,proba,d):
    l = len(values)
    if l == 1:
        return proba[0]*d
    if l == 0:
        return 0
    results = [0]*l
    for i in range(l):
        low = carre(values[0:i],proba[0:i],d+1) 
        high = carre(values[i+1:l],proba[i+1:l],d+1)
        p = proba[i]*d
        results[i] = p + low + high
    return min(results)

def getmin(v,p):
    print("Deloche: ",deloche(v,p))
    print("Carre: ",carre(v,p,1))
    print()


values = [1,2,3,4,5,6,7,8]
proba = [0.1,0.2,0.2,0.1,0.1,0.1,0.1,0.1]
v = [1,2,3]
p1 = [0.2,0.4,0.4]
p2 = [0.5,0.3,0.2]
p3 = [0.6,0.2,0.2]
p4 = [0.3,0.2,0.5]
p5 = [0.1,0.3,0.6]

getmin(values,proba)
getmin(v,p1)
getmin(v,p2)
getmin(v,p3)
getmin(v,p4)
getmin(v,p5)
