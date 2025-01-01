#include <stdint.h>
#include <stdlib.h>

// Exercise: https://leetcode.com/problems/valid-parentheses/
//
// 0ms, beats 100%, uses ~5KB of statically allocated memory, no dyn memory

typedef uint8_t bracket_t;
#define PAREN   ((bracket_t)1)
#define BRACKET ((bracket_t)2)
#define CURLY   ((bracket_t)3)

#define STACK_SIZE 5000
typedef struct {
    bracket_t data[STACK_SIZE];
    int16_t top;
} bracket_stack_t;

typedef uint8_t stack_err_t;
#define STACK_ERR_OK   ((stack_err_t)0)
#define STACK_ERR_FULL ((stack_err_t)1)

static inline void init_bracket_stack(bracket_stack_t *stack) {
    stack->top = -1;
}

static inline bool bracket_stack_is_empty(bracket_stack_t *stack) {
    return stack->top == -1;
}

static inline stack_err_t bracket_stack_push(bracket_stack_t *stack, bracket_t b) {
    if (stack->top+1 >= STACK_SIZE) return STACK_ERR_FULL;
    stack->data[++stack->top] = b;
    return STACK_ERR_OK;
}

static inline bracket_t *bracket_stack_pop(bracket_stack_t *stack) {
    if (stack->top == -1) return NULL;
    return &stack->data[stack->top--];
}

bool isValid(char *s) {
    // parentheses, braces, curly braces
    bracket_stack_t stack;
    init_bracket_stack(&stack);
    char c;
    bracket_t *last;
    stack_err_t stack_err = 0;
    while ((c = *s++) != '\0') {
        switch (c) {
            case '(':
                stack_err = bracket_stack_push(&stack, PAREN);
                if (stack_err != STACK_ERR_OK) return false;
                break;
            case ')':
                last = bracket_stack_pop(&stack);
                if (last == NULL || *last != PAREN) return false;
                break;
            case '[':
                stack_err = bracket_stack_push(&stack, BRACKET);
                if (stack_err != STACK_ERR_OK) return false;
                break;
            case ']':
                last = bracket_stack_pop(&stack);
                if (last == NULL || *last != BRACKET) return false;
                break;
            case '{':
                stack_err = bracket_stack_push(&stack, CURLY);
                if (stack_err != STACK_ERR_OK) return false;
                break;
            case '}':
                last = bracket_stack_pop(&stack);
                if (last == NULL || *last != CURLY) return false;
                break;
        }
    }
    return bracket_stack_is_empty(&stack);
}
