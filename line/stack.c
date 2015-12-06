#include "stack.h"
void stack_init(struct stack* s){
   s->top = -1;
}

int stack_is_empty(struct stack *s){
    if (s->top == -1){
        return 1;
    }
    else
        return -1;
}
int stack_is_full(struct stack *s){
    if (s->top == 14){
        return 1;
    }
    else
        return -1;
}
int stack_push (struct stack* s, int new_data){
    if (stack_is_full(s) == 1){
        printf("Error, stack is full\n");
        return -1;
    }
    s->arr[(s->top)+1] = new_data;
    s->top +=1;
}

int stack_pop (struct stack* s){
    if (stack_is_empty(s) == 1){
        printf("Error, stack is empty\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

void stack_make_empty(struct stack *s){
    s->top = -1;
}


void stack_print(struct stack *s){
    int index = s->top;
    for (int i = 0; i<index ; i++){
        printf("%d - ", s->arr[i]);
    }
}
