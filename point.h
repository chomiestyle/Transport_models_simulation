#ifndef _POINT
#define _POINT
namespace Model{

    class point{
     private:
        double t;//tiempo
        double x;//posicion
        double v;//velocidad
        double a;//aceleracion
        int lane;//la pista
     public:
        point (double ,double ,double ,double,int );
        void set_accel(double);
        void set_x(double);
        void set_lane(int);
        double T();
        double X();
        double V();
        double A();
        int LANE();
    
    
    };
    
}
#endif
