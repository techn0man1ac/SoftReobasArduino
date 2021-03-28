#include <EEPROM.h>  // библиотека для работы с энергонезависимой памятью
// By Techn0man1ac https://github.com/techn0man1ac/SoftReobasArduino/   
byte val1 = 0, val2 = 0, val3 = 0;
// тип байт идеально подходит, диапазон 0-255
unsigned long previousMillis = 0;
#define interval 1000

void setup()
{

  /////////////////////////////////////////////// для ATmega 328p(по умолчанию для Arduino Nano)
  TCCR1A = 0x01; // зададим делитель для ШИМа N = 1
  TCCR2B = 0x01; // тоже самое
  //////////////////////////////////////////////////////

  //////////////////////////////////////////////// для ATmega 8А
  //TCCR1B = 0b00000001; // зададим делитель для ШИМа N = 1
  //TCCR2 =  0b01101001; // зададим делитель для ШИМа N = 1
  //////////////////////////////////////////////////////
  /*
    TCCR1B = 0x05 (N = 1024), 16000000(16 МГц) / 1024 / 256 = 61(30.5) Гц
    TCCR1B = 0x04; (N = 256), 16000000(8000000) / 256 / 256 = 224(112) Гц
    TCCR1B = 0x03 (N = 64), 16000000(8000000) / 64 / 256 = 976(488) Гц
    TCCR1B = 0x02 (N = 8), 16000000(8000000) / 8 / 256 = 7812(3906) Гц
    TCCR1B = 0x01 (N = 1), 16000000(8000000) / 1 / 256 = 62500(31250) Гц
  */

  Serial.begin(9600);    // скорость компорта бод
  // При вызове parseInt() задержка ожидания последующего символа по умолчанию 1 секунда.
  // Функцией setTimeout() можно уменьшить эту задержку. Например на 4 миллисекунды, setTimeout(4);.
  // Чем выше скорость Serial.begin, тем меньше потребуется значение setTimeout.
  Serial.setTimeout(4);  // 4

  val1 = EEPROM.read(1); //считаем что у нас записано в
  val2 = EEPROM.read(2); // энергонезависимой памяти
  val3 = EEPROM.read(3); // там у нас храниться скорость

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(9, HIGH);    // разгон кулеров
  delay(2000);
  analogWrite(9, val1);  // выставляем скорость
  digitalWrite(10, HIGH);    // чтобы стартануть
  delay(2000);
  analogWrite(10, val2); // диапазон значений от 0 до 255
  digitalWrite(11, HIGH);
  delay(2000);
  analogWrite(11, val3);

  /*
    ...
  */

}

void loop()
{

  /*
    ...
  */

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (Serial.available()) // если данные идут то
    {
      char data = Serial.read();

      if (data == 'd') { // ловим мимвол "d" и приступаем до
        val1 = Serial.parseInt(); // получений данных
        val2 = Serial.parseInt(); // данные должны быть в формате
        val3 = Serial.parseInt(); // n255.255.255 или напр.: n64.112.230

        EEPROM.write(1, val1); //записываем полученые данные в
        EEPROM.write(2, val2); // энергонезависимую память
        EEPROM.write(3, val3);
        delay(2000); // обязательно ждём 2 сек, для защиты
      }

      if (data == 'n') { // ловим символ "n" - норм режим
        val1 = EEPROM.read(1); //считаем что у нас записано в
        val2 = EEPROM.read(2); // энергонезависимой памяти
        val3 = EEPROM.read(3); // там у нас храниться скорость
      }

      if (data == 'm') { // ловим символ "m" - макс скорость
        val1 = 255;
        val2 = 255;
        val3 = 255;
      }

      if (data == 's') { // ловим символ "s" - стоп
        val1 = 0;
        val2 = 0;
        val3 = 0;
      }

      if (data == 'r') { // ловим символ "r" - значит нужно перезагрузиться
        reboot();
      }

      Serial.flush();  // чистим буфер

      analogWrite(9, val1); // задаём скорость для 3 куллеров
      analogWrite(10, val2);
      analogWrite(11, val3);
    }

    /////////////////////////////////////////////////////////////

    Serial.print(val1); // отправляем значение кулеров в ком порт
    Serial.print(","); // чисто для отладки
    Serial.print(val2); // хотя... может и пускай будет
    Serial.print(",");
    Serial.println(val3);

    /////////////////////////////////////////////////////////////
  }

  /*
    ...
  */

}

void reboot() // функция ресета
{
  Serial.end ();  // if necessary

  asm ("cli");          // interrupts off

  // reset USART to reset defaults
#ifdef __AVR_ATmega8__
  UDR = 0;
  UCSRA = _BV (UDRE);
  UCSRB = 0;
  UCSRC = _BV (URSEL) | _BV (UCSZ1) |  _BV (UCSZ0);
  UBRRL = 0;
  UBRRH = 0;
#else
  UDR0   = 0;
  UCSR0A = _BV (UDRE0);
  UCSR0B = 0;
  UCSR0C = _BV (UCSZ01) |  _BV (UCSZ00);
  UBRR0L = 0;
  UBRR0H = 0;
#endif

  asm volatile ("eor r1,r1");     // make sure zero-register is zero
  asm volatile ("ldi r16,0xFF");  // end of RAM (0xFF)
  asm volatile ("sts 0x5E,r16");  // SPH
  asm volatile ("sts 0x5D,r16");  // SPL
  asm volatile ("eor r31,r31");   // Clear Z register
  asm volatile ("eor r30,r30");
  asm volatile ("ijmp");          // jump to (Z)
}
