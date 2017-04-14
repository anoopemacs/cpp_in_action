#include <iostream>

class World
{
public:
    World(int id) : _identifier(id)
    {
	std::cout << "Hello from " << _identifier << "\n";
    }
    ~World()
    {
	std::cout << "Good by from " << _identifier << "\n";
    }
private:
    const int _identifier;	// the names of all private members are starting with underscore as a convention
};

World TheWorld(1);

int main()
{
    World myWorld(2);

    for(int i=3; i<6; ++i)
    {
	World aWorld(i);
    }

    World oneMoreWorld(6);
}
