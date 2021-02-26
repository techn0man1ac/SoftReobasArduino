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

В качестве процессора можно взять как ATmega8, так и Arduino Nano, в последнем случае нужно закомментировать 17 и 18 строчки, и разкомментировать 12 и 13, как на картинке ниже:
![ATmega8 or ATmega328](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/8or328.png "ATmega8 or ATmega328")

# Windows application:
 
![Windows10 screenshot app](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Win10Scrn.jpg "Windows10 screenshot app")

Программа для ПК(проверенно на Windows 10) написана на языке С#, скачать можно тут:

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/WinApp

# С# sourse code:

Исходники программы для ПК Fans speed controller(Windows):

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/Code/Fans%20speed%20controller(Windows)/WindowsFormsApplication1


# Arduino community support

Ветка проекта на форуме Arduino:

http://arduino.ru/forum/proekty/programmno-upravlyaemyi-reobas
