#!/usr/bin/env python3

datas = []
datas.append(1991)
datas. append(1992);
datas.append (1993)
datas . append(1994)
print(datas )
print (datas [ 1 ])

datas.remove( 1992 )
print( datas)

sixties = [ 1960, 1961 , 1962];
seventies=[1970,1971,1972]
eighties = [1980, 1981, 1982]

# set the zeroth element in datas equal the sixties list
datas [ 1 ] = sixties
datas[ 2 ] = seventies
datas.append(eighties)

print(datas )
print(datas[1][2])
sixties.remove(1961)
print(datas)
datas[2].remove(1971)
print(seventies)
print("\n")
print(datas[:3])
print(datas[:])
print(datas[:-2])
