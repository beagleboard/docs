.. _pru-cookbook-details:

Running a Program; Configuring Pins
####################################

There are a lot of details in compiling and running PRU code.
Fortunately those details are captured in a common `Makefile` that is
used througout this book. This chapter shows how to use the `Makefile` to 
compile code and also start and stop the PRUs.

The following are resources used in this chapter.

.. note::
   * `PRU Code Generation Tools - Compiler <http://software-dl.ti.com/codegen/esd/cgt_ai_64_lic_sw/PRU/2.1.5/ti_cgt_pru_2.1.5_armlinuxa8hf_busybox_installer.sh>`_
   * `PRU Software Support Package <http://git.ti.com/pru-software-support-package>`_
   * `PRU Optimizing C/C++ Compiler <http://www.ti.com/lit/ug/spruhv7b/spruhv7b.pdf>`_
   * `PRU Assembly Language Tools <http://www.ti.com/lit/ug/spruhv6b/spruhv6b.pdf>`_
   * `AM572x Technical Reference Manual <http://www.ti.com/lit/pdf/spruhz6l>`_ (AI)
   * `AM335x Technical Reference Manual <http://www.ti.com/lit/pdf/spruh73>`_ (All others)

Getting Example Code
=====================

Problem
---------

I want to get the files used in this book.

Solution
---------

It's all on a GitHub repository.

.. code-block:: bash

    bone$ git clone https://github.com/MarkAYoder/PRUCookbook.git


.. note::
   #TODO#: There needs to be a code-only repo that is validated against the documentation
   code to be identical for specific version. The version needs to be noted in the
   documentation.


Compiling with clpru and lnkpru
================================


Problem
---------

You need details on the c compiler, linker and other tools for the PRU.

Solution
---------

The PRU compiler and linker are already installed on many images.
They are called ``clpru`` and ``lnkpru``.  Do the following to see if ``clpru`` is installed.

.. code-block:: bash

    bone$ which clpru
    /usr/bin/clpru

.. tip::
    If ``clpru`` isn't installed, follow the instructions at
    https://elinux.org/Beagleboard:BeagleBoneBlack_Debian#TI_PRU_Code_Generation_Tools
    to install it.

.. code-block:: bash

    bone$ sudo apt update
    bone$ sudo apt install ti-pru-cgt-installer


Details on each can be found here:

* `PRU Optimizing C/C++ Compiler <http://www.ti.com/lit/ug/spruhv7b/spruhv7b.pdf>`_
* `PRU Assembly Language Tools <http://www.ti.com/lit/ug/spruhv6b/spruhv6b.pdf>`_

In fact there are PRU versions of many of the standard code generation tools.

