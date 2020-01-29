<style>
a{
  text-decoration: none;
  font-weight: bold;
  border-bottom: 1px dotted gray;
  color: black;
}
</style>
# Table of Contents<!-- MDTOC maxdepth:6 firsth1:1 numbering:0 flatten:0 bullets:1 updateOnSave:1 -->

- [Overview](#overview)   
   - [Get(](#get)   
      - [Notes](#notes)   
      - [Examples](#examples)   
   - [length(](#length)   
      - [Notes](#notes)   
      - [Examples](#examples)   
   - [Send(](#send)   
      - [Notes and Errors](#notes-and-errors)   
   - [Unarchive](#unarchive)   
   - [Archive](#archive)   
   - [Delvar](#delvar)   
- [Appvars and Programs](#appvars-and-programs)   
- [Picture Vars](#picture-vars)   
- [OS Strings](#os-strings)   
- [OS Real Vars](#os-real-vars)   

<!-- /MDTOC -->

# Overview
If you want to store data for long-term use, such as player data or high scores,
you will need to know how to create, find, and store data to variables. Appvars
provide the most versatile storage means, while OS strings, picture vars, and
Real vars have some specialized commands.

## Get(
To get a pointer to a variable's data, use the `Get(` command, located at
`[prgm][right][up][up]`. If you are using the Grammer token hook, this is
renamed to `FindVar(`.

The syntax is `Get("varname"`. This returns a pointer to the data in `Ans`, or 0
if it doesn't exist. If the pointer is less than 32768, then it is archived.

### Notes
- The flash page is returned in `Ɵ'`, though it really isn't useful in Grammer.
- `"varname"` needs to contain a type prefix. See [Data Types](datatypes.md) for
  more info.

### Examples
Look for appvar MyVar, and:
- If it doesn't exist, draw "NOT FOUND"
- If it exists, but is archived, draw "ARCHIVED"
- If it exists in RAM, draw the first 10 chars

Note that the prefix for appvars can be `5` or `U`. I'll use `5`.

```
:.0:Return
:Get("5MyVar→Z
:If !Z
:Then
:Text(0,0,"NOT FOUND
:Else
:If Z<32768
:Then
:Text(0,0,"ARCHIVED
:Else
:Text(0,0,Z,10
:End
:End
:Dispgraph
:Stop
```

## length(
`length(` was intended to get the size of a variable, but it is probably more
useful than `Get(`. It takes the same arguments, but it returns the size in
`Ans`, and the pointer in `Ɵ'`. However, size is returned as `-1` (65535) if it
doesn't exist.

### Notes
- If the var doesn't exist, the pointer in `Ɵ'` will NOT be 0. You have to check
  the size.

### Examples
Look for appvar MyVar, and:
- If it doesn't exist, draw "NOT FOUND"
- if it exists, draw the size
- If it exists, but is archived, draw "ARCHIVED"
- If it exists in RAM, draw "UNARCHIVED"

Note that the prefix for appvars can be `5` or `U`. I'll use `5`. As well, I use
the 32-bit store described in the
[Basic Operations](../readme.md#basic-operations) section. This will put the
pointer in `Z` and size in `Ɵ`

```
:.0:Return
:length("5MyVar→ZƟ
:If Ɵ=-1
:Then
:Text(0,0,"NOT FOUND
:Else
:Text('0,0,Ɵ
:If Z<32768
:Then
:Text(6,0,"ARCHIVED
:Else
:Text(6,0,"UNARCHIVED
:End
:End
:Dispgraph
:Stop
```

## Send(
To create a variable, use the `Send(` command, located at `[prgm][right][up]`.
If you are using the Grammer token hook, this is renamed to `MakeVar(`.

The syntax is `Send(#,"varname"`. This returns a pointer to the data

### Notes
- `"varname"` needs to contain a type prefix. See [Data Types](datatypes.md) for
  more info.
- When the data is newly created, it is filled with null bytes.
- If the var already exists, it will not be overwritten.
  **This also means it won't be resized if needed!**
  - If the var already exists as the wrong size, you might cause a crash when
    you write to it. Always check the variable info with the [Get(](#get) or
    [length(](#length) commands!

### Examples
So as an example, suppose we want to create an AppVar of 100 bytes called
"MyVar". The prefix for appvars can be `5` or `U`, and I'll use `5`:

```
.0:Return
:Send(100,"5MyVar
:Stop
```

## Unarchive
## Archive
## Delvar

# Appvars and Programs

# Picture Vars

# OS Strings

# OS Real Vars
