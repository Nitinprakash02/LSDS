LSDS_HW4: LSDS_HW4.o Queries_NW.o Queries_BL.o
	g++ LSDS_HW4.o Queries_NW.o Queries_BL.o -o LSDS_HW4
	
LSDS_HW2.o: LSDS_HW4.cpp
	g++ -c LSDS_HW4.cpp
	
Queries_NW.o: Queries_NW.cpp Queries_NW.h
	g++ -c Queries_NW.cpp
	
Queries_BL.o: Queries_BL.cpp Queries_BL.h
	g++ -c Queries_BL.cpp
	
clean:
	rm *.o