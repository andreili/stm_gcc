# STM32F10x template
Шаблон проекта на STM32F10x_md для сборки через qmake с использованием arm-none-eabi-gcc.

Для сборки проекта необходимо выполнить команды:

    qmake -o Makefile -spec cortex-m3 test_app.pro
    make debug (make release)

После завершения сборки в каталоге сборки будут находиться 2 файла:
 - test_app.bin - Бинарный файл прошивки для МК;
 - test_app.lst - Дизассемблерированный файл программы.
