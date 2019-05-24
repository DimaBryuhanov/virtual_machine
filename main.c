#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    INST_PUSH,
    INST_ADD,
    INST_PRINT
} Inst_Type;

typedef struct
{
    Inst_Type type;
    int operand;
} Inst;

Inst program[] = {
    {.type = INST_PUSH, .operand = 35},
    {.type = INST_PUSH, .operand = 34},
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

int main()
{

    for (size_t ip = 0; ip < PROGRAM_SIZE; ++ip)
    {
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