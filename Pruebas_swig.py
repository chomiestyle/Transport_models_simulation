# -*- coding: utf-8 -*-
"""
Created on Mon Aug 27 14:59:13 2018

@author: root
"""

from modelo_transporte import *

ld=point(3.9,10,5,1,1)
GEO=geometry(50,2,0,0,0)
Model=gipps()
creator=fixed_state_creator(Model,0.2,12)
initial_cars=creator.initial_state(ld)
#for i in range (10):
print(initial_cars[1].T())
#simu=simulation(Model,10,GEO,creator,ld)
#nueva_matriz=simu.run()