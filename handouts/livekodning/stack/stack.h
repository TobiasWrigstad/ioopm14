typedef struct stack *Stack;

// Make a new stack
Stack mkStack();

// Remove a stack from memory
void freeStack();

// Push elem to s
void push(Stack s, void *elem);

// Pop an element from s. Returns NULL if s is empty
void *pop(Stack s);

// Return the top element of s. Returns NULL if s is empty
void *top(Stack s);

// Return the number of elements in the stack
int size(Stack s);

// An iterator for the stack
typedef struct iterator *Iterator;

// Initialize an iterator
Iterator init(Stack s);

// 1 if i has more elements, 0 otherwise 
int hasNext(Iterator i);

// Return current element and move iterator forward
void *getNext(Iterator i);

// Remove an iterator from memory
void freeIterator(Iterator i);