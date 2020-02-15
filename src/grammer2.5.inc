;===============================================================================
; Useful TI-OS Equates
;===============================================================================
#define bcall(x) rst 28h \ .dw x
#define rMov9ToOP1    20h
#define rFindSym    10h

_FindAlphaDn    = 4A47h
_FindAlphaUp    = 4A44h
_RclAns         = 4AD7h
_ChkFindSym     = 42F1h
_DispHL         = 4507h
_CreateTempStr  = 4324h
_SetParserHook  = 5026h
_CreateVar      = 4E70h
_CreateAppVar   = 4E6Ah
_CreatePict     = 4333h
_EnoughMem      = 42FDh
_InsertMem      = 42F7h
_Get_Tok_Strng  = 4594h
_DelMem         = 4357h
_JForceCmdNoChar= 4027h
_JError         = 44D7h
_DelVarArc      = 4FC6h
_CreateStrng    = 4327h
_CreateReal     = 430Fh
_SetXXXXOP2     = 4792h
_Arc_Unarc      = 4FD8h
_ConvKeyToTok   = 4A02h
_GetKeyRetOff   = 500Bh
_RunIndicOff    = 4570h
_DeleteTempPrograms = 5041h
_MemChk         = 42E5h
_clrTxtShd      = 454Ch
_saveCmdShadow  = 4573h
_PutS           = 450Ah
_OP5ToOP1       = 413Bh
_OP1ToOP5       = 4153h
_VPutMap        = 455Eh
_Load_LFontV    = 806Fh
_SFont_Len      = 4786h
appErr1         = 984Dh
appErr2         = 985Ah
cxErrorEP       = 8595h
curRow          = 844Bh
curCol          = 844Ch
kbdScanCode     = 843Fh
basic_prog      = 9652h
progStart       = 965Bh
parsePtr        = 965Dh
progEnd         = 965Fh
parserHookPtr   = 9BACh
tokenHookPtr    = 9BC8h
OP1             = 8478h
OP2             = 8483h
OP3             = 848Eh
OP4             = 8499h
OP5             = 84A4h
OP6             = 84AFh
flags           = 89F0h
saveSScreen     = 86ECh
textShadow      = 8508h
plotSScreen     = 9340h
progPtr         = 9830h
FPS             = 9824h
OPS             = 9828h
smallEditRAM    = 90D3h  ;108 bytes
iMathPtr1       = 84D3h  ;10 bytes
iMathPtr2       = 84D5h
iMathPtr3       = 84D7h
iMathPtr4       = 84D9h
iMathPtr5       = 84DBh
asm_data_ptr1   = 84EBh
asm_data_ptr2   = 84EDh
cmdShadow       = 966Eh  ;128 bytes
pTemp           = 982Eh  ;bottom of named vars VAT
appBackUpScreen = 9872h
ramCode         = 8100h
tempSwapArea    = 82A5h
penCol          = 86D7h
penRow          = 86D8h
lFont_record    = 845Ah

;==============================
;Flags
;==============================
CursorFlags     = 12
CursorActive    =   3

onFlags         = 9        ;on key flags
onInterrupt     =   4      ;1=on key interrupt request

curFlags        = 12       ;Cursor
fmtEdit         =   0      ;1=format number for editing
curAble         =   2      ;1=cursor flash is enabled
curOn           =   3      ;1=cursor is showing
curLock         =   4      ;1=cursor is locked off
cmdVirgin       =   5      ;1=nothing has been typed in cmd bfr
;----------------------------------------------------------------------
indicFlags        = 18         ;Indicator flags
indicRun          =   0        ;1=run indicator ON
shiftFlags        = 18         ;[2nd] and [ALPHA] flags
shift2nd          =   3        ;1=[2nd] has been pressed
shiftAlpha        =   4        ;1=[ALPHA] has been pressed
shiftLwrAlph      =   5        ;1=lower case, 0=upper case
shiftALock        =   6        ;1=alpha lock has been pressed
shiftKeepAlph     =   7        ;1=cannot cancel alpha shift

sGrFlags          = 14h
textWrite         = 7

fontFlags         = 32h
fracDrawLFont     = 2

hookflags3        = 35h
tokenHookActive   = 0		;1 = token hook active
fontHookActive    = 5		;1 = font hook active
hookflags4        = 36h ;also sysHookFlag2
parserHookActive  = 1		;1 = parser hook active

appLwrCaseFlag    = 24h
lwrCaseActive     = 3

;This is used in gvardata
tokenhook_optout  = 0
;===============================================================================



;===============================================================================
; Grammer Equates
;===============================================================================
#define MODULE_VERSION 3
moduleExec      = saveSScreen
gbuf            = plotSScreen
pvars           = smallEditRAM
ThetaPrimeVar   = pvars+106
TempWord1   = OP6-1       ;2       2
TempWord2   = TempWord1+2 ;2       4
TempWord3   = TempWord2+2 ;2       6
TempWord4   = TempWord3+2 ;2       8
TempWord5   = TempWord4+2 ;2      10
textRow     = TempWord5+2 ;1      11
textCol     = textRow+1   ;1      12

g_ram       = 8020h

FS_begin  = iMathPtr4
FS_end    = FS_begin+2

BufPtr      = g_ram        ;2
GrayBufPtr  = BufPtr+2     ;2
gbuf_temp   = GrayBufPtr+2 ;2
FontPointer = gbuf_temp+2  ;2
font_ptr_page=FontPointer+2;1
g_internal  = font_ptr_page+1
Ans         = appErr2      ;2


;==============================
; Grammer Flags
;==============================
InternalFlag    = 33
SlowTextFlag    =   0
IntActiveFlag   =   1
FactorialFlag   =   2
errorChecking   =   3
grayFlag        =   4   ;this determines the checker pattern for the next gray object drawn
bit32           =   5   ;This determines if the output was 32-bit or not
Mod2nd          =   6
nogrampkg       =   7   ;This determines the checker pattern for grayscale mode

UserFlags       = 34
InvertTextFlag  =   0
InvertLCDFlag   =   1
OnBlockFlag     =   2
baseInput       =   3
pxlBoundsRes    =   4
SignedText      =   5
;    =   6
;    =   7

ParticleFlag    = 35
Xis0            = 0
Xis95           = 1
Yis0            = 2
Yis63           = 3
OffScrn         = 4

InternalFlag2   = 35
inputflag       = 0

ModeFlags2      = 35
floatmode       = 5

textmode_default  = 0
textmode_varwidth = 1
textmode_smallfixed=2
textmode_Omnicalc = 3
textmode_OS_small = 4
textmode_OS_large = 5


FS_uint8        = 0
FS_str          = 3
FS_array        = 4
;===============================================================================
; Grammer Jump Table
;===============================================================================
#ifndef NO_JUMP_TABLE
cmdJmp              = $4023
ProgramAccessStart  = $4026
CompatCall          = $4029
SelectedProg        = $402C
ExecOP1             = $402F
ParseFullArg        = $4032
ParseNextFullArg    = $4035
ParseNextFullArg_Inc= $4038
ParseCondition      = $403B
DrawRectToGraph     = $403E
GraphToLCD          = $4041
VPutSC              = $4044
GetKey              = $4047
GetGrammerText      = $404A
GetGrammerText_DE   = $404D
GetGrammerStr       = $4050
GetKeyDebounce      = $4053
SearchString        = $4056
FS_createvar_max    = $4059
FS_delvar           = $405C
FS_resize           = $405F
FS_findvar          = $4062
ErrMem              = $4065
#endif