#include <stdio.h>
#include <stdlib.h>

typedef struct Customer{
  char name[16];
  int numSmoothies;
  int lineNum;
  int time;
} Customer;

typedef struct node {
  Customer *customer;
  struct node *next;
} node;

typedef struct queue {
  node *front;
  node *back;
} queue;

void init(queue *q){
  q->front = NULL;
  q->back = NULL;
};

//Add Customer to Queue
void enqueue(queue *q, Customer *c){
  node *newNode = malloc(sizeof(node));
  newNode->customer = c;
  newNode->next = NULL;
  
  //If Queue is Empty
  if(q->back != NULL){
    q->back->next = newNode;
    q->back = newNode;
  }
  else{
    q->front = newNode;
    q->back = newNode;
  }
}

//Remove Customer from Queue
Customer* dequeue(queue *q){
  if(q->front == NULL){
    return NULL;
  }
  
  //Store the front customer and frees the temp node
  node *temp = q->front;
  Customer *c = temp->customer;
  q->front = q->front->next;
  free(temp);
  if(q->front == NULL){
    q->back = NULL;
  }
  return c;
}

//Peek at Queue
Customer *peek(queue *q){
  if(q->front != NULL){
    return q->front->customer;
  }
  else{
    return NULL;
  }
}

//Empty Queue
int empty(queue *q){
  if(q->front == NULL){
    return 1;
  }
  else{
    return 0;
  }
}

//Allocates a new customer struct
Customer *createCustomer(char name[16], int numSmoothies, int lineNum, int time){
  Customer *c = malloc(sizeof(Customer));
  c->numSmoothies = numSmoothies;
  c->lineNum = lineNum;
  c->time = time;
  strcpy(c->name, name);
  return c;
}

//Customer transactions with multiple lines
void testCases(int numCustomers){
  int numCases, lineNum, cusTime;
  queue lines[12];
  for (int i = 0; i < 12; i++) {
      init(&lines[i]);
  }
  
  //Loop to read and enqueue customer data
  for (int i = 0; i < numCustomers; i++) {
      int cusTime, lineNum, numSmoothies;
      char cusName[16];
      scanf("%d %d %s %d", &cusTime, &lineNum, cusName, &numSmoothies);
      Customer *c = createCustomer(cusName, numSmoothies, lineNum, cusTime);
      enqueue(&lines[lineNum - 1], c);
  }

  int currentTime = 0;

  while (1) {
  Customer *selectedCustomer = NULL;
          int selectedLine = -1;

          // Find the customer with the earliest time and the least number of smoothies
          for (int i = 0; i < 12; i++) {
              if (!empty(&lines[i])) {
                  Customer *c = peek(&lines[i]);
                
                  // Check if the customer has already been selected
                  if (selectedCustomer == NULL || 
                      (c->time <= currentTime && c->numSmoothies < selectedCustomer->numSmoothies) ||
                      (c->time <= currentTime && c->numSmoothies == selectedCustomer->numSmoothies && i < selectedLine) ||
                      (selectedCustomer->time > currentTime && c->time < selectedCustomer->time)) {
                      selectedCustomer = c;
                      selectedLine = i;
                  }
              }
          }

          if (selectedLine == -1) {
              break;
          }
    
          // Dequeue the selected customer
          Customer *c = dequeue(&lines[selectedLine]);
          if (c->time > currentTime) {
              currentTime = c->time;
          }

          // Calculate the checkout time and update the current time
          int checkoutTime = 30 + c->numSmoothies * 5;
          currentTime += checkoutTime;

          printf("At time %d, %s left the counter from line %d.\n", currentTime, c->name, c->lineNum);

          free(c);
      }
  }


//Main
int main(void) {
  
  int numCases;
  scanf("%d", &numCases);
  for(int i = 0; i < numCases; i++){
    int numCustomers;
    scanf("%d", &numCustomers);
    testCases(numCustomers);
  }
  
  return 0;
}