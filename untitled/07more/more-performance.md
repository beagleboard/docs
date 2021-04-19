# More Performance

So far in all our examples we’ve been able to meet our timing goals by writing our code in the C programming language. The C compiler does a suprisingly good job at generating code, most the time. However there are times when very precise timing is needed and the compiler isn’t doing it.

At these times you need to write in assembly language. This chapter introduces the PRU assembler and shows how to call assembly code from C. Detailing on how to program in assembly are beyond the scope of this text.

The following are resources used in this chapter.

## [1.1. Calling Assembly from C](more-performance.md#_calling_assembly_from_c) <a id="_calling_assembly_from_c"></a>

### [Problem](more-performance.md#_problem) <a id="_problem"></a>

You have some C code and you want to call an assembly language routine from it.

### [Solution](more-performance.md#_solution) <a id="_solution"></a>

You need to do two things, write the assembler file and modify the `Makefile` to include it. For example, let’s write our own `my_delay_cycles` routine in in assembly. The intrinsic `__delay_cycles` must be passed a compile time constant. Our new `delay_cycles` can take a runtime delay value.

[delay-test.pru0.c](more-performance.md#more_delay-test) is much like our other c code, but on line 10 we declare `my_delay_cycles` and then on lines 24 and 26 we’ll call it with an argument of 1.

delay-test.pru0.c

```text

  12345678910111213141516171819202122232425262728#include #include #include "resource_table_empty.h"#include "prugpio.h"extern void my_delay_cycles(uint32_t);volatile register uint32_t R30;volatile register uint32_t R31;void main(void){    uint32_t gpio = P9_31;          CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;    while(1) {        R30 |= gpio;              my_delay_cycles(1);        R30 &= ~gpio;             my_delay_cycles(1);    }}
```

delay.pru0.asm

```text

  123456789; This is an example of how to call an assembly routine from C.;   Mark A. Yoder, 9-July-2018    .global my_delay_cyclesmy_delay_cycles:delay:    sub     r14,   r14, 1       ; The first argument is passed in r14    qbne    delay, r14, 0    jmp     r3.w2           ; r3 contains the return address
```

The `Makefile` has one addition that needs to be made to compile both [delay-test.pru0.c](more-performance.md#more_delay-test) and [delay.pru0.asm](more-performance.md#more_delay). If you look in the local `Makefile` you’ll see:

Makefile

```text
include /var/lib/cloud9/common/Makefile
```

This Makefle includes a common Makfile at `/var/lib/cloud9/common/Makefile`, this the Makefile you need to edit. Edit `/var/lib/cloud9/common/Makefile` and go to line 197.

```text
$(GEN_DIR)/%.out: $(GEN_DIR)/%.o $(GEN_DIR)/$(TARGETasm).o
    @mkdir -p $(GEN_DIR)
    @echo 'LD   $^'
    $(eval $(call target-to-proc,$@))
    $(eval $(call proc-to-build-vars,$@))
    @$(LD) $@ $^ $(LDFLAGS)
```

Add **`(GEN_DIR)/$(TARGETasm).o`** as shown in bold above. You will want to remove this addition once you are done with this example since it will break the other examples.

The following will compile and run everything.

```text
bone$ config-pin P9_31 pruout
bone$ make TARGET=delay-test.pru0 TARGETasm=delay.pru0
/var/lib/cloud9/common/Makefile:29: MODEL=TI_AM335x_BeagleBone_Black,TARGET=delay-test.pru0
-    Stopping PRU 0
-   copying firmware file /tmp/cloud9-examples/delay-test.pru0.out to /lib/firmware/am335x-pru0-fw
write_init_pins.sh
-    Starting PRU 0
MODEL   = TI_AM335x_BeagleBone_Black
PROC    = pru
PRUN    = 0
PRU_DIR = /sys/class/remoteproc/remoteproc1
```

Output of my\_delay\_cycles\(\)

Notice the on time is about 35ns and the off time is 30ns.

### [Discission](more-performance.md#_discission) <a id="_discission"></a>

There is much to explain here. Let’s start with [delay.pru0.asm](more-performance.md#more_delay).

<table>
  <thead>
    <tr>
      <th style="text-align:left">Table 1. Line-by-line of delay.pru0.asm</th>
      <th style="text-align:left"></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align:left">Line</td>
      <td style="text-align:left">Explanation</td>
    </tr>
    <tr>
      <td style="text-align:left">3</td>
      <td style="text-align:left">Declare <code>my_delay_cycles</code> to be global so the linker can find
        it.</td>
    </tr>
    <tr>
      <td style="text-align:left">4</td>
      <td style="text-align:left">Label the starting point for <code>my_delay_cycles</code>.</td>
    </tr>
    <tr>
      <td style="text-align:left">5</td>
      <td style="text-align:left">Label for our delay loop.</td>
    </tr>
    <tr>
      <td style="text-align:left">6</td>
      <td style="text-align:left">
        <p>The first argument is passed in register <code>r14</code>. Page 111 of
          <a
          href="http://www.ti.com/lit/ug/spruhv7b/spruhv7b.pdf">PRU Optimizing C/C++ Compiler, v2.2, User&#x2019;s Guide</a>gives the
            argument passing convention. Registers <code>r14</code> to <code>r29</code> are
            used to pass arguments, if there are more arguments, the argument stack
            (<code>r4</code>) is used. The other register conventions are found on
            page 108.</p>
        <p>Here we subtract 1 from <code>r14</code> and save it back into <code>r14</code>.</p>
      </td>
    </tr>
    <tr>
      <td style="text-align:left">7</td>
      <td style="text-align:left"><code>qbne</code> is a quick branch if not equal.</td>
    </tr>
    <tr>
      <td style="text-align:left">9</td>
      <td style="text-align:left">Once we&#x2019;ve delayed enough we drop through the quick branch and
        hit the jump. The upper bits of register <code>r3</code> has the return address,
        therefore we return to the c code.</td>
    </tr>
  </tbody>
</table>

[Output of my\_delay\_cycles\(\)](more-performance.md#more_my_delay_cycles) shows the _on_ time is 35ns and the off time is 30ns. With 5ns/cycle this gives 7 cycles on and 6 off. These times make sense because each instruction takes a cycle and you have, set `R30`, jump to `my_delay_cycles`, `sub`, `qbne`, `jmp`. Plus the instruction \(not seen\) that initilizes `r14` to the passed value. That’s a total of six instructions. The extra instruction is the branch at the bottom of the `while` loop.

## [1.2. Returning a Value from Assembly](more-performance.md#_returning_a_value_from_assembly) <a id="_returning_a_value_from_assembly"></a>

### [Problem](more-performance.md#_problem_2) <a id="_problem_2"></a>

Your assembly code needs to return a value.

### [Solution](more-performance.md#_solution_2) <a id="_solution_2"></a>

`R14` is how the return value is passed back. [delay-test2.pru0.c](more-performance.md#more_test2) shows the c code.

delay-test2.pru0.c

```text

  1234567891011121314151617181920212223242526272829303132#include #include #include "resource_table_empty.h"#include "prugpio.h"#define TEST    100extern uint32_t my_delay_cycles(uint32_t);uint32_t ret;volatile register uint32_t R30;volatile register uint32_t R31;void main(void){    uint32_t gpio = P9_31;          CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;    while(1) {        R30 |= gpio;              ret = my_delay_cycles(1);        R30 &= ~gpio;             ret = my_delay_cycles(1);    }}
```

delay2.pru0.asm

```text

  123456789101112131415; This is an example of how to call an assembly routine from C with a retun value.;   Mark A. Yoder, 9-July-2018    .cdecls "delay-test2.pru0.c"    .global my_delay_cyclesmy_delay_cycles:delay:    sub     r14,   r14, 1       ; The first argument is passed in r14    qbne    delay, r14, 0    ldi     r14, TEST       ; TEST is defined in delay-test2.c                            ; r14 is the return register    jmp     r3.w2           ; r3 contains the return address
```

An additional feature is shown in line 4 of [delay2.pru0.asm](more-performance.md#more_delay2). The `.cdecls "delay-test2.pru0.c"` says to include any defines from `delay-test2.pru0.c` In this example, line 6 of [delay-test2.pru0.c](more-performance.md#more_test2) `#defines` TEST and line 12 of [delay2.pru0.asm](more-performance.md#more_delay2) reference it.

## [1.3. Using the Built-In Counter for Timing](more-performance.md#_using_the_built_in_counter_for_timing) <a id="_using_the_built_in_counter_for_timing"></a>

### [Problem](more-performance.md#_problem_3) <a id="_problem_3"></a>

I want to count how many cycles my routine takes.

### [Solution](more-performance.md#_solution_3) <a id="_solution_3"></a>

Each PRU has a `CYCLE` register which counts the number of cycles since the PRU was enabled. They also have a `STALL` register that counts how many times the PRU stalled fetching an instruction. [cycle.pru0.c - Code to count cycles.](more-performance.md#more_cycle) shows they are used.

cycle.pru0.c - Code to count cycles.

```text

  1234567891011121314151617181920212223242526272829303132#include #include #include #include "resource_table_empty.h"#include "prugpio.h"volatile register uint32_t R30;volatile register uint32_t R31;void main(void){    uint32_t gpio = P9_31;          uint32_t cycle, stall;        CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;    PRU0_CTRL.CTRL_bit.CTR_EN = 1;      R30 |= gpio;                          PRU0_CTRL.CYCLE = cycle;    R30 &= ~gpio;                 cycle = PRU0_CTRL.CYCLE;        stall = PRU0_CTRL.STALL;        __halt();}
```

### [Discission](more-performance.md#_discission_2) <a id="_discission_2"></a>

The code is mostly the same as other examples. `cycle` and `stall` end up in registers which we can read using prudebug. [Line-by-line for cycle.pru0.c](more-performance.md#more_cycle_lines) is the Line-by-line.

| Table 2. Line-by-line for cycle.pru0.c |  |
| :--- | :--- |
| Line | Explanation |
| 4 | Include needed to reference `CYCLE` and `STALL`. |
| 16 | Declaring `cycle` and `stall`. The compiler will optimize these and just keep them in registers. We’ll have to look at the `cycle.pru0.lst` file to see where they are stored. |
| 21 | Enables `CYCLE`. |
| 26 | Reset `CYCLE`. It ignores the value assigned to it and always sets it to 0. `cycle` is on the right hand side to make the compiler give it it’s own register. |
| 28, 29 | Reads the `CYCLE` and `STALL` values into registers. |

/tmp/cloud9-examples/cycle.pru0.lst Lines 113..119

```text

  1234567     103;----------------------------------------------------------------------     104;  23 | PRU0_CTRL.CTRL_bit.CTR_EN = 1;  // Enable cycle counter     105;----------------------------------------------------------------------     106 0000000c 200080240002C0          LDI32     r0, 0x00022000        ; [ALU_PRU] |23| $O$C1     107 00000014 000000F1002081          LBBO      &r1, r0, 0, 4         ; [ALU_PRU] |23|     108 00000018 0000001F03E1E1          SET       r1, r1, 0x00000003    ; [ALU_PRU] |23|     109 0000001c 000000E1002081          SBBO      &r1, r0, 0, 4         ; [ALU_PRU] |23|
```

/tmp/cloud9-examples/cycle.pru0.lst Lines 146..152

```text

  1234567     131;----------------------------------------------------------------------     132 0000002c 000000F10C2081          LBBO      &r1, r0, 12, 4        ; [ALU_PRU] |30| $O$C1     133        .dwpsn  file "cycle.pru0.c",line 31,column 2,is_stmt,isa 0     134;----------------------------------------------------------------------     135;  31 | stall = PRU0_CTRL.STALL;        // Ditto for stall     136;----------------------------------------------------------------------     137 00000030 000000F1102080          LBBO      &r0, r0, 16, 4        ; [ALU_PRU] |31| $O$C1
```

The first `LBBO` takes the contents of `r0` and adds the offset 12 to it and copies 4 bytes into `r1`. This points to `CYCLE`, so `r1` has the contents of `CYCLE`.

The second `LBBO` does the same, but with offset 16, which points to `STALL`, thus `STALL` is now in `r0`.

Now fire up prudebug and look at those registers.

```text
bone$ sudo prudebug
PRU0> r
r
r
Register info for PRU0
    Control register: 0x00000009
      Reset PC:0x0000  STOPPED, FREE_RUN, COUNTER_ENABLED, NOT_SLEEPING, PROC_DISABLED

    Program counter: 0x0012
      Current instruction: HALT

    R00: 0x00000005    R08: 0x00000200    R16: 0x000003c6    R24: 0x00110210
    R01: 0x00000003    R09: 0x00000000    R17: 0x00000000    R25: 0x00000000
    R02: 0x000000fc    R10: 0xfff4ea57    R18: 0x000003e6    R26: 0x6e616843
    R03: 0x0004272c    R11: 0x5fac6373    R19: 0x30203020    R27: 0x206c656e
    R04: 0xffffffff    R12: 0x59bfeafc    R20: 0x0000000a    R28: 0x00003033
    R05: 0x00000007    R13: 0xa4c19eaf    R21: 0x00757270    R29: 0x02100000
    R06: 0xefd30a00    R14: 0x00000005    R22: 0x0000001e    R30: 0xa03f9990
    R07: 0x00020024    R15: 0x00000003    R23: 0x00000000    R31: 0x00000000
```

So `cycle` is 3 and `stall` is 5. It must be one cycle to clear the GPIO and 2 cycles to read the `CYCLE` register and save it in the register. It’s interesting there are 5 `stall` cycles.

If you switch the order of lines 30 and 31 you’ll see `cycle` is 7 and `stall` is 2. `cycle` now includes the time needed to read `stall` and `stall` no longer includes the time to read `cycle`.

## [1.4. Xout and Xin - Transfering Between PRUs](more-performance.md#_xout_and_xin_transfering_between_prus) <a id="_xout_and_xin_transfering_between_prus"></a>

### [Problem](more-performance.md#_problem_4) <a id="_problem_4"></a>

I need to transfer data between PRUs quickly.

### [Solution](more-performance.md#_solution_4) <a id="_solution_4"></a>

The `__xout()` and `__xin()` intrinsics are able to transfer up to 30 registers between PRU 0 and PRU 1 quickly. [xout.pru0.c](more-performance.md#more_xout) shows how `xout()` running on PRU 0 transfers six registers to PRU 1.

xout.pru0.c

```text

  12345678910111213141516171819202122232425262728293031323334353637383940414243444546474849505152#include #include #include "resource_table_pru0.h"volatile register uint32_t R30;volatile register uint32_t R31;typedef struct {    uint32_t reg5;    uint32_t reg6;    uint32_t reg7;    uint32_t reg8;    uint32_t reg9;    uint32_t reg10;} bufferData;bufferData dmemBuf;#define PRU1_PRU0_INTERRUPT (18)#define PRU0_ARM_INTERRUPT (19+16)void main(void){        CT_INTC.SECR0 = 0xFFFFFFFF;    CT_INTC.SECR1 = 0xFFFFFFFF;        dmemBuf.reg5 = 0xDEADBEEF;    dmemBuf.reg6 = 0xAAAAAAAA;    dmemBuf.reg7 = 0x12345678;    dmemBuf.reg8 = 0xBBBBBBBB;    dmemBuf.reg9 = 0x87654321;    dmemBuf.reg10 = 0xCCCCCCCC;        while ((R31 & (1<<30)) == 0) {    }            xout(14, 5, 0, dmemBuf);        CT_INTC.SICR = PRU1_PRU0_INTERRUPT;        __halt();}
```

PRU 1 waits at line 42 until PRU 0 signals it. [xin.pru1.c](more-performance.md#more_xin) sends sends an interupt to PRU 0 and waits for it to send the data.

xin.pru1.c

```text

  12345678910111213141516171819202122232425262728293031323334#include #include "resource_table_empty.h"volatile register uint32_t R30;volatile register uint32_t R31;typedef struct {    uint32_t reg5;    uint32_t reg6;    uint32_t reg7;    uint32_t reg8;    uint32_t reg9;    uint32_t reg10;} bufferData;bufferData dmemBuf;#define PRU1_PRU0_INTERRUPT (18)#define PRU1_ARM_INTERRUPT (20+16)void main(void){        R31 = PRU1_PRU0_INTERRUPT+16;            xin(14, 5, 0, dmemBuf);        __halt();}
```

Use `prudebug` to see registers R5-R10 are transfered from PRU 0 to PRU 1.

```text

  1234567891011121314151617181920212223242526272829303132333435363738PRU0> rRegister info for PRU0    Control register: 0x00000001      Reset PC:0x0000  STOPPED, FREE_RUN, COUNTER_DISABLED, NOT_SLEEPING, PROC_DISABLED    Program counter: 0x0026      Current instruction: HALT    R00: 0x00000012    R08: 0xbbbbbbbb    R16: 0x000003c6    R24: 0x00110210    R01: 0x00020000    R09: 0x87654321    R17: 0x00000000    R25: 0x00000000    R02: 0x000000e4    R10: 0xcccccccc    R18: 0x000003e6    R26: 0x6e616843    R03: 0x0004272c    R11: 0x5fac6373    R19: 0x30203020    R27: 0x206c656e    R04: 0xffffffff    R12: 0x59bfeafc    R20: 0x0000000a    R28: 0x00003033    R05: 0xdeadbeef    R13: 0xa4c19eaf    R21: 0x00757270    R29: 0x02100000    R06: 0xaaaaaaaa    R14: 0x00000005    R22: 0x0000001e    R30: 0xa03f9990    R07: 0x12345678    R15: 0x00000003    R23: 0x00000000    R31: 0x00000000PRU0> pru 1pru 1Active PRU is PRU1.PRU1> rrRegister info for PRU1    Control register: 0x00000001      Reset PC:0x0000  STOPPED, FREE_RUN, COUNTER_DISABLED, NOT_SLEEPING, PROC_DISABLED    Program counter: 0x000b      Current instruction: HALT    R00: 0x00000100    R08: 0xbbbbbbbb    R16: 0xe9da228b    R24: 0x28113189    R01: 0xe48cdb1f    R09: 0x87654321    R17: 0x66621777    R25: 0xddd29ab1    R02: 0x000000e4    R10: 0xcccccccc    R18: 0x661f83ea    R26: 0xcf1cd4a5    R03: 0x0004db97    R11: 0xdec387d5    R19: 0xa85adb78    R27: 0x70af2d02    R04: 0xa90e496f    R12: 0xbeac3878    R20: 0x048fff22    R28: 0x7465f5f0    R05: 0xdeadbeef    R13: 0x5777b488    R21: 0xa32977c7    R29: 0xae96b530    R06: 0xaaaaaaaa    R14: 0xffa60550    R22: 0x99fb123e    R30: 0x52c42a0d    R07: 0x12345678    R15: 0xdeb2142d    R23: 0xa353129d    R31: 0x00000000
```

### [Discussion](more-performance.md#_discussion) <a id="_discussion"></a>

<table>
  <thead>
    <tr>
      <th style="text-align:left">Table 3. xout.pru0.c Line-by-line</th>
      <th style="text-align:left"></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align:left">Line</td>
      <td style="text-align:left">Explanation</td>
    </tr>
    <tr>
      <td style="text-align:left">4</td>
      <td style="text-align:left">A different resource so PRU 0 can receive a signal from PRU 1.</td>
    </tr>
    <tr>
      <td style="text-align:left">9-16</td>
      <td style="text-align:left"><code>dmemBuf</code> holds the data to be sent to PRU 1. Each will be transfered
        to its corresponding register by <code>xout()</code>.</td>
    </tr>
    <tr>
      <td style="text-align:left">21-22</td>
      <td style="text-align:left">Define the interupts we&#x2019;re using.</td>
    </tr>
    <tr>
      <td style="text-align:left">27-28</td>
      <td style="text-align:left">Clear the interrupts.</td>
    </tr>
    <tr>
      <td style="text-align:left">31-36</td>
      <td style="text-align:left">Initialize dmemBuf with easy to recognize values.</td>
    </tr>
    <tr>
      <td style="text-align:left">40</td>
      <td style="text-align:left">Wait for PRU 1 to signal.</td>
    </tr>
    <tr>
      <td style="text-align:left">45</td>
      <td style="text-align:left">
        <p><code>__xout()</code> does a direct transfer to PRU 1. Page 92 of <a href="http://www.ti.com/lit/ug/spruhv7b/spruhv7b.pdf">PRU Optimizing C/C++ Compiler, v2.2, User&#x2019;s Guide</a> shows
          how to use <code>xout()</code>. The first argument, 14, says to do a direct
          transfer to PRU 1. If the first argument is 10, 11 or 12, the data is transfered
          to one of three scratchpad memories that PRU 1 can access later.</p>
        <p>The second argument, 5, says to start transfering with register <code>r5</code> and
          use as many regsiters as needed to transfer all of <code>dmemBuf</code>.</p>
        <p>The third argument, 0, says to not use remapping. (See the User&#x2019;s
          Guide for details.)</p>
        <p>The final argument is the data to be transfered.</p>
      </td>
    </tr>
    <tr>
      <td style="text-align:left">48</td>
      <td style="text-align:left">Clear the interupt so it can go again.</td>
    </tr>
  </tbody>
</table>

| Table 4. xin.pru1.c Line-by-line |  |
| :--- | :--- |
| Line | Explanation |
| 8-15 | Place to put the received data. |
| 26 | Signal PRU 0 |
| 30 | Receive the data. The arguments are the same as `xout()`, 14 says to get the data directly from PRU 0. 5 says to start with register `r5`. `dmemBuf` is where to put the data. |

If you really need speed, considering using `__xout()` and `__xin()` in assembly.

## [1.5. Copyright](more-performance.md#_copyright) <a id="_copyright"></a>

copyright.c

```text

  1234567891011121314151617181920212223242526272829303132
```

