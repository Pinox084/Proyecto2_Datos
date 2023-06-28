#include <cmath>
#include <iostream>
#include <vector>
#include "Quad.h"
#include <time.h>
#include <chrono>
using namespace std;
int main()
{
    Quad center(Point(0, 0), Point(3000000, 3000000));
    for(int j=0; j<5;j++){
    	string linea;
	ifstream archivo("worldcitiespop_fixed.csv");
	int i=0;
	getline(archivo, linea);
	
	while(getline(archivo,linea) && i<30000000){
		stringstream stream(linea);
		string posicion_x, posicion_y, poblacion, basura;
		getline(stream, basura,';');
		getline(stream, basura,';');
		getline(stream, basura,';');
		getline(stream, basura,';');
		getline(stream, poblacion,';');
		getline(stream, posicion_y,';');
		getline(stream, posicion_x,';');
		int population=stoi(poblacion);
		srand(time(NULL));
		float  derp = stof(posicion_x)+180;
        float pepe = stof(posicion_y)+180;
        derp = derp * 1000;
        pepe = pepe * 1000;
        int aux1 = (int)derp;
        int aux2 = (int)pepe;
        Point euler(aux1, aux2);
		int num=1+rand()%(1001-1);
		Node* ins1= new Node(euler,population);
		center.insert(ins1);
		i++;
	}
	auto start_time= chrono::high_resolution_clock::now();
	int aux = center.aggregateRegion(Point(150,150),3000000);
	auto end_time=chrono::high_resolution_clock::now();
	chrono::duration<float, milli> duration = end_time - start_time;
    cout<<"duracion: "<< duration.count()<<"ms<\n"<<endl;
    cout<<"cantidad de poblacion en la zona:  "<< aux<<endl;
	}

    return 0;
}
