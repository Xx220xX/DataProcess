#include <cstdarg>
#include <cctype>
#include <cmath>

//
// Created by PC on 01/08/2019.
//
#include "DataProcess.h"

int len(const char *str) {
    int i = 0;
    for (; str[i] && str[i] != ':'; i++);
    return i;
}

int strLength(const char *str) {
    int i;
    for (i = 0; str[i]; ++i);
    return i;
}

int nextInt(const char *source, int *bg) {
    int aux = 0;
    if (bg == 0)
        bg = &aux;
    if (strLength(source) < *bg)
        return 0;
    int n = 0;
    char *p = (char *) (source + *bg);
    int i = 0;
    int achei = 0;
    for (; p[i]; i++) {
        if (isdigit(p[i])) {
            achei = 1;
            n = n * 10 + p[i] - '0';
        } else if (achei) {
            break;
        }
    }
    *bg = *bg + i;
    return n;
}

double nextDouble(const char *source, int *bg) {
    int aux = 0;
    if (bg == 0)
        bg = &aux;
    if (strLength(source) < *bg)
        return 0;

    int n = 0;
    int dec = 0;
    double b = 0;
    char *p = (char *) (source + *bg);
    int i = 0;
    int achei = 0;
    for (; p[i]; i++) {
        if (p[i] == '.' || p[i] == ',') {
            dec = 1;
            continue;
        }
        if (isdigit(p[i])) {
            achei = 1;
            n = n * 10 + p[i] - '0';
            if (dec)dec++;
        } else if (achei) break;
    }
    *bg = *bg + i;
    b = n;
    if (dec) {
        dec--;
        b = b * pow(10, -dec);
    }
    return b;
}


void nextStr(char *buf, int tam, const char *font, int *iat) {
    int i = 0, j;
    char *p = (char *) font + *iat;
    int escape = 0;
    for (i = 0; p[i] && i < tam; ++i) {
        if (p[i] == '[') {
            if (escape) {
                i++;
                break;
            } else {
                escape = 1;
            }
            continue;
        }
        escape = 0;
    }
    for (j = 0; p[i] && j < tam; i++) {
        if (p[i] != ']') {
            buf[j++] = p[i];
        } else if (p[i + 1] && p[i + 1] == ']') {
            i++;
            break;
        }
    }
    *iat = *iat + i;
    buf[j] = 0;

}

bool loadCommand(const char *source, const char *command, const char *format, ...) {
    int tam = len(command);
    int i, j;
    va_list args;

    int *d;
    float *f;
    double *g;
    char *s;

    if (len(source) != tam)return false;
    for (i = 0; i < tam; i++)
        if (source[i] != command[i])return false;

    if (!source[i])return true; //fim da fonte nao ha dados a serem lidos
    i++;//sai de cima do ':'
    va_start(args, format);
    for (j = 0; format[j]; j++) {
        switch (format[j]) {
            case 'd':
                d = va_arg(args, int *);
                *d = nextInt(source, &i);
                break;
            case 'f':
                f = va_arg(args, float *);
                *f = (float) nextDouble(source, &i);
                break;
            case 'g':
                g = va_arg(args, double *);
                *g = nextDouble(source, &i);
                break;
            case 's':
                s = va_arg(args, char *);
                tam = nextInt(format, &j);
                nextStr(s, tam, source, &i);// return str entre [[ ]]
                break;
        }
    }
    va_end(args);
    return true;
}


