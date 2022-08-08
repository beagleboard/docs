Digital read example
====================

.. image:: images/led_button_pocket_beagle.png
   :width: 598
   :align: center
   :height: 400
   :alt: Digital read example

Code
----

.. code:: python

   while : true {
       if : digital_read(P1_29) {
           digital_write(P1_31, false);
       }
       else {
           digital_write(P1_31, true);
       }
   }

-  Following code works on PocketBeagle, to use on other boards, please
   change the pins accordingly.

Explaination
------------

This code runs a never ending loop, since it is ``while : true``. Inside
``while`` it checks if header pin P1_29 is HIGH or LOW. If header pin
P1_29 is HIGH, header pin P1_31 is set to LOW, and if header pin P1_29
is LOW, header pin P1_31 is set to HIGH.

