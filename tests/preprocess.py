from os import listdir
from os.path import isfile, join

def readFile(input, outputs, flag):
    flag = 3
    out1 = open(outputs[0], 'w')
    out2 = open(outputs[1], 'w')
    out3 = open(outputs[2], 'w')
    f = open(input)

    current = 0
    times = []
    txs = []
    conflicts = []
    op = 0

    all_times = []

    for line in f:
        if line[0] in '0123456789-~':
            if line[0] == '~':
                op = 0
            elif line[1] == '-':
                op = 1
            elif op == 0:
                x = int(line.strip())
                if x != current and current != 0:
                    '''print current, len(times)
                    print times
                    print txs
                    print conflicts'''
                    if current < 100:
                        times.sort()
                        if flag == 0:
                            out1.write(str(current) + " " + str(times[0]) + "\n")
                        elif flag == 1:
                            out1.write(str(current) + " " + str(times[-1]) + "\n")
                        elif flag == 2:
                            out1.write(str(current) + " " + str(times[len(times)/2]) + "\n")
                        elif flag == 3:
                            if len(times) > 0:
                                out1.write(str(current) + " " + str(sum(times) / (len(times))) + " " + str(times[0]) + " " + str(times[-1]) + "\n")
                        elif flag == 4:
                            out1.write(str(current) + " " + str(sum(times[:-1]) / (len(times) - 1)) + "\n")
                    if len(txs) > 0:
                        out2.write(str(current) + " " + str(sum(txs) / len(times)) + "\n")
                        out3.write(str(current) + " " + str(sum(conflicts) / len(times)) + "\n")

                    times = []
                    txs = []
                    conflicts = []

                current = x
                op += 1
            elif op == 1:
                times.append(float(line))
                op += 1
            elif op == 2:
                txs.append(float(line))
                op += 1
            elif op == 3:
                conflicts.append(float(line))
                op = 4

    '''print current, len(times)
    print times
    print txs
    print conflicts'''
    if current > 100:
        out1.close()
        out2.close()
        out3.close()
        return

    times.sort()
    if flag == 0:
        out1.write(str(current) + " " + str(times[0]) + "\n")
    elif flag == 1:
        out1.write(str(current) + " " + str(times[-1]) + "\n")
    elif flag == 2:
        out1.write(str(current) + " " + str(times[len(times)/2]) + "\n")
    elif flag == 3:
	if len(times) > 0:
            out1.write(str(current) + " " + str(sum(times) / (len(times))) + " " + str(times[0]) + " " + str(times[-1]) + "\n")
    elif flag == 4:
        out1.write(str(current) + " " + str(sum(times[:-1]) / (len(times) - 1)) + "\n")


    if len(times) > 0:
        out2.write(str(current) + " " + str(sum(txs) / len(times)) + "\n")
        out3.write(str(current) + " " + str(sum(conflicts) / len(times)) + "\n")
    out1.close()
    out2.close()
    out3.close()

alld = listdir('data')
#alld = ['genome-','genome+','genome++',"intruder-","intruder+","intruder++","kmeanshigh","kmeanshigh+","kmeanshigh++","kmeanslow","kmeanslow+","kmeanslow++","ssca2-","ssca2+","ssca2++","vacationhigh","vacationhigh+","vacationhigh++","vacationlow","vacationlow+","vacationlow++","yada-","yada+","yada++"]
#print len(alld)
print alld
for d in alld:
    d = 'data/' + d
    #readFile(d+'/qs_output', [d+'/qs_time', d+'/qs_tx', d+'/qs_conflict'], 3)
    readFile(d+'/rtm_output', [d+'/rtm_time', d+'/rtm_tx', d+'/rtm_conflict'], 3)
    readFile(d+'/hle_output', [d+'/hle_time', d+'/hle_tx', d+'/hle_conflict'], 3)
    readFile(d+'/scm_output', [d+'/scm_time', d+'/scm_tx', d+'/scm_conflict'], 3)
    readFile(d+'/seer_output', [d+'/seer_time', d+'/seer_tx', d+'/seer_conflict'], 3)
