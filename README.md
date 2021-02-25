# ATmega8Reobas

![Board photo](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Photo.jpg "Board photo")

Проект регулятора оборотов 3-х вентиляторов из ПК(под управлением Windows 7/10), посредством программы, которая работает на компьютере. 

Видео с демонстрацией работы:

https://youtu.be/8hW6mBzUgN4?list=PLEL7qGoBXwEaDuzdx020j9YMi9B89LieX

Схема простая, не было необходимости разводить её в PCB формате. Схема платы на контроллере ATmega8/Arduino Nano(ATmega328):

![Schematic ATmega8/ArduinoNano](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/Schematic_SoftReobasArduino_2021-02-25.png "Schematic ATmega8/ArduinoNano")

Проект схемы на EasyEDA:

https://easyeda.com/raznie.podelki/softreobasarduino

В качестве процессора выбран ATmega8 + ему нужен USB-UART преобразователь, можно взять готовую плату Arduino Nano(ATmega328), где он уже имеется на плате. 
Для перехода на Arduino Nano нужно закомментировать 17 и 18 строчки, и разкомментировать 12 и 13, как на картинке:

![ATmega8 or ATmega328](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/8or328.png "ATmega8 or ATmega328")

Исходники Arduino IDE:

https://github.com/techn0man1ac/SoftReobasArduino/tree/main/ATmega8Reobas/Code/Arduino%20IDE/ATmega8Reobas

![Windows10 screenshot app](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Win10Scrn.jpg "Windows10 screenshot app")

Программа для ПК(проверенно на Windows 10) написана на языке С#, скачать можно тут:

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/WinApp

Исходники программы для ПК Fans speed controller(Windows):

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/Code/Fans%20speed%20controller(Windows)/WindowsFormsApplication1


Ветка проекта на форуме Arduino:

http://arduino.ru/forum/proekty/programmno-upravlyaemyi-reobas
