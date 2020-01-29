# Control Flow

If you already know how to use BASIC control flow you can skip to the next
section on Grammer's control flow perks. `If` not, then read up on this section
before moving on. There is a lot of info to retain.

Control Flow is the ability to control the flow of your program. We do this by
using commands such as `If`, `While`, `Repeat`, `For`, and `Goto`/`Lbl`.

## Code Blocks and Loops

## Using If-Then-Else

If I use `If` in a program `Then`, *if* the statement is true *then* the
following code will be executed until the corresponding `End` token is reached.

Code:
```
If 1
Then
<<<code to execute>>>
End
```
*Note: In Grammer, `true` simply means non-zero, while `0` is `false`, as in
TI-BASIC.*

However, as in TI-BASIC, if we only need to execute one line of code, `Then` and
`End` can be omitted.

Code:
```
If 1
<<<code to execute>>>
```

If I use an `If`, `Then`, and `Else` in a single block _then_ if the statement
is true, the following code will be executed until the `Else` token. If the
statement is false the code under `Else` will be executed until the
corresponding `End` token is reached.

Code:
```
If 0
Then
<<<code to execute if true>>>
Else
<<<code to execute if false>>>
End
```

A statement is any block of math to be used after the `If`. I used `1` and `0`
as to represent not just how `If` sees the equation but all control flow
commands. However, you can use a variable such as `A` or an expression like
`A>1` which would return `1` if `A` is greater than `1` and `0` if less than
`A`.


### While loops
While loops repeat _while_ the statement is true. 

### Repeat loops



### For loops



### Pause & Pause If
A pause is pretty much like a loop. The only difference is the way that it loops. 
In Grammer Pause can be used in 3 ways, so long as you don't count the `!` modifier. 
The syntax is as follows...
```
Pause xx   ;Pauses for approx. xx/100 seconds(useful for delays)
Pause If   ;Pauses while a statement is true
Pause      ;Pauses until [ENTER] is pressed(same as BASIC)
```
#### Pause xx

`Pause xx` is kind of like `For xx:End` It repeats that many times. Don't get the 2 mixed up though!
Let's say you were displaying text and you want to display it in intervals.
`Pause xx` will allow you to do that. 

Code:
```
.0:Return
102→A
ClrDraw
Text(°"Super Cool Text!
DispGraph
Pause A       ;This pauses for about 102/100 of a second.
Text(°" Using Pause !
Pause 50
Text(°" Oh and pvars!
Stop
```


#### Pause

`Pause` is kind of like doing `Repeat getKey(9:End`. It loops over and over until you press [ENTER]
Its best use is probably waiting for the user to press Enter... ;P

Code:
```
.0:Return
ClrDraw
Text(°"Press Enter
DispGraph
Pause
Stop
```


#### Pause If

`Pause If` is a way to use conditional statements with Pause. Please remember
that you can't exit a statement that is always true without pressing [ON].
There are too ways to use this (as far as I'm concerned). The main use for this
is to pause and either wait for a keypress, or wait for the keypress to be done.

Code:
```
.0:Return
ClrDraw
Text(°"Press [MODE]
!Pause If getKey(55              ;Note the use of the ! modifier
Text(10,0,"Thanks!
Stop
```

You might also want to wait for an interrupt to signal for some reason. In this
example, `Pause If S` looks like it should loop forever, but the interrupt is
decrementing S and eventually S will be 0, causing the `Pause If` to finish.

Code:
```
.0:Return
FuncLbl "APPLE
100→S
Pause If S
Text(10,0,"Continues executing once S equals 0.
Stop
.APPLE
ClrDraw
Text('°S
GetDec(S
DispGraph
End
```
Note: This works because interrupts are set. Without them this code wouldn't
really have a way to exit. 

## Labels and Subroutines

### Lbl



### Return



### Goto



### ▶Nom(



### Line Jumping With ln(



### prgm



#### Passing Parameters



### Asm(



### AsmPrgm

## Others

### expr(
### Interrupts
Interrupts are pretty handy when you want a task to be able to run separately
from your main code. For example, with grayscale, maybe you want to be able to
pause but still have grayscale going:

```
.0:Return

FuncLbl "Draw         ;Setup the interrupt to execute .Draw

SetBuf(°gbuf'→B       ;Set up the gray/secondary buffer
2→SetBuf(             ;Set 4-level grayscale

Rect(0,0,16,8         ;Draw a 16x8 rect on the main buffer
Rect(0,0,8,16,1,B     ;Draw an 8x16 rect on the secondary buffer

!Pause If getKey      ;Now wait for a keypress
Stop

.Draw
DispGraph
End
```
This still does DispGraph while the program is Paused!

### Execute a line of code
