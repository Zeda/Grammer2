<h1>Table of Contents</h1>

<!-- MDTOC maxdepth:6 firsth1:2 numbering:0 flatten:0 bullets:1 updateOnSave:1 -->

- [Math](#math)   
- [Floating Point](#floating-point)   
- [Number System](#number-system)   
- [Binary Lesson](#binary-lesson)   
   - [Converting from Dec to Hex](#converting-from-dec-to-hex)   
   - [Converting from Hex to Dec](#converting-from-hex-to-dec)   
   - [Binary.](#binary)   
   - [Octal.](#octal)   
   - [Other Bases](#other-bases)  

<!-- /MDTOC -->

# Grammer Math

Grammer uses 16-bit math. If you are not familiar with what this means, please look at the [Number System](#number-system) section.

Much of Grammer is numbers and math. For example, when you do something like `"HELLO WORLD→A`, this isn't storing the string anywhere, it is actually storing the location of the string as a 16-bit number. If you don't know what pointers are, you should read the [Pointers](readme.md#pointers) section.

## Math

Grammer math is very different from the math that you are used to. The main
points are:
* Math is done right to left
* All functions in Grammer are math.

For the first point, let's look at an example of the math string 3+9/58-3\*14+2\*2:
```
3+9/58-3*14+2*2
3+9/58-3*14+4
3+9/58-3*18
3+9/58-54
3+9/4
3+2
5
```
Parentheses are not part of Grammer math, but to give you you can use a space or use a colon between chunks of math to compute
each chunk in order. In most situations, you should use a colon. So say you want to
do ((3+4)*(6+3))/6. You have 3 chunks that you can compute in order:
```
3+4:*6+3:/6
7:*6+3:/6
7*6+3:/6
7*9:/6
63:/6
63/6
10
```
Pretty cool, right? That is actually even more optimized than using parentheses! Now, if you are like me, you might not like the look of that missing remainder of 3 in that division. 63/6 is 10.5, not 10, but Grammer truncates the results. However, a system variable called θ' will contain the remainder after division and other such extra information after math.

Here are the math operations currently available.

| Example | Token | Grammer | Description                                      |
|:------- |:----- |:------- |:------------------------------------------------ |
| a+b     | +     | +       | Adds two numbers. If there is overflow, θ'=1, else it is 0.|
| a-b     | -     | -       | Subtracts two numbers. If there is overflow, θ'=65535, else it is zero |
| a*b     | *     | *       | Multiplies two numbers. Overflow is stored in θ' |
| a/b     | /     | /       | Divides two numbers. The remainder is stored in θ'. |
| a/ b    | `/ `  | `/ `    | Divides two __signed__ numbers. Ex. `65533/ 65535` returns `3` since this is equivalent to `-3/-1`. |
| a<sup>2</sup> | <sup>2</sup> | <sup>2</sup> | This squares a number. Overflow is stored in θ'. |
| -a      | (-)   | (-)     | Negates a number. |
| min(a,b | min(  | min(    | Returns the minimum of two numbers. |
| max(a,b | max(  | max(    | Returns the maximum of two numbers. |
| sin(a   | sin(  | sin(    | This returns the sine of a number as a value between -128 and 127. The period is 256, not 360. For example, sin(32) is like sin(45) in normal math. If you need help, take the actual sin(45) and multiply by 128. Rounded, this is 91. So, sin(32)=91. |
| cos(a   | cos(  | cos(    | This calculates cosine. See notes on sine. |
| tan<sup>-1</sup>(a[,b   | tan<sup>-1</sup>(  | tan<sup>-1</sup>(    | This calculates arctangent such that `arctan(sin(x),cos(x))=x` using Grammer's integer trig. |
| e^(a    | e^(   | e^(     | Computes a power of 2. |
| gcd(a,b | gcd(  | gcd(    | Returns the greatest common divisor of two numbers. |
| lcm(a,b | lcm(  | lcm(    | Returns the least common multiple of two numbers. |
| a▶Frac  | ▶Frac | ▶lFactor | θ' contains the smallest factor of the number. Output is a divided by that number. For example, 96▶Frac will output 48 with θ'=2. You can use this to test primality. |
| √(a     | √(    | √(a     | Returns the square root of the number, rounded down. θ' contains a remainder. |
| √('a    | √('   | √('     | Returns the square root rounded to the nearest integer. |
| abs(a   | abs(  | abs(    | Returns the absolute value of a number. If a>32767, it is treated as negative. |
| rand    | rand  | rand    | Returns a random integer between 0 and 65535. |
| randInt(a,b | randInt( | randInt( | Returns a random integer between `a` and `b-1`. |
| ~~a nCr b~~ | ~~nCr~~ | ~~nCr~~ | ~~Returns `a` choose `b`. In mathematics, this is typically seen as n!/((n-r)!r!). I had to invent an algorithm for this to avoid factorials because otherwise, you could not do anything like 9 nCr 7 (9!>65535).~~|
| !a      | !     | !       | If the following expression results in 0, this returns 1, else it returns 0. |
| a and b | and   | and     | Computes bit-wise AND of two values. Remember the [Binary Lesson](binary-lesson.md) ? |
| a or b  | or    | or      | Computes bit-wise OR of two values. |
| a xor b | xor   | xor     | Computes bit-wise XOR of two values. |
| not(a   | not(  | not(    | Inverts the bits of a number. |
| a=b     | =     | =       | If a and b are equal, this returns 1, else it returns 0. |
| a≠b     | ≠     | ≠       | If a and b are not equal, this returns 1, else it returns 0. |
| a>b     | >     | >       | If a is greater than b, this returns 1, else it returns 0. |
| a≥b     | ≥     | ≥       | If a is greater than or equal to b, this returns 1, else it returns 0. |
| a<b     | <     | <       | If a is less than b, this returns 1, else it returns 0. |
| a≤b     | ≤     | ≤       | If a is less than or equal to b, this returns 1, else it returns 0. |

## Floating Point
As of version 2.50.1.0, Grammer is beginning to have support for floating point numbers. Grammer was originally only intended to have 16-bit integer math support. As a consequence, many useful tokens were already in use, making float support convoluted. I want to reinforce this idea, though: Grammer is a 16-bit integer-centric language.

You will have to interface with floats via pointers. Internally, there is a special floating-point storage that holds a few elements for intermediate processing. If this storage gets full, it wraps around and starts overwriting old items. In particular, this can happen in expressions with many operations. For example, `3.14159+.6.789` will overwrite three values-- two for the numbers 3.14159, 6.789, and one for the sum. At the time of this writing, it can hold 8 floats. In the future this might change, but if you need long-term storage, you will need to copy the 4-byte float to somewhere safe. With that in mind, Grammer now supports a special-purpose move operator `→.` that takes a pointer on the left side, `x` and a pointer *var* on the right side, `Y` and copies the 4 bytes at `x` to the memory at `Y`. Floats must start with a number: `.367` will be interpreted as a comment/label (float support was added on top of the existing Grammer framework), whereas `0.367` is interpreted as a float, and returns a pointer to its converted value.

In general, float commands are signified by an operations followed by a `.`. As of this writing, there are a handful of known bugs, so don't count on this for your math homework yet!

| Example | Token | Grammer | Description                                      |
|:------- |:----- |:------- |:------------------------------------------------ |
| e       | e     |         | Returns approximately 2.718282 (Euler's number) |
| π       | π     |         | Returns approximately 3.141596 (pi). If a hexadecimal digit follows, it will instead return the value for the hexadecimal string. |
| A→.B    | →.    | →.      | Stores the 4 bytes at ptr A to ptr B             |
| A+.B    | +.    | +.      | Adds the floats at A and B, returns a pointer.   |
| A-.B    | -.    | -.      | Subtracts the floats at A and B, returns a pointer. |
| mean(.A,B | mean(. |      | Computes the mean of A and B                     |
| A*.B    | *.    | *.      | Multiplies the floats at A and B, returns a pointer. |
| A/.B    | /.    | /.      | Divides the floats at A and B, returns a pointer. |
| √(.B    | √(.   | √(.     | Computes the square root of the float at A, returns a pointer. |
| e^(.A   | e^(.  |         | Returns e^A. |
| 10^(.A  | 10^(. |         | Returns 10^A. |
| A^.B    | ^.    | ^.      | Returns A^B |
| abs(.A  | abs(. |         | Returns the absolute value of the float. |
| -.A     | (-)   |         | Returns the negative of the float. This is the negative token, not minus. |
| sin(.A  | sin(. |         | Returns the sine of A (in radians).
| cos(.A  | cos(. |         | Returns the cosine of A (in radians).
| tan(.A  | tan(. |         | Returns the tangent of A (in radians).
| sinh(.A  | sinh(. |       | Returns the hyperbolic sine of A.
| cosh(.A  | cosh(. |       | Returns the hyperbolic cosine of A.
| tanh(.A  | tanh(. |       | Returns the hyperbolic tangent of A.
| sin<sup>-1</sup>(.A  | sin<sup>-1</sup>(. |         | Returns the arcsine of A (in radians).
| cos<sup>-1</sup>(.A  | cos<sup>-1</sup>(. |         | Returns the arccosine of A (in radians).
| tan<sup>-1</sup>(.A  | tan<sup>-1</sup>(. |         | Returns the arctangent of A (in radians).
| sinh<sup>-1</sup>(.A  | sinh<sup>-1</sup>(. |       | Returns the hyperbolic arcsine of A.
| cosh<sup>-1</sup>(.A  | cosh<sup>-1</sup>(. |       | Returns the hyperbolic arccosine of A.
| tanh<sup>-1</sup>(.A  | tanh<sup>-1</sup>(. |       | Returns the hyperbolic arctangent of A.
| log(.A[,B  | log(. |      | `log(.A` returns the base-10 logarithm.  `log(.A,B` returns the base-B logarithm of A.
| rand.   | rand. |         | Returns a random number on [0,1) |
| A▶Dec   | ▶Dec  | ▶Float  | A is a pointer. This converts the data at the pointer to a float. Can be used on strings, or `Input` for example. |
| Text(x,y,`.`A |      |    | Displays a float located at A. |
| A=.B    | =.    |         | Returns an 1 if float A equals float B, else 0. |
| A≠.B    | =.    |         | Returns an 1 if float A is not equal to float B, else 0. |
| A>.B    | =.    |         | Returns an 1 if float A is greater than float B, else 0. |
| A≥.B    | =.    |         | Returns an 1 if float A is greater than or equal to float B, else 0. |
| A<.B    | =.    |         | Returns an 1 if float A is less than float B, else 0. |
| A≤.B    | =.    |         | Returns an 1 if float A is less than or equal to float B, else 0. |
| int(.A  | int(. |         | Converts  a float to a signed integer. |


Examples. The following two codes produce the same result, but the first one uses temporary storage that may get overwritten later, and the second one copies values to less volatile storage:
```
3.1415926→X     ;Notice it is just storing a pointer, not copying actual data!
1.2345678→Y
Text(0,0,.X+.Y
```

```
G-T'→X+4→Y      ;Instead of grayscale graphics, we'll use the back buffer as safe storage. No grayscale quadratic formula program here, apparently.
3.1415926→.X    ;Now we are copying the float from temp storage to safe storage
1.2345678→.Y
Text(0,0,.X+.Y
```

## Number System
Grammer's number system works like this: Numbers are integers 0 to 65535. This means no fractions, or decimals, though are a few commands that handle larger numbers.

Let's look at this closer. First, why 65535? That is easy to answer. Grammer
uses 16-bit math. In binary, the numbers are 0000000000000000b to
1111111111111111b. Convert that to decimal (our number system) and you get 0 to 65535. If you don't understand binary or hexadecimal, see the [Binary Lesson](#binary-lesson)
section below. Understanding binary and hex is not necessary, but it will help you
understand why certain commands act the way they do. Plus, it can help you figure
out some advanced tricks.

Now, let's look at some scenarios. If you overflow and add 1 to 65535, it
loops back to 0. Similarly, if you subtract 1 from 0, you loop back to 65535.
Then you can see that 65530+11=5. You also now know that -1=65535. So what happens
if you multiply 11\*65535? Believe it or not, you will get -11 which is 65536-
11=65525.(If you ever want to go into more advanced math in college, hold on to
this info for when you get into Abstract Algebra. You are working with the ring
**Z**<sub>2<sup>16</sup></sub>).


# Binary Lesson

This document was designed to explain the basics of Decimal (our number system),
Hexadecimal (base16, the ASM number system), and binary (machine code, 0's and
1's). Again, this is going to be very basic. Check the internet if you want to
learn more.

## Converting from Dec to Hex
1. Divide the number by 16. The remainder is the first number. If it is 0 to 9,
just keep that. If it is 10 to 15, use letters A to F.

2. If the number is 16 or larger, still, divide by 16.
3. Repeat step 1 and 2 until finished.

Here is an example of 32173 converted to Hex:
```
32173/16= 2010 13/16  Remainder=13 “D”
2010/16= 125 10/16    Remainder=10 “A”
125/16= 7 13/16       Remainder=13 “D”
7/16= 7/16            Remainder=7  “7”
```
So the number is 7DADh

## Converting from Hex to Dec
I will start this with an example of 731h:
```
1*16^0 = 1
3*16^1 = 48
7*16^2 = 1792
```
Add them all up to get 1841. Did you see the pattern with the 16<sup>n</sup>?

## Binary.
Converting to and from binary is pretty similar. Just replace all the 16's with 2's
and you will have it.

## Octal.
Replace all the 16's with 8's.

## Other Bases
Replace the 16's with whatever number you want.

Here is some cool knowledge for spriting. Each four binary digits represents one
hexadecimal digit. For example:
`00110101` corresponds to `35` in hexadecimal. This makes it super easy to convert a sprite which is
binary to hexadecimal! You only need the first 16 digits, so here you go:
```
0000 = 0 0100 = 4 1000 = 8 1100 = C
0001 = 1 0101 = 5 1001 = 9 1101 = D
0010 = 2 0110 = 6 1010 = A 1110 = E
0011 = 3 0111 = 7 1011 = B 1111 = F
```

Division, unfortunately is not as nice as multiplication, addition, or
subtraction. 3/-1 will give you 0 because it is 3/65535.
