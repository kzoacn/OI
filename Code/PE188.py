mo=1000000000
def pw(x,k):
	an=1
	while(k>0):
		if(k%2==1):an=an*x%mo
		x=x*x%mo
		k>>=1
	return an
def ppw(x,k):
	

