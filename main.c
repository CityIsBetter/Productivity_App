#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    double data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

void initializeStack(struct Stack* stack) {
    stack->top = NULL;
}

void push(struct Stack* stack, double data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

double pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    double data = stack->top->data;
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

double performOperation(double operand1, double operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            printf("Error: Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

double evaluatePostfixExpression(const char* expression) {
    struct Stack calculatorStack;
    initializeStack(&calculatorStack);

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (isdigit(expression[i])) {
            push(&calculatorStack, expression[i] - '0');
        } else if (expression[i] == ' ') {
            // Ignore spaces
            continue;
        } else {
            double operand2 = pop(&calculatorStack);
            double operand1 = pop(&calculatorStack);
            double result = performOperation(operand1, operand2, expression[i]);
            push(&calculatorStack, result);
        }
    }
    return pop(&calculatorStack);
}

void calculator(){
    char postfixExpression[100];
    printf("\n=====================================================\n");
    printf("Enter a postfix expression: ");
    scanf("%s", postfixExpression);
    double result = evaluatePostfixExpression(postfixExpression);
    printf("Result: %.2f", result);
}

struct Task {
    char description[100];
    int completed;
    struct Task* next;
};

struct Task* createTask(const char* description) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    if (newTask == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    snprintf(newTask->description, sizeof(newTask->description), "%s", description);
    newTask->completed = 0;  // 0 for false, 1 for true
    newTask->next = NULL;
    return newTask;
}

void addTask(struct Task** head, const char* description) {
    struct Task* newTask = createTask(description);
    newTask->next = *head;
    *head = newTask;
    printf("Task added: %s", description);
}

void displayTasks(const struct Task* head) {
    if (head == NULL) {
        printf("To-do list is empty.");
        return;
    }
    printf("To-Do List:");
    while (head != NULL) {
        printf("\n%s - %s", head->completed ? "[X]" : "[ ]", head->description);
        head = head->next;
    }
}

void markCompleted(struct Task* head, const char* description) {
    while (head != NULL) {
        if (strcmp(head->description, description) == 0) {
            head->completed = 1;  // Mark as completed
            printf("Task marked as completed: %s", description);
            return;
        }
        head = head->next;
    }
    printf("Task not found: %s", description);
}

void freeToList(struct Task* head) {
    while (head != NULL) {
        struct Task* temp = head;
        head = head->next;
        free(temp);
    }
}

void todo(){
     struct Task* todoList = NULL;
    int choice;
    char description[100];
    do {
        printf("\n=====================================================\n");
        printf("To-Do List Menu");
        printf("\n=====================================================\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\n=====================================================\n");
                printf("Enter task description: ");
                scanf(" %[^\n]", description);
                addTask(&todoList, description);
                break;
            case 2:
                printf("\n=====================================================\n");
                displayTasks(todoList);
                break;
            case 3:
                printf("\n=====================================================\n");
                printf("Enter task description to mark as completed: ");
                scanf(" %[^\n]", description);
                markCompleted(todoList, description);
                break;
            case 4:
                printf("\n=====================================================\n");
                printf("Quitting the to-do list app.");
                break;
            default:
                printf("\n=====================================================\n");
                printf("Invalid choice. Please try again.");
        }
    } while (choice != 4);
    freeToList(todoList);
}

struct Contact {
    char name[50];
    char phoneNumber[15];
    struct Contact* next;
    struct Contact* prev;
};

struct Contact* createContact(const char* name, const char* phoneNumber) {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        printf("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    snprintf(newContact->name, sizeof(newContact->name), "%s", name);
    snprintf(newContact->phoneNumber, sizeof(newContact->phoneNumber), "%s", phoneNumber);
    newContact->next = NULL;
    newContact->prev = NULL;
    return newContact;
}

void addContact(struct Contact** head, const char* name, const char* phoneNumber) {
    struct Contact* newContact = createContact(name, phoneNumber);
    if (*head != NULL) {
        (*head)->prev = newContact;
    }
    newContact->next = *head;
    *head = newContact;
    printf("Contact added: %s", name);
}

void displayContacts(const struct Contact* head) {
    if (head == NULL) {
        printf("Contact list is empty.");
        return;
    }
    printf("Contact List:");
    while (head != NULL) {
        printf("\nName: %-20sPhone: %s", head->name, head->phoneNumber);
        head = head->next;
    }
}

void searchContact(const struct Contact* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            printf("Contact found:");
            printf("\nName: %-20sPhone: %s", head->name, head->phoneNumber);
            return;
        }
        head = head->next;
    }
    printf("Contact not found: %s", name);
}

void freeList(struct Contact* head) {
    while (head != NULL) {
        struct Contact* temp = head;
        head = head->next;
        free(temp);
    }
}

void contactList(){
    struct Contact* contactList = NULL;
    int choice;
    char name[50];
    char phoneNumber[15];
    do {
        printf("\n=====================================================\n");
        printf("Contact List Menu");
        printf("\n=====================================================\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n=====================================================\n");
                printf("Enter contact name: ");
                scanf(" %[^\n]", name);
                printf("Enter contact phone number: ");
                scanf(" %[^\n]", phoneNumber);
                addContact(&contactList, name, phoneNumber);
                break;
            case 2:
                printf("\n=====================================================\n");
                displayContacts(contactList);
                break;
            case 3:
                printf("\n=====================================================\n");
                printf("Enter contact name to search: ");
                scanf(" %[^\n]", name);
                searchContact(contactList, name);
                break;
            case 4:
                printf("\n=====================================================\n");
                printf("Quitting the contact list app.");
                break;
            default:
                printf("\n=====================================================\n");
                printf("Invalid choice. Please try again.");
        }

    } while (choice != 4);
    freeList(contactList);
}

int main() {
    int c = 0;
    do{
        printf("\n=====================================================\n");
        printf("Productivity App");
        printf("\n=====================================================\n");
        printf("1. Calculator \n2. Todo List \n3. Contact List \n4. Exit \nEnter your choice:");
        scanf("%d", &c);
        switch(c){
            case 1:
                calculator();
                break;
            case 2:
                todo();
                break;
            case 3:
                contactList();
                break;
            case 4:
                printf("Exited!");
                break;
            default:
                printf("Enter valid input!");
        }
    } while (c != 4);
}