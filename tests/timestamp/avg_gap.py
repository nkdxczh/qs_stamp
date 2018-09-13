f=open('64/gap')

s=0
c=0
for i in f:
    s+=float(i)
    c+=1
print s/c
