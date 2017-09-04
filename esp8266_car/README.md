This is designed to control a car using 2 stepper motors via WiFi with a Joystick. It requires an ESP8266 module.
It has been successfuly tested on the following hardware: CH340 NodeMCU v3 development board (featuring an ESP8266 WiFi module), L9110S DC Stepper Motor Bridge, Logitech Wireless Gamepad F710.
If you use a board other than the NodeMCU CH340, then you might want to review the code and adapt it to your board.

How to use the project:
1) Modify the esp8266_car.ino so that it contains your SSID and SSID password: <br>
#define SSID_NAME "my ssid" //your wifi network name <br>
#define SSID_PASSWORD "my ssid password" //your wifi password <br>

2) Connect the two motors on the pins shown below. You may modify this to your liking. Be aware that the direction of the wheels depends on how you wire the motors. <br>
	int leftMotorForward = 5; //D1 pin, GPIO5 <br>
	int rightMotorForward = 2; //D4 pin, GPIO2 <br>
	int leftMotorBackward = 4; //D2 pin, GPIO4 <br>
	int rightMotorBackward = 0; //D3 pin. GPIO0 <br>

2) Connect your Joystick to http://html5gamepad.com/ and then insert the JavaScript code into the website using a browser extension. For example, CJS or Tampermonkey for Google Chrome. <br>
You should now see some boxes with "Axis nr." and their values. Modify the JavaScript code so you may use whichever axis you want. It requires one for steering and one for acceleration. <br>
	axis3 = list.getElementsByClassName ("ng-scope")[3]; <br>
	axis0 = list.getElementsByClassName ("ng-scope")[0]; <br>
I have used Axis 0 for steering and Axis 3 for acceleration.

3) Make sure you have "Automatically download files" enabled in your browser!!! Otherwise, you will receive too many prompts and your browser will crash. <br>
Make sure your browser overwrites downloaded files that have the same name. For Google Chrome, you can use an extension such as https://chrome.google.com/webstore/detail/downloads-overwrite-alrea/lddjgfpjnifpeondafidennlcfagekbp/related

4) Find the Local IP for the ESP8266 module. You can do this with sudo arp-scan --interface=YourInterface --localnet. <br>
You can find the interface with ifconfig.

5) Run the script as: <br>
watch -n 0,1 ./sendVals.sh LocalIpForTheESP8266Module 1111 <br>
The board will listen for data on port 1111. Make sure you modify the bash script so that it contains the right path to the file downloaded by JavaScript. Don't forget to give execution writes for the bash script (chmod +x sendVals.sh)

6) Have fun! :)


WARNING!!!
1) The JavaScript script will download files every 100 miliseconds (by default). This can cause performance issues in the browser.
For the best outcome, modify the default download speed so that it suits you best.
2) Do not, under any circumstances, directly power the motors from the NodeMCU board. Use a separate power source for the 2 motors.

I do not own the http://html5gamepad.com/ website. I have used it as a "middle-man". 
