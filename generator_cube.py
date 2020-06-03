import random

f = open('input/input_cube2.txt', 'w')

f.write(str(30.0) + '\n')
f.write(str(100) + '\n')

l = []
for i in range(100):
    n = [round(random.uniform(5, 15), 1), round(random.uniform(5, 15), 1), round(random.uniform(5, 15), 1)]
    l.append(n)

l.sort(reverse=True, key = lambda s: s[0]*s[1]*s[2])
for i in l:
    f.write(str(i[0]) + ' ' + str(i[1]) + ' ' + str(i[2]) + '\n')

f.close()