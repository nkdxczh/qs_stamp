f=open('rtm_total')

s=0
c=0
d=0
for i in f:
    if i[0]=='-':
        d=1
    elif i[0]=='~':
        if d==0:
            continue
        d=0
    elif i[0] == '^':
        print s/c
        s=0
        c=0
        d=2
    elif d==1:
        tmps=float(i.split(',')[0])
        tmpc=int(i.split(',')[1])
        s+=tmps*tmpc
        c+=tmpc
