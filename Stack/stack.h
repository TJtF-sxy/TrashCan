#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

enum CmdId{
    CMD_UNKNOWN = 0,
  CMD_PUSH,
  CMD_POP,
  CMD_QUERY,    
  CMD_SIZE,
};

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

void push(Stack *stack, int value);
int pop(Stack *stack);
int query(Stack *stack);
int size(Stack *stack);
CmdId parse_command(const char* name);

#endif // STACK_H