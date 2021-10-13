#ifndef OptPhysicsList_h
#define OptPhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"


class G4Scintillation;
class G4OpAbsorption;
class G4OpBoundaryProcess;
class G4OpWLS;

class OptPhysicsList : public G4VUserPhysicsList
{
  public:

    OptPhysicsList();
    virtual ~OptPhysicsList();

  public:
    
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    virtual void SetCuts();

    void ConstructEM();
    void ConstructDecay(); 
    void ConstructOp();
    void SetVerbose(G4int);
    
  private:

    static G4ThreadLocal G4int fVerboseLevel;
    static G4ThreadLocal G4int fMaxNumPhotonStep;

    static G4ThreadLocal G4Scintillation* fScintillationProcess;
    static G4ThreadLocal G4OpAbsorption* fAbsorptionProcess;
    static G4ThreadLocal G4OpWLS* fWLSProcess;
    static G4ThreadLocal G4OpBoundaryProcess* fBoundaryProcess;
    
    
};

#endif