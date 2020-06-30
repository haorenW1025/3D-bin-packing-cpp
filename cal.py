import numpy as np
f = open("mutation_only_200.txt", "r")
temp = f.read().split('\n')
data = []
for i in temp:
    if i:
        data.append(i.split())
for i in range(len(data)):
    for j in range(len(data[0])):
        data[i][j] = float(data[i][j])
data = np.asarray(data)
print(data.shape)
mean = np.mean(data, axis=0)
std = np.std(data, axis=0)
print(mean)
print(std)
print(data.min(axis=0))