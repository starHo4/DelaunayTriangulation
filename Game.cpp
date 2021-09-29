#include "Game.hpp"

Game::Game()
{
    // Init.
    param = new Parameter();
    flock = new Flock();
    // Set a random seed of mt.
    mt.seed(param->RANDOM_SEED);
    // Init a flock
    for (int i = 0; i < param->N; i++)
    {
        Agent a;
        a.init(mt, param->FIELD_W, param->FIELD_H, param->s);
        flock->addAgent(a);
    }

    // SFML
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    window.create(sf::VideoMode(param->FIELD_W, param->FIELD_H), "", sf::Style::None, settings);
    window.setFramerateLimit(param->FPS);
}

void Game::Run()
{
    // Main Loop
    for (int t = 0; t < param->maxTimesteps; t++)
    {
        HandleInput();
        MainProcess();
        Render();
        if (!window.isOpen())
        {
            break;
        }
    }
}

void Game::MainProcess()
{
    // flock->flocking(mt);

    // Make a delaunay triangles.
    MakeDelaunay();
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Closed processing
        if ((event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        // if Mouse pressed
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
        }
    }
}

void Game::Render()
{
    window.clear();

    DrawFlock();
    DrawTri();

    window.display();
}

void Game::MakeDelaunay()
{
    // Vector of PVector (coordination of agents position)
    vector<PVector> Points(param->N);
    for (int i = 0; i < param->N; i++)
    {
        Points[i] = flock->getAgent(i).getPos();
    }
    // Make a huge inital triangle.
    double width = (double)param->FIELD_W;
    double height = (double)param->FIELD_H;
    PVector p1 = NewVec(width / 2, -width * sin(PI / 3));
    PVector p2 = NewVec(-height / tan(PI / 3), height);
    PVector p3 = NewVec(width + height / tan(PI / 3), height);
    Triangle init_tri(p1, p2, p3);
    triangles.push_back(init_tri);
    // Main processing of Delaunay triangulation
    for (int i = 0; i < Points.size(); i++)
    {
        PVector P = Points[i];
        // Find a triangle which includes the point P.
        int index_inP;
        for (int i = 0; i < triangles.size(); i++)
        {
            if (triangles[i].includePoint(P))
            {
                index_inP = i;
                break;
            }
        }
        Triangle tri_inP = triangles[index_inP];
        // Devide the triangle which includes P into three triangles for Delaunay triangulation.
        triangles.push_back(Triangle(tri_inP.Vertex[0], tri_inP.Vertex[1], P));
        triangles.push_back(Triangle(P, tri_inP.Vertex[1], tri_inP.Vertex[2]));
        triangles.push_back(Triangle(tri_inP.Vertex[0], P, tri_inP.Vertex[2]));
        triangles.erase(triangles.begin() + index_inP);
        // Temporary stack which have sides of tri_inP.
        stack<vector<PVector>> S;
        S.push(vector<PVector>{tri_inP.Vertex[0], tri_inP.Vertex[1]});
        S.push(vector<PVector>{tri_inP.Vertex[1], tri_inP.Vertex[2]});
        S.push(vector<PVector>{tri_inP.Vertex[2], tri_inP.Vertex[0]});


        // while ...

    }
    // Remove the initial huge triangle and the regarding triangles.
    auto itr = triangles.begin();
    while (itr != triangles.end())
    {
        if (itr->isVertex(p1) || itr->isVertex(p2) || itr->isVertex(p3))
        {
            // cout << itr->Vertex[0].x << ", " << itr->Vertex[0].y << endl;
            itr = triangles.erase(itr);
        }
        else
        {
            itr++;
        }
    }
}

void Game::DrawTri()
{
    for (int i = 0; i < triangles.size(); i++)
    {
        sf::ConvexShape triangle;
        triangle.setPointCount(triangles[i].getVertexNum());
        for (int j = 0; j < triangles[i].getVertexNum(); j++)
        {
            triangle.setPoint(j, sf::Vector2f(triangles[i].Vertex[j].x, triangles[i].Vertex[j].y));
        }
        triangle.setOutlineColor(sf::Color::Red);
        triangle.setOutlineThickness(1);
        triangle.setFillColor(sf::Color::Transparent);
        window.draw(triangle);
    }
}

void Game::DrawCircle()
{
    for (int i = 0; i < circles.size(); i++)
    {
        Circle ccircle = circles[i];
        if (ccircle.radius > 0)
        {
            double c_radius = ccircle.radius;
            PVector c_center = ccircle.center;
            sf::CircleShape circle(c_radius, c_radius * 10);
            circle.setPosition(c_center.x - c_radius, c_center.y - c_radius);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1.5);
            circle.setFillColor(sf::Color::Transparent);

            window.draw(circle);
        }
    }
}

void Game::DrawFlock()
{
    for (int i = 0; i < param->N; i++)
    {
        sf::ConvexShape shape;
        double r = 5;
        shape.setPointCount(3);
        shape.setOrigin(0, 0);
        shape.setPoint(0, sf::Vector2f(0, -r));
        shape.setPoint(1, sf::Vector2f(-r * cos(54 * PI / 180), r * sin(54 * PI / 180)));
        shape.setPoint(2, sf::Vector2f(r * cos(54 * PI / 180), r * sin(54 * PI / 180)));
        shape.setPosition(flock->getAgent(i).getPos().x, flock->getAgent(i).getPos().y);
        shape.rotate(flock->getAgent(i).getAngle() * 180 / PI);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(0.5);
        shape.setFillColor(sf::Color::Green);

        window.draw(shape);
    }
}