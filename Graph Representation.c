#include <stdio.h>
#include <stdlib.h>

typedef struct list_node_ver
{
   struct list_node_ver *prev, *next;
   int id;
   struct list_node_adj *adj;
}TNode_ver;

typedef struct list_node_adj
{
   struct list_node_adj *next;
   TNode_ver *ptr;
}TNode_adj;

typedef struct list
{
   struct list_node_ver *first, *last;
}TList;


TNode_ver *node_create_ver(int item_data);
TNode_adj *node_create_adj(TNode_ver *ptr_j);
void list_push(TList *list, int item_data);
TList *list_create(void);
void create_adjacent(TNode_ver *ptr_i, TNode_ver *prt_j);
void push_back_adj(TNode_ver *ptr_i, TNode_ver *ptr_j);
void print_graph(TList *list);


int main()
{
    int n, m, i;
    TList *list = list_create();
    TNode_ver *ptr_i = NULL;
    TNode_ver *ptr_j = NULL;
    //printf("Valor de N: ");
    scanf("%d", &n);
    for(i=1; i<=n; i++)
    {
        list_push(list, i);
    }
    for(ptr_i = list->first; ptr_i!=NULL; ptr_i = ptr_i->next)
    {
        for(ptr_j = list->first; ptr_j!=NULL; ptr_j = ptr_j->next)
        {
            scanf("%d", &m);
            if(m == 1)
            {
                push_back_adj(ptr_i, ptr_j);
            }
        }
    }
    print_graph(list);
    free(list);
}

TList *list_create(void)
{
   struct list *n = (struct list*)malloc(sizeof(struct list));
   if (n == NULL)
   {
      exit(EXIT_FAILURE);
   }
   n -> first = n -> last = NULL;
   return n;
}

TNode_ver *node_create_ver(int item_data)
{
   TNode_ver *newe = (TNode_ver*)malloc(sizeof(TNode_ver));
   newe -> id = item_data;
   newe -> next = NULL;
   newe -> prev = NULL;
   newe->adj = NULL;
   return newe;
}

TNode_adj *node_create_adj(TNode_ver *ptr_j)
{
    TNode_adj *newe = (TNode_adj*)malloc(sizeof(TNode_adj));
    newe->next = NULL;
    newe->ptr = ptr_j;
    return newe;
}


void list_push(TList *list, int item_data)
{
   TNode_ver *newe = node_create_ver(item_data);
   if (list -> first == NULL)
   {
      list -> first = newe;
      list -> last = newe;
      newe -> next = newe -> prev = NULL;
      return;
   }

   TNode_ver *aux = list -> last;
   aux -> next = newe;
   newe -> prev = list -> last;
   newe -> next = NULL;
   list -> last = newe;
}


void push_back_adj(TNode_ver *ptr_i, TNode_ver *ptr_j)
{
    TNode_adj *newe = node_create_adj(ptr_j);
    TNode_adj *aux = ptr_i->adj;
    if(ptr_i->adj == NULL)
    {
        ptr_i->adj = newe;
    }
    else
    {
        if(aux->next == NULL)
        {
            aux->next = newe;
        }
        else
        {
            while (aux->next != NULL)
            {
                aux = aux->next;
            }
            aux->next = newe;
        }
    }
}

void print_graph(TList *list)
{
    TNode_ver *aux = list->first;
    while(aux!=NULL)
    {
        printf("%d ", aux->id);
        TNode_adj *aux2 = aux->adj;
        while(aux2 != NULL)
        {
             printf("%d ", aux2->ptr->id);
             aux2 = aux2->next;
        }
        aux = aux->next;
        printf("\n");
    }
    return;
}