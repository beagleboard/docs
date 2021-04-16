# Getting Started

## Getting Started

Beagles are tiny computers ideal for learning and prototyping with electronics. Read the step-by-step getting started tutorial below to begin developing with your Beagle in minutes.

## Update board with latest software <a id="update"></a>

This step may or may not be necessary, depending on how old a software image you already have, but executing this, the longest, step will ensure the rest will go as smooth as possible.

#### Step \#0.A: Download the latest software image

Download the lastest Debian image from [beagleboard.org/latest-images](https://beagleboard.org/latest-images). The "IoT" images provide more free disk space if you don't need to use a graphical user interface \(GUI\).

**Note:** Due to sizing necessities, this download may take 30 minutes or more.

The Debian distribution is provied for the boards. The file you download will have an .img.xz extension. This is a compressed sector-by-sector image of the SD card.

#### Step \#0.B: Install SD card programming utility

Download and install [balenaEtcher](https://www.balena.io/etcher/).

#### Step \#0.C: Connect SD card to your computer

Use your computer's SD slot or a USB adapter to connect the SD card to your computer.

#### Step \#0.D: Write the image to your SD card

Use Etcher to write the image to your SD card. Etcher will transparently decompress the image on-the-fly before writing it to the SD card.

#### Step \#0.E: Eject the SD card

Eject the newly programmed SD card.

#### Step \#0.F: Boot your board off of the SD card

Insert SD card into your \(powered-down\) board, hold down the USER/BOOT button \(if using Black\) and apply power, either by the USB cable or 5V adapter.

If using an original BeagleBone or PocketBeagle, you are done.

If using BeagleBone Black, BeagleBone Blue, BeagleBone AI or other board with on-board eMMC flash and you desire to write the image to your on-board eMMC, you'll need to follow the instructions at [http://elinux.org/Beagleboard:BeagleBoneBlack\_Debian\#Flashing\_eMMC](http://elinux.org/Beagleboard:BeagleBoneBlack_Debian#Flashing_eMMC). When the flashing is complete, all 4 USRx LEDs will be steady on or off. The latest Debian flasher images automatically power down the board upon completion. _This can take up to 45 minutes._ Power-down your board, _remove the SD card_ and apply power again to finish.

## Start your Beagle

#### _If any step fails, it is recommended to update to the_ [_latest software image_]() _using the instructions above._

[ **Power and boot**]()

Most Beagles include a USB cable, providing a convenient way to provide both power to your Beagle and connectivity to your computer. If you provide your own, ensure it is of good quality.

Alternatively, your Beagle may have a barrel jack. The voltage should be 5V except for BeagleBoard-X15 and BeagleBone Blue which use 12V.

_Note that BeagleBoard-X15 must always be powered by a 12V adapter with a barrel jack._

If you are using your Beagle with an [SD \(microSD\) card](https://en.wikipedia.org/wiki/Secure_Digital), make sure it is inserted ahead of providing power. Most Beagles include programmed on-board flash and therefore do not require an SD card to be inserted.

You'll see the power \(PWR or ON\) LED lit steadily. Within a minute or so, you should see the other LEDs blinking in their default configurations. Consult the Quick Start Guide \(QSG\) or System Reference Manual \(SRM\) for your board to locate these LEDs.

* USR0 is typically configured at boot to blink in a heartbeat pattern
* USR1 is typically configured at boot to light during SD \(microSD\) card accesses
* USR2 is typically configured at boot to light during CPU activity
* USR3 is typically configured at boot to light during eMMC accesses
* USR4/WIFI is typically configured at boot to light with WiFi \(client\) network association \(_BeagleBone Blue and BeagleBone AI only_\)

  
[**Enable a network connection**]()

If connected via USB, a network adapter should show up on your computer. Your Beagle should be running a DHCP server that will provide your computer with an IP address of either 192.168.7.1 or 192.168.6.1, depending on the type of USB network adapter supported by your computer's operating system. Your Beagle will reserve 192.168.7.2 or 192.168.6.2 for itself.

If your Beagle includes WiFi, an access point called "BeagleBone-XXXX" where "XXXX" varies between boards. The access point password defaults to "BeagleBone". Your Beagle should be running a DHCP server that will provide your computer with an IP address in the 192.168.8.x range and reserve 192.168.8.1 for itself.

If your Beagle is connected to your local area network \(LAN\) via either Ethernet or WiFi, it will utilize [mDNS](https://en.wikipedia.org/wiki/Multicast_DNS) to broadcast itself to your computer. If your computer supports mDNS, you should see your Beagle as beaglebone.local. _Non-BeagleBone boards will utilize alternate names. Multiple BeagleBone boards on the same network will add a suffix such as beaglebone-2.local._

The below table summarizes the typical addresses and should dynamically update to indicate an active connection.

**Note:** You must "load unsafe scripts" or load [this page](http://beagleboard.org/getting-started) without HTTPS security for the automatic detection to work.

| IP Address | Connection Type | Operating System\(s\) | Status |
| :--- | :--- | :--- | :--- |
| 192.168.7.2 | USB | Windows |  |
| 192.168.6.2 | USB | Mac OS X, Linux |  |
| 192.168.8.1 | WiFi | all |  |
| beaglebone.local | all | mDNS enabled |  |
| beaglebone-2.local | all | mDNS enabled |  |

[**Browse to your Beagle**]()

Using either [Chrome](https://www.google.com/chrome) or [Firefox](http://www.mozilla.org/firefox) \(Internet Explorer will **NOT** work\), browse to the web server running on your board. It will load a presentation showing you the capabilities of the board. Use the arrow keys on your keyboard to navigate the presentation.

* Click here to launch: [http://192.168.7.2](http://192.168.7.2/)  Older software images require you to EJECT the BEAGLE\_BONE drive to start the network. With the latest software image, that step is no longer required.

### Troubleshooting <a id="troubleshooting"></a>

_Do not use Internet Explorer._

Virtual machines are not recommended when using the direct USB connection. It is recommended you use only network connections to your board if you are using a virtual machine.

When using 'ssh' with the provided image, the username is 'debian' and the password is 'temppwd'.

With the latest images, _it should no longer be necessary to install drivers_ for your operating system to give you network-over-USB access to your Beagle. In case you are running an older image, an older operating system or need additional drivers for serial access to older boards, links to the old drivers are below.

<table>
  <thead>
    <tr>
      <th style="text-align:left">Operating System</th>
      <th style="text-align:left">USB Drivers</th>
      <th style="text-align:left">Comments</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="text-align:left">Windows (64-bit)</td>
      <td style="text-align:left"> <a href="https://beagleboard.org/static/Drivers/Windows/BONE_D64.exe">64-bit installer</a>
      </td>
      <td style="text-align:left">
        <p>If in doubt, try the 64-bit installer first.</p>
        <ul>
          <li><b>Note #1:</b> Windows Driver Certification warning may pop up two or
            three times. Click &quot;Ignore&quot;, &quot;Install&quot; or &quot;Run&quot;</li>
          <li><b>Note #2:</b> To check if you&apos;re running 32 or 64-bit Windows see
            this: <a href="https://support.microsoft.com/kb/827218">support.microsoft.com/kb/827218</a>.</li>
          <li><b>Note #3:</b> On systems without the latest service release, you may
            get an error (0xc000007b). In that case, please install the following and
            retry: <a href="https://www.microsoft.com/en-us/download/confirmation.aspx?id=13523">www.microsoft.com/en-us/download/confirmation.aspx?id=13523</a>.</li>
          <li><b>Note #4:</b> You may need to reboot Windows.</li>
          <li><b>Note #5:</b> These drivers have been tested to work up to Windows 10</li>
        </ul>
      </td>
    </tr>
    <tr>
      <td style="text-align:left">Windows (32-bit)</td>
      <td style="text-align:left"> <a href="https://beagleboard.org/static/Drivers/Windows/BONE_DRV.exe">32-bit installer</a>
      </td>
      <td style="text-align:left"></td>
    </tr>
    <tr>
      <td style="text-align:left">Mac OS X</td>
      <td style="text-align:left"> <a href="https://beagleboard.org/static/Drivers/MacOSX/RNDIS/HoRNDIS.pkg">Network</a>
        <br
        /> <a href="https://beagleboard.org/static/Drivers/MacOSX/FTDI/EnergiaFTDIDrivers2.2.18.pkg">Serial</a>
        <br
        />
      </td>
      <td style="text-align:left">Install both sets of drivers.</td>
    </tr>
    <tr>
      <td style="text-align:left">Linux</td>
      <td style="text-align:left"> <a href="https://beagleboard.org/static/Drivers/Linux/FTDI/mkudevrule.sh">mkudevrule.sh</a>
      </td>
      <td style="text-align:left">Driver installation isn&apos;t required, but you might find a few udev
        rules helpful.</td>
    </tr>
  </tbody>
</table>

**Note:** Additional FTDI USB to serial/JTAG information and drivers are available from [www.ftdichip.com/Drivers/VCP.htm](https://www.ftdichip.com/Drivers/VCP.htm).

**Note:** Additional USB to virtual Ethernet information and drivers are available from [www.linux-usb.org/gadget/](https://www.linux-usb.org/gadget/) and [joshuawise.com/horndis](https://joshuawise.com/horndis).

Visit [beagleboard.org/support](https://beagleboard.org/support) for additional debugging tips.

### Other currently available software images <a id="distros"></a>

Some of the starting images below involve multiple steps to produce an SD card image or otherwise change some of the steps above, so be sure to read all the instructions on their pages. Choose the starting point you want, download or produce the SD card image and follow the steps above.

At the time of release, not all of these distributions support BeagleBone Black, but should soon.

* Texas Instruments releases: [Android](https://beagleboard.org/project/android/), [Linux](https://beagleboard.org/project/amsdk/), [StarterWare \(no OS\)](https://beagleboard.org/project/starterware/)
* Linux: [Debian](https://beagleboard.org/project/Debian/), [Angstrom Distribution](https://beagleboard.org/project/angstrom), [Ubuntu](https://beagleboard.org/project/ubuntu/), [ArchLinux](https://beagleboard.org/project/AM/), [Gentoo](https://beagleboard.org/project/Gentoo/), [Sabayon](https://beagleboard.org/project/sabayon/), [Buildroot](https://beagleboard.org/project/buildroot/), [Erlang](https://beagleboard.org/project/Nerves/), [Fedora](https://beagleboard.org/project/fedora/)
* Other: [QNX](https://beagleboard.org/project/QNX+Neutrino+on+OMAP/), [FreeBSD](https://beagleboard.org/project/freebsd/)
* [Projects page](https://beagleboard.org/project)

### Hardware documentation <a id="hardware"></a>

Time to read that manual and check out the design materials: [BeagleBoard](https://github.com/beagleboard/beagleboard), [BeagleBoard-xM](https://github.com/beagleboard/beagleboard-xm), [BeagleBoard-X15](https://github.com/beagleboard/beagleboard-x15), [BeagleBone](https://github.com/beagleboard/beaglebone), [BeagleBone Black](https://github.com/beagleboard/beaglebone-black), [BeagleBone Black Wireless](https://github.com/beagleboard/beaglebone-black-wireless), [BeagleBone Blue](https://github.com/beagleboard/beaglebone-blue), [PocketBeagle](https://github.com/beagleboard/pocketbeagle), and [BeagleBone AI](https://github.com/beagleboard/beaglebone-ai).

Other links to design materials for various releases can be found at [beagleboard.org/hardware/design](https://beagleboard.org/hardware/design).

### Books <a id="books"></a>

For a complete list of books on BeagleBone, see [beagleboard.org/books](https://beagleboard.org/books).

#### [Bad to the Bone](https://bbb.io/bad-to-the-bone)

Perfect for high-school seniors or freshman univerisity level text, consider using "Bad to the Bone"

#### [BeagleBone Cookbook](https://bbb.io/cookbook)

A lighter treatment suitable for a bit broader audience without the backgrounders on programming and electronics, consider "BeagleBone Cookbook"

#### [Exploring BeagleBone](https://bbb.io/ebb) and [Embedded Linux Primer](https://bbb.io/elp)

To take things to the next level of detail, consider "Exploring BeagleBone" which can be considered the missing software manual and utilize "Embedded Linux Primer" as a companion textbook to provide a strong base on embedded Linux suitable for working with any hardware that will run Linux.

