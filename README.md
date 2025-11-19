# \# existential clock

# 15-Nov-2023

# \*\*Related\*\*

# 

# \*\*External References\*\*

# 

# ---

# \# Version 3# existential clock

# 15-Nov-2023

# \*\*Related\*\*

# 

# \*\*External References\*\*

# 

# ---

# \# Version 3

# \## Issues

# \- See \[here.](https://github.com/GralastairBean/Existential-Clock/issues)

# \## Project Targets

# \- Inspiration: https://inqfactory.com/pages/death-clock

# \- Use 7 segment displays

# \- RTC to keep time if unplugged.

# \- Easy setup/ability to change death date

# \- brightness control

# \- various display options (change with pushbutton?)

# \## Brain-storm

# \- Scroll through various output options with a pushbutton e.g. can show just SSSSSSSSSS or YYDDHHMMSS or "summers" remaining etc.

# \- Manual brightness control.

# \- Auto brightness control with a photo-sensor.

# \- Button to cycle through family members? Can use first digit to have first letter of their name?

# \## Electronics

# \### 7-segment displays

# \- Main note here: \[\[7 segment display]]

# \- Common Cathode (CC): All cathodes (grounds) are connected to GND, and segments light up when a HIGH voltage is applied to their anodes.

# \- https://github.com/iotdevspot/max7219-driven-8-digit-7-segment-display-common-cathode

# \- My displays = \*\*common cathode\*\* = connect all grounds.

# \- Come in a large and small size, need to use the small ones. Make sure when designing the PCB to use the correct footprint. Very confusing because the display size of the large ones (0.56") is the same as the total package size of the small ones!

# \- \*\*Planning to use the small ones = Screen Size = 0.36 Inches\*\*

# 

# Planning to sue the small ones = Screen Size = 0.36 Inches

# \### PCB design

# \- Digits = need 10 since (100 years is 10 digits in seconds)

# \- Each

# \- copy \[this](https://github.com/iotdevspot/max7219-driven-8-digit-7-segment-display-common-cathode)

# \- 7 segment displays = 5161AH = https://www.lcsc.com/product-detail/C8093.html

# \- Driver IC = MAX7219CNG = each can only drive 8 displays so we need 2.

# \- Driver IC socket

# \- Diode = no

# \- Resistor = ISET resistor is \*\*10kΩ\*\*, which sets the segment current to about \*\*40mA\*\* at full brightness. Between pin 18 and ground drops to about 1.5V then can control brightness in software.

# \- Capacitors...

#  	- 10 uf cap on power rails between VCC and GND

#  	- 0.1uf (100nf) ceramic cap right next to each chip between VCC and GND

# \- 10k$\\Omega$ resistor to pull CS pin on Arduino to ground to stop unknown state at start and flashing of display to full bright.

# \## Structure

# \- Either \[\[3D Printing|3D printed]] or get it metal printed or CNC milled by PCB way.

# \- To secure PCB to case...

#  	- 4.0 mm blind hole pillars (can add spacers to adjust segment to case front distance).

#  	- 4 m3x3 \[\[threaded inserts]]

#  	- 4 m3x6mm bolts

# \# Life Expectancy

# \- LE is a mean, so it is skewed by infant mortality, young male deaths at the low end and the group of really long lifers at the other end. Like income, LE (mean) isn't useful for individuals. A much better indicator would be median age at death. Which is the age that most people die at.

# \- For Australia these are pretty close anyway.

#  	- Median age of death for 2021 = 79 years (men)

#  	- Life expectancy 2021 = 81 (men)

#  	- ==Therefore, use 80 as the clock limit.==

# \# Obsolete Versions

# \## Version 1 (v1)

# 

# !\[\[IMG\_5350.jpeg]]

# \## Version 2 (v2)

# 

# !\[\[IMG\_3648.jpeg]]

# 

# !\[\[Existential Clock v2.0 v9.png]]

# 

# !\[\[cutaway.png]]

# 

# !\[\[IMG\_3630.jpeg]]

# \### Possible Ideas

# \- \[x]  Red LED on top that beats gently as a heart to add to imagery.

# \### Software

# \### Overview

# \### To do

# \### Issues

# \- \[ ] Forgets everything when unplugged, possibly use a RTC module?

# \- \[x] Code worked on 1 year = 365 days not 356.15 etc.

# \### Hardware

# \- LCD = 20x4 mounted with

#  	- 4x \[M3x10 mm] cap head bolts

#  	- 4x M3 nuts

#  	- 4x M3 washers

# \- 5mm red LED + 330 Ohm resistor

# \- Arduino Uno clone mounted with

#  	- 3x \[M3x6 mm] cap head bolts (only use three holes of arduino)

# \### To do

# \- \[ ] Redesign case on angle to allow better desk viewing

# \- \[ ] Decide on LCD mounting plan (bolts, capture etc.)

# \- \[ ] Decide on Arduino mounting plan (bolts, capture etc.)

# \- \[ ] Use threaded inserts?

# \- \[ ] Cable relief

# \- \[ ] Check can print in one go

# \- \[ ] Check 1 layer lets heartbeat light through

