from os import listdir
from os.path import isfile, join

def readFile(input, outputs, flag, base):
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
                    if current <= 64:
                        times.sort()
                        if flag == 0:
                            out1.write(str(current) + " " + str(times[0]) + "\n")
                        elif flag == 1:
                            out1.write(str(current) + " " + str(times[-1]) + "\n")
                        elif flag == 2:
                            out1.write(str(current) + " " + str(times[len(times)/2]) + "\n")
                        elif flag == 3:
                            if len(times) > 0:
                                dur = sum(times) / len(times)
                                dur = times[len(times) / 2]
                                speedup = base/dur
                                out1.write(str(current) + " " + str(speedup) + " " + str(times[0]) + " " + str(times[-1]) + "\n")
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

    if current > 64:
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
            dur = sum(times) / len(times)
            dur = times[len(times) / 2]
            speedup = base/dur
            out1.write(str(current) + " " + str(speedup) + " " + str(times[0]) + " " + str(times[-1]) + "\n")
    elif flag == 4:
        out1.write(str(current) + " " + str(sum(times[:-1]) / (len(times) - 1)) + "\n")


    if len(times) > 0:
        out2.write(str(current) + " " + str(sum(txs) / len(times)) + "\n")
        out3.write(str(current) + " " + str(sum(conflicts) / len(times)) + "\n")
    out1.close()
    out2.close()
    out3.close()

alld = listdir('data')
#alld = ['vacationhigh']
#print len(alld)
print alld

baseline=dict()
baseline['genome++']=7.423782
baseline['genome-']=0.009298
baseline['genome+']=0.010253
baseline['genome']=7.423782

baseline['intruder++']=15.893175
baseline['intruder+']=0.022405
baseline['intruder-']=0.008512
baseline['intruder']=0.008512

baseline['kmeanshigh++']=1.31355
baseline['kmeanshigh+']=0.011179
baseline['kmeanshigh']=0.015509
baseline['kmeans-high']=0.015509

baseline['kmeanslow++']=7.81184
baseline['kmeanslow+']=0.053961
baseline['kmeanslow']=0.031820
baseline['kmeans-low']=0.031820

baseline['ssca2++']=7.877823
baseline['ssca2+']=0.043058
baseline['ssca2-']=0.023238
baseline['ssca2-']=0.015
baseline['ssca2']=0.023238

baseline['vacationhigh++']=14.794115
baseline['vacationhigh+']=0.016892
baseline['vacationhigh']=0.023331
baseline['vacation-high']=0.023331

baseline['vacationlow++']=11.040216
baseline['vacationlow+']=0.013454
baseline['vacationlow']=0.017063
baseline['vacation-low']=0.017063

baseline['yada++']=6.218
baseline['yada+']=0.277
baseline['yada-']=0.025578
baseline['yada']=0.025578

for d in alld:
    test = d
    d = 'data/' + d
    readFile(d+'/qs_output', [d+'/qs_time', d+'/qs_tx', d+'/qs_conflict'], 3, baseline[test])
    readFile(d+'/rtm_output', [d+'/rtm_time', d+'/rtm_tx', d+'/rtm_conflict'], 3, baseline[test])
    readFile(d+'/hle_output', [d+'/hle_time', d+'/hle_tx', d+'/hle_conflict'], 3, baseline[test])
    readFile(d+'/scm_output', [d+'/scm_time', d+'/scm_tx', d+'/scm_conflict'], 3, baseline[test])
    readFile(d+'/seer_output', [d+'/seer_time', d+'/seer_tx', d+'/seer_conflict'], 3, baseline[test])
