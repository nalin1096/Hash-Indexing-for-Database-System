import numpy as np 

s = np.random.uniform(0,800000,100000)
s = s.astype(int)

f = open("db_a.txt","w")
for num in s:
	f.write(str(num))
	f.write("\n")
f.close()

s = np.random.uniform(700000,800000,70000)
s = s.astype(int)
p = np.random.uniform(0,700000,30000)
p = p.astype(int)
s = np.append(s,p)

f = open("db_b.txt","w")
for num in s:
	f.write(str(num) + "\n")
f.close()