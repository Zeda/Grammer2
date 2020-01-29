#define db .db
#define callp(x) call call_previous_page \ .dw x
#define calln(x) call call_next_page \ .dw x

intmask         = %00001011
invlogic        = 2
gflags          = 33
tok_NegRelPtr   = $EE


TextPauseTime=appErr2+4       ;1
StackCount  = TextPauseTime+1 ;2
StackLoc    = StackCount+2    ;2
OutputLogic = StackLoc+2      ;1
ErrorLoc    = OutputLogic+1   ;2
SPSave      = ErrorLoc+2      ;2

parseError  = asm_data_ptr1   ;2
PBufPtr     = 9311h           ;2


IntLoc      = g_internal   ;2
IntCount    = IntLoc+2     ;2  Counts down from IntMax, at zero, executes code at IntLoc, and resets to IntMax
IntMax      = IntCount+2   ;2
PBufType    = IntMax+2     ;1
PBufRule    = PBufType+1   ;2
GrayMask    = PBufRule+2   ;1
graymode    = GrayMask+1   ;1
textmode    = graymode+1   ;1
ForBackUp   = textmode+1   ;2
seed1       = ForBackUp+2  ;2
seed2       = seed1+2      ;2
k_save      = seed2+2
k_count     = k_save+1
k_delay     = k_count+1
qmarkVar    = k_delay+1
ddd         = qmarkVar+2   ;0

VATPtr     = ddd        ; Used during the main menu
VATPtr_next= VATPtr+2   ;
main_menu_cursor    = VATPtr_next+2
main_menu_cursor_max= main_menu_cursor+1
main_menu_index     = main_menu_cursor_max+1
mode_menu_header_RAM= main_menu_index+2
mode_menu_scrap     = mode_menu_header_RAM+5

vars        = ddd                 ;used while compiling
vars_count  = vars+2              ;
size_of_buffer = vars_count+2     ;
start_of_prog = size_of_buffer+2  ;
end_of_src  = start_of_prog+2     ;
data_top    = end_of_src+2        ;
end_of_buffer = data_top+2        ;
buffer_top  = end_of_buffer+2     ;
in_head     = buffer_top+2        ;
out_head    = in_head+2           ;

floatstack_ptr    = vars
floatstack_bottom = vars+2
floatstack_top    = vars+2+32     ;Give room for 8 floats. I am a generous god.
seedsingle0 = floatstack_top
seedsingle1 = seedsingle0+4

stack_base  = seedsingle1+4
stack_top   = stack_base+2
stack_ptr   = stack_top+2

input_base  = stack_ptr+2
input_size  = input_base+2

vfont_index = input_size+2    ;8 bytes


module_count= vfont_index+8
module0     = module_count+1
module1     = module0+2
module2     = module1+2
module3     = module2+2
module4     = module3+2

buf_end     = module4+2
buf_top     = buf_end+2

;tilemap RAM
tilemap_base    = buf_top+2
tilemap_height  = tilemap_base+2
tilemap_width   = tilemap_height+1
sprite_select   = tilemap_width+1
tilemap_buf     = sprite_select+2
tilemap_sy      = tilemap_buf+2
tilemap_y       = tilemap_sy+1
tilemap_sx_mask = tilemap_y+1
tilemap_x       = tilemap_sx_mask+1
tilemap_top     = tilemap_x+2
tilemap_bottom  = tilemap_top+2
tilemap_flags   = tilemap_bottom+2
spritesheet_ptr = tilemap_flags+2

PBuf          = appBackupScreen
SetLinePix    = ramCode
TSA           = tempSwapArea
interruptLoc  = 8A8Ah




#define zlz_vars OP1
#define ZLZ_MIN_RUN 4

zlz_base      = zlz_vars
zlz_runstart  = zlz_vars+2
zlz_match_base= zlz_vars+4
zlz_match_size= zlz_vars+6
zlz_top       = zlz_vars+8
zlz_match_loc = zlz_vars+10
zlz_head      = zlz_vars+12

zcomp_freq_table  = saveSScreen
zcomp_keymap      = 8700h
zcomp_vars        = OP1
zcomp_input_base  = zcomp_vars
zcomp_input_size  = zcomp_vars+2
zcomp_partition_len=zcomp_input_size+2
zcomp_table_len   = zcomp_partition_len+2
zcomp_best_size   = zcomp_table_len+2
zcomp_part0_size  = zcomp_best_size+3
zcomp_part1_size  = zcomp_part0_size+2
