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
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
using namespace std;

int* alloc_array (int graph_size){
    int *a;
    a = (int*)malloc(graph_size*sizeof(int));
    return a;
}

int* dijkstra (t_graph** adjacent_list, int graph_size, int vertex_ini){

    int *distancia, *fechado, *aberto, *anterior, v_ini = vertex_ini, abertos, k, inf = INT_MAX/2, maior = INT_MAX, custo;
    distancia = alloc_array (graph_size);
    fechado = alloc_array (graph_size);
    aberto = alloc_array (graph_size);
    anterior = alloc_array (graph_size);

    for(int i = 0; i<graph_size; i++){
        if(i == v_ini)
            distancia[i] = 0;
        else
            distancia[i] = inf;
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
        if(abertos==1)
            k=v_ini;
        else{
            for (int i=0; i<graph_size; i++){
                if(aberto[i]==1 && distancia[i]<maior){
                    maior = distancia[i];
                    k=i;
                }
            }
        }
        if(abertos!=1){
            aberto[k] = 0;
            fechado[k] = 1;
        }

        for(t_graph* p = adjacent_list[k]; p!=NULL; p = p->prox){
            if(aberto[p->vertex]!=0){
                custo = MIN (distancia[p->vertex], (distancia[k]+p->cost));
                if(custo < distancia[p->vertex]){
                    distancia[p->vertex] = custo;
                    anterior[p->vertex] = k;
                }
            }
        }
        abertos ++;
        maior = INT_MAX;
    }

    for(int j=0;j<graph_size;j++)
        cout<<anterior[j]+1<<" ";
    getchar();

    return (distancia);
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

    if(adjacent_list[u] == NULL){
        adjacent_list[u] = c;
    }
    else{
        p = adjacent_list[u];
        while ( p -> prox != NULL ){
            p = p -> prox;
        }
        p -> prox = c;
    }
    d = new_node;
    d->vertex = u;
    d->cost = w;
    d->prox = NULL;
    if(adjacent_list[v] == NULL){
        adjacent_list[v] = d;
    }
    else{
        p = adjacent_list[v];
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
    int **distance_matrix;
    int *distance;
    FILE *f;
    int u, v, w, i;

    f = fopen ("graph.txt", "r");
    fscanf(f, "%d", &graph_size);
    printf("Graph Vertexes: %d\n", graph_size);
    adjacent_list = (t_graph**)malloc(graph_size*sizeof(t_graph*));
    for(i=0; i<graph_size;i++){
        adjacent_list[i] = NULL;
    }
    distance_matrix = (int**)malloc(graph_size*sizeof(int*));
    for(int i=0;i<graph_size;i++)
        distance_matrix[i] = (int*)malloc(graph_size*sizeof(int));
    //while (fgetc(f) != '\n');
    while (fscanf(f, "%d %d %d", &u, &v, &w) == 3){
        adjacent_list = add_to_list(adjacent_list, u, v, w);
    }

    for(int i=0; i<graph_size;i++){
        printf("Vertex %d\t", i);
        print_list(adjacent_list[i]);
        printf("\n");
    }

    for(int i=0; i<graph_size; i++){
        distance = dijkstra (adjacent_list, graph_size, i);
        for(int j=0;j<graph_size;j++)
            distance_matrix[i][j] = distance[j];
        free(distance);

    }
    printf("\n");

    for(int i=0;i<graph_size;i++){
        for(int j=0;j<graph_size;j++){
            cout<<distance_matrix[i][j]<<"\t";
        }
        cout<<"\n";
    }


}