code tools
~~~~~~~~~~~
.. code-block:: bash

    bone$ ls /usr/bin/*pru
    /usr/bin/abspru    /usr/bin/clistpru  /usr/bin/hexpru      /usr/bin/ofdpru
    /usr/bin/acpiapru  /usr/bin/clpru     /usr/bin/ilkpru      /usr/bin/optpru
    /usr/bin/arpru     /usr/bin/dempru    /usr/bin/libinfopru  /usr/bin/rc_test_encoders_pru
    /usr/bin/asmpru    /usr/bin/dispru    /usr/bin/lnkpru      /usr/bin/strippru
    /usr/bin/cgpru     /usr/bin/embedpru  /usr/bin/nmpru       /usr/bin/xrefpru

See the `PRU Assembly Language Tools <http://www.ti.com/lit/ug/spruhv6b/spruhv6b.pdf>`_ for more details.

Making sure the PRUs are configured
====================================

Problem
---------

When running the Makefile for the PRU you get and error about ``/dev/remoteproc`` is missing.

Solution
---------

Edit ``/boot/uEnv.txt`` and enble pru_rproc by doing the following.

.. code-block:: bash

    bone$ *sudo vi /boot/uEnv.txt*

Around line 40 you will see:

.. code-block:: bash

    ###pru_rproc (4.19.x-ti kernel)
    uboot_overlay_pru=AM335X-PRU-RPROC-4-19-TI-00A0.dtbo

Uncomment the ``uboot_overlay`` line as shown and then reboot.
``/dev/remoteproc`` should now be there.

.. code-block:: bash

    bone$ sudo reboot
    bone$ ls -ls /dev/remoteproc/
    total 0
    0 lrwxrwxrwx 1 root root 33 Jul 29 16:12 pruss-core0 -> /sys/class/remoteproc/remoteproc1
    0 lrwxrwxrwx 1 root root 33 Jul 29 16:12 pruss-core1 -> /sys/class/remoteproc/remoteproc2

Compiling and Running
======================

Problem
---------

I want to compile and run an example.

Solution
---------

Change to the directory of the code you want to run.

.. code-block:: bash

    bone$ cd PRUCookbook/docs/06io/code
    bone$ ls
    gpio.pru0.c  Makefile  setup.sh

Source the setup file.

.. code-block:: bash

    bone$ source setup.sh
    TARGET=gpio.pru0
    PocketBeagle Found
    P2_05
    Current mode for P2_05 is:     gpio
    Current mode for P2_05 is:     gpio

Now you are ready to compile and run.  This is automated for you in the Makefile

.. code-block:: bash

    bone$ make
    /var/lib/cloud9/common/Makefile:28: MODEL=TI_AM335x_BeagleBone_Black,TARGET=gpio.pru0,COMMON=/var/lib/cloud9/common
    /var/lib/cloud9/common/Makefile:147: GEN_DIR=/tmp/cloud9-examples,CHIP=am335x,PROC=pru,PRUN=0,PRU_DIR=/sys/class/remoteproc/remoteproc1,EXE=.out
    -    Stopping PRU 0
    /bin/sh: 1: echo: echo: I/O error
    Cannot stop 0
    CC	gpio.pru0.c
    "/var/lib/cloud9/common/prugpio.h", line 53: warning #1181-D: #warning directive: "Found am335x"
    LD	/tmp/cloud9-examples/gpio.pru0.o
    -	copying firmware file /tmp/cloud9-examples/gpio.pru0.out to /lib/firmware/am335x-pru0-fw
    write_init_pins.sh
    writing "out" to "/sys/class/gpio/gpio30/direction"
    -    Starting PRU 0
    MODEL   = TI_AM335x_BeagleBone_Black
    PROC    = pru
    PRUN    = 0
    PRU_DIR = /sys/class/remoteproc/remoteproc1
    rm /tmp/cloud9-examples/gpio.pru0.o

Congratulations, your are now running a PRU.  If you have an LED attached to
``P9_11`` on the Black, or ``P2_05`` on the Pocket, it should be blinking.

Discussion
------------

The ``setup.sh`` file sets the ``TARGET`` to the file you want to compile.
Set it to the filename, without the ``.c`` extension (``gpio.pru0``).
The file extension ``.pru0`` specifies the number of the PRU you are using 
(either ``1_0``, ``1_1``, ``2_0``, ``2_1`` on the AI or ``0`` or ``1`` on the others)

You can override the ``TARGET`` on the command line.

.. code-block:: bash

    bone$ cp gpio.pru0.c gpio.pru1.c
    bone$ export TARGET=gpio.pru1

Notice the ``TARGET`` doesn't have the ``.c`` on the end.

You can also specify them when running ``make``.
.. code-block:: bash

    bone$ cp gpio.pru0.c gpio.pru1.c
    bone$ make TARGET=gpio.pru1

The setup file also contains instructions to figure out which Beagle you are running
and then configure the pins acordingly.

setup.sh
~~~~~~~~~

:download:`gpio_setup.sh <code/gpio_setup.sh>`

.. table::

    +-----+---------------------------------------------------+
    |Line | Explanation                                       |
    +=====+===================================================+
    |2-5  | Set which PRU to use and which file to compile.   |
    +-----+---------------------------------------------------+
    |7    | Figure out which type of Beagle we have.          |
    +-----+---------------------------------------------------+
    |9-21 | Based on the type, set the `pins`.                |
    +-----+---------------------------------------------------+
    |23-28| Configure (set the pin mux) for each of the pins. |
    +-----+---------------------------------------------------+

.. tip::

    The BeagleBone AI has it's pins preconfigured at boot time, so there's no
    need to use ``config-pin``.


The ``Makefile`` stops the PRU, compiles the file and moves it where it will 
be loaded, and then restarts the PRU.

Stopping and Starting the PRU
==============================

Problem
---------

I want to stop and start the PRU.

Solution
---------

It's easy, if you already have ``TARGET`` set up:

.. code-block:: bash

    bone$ make stop
    -    Stopping PRU 0
    stop
    bone$ make start
    -    Starting PRU 0
    start

See :ref:`_dmesg_hw` to see how to tell if the PRU
is stopped.

This assumes ``TARGET`` is set to the PRU you are using.
If you want to control the other PRU use:

.. code-block:: bash

    bone$ cp gpio.pru0.c gpio.pru1.c
    bone$ make TARGET=gpio.pru1
    bone$ make TARGET=gpio.pru1 stop
    bone$ make TARGET=gpio.pru1 start


.. _details_makefile:

The Standard Makefile
=====================

Problem
---------

There are all sorts of options that need to be set when compiling
a program.  How can I be sure to get them all right?

Solution
---------

The surest way to make sure everything is right is to use our
standard ``Makefile``.

Discussion
-----------

It's assumed you already know how Makefiles work.  If not, there are
many resources online that can bring you up to speed.
Here is the local ``Makefile`` used throughout this book.

Local Makefile
~~~~~~~~~~~~~~~

:download:`Makefile <code/Makefile>`

Each of the local Makefiles refer to the same standard Makefile. The details
of how the Makefile works is beyond the scope of this cookbook.

Fortunately you shouldn't have to modify the `Makefile`.

.. _detail_linker:

The Linker Command File - am335x_pru.cmd
=========================================


Problem
---------

The linker needs to be told where in memory to place the code and variables.

Solution
---------

``am335x_pru.cmd`` is the standard linker command file that tells the linker
where to put what for the BeagleBone Black and Blue, and the Pocket. 
The ``am57xx_pru.cmd`` does the same for the AI.
Both files can be found in ``/var/lib/cloud9/common``.

am335x_pru.cmd
~~~~~~~~~~~~~~~~

:download:`am335x_pru.cmd <code/am335x_pru.cmd>`

.. TODO does  this need updating?

The cmd file for the AI is about the same, with appropriate addresses for the AI.

Discussion
-----------


The important things to notice in the file are given in the following table.

AM335x_PRU.cmd important things
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. table::

    +-----+-----------------------------------------------------------------------------------------+
    |Line | Explanation                                                                             |
    +=====+=========================================================================================+
    |16   | This is where the instructions are stored. See page 206 of the                          |
    |     | `AM335x Technical Reference Manual <https://www.ti.com/lit/ug/spruh73p/spruh73p.pdf>`_  |
    |     | Or see page 417 of                                                                      |
    |     | `AM572x Technical Reference Manual <http://www.ti.com/lit/pdf/spruhz6l>`_ for the AI.   |
    +-----+-----------------------------------------------------------------------------------------+
    |22   | This is where PRU 0's DMEM 0 is mapped.  It's also where PRU 1's                        |
    |     | DMEM 1 is mapped.                                                                       |
    +-----+-----------------------------------------------------------------------------------------+
    |23   | The reverse to above.  PRU 0's DMEM 1 appears here and PRU 1's DMEM 0                   |
    |     | is here.                                                                                |
    +-----+-----------------------------------------------------------------------------------------+
    |26   | The shared memory for both PRU's appears here.                                          |
    +-----+-----------------------------------------------------------------------------------------+
    |72   | The `.text` section is where the code goes.  It's mapped to `IMEM`                      |
    +-----+-----------------------------------------------------------------------------------------+
    |73   | The ((stack)) is then mapped to DMEM 0. Notice that DMEM 0 is one bank                  |
    +-----+-----------------------------------------------------------------------------------------+
    |     | of memory for PRU 0 and another for PRU1, so they both get their own stacks.            |
    +-----+-----------------------------------------------------------------------------------------+
    |74   | The `.bss` section is where the **heap** goes.                                          |
    +-----+-----------------------------------------------------------------------------------------+

Why is it important to understand this file?  If you are going to store things
in DMEM, you need to be sure to start at address 0x0200 since the **stack** and 
the **heap** are in the locations below 0x0200.

Loading Firmware
==================

Problem
---------

I have my PRU code all compiled and need to load it on the PRU.

Solution
---------

It's a simple three step process.

* Stop the PRU
* Write the ``.out`` file to the right place in ``/lib/firmware``
* Start the PRU.

This is all handled in the :ref:`details_makefile`.

Discussion
-----------


The PRUs appear in the Linux file space at ``/dev/remoteproc/``.

Finding the PRUs
~~~~~~~~~~~~~~~~~~~

.. code-block:: bash

    bone$ cd /dev/remoteproc/
    bone$ ls
    pruss-core0  pruss-core1

Or if you are on the AI:

.. code-block:: bash

    bone$ cd /dev/remoteproc/
    bone$ ls
    dsp1  dsp2  ipu1  ipu2  pruss1-core0  pruss1-core1  pruss2-core0  pruss2-core1

You see there that the AI has two pairs of PRUs, plus a couple of DSPs and other goodies.

Here we see PRU 0 and PRU 1 in the path.  Let's follow PRU 0.

.. code-block:: bash

    bone$ cd pruss-core0
    bone$ ls
    device  firmware  name  power  state  subsystem  uevent

Here we see the files that control PRU 0.  ``firmware`` tells where in ``/lib/firmware``
to look for the code to run on the PRU.

.. code-block:: bash

    bone$ cat firmware
    am335x-pru0-fw

Therefore you copy your ``.out`` file to ``/lib/firmware/am335x-pru0-fw``.

.. _details_configure_servos:

Configuring Pins for Controlling Servos
========================================

Problem
---------

You want to **configure** the pins so the PRU outputs are accessable.

Solution
---------

It depends on which Beagle you are running on.  If you are on the AI or Blue, 
everything is already configured for you.
If you are on the Black or Pocket you'll need to run the following script.

servos_setup.sh
~~~~~~~~~~~~~~~~

:download:`servos_setup.sh <code/servos_setup.sh>`

Discussion
-----------

The first part of the code looks in ``/proc/device-tree/model`` to see which Beagle is running. Based on that it
assigns ``pins`` a list of pins to configure.  Then the last part of the script loops through each of the pins and configures it.


.. _details_configure_encoders:

Configuring Pins for Controlling Encoders
==========================================

Problem
---------

You want to **configure** the pins so the PRU inputs are accessable.

Solution
---------

It depends on which Beagle you are running on.  If you are on the AI or Blue, 
everything is already configured for you.
If you are on the Black or Pocket you'll need to run the following script.

.encoder_setup.sh

:download:`encoder_setup.sh <code/encoder_setup.sh>`

Discussion
-----------

This works like the servo setup except some of the pins are configured as 
to the hardware eQEPs and other to the PRU inputs.

