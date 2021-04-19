# Case Studies - Introduction

## [Solution](case-studies-introduction.md#_solution_7) <a id="_solution_7"></a>

```text
LEDscape is a library and service for controlling individually addressable LEDs from a Beagle Bone Black or Beagle Bone Green using the onboard PRUs. It currently supports WS281x (WS2811, WS2812, WS2812b), WS2801 and initial support for DMX.

It can support up to 48 connected strings and can drive them with very little load on the main processor.

Background
LEDscape was originally written by Trammell Hudson (http://trmm.net/Category:LEDscape) for controlling WS2811-based LEDs. Since his original work, his version (https://github.com/osresearch/LEDscape) has been repurposed to drive a different type of LED panel (e.g. http://www.adafruit.com/products/420).

This version of the library was forked from his original WS2811 work. Various improvements have been made in the attempt to make an accessible and powerful LED driver based on the BBB. Many thanks to Trammell for his excellent work in scaffolding the BBB and PRUs for driving LEDs.
```

 — https://github.com/Yona-Appletree/LEDscape

LEDscape can drive 48 strings of LEDs that are arbitary length with no addional hardware! Here’s how to install it.

| Note | This has only been tested on the BeagleBone Black. |
| :--- | :--- |


First install LEDscape and openpixelcontrol.

```text
bone$ git clone https://github.com/Yona-Appletree/LEDscape.git
bone$ git clone https://github.com/zestyping/openpixelcontrol
```

Next find which channels are on which pins

```text
bone$ node LEDscape/pru/pinmap.js
Using mapping: Original LEDscape from original-ledscape
                       Internal Channel Index
 Row  Pin#           P9            Pin#  |  Pin#           P8            Pin# Row
  1    1                            2    |   1                            2    1
  2    3                            4    |   3                            4    2
  3    5                            6    |   5                            6    3
  4    7                            8    |   7       25          26       8    4
  5    9                            10   |   9       28          27       10   5
  6    11      13          23       12   |   11      16          15       12   6
  7    13      14          21       14   |   13      10          11       14   7
  8    15      19          22       16   |   15      18          17       16   8
  9    17                           18   |   17      12          24       18   9
  10   19                           20   |   19       9                   20   10
  11   21       1           0       22   |   21                           22   11
  12   23      20                   24   |   23                           24   12
  13   25                   7       26   |   25                           26   13
  14   27                  47       28   |   27      41                   28   14
  15   29      45          46       30   |   29      42          43       30   15
  16   31      44                   32   |   31       5           6       32   16
  17   33                           34   |   33       4          40       34   17
  18   35                           36   |   35       3          39       36   18
  19   37                           38   |   37      37          38       38   19
  20   39                           40   |   39      35          36       40   20
  21   41       8           2       42   |   41      33          34       42   21
  22   43                           44   |   43      31          32       44   22
  23   45                           46   |   45      29          30       46   23
```

LEDscape supports up to 48 channels \(strings\) of LEDs. The above table shows how the channel numbers map to BeagleBone Black pins. We’ll use channel 0 which maps to P9\_22. Wire your LED string to P9\_22.

| Warning | The following is a hack, but it makes it work. |
| :--- | :--- |


We need to edit `ledsacpe.c` and `opc-server.c` to make them work.

Now edit `opc-server.c` and comment out line 723.

```text
// pthread_create(&g_threads.e131_server_thread.handle, NULL, e131_server_thread, NULL
```

Next edit `ledscape.c` and comment out lines 29-44

```text
// static const uint8_t gpios0[] = {
//  // 2, 3, 7, 8, 9, 10, 11, 14, 20, 22, 23, 26, 27, 30, 31
//  3, 7, 8, 9, 10, 11, 14, 20, 22, 23, 26, 27, 30, 31
// };

// static const uint8_t gpios1[] = {
//  12, 13, 14, 15, 16, 17, 18, 19, 28, 29
// };

// static const uint8_t gpios2[] = {
//  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 22, 23, 24, 25,
// };

// static const uint8_t gpios3[] = {
//  14, 15, 16, 17, 19, 21
// };
```

And also lines 176-184

```text
// Configure all of our output pins.
// for (unsigned i = 0 ; i < ARRAY_COUNT(gpios0) ; i++)
//  pru_gpio(0, gpios0[i], 1, 0);
// for (unsigned i = 0 ; i < ARRAY_COUNT(gpios1) ; i++)
//  pru_gpio(1, gpios1[i], 1, 0);
// for (unsigned i = 0 ; i < ARRAY_COUNT(gpios2) ; i++)
//  pru_gpio(2, gpios2[i], 1, 0);
// for (unsigned i = 0 ; i < ARRAY_COUNT(gpios3) ; i++)
//  pru_gpio(3, gpios3[i], 1, 0);
```

