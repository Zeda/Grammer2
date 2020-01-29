Let's set up the `prgm`!
```
.0:Return               ;Make prgm visible to Grammer
```

To make any game that involves a list or matrix you need to initiate the deck.
This involves using an area of safe RAM. Say we wanted a 4 by 4 matrix. A matrix is
just a list of data. To get the elements of this matrix we will use a formula: `(Z+X+Y*R`.

_Note: The `(` is grammers **read byte** token. The Z is a pointer to the area of ram the list will be located. 
The **R** is the number of rows we are using for the matrix._
```
MakeVar(16,"5List→Z     ;Create an appvar and stores the pointer into Z

For K,0,7               ;Starts counting at 0 and increments K until 7

WriteB(Z+K,K            ;Since K is incrementing we can store the value of K
                        ;as well as use the pointer plus K to store the bytes.

WriteB(K+8+Z,K          ;Note this makes it so there are to of the same byte for matching!

End                     ;Ends the For loop if K=7
```

Now we want to shuffle the deck that we made. The OS stores the size of the variable
2 bytes before it's pointer. So we will use `{Z-2` and store it to `K`. Then we will
use the Fisher-Yates algorithm implemented in Grammer by Zeda. ([DeckShuffle.md](../tutorials/DeckShuffle.md))
```
{Z-2→K
While K>2
K-1→K
randInt(0,K→A
(Z+K→B
WriteB(Z+K,(Z+A
WriteB(Z+A,B
End
```

Great! Now we have code that creates the deck and then shuffles it! Now we need to set up graphics...
```
For F,0,3                
For G,0,3
Text(2+8*F,1+2*G,"O     ;Makes a 4x4 display of small font O's
                        ;The math is to manipulate where at on the screen the O's will appear
End
End
Rect(1,0,33,33,3        ;Draws a black border around the small display
DispGraph               ;Displays every thing at once! :D
```

After setting up the Graphics we shall set up the game variables. 
We need to do this so that the game will start and run the way we code it to.
```
0→X→Y
8→θ
```

```
Repeat !θ  or getKey(55
```
```
Rext(2+8*X,1+8*Y,7,7,2
DispGraph
Rext(2+8*X,1+8*Y,7,7,2
```
```
(Z+X+Y*4
If ≠8 *getKey(5
Then
If B
Then
→A
0→B
Z+X+Y*4
If ≠D *!B
Then
→E
(E→C
1→B
2+8*Y→H
1+2*X→I
Text('5,12,C
DispGraph
If C≠A
Pause 30
Text(5,10,"_ _ _            ;3 Spaces to remove the numbers
Else
WriteB(D,8:WriteB(E,8
Text(F,G,"X
Text(H,I,"X
θ-1→θ
End
End
End
```
```
X+getKey(3 -getkey(2
max(0,min3,Ans→X
Y+getKey(1 -getKey(4
max(0,min(3,Ans→Y
End
```
```
Stop
```
