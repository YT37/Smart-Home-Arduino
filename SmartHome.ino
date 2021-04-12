#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

#define ESP8266_BAUD 9600

SoftwareSerial EspSerial(2, 3);
ESP8266 wifi(&EspSerial);

char auth[] = "";
char ssid[] = "";
char pass[] = "";

const int RAIN = 10;
const int GAS = 9;
const int Out = 11;
const int In = 12;

int Count = 0;

WidgetLED led(V1);
WidgetLED led1(V2);
WidgetLCD lcd(V3);
BlynkTimer timer;
void Sensor()
{
  if (digitalRead(In) == HIGH)
  {
    Count = Count + 1;
    lcd.clear();
    lcd.print(0, 0, "Person In Room:");
    lcd.print(0, 1, Count);
  }

  else if (digitalRead(Out) == HIGH)
  {
    Count = Count - 1;
    lcd.clear();
    lcd.print(0, 0, "Person In Room:");
    lcd.print(0, 1, Count);
  }

  if (digitalRead(RAIN) == LOW)
  {
    led.on();
    Blynk.notify("Its Raing Outside, Dont sorget Your Umbrella.");
  }

  if (digitalRead(GAS) == LOW)
  {
    led1.on();
    Blynk.notify("There Is a Gas Leak, Please Evacuate The House");
  }

  else
  {
    lcd.print(0, 0, "Person In Room:");
    lcd.print(0, 1, Count);
    led.off();
    led1.off();
  }
}

void setup()
{
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);

  pinMode(In, INPUT);
  pinMode(Out, INPUT);

  digitalWrite(RAIN, HIGH);

  pinMode(RAIN, INPUT_PULLUP);
  pinMode(GAS, INPUT);

  timer.setInterval(100l, Sensor);
}
void loop()
{
  Blynk.run();
  timer.run();
}
