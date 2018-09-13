f=open('qs_total')

s=0
c=0
d=0
base=0
for i in f:
    if i[0]=='-':
        d=1
    elif i[0]=='~':
        if d==0:
            continue
        print base-s/c
        s=0
        c=0
        d=0
    elif i[0] == '^':
        #print s/c
        base=s/c
        s=0
        c=0
        d=2
    elif d==1:
        tmps=float(i.split(',')[0])
        tmpc=int(i.split(',')[1])
        s+=tmps*tmpc
        c+=tmpc
    elif d==2:
        s+=float(i)
        c+=1

print base-s/c
