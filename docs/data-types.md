# Data Types

```
   name     You use:
00=Real         log(    Real Format
01=List         A       Real Format
02=Matrix       B       Real Format
03=EQU          C       Symbol Var
04=String       D       Symbol Var
05=Program      E       Named Var
06=ProtProg     [       Named Var
07=Picture      ]       Symbol Var
08=GDB          {       Symbol Var
09=Unknown      }       Not Supported
10=UnknownEqu   J       Not Supported
11=New EQU      K       Not Supported
12=Complex      L       Real Format
13=Complex List M       Real Format
14=Undefined    N       Not Supported
15=Window       O       Not Supported
16=ZSto         0       Not Supported
17=Table Range  1       Not Supported
18=LCD          2       Not Supported
19=BackUp       3       Not Supported
20=App          4       Not Supported
21=Appvar       5       Named Var
22=TempProg     6       Named Var
23=Group        7       Named Var   this can mess stuff up unless you *really* know what you are doing.
```

Symbol Vars are compatible with each other.
Named Vars are compatible with each other.
Real Format variables are a special format generally not supported by Grammer.
