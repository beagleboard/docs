# Accessing More I/O

So far the examples have shown how to access the GPIO pins on the BeagleBone Black’s `P9` header and through the `__R30` register. Below shows how more GPIO pins can be accessed.

The following are resources used in this chapter.

### [Problem](accessing-more-i-o.md#_problem) <a id="_problem"></a>

When I try to configure some pins on the `P8` header of the Black I get an error.

config-pin

```text
bone$ config-pin P8_28 pruout
ERROR: open() for /sys/devices/platform/ocp/ocp:P8_28_pinmux/state failed, No such file or directory
```

### [Solution](accessing-more-i-o.md#_solution) <a id="_solution"></a>

On the images for the BeagleBone Black, the HDMI display driver is enabled by default and uses many of the `P8` pins. If you are not using HDMI video \(or the HDI audio, or even the eMMC\) you can disable it by editing `/boot/uEnv.txt`

Open `/boot/uEnv.txt` and scroll down aways until you see:

/boot/uEnv.txt

```text
###Disable auto loading of virtual capes (emmc/video/wireless/adc)
#disable_uboot_overlay_emmc=1
disable_uboot_overlay_video=1
#disable_uboot_overlay_audio=1
```

Uncomment the lines that correspond to the devices you want to disable and free up their pins.

Save the file and reboot. You now have access to the `P8` pins.

## [1.2. Accessing gpio](accessing-more-i-o.md#_accessing_gpio) <a id="_accessing_gpio"></a>

### [Problem](accessing-more-i-o.md#_problem_2) <a id="_problem_2"></a>

I’ve used up all the GPIO in `__R30`, where can I get more?

### [Solution](accessing-more-i-o.md#_solution_2) <a id="_solution_2"></a>

