#include "geometry.h"

namespace Geometry{

geometry::geometry(double _length, int _lanes, double _merge, double _diverge, double _scope){
    length=_length;
    lanes=_lanes;
    merge=_merge,
    diverge=_diverge;
    scope=_scope;
    
};
double geometry::Length(){
    return length;
    
};
int geometry::Lanes(){
    return lanes;
    
};
void  geometry::Set_lanes(int n){
    lanes=lanes + n;
    return;
    
};
double geometry::Merge(){
    return merge;
        
};
double geometry::Diverge(){
    return diverge;
        
};
double geometry::Scope(){
    return scope;
        
};
bool geometry::Can_lch(double x){
    //encontrar si se puede doblar por la forma de la pista
    return true;
        
};
void geometry::Set_merge(double x){
    return;
        
};
void geometry::Set_diverge(double x){
    return;
        
};
}

