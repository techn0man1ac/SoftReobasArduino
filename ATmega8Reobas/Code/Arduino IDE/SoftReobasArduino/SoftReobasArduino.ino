// SoftReobasArduino By Serhii Trush for MIT License
// https://github.com/techn0man1ac/SoftReobasArduino/

#include <EEPROM.h>                 // EEPROM librarry
byte val1 = 0, val2 = 0, val3 = 0;  // byte type is ideal 0..255

#define interval 1000  // ewery 1 sec. work for datas

unsigned long previousMillis = 0;

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

  Serial.begin(9600);

  Serial.setTimeout(4);  // time for one symbol is 4 ms - good working

  val1 = EEPROM.read(1);  // Read EEPROM Memory
  val2 = EEPROM.read(2);  // PWM duty cycle
  val3 = EEPROM.read(3);  // Every fan have own EEPROM Memory value

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(9, HIGH);  // forse start all fans
  delay(2000);
  analogWrite(9, val1);  // set speed
  digitalWrite(10, HIGH);
  delay(2000);
  analogWrite(10, val2);  // 0..255(0..100%) - PWM duty cycle
  digitalWrite(11, HIGH);
  delay(2000);
  analogWrite(11, val3);

  /*
    You initialization here...
  */
}

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (Serial.available())  // if datas receive
    {
      char data = Serial.read();

      if (data == 'd') {           // catch the symbol "d" and proceed to
        val1 = Serial.parseInt();  // receiving data(PWM duty cycle)
        val2 = Serial.parseInt();  // data must be in the format
        val3 = Serial.parseInt();  // d255.255.255 or, example d64.112.230

        EEPROM.write(1, val1);  // write datas in
        EEPROM.write(2, val2);  // non volatile memory(EEPROM)
        EEPROM.write(3, val3);
        delay(2000);  // important wait 2 seconds, for protect
      }

      if (data == 'n') {        // catch the symbol "n" - normal mode
        val1 = EEPROM.read(1);  // read what we have into EEPROM
        val2 = EEPROM.read(2);  // it's speed level
        val3 = EEPROM.read(3);
      }

      if (data == 'm') {  // catch the symbol "m" - max speed
        val1 = 255;
        val2 = 255;
        val3 = 255;
      }

      if (data == 's') {  // catch the symbol "s" - all stop
        val1 = 0;
        val2 = 0;
        val3 = 0;
      }

      if (data == 'r') {  // catch the symbol "r" - board reboot
        reboot();
      }

      Serial.flush();  // clear buffer

      analogWrite(9, val1);  // set fans speed
      analogWrite(10, val2);
      analogWrite(11, val3);
    }

    /////////////////////////////////////////////////////////////

    Serial.print(val1);  // Transmit values of speed
    Serial.print(",");   // just for debug
    Serial.print(val2);
    Serial.print(",");
    Serial.println(val3);

    /////////////////////////////////////////////////////////////
  }

  /*
    You code here...
  */
}

void reboot()  // Reset function
{
  Serial.end();  // if necessary

  asm("cli");  // interrupts off

  // reset USART to reset defaults
#ifdef __AVR_ATmega8__
  UDR = 0;
  UCSRA = _BV(UDRE);
  UCSRB = 0;
  UCSRC = _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0);
  UBRRL = 0;
  UBRRH = 0;
#else
  UDR0 = 0;
  UCSR0A = _BV(UDRE0);
  UCSR0B = 0;
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  UBRR0L = 0;
  UBRR0H = 0;
#endif

  asm volatile("eor r1,r1");     // make sure zero-register is zero
  asm volatile("ldi r16,0xFF");  // end of RAM (0xFF)
  asm volatile("sts 0x5E,r16");  // SPH
  asm volatile("sts 0x5D,r16");  // SPL
  asm volatile("eor r31,r31");   // Clear Z register
  asm volatile("eor r30,r30");
  asm volatile("ijmp");  // jump to (Z)
}
