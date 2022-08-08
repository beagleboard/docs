.. _bone-cook-book-parts:

Parts and Suppliers
####################

// Do we really need this?

Parts
----------

The following tables list where you can find the parts used in this book. 
We have listed only one or two sources here, but you can often find a given part in many places.

United States suppliers

.. table::

    +-------------+------------------------------------+------------------------------------+
    | Supplier    | Website                            | Notes                              |
    +=============+====================================+====================================+
    | Adafruit    | http://www.adafruit.com            | Good for modules and parts         |
    +-------------+------------------------------------+------------------------------------+
    | Amazon      | http://www.amazon.com/             | Carries everything                 |
    +-------------+------------------------------------+------------------------------------+
    | Digikey     | http://www.digikey.com/            | Wide range of components           |
    +-------------+------------------------------------+------------------------------------+
    | MakerShed   | http://www.makershed.com/          | Good for modules, kits, and tools  |
    +-------------+------------------------------------+------------------------------------+
    | RadioShack  | http://www.radioshack.com/         | Walk-in stores                     |
    +-------------+------------------------------------+------------------------------------+
    | SeeedStudio | http://www.seeedstudio.com/depot/  | Low-cost modules                   |
    +-------------+------------------------------------+------------------------------------+
    | SparkFun    | http://www.sparkfun.com            | Good for modules and parts         |
    +-------------+------------------------------------+------------------------------------+

Other suppliers

.. table::

    +-----------+----------------------------------+-------------------------------------------------------------------------------------------+
    | Supplier  | Website                          | Notes                                                                                     |
    +===========+==================================+===========================================================================================+
    | Element14 | http://element14.com/BeagleBone  | World-wide BeagleBoard.org-compliant clone of BeagleBone Black, carries many accessories  |
    +-----------+----------------------------------+-------------------------------------------------------------------------------------------+

.. _app_proto:

Prototyping Equipment
-----------------------

Many of the hardware projects in this book use jumper wires and a breadboard. 
We prefer the preformed wires that lie flat on the board. <<parts_jumper>> lists places 
with jumper wires, and <<parts_breadboard>> shows where you can get breadboards.

.. _parts_jumper:

Jumper wires

.. table::

    +-------------+--------------------------------------------------------------------------------------------+
    | Supplier    | Website                                                                                    |
    +=============+============================================================================================+
    | Amazon      | http://www.amazon.com/Elenco-Piece-Pre-formed-Jumper-Wire/dp/B0002H7AIG                    |
    +-------------+--------------------------------------------------------------------------------------------+
    | Digikey     | http://www.digikey.com/product-detail/en/TW-E012-000/438-1049-ND/643115                    |
    +-------------+--------------------------------------------------------------------------------------------+
    | RadioShack  | http://www.radioshack.com/solderless-breadboard-jumper-wire-kit/2760173.html#.VG5i1PnF8fA  |
    +-------------+--------------------------------------------------------------------------------------------+
    | SparkFun    | https://www.sparkfun.com/products/124                                                      |
    +-------------+--------------------------------------------------------------------------------------------+


.. _parts_breadboard:

Breadboards

.. table::

    +-------------+---------------------------------------------------------------------------------------------------------------------------------------------+
    | Supplier    | Website                                                                                                                                     |
    +=============+=============================================================================================================================================+
    | Amazon      | http://www.amazon.com/s/ref=nb_sb_noss_1?url=search-alias%3Dtoys-and-games&field-keywords=breadboards&sprefix=breadboards%2Ctoys-and-games  |
    +-------------+---------------------------------------------------------------------------------------------------------------------------------------------+
    | Digikey     | http://www.digikey.com/product-search/en/prototyping-products/solderless-breadboards/2359510?k=breadboard                                   |
    +-------------+---------------------------------------------------------------------------------------------------------------------------------------------+
    | RadioShack  | http://www.radioshack.com/search?q=breadboard                                                                                               |
    +-------------+---------------------------------------------------------------------------------------------------------------------------------------------+
    | SparkFun    | https://www.sparkfun.com/search/results?term=breadboard                                                                                     |
    +-------------+---------------------------------------------------------------------------------------------------------------------------------------------+
    | CircuitCo   | http://elinux.org/CircuitCo:BeagleBone_Breadboard                                                                                           |
    +-------------+---------------------------------------------------------------------------------------------------------------------------------------------+

If you want something more permanent, try `Adafruit's Perma-Proto Breadboard <https://www.adafruit.com/product/1609>`_, laid out like a breadboard.

.. _app_resistor:

Resistors
----------

