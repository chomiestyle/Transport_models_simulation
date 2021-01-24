# -*- coding: utf-8 -*-
"""
Created on Fri Aug  3 13:38:33 2018

@author: ing
"""

from modelo_transporte import*
import matplotlib.pyplot as pt

#inicializamos la simulacion
leader_lanes=trajectory()
ld_1=point(0,1000,2,0,0)
leader_lanes.add(ld_1)
ld_2=point (0,500,6,0,1)
leader_lanes.add(ld_2)
geo=geometry(7000,2,0,0,0)
model=gipps()
creator=fixed_state_creator(model,4,18)
simu=simulation(model,1000,geo,creator,leader_lanes,0.1)
r=simu.run()


#graficamos


def graficar(arreglo):
    pt.figure()
    for auto in range(235):
        new_trajectory=trajectory()
        new_trajectory=arreglo[auto]
        tt=[new_trajectory[p].T() for p in range (new_trajectory.len())]
        xx=[new_trajectory[p].X() for p in range (new_trajectory.len())]
        pt.plot(tt,xx)
    pt.show()
    
def graficar2(arreglo):
    pt.figure()
    colores=['g-', 'r-', 'b-']
    #pt.plot(tt,xx)
    for i in range(90):
        new_trajectory=trajectory()
        auto = i*12
        new_trajectory=arreglo[auto]
        tt1=[new_trajectory[p].T() for p in range (new_trajectory.len()) if new_trajectory[p].LANE()==0]
        xx1=[new_trajectory[p].X() for p in range (new_trajectory.len()) if new_trajectory[p].LANE()==0]
        tt2=[new_trajectory[p].T() for p in range(new_trajectory.len()) if new_trajectory[p].LANE()==1]
        xx2=[new_trajectory[p].X() for p in range(new_trajectory.len()) if new_trajectory[p].LANE()==1]
        if auto==0:
            pt.plot(tt1,xx1,colores[0])
            pt.plot(tt2,xx2,colores[0])
            
        pt.plot(tt1,xx1,colores[1])
        pt.plot(tt2,xx2,colores[2])
    pt.show()
    
graficar2(r)