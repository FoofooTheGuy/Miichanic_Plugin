<p align="center">
<img width="708" height="-1" src="https://user-images.githubusercontent.com/32585652/149023595-aa0d8153-a942-4c2b-947d-a7214ef68e21.png">
</p>

# Miichanic's Tool Box
A Luma3DS plugin for the Title Mii Maker that uses CTRPF 0.7.0 and supports every region.

# Installation guide:
(You will need to first install Custom Firmware to use this plugin)

Method 1 (Assisted installation using a Windows PC):
---

- If you use a Windows PC, (Windows 7 and above), then you can do this simple method!

1. Turn off your console and put your SD card into your computer

2. Download and run the [Miichanics-Tool-Box-Installer](https://github.com/FoofooTheGuy/Miichanic_Plugin/releases/latest/download/Miichanics-Tool-Box-Installer.exe) program, and follow the instructions there. Come back here when it is finished.
3. Put your SD card back into your console and open the rosalina menu (L + D-pad down + select by default) and enable the plugin loader (4th option)
4. Launch Mii maker, and the screen will flash a light blue color and the message "Plugin ready!" shall appear soon after.

Method 2 (Manual installation):
---
1. Turn off your console and put your SD card into your computer
2. Download the boot.firm file for [Luma3DS 3GX Loader Edition](https://github.com/Nanquitas/Luma3DS/releases/latest) and
replace the boot.firm on your SD card root with that one.
3. Create a folder called "plugins" (without quotes) in the luma folder that is on your SD card root (SD:/luma/plugins/)
4. Create a folder corresponding to your game title ID in the plugins folder:

Japan: SD:/luma/plugins/0004001000020700/

USA: SD:/luma/plugins/0004001000021700/

Europe: SD:/luma/plugins/0004001000022700/

China: SD:/luma/plugins/0004001000026700/

Korea: SD:/luma/plugins/0004001000027700/

Taiwan: SD:/luma/plugins/0004001000028700/

5. Place [Miichanic.3gx](https://github.com/FoofooTheGuy/Miichanic_Plugin/releases/latest/download/Miichanic.3gx) in that folder (E.g. SD:/luma/plugins/0004001000020700/Miichanic.3gx)
6. Put your SD card back into your console and open the rosalina menu (L + D-pad down + select by default) and enable the plugin loader (4th option)
7. Launch Mii maker, and the screen will flash a light blue color and the message "Plugin ready!" shall appear soon after.

Press select to open the menu.
# Features:

# (Directory for Editor codes)

Nickname / Creator Modifier

Copy and paste Mii data

(End of directory)

# (Directory for Save file options)

Dump save file

Restore save file

Mega menu

Create Mii QR code

# Mega menu contains:

Change name

Change creator

Toggle gender

Change favorite color

Change birth day

Toggle favorite

Toggle sharing

Toggle copying

Toggle gold pants

Take ownership

Swap with personal Mii

Delete Mii

(End of directory)

# (Root of menu)

Useless OSD

Toggle theme

Exit to home menu
# Screenshots:
Dark theme (default) and Light theme (ugly)

![first](https://user-images.githubusercontent.com/32585652/130987833-675f510d-0dfe-4c21-964e-490167394066.png)
![second](https://user-images.githubusercontent.com/32585652/130987860-290ce40d-830e-4aac-9eba-a7fd4b618530.png)

Mega Menu:

![megalong](https://user-images.githubusercontent.com/32585652/145294918-89fb4220-dbbb-4a4a-a785-fa4874113009.png)

Change Favorite color:

![ChangeColor](https://user-images.githubusercontent.com/32585652/133910032-470f58b3-5c04-442c-a9d7-04b0fc8f6ea0.png)

JP/US/EU menu:

![JPUSEU](https://user-images.githubusercontent.com/32585652/130695895-75d2d25c-03b3-4963-95b6-aac232aab580.png)

CHN/TWN menu on the CHN version and on the TWN version:

![CHNTWN](https://user-images.githubusercontent.com/32585652/130695992-10242923-a364-45d1-ba59-bce55d4a8a1b.png)
![TWN](https://user-images.githubusercontent.com/32585652/130696044-32db5ee2-a9b1-4379-95ef-c5b648c34e92.png)

KOR menu:

![KOR](https://user-images.githubusercontent.com/32585652/130696091-d48ac080-61a7-4f96-afb0-2d9fbd8988c6.png)

# Building

install [this](https://mega.nz/file/bzRU1BaA#rwaZNp-_iki1dEwz-rAWrlG67TAg5nW5NxmQSBgBUnE) version of devkitpro and then run [build.bat](https://github.com/FoofooTheGuy/Miichanic_Plugin/blob/main/build.bat)
