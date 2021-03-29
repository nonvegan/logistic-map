logisticMap : logisticMap.o
	g++ logisticMap.o -o logisticMap -lsfml-graphics -lsfml-window -lsfml-system 
	rm logisticMap.o
logisticMap.o : logisticMap.cpp
	g++ -c logisticMap.cpp

