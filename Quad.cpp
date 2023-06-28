#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Quad.h"
using namespace std;
Quad:: Quad(Point topL, Point botR)
{
	//el que almacena la ciudad
	n = NULL;
	
	//los cuadrantes
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    
    //los limites del cuadrante actual
    topLeft = topL;
    botRight = botR;
}


// Insert a node into the quadtree
void Quad::insert(Node* node)
{
        if (node == NULL)
		return;

	// Current quad cannot contain it
	if (!inBoundary(node->pos))
		return;

	// We are at a quad of unit area
	// We cannot subdivide this quad further
	if (abs(topLeft.x - botRight.x) <= 1
		&& abs(topLeft.y - botRight.y) <= 1) {
	  if (n == NULL)
	  		black=true;
			n = node;

	    return;
	}

	if ((topLeft.x + botRight.x) / 2 > node->pos.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
		  if (topLeftTree == NULL) 
				topLeftTree = new Quad(
					Point(topLeft.x, topLeft.y),
					Point((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2));
			topLeftTree->black=true;
		  topLeftTree->insert(node);
		}

		// Indicates botLeftTree
		else {
		  if (botLeftTree == NULL) 
				botLeftTree = new Quad(
					Point(topLeft.x,
						(topLeft.y + botRight.y) / 2),
					Point((topLeft.x + botRight.x) / 2,
					      botRight.y));
			botLeftTree->black=true;
		  botLeftTree->insert(node);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 > node->pos.y) {
		  if (topRightTree == NULL) 
				topRightTree = new Quad(
					Point((topLeft.x + botRight.x) / 2,
						topLeft.y),
					Point(botRight.x,
						(topLeft.y + botRight.y) / 2));
			topRightTree->black=true;
		  topRightTree->insert(node);
		}

		// Indicates botRightTree
		else {
		  if (botRightTree == NULL)
				botRightTree = new Quad(
					Point((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2),
					Point(botRight.x, botRight.y));
		  botRightTree->black=true;
		  botRightTree->insert(node);
		}
	}
}

Node* Quad::search(Point p)
{
	// Current quad cannot contain it
	if (!inBoundary(p))
		return NULL;

	// We are at a quad of unit length
	// We cannot subdivide this quad further
	if (n != NULL)
		return n;

	if ((topLeft.x + botRight.x) / 2 > p.x) {
		// Indicates topLeftTree
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		}

		// Indicates botLeftTree
		else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	}
	else {
		// Indicates topRightTree
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				return NULL;
			return botRightTree->search(p);
		}
	}
};
 
// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
	return (p.x >= topLeft.x && p.x <= botRight.x
			&& p.y >= topLeft.y && p.y <= botRight.y);
}
void escribir(string texto){
	ofstream out_file;
    out_file.open("Prueba.txt", ios::app);
    out_file << texto <<";\n";
    out_file.close();
}
void Quad::list(Quad* t){	
	if(t!=NULL && t->n!=NULL){
		string s1 = to_string(t->n->data);
		string s2 = to_string(t->n->pos.x);
		string s3 = to_string(t->n->pos.y);
		string s;
		escribir(s.append(s2).append(".").append(s3).append(";").append(s1));
	}
	else if(t!=NULL && t->n==NULL){
		if(t->botLeftTree!=NULL && t->botLeftTree->black==true) list(t->botLeftTree);
		if(t->botRightTree!=NULL && t->botRightTree->black==true) list(t->botRightTree);
		if(t->topLeftTree!=NULL && t->topLeftTree->black==true) list(t->topLeftTree);
		if(t->topRightTree!=NULL && t->topRightTree->black==true) list(t->topRightTree);
	}
}
vector<Node*> Quad::_list(){
	remove("Prueba.txt");
	list(this->botLeftTree);
	list(this->botRightTree);
	list(this->topLeftTree);
	list(this->topRightTree);
	vector<Node*> contenedor;
	
	string linea;
	ifstream archivo("Prueba.txt");
	
	while(getline(archivo,linea)){
		stringstream stream(linea);
		string posicion_x,posicion_y;
		getline(stream, posicion_x,'.');
		getline(stream, posicion_y,';');
		contenedor.push_back(search(Point(stoi(posicion_x),stoi(posicion_y))));
	}
	return contenedor;
}
int Quad:: countRegion(Point p, int d ){

    Point aux1, aux2;
    int x1,x2,y1,y2;
    aux1.setXY(p.x - d, p.y-d);
    aux2.setXY(p.x +d, p.y +d);
    int aux = search_inRegion(this, aux1, aux2,1);

    return aux;
}

