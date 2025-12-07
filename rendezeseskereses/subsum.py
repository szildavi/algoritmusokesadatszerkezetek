from sys import stdin

size = 0
x = 0
integers = []
state = "sizeandx"

for line in stdin:
    line = line.strip()
    if state == "sizeandx":
        tmparray = line.split()
        size = int(tmparray[0])
        x = int(tmparray[1])
        state = "integers"
    elif state == "integers":
        tmparray = line.split()
        for i in range(len(tmparray)):
            integers.append(int(tmparray[i]))
        break


possible = 0
sum = 0
index = 0

for i in range(len(integers)):
    sum += integers[i]
    while sum >= x:
        if sum == x:
            possible += 1
        sum -= integers[index]
        index += 1

print(possible)



