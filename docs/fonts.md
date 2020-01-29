# Fonts
Grammer has two built-in fonts, and currently supports three kinds of font.

## Default 4x6
The default font is a 4x6 fixed-width font. Each character is packed into
3 bytes, making the entire font set (256 chars) 768 bytes. If you would like to
create your own font in this format, you can use DrDnar's
[Monochrome Font Editor](https://github.com/drdnar/MFE/releases).

I recommend loading Grammer's [fixed font file](../../src/gramfont_fix.mfefont)
as a template.

If you are making a font from scratch, I recommend using these settings in MFE:
- `Windows>Chart` to display the chart
- `Windows>Font Properties` to open font properties
  - Set `Height` to 6
  - Deselect the `Data Width Multiple of 8` option
  - Deselect the `Variable Width` option
  - Set `Data Width` to 4
  - Set `Width` to 4


When you are ready to export the font data, Go to `Windows>Export` and select
`Xeda's Format #1`. Then save it and MFE generates a `.asm` file with the right
format for the font data. You can then compiled it with something like spasm
to an appvar:
```
  spasm myfont.asm myfont.8xv
```

Send `myfont.8xv` to your calc, and now you can use it in Grammer :)


## Variable Font
Grammer also has a built-in variable-width font that is 7 pixels tall. It is
basically a large font that looks better than the OS large font. This format
is set up so that the first byte is the height for the entire font, followed by
all of the char data. Each char is prefixed with a width byte (width in pixels)
followed by data. Each row of pixels is padded to a multiple of 8 bits. So say a
char is 5 pixels wide. Then each row is 8 bits (1 byte), with the bottom 3 bits
being 0.

(Yes, you can have very large fonts.)

As with the fixed-width font, you can use DrDnar's
[Monochrome Font Editor](https://github.com/drdnar/MFE/releases).

I recommend loading Grammer's
[variable font file](../../src/gramfont_var.mfefont) as a template.

If you are making a font from scratch, I recommend using these settings in MFE:
- `Windows>Chart` to display the chart
- `Windows>Font Properties` to open font properties
  - Set `Height` to your font height (you choose)
  - **Select** the `Variable Width` option


When you are ready to export the font data, Go to `Windows>Export` and select
`Xeda's Format #2`. Then save it and MFE generates a `.asm` file with the right
format for the font data. You can then compiled it with something like spasm
to an appvar:
```
  spasm myfont.asm myfont.8xv
```

Send `myfont.8xv` to your calc, and now you can use it in Grammer :)

## Omnicalc and Batlib Fonts
Omnicalc fonts are used by Omnicalc and (Batlib) to replace the OS large font.
These are 5x7 fonts, so each char takes 7 bytes. Omnicalc fonts have a special
header, which is why the Grammer docs say they need an offset of 11 bytes.
Batlib fonts don't have a header, so you don't need to offset. You can use
DrDnar's font editor to create your font, or download from a multitude of
available fonts from TICalc.org. If you use DrDnar's MFE, I think it exports
directly to an appvar or program file.
