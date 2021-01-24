#ifndef GEOMETRY_H
#define GEOMETRY_H
namespace Geometry{
class geometry{
    public:
        double length;
        int lanes;
        double merge;
        double diverge;
        double scope;
        
        
    public:
         geometry(double _length, int _lanes ,double _merge,double _diverge,double _scope);
         double Length( );//entrega el largo de la pista
         int Lanes();
         void Set_lanes(int n);//agrega n pistas
         double Merge();//en donde converge
         double Diverge();//en donde diverge
         double Scope();//pendiente
         bool Can_lch(double x);//la geometria permite doblar?
         void Set_merge(double x);//agrega convergencia
         void Set_diverge(double x);//agrega divergencia
    };
}
#endif
