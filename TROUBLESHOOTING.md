# Troubleshooting

You may experience problems with your HPDL1414 displays.  
This guide will explain basic problems you may encounter.  

### Nothing shows up on the display

Remember that new version the the library requires using display() to show text on the display.  

If that doesn't work, try wiring just one display and double check your connections with the datasheet.  
Then compare your wiring to your code. If power, ~EN, A0 and A1 pins are wired correctly the display should show something (gibberish, but still anything).  

### Not all segments work

Check the wiring and if you added all ~EN pins to your code. First entry in the array should be for the leftmost segment.  

### Random dimming, lost characters
This issue might come up when assembling the circiut on a breadboard.  
Temporary fix is to wiggle the cables to make better contact.  

### Unknown cause, unknown fix

At the moment printing all complex characters might cause the display to glitch.  
Moving around the cables will cause it to flicker and holding reset button will make it go away.  
The test print from examples will be fine, but printing 'G' on all segments could trigger it.  
All I know is they are very current-heavy.  
You can try adding bypass caps, but based on my experiments it doesn't always work.