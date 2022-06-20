#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COUNT 5

typedef struct point_t{
    double x;
    double y;
} point_t;

typedef struct rectangle_t{
    point_t A;
    point_t B;
} rectangle_t;

typedef struct node{
    rectangle_t Rect;
    struct node* next;
} node_t;

double rand_double(double min, double max);
double area(rectangle_t rect);
double areaRects(node_t* list);
void filterRects(node_t** list, double min, double max);

node_t* create_node();
void push_end(node_t* list, node_t* node);
void print_list(node_t* list);

int main(){
    srand(time(NULL));

    node_t* head = create_node();

    for(int i = 1; i < COUNT; i++){
        node_t* new_node = create_node();
        push_end(head, new_node);
    }

    print_list(head);
    printf("\n");
    filterRects(&head, 5, 6);
    printf("\n");
    print_list(head);

    return 0;
}

double rand_double(double min, double max){
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double area(rectangle_t rect){
    return abs(rect.A.x - rect.B.x) * abs(rect.A.y - rect.B.y);
}

double areaRects(node_t* list){
    node_t* current = list;
    double sum_area = 0;
    while(current){
        sum_area += area(current->Rect);
        current = current->next;
    }
    return sum_area;
}

void filterRects(node_t** list, double min, double max){
    if(*list == NULL){
        return;
    }

    node_t* current = *list;
    node_t* prev = current;

    while (current){
        double area_rect = area(current->Rect);
        if(area_rect >= min && area_rect <= max){
            node_t* to_delete = current;

            prev->next = current->next;
            current = prev;

            free(to_delete);
        }
        prev = current;
        current = current->next;
    }
}

node_t* create_node(){
    node_t* head = malloc(sizeof(node_t));

    head->Rect.A.x = rand_double(-10.0, 10.0);
    head->Rect.B.x = rand_double(-10.0, 10.0);

    head->Rect.A.y = rand_double(-10.0, 10.0);
    head->Rect.B.y = rand_double(-10.0, 10.0);

    return head;
}

void push_end(node_t* list, node_t* node){
    node_t* current = list;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = node;
}

void print_list(node_t* list){
    node_t* current = list;

    while (current){
        printf("Points:\t%lf\t%lf\t%lf\t%lf\n", current->Rect.A.x, current->Rect.A.y,
        current->Rect.B.x, current->Rect.B.y);
        printf("Area:\t%lf\n", area(current->Rect));

        current = current->next;
    }
}