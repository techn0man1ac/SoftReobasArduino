// SoftReobasArduino By Serhii Trush for MIT License
// https://github.com/techn0man1ac/SoftReobasArduino/

#include <stdint.h>
#include <EEPROM.h>           // EEPROM librarry

#define INTERVAL_1S                     (1000)  // ewery 1 sec. work for datas
#define ZERO_FAN_SPEED                  (0)
#define MAX_FAN_SPEED                   (255)
#define UART_BAUDRATE                   (9600)
#define UART_SINGLE_CHAR_TIMEOUT_MS     (4)

uint8_t fan1Speed = ZERO_FAN_SPEED;
uint8_t fan2Speed = ZERO_FAN_SPEED;
uint8_t fan3Speed = ZERO_FAN_SPEED;  // byte type is ideal 0..255

uint32_t previousMillis = 0;

void setup() {

  /////////////////////////////////////////////// for ATmega 328p(defalt, Arduino Nano 16MHz CPU work freq.)
  // Pins D9 and D10 - 31.4 kHz
    TCCR1A = 0b00000001;  // 8bit
    TCCR1B = 0b00000001;  // x1 phase correct
    // Pins D3 and D11 - 31.4 kHz
    TCCR2B = 0b00000001;  // x1
    TCCR2A = 0b00000001;  // phase correct
  // https://nerdytechy.com/how-to-change-the-pwm-frequency-of-arduino/
  //////////////////////////////////////////////////////

  // TODO remove unused code

  //////////////////////////////////////////////// for ATmega 8А(16MHz CPU work freq.)
  // TCCR1B = 0b00000001; // set divider for PWM N = 1
  // TCCR2 =  0b01101001; // set divider for PWM N = 1
  //////////////////////////////////////////////////////
  /*
    TCCR1B = 0x05 (N = 1024), 16000000(16 MHz) / 1024 / 256 = 61(30.5) Hz
    TCCR1B = 0x04; (N = 256), 16000000(8000000) / 256 / 256 = 224(112) Hz
    TCCR1B = 0x03 (N = 64), 16000000(8000000) / 64 / 256 = 976(488) Hz
    TCCR1B = 0x02 (N = 8), 16000000(8000000) / 8 / 256 = 7812(3906) Hz
    TCCR1B = 0x01 (N = 1), 16000000(8000000) / 1 / 256 = 62500(31250) Hz
  */
  S
    Serial.begin(UART_BAUDRATE);
    Serial.setTimeout(UART_SINGLE_CHAR_TIMEOUT_MS);  // time for one symbol is 4 ms - good working

    fan1Speed = EEPROM.read(1);  // Read EEPROM Memory
    fan2Speed = EEPROM.read(2);  // PWM duty cycle
    fan3Speed = EEPROM.read(3);  // Every fan have own EEPROM Memory value

    pinMode(9, OUTPUT);  // Fan1(CN1)
    pinMode(10, OUTPUT); // Fan2(CN2)
    pinMode(11, OUTPUT); // Fan3(CN3)

    digitalWrite(9, HIGH);  // force start all fans
    delay(2000);
    analogWrite(9, fan1Speed);  // set speed
    digitalWrite(10, HIGH);
    delay(2000);
    analogWrite(10, fan2Speed);  // 0..255(0..100%) - PWM duty cycle
    digitalWrite(11, HIGH);
    delay(2000);
    analogWrite(11, fan3Speed);

  /*
    You initialization here...
  */
}

void loop() {
    uint32_t currentMillis = millis();

    if (currentMillis - previousMillis > INTERVAL_1S) {
        previousMillis = currentMillis;

        if (Serial.available())  // if data receive
        {
            char data = Serial.read();

            switch (data) {
                case 'd':  // catch the symbol "d" and proceed to
                    fan1Speed = Serial.parseInt();  // receiving data(PWM duty cycle)
                    fan2Speed = Serial.parseInt();  // data must be in the format
                    fan3Speed = Serial.parseInt();  // d255.255.255 or, example d64.112.230

                    EEPROM.write(1, fan1Speed);  // write datas in
                    EEPROM.write(2, fan2Speed);  // non volatile memory(EEPROM)
                    EEPROM.write(3, fan3Speed);
                    delay(2000);  // important wait 2 seconds, for protect
                    break;

                case 'n':  // catch the symbol "n" - normal mode
                    fan1Speed = EEPROM.read(1);  // read what we have into EEPROM
                    fan2Speed = EEPROM.read(2);  // it's speed level
                    fan3Speed = EEPROM.read(3);
                    break;

                case 'm':  // catch the symbol "m" - max speed
                    fan1Speed = MAX_FAN_SPEED;
                    fan2Speed = MAX_FAN_SPEED;
                    fan3Speed = MAX_FAN_SPEED;
                    break;

                case 's':  // catch the symbol "s" - all stop
                    fan1Speed = ZERO_FAN_SPEED;
                    fan2Speed = ZERO_FAN_SPEED;
                    fan3Speed = ZERO_FAN_SPEED;
                    break;

                case 'r':  // catch the symbol "r" - board reboot
                    reboot();
                    break;

                default:
                    break; // unrecognized char
            }

            Serial.flush();  // clear buffer

            analogWrite(9, fan1Speed);  // set fans speed
            analogWrite(10, fan2Speed);
            analogWrite(11, fan3Speed);
        }

        Serial.print(fan1Speed);  // Transmit values of speed
        Serial.print(",");   // just for debug
        Serial.print(fan2Speed);
        Serial.print(",");
        Serial.println(fan3Speed);
    }
}
