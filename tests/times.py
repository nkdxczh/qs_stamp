def conclude(firstAll, secondAll):
    Min = min(firstAll)
    Max = max(secondAll)

    grain = 0.0005
    length = int((Max - Min) / grain) + 1
    firstCount = [0 for i in range(length)]
    secondCount = [0 for i in range(length)]

    for i in firstAll:
        firstCount[int((i - Min)/grain)] += 1

    for i in secondAll:
        secondCount[int((i - Min)/grain)] += 1

    return grain, Min, firstCount, secondCount

f = open("time3")
first = open("first", 'w')
second = open("second", 'w')
#third = open("third", 'w')
read = False
status = -1
target = 32
data = 1

none = True

firstAll = []
secondAll = []

for line in f:
    if line[0] == '~':
        first.close()
        second.close()
        #third.close()
        read = False
        status = 0
        if none:
            none = False
        else:
            grain, Min, firstCount, secondCount = conclude(firstAll, secondAll)
            print len(firstCount)
            for i in range(len(firstCount)):
                if firstCount[i] > 0:
                    res.write(str(i*grain + Min) + " " + str(float(secondCount[i]) / firstCount[i]) + '\n')
            res.close()
        firstAll = []
        secondAll = []
    elif line[0] == '-':
        status = 1
    elif status == 0:
        print line.strip()
        first = open("timestamp/"+line.strip()+"/first", 'w')
        second = open("timestamp/"+line.strip()+"/second", 'w')
        #third = open("timestamp/"+line.strip()+"/third", 'w')
        res = open("timestamp/"+line.strip()+ '/distribute', 'w')

        read = True
        data = 1
    elif status >= 1 and status <= 3:
        status += 1
    elif read:
        if data == 1:
            first.write(line.strip() + '\n')
            firstAll.append(float(line.strip()))
            data = 2
        elif data == 2:
            second.write(line.strip() + '\n')
            secondAll.append(float(line.strip()))
            data = 1

grain, Min, firstCount, secondCount = conclude(firstAll, secondAll)
print len(firstCount)
for i in range(len(firstCount)):
    if firstCount[i] > 0:
        res.write(str(i*grain + Min) + " " + str(float(secondCount[i]) / firstCount[i]) + '\n')
res.close()
first.close()
second.close()
#third.close()

