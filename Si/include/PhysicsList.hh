#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"



class PhysicsList : public G4VUserPhysicsList
{
  public:

    PhysicsList();
    virtual ~PhysicsList();

  public:
    
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    virtual void SetCuts();

    //these methods Construct physics processes and register them
    void ConstructEM();
    void SetVerbose(G4int);
    
  private:

    static G4ThreadLocal G4int fVerboseLevel;
    
    
    
};

#endif /* PhysicsList_h */