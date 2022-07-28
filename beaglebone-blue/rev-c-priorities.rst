.. _beaglebone-blue-rev-c-updates:

Rev-C updates:
##############

Priorities
===========

-  Update to dual-A53 processor
-  Protect serial ports, QEP and others that could drive inputs while
   power is off (at least 5V tolerance)
-  Switch USB type-microB to USB type-C
-  Add 5Gbps (SS) to USB type-C
-  Add mux to support USB type-C host mode (cable flip support)
-  Perform PD on USB type-C to enable charging when 20V is available,
   drop barrel jack
-  `Move MPU9250 to
   SPI <https://github.com/beagleboard/beaglebone-blue/issues/43>`__
-  Swap out motor connectors
-  Move up to 3S LiPo battery and 12V motors
-  Add support for quad 3-phase motors
-  Add BeagleConnect-compatible subG wireless
-  Add +/- 12V support on ADC
-  Add Pi-compatible CSI connector for camera
-  Add 5GHz WiFi
-  Add PCIe as alt-mode to USB type-C
-  Add RS-485
-  Switch to push-pull microSD card cage
-  Use gold plated pins
-  Power motors when running on USB type-C
-  TODO: Consider 28V 3-phase motors
-  Switch some connectors to Click Shuttle ribbon header
-  Support I3C
-  Support FD-CAN
-  ~Switch to Atheros9K for WiFi~ Consider going with WiLink8 discrete
   and 5GHz
-  On-board audio codec

Wishlist
===========

-  PoE expansion
-  MIDI expansion
-  Multi-channel audio expansion

Features suitable to remove
==============================

-  Bluetooth (not commonly used, whereas BLE and SubG can be more
   useful)
-  2.4GHz WiFi (too much interference)

Example motors to drive
=======================

Brushed DC
----------

-  `DFRobot
   FIT0441 <https://www.digikey.com/product-detail/en/dfrobot/FIT0441/1738-1157-ND/6588579?utm_adgroup=Motors%20-%20AC,%20DC&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Motors,%20Solenoids,%20Driver%20Boards/Modules&utm_term=&utm_content=Motors%20-%20AC,%20DC&gclid=CjwKCAjw26H3BRB2EiwAy32zhVs5Yf-JZ6fIOZlI79NlxhSv1wkXs-ZDEyYi8ZD7XIP9H9fyWHnxQxoCAmEQAvD_BwE>`__
-  `Geartisan 12V
   DC <https://smile.amazon.com/Greartisan-Electric-Reduction-Eccentric-Diameter/dp/B072R5QSRG>`__

3 phase (BLDC, 3 phase stepper, etc.)
-------------------------------------

-  `Moon NEMA 17 3 phase
   stepper <https://www.moonsindustries.com/series/nema-17-smooth-hybrid-stepper-motors-b020302>`__
-  `Primopal NEMA 17 3 phase
   stepper <http://www.primopal.com/web/Product4_GoodsID_25.html>`__ [
   `$6 on
   Alibaba <https://primopal.en.alibaba.com/product/60637037880-811771415/1_2_degree_3_phase_dc_hybrid_china_bipolar_control_step_valve_flat_nema_17_stepper_motor_for_3d_printer_robot_arm_cnc_kit.html>`__
   ]
-  `XXD A2212 KV1000
   BLDC <https://usa.banggood.com/Wholesale-XXD-A2212-KV1000-Brushless-Motor-H363-For-RC-Airplane-Quadcopter-p-57432.html?cur_warehouse=CN>`__
-  `OMC NEMA 23 3 phase
   stepper <https://www.omc-stepperonline.com/3-phase-stepper-motor/p-series-nema-23-1-2deg-3-phase-stepper-motor-5-5a-1nm-141-64oz-in.html>`__

Proposed motor drive circuit
----------------------------

-  Driver: https://www.ti.com/product/DRV8316
-  [STRIKEOUT:Reference design: https://www.ti.com/tool/TIDA-01516]
-  [STRIKEOUT:Gate driver, shunt amp:
   https://www.ti.com/product/DRV8323]
-  [STRIKEOUT:FET pairs (1/2 H-bridge):
   https://www.ti.com/product/CSD87353Q5D]
-  Temperature sensor: https://www.ti.com/product/LM95071

Issues to review
================

-  https://github.com/beagleboard/beaglebone-blue/issues?q=is%3Aissue+is%3Aopen+label%3Afix-in-rev-b
-  https://github.com/beagleboard/beaglebone-blue/issues?q=is%3Aissue+is%3Aopen+label%3Afix-in-rev-c

Integrate feedback from
=======================

-  TAMU - https://mxet.github.io/SCUTTLE/ -
   https://docs.google.com/document/d/1LxO_4hpFQ1i4Vw9NmBai6ByAXrzt0i4g4wozqWoz0x4/edit?usp=sharing
-  GT - https://fis.gatech.edu/multisensor-kit-mechanical-assembly/

GT
--

Blue GT feedback

- 24V DC input option in cabinets
- 24V/12V/5V DC output helpful for sensors
- 4-20mA loop (definitely!)
- ADC (big bottleneck) (brings to NI DAQ level)
- -12V to 12V
- Current measurement (currently rectifying)
   - 12/14-bit is good enough as is SAR max
   - 7/8 channels is good enough
   - Flexible software configuration ideal
   - How much tolerance? (not seen as much more than 12V)
- Enclosure is important
- Look at Automation Direct Productivity Open
- Look at ncd.io
   - Nice to have a block without doing extra jump
   - Wired version would be more determinisitc
      - OPC-UA, etc. when is time 0?
- 5GHz WiFi
   - Better stock WiFi antennas
      - Pi has better?
      - USB dongle did better
   - Better WiFi config
- Better PRU support
   - High-school/undergrad-level
   - Example code and interpreters
- Better support on image management
   - eMMC to microSD
   - Need to advertise it!
- Better community on-boarding
- Build on PRU and ADC advantages over Pi

IoT workshop in November

Review the GT cape

Linear position sensor cape just done

Thoughts on ribbon cables?
