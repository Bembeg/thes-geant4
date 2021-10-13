#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(
                      const DetectorConstruction* detectorConstruction,
                      EventAction* eventAction,
                      std::array<G4double,DetectorConstruction::ArrayXYSize> *edepArray
                      )
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction),
    fEdep(edepArray)
{}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  G4int volumeindex = volume->GetCopyNo();


  //mu- PDGCode 13; pi+ PDGCode 211
  if(step->GetTrack()->GetDynamicParticle()->GetPDGcode() == 211){
    auto edep = step->GetTotalEnergyDeposit();
    
      if(1000 <= volumeindex && volumeindex < 1000+DetectorConstruction::ArrayXYSize)
      {
        fEdep->at(volumeindex-1000)+=edep;
      }
    

  }
  
}


