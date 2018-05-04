#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <limits.h>


struct type_graph{
    int vertex;
    int cost;
    struct type_graph *prox;
};
typedef struct type_graph t_graph;
#define new_node (t_graph*)malloc(sizeof(t_graph))
using namespace std;

int* alloc_array (int graph_size){
    int *a;
    a = (int*)malloc(graph_size*sizeof(int));
    return a;
}

void dijkstra (t_graph** adjacent_list, int graph_size){

    int *distancia, *fechado, *aberto, *anterior, v_ini = 0, abertos, k;
    distancia = alloc_array (graph_size);
    fechado = alloc_array (graph_size);
    aberto = alloc_array (graph_size);
    anterior = alloc_array (graph_size);

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            distancia[i] = 0;
        else
            distancia[i] = INT_MAX;
    }

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            fechado[i] = 1;
        else
            fechado[i] = 0;
    }

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            aberto[i] = 0;
        else
            aberto[i] = 1;
    }
    abertos = 1;

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            anterior[i] = 0;
        else
            anterior[i] = 0;
    }

    while (abertos != graph_size){


    }



}

void print_list(t_graph *graph){
    for(t_graph *p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

t_graph** add_to_list(t_graph **adjacent_list, int u, int v, int w){
    //printf("%d %d %d\n", u,v,w);
    t_graph *c, *d, *p;
    c = new_node;
    c->vertex = v;
    c->cost = w;
    c->prox = NULL;

    if(adjacent_list[u-1] == NULL){
        adjacent_list[u-1] = c;
    }
    else{
        p = adjacent_list[u-1];
        while ( p -> prox != NULL ){
            p = p -> prox;
        }
        p -> prox = c;
    }
    d = new_node;
    d->vertex = u;
    d->cost = w;
    d->prox = NULL;
    if(adjacent_list[v-1] == NULL){
        adjacent_list[v-1] = d;
    }
    else{
        p = adjacent_list[v-1];
        while ( p -> prox != NULL ){
            p = p -> prox;
        }
        p -> prox = d;
    }

    return (adjacent_list);
}

int main(){


    int graph_size;
    t_graph edge;
    t_graph **adjacent_list;
    FILE *f;
    int u, v, w, i;

    f = fopen ("graph.txt", "r");
    fscanf(f, "%d", &graph_size);
    printf("Graph Vertexes: %d\n", graph_size);
    adjacent_list = (t_graph**)malloc(graph_size*sizeof(t_graph*));
    for(i=0; i<graph_size;i++){
        adjacent_list[i] = NULL;
    }
    //while (fgetc(f) != '\n');
    while (fscanf(f, "%d %d %d", &u, &v, &w) == 3){
        adjacent_list = add_to_list(adjacent_list, u, v, w);
    }

    for(int i=0; i<graph_size;i++){
        printf("Vertex %d\t", i+1);
        print_list(adjacent_list[i]);
        printf("\n");
    }

    dijkstra (adjacent_list, graph_size);
}
