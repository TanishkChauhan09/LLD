#include <iostream>
#include <string>

using namespace std;

// Component Interface: defines a common interface for Mario and all power-up decorators.
class Character {
public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {}  // Virtual destructor
};

// Concrete Component: Basic Mario character with no power-ups.
class Mario : public Character {
public:
    string getAbilities() const override {
        return "Mario";
    }
};

// Abstract Decorator: CharacterDecorator "is-a" Charatcer and "has-a" Character.
class CharacterDecorator : public Character {
protected:
    Character* character;  // Wrapped component
public:
    CharacterDecorator(Character* c){
        this->character = c;
    }

};

// Concrete Decorator: Height-Increasing Power-Up.
class HeightUp : public CharacterDecorator {
public:
    HeightUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with HeightUp";
    }
    
};