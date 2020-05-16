import random

f = open('input/input_4.txt', 'w')

f.write(str(70.0) + '\n')
f.write(str(500) + '\n')

l = []
for i in range(500):
    n = round(random.uniform(5, 15), 1)
    l.append(n)

l.sort(reverse=True)
for i in l:
    f.write(str(i) + '\n')

f.close()
