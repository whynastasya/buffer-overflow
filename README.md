# Отчёт о проделанной практической работе 5

## Задание
Вариант 2 (номер студенческого билета Б0826)
`\#include <stdio.h>
\#include <stdlib.h>
\#include <sys/types.h>
\#include <unistd.h>

void shell() {
    setreuid(geteuid(), geteuid());
    system("/bin/bash");
}

void sup() {
    printf("Hey dude ! Waaaaazzaaaaaaaa ?!\\n");
}

void main()
{ 
    int var;
    void (\*func)()=sup;
    char buf\[128\];
    fgets(buf,133,stdin);
    func();
}`

### 1. Необходимо провести динамическую отладку программного обеспечения с бинарной уязвимостью 

Запустила докер контейнер с ОС ubuntu и установила все небходимые утилиты 

#### 1. Переполнение буфера

- Поставила брекпоинты на функции main() и fgets(buf,133,stdin)

![](https://github.com/user-attachments/assets/e71368d8-4e10-43bb-8cf2-3cc7d18873c2)

- Проверяем состояние памяти до переполнения, вводим длинную строчку и снова проверяем

![](https://github.com/user-attachments/assets/aeb18ec4-6bb4-492f-95ff-1cdbb6f956b6)

##### Данные за пределами buf перезаписаны, так как он имеет размер 128 байт, а в fgets указано чтение 133 байт. Это приводит к перезаписи данных за пределами буфера, включая указатель func.

#### 2. Перезапись указателя функции

Из-за переполнения буфера можно изменить значения func и заставить его указывать на функцию shell 
![](https://github.com/user-attachments/assets/d7258764-209e-43d0-bdf8-e4985f37de02)

##### Что, собственно, и видим - выполнилась функция shell и открылась оболочка /bin/bash

### 2. Проанализировать код и сделать кодревью, указав слабые места
- Невостребованная переменная var: Переменная var не используется в программе, её можно удалить, чтобы избежать ненужных затрат памяти.
- Неверный размер в fgets: Функция fgets(buf, 133, stdin) пытается читать 133 байта, что превышает размер буфера (128 байт). Это приведет к переполнению буфера, что создаёт уязвимость для изменения содержимого памяти.
- Отсутствие проверки возврата из fgets: Функция fgets может не выполнить успешное чтение, но нет проверки ошибки. Это может привести к непредсказуемым результатам, если ввод не был корректно прочитан.
- Уязвимость переполнения буфера: Переполнение буфера через fgets позволяет злоумышленнику перезаписать указатель func, который указывает на функцию sup(), и перенаправить его на функцию shell(). Это может привести к выполнению произвольного кода (например, запуску оболочки /bin/bash), что является серьёзной уязвимостью.
- Отсутствие явного возвращаемого значения в main(): Стандарт C требует, чтобы функция main возвращала значение (например, return 0;), чтобы явно указать успешное завершение программы.

### 3. Предложить исправление для кода с целью избежать ошибки

- ![upgraded_program.c]()
