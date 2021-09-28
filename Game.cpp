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
    while (window.isOpen())
    {
        HandleInput();
        MainProcess();
        Render();
    }
}

void Game::MainProcess()
{
    flock->flocking(mt);

    // Make a delaunay triangles.
    // MakeDelaunay();
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
    
}

// vector<PVector> Points(param->N);
//     for (int i = 0; i < param->N; i++)
//     {
//         Points[i] = flock->getAgent(i).getPos();
//     }
//     // Make a huge triangle which includes all points.
//     double width = param->FIELD_W;
//     double height = param->FIELD_H;
//     PVector v1 = NewVec(width / 2, -width * sin(PI / 3));
//     PVector v2 = NewVec(-height / tan(PI / 3), height);
//     PVector v3 = NewVec(width + height / tan(PI / 3), height);
//     Triangle init_tri(v1, v2, v3);
//     // Push back a huge triangle into "triangles"
//     triangles.push_back(init_tri);
//     // Main Loop of Delaunay Algorithm.
//     for(int n = 0; n < Points.size(); n+;)
//     {
//         int index_inP;
//         // Find a triangle which includes the point P.
//         for (int i = 0; i < triangles.size(); i++)
//         {
//             Circle tmp_Circle;
//             tmp_Circle.CalcCircle(triangles[i]);
//             if (Dist(tmp_Circle.center, P) <= tmp_Circle.radius)
//             {
//                 index_inP = i;
//                 break;
//             }
//         }
//         Triangle tmp_tri = triangles[index_inP];
//         triangles.push_back(Triangle(tmp_tri.Vertex[0], tmp_tri.Vertex[1], P));
//         triangles.push_back(Triangle(tmp_tri.Vertex[0], P, tmp_tri.Vertex[2]));
//         triangles.push_back(Triangle(P, tmp_tri.Vertex[1], tmp_tri.Vertex[2]));
//         triangles.erase(triangles.begin() + index_inP);
//         stack<vector<PVector>> S;
//         S.push(vector<PVector>{tmp_tri.Vertex[0], tmp_tri.Vertex[1]});
//         S.push(vector<PVector>{tmp_tri.Vertex[1], tmp_tri.Vertex[2]});
//         S.push(vector<PVector>{tmp_tri.Vertex[2], tmp_tri.Vertex[0]});
//         while (!S.empty())
//         {
//             vector<PVector> AB = S.top();
//             S.pop();
//             PVector A = AB[0];
//             PVector B = AB[1];
//             int index_tri1 = -1;
//             int index_tri2 = -1;
//             for (int i = 0; i < triangles.size(); i++)
//             {

//                 if (triangles[i].includeEdge(AB))
//                 {
//                     index_tri1 = i;
//                     break;
//                 }
//             }
//             for (int i = 0; i < triangles.size(); i++)
//             {

//                 if (triangles[i].includeEdge(AB) && i != index_tri1)
//                 {
//                     index_tri2 = i;
//                     break;
//                 }
//             }

//             if (index_tri2 == -1)
//             {
//                 continue;
//             }

//             Triangle tri_ABC = triangles[index_tri1];
//             Triangle tri_ABD = triangles[index_tri2];
//             Circle circle_ABC;
//             circle_ABC.CalcCircle(tri_ABC);
//             PVector C = tri_ABC.findVertex(A, B);
//             PVector D = tri_ABD.findVertex(A, B);
//             if (Dist(circle_ABC.center, D) <= circle_ABC.radius)
//             {
//                 // Flipping.
//                 triangles.push_back(Triangle(A, C, D));
//                 triangles.push_back(Triangle(B, C, D));
//                 triangles.erase(triangles.begin() + index_tri1);
//                 triangles.erase(triangles.begin() + index_tri2);

//                 S.push(vector<PVector>{A, C});
//                 S.push(vector<PVector>{A, D});
//                 S.push(vector<PVector>{B, C});
//                 S.push(vector<PVector>{B, D});
//             }
//         }
//     }

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
    // if (ccircle->radius > 0)
    // {
    //     double c_radius = ccircle->radius;
    //     PVector c_center = ccircle->center;
    //     sf::CircleShape circle(c_radius, c_radius * 10);
    //     circle.setPosition(c_center.x - c_radius, c_center.y - c_radius);
    //     circle.setOutlineColor(sf::Color::Red);
    //     circle.setOutlineThickness(1.5);
    //     circle.setFillColor(sf::Color::Transparent);

    //     window.draw(circle);
    // }
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