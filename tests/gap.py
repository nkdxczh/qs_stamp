f = open("time3")

gap = open("gap", 'w')
read = False
status = -1
target = 32
data = 1

count = 0
Sum = 0
allc = 0

for line in f:
    if line[0] == '~':
        if count > 0:
            print str(allc)
            print str(Sum / count)
        allc = 0
        Sum = 0
        count = 0
        gap.close()
        read = False
        status = 0
    elif line[0] == '-':
        status = 1
    elif status == 0:
        gap = open("timestamp/"+line.strip()+"/gap", 'w')
        read = True
        data = 1
    elif status >= 1 and status <= 3:
        status += 1
    elif read:
        if data == 1:
            allc += 1
            begin = float(line.strip())
            data = 2
        else:
            allc += 1
            if float(line.strip()) > begin or True: 
                Sum += float(line.strip()) - begin
                count += 1
                gap.write(str(float(line.strip()) - begin) + '\n')
            data = 1

gap.close()
