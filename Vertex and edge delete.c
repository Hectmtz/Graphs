#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node_ver
{
   struct list_node_ver *prev, *next;
   int id;
   int grade_in;
   int grade_out;
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
void erase_vertex(int ver, TList *list);
void pop_front(TNode_ver *ptr_i);
void erase_double(TList *list, int data);
void erase(TNode_adj **cab, int info);

int main()
{
    int n, funct, ver, dest, m, i;
    char cad[25];
    TList *list = list_create();
    TNode_ver *ptr_i = NULL;
    TNode_ver *ptr_j = NULL;
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
                ptr_i->grade_out++;
                ptr_j->grade_in++;
            }
        }
    }
    scanf("%d", &funct);
    for(i=0; i<funct; i++)
    {
        scanf("%s", cad);
        if(strcmp(cad,"erase_vertex") == 0)
        {
            scanf("%d", &ver);
            erase_vertex(ver, list);
        }
        if(strcmp(cad,"erase_edge") == 0)
        {
            scanf("%d", &ver);
            scanf("%d", &dest);
            for(ptr_i = list->first; ptr_i!=NULL; ptr_i = ptr_i->next)
            {
                if(ptr_i->id == ver)
                {
                    ptr_i->grade_out--;
                    erase(&ptr_i->adj, dest);
                }

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
   newe->grade_in=0;
   newe->grade_out=0;
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
        printf("%d %d %d ", aux->id, aux->grade_in, aux->grade_out);
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

//elimina un vertice y las adyacencias de otros vertices con el
void erase_vertex(int ver, TList *list)
{
    TNode_ver *ptr_i = NULL;
    TNode_ver *ptr_j = NULL;
    for(ptr_i = list->first; ptr_i!=NULL; ptr_i = ptr_i->next)
    {
        if (ptr_i->id == ver)
        {
            while(ptr_i->adj!=NULL)
            {
                ptr_i->adj->ptr->grade_in--;
                pop_front(ptr_i);
            }
            for(ptr_j = list->first; ptr_j!=NULL; ptr_j = ptr_j->next)
            {
                TNode_adj *aux = ptr_j->adj;
                while(aux != NULL)
                {
                    if(aux->ptr->id == ver)
                    {
                        ptr_j->grade_out--;
                    }
                    aux = aux->next;
                }
                erase(&ptr_j->adj, ver);
            }
            erase_double(list, ptr_i->id);
            return;
        }
    }
    return;
}

//elimina el primer nodo de una lista simple
void pop_front(TNode_ver *ptr_i)
{
    TNode_adj *aux = ptr_i->adj;
    if(aux != NULL)
    {
        ptr_i->adj = aux->next;
        free(aux);
    }
}

//elimina un nodo en especifico de la lista principal
void erase_double(TList *list, int data)
{
    TNode_ver *aux = list->first;
    while(aux != NULL)
    {
        if (aux->id == data)
        {
            // Item in first position
            if (aux->prev != NULL)
            {
                aux->prev->next = aux->next;
            }
            else
            {
                list->first = aux->next;
            }
            //Item in last position
            if (aux->next != NULL)
            {
                aux->next->prev = aux->prev;
            }
            else
            {
                list->last = aux->prev;
            }
            free (aux);
            return;
        }
        aux = aux->next;
    }
    return;
}

//elimina un nodo en especifico de una lista simple
void erase(TNode_adj **cab, int info)
{
    TNode_adj *aux = *cab,*auxd=NULL;
    if (aux == NULL)
    {
        return;
    }
    if (aux->ptr->id == info)
    {
        aux->ptr->grade_in--;
        auxd = aux;
        *cab = aux->next;
        free(auxd);
        return;
    }
    while (aux->next != NULL)
    {
        if(aux->next->ptr->id == info)
        {
            aux->next->ptr->grade_in--;
            auxd = aux->next;
            aux->next = aux->next->next;
            free(auxd);
            return;
        }
        if(aux->next->next == NULL && aux->next->ptr->id == info)
        {
            free(aux->next);
            aux->next=NULL;
        }
        aux = aux->next;
    }
    return;
}