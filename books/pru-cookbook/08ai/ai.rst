.. _pru-cookbook-ai:

Moving to the BeagleBone AI
############################

So far all our examples have focussed mostly on the BeagleBone Black and Pocket Beagle.
These are both based on the am335x chip.  The new kid on the block is the BeagleBone AI
which is based on the am5729. The new chip brings with it new capabilities one of
which is four PRUs.  This chapter details what changes when moving from two to
four PRUs.

The following are resources used in this chapter.

Resources
~~~~~~~~~~~

* `AM572x Technical Reference Manual <http://www.ti.com/lit/pdf/spruhz6l>`_ (AI)
* `BeagleBone AI PRU pins <https://docs.google.com/spreadsheets/d/1dFSBVem86vAUD7MLXvqdS-N0Efi8_g_O1iTqzql8DAo/edit#gid=0>`_

Moving from two to four PRUs
=============================

Problem
--------

You have code that works on the am335x PRUs and you want to move it to the 
am5729 on the AI.

Solution
--------

Things to consider when moving to the AI are:

* Which pins are you going to use
* Which PRU are you going to run on

Knowing which pins to use impacts the PRU you'll use.

Discission
--------

The various System Reference Manuals (SRM's) list which pins go to the PRUs.
Here the tables are combined into one to make it easier to see what goes where.

.. _aimapping_bits:

Mapping bit positions to pin names
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. table::

	+---+---+---------+-----------+-----------+-------------+
	|PRU|Bit|Black pin|AI PRU1 pin|AI PRU2 pin|Pocket pin	|
	|0  |0  |P9_31    |           |P8_44      |P1.36		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |1  |P9_29    |           |P8_41      |P1.33     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |2  |P9_30    |           |P8_42/P8_21|P2.32     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |3  |P9_28    |P8_12      |P8_39/P8_20|P2.30     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |4  |P9_92    |P8_11      |P8_40/P8_25|P1.31     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |5  |P9_27    |P9_15      |P8_37/P8_24|P2.34     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |6  |P9_91    |           |P8_38/P8_5 |P2.28     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |7  |P9_25    |           |P8_36/P8_6 |P1.29     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |8  |         |           |P8_34/P8_23|     		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |9  |         |           |P8_35/P8_22|     		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |19 |         |           |P8_33/P8_3 |     		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |11 |         |           |P8_31/P8_4 |     		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |12 |         |           |P8_32      |     		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |13 |         |           |P8_45      |     		|
	+---+---+---------+-----------+-----------+-------------+
	|0  |14 |P8_12(out) P8_16(in)||P9_11      |P2.24     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |15 |P8_11(out) P8_15(in)||P8_17/P9_13|P2.33     	|
	+---+---+---------+-----------+-----------+-------------+
	|0  |16 |P9_41(in) P9_26(in)| |P8_27	  |				|
	+---+---+---------+-----------+-----------+-------------+
	|0  |17 |         |P9_26      |P8_28      |				|
	+---+---+---------+-----------+-----------+-------------+
	|0  |18 |         |           |P8_29      |				|
	+---+---+---------+-----------+-----------+-------------+
	|0  |19 |         |           |P8_30      |				|
	+---+---+---------+-----------+-----------+-------------+
	|0  |20 |         |           |P8_46/P8_8 |				|
	+---+---+---------+-----------+-----------+-------------+
	|   |   |         |           |           |             |
	+---+---+---------+-----------+-----------+-------------+
	|1  |0  |P8_45    |           |P8_32      |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |1  |P8_46    |*P9_20*    |           |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |2  |P8_43    |*P9_19*    |           |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |3  |P8_44    |P9_41      |           |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |4  |P8_41    |           |           |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |5  |P8_42    |*P8_18*    |P9_25      |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |6  |P8_39    |*P8_19*    |P8_9       |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |7  |P8_40    |*P8_13*    |P9_31      |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |8  |P8_27    |           |P9_18      |P2.35     	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |9  |P8_29    |P8_14      |P9_17      |P2.01     	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |10 |P8_28    |P9_42      |P9_31      |P1.35     	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |11 |P8_30    |P9_27      |P9_29      |P1.04     	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |12 |P8_21    |           |P9_30      |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |13 |P8_20    |           |P9_26      |          	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |14 |         |P9_14      |P9_42      |P1.32     	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |15 |         |*P9_16*    |P8_10      |P1.30     	|
	+---+---+---------+-----------+-----------+-------------+
	|1  |16 |P9_26(in)|*P8_15*    |P8_7       |     		|
	+---+---+---------+-----------+-----------+-------------+
	|1  |17 |         |*P8_26*    |P8_27      |     		|
	+---+---+---------+-----------+-----------+-------------+
	|1  |18 |         |*P8_16*    |P8_45      |     		|
	+---+---+---------+-----------+-----------+-------------+
	|1  |19 |         |           |P8_46      |     		|
	+---+---+---------+-----------+-----------+-------------+
	|1  |19 |         |           |P8_43      |     		|
	+---+---+---------+-----------+-----------+-------------+

The pins in *bold* are already configured as pru pins.  See :ref:`ai_config` to
see what's currently configured as what.  See :ref:`ai_device_tree` to 
configure pins.

.. _ai_config:

Seeing how pins are configured
===============================

Problem
--------

You want to know how the pins are currently configured.

Solution
---------

The ``show-pins.pl`` command does what you want, but you have to set it up first.

.. code-block:: bash

	bone$ cd ~/bin
	bone$ ln -s /opt/scripts/device/bone/show-pins.pl .

This creates a symbolic link to the ``show-pins.pl`` command that is rather hidden
away.  The link is put in the ``bin`` directory which is in the default command
``$PATH``.  Now you can run ``show-pins.pl`` from anywhere.

.. code-block:: bash

	bone$ *show-pins.pl*
	P9.19a                    16   R6 7 fast rx  up  i2c4_scl
	P9.20a                    17   T9 7 fast rx  up  i2c4_sda
	P8.35b                    57  AD9 e fast    down gpio3_0
	P8.33b                    58  AF9 e fast    down gpio3_1
	...

Here you see ``P9.19a`` and ``P9.20a`` are configured for i2c with pull up resistors.
The ``P8`` pins are configured as gpio with pull down resistors. They are 
both on gpio port 3.  ``P8.35b`` is bit 0 while ``P8.33b`` is bit 1. You can find
which direction they are set by using ``gpioinfo`` and the chip number.  
Unfortunately you subtract one from the port number to get the chip number.
So ``P8.35b`` is on chip number 2.

.. code-block:: bash

	bone$ *gpioinfo 2*
		line   0:      unnamed       unused   *input*  active-high 
		line   1:      unnamed       unused   *input*  active-high 
		line   2:      unnamed       unused   input  active-high 
		line   3:      unnamed       unused   input  active-high 
		line   4:      unnamed       unused   input  active-high 
	...

Here we see both (lines 0 and 1) are set to input.

Adding ``-v`` gives more details.

.. code-block:: bash

	bone$ *show-pins.pl -v*
	...
	sysboot 14                14   H2 f fast    down sysboot14
	sysboot 15                15   H3 f fast    down sysboot15
	P9.19a                    16   R6 7 fast rx  up  i2c4_scl
	P9.20a                    17   T9 7 fast rx  up  i2c4_sda
							18   T6 f fast    down Driver off
							19   T7 f fast    down Driver off
	bluetooth in              20   P6 8 fast rx      uart6_rxd        mmc@480d1000 (wifibt_extra_pins_default)
	bluetooth out             21   R9 8 fast rx      uart6_txd        mmc@480d1000 (wifibt_extra_pins_default)
	...

The best way to use ``show-pins.pl`` is with ``grep``.  To see all the pru pins try:

.. code-block:: bash

	bone$ *show-pins.pl  | grep -i pru | sort*
	P8.13                    100   D3 c fast rx      pr1_pru1_gpi7
	P8.15b                   109   A3 d fast    down pr1_pru1_gpo16
	P8.16                    111   B4 d fast    down pr1_pru1_gpo18
	P8.18                     98   F5 c fast rx      pr1_pru1_gpi5
	P8.19                     99   E6 c fast rx      pr1_pru1_gpi6
	P8.26                    110   B3 d fast    down pr1_pru1_gpo17
	P9.16                    108   C5 d fast    down pr1_pru1_gpo15
	P9.19b                    95   F4 c fast rx  up  pr1_pru1_gpi2
	P9.20b                    94   D2 c fast rx  up  pr1_pru1_gpi1

Here we have nine pins configured for the PRU registers ``R30`` and ``R31``.
Five are input pins and four are out.

.. _ai_device_tree:

Configuring pins on the AI via device trees
============================================

Problem
--------

I want to configure another pin for the PRU, but I get an error.

.. code-block:: bash
		
	bone$ *config-pin P9_31 pruout*
	ERROR: open() for /sys/devices/platform/ocp/ocp:P9_31_pinmux/state failed, No such file or directory

Solution
---------

The pins on the AI must be configure at boot time and therefor cannot be
configured with ``config-pin``.  Instead you must edit the device tree.

Discission
-----------

Suppose you want to make ``P9_31`` a PRU output pin. First go to the
`am5729 System Reference Manual <https://github.com/beagleboard/beaglebone-ai/wiki/System-Reference-Manual#p8.10-p8.13>`_
and look up ``P9_31``.  

.. tip::

	The `BeagleBone AI PRU pins <https://docs.google.com/spreadsheets/d/1dFSBVem86vAUD7MLXvqdS-N0Efi8_g_O1iTqzql8DAo/edit#gid=0>`_
	table may be easier to use.

``P9_31`` appears twice, as ``P9_31a`` and ``P9_31b``. Either should work, let's pick ``P9_31a``.

.. warning::
	When you have two internal pins attached to the same header (either P8 or P9)
	make sure only one is configured as an output.  If both are outputs, you could
	damage the AI.

We see that when ``P9_31a`` is set to ``MODE13`` it will be a PRU **out** pin.  
``MODE12`` makes it a PRU **in** pin.  It appears at bit 10 on PRU2_1.

Next, find which kernel you are running.

.. code-block:: bash
	bone$ uname -a
	Linux ai 4.14.108-ti-r131 #1buster SMP PREEMPT Tue Mar 24 19:18:36 UTC 2020 armv7l GNU/Linux

I'm running the 4.14 version. Now look in ``/opt/source`` for your kernel.

.. code-block:: bash

	bone$ cd /opt/source/
	bone$ ls
	adafruit-beaglebone-io-python  dtb-5.4-ti       rcpy
	BBIOConfig                     librobotcontrol  u-boot_v2019.04
	bb.org-overlays                list.txt         u-boot_v2019.07-rc4
	*dtb-4.14-ti*                    pyctrl
	dtb-4.19-ti                    py-uio

``am5729-beagleboneai.dts`` is the file we need to edit.  Search for ``P9_31``. You'l see:

.. code-block:: bash
	:linenos:

	DRA7XX_CORE_IOPAD(0x36DC, MUX_MODE14) // B13: P9.30: mcasp1_axr10.off //
	DRA7XX_CORE_IOPAD(0x36D4, *MUX_MODE13*) // B12: *P9.31a*: mcasp1_axr8.off //
	DRA7XX_CORE_IOPAD(0x36A4, MUX_MODE14) // C14: P9.31b: mcasp1_aclkx.off //

Change the ``MUX_MODE14`` to ``MUX_MODE13`` for output, or ``MUX_MODE12`` for input.

Compile and install.  The first time will take a while since it recompiles all the dts files.

.. code-block:: bash
	:linenos:

	bone$ make
	...
	DTC     src/arm/am335x-sl50.dtb
	DTC     src/arm/am5729-beagleboneai.dtb
	DTC     src/arm/am335x-nano.dtb
	...
	bone$ sudo make install
	...
	'src/arm/am5729-beagleboneai.dtb' -> '/boot/dtbs/4.14.108-ti-r131/am5729-beagleboneai.dtb'
	...
	bone$ reboot
	...
	bone$ *show-pins.pl -v | sort | grep -i pru*
	P8.13                    100   D3 c fast rx      pr1_pru1_gpi7
	P8.15b                   109   A3 d fast    down pr1_pru1_gpo16
	P8.16                    111   B4 d fast    down pr1_pru1_gpo18
	P8.18                     98   F5 c fast rx      pr1_pru1_gpi5
	P8.19                     99   E6 c fast rx      pr1_pru1_gpi6
	P8.26                    110   B3 d fast    down pr1_pru1_gpo17
	P9.16                    108   C5 d fast    down pr1_pru1_gpo15
	P9.19b                    95   F4 c fast rx  up  pr1_pru1_gpi2
	P9.20b                    94   D2 c fast rx  up  pr1_pru1_gpi1
	P9.31a                   181  B12 d fast    down pr2_pru1_gpo10


There it is.  `P9_31` is now a PRU output pin on PRU1_0, bit 3.

.. _ai_using_pru_pins:

Using the PRU pins
====================

Problem
--------

Once I have the PRU pins configured on the AI how do I use them?

Solution
--------

In :ref:`ai_device_tree` we configured ``P9_31a`` to be a PRU pin.  ``show-pins.pl`` showed
that it appears at ``pr2_pru1_gpo10``, which means pru2_1 accesses it using
bit 10 of register ``R30``.

Discission
--------

It's easy to modify the pwm example from :ref:`blocks_pwm` to use this pin.
First copy the example you want to modify to ``pwm1.pru2_1.c``.  The ``pru2_1`` in
the file name tells the Makefile to run the code on pru2_1.  :ref:`ai_pwm1` shows
the adapted code.

.. _ai_pwm1:

pwm1.pru2_1.c
~~~~~~~~~~~~~~

:download:`pwm1.pru2_1.c <code/pwm1.pru2_1.c>`


One line 6 ``P9_31`` is defined as ``(0x1:ref:`10)``, which means shift ``1`` over by 10 bits.
That's the only change needed.  Copy the local Makefile to the same directory and
compile and run.

.. code-block:: bash
	:linenos:

	bone$ make TARGET=pwm1.pru2_1

Attach an LED to ``P9_31`` and it should be blinking.
