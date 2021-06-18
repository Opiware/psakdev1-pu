del *.elf
echo on

set targetcpu=__SAM3N4C__

rem SETUP FREERTOS MEMEORY MANAGER
rem heap_1: allocate only
rem heap_2: allocate + deallocate
set RTOSMEMMGR=heap_2

set gccpath="../../software\ARMGCCToolchain/bin"

set include1=freertos/include
set include2=freertos/portable
set include3=cm3/include
set include4=source/include
set include5=cm3/include/component
set include6=cm3/include/instance
set include7=cm3/include/pio

set include=-I %include1% -I %include2% -I %include3% -I %include4% -I %include5% -I %include6% -I %include7% 

set compiler_args=%include% -D%targetcpu% -DBOARD=SAM3N_EK -mthumb -mcpu=cortex-m3 -O0 -fdata-sections -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 -MD -MP
set linker_args=%include% -Wl,-Map=out.map -Wl,--start-group -lm  -Wl,--end-group -L\"../../cmsis/linkerScripts\" -Wl,--gc-sections -Tflash.ld -Wl,--cref -Wl,--entry=Reset_Handler -mthumb -mcpu=cortex-m3
set assembler_args=%include% -mthumb -g -mcpu=cortex-m3

set compiler=arm-none-eabi-gcc
set linker=arm-none-eabi-gcc
set assembler=arm-none-eabi-as
set size=arm-none-eabi-size.exe

rem ============= COMPILE DEMO =============
%gccpath%\%compiler% source/main.c %compiler_args%
%gccpath%\%compiler% source/serial.c %compiler_args%

rem ============= COMPILE FREERTOS =============
%gccpath%\%compiler% freertos/croutine.c %compiler_args% 
%gccpath%\%compiler% freertos/list.c %compiler_args% 
%gccpath%\%compiler% freertos/queue.c %compiler_args% 
%gccpath%\%compiler% freertos/tasks.c %compiler_args% 
%gccpath%\%compiler% freertos/timers.c %compiler_args% 
%gccpath%\%compiler% freertos/mem/%RTOSMEMMGR%.c %compiler_args% 
%gccpath%\%compiler% freertos/portable/port.c %compiler_args% 

rem ============= COMPILE CM3 CORE =============
%gccpath%\%compiler% cm3/exceptions.c %compiler_args% 
%gccpath%\%compiler% cm3/startup_sam3n.c %compiler_args% 
%gccpath%\%compiler% cm3/system_sam3n.c %compiler_args% 

rem ============= LINK ALL =============
%gccpath%\%linker% -o demo.elf %RTOSMEMMGR%.o port.o croutine.o list.o queue.o tasks.o timers.o exceptions.o startup_sam3n.o system_sam3n.o serial.o main.o %linker_args%

%gccpath%\%size% demo.elf

echo off
del *.map
del *.asm
del *.sdf
del *.pwi
del *.dbk
del *.o
del *.d