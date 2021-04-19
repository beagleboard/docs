# Running a Program; Configuring Pins

There are a lot of details in compiling and running PRU code. Fortunately those details are captured in a common `Makefile` that is used througout this book. This chapter shows how to use the `Makefile` to compile code and also start and stop the PRUs.

The following are resources used in this chapter.

## [1.2. Compiling and Running](running-a-program-configuring-pins.md#_compiling_and_running) <a id="_compiling_and_running"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_2) <a id="_problem_2"></a>

I want to compile and run an example.

### [Solution](running-a-program-configuring-pins.md#_solution_2) <a id="_solution_2"></a>

Change to the directory of the code you want to run.

```text
bone$ cd PRUCookbook/docs/06io/code
bone$ ls
gpio.pru0.c  Makefile  setup.sh
```

Source the setup file.

```text
bone$ source setup.sh
TARGET=gpio.pru0
PocketBeagle Found
P1_36
Current mode for P1_36 is:     default
```

Now you are ready to compile and run. This is automated for you in the Makefile

```text
bone$ make
/var/lib/cloud9/common/Makefile:28: MODEL=TI_AM335x_BeagleBone_Black,TARGET=gpio.pru0,COMMON=/var/lib/cloud9/common
/var/lib/cloud9/common/Makefile:147: GEN_DIR=/tmp/cloud9-examples,CHIP=am335x,PROC=pru,PRUN=0,PRU_DIR=/sys/class/remoteproc/remoteproc1,EXE=.out
-    Stopping PRU 0
/bin/sh: 1: echo: echo: I/O error
Cannot stop 0
CC  gpio.pru0.c
"/var/lib/cloud9/common/prugpio.h", line 53: warning #1181-D: #warning directive: "Found am335x"
LD  /tmp/cloud9-examples/gpio.pru0.o
-   copying firmware file /tmp/cloud9-examples/gpio.pru0.out to /lib/firmware/am335x-pru0-fw
write_init_pins.sh
writing "out" to "/sys/class/gpio/gpio30/direction"
-    Starting PRU 0
MODEL   = TI_AM335x_BeagleBone_Black
PROC    = pru
PRUN    = 0
PRU_DIR = /sys/class/remoteproc/remoteproc1
rm /tmp/cloud9-examples/gpio.pru0.o
```

Congratulations, your are now running a PRU. If you have an LED attached to `P9_11` on the Black, it should be blinking.

### [Discussion](running-a-program-configuring-pins.md#_discussion) <a id="_discussion"></a>

The `setup.sh` file sets the `TARGET` to the file you want to compile. Set it to the filename, without the `.c` extension \(`gpio.pru0`\). The file extension `.pru0` specifies the number of the PRU you are using \(either `1_0`, `1_1`, `2_0`, `2_1` on the AI or `0` or `1` on the others\)

You can override the `TARGET` on the command line.

```text
bone$ cp gpio.pru0.c gpio.pru1.c
bone$ export TARGET=gpio.pru1
```

Notice the `TARGET` doesn’t have the `.c` on the end.

You can also specify them when running `make`.

```text
bone$ cp gpio.pru0.c gpio.pru1.c
bone$ make TARGET=gpio.pru1
```

The setup file also contains instructions to figure out which Beagle you are running and then configure the pins acordingly.

setup.sh

```text
#!/bin/bash

export TARGET=gpio.pru0
echo TARGET=$TARGET

# Configure the PRU pins based on which Beagle is running
machine=$(awk '{print $NF}' /proc/device-tree/model)
echo -n $machine
if [ $machine = "Black" ]; then
    echo " Found"
    pins="P9_11"
elif [ $machine = "Blue" ]; then
    echo " Found"
    pins=""
elif [ $machine = "PocketBeagle" ]; then
    echo " Found"
    pins="P2_05"
else
    echo " Not Found"
    pins=""
fi

for pin in $pins
do
    echo $pin
    config-pin $pin out
    config-pin -q $pin
done
```

