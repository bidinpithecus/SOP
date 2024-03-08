#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX_SIZE 50

typedef struct {
  char* name;
  int num;
} Priority;

typedef struct QueueNode {
  Priority priority;
  struct QueueNode* p_next;
} QueueNode;

typedef struct {
  int size;
  QueueNode* p_rear;
  QueueNode* p_front;
} Queue;

Priority* createPriority(char* name, int num) {
  Priority* priority = (Priority*) malloc(sizeof(Priority));
  priority->name = (char*) calloc(STRING_MAX_SIZE, sizeof(char));

  strcpy(priority->name, name);
  priority->num = num;

  return priority;
}

void destroyPriority(Priority* priority) {
  free(priority->name);
  priority->num = 0;

  free(priority);
}

QueueNode* createQueueNode(Priority priority) {
  QueueNode* queueNode = (QueueNode*) malloc(sizeof(QueueNode));

  queueNode->priority.name = priority.name;
  queueNode->priority.num = priority.num;
  queueNode->p_next = NULL;

  return queueNode;
}

void destroyQueueNode(QueueNode* queueNode) {
  queueNode->p_next = NULL;
  free(queueNode->priority.name);
  queueNode->priority.num = 0;

  free(queueNode);
}

Queue* createQueue() {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue->size = 0;
  queue->p_rear = queue->p_front = NULL;

  return queue;
}

void destroyQueue(Queue* queue) {
  while (queue->p_front != NULL) {
    QueueNode* temp = queue->p_front;
    queue->p_front = temp->p_next;
    destroyQueueNode(temp);
  }

  free(queue);
}

void enqueue(Queue* queue, Priority priority) {
  QueueNode* qNode = createQueueNode(priority);

  if (queue->p_rear == NULL) {
    queue->p_rear = qNode;
    queue->p_front = qNode;
  } else {
    queue->p_rear->p_next = qNode;
    queue->p_rear = qNode;
  }

  queue->size++;
}

Priority dequeue(Queue* queue) {
  if (queue->p_front == NULL) {
    Priority empty_priority = {NULL, 0};
    return empty_priority;
  }

  QueueNode* temp = queue->p_front;
  Priority priority = temp->priority;

  queue->p_front = temp->p_next;
  if (queue->p_front == NULL) {
    queue->p_rear = NULL;
  }
  destroyQueueNode(temp);

  queue->size--;

  return priority;
}

void printQueue(Queue* queue) {
  if (queue->size == 0) {
    printf("Fila vazia\n");
    return;
  }

  QueueNode* current = queue->p_front;
  while (current != NULL) {
    printf("%s ", current->priority.name);
    current = current->p_next;
  }

  printf("\n");
}

int main(void) {
  Queue** queues = NULL;
  int num_of_priorities = 0;
  char string[STRING_MAX_SIZE];
  int num;

  for (;;) {
    int ret = scanf("%s", string);

    if (ret == EOF || strcmp(string, "FIM") == 0) {
      break;
    }

    ret = scanf("%d", &num);

    if (ret != 1) {
      printf("Erro na entrada padrão\n");
      break;
    }

    if (strcmp(string, "IGUAL") == 0) {
      if (num >= 0 && num < num_of_priorities && queues[num] != NULL) {
        printf("Prioridade %d: ", num);
        printQueue(queues[num]);
      }
    } else if (strcmp(string, "MENIG") == 0) {
      for (int i = 0; i < num_of_priorities; i++) {
        if (queues[i] != NULL && i <= num) {
          printf("Prioridade %d: ", i);
          printQueue(queues[i]);
        }
      }
    } else {
      if (num >= num_of_priorities) {
        queues = (Queue**) realloc(queues, (num + 1) * sizeof(Queue*));
        for (int i = num_of_priorities; i <= num; i++) {
          queues[i] = NULL;
        }
        num_of_priorities = num + 1;
      }
      if (queues[num] == NULL) {
        queues[num] = createQueue();
      }
      Priority priority = *createPriority(string, num);
      enqueue(queues[num], priority);
    }
  }

  for (int i = 0; i < num_of_priorities; i++) {
    if (queues[i] != NULL) {
      destroyQueue(queues[i]);
    }
  }

  free(queues);

  return 0;
}