bool Quad:: inRect(Point rectAInit, Point rectALimit, Point rectBInit, Point rectBLimit){
    int A_left,A_right,A_bot,A_top,B_left,B_right,B_bot,B_top;
    A_left = rectAInit.x;
    A_right = rectALimit.x;
    A_top = rectAInit.y;
    A_bot = rectALimit.y;
    B_left = rectBInit.x;
    B_right = rectBLimit.x;
    B_top = rectBInit.y;
    B_bot = rectBLimit.y;


    if(A_bot <= B_top){return false;}
    if(A_top >= B_bot){return false;}
    if(A_right <= B_left){return false;}
    if(A_left >= B_right){return false;}
    //Bandera de colision
    return true;
}

int Quad::search_inRegion(Quad* current, Point init, Point limit, int caso){
    /* Funcion Principal de busqueda, recibe un quad, y los puntos del rectangulo del area de busqueda
    Junto con ello un entero que depende el caso que queremos entregar, como entero de nodos negros, blancos y negros, o poblacion"*/
    int derp = 0;
    int jesse = 0;

    if(current == NULL){
        return 0;
    }

    if(current->n != NULL && caso == 1){
        //caso solo negros
        return 1;
    }
    if(current->n != NULL && caso == 3){
        //caso negros y blancos
        return 1;
    }
    if(current->n != NULL && caso == 2){
        //caso de poblacion
        return current->n->data;
    }
    else{


        if(inRect(current->topLeft,current->botRight, init,limit) == true){
            if (caso == 3){
                derp++;
            }
            if(current->topLeftTree != NULL){
               
                    derp = derp + search_inRegion(current->topLeftTree, init, limit, caso);
                
            }
            if(current->topRightTree != NULL){
                
                    derp = derp + search_inRegion(current->topRightTree, init, limit, caso);
                   
            }
            if(current->botLeftTree != NULL){
               
                    derp = derp + search_inRegion(current->botLeftTree, init, limit, caso);
                  
            }
            if(current->botRightTree != NULL){
                
                    derp = derp + search_inRegion(current->botRightTree, init, limit, caso);
                    
            }

            if(caso == 3){
                if(current->topLeftTree == NULL){
                    jesse++;
                }
                if(current->topRightTree == NULL){
                    jesse++;
                }
                if(current->botLeftTree == NULL){
                    jesse++;
                }
                if(current->botRightTree == NULL){
                    jesse++;
                }
                derp = derp + jesse;
            }


        }


    }
   
    return derp;
}

int Quad:: totalPoints(){
    return search_inRegion(this,this->topLeft, this->botRight,1);
}

int Quad:: totalNodes(){
    return search_inRegion(this,this->topLeft, this->botRight,3);
}

int Quad:: aggregateRegion(Point p, int d){
    Point aux1, aux2;
    int x1,x2,y1,y2;
    aux1.setXY(p.x - d, p.y-d);
    aux2.setXY(p.x +d, p.y +d);
    int aux = search_inRegion(this, aux1, aux2,2);

    return aux;
}
void Quad::_printQuadTree(Quad* t, int indent)
{
  for(int i=0; i < indent; i++)
    std::cout << "--";

  if(t != NULL && t->n != NULL)
    std::cout << " " << t->n->data <<" "<< t->black<< std::endl;
  else if(t == NULL)
    std::cout << " NULL" << std::endl;
  else {
    std::cout << " X " <<" black=" << t->black<<std::endl;
  
    _printQuadTree(t->topLeftTree, indent+1);
    _printQuadTree(t->topRightTree, indent+1);
    _printQuadTree(t->botLeftTree, indent+1);
    _printQuadTree(t->botRightTree, indent+1);
  }
}

void Quad::printQuadTree()
{
  _printQuadTree(this->topLeftTree, 1);
  _printQuadTree(this->topRightTree, 1);
  _printQuadTree(this->botLeftTree, 1);
  _printQuadTree(this->botRightTree, 1);
};