Now configure P9\_22 and run `make`.

```text
bone$ config-pin P9_22 out
bone$ config-pin -q P9_22
P9_22 Mode: gpio Direction: out Value: 0
bone$ make
```

Now run `sudo opc-server`.

```text
bone$ sudo ./opc-server
[main] Starting server on ports (tcp=7890, udp=7890) for 176 pixels on 48 strips
[main] Demo Mode Enabled
Allocating buffers for 8448 pixels (202752 bytes)
[main] Initializing / Updating server...frame_size1=8448
Starting demo data thread
[udp] Starting UDP server on port 7890
[render] Starting render thread for 8448 total pixels
[main] Starting LEDscape...pru_init: PRU 0: data 0xb4d5d000 @ 8192 bytes,  DMA 0xb4cdd000 / 9c940000 @ 262144 bytes
pru_init: PRU 1: data 0xa4c5f000 @ 8192 bytes,  DMA 0xa4bdd000 / 9c940000 @ 262144 bytes
String PRU0 with pru/bin/ws281x-original-ledscape-pru0.bin... OK
String PRU1 with pru/bin/ws281x-original-ledscape-pru1.bin... OK
[tcp] Starting TCP server on 7890
[demo] Starting Demo: fade
{
    "outputMode": "ws281x",
    "outputMapping": "original-ledscape",
    "demoMode": "fade",
    "ledsPerStrip": 176,
    "usedStripCount": 48,
    "colorChannelOrder": "BRG",
    "opcTcpPort": 7890,
    "opcUdpPort": 7890,
    "enableInterpolation": true,
    "enableDithering": true,
    "enableLookupTable": true,
    "lumCurvePower": 2.0000,
    "whitePoint": {
        "red": 0.9000,
        "green": 1.0000,
        "blue": 1.0000
    }
}
[render] fps_info={frame_avg_usec: 1924, possible_fps: 519.75, actual_fps: 0.10, sample_frames: 1}
```

You should now see "a pleasing pattern of rotating color hues".

## [Discussion](case-studies-introduction.md#_discussion_3) <a id="_discussion_3"></a>

LEDscape is higly configurable. When you run `opc-server` it first prints out its configuration. If it doesn’t receive any data after three seconds it will go into demo mode. In this configuration, `demoMode` is set to `fade` which produces the nice pattern you are seeing. \(You can set `demoMode` to `none` if you would rather not see anything. See README.md for other options.\)

Notice it’s currently configured to drive 48 strings \(`usedStripCount`\) with 176 LEDS \(`ledsPerStrip`\). It’s also set to interpolate \(`enableInterpolation`\) colors, that is, rather than abruptly switching to a new color, it will smoothly fade between the two. With this configuration it uses about 26% of the ARM CPU.

Let’s write a configuration file that fits our LEDs string. Copy the default configuration and edit it.

```text
bone$ cp configs/ws281x-config.json my-config.json
```

my-config.json

```text
{
    "outputMode": "ws281x",
    "outputMapping": "original-ledscape",
    "demoMode": "fade",
    "ledsPerStrip": 16,
    "usedStripCount": 1,
    "colorChannelOrder": "BRG",
    "opcTcpPort": 7890,
    "opcUdpPort": 7890,
    "enableInterpolation": false,
    "enableDithering": false,
    "enableLookupTable": true,
    "lumCurvePower": 2.0000,
    "whitePoint": {
        "red": 0.9000,
        "green": 1.0000,
        "blue": 1.0000
    }
}
```

Run this with:

```text
bone$ sudo ./opc-server --config my-config.json
```

Now we are only using about 7% of the ARM CPU.

You can now run a program that sends data to the string. [circle.py](case-studies-introduction.md#case_circle) is a simple python example that sequencies an LED through the entire string. It uses `opc.py` which is included in the `code` directory.

circle.py

```text
#!/usr/bin/env python3

"""A demo client for Open Pixel Control
http://github.com/zestyping/openpixelcontrol

Runs an LED around in a circle

"""

import time
import opc

ADDRESS = 'localhost:7890'

# Create a client object
client = opc.Client(ADDRESS)

# Test if it can connect
if client.can_connect():
    print('connected to %s' % ADDRESS)
else:
    # We could exit here, but instead let's just print a warning
    # and then keep trying to send pixels in case the server
    # appears later
    print('WARNING: could not connect to %s' % ADDRESS)

# Send pixels forever
STR_LEN=16
for i in range(STR_LEN):
    leds = [(0, 0, 0)] * STR_LEN
leds[0] = (0, 127, 0)

while True:
    tmp = leds[0]
    for i in range(STR_LEN-1):
        leds[i] = leds[i+1]
    leds[-1] = tmp
    if client.put_pixels(leds, channel=0):
        print('sent')
    else:
        print('not connected')
    time.sleep(0.1)
```

