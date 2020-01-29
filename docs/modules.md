<h1>Table of Contents</h1>

<!-- MDTOC maxdepth:6 firsth1:1 numbering:0 flatten:0 bullets:1 updateOnSave:1 -->

   - [Modules](#modules)   
   - [Grammer Routines](#grammer-routines)   

<!-- /MDTOC -->

## Modules

Modules help to extend the Grammer language. Unfortunately, there is a lot of overhead involved, so locating and loading routines is rather slow. As such, I recommend modules where speed isn't critical. Where it is, you can still use assembly programs and hex codes.

Here is the format of a module:
```
;All routines must be 768 bytes or less
;They get copied to moduleExec
#include "grammer2.5.inc"
  .db "Gram"         ;Magic number
  .dw MODULE_VERSION ;Minimum module version. Uses the current version.
  .dw TableSize      ;Number of elements on the table
  .dw func0
  .dw func1
  ...
.org 0               ;Set the code counter to 0 here

func0: .db "MYFUNC0",$10  \ .dw size_of_func0_code
  ;func0
  ;code

func1: .db "MYFUNC1",$10  \ .dw size_of_func1_code
  ;func1
  ;code

```

Here is the template that I use:
```
;All routines must be 768 bytes or less
;They get copied to moduleExec
#include "grammer2.5.inc"
  .db "Gram"            ;magic number
  .dw MODULE_VERSION    ;minimum version
  .dw (mod_start-2-$)/2 ;num elements
  .dw func0-mod_start   ;offset to func0
  .dw func1-mod_start   ;offset to func1
  .dw func2-mod_start   ;
  ...
  .dw funcn-mod_start   ;offset to funcn
mod_start:

func0: .db "func0",$10 \ .dw func1-$-2
    ;<<code>>

func1: .db "func1",$10 \ .dw func2-$-2
    ;<<code>>

func2:
;...

funcn: .db "funcn",$10 \ .dw mod_end-$-2
    ;<<code>>

mod_end:
```

There is already a lot of overhead with module look-up and loading, so to
minimize lookup time a little, Grammer uses binary search to locate functions.
As a consequence, the table needs to be sorted by their strings. For example, if
func0 is called "XXX" and func1 is called "AAA", then the table should have
`.dw func1` before `.dw func0`.

Another issue to take into account is that the code is copied to `moduleExec`.
At this time, this limits your code to 768 bytes, and also jumps and calls need
to be relocated if they occur in your code. *This does* **not** *apply to `jr`
instructions as these jump a relative distance.*

So for example, let's look at this super complicated piece of code and make it even more complicated:
```
func0: .db "XXX",$10 .dw func0_end-func0_start
func0_start:
  call label
  ret
label:
  ret
func0_end:
```
That call will almost certainly crash. Instead, you need:
```
func0: .db "XXX",$10 .dw funco_end-func0_start
func0_start:
  call moduleExec+label-func0_start
  ret
label:
  ret
func0_end:
```
Again, this only applies to `jp` and `call` instructions, and only those for routines within the code. You can still make calls to Grammer routines without all the `moduleExec+` stuff.

One final note before we get to Grammer routines: the function names must be terminated by a `0` byte, a space token (`$29`), or an open parentheses (`$10`).

## Grammer Routines

To use the parser and some of the more useful routines, you can use Grammer's
jump table. **NOTE:** *This jump table might change in the future, which is why
the `minimum module version` field is necessary.*

You can use [`grammer2.5.inc`](grammer2.5.inc) for all the equates, available to
modules.

First, it is important to note that any routines that invoke the parser expect
BC to hold the "ans" value.

| call                | description | example  |
|:------------------- |:----------- |:-------- |
| cmdJmp              | `A` is holds the first byte of the token to evaluate, `(parsePtr)` points to the next byte to parse | Suppose your function mimics `sin(`, given `$C2` is the `sin(` token: `ld a,$C2 \ jp cmdJmp` |
| ~~ProgramAccessStart~~ | ~~This takes a string in the OS Ans variable as the name of a var. The var is then executed as a Grammer program.~~ | ~~`jp ProgramAccessStart`~~ |
| CompatCall          | I can't remember. | Sorry. |
| SelectedProg        | Why tf is this in the jump table? | Just why? |
| ExecOP1             | OP1 contains the name of the program to execute as Grammer code. | `ld hl,prog_name \ rst rMov9ToOP1 \ jp ExecOP1` |
| ParseFullArg        | This parses an argument. `BC` is the input, `HL` points to the next byte to parse. **Note:** *Use this to parse the first argument in most cases!* | `call ParseFullArg` |
| ParseNextFullArg    | This parses an argument. `BC` is the input, `HL` points to the next byte to parse. **Note:** *Use this to parse subsequent arguments!* | `call ParseNextFullArg` |
| ParseNextFullArg_Inc | `HL` points to the byte before the code to parse. | `ld hl,my_code \ call ParseNextFullArg_Inc \ ...` |
| ParseCondition      | Use this to parse a condition, as in for `While`, `Repeat`, etc. | `jp ParseCondition` |
| DrawRectToGraph     | See [drawrect.z80](../src/gfx/drawrect.z80) | Draw an inverted rectangle in the upper-left quarter of the screen: `ld a,2 \ ld bc,$0000 \ ld de,$3020 \ call DrawRectToGraph`        |
| GraphToLCD          | This copies the gbuf to the LCD. (BufPtr) and (GrayBufPtr) point to the primary and secondary buffers respectively. | `call GraphToLCD` |
| VPutSC              | `B` is the char to draw, (textrow) and (textcol) are where to draw | Draw an exclamation point at (x,y): `ld hl,$xxyy \ ld b,'!' \ call VPutSC` |
| GetKey              | This reads the current keypress into the `A` register. | `call GetKey` |
| GetGrammerText      | This is used to convert a token string to an ASCII string. `HL` points to the start, returns `BC` is the size, `DE` points to the converted string. | `ld hl,tok_str \ call GetGrammerText` |
| GetGrammerText_DE   | This is used to convert a token string to an ASCII string. **`DE` points to where to output the converted text** `HL` points to the start, returns `BC` is the size, `DE` points to the converted string. | Convert from the string at HL to OP1: `ld hl,tok_str \ ld de,OP1 \ call GetGrammerText_DE` |
| GetGrammerStr       | Gets the size of a token string. HL` points to the string. Returns `BC` as the size, `HL` points to the end of the input string. | `ld hl,tok_str \ call GetGrammerStr` |
| GetKeyDebounce      | This reads a debounced keypress into the `A` register. This is best for things like menus where you don't want key presses to be *too* fast. | `call GetKeyDebounce` |
| SearchString        | Use this to find a substring within a string. See [searchstring.z80](../src/cmd/searchstring.z80) | _ |

If you wanted to make your own addition routine that looked like:
```
$ADD(x,y
```

Your module code would look something like:
```
func_add: .db "ADD",$10 \ .dw nextfunc-$-2

    call ParseFullArg     ;parse the first argument
    push bc               ;Save the result
    call ParseNextFullArg ;parse subsequent arguments
    pop hl        ;pop first arg back into HL
    add hl,bc     ;Second arg in BC. Add the two.
    ld b,h        ;\ Store the result in BC
    ld c,l        ;/
    ret

nextfunc:
```
