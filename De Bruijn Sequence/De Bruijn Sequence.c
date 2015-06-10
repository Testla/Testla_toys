/*
 * each node's length is sub_length - 1
 * an edge to the next node means concatenate that bit to the number and
 * get the lower (sub_length - 1) bits
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char alphabet[] = "0123456789ABCDEF";
int base, sub_length;

int power(int base, int times) {
    int result = 1;
    while (times > 0) {
        result *= base;
        --times;
    }
    return result;
}

int next_node(int current_node, int edge) {
    return (current_node * base % power(base, sub_length - 1) + edge);
}

/*
 * Uses BFS to judge.
 * If the current_node is not alone and we cannot go back to the current_node
 * from the destiny , it's a bridge.
 */
int is_bridge(int **graph, int current_node, int attempting_edge) {
    int number_of_node, queue_front, queue_rear, result, expand_edge;
    int *visited, *queue;
    /*self-loop*/
    if (current_node == next_node(current_node, attempting_edge))
        return 0;
    /*check if the current_node is alone*/
    for (expand_edge = 0; expand_edge < base; ++expand_edge)
        if (expand_edge != attempting_edge && !graph[current_node][expand_edge])
            break;
    if (expand_edge == base)
        return 0;
    number_of_node = power(base, sub_length - 1);
    visited = (int *)malloc(number_of_node * sizeof(int));
    queue = (int *)malloc(number_of_node * sizeof(int));
    memset(visited, 0, number_of_node * sizeof(int));
    queue[0] = next_node(current_node, attempting_edge);
    visited[queue[0]] = 1;
    queue_front = 0;
    queue_rear = 1;
    result = 1;
    /*expand from the destiny, if current_node is reachable, it's not bridge*/
    while (queue_front != queue_rear) {
        for (expand_edge = 0; expand_edge < base; ++expand_edge)
            if (!graph[queue[queue_front]][expand_edge]
            && !visited[next_node(queue[queue_front], expand_edge)]) {
                if (next_node(queue[queue_front], expand_edge) == current_node) {
                    result = 0;
                    break;
                } else {
                    queue[queue_rear++] = next_node(queue[queue_front], expand_edge);
                    visited[next_node(queue[queue_front], expand_edge)] = 1;
                }
            }
        ++queue_front;
    }
    free(visited);
    free(queue);
    return result;
}

int main(void) {
    int number_of_edge, number_of_node, current_node, edge_count, attempting_edge;
    int **graph;
    puts("Input the size of alphabet and length of subsequence: ");
    scanf("%d%d", &base, &sub_length);
    number_of_edge = power(base, sub_length);
    number_of_node = power(base, sub_length - 1);
    graph = (int **)malloc(number_of_node * sizeof(int *));

    /*initialize*/
    for (current_node = 0; current_node < number_of_node; ++current_node) {
        graph[current_node] = (int *)malloc(base * sizeof(int));
        memset(graph[current_node], 0, base * sizeof(int));
    }

    /*uses FLEURY's algorithm to get a Euler path*/
    /*set the start to ma to have the least lexicographic order sequence*/
    current_node = number_of_node - 1;
    edge_count = 0;
    for (edge_count = 0; edge_count < number_of_edge; ++edge_count)
        for (attempting_edge = 0; attempting_edge < base; ++attempting_edge)
            if (!graph[current_node][attempting_edge]
            && !is_bridge(graph, current_node, attempting_edge)) {
                putchar(alphabet[attempting_edge]);
                graph[current_node][attempting_edge] = 1;
                current_node = next_node(current_node, attempting_edge);
                break;
            }
    putchar('\n');

    /*cleaning job*/
    for (current_node = 0; current_node < number_of_node; ++current_node)
        free(graph[current_node]);
    free(graph);
	return 0;
}

