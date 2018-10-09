# Temperature Control
This is a personal project. I have a thermostat and I wanted to be able to control it via the Internet.

Legend:
1. currentTemp is my current room temperature
2. targetTemp is the temperature that I wish to have in my room
3. thermostatTargetTemp is the temperature that my thermostat has as its targetTemp

Scenario to clarify the last two:
1. The current targetTemp is 20 degrees, so I set the thermostat to make 20 degrees in the room (so thermostatTargetTemp is also 20 degrees)
2. targetTemp gets updated to 22 degress, so the project presses the '+' button on the thermostat
3. thermostatTargetTemp goes from 20 to 20.5, 21, 21.5, 22; each press of the button modifies the thermostatTargetTemp by 0.5 degrees

How the project works:
1. It continously [updates on my thingspeak channel](https://thingspeak.com/) the current temperature & humidity
2. It looks for updates in the targetTemp on the thingspeak channel and then updates the thermostatTargetTemp by pressing its buttons using the MicroServo SG90
3. I can update the targetTemp using my phone, for example

Hardware requirements: 
1. ESP8266 (I used a NodeMCU v3 lua, ESP8266 integrated)
2. 4-digit display (needs to work with the TM1637Display library)
3. Micro Servo (I used a SG90)
4. Humidity + temperature sensor (I used a DHT11)

The code was wrote using OOP so it should be highly adaptable, in case anybody wishes to use this.
