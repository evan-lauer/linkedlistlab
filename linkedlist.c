#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>
#include "linkedlist.h"
#include "value.h"


// Create a new NULL_TYPE value node.
Value *makeNull(){
    Value *val = (Value *)malloc(sizeof(Value));
    val->type = NULL_TYPE;
    return val;
}

// Create a new CONS_TYPE value node.
Value *cons(Value *newCar, Value *newCdr){
    Value *val = (Value *)malloc(sizeof(Value));
    val->type = CONS_TYPE;
    // confusing ahhg  val->c
    return val;
}


// Utility to make it less typing to get car value. Use assertions to make sure
// that this is a legitimate operation.
Value *car(Value *list){
    assert(list->type != NULL_TYPE);
    return list->c.car;
}

// Utility to make it less typing to get cdr value. Use assertions to make sure
// that this is a legitimate operation.
Value *cdr(Value *list){
    assert(list->type != NULL_TYPE);
    return list->c.cdr;
}

// Utility to check if pointing to a NULL_TYPE value. Use assertions to make sure
// that this is a legitimate operation.
bool isNull(Value *value){
    return value->type == NULL_TYPE;
}

// Display the contents of the linked list to the screen in some kind of
// readable format
void display(Value *list){
    Value *cur = list;
    while (cur->type != NULL_TYPE) {
        if (list->type == INT_TYPE){
            printf("value = %d\n", car(cur)->i);
        }
        if (list->type == DOUBLE_TYPE){
            printf("value = %lf\n", cur->c.car->d);
        }
        if (list->type == STR_TYPE){
            printf("value = %s\n", cur->c.car->s);
        }
        cur = list->c.cdr->c.car;
    }
}

// Return a new list that is the reverse of the one that is passed in. All
// content within the list should be duplicated; there should be no shared
// memory whatsoever between the original list and the new one.
Value *reverse(Value *list){
    Value* cur = list;
    Value* head = makeNull();
    while(cur->type != NULL_TYPE)
    {
        Value* newCar = car(cur);
        Value* newConsCell = cons(newCar, head);
        head = newConsCell;
        cur = cur->c.cdr;
    }
    head->type = CONS_TYPE;
    head->c.car = car(cdr(cur));
    head->c.cdr = cur;
    return head;
}

// Frees up all memory directly or indirectly referred to by list. This includes strings.
void cleanup(Value *list){
    Value *cur = list;
    while (!isNull(cur)){
        Value *next = cdr(cur);
        free(cur);
        cur = next;
    }
}

// Measure length of list. Use assertions to make sure that this is a legitimate
// operation.
int length(Value *value){
    Value *cur = value;
    assert(isNull(cur));
    int length = 0;
    while (!isNull(cur)){
        Value *next = cdr(cur);
        length++;
        cur = next;
    }
    return length;
}


void testForward(Value *head, int correctLength, bool exemplary) {
  Value *value = head;
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(1 == car(value)->d);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("2.0s", car(value)->s));

    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("3.0s", car(value)->s));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(4 == car(value)->d);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("5.0s", car(value)->s));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(6 == car(value)->d);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(INT_TYPE == car(value)->type);
  assert(7 == car(value)->i);

  value = cdr(value);
  assert(NULL_TYPE == value->type);

  assert(correctLength == length(head));
  assert(!isNull(head));
}

void testBackward(Value *head, int correctLength, bool exemplary) {
  Value *value = head;

  assert(CONS_TYPE == value->type);
  assert(INT_TYPE == car(value)->type);
  assert(7 == car(value)->i);

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(6 == car(value)->d);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("5.0s", car(value)->s));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(4 == car(value)->d);

  if (exemplary) {
    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("3.0s", car(value)->s));

    value = cdr(value);
    assert(CONS_TYPE == value->type);
    assert(STR_TYPE == car(value)->type);
    assert(!strcmp("2.0s", car(value)->s));
  }

  value = cdr(value);
  assert(CONS_TYPE == value->type);
  assert(DOUBLE_TYPE == car(value)->type);
  assert(1 == car(value)->d);

  value = cdr(value);
  assert(NULL_TYPE == value->type);

  assert(correctLength == length(head));
  assert(!isNull(head));
}


int main(int argc, char **argv) {

  bool exemplary = false;
  if (argc == 2 && !strcmp(argv[1], "E")) {
    exemplary = true;
  }

  Value *head = makeNull();
  int correctLength = 0;
  assert(length(head) == correctLength);

  Value *reverseLengthZero = reverse(head);
  assert(length(reverseLengthZero) == correctLength);
  cleanup(reverseLengthZero);

  Value *val1 = malloc(sizeof(Value));
  val1->type = INT_TYPE;
  val1->i = 7;
  head = cons(val1,head);
  correctLength++;
  assert(length(head) == correctLength);

  Value *reverseLengthOne = reverse(head);
  assert(length(reverseLengthOne) == correctLength);
  cleanup(reverseLengthOne);

  Value *val2 = malloc(sizeof(Value));
  val2->type = DOUBLE_TYPE;
  val2->d = 6.00;
  head = cons(val2,head);
  correctLength++;
  assert(length(head) == correctLength);

  if (exemplary) {
    Value *val3 = malloc(sizeof(Value));
    val3->type = STR_TYPE;
    char *text = "5.0s";
    val3->s = malloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val3->s,text);
    head = cons(val3,head);
    correctLength++;
    assert(length(head) == correctLength);

  }

  Value *val4 = malloc(sizeof(Value));
  val4->type = DOUBLE_TYPE;
  val4->d = 4.00000;
  head = cons(val4,head);
  correctLength++;
  assert(length(head) == correctLength);

  if (exemplary) {
    Value *val5 = malloc(sizeof(Value));
    val5->type = STR_TYPE;
    char *text = "3.0s";
    val5->s = malloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val5->s,text);
    head = cons(val5,head);
    correctLength++;
    assert(length(head) == correctLength);

    Value *val6 = malloc(sizeof(Value));
    val6->type = STR_TYPE;
    text = "2.0s";
    val6->s = malloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val6->s,text);
    head = cons(val6,head);
    correctLength++;
    assert(length(head) == correctLength);

  }

  Value *val7 = malloc(sizeof(Value));
  val7->type = DOUBLE_TYPE;
  val7->d = 1.0;
  head = cons(val7,head);
  correctLength++;
  assert(length(head) == correctLength);

    
  display(head);
  testForward(head, correctLength, exemplary);

  Value *rev = reverse(head);
  display(rev);

  testBackward(rev, correctLength, exemplary);

  cleanup(head);
  cleanup(rev);

  head = NULL;
  rev = NULL;
}
