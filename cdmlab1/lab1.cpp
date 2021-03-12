#include "common.h"

using namespace Minisat;

/*
//init states of stones
static int states[1000];

//which button/switch controls which stones
static int button[1000][2];

//SAT answer
static bool answer[1000];

//the number of buttons/switches
static int m;

//the bumber of stones
static int n;

//the number of cases
static int iter;
*/


bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var variables[1000];
    int i, j;
    int switchs[2];
    int switch_index = 0;

    for(i = 0; i<m; ++i)
        variables[i] = solver.newVar();//each switch
    
    for(i=0; i<n; i++)//bianli each stone
    {
        switch_index = 0;
        if (states[i]==1)//stone is above the water
        {
            for (j=0; j<m; j++)
            {
                if (button[j][0]==i+1 || button[j][1]==i+1 ) {switchs[switch_index]=j;switch_index++;}
                if (switch_index == 2) break;
            }
            
            if (switch_index == 2)//stone is controlled by 2 switches
            {
                solver.addClause( ~mkLit(variables[ switchs[0] ]),  mkLit(variables[ switchs[1] ]));
                solver.addClause( mkLit(variables[ switchs[0] ]),  ~mkLit(variables[ switchs[1] ]));
            }
            else solver.addClause( ~mkLit(variables[ switchs[0] ]));//stone is controlled by 1 switch
            
        }

        else if (states[i]==0)//stone is under the water
        {
            for (j=0; j<m; j++)
            {
                if (button[j][0]==i+1 || button[j][1]==i+1 ) {switchs[switch_index]=j;switch_index++;}
                if (switch_index == 2) break;
            }
            if (switch_index == 2)//stone is controlled by 2 switches
            {
                solver.addClause( ~mkLit(variables[ switchs[0] ]),  ~mkLit(variables[ switchs[1] ]));
                solver.addClause( mkLit(variables[ switchs[0] ]),  mkLit(variables[ switchs[1] ]));
            }
            else solver.addClause( mkLit(variables[ switchs[0] ]));//stone is controlled by 1 switch
        }
    } 
    
    
    //TODO : your solution here.


    //solve SAT problem
    auto sat = solver.solve();
    if(sat)
    {
        for(i = 0; i < m; ++i)
            answer[i] = (solver.modelValue(variables[i]) == l_True);
        return true;
    }
    return false;
}




