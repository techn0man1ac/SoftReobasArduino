# ATmega8Reobas

Проект регулятора оборотов 3 вентиляторов из ПК(под управлением Windows 7/10), посредством программы, работабщей на компьютере. 

Видео с демонстрацией работы:

https://youtu.be/8hW6mBzUgN4?list=PLEL7qGoBXwEaDuzdx020j9YMi9B89LieX

В качестве процессора выбран ATmega8 + ему нужен USB-UART преобразователь, можно взять готовую плату Arduino Nano(ATmega328), где он уже имеется на плате. 
Для перехода на Arduino Nano нужно закомментировать 17 и 18 строчки, и разкомментировать 12 и 13, как на картинке:

![ATmega8 or ATmega328](https://raw.githubusercontent.com/techn0man1ac/SoftReobasArduino/main/ATmega8Reobas/Img/8or328.png "ATmega8 or ATmega328")

Фотография платы собранной на макетке:

![Board photo](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Photo.jpg "Board photo")

Схема простая, не было необходимости разводить её в PCB формате.

Схема платы на контроллере ATmega8:

![Schematic ATmega8](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Schematic.jpg "Schematic ATmega8")

Скрин программы для ПК(проверенно на Windows 10):

![Win10 screenshot app](https://raw.githubusercontent.com/techn0man1ac/ATmega8Reobas/main/ATmega8Reobas/Img/Win10Scrn.jpg "Win10 screenshot app")

Скачать можно тут:

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/WinApp

Исходники программы для ПК Fans speed controller(Windows):

https://github.com/techn0man1ac/ATmega8Reobas/tree/main/ATmega8Reobas/Code/Fans%20speed%20controller(Windows)/WindowsFormsApplication1

Исходники Arduino IDE:

https://github.com/techn0man1ac/SoftReobasArduino/tree/main/ATmega8Reobas/Code/Arduino%20IDE/ATmega8Reobas

Ветка проекта на форуме Arduino:

http://arduino.ru/forum/proekty/programmno-upravlyaemyi-reobas
