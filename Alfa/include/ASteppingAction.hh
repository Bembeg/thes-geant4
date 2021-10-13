#ifndef ASteppingAction_h
#define ASteppingAction_h 1

#include "G4UserSteppingAction.hh"

class ADetectorConstruction;
class AEventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in B4aEventAction.

class ASteppingAction : public G4UserSteppingAction
{
  public:
    ASteppingAction(const ADetectorConstruction* detectorConstruction,
                    AEventAction* eventAction);
    virtual ~ASteppingAction();

    virtual void UserSteppingAction(const G4Step* step);
    
  private:
    const ADetectorConstruction* fDetConstruction;
    AEventAction*  fEventAction;  
};

#endif
