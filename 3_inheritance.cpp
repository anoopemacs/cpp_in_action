// IS-A relationships
// Star is a CelestialBody

#include <iostream>

class CelestialBody ()
{
 public:
    CelestialBody (double mass) : _mass (mass)
    {
	std::cout << "Creating celestial body of mass " << _mass << "\n";
    }
    ~CelestialBody ()
    {
	std::cout << "Destroying celestial body of mass " << _mass << "\n";
    }
 private:
    const double _mass;
};

class Star: public CelestialBody
// Star is a CelestialBody, inheritance
// why public CelestialBody:

{ 
public:
    // order of construction during inheritance is very important
    // first the base class if fully constructed , here that is CelestialBody
    // second the derived class is constructed, here it is Star.

    // construction of derived class follows the usual order of:
    // first the embeddings: here they are _brightness, visualize them as being done when preamble or the initializer list is executed
    // second the code in the constructor
    
    Star (double mass, double brightness) : CelestialBody (mass), _brightness (brightness)
    {
	std::cout << "Creating a star of brightness " << _brightness << "\n";
    }

    // Destructor order:
    // first the derived class is destroyed: here it is Star
    // second the base class is destroyed: here it is CelestialBody
    
    ~Star ()
    {
	std::cout << "Destroying a star of brightness " << _brightness << "\n";
    }
    
private:
    const double _brightness;
};

int main () 
{
    
}
