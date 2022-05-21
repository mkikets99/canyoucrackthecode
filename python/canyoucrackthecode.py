from itertools import product
from collections import Counter
from re import search

def replacer(str_to_change,ind,symb):
    return str_to_change[:ind]+symb+str_to_change[ind+1:]

def check_pos(item,rule,is_right):
    rm=not is_right
    for i in range(len(item)):
        if is_right and rule[i]==item[i]:
            rm=True
        if not is_right and rule[i]==item[i]:
            return False
    return rm

def check_count(item,rule,count,Pos=False):
    j=0
    for i in range(len(item)):
        j+=int((item[i] in rule) if not Pos else (item[i]==rule[i]))
    return j==count


def check_and_exit(li,check="None"):
    if len(li)==1 :
        print("Result is:",li[0])
        exit(0)
    if len(li)==0 :
        print("Something wrong",check)
        exit(1)

key_length = int(input("Key length: "))

non_right = input("Code with no right: ")
if len(non_right) is not key_length :
    print("Wrong key lenght")
    exit(1)
elif search("[^0-9]",non_right) :
    print("Wrong key: key must be only with numbers")
    exit(1)
elif len(Counter(non_right).keys()) is not key_length :
    print("Wrong key: no repeating allowed")
    exit(1)

orpr = input("Code with "+str(key_length-2)+" right and right pos: ")
if len(orpr) is not key_length :
    print("Wrong key lenght")
    exit(1)
elif search("[^0-9]",orpr) :
    print("Wrong key: key must be only with numbers")
    exit(1)
elif len(Counter(orpr).keys()) is not key_length :
    print("Wrong key: no repeating allowed")
    exit(1)

orwp1 = input("Code with "+str(key_length-2)+" right but wrong pos: ")
if len(orwp1) is not key_length :
    print("Wrong key lenght")
    exit(1)
elif search("[^0-9]",orwp1) :
    print("Wrong key: key must be only with numbers")
    exit(1)
elif len(Counter(orwp1).keys()) is not key_length :
    print("Wrong key: no repeating allowed")
    exit(1)

orwp2 = input("Second code with "+str(key_length-2)+" right but wrong pos: ")
if len(orwp2) is not key_length :
    print("Wrong key lenght")
    exit(1)
elif search("[^0-9]",orwp2) :
    print("Wrong key: key must be only with numbers")
    exit(1)
elif len(Counter(orwp2).keys()) is not key_length :
    print("Wrong key: no repeating allowed")
    exit(1)

trwp = input("Code with "+str(key_length-1)+" right but wrong pos: ")
if len(trwp) is not key_length :
    print("Wrong key lenght")
    exit(1)
elif search("[^0-9]",trwp) :
    print("Wrong key: key must be only with numbers")
    exit(1)
elif len(Counter(trwp).keys()) is not key_length :
    print("Wrong key: no repeating allowed")
    exit(1)

# first remove non_right
rep_sym='*'
for a in range(key_length):
    if orpr[a] in non_right:
        orpr=replacer(orpr,a,rep_sym)
    if orwp1[a] in non_right:
        orwp1=replacer(orwp1,a,rep_sym)
    if orwp2[a] in non_right:
        orwp2=replacer(orwp2,a,rep_sym)
    if trwp[a] in non_right:
        trwp=replacer(trwp,a,rep_sym)

if Counter(orpr)[rep_sym] > 2 :
    print("Wrong key: Rule is cracked")
    exit(1)
if Counter(orwp1)[rep_sym] > 2 :
    print("Wrong key: Rule is cracked")
    exit(1)
if Counter(orwp2)[rep_sym] > 2 :
    print("Wrong key: Rule is cracked")
    exit(1)
if Counter(trwp)[rep_sym] > 1 :
    print("Wrong key: Rule is cracked")
    exit(1)

for a in range(key_length):
    if orpr[a] == orwp1[a] or orpr[a] == orwp2[a] or orpr[a] == trwp[a]:
        s=orpr[a]
        orpr=replacer(orpr,a,rep_sym)
        if s in orwp1 :
            orwp1=replacer(orwp1,orwp1.index(s),rep_sym)
        if s in orwp2 : 
            orwp2=replacer(orwp2,orwp2.index(s),rep_sym) 
        if s in trwp :
            trwp=replacer(trwp,trwp.index(s),rep_sym)

left = ''.join([str(a) for a in range(10) if str(a) in orpr+orwp1+orwp2+trwp])

all_codes = [a for a in map(''.join,product(left,repeat=key_length))]
all_codes = [a for a in all_codes if len(Counter(a).keys())==key_length]

all_codes = [a for a in all_codes if check_pos(a,orpr,True) ]
check_and_exit(all_codes,"orpr")
all_codes = [a for a in all_codes if check_count(a,trwp,key_length-1) ]
check_and_exit(all_codes,"trwp(2)")
all_codes = [a for a in all_codes if check_count(a,orwp1,key_length-2) ]
check_and_exit(all_codes,"orwp1(2)")
all_codes = [a for a in all_codes if check_count(a,orwp2,key_length-2) ]
check_and_exit(all_codes,"orwp2(2)")
all_codes = [a for a in all_codes if check_count(a,orpr,key_length-2,True) ]
check_and_exit(all_codes,"orpr(2)")
all_codes = [a for a in all_codes if check_pos(a,trwp,False) ]
check_and_exit(all_codes,"trwp")
all_codes = [a for a in all_codes if check_pos(a,orwp1,False) ]
check_and_exit(all_codes,"orwp1")
all_codes = [a for a in all_codes if check_pos(a,orwp2,False) ]
check_and_exit(all_codes,"orwp2")


print(len(all_codes),(all_codes))
