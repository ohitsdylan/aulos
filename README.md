# aulos
An automotive media interface.

Audio playback is handled by [cmus](https://github.com/cmus/cmus) and it features a clock via [tock](https://github.com/nwtnni/tock) and a visualizer by [vis (cli-visualizer)](https://github.com/dpayne/cli-visualizer), wrapped up and served to your Raspberry Pi via [buildroot](http://buildroot.org/).

Intended to be run on a Euro-spec 2017 Ford Focus, but can probably be adapted to work with other makes and models.

### Directories and Files
- `buildroot` : Contains the downloaded buildroot source files (not included in this repo)
- `external` : Contains the aulos-specific buildroot configs and packages
- `controller.ino` : Arduino code to translate CANBUS messages to key presses
- `README.md` : This file
- `setup.sh` : A script that stages the buildroot environment

### Prerequisites & Notes
This system is intended to be run in an automotive environment, and so the primary needs were determined to be:
- Speed at which the system would boot
- Resiliency in case of a power failure event
- Quality audio playback

Additionally, keyboard shortcuts for cmus are not keyboard-friendly given that interaction is through the media keys on the car audio system.

#### ⚠️ NOTE
There is _no_ network stack and the kernel has been stripped of things considered to be "non-essential" (drivers, mostly).

### Hardware List
- [RaspberryPi 4B 8GB RAM](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
- [HiFiBerry DAC2 HD](https://www.hifiberry.com/shop/boards/hifiberry-dac2-hd/)
- [KKSB Tall Aluminium Case for Raspberry Pi 4](https://thepihut.com/products/raspberry-pi-power-rtc-hat)
- [Power + RTC HAT for Raspberry Pi](https://thepihut.com/products/raspberry-pi-power-rtc-hat)
    - [CR1220 3V Lithium Coin Cell Battery](https://thepihut.com/products/cr1220-12mm-diameter-3v-lithium-coin-cell-battery)
- [Pure Copper 4-Piece Heatsink Set for Raspberry Pi 4](https://thepihut.com/products/pure-copper-4-piece-heatsink-set-for-raspberry-pi-4)
- [Noctua NF-A4x10 5V Fan](https://noctua.at/en/products/fan/nf-a4x10-5v)
- [Waveshare 7inch IPS/QLED Integrated Display, 1024 × 600](https://www.waveshare.com/product/displays/lcd-oled/lcd-oled-1/70h-1024600.htm?sku=22684)

### Building
1. Clone this repository `git clone https://github.com/ohitsdylan/aulos`
2. Change directories into the repo `cd aulos`
3. Run the setup script `./setup.sh`

### Principle Functionality
1. The Pi boots and logs into the `aulos` user automatically
2. A script, `start-aulos.sh`, in `/etc/profile.d` runs and:
    1. Starts tmux and creates three panes
    2. In pane one, `cmus` is started
    3. In pane two, `tock` is started
    4. In pane three, `vis` is started
    5. Focus is switched back to pane one.
3. Interaction with the system is done via a CANBUS media interface. Button presses are converted from CANBUS data to HID key presses and sent to the Pi, which are interpreted by `cmus`.
4. Media is stored in `/home/aulos/music` and is read-only.

### TODO
- Test running system as a RAM disk
    - Or maybe toggle the "mount read-write" setting in buildroot
- Add photos and screenshots
- Configure RTC clock
- Create a metapackage to copy over music files and then generate a new lib.pl file for cmus
- Create a fakeroot script to modify some directory permissions
- See if autologin script works for aulos user
- Setup psplash
