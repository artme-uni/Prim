#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int begin;
    int end;
    int weight;
} edge;

int compare(const void *a, const void *b)
{
    return ((edge *) a)->weight - ((edge *) b)->weight;
}

int prim(edge *graph, int cnt_edge, int cnt_vert, edge *list)
{
    int *colors = calloc(sizeof(int), cnt_vert);
    int list_cnt = 0;

    colors[0] = 1;

    while (list_cnt != cnt_vert - 1)
    {
        int found = 0;

        for (int i = 0; i < cnt_edge; i++)
        {
            int color_begin = colors[graph[i].begin];
            int color_end = colors[graph[i].end];

            if ((color_begin != 0) && (color_end == 0))
            {
                colors[graph[i].end] = 1;
                list[list_cnt++] = graph[i];
                found = 1;
                break;
            }
            else if ((color_begin == 0) && (color_end != 0))
            {
                colors[graph[i].begin] = 1;
                list[list_cnt++] = graph[i];
                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("no spanning tree %d\n", list_cnt);
            free(colors);

            return 1;
        }
    }

    free(colors);
    return 0;
}

int main()
{
    int cnt_vert;
    int cnt_edge;

    scanf("%d\n", &cnt_vert);

    if (cnt_vert < 0 || cnt_vert > 5000)
    {
        printf("bad number of vertices\n");
        return 1;
    }
    else if (cnt_vert == 0)
    {
        printf("no spanning tree\n");
        return 1;
    }
    else if (cnt_vert == 1)
    {
        return 1;
    }

    if (scanf("%d\n", &cnt_edge) != 1)
    {
        printf("bad number of lines\n");
        return 1;
    }


    if (cnt_edge < 0 || cnt_edge > ((cnt_vert) * (cnt_vert + 1)) / 2)
    {
        printf("bad number of edges\n");
        return 1;
    }

    edge *graph = malloc(sizeof(edge) * cnt_edge);
    for (int i = 0; i < cnt_edge; i++)
    {
        if ((scanf("%d %d %d", &graph[i].begin, &graph[i].end, &graph[i].weight) != 3))
        {
            printf("bad number of lines\n");
            return 1;
        }

        if (graph[i].begin < 1 || graph[i].begin > cnt_vert ||
            graph[i].end < 1 || graph[i].end > cnt_vert)
        {
            printf("bad vertex\n");
            free(graph);
            return 1;
        }

        graph[i].begin -= 1;
        graph[i].end -= 1;

        if (graph[i].weight < 0)
        {
            printf("bad lengthn\n");
            free(graph);
            return 1;
        }
    }

    edge *list = malloc(sizeof(edge) * (cnt_vert - 1));

    if (prim(graph, cnt_edge, cnt_vert, list) == 0)
    {
        for (int i = 0; i < cnt_vert - 1; i++)
        {
            printf("%d %d %d\n", graph[i].begin + 1, graph[i].end + 1, graph[i].weight);
        }
    }

    return 0;
}