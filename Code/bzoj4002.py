import math
b,d,n=map(int,raw_input().split())
def pw(x,k):
	ans=1	
	while(k):
		if(k%2==1):ans=ans*x
		x=x*x
		k=k/2
	return ans
res=int(pw((b+math.sqrt(d))/2,n))
print res%7528443412579576937
	