So far we have focused on using PRU 0. [Mapping bit positions to pin names PRU](https://markayoder.github.io/PRUCookbook/05blocks/blocks.html.html#blocks_mapping_bits) shows that PRU 0 can access ten GPIO pins on the BeagleBone Black. If you use PRU 1 you can get to an additional 14 pins \(if they aren’t in use for other things.\)

What if you need even more GPIO pins? You can access _any_ GPIO pin by going through the **o**ne **c**hip **p**eripheral \(OCP\) port.

PRU Integration

The figure above shows we’ve been using the _Enhanced GPIO_ interface when using `__R30`, but it also shows you can use the OCP. You get access to many more GPIO pins, but it’s a slower access.

gpio.pru0.c

```text

  12345678910111213141516171819202122#include #include #include "resource_table_empty.h"#include "prugpio.h"#define P9_11   (0x1<<30)           volatile register uint32_t __R30;volatile register uint32_t __R31;void main(void){    uint32_t *gpio0 = (uint32_t *)GPIO0;    while(1) {        gpio0[GPIO_SETDATAOUT]   = P9_11;        __delay_cycles(100000000);        gpio0[GPIO_CLEARDATAOUT] = P9_11;        __delay_cycles(100000000);    }}
```

This code will toggle `P9_11` on and off. Here’s the setup file.

setup.sh

```text

  12345678910111213141516171819202122232425262728#!/bin/bashexport TARGET=gpio.pru0echo TARGET=$TARGET# Configure the PRU pins based on which Beagle is runningmachine=$(awk '{print $NF}' /proc/device-tree/model)echo -n $machineif [ $machine = "Black" ]; then    echo " Found"    pins="P9_11"elif [ $machine = "Blue" ]; then    echo " Found"    pins=""elif [ $machine = "PocketBeagle" ]; then    echo " Found"    pins="P1_36"else    echo " Not Found"    pins=""fifor pin in $pinsdo    echo $pin    config-pin $pin out    config-pin -q $pindone
```

Notice in the code `config-pin` set `P9_11` to `gpio`, not `pruout`. This is because are are using the OCP interface to the pin, not the usual PRU interface.

Set your exports and make.

```text
bone$ source setup.sh
TARGET=gpio.pru0
...
bone$ make
/var/lib/cloud9/common/Makefile:29: MODEL=TI_AM335x_BeagleBone_Black,TARGET=gpio.pru0
-    Stopping PRU 0
-   copying firmware file /tmp/cloud9-examples/gpio.pru0.out to /lib/firmware/am335x-pru0-fw
write_init_pins.sh
-    Starting PRU 0
MODEL   = TI_AM335x_BeagleBone_Black
PROC    = pru
PRUN    = 0
PRU_DIR = /sys/class/remoteproc/remoteproc1
```

### [Discussion](accessing-more-i-o.md#_discussion) <a id="_discussion"></a>

When you run the code you see `P9_11` toggling on and off. Let’s go through the code line-by-line to see what’s happening.

<table>
  <thead>
    <tr>
      <th style="text-align:left">Table 1. gpio.pru0.c line-by-line</th>
      <th style="text-align:left"></th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align:left">Line</td>
      <td style="text-align:left">Explanation</td>
    </tr>
    <tr>
      <td style="text-align:left">2-5</td>
      <td style="text-align:left">Standard includes</td>
    </tr>
    <tr>
      <td style="text-align:left">5</td>
      <td style="text-align:left">
        <p>The AM335x has four 32-bit GPIO ports. Lines 55-58 of <code>prugpio.h</code> define
          the addresses for each of the ports. You can find these in Table 2-2 page
          180 of the <a href="https://www.ti.com/lit/ug/spruh73p/spruh73p.pdf">AM335x Technical Reference Manual</a>.
          Look up <code>P9_11</code> in the <a href="https://github.com/derekmolloy/exploringBB/blob/master/chp06/docs/BeagleboneBlackP9HeaderTable.pdf">P9 Header Table</a>.
          Under the <em>Mode7</em> column you see <code>gpio0[30]</code>. This means <code>P9_11</code> is
          bit 30 on GPIO port 0. Therefore we will use <code>GPIO0</code> in this code.</p>
        <p>You can also run <code>gpioinfo</code> and look for P9_11.</p>
      </td>
    </tr>
    <tr>
      <td style="text-align:left">5</td>
      <td style="text-align:left">Line 105 of <code>prugpio.h</code> defines the address offset from <code>GIO0</code> that
        will allow us to <em>clear</em> any (or all) bits in GPIO port 0. Other architectures
        require you to read a port, then change some bit, then write it out again,
        three steps. Here we can do the same by writing to one location, just one
        step.</td>
    </tr>
    <tr>
      <td style="text-align:left">5</td>
      <td style="text-align:left">Line 106 of <code>prugpio.h</code> is like above, but for <em>setting</em> bits.</td>
    </tr>
    <tr>
      <td style="text-align:left">5</td>
      <td style="text-align:left">Using this offset of line 107 of <code>prugpio.h</code> lets us just read
        the bits without changing them.</td>
    </tr>
    <tr>
      <td style="text-align:left">7</td>
      <td style="text-align:left">This shifts <code>0x1</code> to the 30th bit position, which is the one
        corresponding to <code>P9_11</code>.</td>
    </tr>
    <tr>
      <td style="text-align:left">14</td>
      <td style="text-align:left">Here we initialize <code>gpio0</code> to point to the start of GPIO port
        0&#x2019;s control registers.</td>
    </tr>
    <tr>
      <td style="text-align:left">17</td>
      <td style="text-align:left"><code>gpio0[GPIO_SETDATAOUT]</code> refers to the <code>SETDATAOUT</code> register
        of port 0. Writing to this register turns on the bits where 1&#x2019;s
        are written, but leaves alone the bits where 0&#x2019;s are.</td>
    </tr>
    <tr>
      <td style="text-align:left">18</td>
      <td style="text-align:left">Wait 100,000,000 cycles, which is 0.5 seconds.</td>
    </tr>
    <tr>
      <td style="text-align:left">19</td>
      <td style="text-align:left">This is line 17, but the output bit is set to 0 where 1&#x2019;s are written.</td>
    </tr>
  </tbody>
</table>

#### [How fast can it go?](accessing-more-i-o.md#_how_fast_can_it_go) <a id="_how_fast_can_it_go"></a>

This approach to GPIO goes through the slower OCP interface. If you set `__delay_cycles(0)` you can see how fast it is.

gpio.pru0.c with \_\_delay\_cycles\(0\)

The period is 80ns which is 12.MHz. That’s about one forth the speed of the `__R30` method, but still not bad.

If you are using an oscilloscope, look closely and you’ll see the following.

PWM with jitter

The PRU is still as solid as before in it’s timing, but now it’s going through the OCP interface. This interface is shared with other parts of the system, therefore the sometimes the PRU must wait for the other parts to finish. When this happens the pulse width is a bit longer than usual thus adding jitter to the output.

For many applications a few nanoseconds of jitter is unimportant and this GPIO interface can be used. If your application needs better timing, use the `__R30` interface.

## [1.3. Configuring for UIO Instead of RemoteProc](accessing-more-i-o.md#io_uio) <a id="io_uio"></a>

### [Problem](accessing-more-i-o.md#_problem_3) <a id="_problem_3"></a>

You have some legacy PRU code that uses UIO instead of remoteproc and you want to switch to UIO.

### [Solution](accessing-more-i-o.md#_solution_3) <a id="_solution_3"></a>

Edit `/boot/uEnt.txt` and search for `uio`. I find

```text
###pru_uio (4.4.x-ti, 4.9.x-ti, 4.14.x-ti & mainline/bone kernel)
uboot_overlay_pru=/lib/firmware/AM335X-PRU-UIO-00A0.dtbo
```

Uncomment the `uboot` line. Look for other lines with `uboot_overlay_pru=` and be sure they are commented out.

Reboot your Bone.

Check that UIO is running.

```text
bone$ lsmod | grep uio
uio_pruss              16384  0
uio_pdrv_genirq        16384  0
uio                    20480  2 uio_pruss,uio_pdrv_genirq
```

You are now ready to run the legacy PRU code.

