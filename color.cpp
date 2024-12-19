//
// Created by Janam Zaveri on 09/02/2023.
//

#include <iostream>
#include <stack>
#include <map>
#include "color.h"
using namespace std;

int compute_degree(int **Graph, int v, int size)
{

    int deg = 0;

    for (int i = 0; i < size; i++)
    {

        if (Graph[v][i] == 1)
        {

            deg += 1;
        }
    }

    return deg;
}

void add_node(int **old_graph, int **Graph, int size, int v)

{

    for (int i = 0; i < size; i++)
    {

        if (old_graph[v][i] == 1)
        {

            Graph[i][v] = 1;
        }
    }
}

void remove_node(int **Graph, int v, int size)
{

    for (int i = 0; i < size; i++)
    {

        if (Graph[v][i] == 1)
        {

            Graph[v][i] = 0;

            Graph[i][v] = 0;
        }
    }
}

// Greedily assign color to the node added

void assign_color(int **Graph, int v, map<int, int> &color, int size, int k)
{

    int *available_colors = new int[k];

    for (int i = 0; i < k; i++)
    {

        available_colors[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {

        if (Graph[v][i] == 1 && i != v)
        {

            available_colors[color[i]] = 1;
        }
    }

    for (int i = 0; i < k; i++)
    {

        if (available_colors[i] == 0)

        {

            color[v] = i;

            return;
        }
    }
    // Did not find an available color :(

    color[v] = -1;
}

/*
The below procedure removes nodes recursively.
Arguements/Input:
Graph- Expressed as a bit matrix. If graph[i][j]==1 and graph[j][i]==1 there is
an edge between nodes i and j

size- Number of nodes

wrk_lst-Used to keep track of the ordering of the removal of vertices

k-Number of registers

*/
void simplify(int **Graph, int size, stack<int> &wrk_lst, int *stacked, int k)
{

    int flag = 0;

    int spill_node = -1;

    for (int i = 0; i < size; i++)
    {

        int deg = compute_degree(Graph, i, size);

        if (deg < k && stacked[i] == 0)
        {

            flag = 1;

            remove_node(Graph, i, size);

            wrk_lst.push(i);

            stacked[i] = 1;

            break;
        }
        else if (deg >= k)
        {

            spill_node = i;

            flag = 2;
        }
    }

    // All nodes in graph have significant degree

    if (flag == 2)
    { // Add heurisic to compute spill costs of each node.

        remove_node(Graph, spill_node, size);

        stacked[spill_node] = 1;

        wrk_lst.push(spill_node);
    }

    // Graph is empty. Terminate the recursion.

    else if (flag == 0)
    {

        cout << "Recursion terminated" << endl;

        return;
    }

    simplify(Graph, size, wrk_lst, stacked, k);
}

void select(int **old_graph, int size, int **graph, map<int, int> &color, stack<int> &foo, int k)
{

    if (foo.empty())
    {

        return;
    }

    int v = foo.top();

    foo.pop();

    add_node(old_graph, graph, size, v);

    assign_color(graph, v, color, size, k);

    select(old_graph, size, graph, color, foo, k);
}

// Testing for correctness

// Builds the graph

int **create_graph(int edges[][2], int size, int e)
{

    int **Graph = new int *[size];

    for (int i = 0; i < size; i++)
    {

        Graph[i] = new int[size];

        for (int j = 0; j < size; j++)
        {

            Graph[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++)
    {

        int u = edges[i][0];

        int v = edges[i][1];

        Graph[u][v] = 1;

        Graph[v][u] = 1;
    }

    return Graph;
}

/*void do_test(int edges[][2],int num_vertices,int num_edges,int num_colors){


    int **graph_one = create_graph(edge_one, num_vertices, num_edges);

    int **graph_copy = create_graph(edge_one,num_vertices, num_edges);

    for (int i = 0; i < num_vertices; i++)
    {

        stacked[i] = 0;
    }

    stack<int> s;


    int **graph_one = create_graph(edges, num_vertices, num_edges);

    int **graph_copy = create_graph(edges, num_vertices, num_edges);

    simplify(graph_one,s, stacked, num_colors);

    map<int, int> color;

    for (int i = 0; i < 5; i++)
    {

        color[i] = 0;
    }


    select(graph_copy, 5, graph_one, color, s, 2);


     for (int i = 0; i < num_vertices; i++)

     {

        assert(color[edges[i][0]]!=color[edges[i][1]]);


     }

    for (int i = 0; i <num_vertices; i++)


    {

        cout << i << "-" << color[i] << endl;
    }












}*/

map<int, int> color(int **ig, int num_nodes, int k)
{

    int *stacked = new int[num_nodes];

    stack<int> s;

    for (int i = 0; i < num_nodes; i++)
    {

        stacked[i] = 0;
    }

    int **ig_copy = new int *[num_nodes];

    for (int i = 0; i < num_nodes; i++)
    {

        ig_copy[i] = new int[num_nodes];

        for (int j = 0; j < num_nodes; j++)
        {

            ig_copy[i][j] = ig[i][j];
        }
    }

    simplify(ig, num_nodes, s, stacked, k);

    map<int, int> color;

    for (int i = 0; i < num_nodes; i++)
    {

        color[i] = 0;
    }

    select(ig_copy, num_nodes, ig, color, s, k);

    return color;
}

/*int main()

{

    cout << "Initialising test cases" << endl;

    // TEST-1

    int *stacked = new int[5];

    stack<int> s;

    for (int i = 0; i < 5; i++)
    {

        stacked[i] = 0;
    }

    // test case -1

    int edge_one[][2] = {{0, 1}, {1, 3}, {1, 4}, {2, 4}, {3, 4}, {2, 3}, {0, 2}};

    int edge_two[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};

    int edge_three[][2] = {{0, 1}, {1, 2}, {2, 0}};

    int **graph_one = create_graph(edge_three, 3, 3);

    map<int, int> coloring = color(graph_one,3,3);

    for (int i = 0; i < 3; i++)
    {

        cout << i << "-" << coloring[i] << endl;
    }

      for (int i = 0; i < 3; i++)

    {

        assert(coloring[edge_three[i][0]] != coloring[edge_three[i][1]]);
    }

    int **graph_copy = create_graph(edge_one, 5, 7);

    simplify(graph_one, 5, s, stacked, 2);

    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            assert(graph_one[i][j] == 0);
        }
    }

    map<int, int> color;

    for (int i = 0; i < 5; i++)
    {

        color[i] = 0;
    }

    // test algorithm for select phase

    select(graph_copy, 5, graph_one, color, s, 2);

  

    for (int i = 0; i < 5; i++)
    {

        cout << i << "-" << color[i] << endl;
    }
}*/