We use 220 , 1 k, 4.7 k, 10 k, 20 k, and 22 k resistors in this book. 
All are 0.25 W.  The easiest way to get all these, and many more, is to order `SparkFun's Resistor Kit <http://bit.ly/1EXREh8>`_.  
It's a great way to be ready for future projects, because it has 500 resistors. 
`RadioShack's 500-piece Resistor Assortment <http://shack.net/1B4Io4V>`_ is a bit more 
expensive, but it has a wider variety of resistors.

If you don't need an entire kit of resistors, you can order a la carte from a number of places. 
`RadioShack has 5-packs <http://shack.net/1E5NoIC>`_, and DigiKey has more than a quarter million 
`through-hole resistors <http://bit.ly/1C6WQjZ>`_ at good prices, but make sure you are ordering the right one.

You can find the 10 k trimpot (or variable resistor) at `SparkFun <http://bit.ly/18ACvpm>`_,  
`Adafruit <http://bit.ly/1NKg1Tv>`_, or `RadioShack <http://shack.net/1Ag286e>`_.

Flex resistors (sometimes called *flex sensors* or *bend sensors*) are available at 
`SparkFun <http://bit.ly/1Br7HD2>`_ and `Adafruit <http://bit.ly/1HCGoql>`_.

.. _app_transistor:

Transistors and Diodes
-----------------------

The `2N3904 <http://bit.ly/1B4J8H4>`_ is a common NPN transistor that you can get almost anywhere. 
Even `Amazon <http://amzn.to/1AjvcsD>`_ has it. `Adafruit <http://bit.ly/1b2dgxT>`_ has a nice 10-pack. 
`SparkFun <http://bit.ly/1GrZj5P>`_ lets you buy them one at a time.  `DigiKey <http://bit.ly/1GF8H9K>`_
will gladly sell you 100,000.

The `1N4001 <http://bit.ly/1EbRzF6>`_ is a popular 1A diode. Buy one at `SparkFun <http://bit.ly/1Ajw54G>`_, 
10 at `Adafruit <http://bit.ly/1Gs05zP>`_, 25 at `RadioShack <http://shack.net/1E5OTXi>`_, 
or 40,000 at `DigiKey <http://bit.ly/18ADlT2>`_.

.. _app_ic:

Integrated Circuits
---------------------

The PCA9306 is a small integrated circuit (IC) that converts voltage levels between 3.3 V and 5 V. You can get it 
cheaply in large quantities from `DigiKey <http://bit.ly/1Fb8REd>`_, but it's in a very small, hard-to-use, surface-mount 
package. Instead, you can get it from `SparkFun on a Breakout board <http://bit.ly/19ceTsd>`_, which plugs into a breadboard.

The L293D is an `H-bridge IC <http://bit.ly/1wujQqk>`_ with which you can control large loads (such as motors) in 
both directions.  `SparkFun <http://bit.ly/18bXChR>`_, `Adafruit <http://bit.ly/1xd43Yh>`_, and 
`DigiKey <http://bit.ly/18bXKOk>`_ all have it in a DIP package that easily plugs into a breadboard.

The ULN2003 is a 7 darlington NPN transistor IC array used to drive motors one way. You can get it from  
`DigiKey <http://bit.ly/1D5UQIB>`_. A possible substitution is ULN2803 available from 
`SparkFun <http://bit.ly/1xd4oKy>`_ and `Adafruit <http://bit.ly/1EXWhaU>`_.

The TMP102 is an I^2^C-based digital temperature sensor. You can buy them in bulk from 
`DigiKey <http://bit.ly/1EA02Vx>`_, but it's too small for a breadboard. `SparkFun <http://bit.ly/1GFafAE>`_
sells it on a breakout board that works well with a breadboard.

The DS18B20 is a one-wire digital temperature sensor that looks like a three-terminal transistor. 
Both `SparkFun <http://bit.ly/1Fba7Hv>`_ and `Adafruit <http://bit.ly/1EbSYvC>`_ carry it.

.. _app_opto:

Opto-Electronics
-----------------

`LEDs <http://bit.ly/1BwZvQj>`_ are *light-emitting diodes*. LEDs come in a wide range of colors, 
brightnesses, and styles. You can get a basic red LED at `SparkFun <http://bit.ly/1GFaHPi>`_, 
`Adafuit <http://bit.ly/1GFaH1M>`_, `RadioShack <http://shack.net/1KWVVGE>`_, and `DigiKey <http://bit.ly/1b2f2PD>`_.

Many places carry bicolor LED matrices, but be sure to get one with an I^2^C interface. 
`Adafruit <http://bit.ly/18AENVn>`_ is where I got mine.

.. _app_capes:

Capes
------

