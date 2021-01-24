#include <iostream>
#include "point.h"
#include "params.h"
#include "model.h"
#include "geometry.h"
#include "creator.h"
#include <vector>
#include "simulation.h"
#include "trajectory.h"


using namespace std;
using namespace Geometry;
using namespace Model;

namespace Simulation{
    
simulation::simulation(model *_Model,double Time,geometry *_geometry,creator *_Creator,trajectory leaders,double _dt){
    Model=_Model;
    T=Time;
    dt=_dt;
    GEO=_geometry;
    Creator=_Creator;
    vector_initial=leaders;
};
point *simulation::create_leader_trajectory(point *ld_car,int time){
    double x_0=ld_car->X();
    double v_0=ld_car->V();
    double lane_0=ld_car->LANE();
    double new_t =ld_car->T() + dt;
    double a_0;
    double new_v;
    double new_x;
    a_0=ld_car->A();
    new_v = v_0 + dt*(a_0);//aca aplicamos el metodo de euler para determinar los nuevos delta (variaciones)
    new_x = x_0 + dt*(v_0);
    point *new_point=new point(new_t,new_x,new_v,a_0,lane_0);
    return new_point;


};
point* simulation::create_new_point(point *ld_car,point *fl_car){
    double x_0=fl_car->X();
    double v_0=fl_car->V();
    double accel=Model->accel(ld_car,fl_car,Model->params);
    double lane_0=fl_car->LANE();
    double new_t =fl_car->T() + dt;
    double new_v = v_0 + dt*(accel);//aca aplicamos el metodo de euler para determinar los nuevos delta (variaciones)
    double new_x = x_0 + dt*(v_0);
    point *new_point=new point(new_t,new_x,new_v,accel,lane_0);
    return new_point;
        
};
vector<trajectory> simulation::run(){
    int n = T/dt;
    vector < vector<trajectory> > Lanes;
    vector <trajectory> simu;
//creamos un vector por cada pista que exista y una situacion inicial para cada pista segun un lider diferente 
    for (int lane=0 ; lane<GEO->Lanes() ; ++lane){
    	vector <trajectory > new_lane;
    	Lanes.push_back(new_lane);
	trajectory initial_case;
	point	*leader=vector_initial[lane];
    	initial_case=Creator->initial_state(leader);
	cout<<"la pista :"<<lane<<"tiene "<<initial_case.len()<<" autos"<<endl;
    	int num_cars=initial_case.size();
    	for (int i=0 ;i<num_cars;++i){
		point *new_initial_car=initial_case[i];
		trajectory *new_vector=new trajectory();
		new_vector->push_back(new_initial_car);
		Lanes[lane].push_back(*new_vector);

    	}
    point *second_time_leader=create_leader_trajectory(Lanes[lane][0][0],1);
    Lanes[lane][0].push_back(second_time_leader);
    }
//por cada paso de tiempo evaluamos cada una de las pistas y creamos un valor de tiempo en cada una de las trayectorias
    for (int l=0;l<=n;++l){
	for (int d=0 ; d<GEO->Lanes() ; ++d){
//si el valor primero de la pista ( de mayor distancia ) supera el largo de la pista entonces retorna lo que lleva  la simulacion 
		if (Lanes[d][0][l]->X()>=GEO->length ){
			 int contador=0;
    			for (int i = 0 ; i<Lanes.size() ; ++i){
				for (int j=0 ; j<Lanes[i].size() ; ++j){
					simu.push_back(Lanes[i][j]);
					contador=contador+1;

					}
    			}
    			cout<<"cantidad de autos : "<<contador<<endl;
    			return simu;
		}
		if (Lanes[d].size()!=0){
		vector <int> indices (GEO->Lanes(),0);//creamos un vector de contadores que tendra la misma cantidad de valores que de pistas tenga la simulacion
		//recorremos cada auto de la pista hasta que se cumpla el valor maximo de la pista y lo evaluamos
		while (indices[d]<=Lanes[d].size()){
			//cout<<"la pista :" << d <<" tiene largo : "<<Lanes[d].size()<<endl;
			//si es el primer auto de la pista, se ejecuta de forma diferente
			if (indices[d]==0){
				point *old_time_leader_2=Lanes[d][indices[d]][Lanes[d][indices[d]].size()-2];
				point *old_time_leader_1=Lanes[d][indices[d]][Lanes[d][indices[d]].size()-1];
				point *new_leader=create_new_point(old_time_leader_2,old_time_leader_1);
				Lanes[d][indices[d]].push_back(new_leader);
			}
			else{	
		    		point *old_point=Lanes[d][indices[d]-1][Lanes[d][indices[d]-1].size()-1];
		//si llegamos al ultimo auto de la pista, pregunta si es posible crear otro auto en la pista
				if (indices[d]==Lanes[d].size()){
		    			point *new_car=Creator->create(old_point);
		    			if (new_car!=NULL){
		    				int new_car_lane=new_car->LANE();	
						trajectory *new_vector=new trajectory();
						new_vector->push_back(new_car);
						Lanes[d].push_back(*new_vector);
					}
					else{
				//si el nuevo auto es NULL, sale del while (es valido porque como estamos evaluando si el ultimo auto de la pista se puede crear no hay problema de terminarlo ahi )
			     			break;
                            		}
		      		}
		       		else{ 	
				/*En esta  parte lo que hare sera usar el valor de d (la pista a evaluar)  */
		       			point *old_point_2=Lanes[d][indices[d]-1][Lanes[d][indices[d]-1].size()-2];
					point *current_point=Lanes[d][indices[d]][Lanes[d][indices[d]].size()-1];
					point *new_point=create_new_point(old_point_2,current_point);
					if (new_point == NULL){
						//cout<<" el new_point es NULL "<<endl;//en la funcion no tiene opcion de retornar NULL
						break;
					}
					else{	
				//evaluamos si el auto creado cambia de pista ( en este caso solo pueden ser 2 pistas pero tengo que extenderlo)(ya no se usa el valor de d, sino de la pista del auto )
						int new_point_lane=new_point->LANE();
						double current_point_distance=new_point->X();//posicion del auto que vamos a evaluar
						//en el futuro quisiera hacer un ciclo for 
						//evaluamos para el caso que la pista sea 1
						if (new_point_lane==1){
							//Queremos ubicarnos en la ultima posicion ya evaluada
							double current_distance=Lanes[0][indices[new_point_lane-1]][Lanes[0][indices[new_point_lane-1]].size()-1]->X();
							//ubicamos el contador de el auto que sera el nuevo follower
							while ((current_distance > current_point_distance) && (indices[new_point_lane-1] < Lanes[0].size()-1)){
                                                		current_distance=Lanes[0][indices[new_point_lane-1]][Lanes[0][indices[new_point_lane-1]].size()-1]->X();
								indices[new_point_lane-1]=indices[new_point_lane-1] + 1;
									
							}
							point* new_follower_next_lane;
							point* new_leader_next_lane;
							if (indices[new_point_lane-1]>=Lanes[new_point_lane-1].size()-1){
								cout<<"el contador de la pista 0 sale de la pista :"<<indices[new_point_lane-1]<<endl;	
								new_follower_next_lane=(point*) NULL;
							}
							else{
								new_follower_next_lane = Lanes[0][indices[new_point_lane-1]][Lanes[0][indices[new_point_lane-1]].size()-1];
							}
							//despues de encontrar el contador de la proxima pista, preguntamos si existira un leader
							if (indices[new_point_lane-1]==0){
								cout<<"el contador de la pista 0 es : "<<indices[new_point_lane-1]<<endl;
								new_leader_next_lane=(point*)NULL;

							}
							else{
								cout<<"se cae aca"<<endl;
								new_leader_next_lane = Lanes[0][indices[new_point_lane-1]-1][Lanes[0][indices[new_point_lane-1]-1].size()-1];
							}
							//una vez teniendo todo lo necesario preguntamos si es conveniente doblar a la izquierda
							if(Model->lch_left(old_point_2,new_point,new_leader_next_lane,new_follower_next_lane,Model->params)){
								cout<<"hay cambio de pista a la izquierda"<<endl;
								new_point->set_lane(0);
								trajectory new_car_left=Lanes[1][indices[new_point_lane]];
								new_car_left.push_back(new_point);
								Lanes[0].insert(Lanes[0].begin() + indices[new_point_lane-1],new_car_left);
								indices[new_point_lane-1]=indices[new_point_lane-1]+1;
								Lanes[1].erase(Lanes[1].begin() + indices[new_point_lane]);
								indices[new_point_lane]=indices[new_point_lane]-1;
							}
							else{
								Lanes[1][indices[new_point_lane]].push_back(new_point);
							}
						  }
						//hacen lo mismo pero con la pista 0
						else if (new_point_lane == 0){
								double current_distance=Lanes[1][indices[new_point_lane+1]][Lanes[1][indices[new_point_lane+1]].size()-1]->X();
                     				//Debemos encontrar el contador de la otra pista para encontrar los new_leader y los new_follower
								while ((current_distance > current_point_distance) && (indices[new_point_lane+1] < Lanes[1].size()-1)){
                                                                        current_distance=Lanes[1][indices[new_point_lane+1]][Lanes[1][indices[new_point_lane+1]].size()-1]->X();
									indices[new_point_lane+1]=indices[new_point_lane+1] + 1;
								}
								point* new_follower_next_lane;
								point* new_leader_next_lane;
								if (indices[new_point_lane+1]>=Lanes[new_point_lane+1].size()-1){
									cout<<"el contador de la pista 1 sale de la pista :"<<indices[new_point_lane+1]<<endl;
									new_follower_next_lane=(point*) NULL;
								}
								else{
									new_follower_next_lane = Lanes[1][indices[new_point_lane+1]][Lanes[1][indices[new_point_lane+1]].size()-1];
								}
						//Despues de enocontrar el contador de la proxima pista, preguntamos si existira un leader
								if (indices[new_point_lane+1]==0){
									cout<<"el contador de la pista 1 es : "<<indices[new_point_lane+1]<<endl;
									new_leader_next_lane=(point*)NULL;
								}
								else{
									new_leader_next_lane=Lanes[1][indices[new_point_lane+1]-1][Lanes[1][indices[new_point_lane+1]-1].size()-1];
								}
								if(Model->lch_right(old_point_2,new_point,new_leader_next_lane,new_follower_next_lane,Model->params)){
										cout<<"hay cambio de pista a la derecha"<<endl;
										new_point->set_lane(1);
										trajectory new_car_right=Lanes[0][indices[new_point_lane]];
										new_car_right.push_back(new_point);
										Lanes[1].insert(Lanes[1].begin() + indices[new_point_lane+1],new_car_right);
										indices[new_point_lane+1]=indices[new_point_lane+1]+1;
										Lanes[0].erase(Lanes[0].begin() + indices[new_point_lane]);
										indices[new_point_lane]=indices[new_point_lane]-1;
								}
								else{
									    Lanes[0][indices[new_point_lane]].push_back(new_point);
								}
						}
					}	
		       		}
			}		
			indices[d]=indices[d]+1;
			//cout <<"el valor de d es :  "<< d <<" indices[d] es : " << indices[d] << endl;
			}
              }
	      }
    }
    int contador=0;
    for (int i = 0 ; i<Lanes.size() ; ++i){
	for (int j=0 ; j<Lanes[i].size() ; ++j){
		simu.push_back(Lanes[i][j]);
		contador=contador+1;

	}
    }
    cout<<"cantidad de autos : "<<contador<<endl;
    return simu;
};
}

