from math import *
T=int(input())
n=50000
f=[0]*n
f[1]=1
f[2]=2
for i in range(3,n):
	f[i]=f[i-1]+f[i-2]+1
		
#print log(f[n-1],10)

def sol():
	n=int(raw_input())
	x=0
	for i in range(1,n):
		if(f[i]>=n):
			x=i
			break
	print x-1-x/2
while T>0:
	T-=1
	sol()
