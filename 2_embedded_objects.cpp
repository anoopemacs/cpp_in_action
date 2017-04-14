// Mn: Anoop defined object World has-a Anoop defined object of type Matter
// Embedding => HAS-A relationships

#include <iostream>

class Matter
{
public:
    Matter (int id) : _identifier(id)
    {
	std::cout << " Matter in " << _identifier << " created\n";
    }
    ~Matter () {
	std::cout << " Matter in " << _identifier << " annihilated\n";
    }
private:
    const int _identifier;
};

class World
{
public:
    // counter intuitive: the order in the initializer list preamble has nothing to do with the order in which these const variables are initialized
    // The order follows the order in which they are declared in the class definition in the private: part of class definition

    // Data members are initialized in the order in which they are embedded in the classs definition.
    // Destruction follow: the ones constructed first will be destroyed last, Mn: like stack
    
    World(int id) :_matter (_identifier),  _identifier (id)
    {
	// initializing embeddings, initializer list is in the reverse order initentionally to emphasize
	// the fact that order in the initializer list is of no significance
	std::cout << "Hello from " << _identifier << "\n";
    }
    
    ~World()
    {
        std::cout << "Good by from " << _identifier << "\n";
    }
    
private:
    const int _identifier;      // the names of all private members are starting with underscore as a convention
    const Matter _matter;	// This is an embedded object of type Matter, in C++ user created objects are treated the same manner as built in types, beautiful
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
