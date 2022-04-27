#include <stdbool.h>

typedef enum {INT_TYPE, DOUBLE_TYPE, STR_TYPE, NULL_TYPE, CONS_TYPE} valueType;
// grace is here
struct Value {
    valueType type; // type will also have a CONS_TYPE as an option
    union {
        int i;
        double d;
        char c;

        struct ConsCell {
            struct Value *car;
            struct Value *cdr;
        } c;       
    };
};

typedef struct Value Value;

// Create a new NULL_TYPE value node.
Value *makeNull(){

}

// Create a new CONS_TYPE value node.
Value *cons(Value *newCar, Value *newCdr){

}

// Display the contents of the linked list to the screen in some kind of
// readable format
void display(Value *list){
    Value *cur = list;
    while (cur != NULL) {
        printf("value = %i\n", cur->value);
        cur = cur->next;
    }
}

// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory whatsoever between the original list and the new one.
Value *reverse(Value *list);

// Frees up all memory directly or indirectly referred to by list. This includes strings.
void cleanup(Value *list);

// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
Value *car(Value *list);

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
Value *cdr(Value *list);

// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isNull(Value *value);

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(Value *value);
