#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"



ActionInitialization::ActionInitialization
                            (DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}


void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);

  std::array <G4double, DetectorConstruction::ArrayXYSize>* edepArray;
  RunAction* fRunAction = new RunAction;
  edepArray = &fRunAction->fEdep;
  SetUserAction(fRunAction);

  auto eventAction = new EventAction;
  SetUserAction(eventAction);
  SetUserAction(new SteppingAction(fDetConstruction,eventAction,edepArray));
}  

