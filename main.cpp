#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Window.h"
#include "Slab.h"
#include "PointLocationSlabs.h"
#include "PointLocationTrapezoids.h"
#include "PlanarSubdivision.h"
#include "Face.h"
#include <limits>
#include "TopologicalNode.h"
#include <chrono>
#undef max

void input1(vector<Edge>& edges, vector<shared_ptr<Face>>& faces);
void input2(vector<Edge>& edges, vector<shared_ptr<Face>>& faces);
void input3(vector<Edge>& edges, vector<shared_ptr<Face>>& faces);
void runPointLocation(shared_ptr<PointLocation> pointLocation, Window win, vector<Edge> edges);


using std::endl;
using std::cout;
using std::cin;

int main()
{
    vector<Edge> edges;
    vector<shared_ptr<Face>> faces;
    input3(edges, faces);
    shared_ptr<PointLocation> pointLocation;

    //auto start = std::chrono::high_resolution_clock::now();
    //pointLocation = make_shared<PointLocationTrapezoids>(edges);
    pointLocation = make_shared<PointLocationTrapezoids>(edges);
    //cout << std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() << endl;
    Window win(DEFAULT_WID, DEFAULT_HEI, DEFAULT_LIMIT*3/4, 50);

    //checkEdgeComp(win);
    //checkEdgeToVertex(win);
    //checkCrossings(win);
    //checkPlanarSubdivision(win);
    //checkMouseClick(win);
    //checkTopologicalSort(win, edges);
    runPointLocation(pointLocation, win, edges);

    return EXIT_SUCCESS;
}

void runPointLocation(shared_ptr<PointLocation> pointLocation, Window win, vector<Edge> edges)
{
    Vertex p;
    win.drawLines(edges);
    cout << "click somewhere on the screen" << endl;
    while (true)
    {
        try 
        {
            p = win.getClick();
            //cin >> p;
        }
        catch(exception e)
        {
            cout << "window was closed" << endl;
            return;
        }

        cout << p << endl;

        shared_ptr<const Face> face = pointLocation->query(p);
        win.clear();
        if (face == nullptr)
            cout << "Infinity face" << endl;
        else
        {
            win.setThickness(THICK_WIDTH);
            win.drawLines(face->getEdges());
            win.setThickness(NORM_WIDTH);
            
            cout << *face << endl;
        }
        win.drawLines(edges);
        win.drawPoint(p, RED);
    }
}

void input1(vector<Edge>& edges, vector<shared_ptr<Face>>& faces) 
{
    edges.push_back({ {1, 5}, {2, 4} });
    edges.push_back({ {2, 4}, {3, 2} });
    edges.push_back({ {3, 2}, {4, 1} });
    edges.push_back({ {4, 1}, {7, 1} });
    edges.push_back({ {2, 4}, {5, 3} });
    edges.push_back({ {2, 4}, {6, 5} });
    edges.push_back({ {6, 5}, {8, 4} });
    edges.push_back({ {3, 2}, {5, 3} });
    edges.push_back({ {5, 3}, {8, 4} });
    edges.push_back({ {7, 1}, {8, 4} });
    
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[1], edges[4], edges[7] })));
    edges[1].setAboveFace(faces[0]);
    edges[7].setAboveFace(faces[0]);

    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[4], edges[5], edges[6], edges[8] })));
    edges[4].setAboveFace(faces[1]);
    edges[8].setAboveFace(faces[1]);
    

    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[2], edges[3], edges[7], edges[8], edges[9] })));
    edges[2].setAboveFace(faces[2]);
    edges[3].setAboveFace(faces[2]);
    edges[9].setAboveFace(faces[2]);
}

