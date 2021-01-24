CC=g++
CC2=gcc
CFLAGS=-std=c++11 -fPIC
modelo_transporte.so:Final simulation.o geometry.o fixed_demand_creator.o fixed_state_creator.o gipps.o trajectory.o point.o   p_gipps.o params.o diccionario.o modelo_transporte_wrap.o
	$(CC)  $(CFLAGS) -shared simulation.o geometry.o fixed_demand_creator.o fixed_state_creator.o gipps.o trajectory.o point.o p_gipps.o  params.o diccionario.o modelo_transporte_wrap.o -o _modelo_transporte.so
	

modelo_transporte_wrap.cxx: modelo_transporte.i
	swig -python -c++ modelo_transporte.i 

modelo_transporte_wrap.o: modelo_transporte_wrap.cxx
	$(CC)  $(CFLAGS) -c modelo_transporte_wrap.cxx -I/usr/include/python2.7 -o modelo_transporte_wrap.o

Final: main.o simulation.o geometry.o fixed_demand_creator.o fixed_state_creator.o linear.o idm.o gipps.o trajectory.o point.o p_linear.o p_idm.o p_gipps.o params.o diccionario.o
	$(CC)  $(CFLAGS) main.o simulation.o geometry.o fixed_demand_creator.o fixed_state_creator.o linear.o idm.o gipps.o trajectory.o point.o p_linear.o p_idm.o p_gipps.o params.o diccionario.o -o Final
	
main.o: main.cpp simulation.h geometry.h fixed_demand_creator.h fixed_state_creator.h params.h point.h trajectory.h model.h gipps.h idm.h linear.h p_linear.h creator.h 
	$(CC) $(CFLAGS) -c -o main.o main.cpp

simulation.o : simulation.cpp simulation.h model.h params.h point.h geometry.h creator.h
	$(CC) $(CFLAGS) -c -o simulation.o simulation.cpp
	
geometry.o: geometry.cpp geometry.h 
	$(CC) $(CFLAGS) -c -o geometry.o geometry.cpp	

fixed_demand_creator.o: fixed_demand_creator.cpp fixed_demand_creator.h creator.h model.h params.h point.h
	$(CC) $(CFLAGS) -c -o fixed_demand_creator.o fixed_demand_creator.cpp

fixed_state_creator.o: fixed_state_creator.cpp fixed_state_creator.h creator.h model.h params.h point.h
	$(CC) $(CFLAGS) -c -o fixed_state_creator.o fixed_state_creator.cpp
	
linear.o: linear.cpp linear.h model.h p_linear.h 
	$(CC)  $(CFLAGS) -c -o linear.o linear.cpp

idm.o: idm.cpp idm.h model.h p_idm.h
	$(CC)  $(CFLAGS) -c -o idm.o idm.cpp 

gipps.o: gipps.cpp gipps.h model.h p_gipps.h
	$(CC)  $(CFLAGS) -c -o gipps.o gipps.cpp

trajectory.o:trajectory.cpp trajectory.h point.h
	$(CC)  $(CFLAGS) -c -o trajectory.o trajectory.cpp

point.o: point.cpp point.h 
	$(CC)  $(CFLAGS) -c -o point.o point.cpp

p_linear.o: p_linear.cpp  p_linear.h
	$(CC)  $(CFLAGS) -c -o p_linear.o p_linear.cpp

p_idm.o: p_idm.cpp  p_idm.h
	$(CC)  $(CFLAGS) -c -o p_idm.o p_idm.cpp

p_gipps.o: p_gipps.cpp  p_gipps.h
	$(CC)  $(CFLAGS) -c -o p_gipps.o p_gipps.cpp

params.o: params.cpp params.h
	$(CC)  $(CFLAGS) -c -o params.o params.cpp 

diccionario.o: diccionario.cpp diccionario.h
	$(CC)  $(CFLAGS) -c -o diccionario.o diccionario.cpp 





clean:
	rm *.o
	rm -f Final
	rm *.cxx
	rm -f _modelo_transporte.so
	rm -f modelo_transporte.py
	rm -f modelo_transporte.pyc

