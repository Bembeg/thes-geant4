#include "AActionInitialization.hh"
#include "APrimaryGeneratorAction.hh"
#include "ARunAction.hh"
#include "AEventAction.hh"
#include "ASteppingAction.hh"
#include "ADetectorConstruction.hh"

AActionInitialization::AActionInitialization
                            (ADetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AActionInitialization::~AActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AActionInitialization::BuildForMaster() const
{
  SetUserAction(new ARunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AActionInitialization::Build() const
{
  SetUserAction(new APrimaryGeneratorAction);
  SetUserAction(new ARunAction);
  auto eventAction = new AEventAction;
  SetUserAction(eventAction);
  SetUserAction(new ASteppingAction(fDetConstruction,eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
