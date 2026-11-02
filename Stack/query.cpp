#include <iostream>
#include <string>
#include <algorithm>
#include "stack.h"

int query(Stack *stack)
{
    if (stack->top < 0)
    {
        std::cerr << "Stack is empty!" << std::endl;
        return -1; // Return an error value
    }
    return stack->data[stack->top];
}