#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#define SERVER_PORT 1111
#define BAUD_RATE 9600
#define SSID_NAME "my ssid" //your wifi network name
#define SSID_PASSWORD "my ssid password" //your wifi password
#define BUFFER_SIZE 16

WiFiUDP Udp;

//<---MOTOR PINS--->
int leftMotorForward = 5; //D1 pin, GPIO5
int rightMotorForward = 2; //D4 pin, GPIO2
int leftMotorBackward = 4; //D2 pin, GPIO4
int rightMotorBackward = 0; //D3 pin. GPIO0

byte joystickVals[BUFFER_SIZE];

void getJoystickVals(int &, int &);
void moveCar(int &, int &);
void logValues(const int &);
void writeOutputs(int, int);

void initOutputs() {
	pinMode(leftMotorForward, OUTPUT);
	pinMode(rightMotorForward, OUTPUT);
	pinMode(leftMotorBackward, OUTPUT);
	pinMode(rightMotorBackward, OUTPUT);

	digitalWrite(leftMotorForward, LOW);
	digitalWrite(leftMotorBackward, LOW);
	digitalWrite(rightMotorForward, LOW);
	digitalWrite(rightMotorBackward, LOW);
}

void connectWifi() {
	Serial.println();
	Serial.println();
	Serial.print("Connecting to WIFI network");

	WiFi.begin(SSID_NAME, SSID_PASSWORD);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println();
	Serial.print("WiFi connected at: ");
	Serial.println(WiFi.localIP());
	Udp.begin(SERVER_PORT);
}

void setup() {
	Serial.begin(BAUD_RATE);
	initOutputs();
	connectWifi();
}

void loop() {
	int noBytes = Udp.parsePacket();
	int xVal, yVal;

	if (noBytes) {
		Udp.read(joystickVals, noBytes);
		log(noBytes);
		getJoystickVals(xVal, yVal);
		moveCar(xVal, yVal);
	}
}

void getJoystickVals(int &xVal, int &yVal) {
	xVal = 0; yVal = 0;
	bool firstNegative = false, secondNegative = false;
	int i = 0;

	if ((char)joystickVals[0] == '-') {
		firstNegative = true;
		++i;
	}

	for (; (char)joystickVals[i] != ' '; ++i)
		xVal = xVal * 10 + ((char)joystickVals[i] - '0');
	++i;//jump space

	if ((char)joystickVals[i] == '-') {
		secondNegative = true;
		++i;
	}

	for (; (int)joystickVals[i]; ++i) {
		yVal = yVal * 10 + ((char)joystickVals[i] - '0');
	}

	if (firstNegative) xVal = -xVal;
	if (secondNegative) yVal = -yVal;
}


void log(const int &noBytes) {
	Serial.print(millis() / 1000);
	Serial.print(": Packet of ");
	Serial.print(noBytes);
	Serial.print(" received from ");
	Serial.print(Udp.remoteIP());
	Serial.print(": ");
	Serial.println(Udp.remotePort());

	for (int i = 0; i < noBytes; ++i) {
		Serial.print((char)joystickVals[i]);
	}
	Serial.println();
}

void moveCar(int & xVal, int &yVal) {
	int leftMotorVal, rightMotorVal, steerVal;

	leftMotorVal = map(yVal, -10000, 10000, -1023, 1023);
	rightMotorVal = leftMotorVal;

	steerVal = map(xVal, -10000, 10000, -1023, 1023);

	if (leftMotorVal >= 0 && steerVal > 0) {
		leftMotorVal += steerVal;
		rightMotorVal -= steerVal;
	}
	else if (leftMotorVal >= 0 && steerVal < 0) {
		leftMotorVal += steerVal;
		rightMotorVal -= steerVal;
	}
	else if (leftMotorVal < 0 && steerVal > 0) {
		leftMotorVal -= steerVal;
		rightMotorVal += steerVal;
	}
	else if (leftMotorVal < 0 && steerVal < 0) {
		leftMotorVal += -steerVal;
		rightMotorVal += steerVal;
	}

	if (leftMotorVal < -1023) leftMotorVal = -1023;
	if (rightMotorVal < -1023) rightMotorVal = -1023;

	if (leftMotorVal > 1023) leftMotorVal = 1023;
	if (rightMotorVal > 1023) rightMotorVal = 1023;

	Serial.print(leftMotorVal); Serial.print(" "); Serial.println(rightMotorVal);

	writeOutputs(leftMotorVal, rightMotorVal);
}

void writeOutputs(int leftMotorVal, int rightMotorVal) {
	if (leftMotorVal > 0) {
		analogWrite(leftMotorBackward, LOW);
		analogWrite(leftMotorForward, leftMotorVal);
	}
	else {
		analogWrite(leftMotorForward, LOW);
		analogWrite(leftMotorBackward, -leftMotorVal);
	}

	if (rightMotorVal > 0) {
		analogWrite(rightMotorBackward, LOW);
		analogWrite(rightMotorForward, rightMotorVal);
	}
	else {
		analogWrite(rightMotorForward, LOW);
		analogWrite(rightMotorBackward, -rightMotorVal);
	}
}

