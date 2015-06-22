m=int(raw_input())
h1,a1=map(lambda x :int(x)%m,raw_input().split())
x1,y1=map(lambda x :int(x)%m,raw_input().split())
h2,a2=map(lambda x :int(x)%m,raw_input().split())
x2,y2=map(lambda x :int(x)%m,raw_input().split())
flag=0
for i in range(0,m):
	h1=(x1*h1+y1)%m
	h2=(x2*h2+y2)%m
	if(h1==a1 and h2==a2):
		print i+1
		flag=1
		break
if(flag==0):print -1
