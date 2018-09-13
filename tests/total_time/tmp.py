f1=open('rtm_avg')
f2=open('qs_tx_avg')

for i in f1:
    j=f2.readline()
    x=i.split(' ')[0]
    y=float(j)/float(i.split(' ')[1])
    print x,y
