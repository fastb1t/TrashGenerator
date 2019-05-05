# TrashGenerator

Генератор файлов. Иногда нужно протестировать программу на файлах разных размеров и с разным содержимым, программа TrashGenerator поможет в этом.

## Использование

    TrashGenerator
        -h | --help                         - Показать справку по командам.
        -f | --file     [file]              - Имя для файла. Если вы указали более одного файла, то укажите [%] в имени файла,
                                                чтобы указать номер файла, в противном случае будет создан только один файл.
                                                Для примера: filename[%].dat
        -n | --files    [n]                 - Количество файлов.
        -b | --bytes    [n]                 - Количество байтов.
        -s | --size     [fixed | random]    - Размер файла. Если --size равно fixed, тогда файл будет создан с фиксированным размером,
                                                а если --size равно random, то файл будет создан со случайным размером,
                                                максимальное значение которого будет таким, какое вы указали в --bytes.
## Например:

### Создание пустого файла.
    TrashGenerator -f file.dat

### Создание файла случайного размера со случайным содержимым.
    TrashGenerator -f file.dat -s random

### Создание файла размером 1024 байт со случайным содержимым.
    TrashGenerator -f file.dat -b 1024

### Создание пяти файлов размером 1024 байт со случайным содержимым.
    TrashGenerator -f file[%].dat -n 5 -b 1024

### Создание пяти файлов случайного размера со случайным содержимым.
    TrashGenerator -f file[%].dat -n 5 -s random

### Создание пяти файлов случайного размера, не превышающего 1024 байт, со случайным содержимым.
    TrashGenerator -f file[%].dat -n 5 -b 1024 -s random


## Сборка:

### Linux:
    sh build.sh

### Windows:
    build.bat

## Тестировалось в:
    Windows 7 x64
    Linux Ubuntu Server

## Тестировалось компиляторами:
    GCC-8.2.0-3
