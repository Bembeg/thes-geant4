#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <array>
#include "DetectorConstruction.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(const DetectorConstruction* detectorConstruction, EventAction* eventAction,
                   std::array<G4double,DetectorConstruction::ArrayXYSize> *edepArray) ;
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step* step);

  private:
    const DetectorConstruction* fDetConstruction;
    EventAction*  fEventAction;
    std::array<G4double,DetectorConstruction::ArrayXYSize>* fEdep;
};

#endif
