#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    INST_PUSH,  //0000 or 0x00
    INST_ADD,   //0100 or 0x01
    INST_PRINT  //0200 or 0x02
} Inst_Type;

typedef struct
{
    Inst_Type type; //4 bytes
    int operand;    //4 bytes
} Inst;

Inst program[] = {
    {.type = INST_PUSH, .operand = 35}, //35 = 2300 or 0x23
    {.type = INST_PUSH, .operand = 34}, //34 = 2200 or 0x22
    {.type = INST_ADD},
    {.type = INST_PRINT},
};

#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))

#define STACK_CAPACITY 1024

int stack[STACK_CAPACITY];
size_t stack_size = 0;

void stack_push(int value)
{
    assert(stack_size < STACK_CAPACITY);
    stack[stack_size++] = value;
}

int stack_pop(void)
{
    assert(stack_size > 0);
    return stack[--stack_size];
}

void save_program_to_file(const char *file_path)
{

    FILE *f = fopen(file_path, "wb");
    fwrite(program, sizeof(program[0]), PROGRAM_SIZE, f);
    fclose(f);
}

int main()
{

    for (size_t ip = 0; ip < PROGRAM_SIZE; ++ip)
    {

        save_program_to_file("program.vm");

        switch (program[ip].type)
        {
        case INST_PUSH:
        {
            stack_push(program[ip].operand);
            break;
        }
        case INST_ADD:
        {
            int a = stack_pop();
            int b = stack_pop();
            stack_push(a + b);
            break;
        }
        case INST_PRINT:
        {
            printf("%d\n", stack_pop());
            break;
        }

        default:
        {
            assert(0 && "Invalid instructions");
        }
        }
    }

    return 0;
}