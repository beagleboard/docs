QWIIC, STEMMA and Grove on Linux
################################

.. note::

   This article is under construction.

I'm creating a place for me to start taking notes on how to load drivers for I2C devices (mostly), but also other Grove add-ons.

For simplicity sake, I'll use these definitions

* **add-on**: the QWIIC, STEMMA (QT) or Grove add-on separate from your Linux computer
* **device**: the "smart" IC on the add-on to which we will interface from your Linux computer
* **board**: the Linux single board computer with the embedded interface controller you are using
* **module**: a kernel module that might contain the driver

I2C
***

Linux has a ton of drivers for I2C devices. We just need a few parameters to load them.

Using a Linux I2C kernel driver module can be super simple, like in the below example for
monitoring a digital light sensor.

.. code-block:: bash

  cd /sys/bus/i2c/devices/i2c-1
  echo tsl2561 0x29 > new_device
  watch -n0 cat "1-0029/iio:device0/in_illuminance0_input"

Once you issue this, your screen continuously refresh with luminance values from the
add-on sensor.

In the above example, `/sys/bus/i2c/devices/i2c-1` comes from which I2C controller
we are using on the board and there are specific pins on the board where you can
access it.

`tsl2561` is the name of the driver we want to load and `0x29` is the address of the
device on the I2C bus. If you want to know about I2C device addresses, the
`Sparkfun I2C tutorial <https://learn.sparkfun.com/tutorials/i2c>`__ isn't a bad
place to start. The `new_device` virtual file is documented in the
`Linux kernel documentation on instantiating I2C devices <https://www.kernel.org/doc/html/v5.19/i2c/instantiating-devices.html>`__.

On the last line, `watch <https://manpages.debian.org/bullseye/procps/watch.1.en.html>`__
is a program that will repeatedly run the command that follows. The `-n0` sets the refresh 
rate. The program `cat <https://manpages.debian.org/bullseye/coreutils/cat.1.en.html>`__
will share the contents of the file `1-0029/iio\:device0/in_illuminance0_input`.

`1-0029/iio:device0/in_illuminance0_input` is not a file on a disk, but output directly
from the driver. The 1 in `1-0029` represents the I2C controller index. The `0029`
represents the device I2C address. Most small sensor and actuator drivers will show up as
`Industrial I/O (IIO) devices <https://www.kernel.org/doc/html/v5.19/driver-api/iio/index.html>`__.
New IIO devices get incrementing indexes. In this case, `iio:device0` is the first IIO device
driver loaded. Finally, `in_illuminance0_input` comes from the
`SYSFS <https://www.kernel.org/doc/html/v5.19/filesystems/sysfs.html>`__ 
`application binary interface <https://www.kernel.org/doc/html/v5.19/admin-guide/abi.html>`__
for this type of device, a light sensor. The
`Linux kernel ABI documentation for sysfs-bus-iio <https://www.kernel.org/doc/html/v5.19/admin-guide/abi-testing.html#abi-sys-iio-devicex-in-illuminance-input>`__ provides the definition of available data often provided by light sensor drivers.

.. code-block::

  What:		/sys/.../iio:deviceX/in_illuminance_input
  What:		/sys/.../iio:deviceX/in_illuminance_raw
  What:		/sys/.../iio:deviceX/in_illuminanceY_input
  What:		/sys/.../iio:deviceX/in_illuminanceY_raw
  What:		/sys/.../iio:deviceX/in_illuminanceY_mean_raw
  What:		/sys/.../iio:deviceX/in_illuminance_ir_raw
  What:		/sys/.../iio:deviceX/in_illuminance_clear_raw
  KernelVersion:	3.4
  Contact:	linux-iio@vger.kernel.org
  Description:
		Illuminance measurement, units after application of scale
		and offset are lux.

Read further to discover how to find these bits of magic text used above.

Loading the Linux driver
========================

The generic steps are fairly simple:

1. Identify the name and address used to load the appropriate driver for your add-on
2. Ensure the driver is included in your kernel build
3. Identify the location of the I2C signals on the board and the controller link in Linux
4. Ensure the board pinmux is set properly to expose the I2C peripheral
5. Ensure the board to add-on connection is good
6. Issue the Linux command to load the driver
7. Identify and utilize the interface provided by the driver

Driver name
-----------

One resource that is very helpful is the list that Vaishnav put together for supporting
Mikroelektronika Click add-ons. His `list of Click add-ons with driver information <https://git.beagleboard.org/jkridner/manifesto/-/blob/main/click_info.csv>`__ can help a lot with matching
a device to the driver name, device address, and kernel configuration setting.

.. note::

  Documentation for your particular add-on might indicate a different device address than is
  configured on Click add-ons.

I'm not aware of a trivial way of discovering the mapping that Vaishnav created outside
of looking at the kernel sources. As an example, let's look at the 
`Grove Digital Light Sensor add-on <https://wiki.seeedstudio.com/Grove-Digital_Light_Sensor/>`__ 
which is documented to utilize a TSL2561.

Searching through the kernel sources, we can find the driver code at
`drivers/iio/light/tsl2563.c`. There is a list of driver names in a
`i2c_device_id table <https://elixir.bootlin.com/linux/v5.19.5/source/drivers/iio/light/tsl2563.c#L862>`__:

.. code-block::

  static const struct i2c_device_id tsl2563_id[] = {
  	{ "tsl2560", 0 },
  	{ "tsl2561", 1 },
  	{ "tsl2562", 2 },
  	{ "tsl2563", 3 },
  	{}
  };

.. important::

  Don't miss that the driver is a superset (tsl253) 


Kernel configuration
--------------------

Devices
=======

.. note::

  There are some great resources out there:

  * `Adafruit list of I2C devices <https://learn.adafruit.com/i2c-addresses/the-list>`__
  * `Sparkfun list of QWIIC devices <https://www.sparkfun.com/qwiic>`__
  * `Adafruit STEMMA QT introduction <https://learn.adafruit.com/introducing-adafruit-stemma-qt/sparkfun-qwiic>`__


Pitfalls
========

Not all I2C devices with drivers in the Linux kernel can be loaded this way. The most common
reason is that the device driver expects an interrupt signal or other GPIO along with the I2C
communication. In these cases, a device tree overlay or driver modification may be necessary.
