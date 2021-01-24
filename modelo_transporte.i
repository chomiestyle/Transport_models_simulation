%module modelo_transporte

%{
#include "params.h"
#include "p_gipps.h"
#include "trajectory.h"
#include "point.h"
#include "gipps.h"
#include "creator.h"
#include "fixed_state_creator.h"
#include "fixed_demand_creator.h"
#include "geometry.h"
#include "simulation.h"
%}

%include "params.h"
%include "p_gipps.h"
%include "trajectory.h"
%include "point.h"
%include "gipps.h"
%include "geometry.h"
%include "creator.h"
%include "fixed_state_creator.h"
%include "fixed_demand_creator.h"
%include "simulation.h"
%include <std_string.i>
%include <std_iostream.i>
%include <std_vector.i>
%include <cpointer.i>

namespace std
{
  %template(trajectories) vector<trajectory>;
}
namespace Model
{

	%extend trajectory {
		point* __getitem__(unsigned int i){
			return (*($self)).get(i);
		}
	}
}

