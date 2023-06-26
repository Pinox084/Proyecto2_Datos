#include <cmath>
#include <iostream>
#include <vector>
#include "Quad.cpp"//esto cambia dependiendo de DEV o sublime con terminal

using namespace std;
int main()
{
    Quad center(Point(0, 0), Point(30000000, 30000000));
    string linea;
	ifstream archivo("worldcitiespop_fixed.csv");
	int i=0;
	getline(archivo, linea);
	while(getline(archivo,linea) && i<20000){
		stringstream stream(linea);
		string posicion_x, posicion_y, poblacion, basura;
		getline(stream, basura,';');
		getline(stream, basura,';');
		getline(stream, basura,';');
		getline(stream, basura,';');
		//getline(stream, basura,';');//son saltos de columnas
			
		getline(stream, poblacion,';');
		getline(stream, posicion_y,';');
		getline(stream, posicion_x,';');
		
		int pox;
		int poy;
		float delta_pox=stof(posicion_x) - stoi(posicion_x);
		float delta_poy=stof(posicion_y) - stoi(posicion_y);
		int population=stoi(poblacion);
		
		pox=stoi(posicion_x)+delta_pox*10000000;
		poy=stoi(posicion_y)+delta_poy*10000000;
		Node* ins1= new Node(Point(pox+180,poy+180),population);
		center.insert(ins1);
		cout<<"puntero: "<<ins1<<endl;
		i++;
	}
	cout<<"iteraciones "<<i<<endl;
    cout<<"TAMANO DE LA LISTA----->"<<center._list().size()<<endl;
    cout<<"ELEMENTO DE LA LISTA 0----->"<<center._list().at(0)->data<<endl;
    cout<<"ELEMENTO DE LA LISTA 1----->"<<center._list().at(1)->data<<endl;
    return 0;
}