There are a number of sources for capes for BeagleBone Black. 
`BeagleBoard.org <http://bit.ly/1AjlXJ9>`_ keeps a current list.


.. _app_misc:

Miscellaneous
--------------

Here are some things that don't fit in the other categories.

.Miscellaneous

.. table::

    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | 3.3 V FTDI cable                                    | `SparkFun  <http://bit.ly/1FMeXsG>`_,                                     |
    |                                                     | `Adafruit <http://bit.ly/18AF1Mm>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | USB WiFi adapter                                    | `Adafruit <http://www.adafruit.com/products/814>`_                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Female HDMI to male microHDMI adapter               | `Amazon <http://amzn.to/1C5BcLp>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | HDMI cable                                          | `SparkFun <https://www.sparkfun.com/products/11572>`_                     |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Micro HDMI to HDMI cable                            | `Adafruit <http://www.adafruit.com/products/1322>`_                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | HDMI to DVI Cable                                   | `SparkFun <https://www.sparkfun.com/products/12612>`_                     |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | HDMI monitor                                        | `Amazon <http://amzn.to/1B4MABD>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Powered USB hub                                     | `Amazon <http://amzn.to/1NKm2zB>`_,                                       |
    |                                                     | `Adafruit <http://www.adafruit.com/products/961>`_                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Keyboard with USB hub                               | `Amazon <http://amzn.to/1FbblSX>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Soldering iron                                      | `SparkFun <http://bit.ly/1FMfUkP>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1EXZ6J1>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Oscilloscope                                        | `Adafruit <https://www.adafruit.com/products/468>`_                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Multimeter                                          | `SparkFun <http://bit.ly/1C5BUbu>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1wXX3np>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | PowerSwitch Tail II                                 | `SparkFun <http://bit.ly/1Ag5bLP>`_,                                      | 
    |                                                     | `Adafruit <http://bit.ly/1wXX8aF>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Servo motor                                         | `SparkFun <http://bit.ly/1C72cvw>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1HCPQdl>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | 5 V power supply                                    | `SparkFun <http://bit.ly/1C72q5C>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/18c0n2D>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | 3 V to 5 V motor                                    | `SparkFun <http://bit.ly/1b2g65Y>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1C72DWF>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | 3 V to 5 V bipolar stepper motor                    | `SparkFun <http://bit.ly/1Bx2hVU>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/18c0HhV>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | 3 V to 5 V unipolar stepper motor                   | `Adafruit <http://www.adafruit.com/products/858>`_                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Pushbutton switch                                   | `SparkFun <http://bit.ly/1AjDf90>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1b2glhw>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Magnetic reed switch                                | `SparkFun <https://www.sparkfun.com/products/8642>`_                      |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | LV-MaxSonar-EZ1 Sonar Range Finder                  | `SparkFun <http://bit.ly/1C73dDH>`_,                                      |
    |                                                     | `Amazon <http://amzn.to/1wXXvlP>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | HC-SR04 Ultrsonic Range Sensor                      | `Amazon <http://amzn.to/1FbcPNa>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Rotary encoder                                      | `SparkFun <http://bit.ly/1D5ZypK>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1D5ZGp3>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | GPS receiver                                        | `SparkFun <http://bit.ly/1EA2sn0>`_,                                      |
    |                                                     | `Adafruit <http://bit.ly/1MrS2VV>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | BLE USB dongle                                      | `Adafruit <http://www.adafruit.com/products/1327>`_                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | SensorTag                                           | `DigiKey <http://bit.ly/18AGPVt>`_,                                       |
    |                                                     | `Amazon <http://amzn.to/1EA2B9U>`_,                                       |
    |                                                     | `TI <https://store.ti.com/CC2541-SensorTag-Development-Kit-P3192.aspx>`_  |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Syba SD-CM-UAUD USB Stereo Audio Adapter            | `Amazon <http://amzn.to/1EA2GdI>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Sabrent External Sound Box USB-SBCV                 | `Amazon <http://amzn.to/1C74kTU>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Vantec USB External 7.1 Channel Audio Adapter       | `Amazon <http://amzn.to/19cinev>`_                                        |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | Nokia 5110 LCD                                      | `Adafruit <http://bit.ly/1Ag6LgG>`_,                                      |
    |                                                     | `SparkFun <http://bit.ly/19cizdu>`_                                       |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | BeagleBone LCD7                                     | `eLinux <http://elinux.org/CircuitCo:BeagleBone_LCD7#Distributors>`_      |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
    | MiniDisplay Cape                                    | `eLinux <http://elinux.org/CircuitCo:MiniDisplay_Cape>`_                  |
    +-----------------------------------------------------+---------------------------------------------------------------------------+
