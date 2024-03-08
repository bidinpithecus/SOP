#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int *array;
    int front, rear;
    int capacity;
} CircularBuffer;

CircularBuffer* createCircularBuffer(int);
int isCircularBufferFull(CircularBuffer*);
int isCircularBufferEmpty(CircularBuffer*);
void enqueueCircularBuffer(CircularBuffer*, int);
int dequeueCircularBuffer(CircularBuffer*);
void printCircularBuffer(CircularBuffer*);
void destroyCircularBuffer(CircularBuffer* buffer);

CircularBuffer* createCircularBuffer(int capacity) {
  CircularBuffer *buffer = (CircularBuffer*)malloc(sizeof(CircularBuffer));
  buffer->capacity = capacity;
  buffer->array = (int*)malloc(buffer->capacity * sizeof(int));
  buffer->front = buffer->rear = -1;
  return buffer;
}

int isCircularBufferFull(CircularBuffer *buffer) {
  return ((buffer->rear + 1) % buffer->capacity == buffer->front);
}

int isCircularBufferEmpty(CircularBuffer *buffer) {
  return (buffer->front == -1);
}

void enqueueCircularBuffer(CircularBuffer *buffer, int item) {
  if (isCircularBufferEmpty(buffer)) { 
    buffer->front = buffer->rear = 0;
  } else if (isCircularBufferFull(buffer)) {
    buffer->rear = (buffer->rear + 1) % buffer->capacity;
    buffer->front = (buffer->front + 1) % buffer->capacity;
  } else {
    buffer->rear = (buffer->rear + 1) % buffer->capacity;
  }
  buffer->array[buffer->rear] = item;
}

int dequeueCircularBuffer(CircularBuffer *buffer) {
  int item;
  if (isCircularBufferEmpty(buffer)) {
    printf("Fila circular vazia\n");
    return -1;
  }
  item = buffer->array[buffer->front];
  if (buffer->front == buffer->rear) {
    buffer->front = buffer->rear = -1;
  } else {
    buffer->front = (buffer->front + 1) % buffer->capacity;
  }
  return item;
}

void printCircularBuffer(CircularBuffer *buffer) {
  int i;
  if (isCircularBufferEmpty(buffer)) {
    printf("Fila: ");
    return;
  }
  printf("Fila: ");
  for (i = buffer->front; i != buffer->rear; i = (i + 1) % buffer->capacity) {
    printf("%d ", buffer->array[i]);
  }
  printf("%d\n", buffer->array[i]);
}

void destroyCircularBuffer(CircularBuffer* buffer) {
  free(buffer->array);
  free(buffer);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <queue_size>\n", argv[0]);
    return 1;
  }

  int queue_size = atoi(argv[1]);
  CircularBuffer *buffer = createCircularBuffer(queue_size);

  int num;
  while (scanf("%d", &num) == 1) {
    if (num == -1) {
      break;
    } else if (num == -2) {
      printCircularBuffer(buffer);
    } else {
      enqueueCircularBuffer(buffer, num);
    }
  }

  destroyCircularBuffer(buffer);

  return 0;
}
