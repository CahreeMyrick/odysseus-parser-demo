#pragma once

struct Score {
    int value;
};

int add(int a, int b);
int twice(int value);

class Calculator {
public:
    int total(int a, int b) {
        return add(a, b);
    }
};
