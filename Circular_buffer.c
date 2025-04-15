#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // Define buffer capacity

typedef struct {
    int buffer[BUFFER_SIZE];  
    int head;  // Read pointer
    int tail;  // Write pointer
    int size;  // Number of elements in the buffer
} CircularBuffer;

// Initialize the circular buffer
void initBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->size = 0;
}

// Check if buffer is full
int isFull(CircularBuffer *cb) {
    return cb->size == BUFFER_SIZE;
}

// Check if buffer is empty
int isEmpty(CircularBuffer *cb) {
    return cb->size == 0;
}

// Add an element to the buffer (enqueue)
void enqueue(CircularBuffer *cb, int value) {
    if (isFull(cb)) {
        printf("Buffer is full! Cannot add %d\n", value);
        return;
    }
    cb->buffer[cb->tail] = value;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE; // Circular increment
    cb->size++;
}

// Remove an element from the buffer (dequeue)
int dequeue(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty! Cannot dequeue.\n");
        return -1;  // Return an invalid value
    }
    int value = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE; // Circular increment
    cb->size--;
    return value;
}

// Print the buffer contents
void printBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty.\n");
        return;
    }
    printf("Buffer contents: ");
    int index = cb->head;
    for (int i = 0; i < cb->size; i++) {
        printf("%d ", cb->buffer[index]);
        index = (index + 1) % BUFFER_SIZE;
    }
    printf("\n");
}

// Main function to test the circular buffer
int main() {
    CircularBuffer cb;
    initBuffer(&cb);

    enqueue(&cb, 10);
    enqueue(&cb, 20);
    enqueue(&cb, 30);
    enqueue(&cb, 40);
    enqueue(&cb, 50);

    printBuffer(&cb);

    printf("Dequeued: %d\n", dequeue(&cb));
    printf("Dequeued: %d\n", dequeue(&cb));

    printBuffer(&cb);

    enqueue(&cb, 60);
    enqueue(&cb, 70);
    enqueue(&cb, 80);
    
    printBuffer(&cb);

    return 0;
}
 
// In the above code, we have defined a circular buffer structure with an array of integers, head, tail, and size variables.
// The  initBuffer()  function initializes the buffer.
// The  isFull()  and  isEmpty()  functions check if the buffer is full or empty. 
// The  enqueue()  function adds an element to the buffer, and the  dequeue()  function removes an element from the buffer.
// The  printBuffer()  function prints the buffer contents. 
// In the  main()  function, we test the circular buffer by adding and removing elements from it. 
// Output: Buffer contents: 10 20 30 40 50