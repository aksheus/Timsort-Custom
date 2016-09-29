from random import randrange
k=10**6
with open('input.txt','a') as fin:
	print(k,file=fin)
	for _ in range(k):
		print(randrange(1,k),file=fin)


