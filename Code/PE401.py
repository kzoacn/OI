from math import *
def si2(x):
	ans=0
	for i in range(1,int(sqrt(x))+1):
		if(x%i==0):
			ans+=i*i
			if(i*i!=x):
				ans+=(x/i)*(x/i)
	return ans
def si(x):
	ans=0
	for i in range(1,x+1):
		ans+=si2(i)
	return ans
def S(x):return (x*(x+1)*(2*x+1)/6)%1000000000
def f(x):
	ans=0
	i,j=1,1
	while(i<=x):
		j=x//(x//i)
		ans+=(S(j)-S(i-1))*(x//i)
		ans%=1000000000
		i=j+1
		if(i%100000<10):print i
	return ans
print f(1000000000000000)
