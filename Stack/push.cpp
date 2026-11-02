#include <iostream>
#include <string>
#include <algorithm>
#include "stack.h"

void push(Stack *stack, int value)
{
    if (stack->top >= stack->capacity - 1)
    {
        std::cerr << "Stack overflow!" << std::endl;
        return;
    }
    stack->data[++stack->top] = value;
}