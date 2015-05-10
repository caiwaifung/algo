import sys

sys.stdin = open("B-large-practice.in", "r")
sys.stdout = open("B-large-practice.out", "w")

def gcd(a, b):
	return (a if b == 0 else gcd(b, a%b))

case_count = int(input())

for case_id in range(case_count):

	line = input().split(" ")
	n = int(line[0])
	a = [0] * n
	for i in range(n):
		a[i] = int(line[i+1])
		
	if n == 1:
		print("Case #" + str(case_id+1) + ": 0")
	else:		
		a = sorted(a)
		p = a[1] - a[0]
		for i in range(2, n):
			p = gcd(p, a[i] - a[i-1])
		p = (p - a[1]%p) % p
		print("Case #" + str(case_id+1) + ": " + str(p))