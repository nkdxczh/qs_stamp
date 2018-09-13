f1=open('avg')
f2=open('rtm_avg')
for i in [1,2,4,8,16,32,64]:
    l1=float(f1.readline())
    l2=float(f2.readline())
    print l1/(l2)
