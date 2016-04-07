# Uplift Tower
This is an Arduino code and circuit sketch for building a neurofeedback-controlled levitating globe device.

To see it in action, watch this: https://www.youtube.com/watch?v=Us1drZzZepk

## Setup Guide

Here's the deal: we've got two versions of the tower: (1) the full-scale, 36" diameter, 15' tall model, as seen in the video above & (2) a mini tower designed to levitate a ping pong ball.

These instructions apply to the mini tower - instructions for the full-scale model are coming soon. The good news: both use the same code and core electronics.

If you build the mini tower and want to upgrade to the full-scale version, you can swap out the fan, power supply, and ball.

### Materials

If you want to save time and support Project Uplift at the same time, use the short link below to fill an Amazon cart with everything below and a portion of the proceeds will go to Project Uplift.

http://bit.ly/uplift-tower-parts

If you'd rather source parts yourself, here's what you'll need:
- Arduino Uno R3
- Bluetooth Mate Silver with RN-42 class 2 module
- NeuroSky MindWave Mobile BrainWave headset
- 30A 5-30V Single Brushed Dc Motor Driver
- Blower - Squirrel Cage (12V)
- DC power supply (12V, 2A)
- A Ping Pong Ball
- Jumper wires (male to female, male to male, & female to female)
- Break Away Headers (Pin Spacing: 2.54mm, Straight)
- Solder
- AAA batteries

Please note:
1. These are the parts for the desktop version. To build the full-scale tower, replace the blower - squirrel cage (12V), power-supply, and ping pong balls with these items:
- Fan: http://www.mcmaster.com/#5159t45
- Power supply: http://www.ebay.com/itm/Regulated-Switching-Power-Supply-DC-12V-30A-360W-LED-Strip-Light-Cooling-Fan-/231849834132
- Globe: http://www.beachballs.com/36-inch-diameter-astro-earth-globe-beach-balls-inflates-true-size-36in-91cm.asp
- In addition to jumper wires, you should also have 20 AWG wire to connect the larger fan and power supply.
2. There are better prices on certain components elsewhere - specifically, the motor controller and squirrel cage fan. Check RobotShop.com and SparkFun.com respectively.

### Tools

Below are the tools you will need to build the mini tower. A tool list and instructions for the full-size device are coming soon.

- USB Type B Cable
- Soldering iron
- Wire strippers
- Protective eyewear
- Helping hands (optional)
- Screwdriver

### Assembly

Below are V1 of our instructions. If you want more help, we're making a video series that should ship summer 2016. Sign up at http://open.uplift.is to be notified!

#### Step 1: Set up Arduino
- Download code from GitHub
- Connect your Arduino to your computer via USB
- Load the code on to the Arduino with the Arduino Software (IDE)

#### Step 2: Connect Bluetooth module
- Solder break away headers onto Bluetooth Mate Silver 
- Short RTS and CTS together
- Connect Bluetooth Mate Silver Vcc to Arduino's 3v3
- Connect Bluetooth Mate Silver GND to Arduino GND
- Connect Bluetooth Mate Silver TX to Arduino RX
- Connect Bluetooth Mate Silver RX to Arduino TX

#### Step 3: Get MindWave Mobile headset MAC Address
- Pair headset to your computer
- Find device labeled MindWave Mobile
- Copy MAC Address

#### Step 4: Program Bluetooth module
- Once you power up your Arduino board and have the Bluetooth Mate Silver connected, you will see a red LED blink on your Bluetooth module.
- Pair the Bluetooth Mate Silver to your computer. It will appear, as similar to, RN-42-5922. (The Default Baud Rate is 115200)
- Open your Terminal Software, and connect the Bluetooth Mate Silver. The LED will turn green when it's connected. (This may take a few tries. You can power cycle the Arduino if you experience issues.)
- Be sure to enable “Local Echo” to be able to view your input commands.
- To put the Bluetooth Mate Silver into COMMAND mode, type $$$. Please reference this website: http://www.sparkfun.com/datasheets/Wireless/Bluetooth/rn-bluetooth-um.pdf
	- If successful, you will see “CMD”
- Type: D
	- You will see the current configuration of the Bluetooth Mate Silver.
- Now type: SP,0000
	- This will change the pincode from '1234' to '0000'
- Now type: SM,3
	- This will configure the Bluetooth Mate Silver to Auto-Connect Mode. Once the module is powered up, it will immediately look to connect.
	- You should see “AOK” if this is done properly.
- Now type: SR,MAC ADDRESS
	- Insert the 12 digit address you copied from the MindWave Mobile.
	- Again, look for AOK.
- Now type: SU,57.6
	- This will change the BaudRate from 115200 to 57600
- Type: D
	- Check to be sure that the stored address is the Mac address, and it's configure to Auto, not Slave
- Type: — (three minus signs)
	- This will exit out of Coolterm. If successful, you will see END.

#### Step 5: Checking Bluetooth module configuration
- Power on your MindWave Mobile headset
- Power on your Arduino + Bluetooth module
- If the Bluetooth Mate Silver LED turns green, and the MindWave Mobile LED turns solid blue, you are now connected and receiving data from the MindWave Mobile.
	- If not, please retry to configure your Bluetooth module by repeating Step 4 and check the proper MAC address

#### Step 6: Connect Motor driver to Arduino
- Connect Pin 9 of the Arduino to PWM on JP3 of the Motor Driver
- Connect GND of the Arduino to GND & DIR on JP3 of the Motor Driver

#### Step 7: Set up fan
- Connect the fan to the screw terminals labeled "Motor" on the Motor Driver (A and B)
- Connect the power supply output to the screw terminals labeled "Power" on the Motor Driver (be sure to match + to + and - to -)

#### Step 8: Run it
- Start with the Arduino and MindWave headset turned off
- Turn on the MindWave
- Plug in the power supply
- Power up the Arduino
	- The fan should cycle from low to high and then turn off over 5 seconds when the code starts
- Wait for the Bluetooth module to pair with the MindWave
	- LED on MindWave will turn blue
	- LED on Bluetooth module will turn green
- Place Ping Pong ball on the exhaust of the fan
- Put on the MindWave, close your eyes, and focus on your breath
- When you relax enough, the fan should cycle on

Congratulations, you just lifted the world (or more likely a ping pong ball) with your mind!

Parts of this guide were taken from Neurosky's documentation on setting up the MindWave Mobile with Arduino using the Blue Mate Silver module, available here: http://developer.neurosky.com/docs/doku.php?id=mindwave_mobile_and_arduino

## License

The MIT License (MIT)

Copyright (c) 2016 Zachary Valenti

See LICENCE for more.

## Contributing Guide

We'd love your help in any way you see fit, whether its organizing an Uplift even in your area or improvements on our hardware, software, or documentation.

We would also love to support you if you have any questions.

Please contact help@uplift.is for now. Hang tight - a Slack community is in the works.