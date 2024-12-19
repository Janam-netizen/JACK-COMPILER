
// Contains procedures to do liveness analysis and build the interfe

#include <set>
#include <map>
#include <iostream>
#include "flowgraph.h"
#include "color.h"
#include "code_gen.h"

using namespace std;

void compute_union(set<int> &x, set<int> y)
{

    for (auto var : y)
    {

        x.insert(var);
    }
}
void printset(set<int> s)
{

    for (auto &x : s)
    {

        cout << x << " ";
    }
}

void do_livesness_analysis(int fg[30][30], int num_nodes, basic_block blocks[30], int num_blocks)
{

    int convergence = 0;

    int iter = 0;

    while (convergence < num_blocks)
    {

        cout << convergence << endl;
        cout << "--------------------------";
        convergence = 0;

        iter += 1;

        for (int i = 0; i < num_blocks; i++)
        {

            set<int> new_liveout = blocks[i].live_out;

            set<int> new_livein = blocks[i].live_in;

            // Computation of live in

            // new_livein.erase(blocks[i].def);

            // Computation of live out
            for (int j = 0; j < num_blocks; j++)
            {

                if (fg[i][j] == 1)
                {
                    compute_union(new_liveout, blocks[j].live_in);
                }
            }

            compute_union(new_livein, new_liveout);

            new_livein.erase(blocks[i].def);

            compute_union(new_livein, blocks[i].live_in);
            compute_union(new_liveout, blocks[i].live_out);
            if (new_livein.size() == blocks[i].live_in.size() && new_liveout.size() == blocks[i].live_out.size())
            {
                convergence += 1;

                cout << "same" << endl;
            }

            else
            {

                compute_union(blocks[i].live_in, new_livein);

                compute_union(blocks[i].live_out, new_liveout);
            }

            cout << "ITERATION " << iter << endl;

            blocks[i].disp_info();
        }
    }
}

// Treats each pair of temp in conflict set as edges and add its to interference graph ig.
void add_edges(int **ig, set<int> conflict)
{

    for (auto &x : conflict)
    {

        for (auto &y : conflict)

        {
            ig[x][y] = 1;
        }
    }
}

// Returns the interference graph
int **build_interference_graph()
{

    int **x;

    x = new int *[node];

    for (int i = 0; i < node; i++)
    {

        x[i] = new int[node];

        for (int j = 0; j < node; j++)
        {

            x[i][j] = 0;
        }
    }

    for (int i = 0; i < ctr; i++)
    {

        add_edges(x, blocks[i].live_in);

        add_edges(x, blocks[i].live_out);
    }

    return x;
}

void disp_graph(int **ig, int node, map<int, string> get_var)
{

    cout << " ";

    for (int i = 0; i < node; i++)
    {

        cout << get_var[i] << " ";
    }

    cout << endl;
    for (int i = 0; i < node; i++)
    {

        cout << get_var[i] << " ";

        for (int j = 0; j < node; j++)
        {
            cout << ig[i][j] << " ";
        }

        cout << endl;
    }
}

/*int compute_cost(basic_block instr,map<int,int> color){

    int score=0;

    if (color[instr.use_one]==-1){

        // Need to load variable from memory

        score+=2;



    }

    if(color[instr.use_two]==-1){

        score+=2;



    }

    if(color[instr.def]==-1)

}*/

int main()
{
//enter input file path here
    read_stmts("tac_samples_for_testing/tac_1.tac");

    encode_vars_to_vertex();

    print_assignment();

    create_basic_blocks();

    create_flow_graph();

    disp_fg();

    disp_blcoks();

    cout << node << endl;

    cout << ctr << endl;

    do_livesness_analysis(fg, node, blocks, ctr);

    cout << "------------------" << endl;

    // disp_blcoks();

    int **ig = build_interference_graph();

    disp_graph(ig, node, get_var);

    map<int, int> coloring = color(ig, node, 2);

    for (int i = 0; i < node; i++)
    {
        cout << get_var[i] << ":" << coloring[i] << endl;
    }


    cout<<"doing code gen now"<<endl;

    init_codegen("tgt1.asm",coloring,node);




    for (int i = 0; i < ctr; i++)
    {
        
        emit_tgt_instr(blocks[i]);
    }


}
/*int main()
{



    set<int> s1;

    // Function to insert elements
    // in the set container
    s1.insert(1);
    s1.insert(4);
    s1.insert(2);
    s1.insert(5);
    s1.insert(3);

    cout << "The elements in set1 are: ";
    for (auto it = s1.begin(); it != s1.end(); it++)
        cout << *it << " ";

    set<int> s2;

    // Function to insert one set to another
    // all elements from where 3 is to end is
    // inserted to set2
    s2=s1;




    s2.insert(6);

    compute_union(s1,s2);



    cout << "\nThe elements in set2 are: ";
    for (auto it = s1.begin(); it != s1.end(); it++)
        cout << *it << " ";

    return 0;



}*/