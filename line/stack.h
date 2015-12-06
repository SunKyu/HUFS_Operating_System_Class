#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>
struct stack {
    int top;
    int arr[15];
};


void stack_init(struct stack* s);

int stack_is_empty(struct stack *s);
int stack_is_full(struct stack *s);
int stack_push (struct stack* s, int new_data);

int stack_pop (struct stack* s);
int stack_top (struct stack* s);

void stack_make_empty(struct stack *s);


void stack_print(struct stack *s);
#endif
