#include "Tests.h"
#include "TopologicalNode.h"
#include "PointLocationSlabs.h"
#include "PointLocationTrapezoids.h"

void checkEdgeToVertex(Window win)
{
    while (true) {
        Vertex p;
        Edge e;
        cin >> e;
        win.clear();
        win.drawLine(e);
        cin >> p;
        win.drawPoint(p);

        cout << det3PointAndEdge(e, p) << endl;
    }
}

void checkMouseClick(Window win)
{
    win.drawPoint({ 5,3 });
    while (true)
    {
        Vertex p = win.getClick();
        win.drawPoint(p);
    }
}

void checkPlanarSubdivision(Window win)
{
    PlanarSubdivision s;
    while (true)
    {
        Edge u;
        cin >> u;
        win.clear();
        win.drawLine(u);
        win.drawLines(s.getEdges());
        s.addEdge(u);
    }
}

void checkCrossings(Window win)
{
    while (true)
    {
        Edge u;
        cin >> u;

        win.clear();
        win.drawLine(u);

        Edge v;
        cin >> v;

        win.drawLine(v);
        cout << "Are " << u << " and " << v << " crossing " << (areCrossing(u, v) ? "yes" : "no") << endl;
    }
}

void checkEdgeComp(Window win)
{
    while (true)
    {
        Edge u;
        cin >> u;

        win.clear();
        win.drawLine(u);

        Edge v;
        cin >> v;

        win.drawLine(v);
        cout << "is " << u << " below " << v << ((u < v) ? "yes" : "no") << endl;
    }
}

void checkEdgeSegment(Window win)
{
    while (true)
    {
        Edge u;
        cin >> u;

        win.clear();
        win.drawLine(u);

        Edge v;
        cin >> v;

        win.drawLine(v);

        auto segment = getCommonSegment(u, v);
        cout << "u and v common segment: " << segment.first << " " << segment.second << endl;
    }
}

void checkTopologicalSort(Window& win, vector<Edge> edges)
{
    edges = topologicalSortBuild<Edge>(edges, compareEdges);

    int index = 0;
    for (Edge edge : edges)
    {
        win.drawLine(edge);
        win.getClick();
    }
}

void checkTrapezoidPointLocation(vector<Edge> edges)
{
    shared_ptr<PointLocation> pointLocation;

    int size = 0;
    for (unsigned int seed = 1; seed <= 1; ++seed) {
        pointLocation = nullptr;
        cout << "seed: " << seed << endl;
        pointLocation = make_shared<PointLocationTrapezoids>(edges, seed);
        if (size != 0 && dynamic_cast<PointLocationTrapezoids*>(pointLocation.get())->getSize() != size)
            cout << "this is a problem";
        
        size = dynamic_cast<PointLocationTrapezoids*>(pointLocation.get())->getSize();
    }
}