void input2(vector<Edge>& edges, vector<shared_ptr<Face>>& faces)
{

    edges.push_back({ {3, 5}, {5, 8} });
    edges.push_back({ {4, 4}, {5, 8} });
    edges.push_back({ {4, 4}, {2, 4} });
    edges.push_back({ {2, 4}, {3, 5} });
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[0], edges[1], edges[2], edges[3] })));
    edges[1].setAboveFace(faces[0]);
    edges[2].setAboveFace(faces[0]);
    edges[3].setAboveFace(faces[0]);

    edges.push_back({ {5, 8}, {6, 5} });
    edges.push_back({ {4, 4}, {6, 5} });
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[1], edges[4], edges[5]})));
    edges[5].setAboveFace(faces[1]);

    edges.push_back({ {4, 4}, {5, 3} });
    edges.push_back({ {7, 2}, {5, 3} });
    edges.push_back({ {5, 1}, {7, 2} });
    edges.push_back({ {1, 1}, {5, 1} });
    edges.push_back({ {1, 1}, {4, 4} });
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[6], edges[7], edges[8], edges[9], edges[10] })));
    edges[8].setAboveFace(faces[2]);
    edges[9].setAboveFace(faces[2]);

    edges.push_back({ {3, 5}, {1, 5} });
    edges.push_back({ {1, 5}, {1, 1} });
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[2], edges[3], edges[10], edges[11], edges[12] })));
    edges[10].setAboveFace(faces[3]);

    edges.push_back({ {3, 5}, {1, 7} });
    edges.push_back({ {6, 5}, {7, 6} });
}

void input3(vector<Edge>& edges, vector<shared_ptr<Face>>& faces)
{
    edges.push_back({ {1, 5}, {4, 1} });//0
    edges.push_back({ {4, 1}, {4, 4} });//1
    edges.push_back({ {4, 4}, {6, 5} });//2
    edges.push_back({ {6, 5}, {3, 6} });//3
    edges.push_back({ {3, 6}, {1, 8} });//4
    edges.push_back({ {1, 8}, {1, 5} });//5
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[0], edges[1], edges[2], edges[3], edges[4], edges[5] })));
    edges[0].setAboveFace(faces[0]);
    edges[2].setAboveFace(faces[0]);

    edges.push_back({ {4, 1}, {7, 1} });//6
    edges.push_back({ {7, 1}, {9, 3} });//7
    edges.push_back({ {9, 3}, {6, 5} });//8
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[1], edges[2], edges[6], edges[7], edges[8] })));
    edges[6].setAboveFace(faces[1]);
    edges[7].setAboveFace(faces[1]);

    edges.push_back({ {7, 1}, {11, 2} });//9
    edges.push_back({ {11, 2}, {9, 3} });//10
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[7], edges[9], edges[10] })));
    edges[9].setAboveFace(faces[2]);

    edges.push_back({ {11, 2}, {12, 4} });//11
    edges.push_back({ {12, 4}, {9, 3} });//12
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[10], edges[11], edges[12] })));
    edges[10].setAboveFace(faces[3]);
    edges[11].setAboveFace(faces[3]);

    edges.push_back({ {12, 4}, {9, 6} });//13
    edges.push_back({ {9, 6}, {6, 5} });//14
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[8], edges[12], edges[13], edges[14] })));
    edges[8].setAboveFace(faces[4]);
    edges[12].setAboveFace(faces[4]);


    edges.push_back({ {9, 6}, {7, 8} });//15
    edges.push_back({ {7, 8}, {3, 6} });//16
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[3], edges[14], edges[15], edges[16] })));
    edges[3].setAboveFace(faces[5]);
    edges[14].setAboveFace(faces[5]);

    edges.push_back({ {1, 8}, {7, 8} });//17
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[4], edges[16], edges[17] })));
    edges[4].setAboveFace(faces[6]);
    edges[16].setAboveFace(faces[6]);

    edges.push_back({ {1, 8}, {4, 10} });//18
    edges.push_back({ {4, 10}, {7, 8} });//19
    faces.push_back(std::make_shared<Face>(vector<Edge>({ edges[17], edges[18], edges[19] })));
    edges[17].setAboveFace(faces[7]);

}

