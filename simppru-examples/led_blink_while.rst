LED blink using while loop example
==================================

.. image:: images/led_pocket_beagle.png
   :width: 598
   :align: center
   :height: 400
   :alt: LED blink using while loop example

Code
----

.. code:: python

   while : true {
       digital_write(P1_31, true);
       delay(1000);
       digital_write(P1_31, false);
       delay(1000);
   }

-  Following code works on PocketBeagle, to use on other boards, please
   change the pins accordingly.

Explaination
------------

This code runs a never ending while loop, since it is ``while : true``.
Inside ``while`` it sets header pin P1_31 to HIGH, waits for 1000ms,
then sets header pin P1_31 to LOW, then again it waits for 1000ms. This
loop runs endlessly, so we get a Blinking output if one connects a LED

