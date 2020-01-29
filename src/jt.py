import sys
#This reads the jumptable.z80 and generates an include file
hexd="0123456789ABCDEF"
def hexify(x,n):
  s=''
  while n>0:
    s=hexd[x&15]+s
    x>>=4
    n-=1
  return s
def makejt(l):
  s=''
  base=0
  for i in l.split('\n'):
    if i[0:7]==";start=":
      base=int(i[7:],16)
    i=i.strip(" ").strip("\t")
    if i[0:3]=="jp ":
      if base==0:
        print("WARNING! Jumptable has ';start=0'")
      t=i[3:]
      s+=t+" "*(20-len(t))+"= $"+hexify(base,4)+"\n"
      base+=3
  return s
if len(sys.argv)<3:
  print("Too few arguments!\n  python "+sys.argv[0]+" <input file> <output file>")
else:
  f=open(sys.argv[1],'r')
  j=f.read()
  f.close()
  f=open(sys.argv[2],'r')
  s = f.read()
  f.close()
  t = "#ifndef NO_JUMP_TABLE\n"
  s = s.split(t)[0]
  s += t
  s += makejt(j)
  s += "#endif"
  f=open(sys.argv[2],'w')
  f.write(s)
  f.close()
