#include <iostream>
#include <string>
#include <algorithm>
#include "stack.h"

int size(Stack *stack)
{
    return stack->top + 1;
}