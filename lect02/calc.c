#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "사용법: %s <숫자> <연산자> <숫자>\n", argv[0]);
        return 1;
    }

    char expr[100] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expr, argv[i]);
        if (i < argc - 1) strcat(expr, " ");
    }

    double num1, num2;
    char op;

    if (sscanf(expr, "%lf %c %lf", &num1, &op, &num2) != 3) {
        fprintf(stderr, "입력 오류: 예) %s 3 + 4\n", argv[0]);
        return 1;
    }

    double result = 0;

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case 'x':  
        case 'X':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                fprintf(stderr, "오류: 0으로 나눌 수 없습니다.\n");
                return 1;
            }
            result = num1 / num2;
            break;
        default:
            fprintf(stderr, "오류: 지원하지 않는 연산자입니다.\n");
            return 1;
    }

    if (result == (int)result) {
        printf("%d\n", (int)result);
    } else {
        printf("%.6f\n", result);
    }
    return 0;
}

