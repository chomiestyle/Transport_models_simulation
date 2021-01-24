
#include "params.h"
#include "p_linear.h"
#include "p_idm.h"
#include "p_gipps.h"
#include <iostream>
#include "point.h"
#include "model.h"
#include "gipps.h"
#include "idm.h"
#include "linear.h"
#include "creator.h"
#include "fixed_state_creator.h"
#include "fixed_demand_creator.h"
#include <vector>
#include "geometry.h"
#include "simulation.h"
#include "trajectory.h"

using namespace Model;
using namespace std;
using namespace Creator;
using namespace Geometry;
using namespace Simulation;

int main( )
{
    trajectory *leader_lanes=new trajectory();
    point *leader = new point(0,1000,2,0,0);
    point* prueba =leader_lanes->add(leader);
    cout<< prueba->X()<<endl;
    point *leader2=new point(0,500,6,0,1);
    leader_lanes->add(leader2);



    //point *follower = new point(3.9,-6,3,1,2);
    //point *nuevo_leader = new point(5.9,0.08,3,1,2);
    //point *nuevo_follower = new point(1.9,-6,3,1,2);
    geometry *geometria_nueva= new geometry(7000,2,0,0,0);
    gipps g;
    fixed_state_creator *creador_nuevo=new fixed_state_creator(&g,4,18);
    simulation nueva_simulacion=simulation(&g,1000,geometria_nueva,creador_nuevo,*leader_lanes,0.1);
    vector<trajectory> Lanes_simulation= nueva_simulacion.run();
    //cout<<"la cantidad de autos en la fila 1 es  :"<<Lanes_simulation.size()<<endl;
    /*for (int i=0 ; i<Lanes_simulation[1].size();++i){
	cout<<"entra en otra trajectoria de la linea 2 con largo "<<Lanes_simulation[1][i].size()<< endl;
	for (int j=0; j<Lanes_simulation[1][i].size();++j){
	 cout<<"entra al ultimo for"<<endl; 
         cout<<" el valor del X en el auto es "<<Lanes_simulation[1][i].get(j)->X()<<"y el valor de tiempo es "<<Lanes_simulation[1][i].get(j)->T()<<endl;
	}
    }*/
    
    return 0;
}