# \- \[ ] Design snap on back (one or two piece)

# \### Issues

# \- \[ ] Need very thin USB power cable due to small size.

# 



# \## Issues

# \- See \[here.](https://github.com/GralastairBean/Existential-Clock/issues)

# \## Project Targets

# \- Inspiration: https://inqfactory.com/pages/death-clock

# \- Use 7 segment displays

# \- RTC to keep time if unplugged.

# \- Easy setup/ability to change death date

# \- brightness control

# \- various display options (change with pushbutton?)

# \## Brain-storm

# \- Scroll through various output options with a pushbutton e.g. can show just SSSSSSSSSS or YYDDHHMMSS or "summers" remaining etc.

# \- Manual brightness control.

# \- Auto brightness control with a photo-sensor.

# \- Button to cycle through family members? Can use first digit to have first letter of their name?

# \## Electronics

# \### 7-segment displays

# \- Main note here: \[\[7 segment display]]

# \- Common Cathode (CC): All cathodes (grounds) are connected to GND, and segments light up when a HIGH voltage is applied to their anodes.

# \- https://github.com/iotdevspot/max7219-driven-8-digit-7-segment-display-common-cathode

# \- My displays = \*\*common cathode\*\* = connect all grounds.

# \- Come in a large and small size, need to use the small ones. Make sure when designing the PCB to use the correct footprint. Very confusing because the display size of the large ones (0.56") is the same as the total package size of the small ones!

# \- \*\*Planning to use the small ones = Screen Size = 0.36 Inches\*\*

# 

# Planning to sue the small ones = Screen Size = 0.36 Inches

# \### PCB design

# \- Digits = need 10 since (100 years is 10 digits in seconds)

# \- Each

# \- copy \[this](https://github.com/iotdevspot/max7219-driven-8-digit-7-segment-display-common-cathode)

# \- 7 segment displays = 5161AH = https://www.lcsc.com/product-detail/C8093.html

# \- Driver IC = MAX7219CNG = each can only drive 8 displays so we need 2.

# \- Driver IC socket

# \- Diode = no

# \- Resistor = ISET resistor is \*\*10kΩ\*\*, which sets the segment current to about \*\*40mA\*\* at full brightness. Between pin 18 and ground drops to about 1.5V then can control brightness in software.

# \- Capacitors...

#  	- 10 uf cap on power rails between VCC and GND

#  	- 0.1uf (100nf) ceramic cap right next to each chip between VCC and GND

# \- 10k$\\Omega$ resistor to pull CS pin on Arduino to ground to stop unknown state at start and flashing of display to full bright.

# \## Structure

# \- Either \[\[3D Printing|3D printed]] or get it metal printed or CNC milled by PCB way.

# \- To secure PCB to case...

#  	- 4.0 mm blind hole pillars (can add spacers to adjust segment to case front distance).

#  	- 4 m3x3 \[\[threaded inserts]]

#  	- 4 m3x6mm bolts

# \# Life Expectancy

# \- LE is a mean, so it is skewed by infant mortality, young male deaths at the low end and the group of really long lifers at the other end. Like income, LE (mean) isn't useful for individuals. A much better indicator would be median age at death. Which is the age that most people die at.

# \- For Australia these are pretty close anyway.

#  	- Median age of death for 2021 = 79 years (men)

#  	- Life expectancy 2021 = 81 (men)

#  	- ==Therefore, use 80 as the clock limit.==

# \# Obsolete Versions

# \## Version 1 (v1)

# 

# !\[\[IMG\_5350.jpeg]]

# \## Version 2 (v2)

# 

# !\[\[IMG\_3648.jpeg]]

# 

# !\[\[Existential Clock v2.0 v9.png]]

# 

# !\[\[cutaway.png]]

# 

# !\[\[IMG\_3630.jpeg]]

# \### Possible Ideas

# \- \[x]  Red LED on top that beats gently as a heart to add to imagery.

# \### Software

# \### Overview

# \### To do

# \### Issues

# \- \[ ] Forgets everything when unplugged, possibly use a RTC module?

# \- \[x] Code worked on 1 year = 365 days not 356.15 etc.

# \### Hardware

# \- LCD = 20x4 mounted with

#  	- 4x \[M3x10 mm] cap head bolts

#  	- 4x M3 nuts

#  	- 4x M3 washers

# \- 5mm red LED + 330 Ohm resistor

# \- Arduino Uno clone mounted with

#  	- 3x \[M3x6 mm] cap head bolts (only use three holes of arduino)

# \### To do

# \- \[ ] Redesign case on angle to allow better desk viewing

# \- \[ ] Decide on LCD mounting plan (bolts, capture etc.)

# \- \[ ] Decide on Arduino mounting plan (bolts, capture etc.)

# \- \[ ] Use threaded inserts?

# \- \[ ] Cable relief

# \- \[ ] Check can print in one go

# \- \[ ] Check 1 layer lets heartbeat light through

# \- \[ ] Design snap on back (one or two piece)

# \### Issues

# \- \[ ] Need very thin USB power cable due to small size.

# 

