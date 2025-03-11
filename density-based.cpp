#include <TimerOne.h>

// 🚦 Traffic Signal Pins
int signal1[] = {23, 25, 27};  // Red, Yellow, Green
int signal2[] = {46, 48, 50};
int signal3[] = {13, 12, 11};
int signal4[] = {10, 9, 8};

// ⏳ Signal Timings
int redDelay = 5000;    // Red light duration (5 seconds)
int yellowDelay = 2000; // Yellow light duration (2 seconds)

// 📡 Ultrasonic Sensor Pins
volatile int triggerpin1 = 31, echopin1 = 29;
volatile int triggerpin2 = 44, echopin2 = 42;
volatile int triggerpin3 = 7,  echopin3 = 6;
volatile int triggerpin4 = 5,  echopin4 = 4;

// 📏 Sensor Readings
volatile long time; // Variable for storing the time traveled by sound
volatile int S1, S2, S3, S4; // Distances measured by sensors

int t = 5; // Threshold distance for detecting vehicles

void setup() {
    Serial.begin(115200);

    // 🕒 Initialize Timer Interrupt (100 milliseconds)
    Timer1.initialize(100000);  
    Timer1.attachInterrupt(softInterr); 

    // 🎛️ Set up traffic light pins as output
    for (int i = 0; i < 3; i++) {
        pinMode(signal1[i], OUTPUT);
        pinMode(signal2[i], OUTPUT);
        pinMode(signal3[i], OUTPUT);
        pinMode(signal4[i], OUTPUT);
    }

    // 🔌 Set up ultrasonic sensor pins
    pinMode(triggerpin1, OUTPUT);  pinMode(echopin1, INPUT);
    pinMode(triggerpin2, OUTPUT);  pinMode(echopin2, INPUT);
    pinMode(triggerpin3, OUTPUT);  pinMode(echopin3, INPUT);
    pinMode(triggerpin4, OUTPUT);  pinMode(echopin4, INPUT);
}

void loop() {
    // 🚦 Check for vehicles and activate the appropriate signal
    if (S1 < t) { signal1Function(); }
    if (S2 < t) { signal2Function(); }
    if (S3 < t) { signal3Function(); }
    if (S4 < t) { signal4Function(); }
}

// 🕒 Timer Interrupt Function (Runs every 100ms)
void softInterr() {
    // 📡 Read distances from all ultrasonic sensors

    // Sensor 1
    digitalWrite(triggerpin1, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin1, LOW);
    time = pulseIn(echopin1, HIGH);
    S1 = time * 0.034 / 2;

    // Sensor 2
    digitalWrite(triggerpin2, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin2, LOW);
    time = pulseIn(echopin2, HIGH);
    S2 = time * 0.034 / 2;

    // Sensor 3
    digitalWrite(triggerpin3, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin3, LOW);
    time = pulseIn(echopin3, HIGH);
    S3 = time * 0.034 / 2;

    // Sensor 4
    digitalWrite(triggerpin4, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerpin4, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerpin4, LOW);
    time = pulseIn(echopin4, HIGH);
    S4 = time * 0.034 / 2;

    // 🖥️ Debugging - Print distance values
    Serial.print("S1: "); Serial.print(S1);
    Serial.print("  S2: "); Serial.print(S2);
    Serial.print("  S3: "); Serial.print(S3);
    Serial.print("  S4: "); Serial.println(S4);
}

// 🚦 Traffic Signal Functions
void signal1Function() {
    Serial.println("Signal 1 Active");
    low();
    digitalWrite(signal1[0], LOW); // Turn off Red
    digitalWrite(signal1[2], HIGH); // Turn on Green
    delay(redDelay);
    if (S2 < t || S3 < t || S4 < t) {
        digitalWrite(signal1[2], LOW); // Turn off Green
        digitalWrite(signal1[1], HIGH); // Turn on Yellow
        delay(yellowDelay);
    }
}

void signal2Function() {
    Serial.println("Signal 2 Active");
    low();
    digitalWrite(signal2[0], LOW);
    digitalWrite(signal2[2], HIGH);
    delay(redDelay);
    if (S1 < t || S3 < t || S4 < t) {
        digitalWrite(signal2[2], LOW);
        digitalWrite(signal2[1], HIGH);
        delay(yellowDelay);
    }
}

void signal3Function() {
    Serial.println("Signal 3 Active");
    low();
    digitalWrite(signal3[0], LOW);
    digitalWrite(signal3[2], HIGH);
    delay(redDelay);
    if (S1 < t || S2 < t || S4 < t) {
        digitalWrite(signal3[2], LOW);
        digitalWrite(signal3[1], HIGH);
        delay(yellowDelay);
    }
}

void signal4Function() {
    Serial.println("Signal 4 Active");
    low();
    digitalWrite(signal4[0], LOW);
    digitalWrite(signal4[2], HIGH);
    delay(redDelay);
    if (S1 < t || S2 < t || S3 < t) {
        digitalWrite(signal4[2], LOW);
        digitalWrite(signal4[1], HIGH);
        delay(yellowDelay);
    }
}

// 🔄 Reset all LEDs except Red
void low() {
    for (int i = 1; i < 3; i++) {
        digitalWrite(signal1[i], LOW);
        digitalWrite(signal2[i], LOW);
        digitalWrite(signal3[i], LOW);
        digitalWrite(signal4[i], LOW);
    }
    for (int i = 0; i < 1; i++) {
        digitalWrite(signal1[i], HIGH);
        digitalWrite(signal2[i], HIGH);
        digitalWrite(signal3[i], HIGH);
        digitalWrite(signal4[i], HIGH);
    }
}