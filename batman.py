from sys import stdin

cases = 0
bwandm = []
batchopencost = []
ocosts = []
opowers = []
allapot = "bwm"
tcaseindex = 0
ered = []

for line in stdin:
    line = line.strip()
    if line != "":
        if cases == 0:
            cases = int(line)
        elif allapot == "bwm":
            bwandm.append([])
            bwandmstr = line.split(" ")
            for i in range(len(bwandmstr)):
                bwandm[tcaseindex].append(int(bwandmstr[i]))
            allapot = "batchop"
        elif allapot == "batchop":
            batchopencost.append([])
            batch = line.split(" ")
            for i in range(len(batch)):
                batchopencost[tcaseindex].append(int(batch[i]))
            allapot = "costs"
        elif allapot == "costs":
            if tcaseindex == len(ocosts):
                ocosts.append([])
            ocosts[tcaseindex].append([])
            cost = line.split(" ")
            for i in range(len(cost)):
                ocosts[tcaseindex][len(ocosts[tcaseindex])-1].append(int(cost[i]))
            if len(ocosts[tcaseindex]) == bwandm[tcaseindex][0]:
                allapot = "powers"
        elif allapot == "powers":
            if tcaseindex == len(opowers):
                opowers.append([])
            opowers[tcaseindex].append([])
            power = line.split(" ")
            for i in range(len(power)):
                opowers[tcaseindex][len(opowers[tcaseindex])-1].append(int(power[i]))
            if len(opowers[tcaseindex]) == bwandm[tcaseindex][0]:
                allapot = "bwm"
                tcaseindex += 1
        if tcaseindex == cases:
            break


for i in range(cases):
    bocintar = batchopencost[i]
    money = bwandm[i][2]
    powers = opowers[i]
    costs = ocosts[i]

    ertek = []
    tmp = []
    for j in range(money+1):
        ertek.append(0)
        tmp.append(0)
    for k in range(len(costs)):
        for j in range(1, money + 1):
            tmp[j] = ertek[j]
        for j in range(1, money + 1):
            for l in range(len(costs[k])):
                if j >= costs[k][l]:
                    tmp[j] = max(tmp[j], tmp[j - costs[k][l]] + powers[k][l])
        for j in range(bocintar[k],money + 1):
            ertek[j] = max(ertek[j], tmp[j-bocintar[k]])

    ered.append(ertek[money])

for i in range(len(ered)):
    print(str(ered[i]))
