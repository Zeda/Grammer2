To shuffle a deck of cards, you might be inclined to go the classic TI-BASIC route and write some complicated co-sorting algorithm, but you don't need to!
The [Fisher-Yates Shuffle](https://en.m.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle) algorithm is way easier and faster. An example implementation in TI-BASIC to shuffle `L1` looks like:
```
dim(L1→N
For(K,N,2,-1
randInt(1,K→A
L1(K→B
L1(A→L1(K
B→L1(A
End
```

In Grammer, it is just about as easy. You need to first initialize your deck with something like:
```
.Assume Z points to the deck of 52 cards (52 bytes)

For K,0,51
WriteB(Z+K,K
End
```

Then every time you want to shuffle, just call (assuming `Z` still points to the deck):

```
.SHUFFLE
51→K
While K>0
randInt(0,K→A
(Z+K→B
WriteB(Z+K,(Z+A
WriteB(Z+A,B
K-1→K
End
End
```
