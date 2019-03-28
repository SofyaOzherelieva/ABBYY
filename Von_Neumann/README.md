## Виртуальная машина построенная на архитектуре фон Неймана

#### cpu.h:

1. Ассемблер:

Переводит код на ассемблере в бинарный код.

Запуск:

`g++ compile.cpp -o compile`

`./compile <file with assembler code> <output file>`

Пример:

`./compile inputRecFib myBinFile`

2. Дизассемблер:

Переводит бинарный код в код на ассемблере.

Запуск:

`g++ decompile.cpp -o decompile`

`./decompile <binary file with code> <output file>`

Пример:

`./decompile myBinFile myDecompFile`

3. Виртуальная машина:

Исполянет бинарный код.

Запуск:

`g++ run.cpp -o run`

`./run <binary file with code>`

Пример:

`./run myBinFile`


#### Поддерживает:
* рекурсию
* текстовый вывод
* статически размещенные данные
* вызовы функций


#### Описание команд содержится в commands.h
