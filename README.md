# ATmega8/Arduino Nano reobas

![Board photo](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Photo.jpg "Board photo")

Проект регулятора оборотов 3-х вентиляторов из ПК(под управлением Windows 7/10), посредством программы, которая работает на компьютере. Видео с демонстрацией работы:

https://youtu.be/8hW6mBzUgN4?list=PLEL7qGoBXwEaDuzdx020j9YMi9B89LieX

# Schematic:

![Schematic ATmega8/ArduinoNano](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/Schematic_SoftReobasArduino_2021-02-25.png "Schematic ATmega8/ArduinoNano")

Схема платы довольно простая, построенна на контроллерах ATmega8 или Arduino Nano(ATmega328), не было необходимости разводить её в PCB формате. 
Можно использовать как Arduino Nano, так и ATmega8, только в случае ATmega8 нужен USB-UART переходник подключить к J6 (скорость обмена 9600), а у Arduino Nano(ATmega328), где он уже имеется на плате. 5V для работы платы подавать лучше на J4, через защитный диод. 

Так же, можете ознакомится с моей статьей на Habr'е "Превращаем Arduino в полноценный AVRISP программатор":

https://habr.com/ru/post/247329/

Проект схемы на EasyEDA:

https://easyeda.com/raznie.podelki/softreobasarduino

# Arduino IDE:

Исходники к Arduino IDE:

https://github.com/techn0man1ac/SoftReobasArduino/tree/main/ATmega8Reobas/Code/Arduino%20IDE/ATmega8Reobas

В качестве процессора можно взять как ATmega8, так и Arduino Nano(по умолчанию в коде выбрано для Arduino Nano, или же ATmega328), в последнем случае нужно закомментировать 17 и 18 строчки, и разкомментировать 12 и 13, как на картинке ниже:

![ATmega8 or ATmega328](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/8or328.png "ATmega8 or ATmega328")

Этими строчками задается частота ШИМ примерно в 31 кГц(чтобы не было слышно писка вентиляторов) при условии, что контроллер тактируется от частоты 16МГц. 
Единственное, что, ATmega8 должна работать на частоте 16МГц, то есть тактироваться от внешнего кварца.

# Windows application:
 
![Windows10 screenshot app](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/Techn0man1ac%20FSC%20V0.1%20Win10Scrn.jpg "Windows10 screenshot app")

Программа "Techn0man1ac FSC V0.1" для ПК(проверенно на Windows 10), работает следующим образом - подключаете плату к компьютеру, выбираете в выпадающем списке "Port"(слева вверху), номер COM-порта USB-UART преобразователя железки, нажимаете "Connect" - всё, можно посылать плате комманды кнопками пользовательского интерфейса, значение каждой из них:
- "Send" - отправляет текущие значения, заданное ползунками "Fan 1", "Fan 2", "Fan 3"(по умолчанию это 127, отображается справа от ползунка) на микроконтроллер, который запоминает эти значения в свою EEPROM(энергонезависимую память), то есть даже после перезагрузки контроллер будет помнить записаные значения;
- "All fans max" - эта кнопка задает максимальную скорость для всех вентиляторов(тоже записывается в EEPROM);
- "Stop all fans" - полная остановка;
- "Reset" - Перезагрузка платы;
- "Project on GitHub" - кнопка которая приводит пользователя сюда, на страницу проекта.

Скачать программу "Techn0man1ac FSC V0.1" можно тут:
https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/WinApp

# С# sourse code:

Написана на языке С# в среде разработки "Microsoft Visual Studio Community 2019
Версия 16.9.2", исходники программы для ПК Fans speed controller(Windows):

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/Code/Fans%20speed%20controller(Windows)/WindowsFormsApplication1

# Arduino community support

Ветка проекта на форуме Arduino:

http://arduino.ru/forum/proekty/programmno-upravlyaemyi-reobas
