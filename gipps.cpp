#include "p_gipps.h"
#include "gipps.h"
#include "model.h"
#include <math.h>
#include "iostream"
#include <algorithm>

using namespace std;

namespace Model{
    gipps::gipps(){
        P_gipps nuevo_gipps;
        params=nuevo_gipps.p_gipps;
    };
    double gipps::accel(point *leader,point *follower,Params *p){
        double an=p->Params_valor("an");
        double tau=p->Params_valor("tau");
        double vn=p->Params_valor("vn");
        double bn=p->Params_valor("bn");
        double sn=p->Params_valor("sn");
        double bg=p->Params_valor("bg");
        //cout<<leader->X()<<" "<<leader->V()<<"   "<<leader->A()<<endl;
        double vnfl = follower->V()+2.5*an*tau*(1-(follower->V()/vn))*sqrt(0.025+(follower->V()/vn));
        double vncg= bn*tau+sqrt(pow(bn,2)*pow(tau,2)-bn*(2*(leader->X()-sn-follower->X())-(follower->V()*tau)-(pow(leader->V(),2)/bg)));
        double dv=min(vnfl,vncg) - follower->V();
        return dv/tau;
    };
    double gipps::equil_spcg(point *leader,point *follower, Params *p){
        double tau=p->Params_valor("tau");
        double bn =p->Params_valor("bn");
        double bg=p->Params_valor("bg");
        double real_sparsam_equilibrium=3*follower->V()*tau/2 + pow(leader->V(),2)/(2*bg) - pow(follower->V(),2)/(2*bn);
        //double sparsam_equilibrium=((3*tau)/2)*follower.V()+((leader.V()/(2*bg))-(follower.V()/2*bn));
        return real_sparsam_equilibrium;
        
    };
    double gipps::wave_speed(point leader,point follower,Params p){
        return 0.0;
        
    };
    bool gipps::lch_left(point *leader, point *follower, point *new_leader, point *new_follower,Params *p){
        double vn = p->Params_valor("vn");
        double sn = p->Params_valor("sn");
        if (0.9*vn>follower->V()){
	    if (new_follower == NULL ){
		if (new_leader == NULL){
				return true;
		}
		else{
			if( new_leader->X() - sn >=follower->X() + equil_spcg(new_leader,follower,p)){
				return true;
			}
		}

	    }
	    else{
		if (new_leader == NULL){
			if (new_follower->X()+sn<follower->X() && follower->X() - sn >= new_follower->X() + equil_spcg(follower,new_follower,p)){
				return true;
			}
		}
	    	else{
			if (new_follower->X()+sn<follower->X() && follower->X() - sn >= new_follower->X() + equil_spcg(follower,new_follower,p) && new_leader->X() - sn >= follower->X() + equil_spcg(new_leader,follower,p)){
                	return true;
                	}
		}
	    }
	}
	return false;

    };
    bool gipps::lch_right(point *leader, point *follower, point *new_leader, point *new_follower, Params *p){
        double vn = p->Params_valor("vn");
        double sn = p->Params_valor("sn");
        if (0.95*vn<follower->V()){
	    if (new_follower == NULL ){
		if (new_leader== NULL){
			return true;
		}
		else{
			if( new_leader->X() - sn >=follower->X() + equil_spcg(new_leader,follower,p)){
				cout<<"retornara true"<<endl;
				return true;
			}
			
		}
	    }
	   else{
		if (new_leader == NULL){
			if (new_follower->X()+sn<follower->X() && follower->X() - sn >= new_follower->X() + equil_spcg(follower,new_follower,p)){
				return true;
			}
		}
	    	else{
            		if (new_follower->X()+sn<follower->X() && follower->X() - sn >= new_follower->X() + equil_spcg(follower,new_follower,p) && new_leader->X() - sn >=follower->X() + equil_spcg(new_leader,follower,p)){
                	return true;
            		}
		}
	    }
        }
        return false;
        
    };
    
}
