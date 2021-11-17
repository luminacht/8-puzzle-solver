#include<iostream>
using namespace std;

int main(){

}

// Iterative deepning search.// 
void IDS() {
    int depth=0; // Depth cost.  

    cout << "Starting IDS Algorithm... \n"; 

    while(true){          
        cur = start;     
        fringe.push_front(cur);

    while (!fringe.empty())     
    {       // process the fringe states . 

    cur = fringe.front();  

    // if the front is goal.       
    if (cur.is_goal()) {      

        // calcilate the search time in msec.         
        runtime = ((clock() * 1000) / CLOCKS_PER_SEC) - timer; 

        // print the search costs.         
        cout << "Time= " << runtime << "\n";         
        cout << "Space= " << space << "\n";         
        cout << "Cost= " << cur.g << "\n"; 

        //print the solution path.         
        cout << "Path:\n";         
        PrintPath(&cur); 

        // exit the function         
        return;       
        }

        //if state not the goal and in the search depth.       
        else if (depth > cur.g)      
        {         
            //expand the state.         
            Expand();       
        } 

        else 
        {   //not useable state.         
            //pop it out         
            fringe.pop_front();       
        }     
    }     
    // clear both lists for the next round.     
    fringe.clear();     
    closed.clear();       
    
    // increase the search depth.     
    depth++;   
    } 
}