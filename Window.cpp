#include "Window.h"

Window::Window(int width, int height, double limit, double mult) :
    m_limit(limit),
    m_mult(mult)
{
    initwindow(width, height, "Point Location", 0, 0, false, false);
}

Window::~Window()
{
    closegraph();
}

void Window::drawLines(vector<Edge> edges)
{
    for (const Edge& edge : edges)
        drawLine(edge);
}

void Window::drawLine(Edge edge)
{
    line(edge.p().x() * m_mult, m_limit - edge.p().y() * m_mult, edge.q().x() * m_mult, m_limit - edge.q().y() * m_mult);
    drawPoint(edge.p());
    drawPoint(edge.q());
}

void Window::setThickness(int thickness = NORM_WIDTH)
{
    linesettingstype settings;
    getlinesettings(&settings);
    setlinestyle(settings.linestyle, settings.upattern, thickness);
}

void Window::setColor(int color)
{
    setcolor(color);
}

void Window::clear()
{
    cleardevice();
}

void Window::drawPoint(Vertex p, int color)
{
    char pattern[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    int lastColor = getcolor();
    setfillpattern(pattern, color);
    setcolor(color);
    fillellipse(p.x() * m_mult, m_limit - p.y() * m_mult, POINT_RADIUS, POINT_RADIUS);
    setcolor(lastColor);
    setfillpattern(pattern, lastColor);
}

Vertex Window::getClick()
{
    int x = -1, y;
    while (x == -1)
        getmouseclick(WM_LBUTTONDOWN, x, y);

    double x_d = double(x) / m_mult;
    double y_d = (-double(y) + m_limit) / m_mult ;
    return { x_d, y_d };
}
