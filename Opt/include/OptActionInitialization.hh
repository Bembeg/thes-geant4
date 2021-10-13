#ifndef OptActionInitialization_h
#define OptActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class OptDetectorConstruction;

class OptActionInitialization : public G4VUserActionInitialization
{
  public:
    OptActionInitialization();
    virtual ~OptActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

#endif