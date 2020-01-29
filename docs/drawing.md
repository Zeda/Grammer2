<h1>Table of Contents</h1>

<!-- MDTOC maxdepth:6 firsth1:2 numbering:0 flatten:0 bullets:1 updateOnSave:1 -->

- [Graphics Buffers](#graphics-buffers)   
- [Grayscale](#grayscale)   
- [Sprites](#sprites)   
   - [Sprite Data](#sprite-data)   
   - [Sprite Logic](#sprite-logic)   
   - [Displaying Sprites](#displaying-sprites)   

<!-- /MDTOC -->
# Drawing

Drawing in Grammer has a few similarities to TI-BASIC, but not many. In Grammer, you'll need a lower-level understanding of graphics, and that is what we'll aim to teach here. To understand, a primary difference is that Grammer uses pixel coordinates, like the BASIC `Pxl-*` commands.

The first thing you need to know is that drawing is done on "graphics buffers" before it is displayed on the LCD. This is true for both BASIC and Grammer. The difference is that in Grammer you have to manually issue a command to draw from the buffer to the LCD, and in BASIC it is automatic. This may sound annoying, but it's actually great because it lets you perform batch drawing operations before displaying. It makes for much smoother and faster graphics. We'll discuss buffers in more detail later, but for now here is an example.

Now, to the actual drawing!
In all cases, (0,0) is the upper left corner of the screen.

```
:.0:Return
:ClrDraw
:Repeat getKey(15     ;Loop until [Clear] is pressed.
:randInt(0,96→X
:randInt(0,64→Y
:randInt(0,64→R
:Circle(Y,X,R,1       ;Draws a circle with a black outline with radius R, centered at (Y,X)
:DispGraph            ;Now that we've drawn to the buffer, display it to the LCD
:End
:Stop
```
![Animated Circle Example](https://i.imgur.com/JGllOAw.gif)

## Graphics Buffers

Graphics buffers are 768 byte areas of memory (normally RAM) that store pixel data.
Pixel data is not shown on the LCD until you issue a `DispGraph` command. This means you can modify it however you like before showing the contents. For those who want to do *really* low level modifications, these buffers are stored such that each byte represents 8 pixels, where bit 7 corresponds to the left-most bit, and each twelve bytes forms a 96-pixel row, starting from the top of the screen.

There are various reasons one might want to draw to some other buffer, or display some other buffer (especially in grayscale drawing). Grammer reserves two buffers for graphics, the primary being the graphscreen buffer used by the OS, located at `0x9340`. The other is what is called `AppBackUpScreen` located at `0x9872`. You don't have to memorize these addresses, you can use `G-T` and `G-T'`, respectively.

Most graphics routines allow you to provide an optional argument designating a graphics buffer to draw to. However, you can also set a default buffer with the `Disp ` function. For example, `Disp π9872` or `Disp G-T'`.
Now, whenever you draw or update the LCD, that is the buffer that will be
used. This means you can preserve the graph screen.

## Grayscale
Grammer has built-in grayscale support. Since the calculator is monochrome, this means alternating colors at the right frequency to achieve a gray-looking pixel. Knowing how buffers work, you can give this a try. First, you need two buffers-- a back buffer and a front buffer. Define these using `Disp °` and `Disp '`, respectively (both found in the Angle menu). For example, to add the back buffer, use `Disp °π9872` and now whenever you use `DispGraph`, it will update one cycle of gray. Because the LCD does not support grayscale naturally, you will need to update the LCD often and regularly.

A pixel is seen as gray if it is ON in one of the buffers, but OFF in the other
buffer. If a pixel is on in the front buffer, it will appear darker. Here is
an example program that draws in grayscale:
```
:.0:
:G-T'→Z      ;G-T' is the pointer to 9872h, appBackUpScreen
:Disp °Z
:ClrDraw
:ClrDrawZ
:0→X→Y
:Repeat getKey(15
:Pxl-Change(Y,X       ;Just drawing the cursor
:Pxl-Change(Y,X,Z     ;Pixel changing it on both buffers
:DispGraph
:Pxl-Change(Y,X
:Pxl-Change(Y,X,Z
:If getKey(54
:Pxl-On(Y,X,Z
:If getKey(9
:Pxl-On(Y,X
:If getKey(54:+getKey(56  ;If [2nd] or [Del]
:Pxl-Off(Y,X
:If getKey(9:+getkey(56   ;If [Enter] or [Del]
:Pxl-Off(Y,X,Z
:X+getKey(3:-getKey(2
:If <96
:→X
:Y+getKey(1
:-getKey(4:If <64
:→Y
:End
:Stop
```

## Sprites
Using sprites is a pretty advanced technique, so don't expect to understand everything here. Sprites are pretty much mini pictures. They are a quick way to get detailed objects that move around making them a powerful graphics tool. In Grammer, the main sprite commands are `Pt-On(` and `Pt-Off(` and both have differences and advantages over the other.

### Sprite Data

Sprite data is in the form of bytes or hexadecimal and you will want to understand
binary to hex conversions for this. For example, to draw an 8x8 circle, all the
pixels on should be a 1 in binary and each row needs to be converted to hex:
```
0 0 1 1 1 1 0 0 =3C
0 1 0 0 0 0 1 0 =42
1 0 0 0 0 0 0 1 =81
1 0 0 0 0 0 0 1 =81
1 0 0 0 0 0 0 1 =81
1 0 0 0 0 0 0 1 =81
0 1 0 0 0 0 1 0 =42
0 0 1 1 1 1 0 0 =3C
```
So the data would be `3C4281818181423C` in hexadecimal.

### Sprite Logic
There are 5 forms of sprite logic offered by Grammer, currently. These tell how
the sprite should be drawn and can all be useful in different situations.

* Overwrite
  * For an 8x8 sprite, this will erase the 8x8 area on the screen and draw the sprite.

* AND
  * This leaves the pixel on the screen on if and only if the sprites pixel is on and the pixel on the screen is on.

* OR
  * This will turn a pixel on on the screen if it is already on or the sprite has the pixel on. This never erases pixels.

* XOR
  * If the sprites pixel is the same state as the one on the screen, the pixel is turned off, otherwise, it is turned on. For example, if both pixels are on, the result is off.

* Erase
  * Any pixels that are on in the sprite are erased on screen. The pixels that are off in the sprite do not affect the pixels on the graph buffer.

### Displaying Sprites
`Pt-On(` is used to display sprites as tiles. This means it displays the sprite very quickly, but you can only draw to 12 columns.

`Pt-Off(` is a slightly slower sprite routine, but it allows you to draw the sprite to pixel coordinates.
