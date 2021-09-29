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
    flock->flocking(mt);

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
    // Init triangles.
    triangles.clear();
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
        // Judge the triangulation and flipping
        while (!S.empty())
        {
            vector<PVector> AB = S.top();
            S.pop();
            // Find two triangles which has AB as an edge.
            int index_ABC = -1;
            int index_ABD = -1;
            for (int i = 0; i < triangles.size(); i++)
            {
                if (triangles[i].isEdge(AB))
                {
                    index_ABC = i;
                    break;
                }
            }
            for (int i = 0; i < triangles.size(); i++)
            {
                if (triangles[i].isEdge(AB) && i != index_ABC)
                {
                    index_ABD = i;
                    break;
                }
            }
            // If there are not two triangles which has AB as an edge, flipping process will be skipped.
            if (index_ABD == -1)
            {
                continue;
            }
            // Two triangles that have a common edge, AB.
            Triangle ABC = triangles[index_ABC];
            Triangle ABD = triangles[index_ABD];
            PVector A = AB[0];
            PVector B = AB[1];
            PVector C = ABC.otherVertex(AB);
            PVector D = ABD.otherVertex(AB);
            // Make circumscribed circle of ABC.
            Circle ccircle(ABC);
            // Judge the edge AB whether or not it must be flipped.
            if (Dist(ccircle.center, D) < ccircle.radius)
            {
                // Flipping process.
                triangles.push_back(Triangle(A, C, D));
                triangles.push_back(Triangle(B, C, D));
                // Erase ABC and ABD from 'triangles'.
                for (auto itr = triangles.begin(); itr != triangles.end();)
                {
                    if (*itr == Triangle(A, B, C) || *itr == Triangle(A, B, D))
                    {
                        itr = triangles.erase(itr);
                    }
                    else
                    {
                        itr++;
                    }
                }
                // Push edges of a quad of ACBD into stack S.
                S.push(vector<PVector>{A, C});
                S.push(vector<PVector>{C, B});
                S.push(vector<PVector>{B, D});
                S.push(vector<PVector>{D, A});
            }
        }
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