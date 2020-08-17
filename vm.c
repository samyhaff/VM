#include <stdio.h>
#include <stdbool.h>

int fetch(void);
void eval(int instr);

typedef enum {
    A, B, C, D, E, F, IP, SP, NUM_OF_REGISTERS
    } Registers;

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

int stack[256];
bool running = true;
int registers[NUM_OF_REGISTERS];
#define sp (registers[SP])
#define ip (registers[IP])

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    SET, 0,
    HLT
};

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    return 0;
}

int fetch() { 
    return program[ip];
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = program[++ip];
            break;
        }
        case POP: {
            printf("%d\n", stack[sp--]);
            break;
        }
        case ADD: {
            int a = stack[sp--];
            int b = stack[sp--];
            int r = a + b;
            stack[++sp] = r;
            break;
        }
        case SET: {
            ip = program[++ip] - 1;
        }
    }
}
