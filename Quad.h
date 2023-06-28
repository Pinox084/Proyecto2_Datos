#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
struct Point {
    	int x;
    	int y;
    	Point(int _x, int _y)
    	{
        	x = _x;
        	y = _y;
    	}
    	Point()
    	{
        	x = 0;
        	y = 0;
    	}
    	void setXY(int n, int k){
            x = n;
            y = k;
        }
	};

// The objects that we want stored in the quadtree
struct Node {
	Point pos;
    int data;
    Node(Point _pos, int _data)
    {
       	pos = _pos;
      	data = _data;
    }
    Node() 
	{ 
	data = 0; 
	}
};

class Quad{
	
private:
	//vector<Node*> lista;
	bool black=false;
	// Hold details of the boundary of this node
    Point topLeft;
    Point botRight;
    // Contains details of node
    Node* n;
    // Children of this tree
   	Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

public:

    Quad(Point topL, Point botR);
    //void leerCsv();
    void insert(Node*);
    Node* search(Point p);
    bool inBoundary(Point);
	void list(Quad* t);
	//vector<Node*> leerList();
	vector<Node*> _list();
	bool inRect(Point rectAInit, Point rectALimit, Point rectBInit, Point rectBLimit);
    int search_inRegion(Quad* current, Point init, Point limit, int caso);
    int countRegion(Point p, int d );
    int totalPoints();
    int totalNodes();
    int aggregateRegion(Point p, int d);
	void _printQuadTree(Quad* t, int indent);
	void printQuadTree();
	void getQuads(Quad t);
};