| Line | Explanation |
| :--- | :--- |
| 2-5 | Set which PRU to use and which file to compile. |
| 7 | Figure out which type of Beagle we have. |
| 9-21 | Based on the type, set the `pins`. |
| 23-28 | Configure \(set the pin mux\) for each of the pins. |

| Tip | The BeagleBone AI has it’s pins preconfigured at boot time, so there’s no need to use `config-pin`. |
| :--- | :--- |


The `Makefile` stops the PRU, compiles the file and moves it where it will be loaded, and then restarts the PRU.

## [1.3. Stopping and Starting the PRU](running-a-program-configuring-pins.md#_stopping_and_starting_the_pru) <a id="_stopping_and_starting_the_pru"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_3) <a id="_problem_3"></a>

I want to stop and start the PRU.

### [Solution](running-a-program-configuring-pins.md#_solution_3) <a id="_solution_3"></a>

It’s easy, if you already have `TARGET` set up:

```text
bone$ make stop
-    Stopping PRU 0
stop
bone$ make start
-    Starting PRU 0
start
```

See [dmesg -Hw](https://markayoder.github.io/PRUCookbook/04debug/debug.html.html#_dmesg_hw) to see how to tell if the PRU is stopped.

This assumes `TARGET` is set to the PRU you are using. If you want to control the other PRU use:

```text
bone$ cp gpio.pru0.c gpio.pru1.c
bone$ make TARGET=gpio.pru1
bone$ make TARGET=gpio.pru1 stop
bone$ make TARGET=gpio.pru1 start
```

## [1.4. The Standard Makefile](running-a-program-configuring-pins.md#details_makefile) <a id="details_makefile"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_4) <a id="_problem_4"></a>

There are all sorts of options that need to be set when compiling a program. How can I be sure to get them all right?

### [Solution](running-a-program-configuring-pins.md#_solution_4) <a id="_solution_4"></a>

The surest way to make sure everything is right is to use our standard `Makefile`.

### [Discussion](running-a-program-configuring-pins.md#_discussion_2) <a id="_discussion_2"></a>

It’s assumed you already know how Makefiles work. If not, there are many resources online that can bring you up to speed. Here is the local `Makefile` used throughout this book.

Local Makefile

```text

  1include /var/lib/cloud9/common/Makefile
```

Each of the local Makefiles refer to the same standard Makefile. The details of how the Makefile works is beyond the scope of this cookbook.

Fortunately you shouldn’t have to modify the `Makefile`.

## [1.5. Compiling with clpru and lnkpru](running-a-program-configuring-pins.md#_compiling_with_clpru_and_lnkpru) <a id="_compiling_with_clpru_and_lnkpru"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_5) <a id="_problem_5"></a>

You need details on the c compiler, linker and other tools for the PRU.

### [Solution](running-a-program-configuring-pins.md#_solution_5) <a id="_solution_5"></a>

The PRU compiler and linker are already installed on the standard images. They are called `clpru` and `lnkpru`.

```text
bone$ which clpru
/usr/bin/clpru
```

Details on each can be found here:

In fact there are PRU versions of many of the standard code generation tools.

code tools

```text
bone$ ls /usr/bin/*pru
/usr/bin/abspru    /usr/bin/clistpru  /usr/bin/hexpru      /usr/bin/ofdpru
/usr/bin/acpiapru  /usr/bin/clpru     /usr/bin/ilkpru      /usr/bin/optpru
/usr/bin/arpru     /usr/bin/dempru    /usr/bin/libinfopru  /usr/bin/rc_test_encoders_pru
/usr/bin/asmpru    /usr/bin/dispru    /usr/bin/lnkpru      /usr/bin/strippru
/usr/bin/cgpru     /usr/bin/embedpru  /usr/bin/nmpru       /usr/bin/xrefpru
```

## [1.6. The Linker Command File - am335x\_pru.cmd](running-a-program-configuring-pins.md#detail_linker) <a id="detail_linker"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_6) <a id="_problem_6"></a>

The linker needs to be told where in memory to place the code and variables.

### [Solution](running-a-program-configuring-pins.md#_solution_6) <a id="_solution_6"></a>

`am335x_pru.cmd` is the standard linker command file that tells the linker where to put what for the BeagleBone Black and Blue, and the Pocket. The `am57xx_pru.cmd` does the same for the AI. Both files can be found in `/var/lib/cloud9/common`.

am335x\_pru.cmd

```text

  123456789101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687/****************************************************************************//*  AM335x_PRU.cmd                                                          *//*  Copyright (c) 2015  Texas Instruments Incorporated                      *//*                                                                          *//*    Description: This file is a linker command file that can be used for  *//*                 linking PRU programs built with the C compiler and       *//*                 the resulting .out file on an AM335x device.             *//****************************************************************************/-cr                             /* Link using C conventions *//* Specify the System Memory Map */MEMORY{      PAGE 0:    PRU_IMEM        : org = 0x00000000 len = 0x00002000  /* 8kB PRU0 Instruction RAM */      PAGE 1:    /* RAM */    PRU_DMEM_0_1    : org = 0x00000000 len = 0x00002000 CREGISTER=24 /* 8kB PRU Data RAM 0_1 */    PRU_DMEM_1_0    : org = 0x00002000 len = 0x00002000 CREGISTER=25 /* 8kB PRU Data RAM 1_0 */      PAGE 2:    PRU_SHAREDMEM   : org = 0x00010000 len = 0x00003000 CREGISTER=28 /* 12kB Shared RAM */    DDR             : org = 0x80000000 len = 0x00000100 CREGISTER=31    L3OCMC          : org = 0x40000000 len = 0x00010000 CREGISTER=30    /* Peripherals */    PRU_CFG         : org = 0x00026000 len = 0x00000044 CREGISTER=4    PRU_ECAP        : org = 0x00030000 len = 0x00000060 CREGISTER=3    PRU_IEP         : org = 0x0002E000 len = 0x0000031C CREGISTER=26    PRU_INTC        : org = 0x00020000 len = 0x00001504 CREGISTER=0    PRU_UART        : org = 0x00028000 len = 0x00000038 CREGISTER=7    DCAN0           : org = 0x481CC000 len = 0x000001E8 CREGISTER=14    DCAN1           : org = 0x481D0000 len = 0x000001E8 CREGISTER=15    DMTIMER2        : org = 0x48040000 len = 0x0000005C CREGISTER=1    PWMSS0          : org = 0x48300000 len = 0x000002C4 CREGISTER=18    PWMSS1          : org = 0x48302000 len = 0x000002C4 CREGISTER=19    PWMSS2          : org = 0x48304000 len = 0x000002C4 CREGISTER=20    GEMAC           : org = 0x4A100000 len = 0x0000128C CREGISTER=9    I2C1            : org = 0x4802A000 len = 0x000000D8 CREGISTER=2    I2C2            : org = 0x4819C000 len = 0x000000D8 CREGISTER=17    MBX0            : org = 0x480C8000 len = 0x00000140 CREGISTER=22    MCASP0_DMA      : org = 0x46000000 len = 0x00000100 CREGISTER=8    MCSPI0          : org = 0x48030000 len = 0x000001A4 CREGISTER=6    MCSPI1          : org = 0x481A0000 len = 0x000001A4 CREGISTER=16    MMCHS0          : org = 0x48060000 len = 0x00000300 CREGISTER=5    SPINLOCK        : org = 0x480CA000 len = 0x00000880 CREGISTER=23    TPCC            : org = 0x49000000 len = 0x00001098 CREGISTER=29    UART1           : org = 0x48022000 len = 0x00000088 CREGISTER=11    UART2           : org = 0x48024000 len = 0x00000088 CREGISTER=12    RSVD10          : org = 0x48318000 len = 0x00000100 CREGISTER=10    RSVD13          : org = 0x48310000 len = 0x00000100 CREGISTER=13    RSVD21          : org = 0x00032400 len = 0x00000100 CREGISTER=21    RSVD27          : org = 0x00032000 len = 0x00000100 CREGISTER=27}/* Specify the sections allocation into memory */SECTIONS {    /* Forces _c_int00 to the start of PRU IRAM. Not necessary when loading       an ELF file, but useful when loading a binary */    .text:_c_int00* >  0x0, PAGE 0    .text       >  PRU_IMEM, PAGE 0    .stack      >  PRU_DMEM_0_1, PAGE 1    .bss        >  PRU_DMEM_0_1, PAGE 1    .cio        >  PRU_DMEM_0_1, PAGE 1    .data       >  PRU_DMEM_0_1, PAGE 1    .switch     >  PRU_DMEM_0_1, PAGE 1    .sysmem     >  PRU_DMEM_0_1, PAGE 1    .cinit      >  PRU_DMEM_0_1, PAGE 1    .rodata     >  PRU_DMEM_0_1, PAGE 1    .rofardata  >  PRU_DMEM_0_1, PAGE 1    .farbss     >  PRU_DMEM_0_1, PAGE 1    .fardata    >  PRU_DMEM_0_1, PAGE 1    .resource_table > PRU_DMEM_0_1, PAGE 1    .init_pins > PRU_DMEM_0_1, PAGE 1}
```

The cmd file for the AI is about the same, with appropriate addresses for the AI.

### [Discussion](running-a-program-configuring-pins.md#_discussion_3) <a id="_discussion_3"></a>

The important things to notice in the file are given in the following table.

| Table 1. AM335x\_PRU.cmd important things |  |
| :--- | :--- |
| Line | Explanation |
| 16 | This is where the instructions are stored. See page 206 of the [AM335x Technical Reference Manual](https://www.ti.com/lit/ug/spruh73p/spruh73p.pdf) Or see page 417 of [AM572x Technical Reference Manual](http://www.ti.com/lit/pdf/spruhz6l) for the AI. |
| 22 | This is where PRU 0’s DMEM 0 is mapped. It’s also where PRU 1’s DMEM 1 is mapped. |
| 23 | The reverse to above. PRU 0’s DMEM 1 appears here and PRU 1’s DMEM 0 is here. |
| 26 | The shared memory for both PRU’s appears here. |
| 72 | The `.text` section is where the code goes. It’s mapped to `IMEM` |
| 73 | The stack is then mapped to DMEM 0. Notice that DMEM 0 is one bank of memory for PRU 0 and another for PRU1, so they both get their own stacks. |
| 74 | The `.bss` section is where the heap goes. |

Why is it important to understand this file? If you are going to store things in DMEM, you need to be sure to start at address 0x0200 since the stack and the heap are in the locations below 0x0200.

## [1.7. Loading Firmware](running-a-program-configuring-pins.md#_loading_firmware) <a id="_loading_firmware"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_7) <a id="_problem_7"></a>

I have my PRU code all compiled and need to load it on the PRU.

### [Solution](running-a-program-configuring-pins.md#_solution_7) <a id="_solution_7"></a>

It’s a simple three step process.

1. Stop the PRU
2. Write the `.out` file to the right place in `/lib/firmware`
3. Start the PRU.

### [Discussion](running-a-program-configuring-pins.md#_discussion_4) <a id="_discussion_4"></a>

The PRUs appear in the Linux file space at `/dev/remoteproc/`.

Finding the PRUs

```text
bone$ cd /dev/remoteproc/
bone$ ls
pruss-core0  pruss-core1
```

Or if you are on the AI:

```text
bone$ cd /dev/remoteproc/
bone$ ls
dsp1  dsp2  ipu1  ipu2  pruss1-core0  pruss1-core1  pruss2-core0  pruss2-core1
```

You see there that the AI has two pairs of PRUs, plus a couple of DSPs and other goodies.

Here we see PRU 0 and PRU 1 in the path. Let’s follow PRU 0.

```text
bone$ cd pruss-core0
bone$ ls
device  firmware  name  power  state  subsystem  uevent
```

Here we see the files that control PRU 0. `firmware` tells where in `/lib/firmware` to look for the code to run on the PRU.

```text
bone$ cat firmware
am335x-pru0-fw
```

Therefore you copy your `.out` file to `/lib/firmware/am335x-pru0-fw`.

## [1.8. Configuring Pins for Controlling Servos](running-a-program-configuring-pins.md#details_configure_servos) <a id="details_configure_servos"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_8) <a id="_problem_8"></a>

You want to configure the pins so the PRU _outputs_ are accessable.

### [Solution](running-a-program-configuring-pins.md#_solution_8) <a id="_solution_8"></a>

It depends on which Beagle you are running on. If you are on the AI or Blue, everything is already configured for you. If you are on the Black or Pocket you’ll need to run the following script.

servos\_setup.sh

```text
#!/bin/bash
# Configure the PRU pins based on which Beagle is running
machine=$(awk '{print $NF}' /proc/device-tree/model)
echo -n $machine
if [ $machine = "Black" ]; then
    echo " Found"
    pins="P8_27 P8_28 P8_29 P8_30 P8_39 P8_40 P8_41 P8_42"
elif [ $machine = "Blue" ]; then
    echo " Found"
    pins=""
elif [ $machine = "PocketBeagle" ]; then
    echo " Found"
    pins="P2_35 P1_35 P1_02 P1_04"
else
    echo " Not Found"
    pins=""
fi

for pin in $pins
do
    echo $pin
    config-pin $pin pruout
    config-pin -q $pin
done
```

### [Discussion](running-a-program-configuring-pins.md#_discussion_5) <a id="_discussion_5"></a>

The first part of the code looks in `/proc/device-tree/model` to see which Beagle is running. Based on that it assigns `pins` a list of pins to configure. Then the last part of the script loops through each of the pins and configures it.

## [1.9. Configuring Pins for Controlling Encoders](running-a-program-configuring-pins.md#details_configure_encoders) <a id="details_configure_encoders"></a>

### [Problem](running-a-program-configuring-pins.md#_problem_9) <a id="_problem_9"></a>

You want to configure the pins so the PRU _inputs_ are accessable.

### [Solution](running-a-program-configuring-pins.md#_solution_9) <a id="_solution_9"></a>

It depends on which Beagle you are running on. If you are on the AI or Blue, everything is already configured for you. If you are on the Black or Pocket you’ll need to run the following script.

encoder\_setup.sh

```text
#!/bin/bash
# Configure the pins based on which Beagle is running
machine=$(awk '{print $NF}' /proc/device-tree/model)
echo -n $machine

# Configure eQEP pins
if [ $machine = "Black" ]; then
    echo " Found"
    pins="P9_92 P9_27 P8_35 P8_33 P8_12 P8_11 P8_41 P8_42"
elif [ $machine = "Blue" ]; then
    echo " Found"
    pins=""
elif [ $machine = "PocketBeagle" ]; then
    echo " Found"
    pins="P1_31 P2_34 P2_10 P2_24 P2_33"
else
    echo " Not Found"
    pins=""
fi

for pin in $pins
do
    echo $pin
    config-pin $pin qep
    config-pin -q $pin
done

##########################################
# Configure PRU pins
if [ $machine = "Black" ]; then
    echo " Found"
    pins="P8_16 P8_15"
elif [ $machine = "Blue" ]; then
    echo " Found"
    pins=""
elif [ $machine = "PocketBeagle" ]; then
    echo " Found"
    pins="P2_09 P2_18"
else
    echo " Not Found"
    pins=""
fi

for pin in $pins
do
    echo $pin
    config-pin $pin pruin
    config-pin -q $pin
done
```

### [Discussion](running-a-program-configuring-pins.md#_discussion_6) <a id="_discussion_6"></a>

This works like the servo setup except some of the pins are configured as to the hardware eQEPs and other to the PRU inputs.

