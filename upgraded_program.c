#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void shell() {
    setreuid(geteuid(), geteuid());
    system("/bin/bash");
}

void sup() {
    printf("Hey dude ! Waaaaazzaaaaaaaa ?!\n");
}

int main() // возвращаем int, как того требует стандарт
{ 
    void (*func)() = sup; // указатель на функцию, изначально указывает на sup
    char buf[128]; // размер буфера ограничен

    // безопасное чтение данных с проверкой на ошибку
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        perror("Error reading input");
        return 1; // ошибка при чтении данных
    }

    // дополнительная проверка на переполнение
    if (strlen(buf) >= sizeof(buf)) {
        fprintf(stderr, "Input too large\n");
        return 1;
    }

    func(); // вызов функции через указатель

    return 0; // успешное завершение программы
}
