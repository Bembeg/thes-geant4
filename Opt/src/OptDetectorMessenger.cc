#include "OptDetectorMessenger.hh"
#include "OptDetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"



OptDetectorMessenger::OptDetectorMessenger(OptDetectorConstruction* detector)
 : fOptDetector(detector)
{
  //Setup a command directory for detector controls with guidance
  fDetectorDir = new G4UIdirectory("/Opt/detector/");
  fDetectorDir->SetGuidance("Geometry control");
 
  //Various commands for modifying detector geometry
  fBlockXCmd = new G4UIcmdWithADoubleAndUnit("/Opt/detector/blockX", this);
  fBlockXCmd->SetGuidance("Set X-dimension of the scintillation block.");
  fBlockXCmd->SetDefaultUnit("mm");
  fBlockXCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fBlockXCmd->SetToBeBroadcasted(false);

  fBlockYCmd = new G4UIcmdWithADoubleAndUnit("/Opt/detector/blockY", this);
  fBlockYCmd->SetGuidance("Set Y-dimension of the scintillation block.");
  fBlockYCmd->SetDefaultUnit("mm");
  fBlockYCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fBlockYCmd->SetToBeBroadcasted(false);

  fBlockZCmd = new G4UIcmdWithADoubleAndUnit("/Opt/detector/blockZ", this);
  fBlockZCmd->SetGuidance("Set Z-dimension of the scintillation block.");
  fBlockZCmd->SetDefaultUnit("mm");
  fBlockZCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fBlockZCmd->SetToBeBroadcasted(false);

  fRInnerCmd = new G4UIcmdWithADoubleAndUnit("/Opt/detector/rInner", this);
  fRInnerCmd->SetGuidance("Set inner radius of the WLS fibre.");
  fRInnerCmd->SetDefaultUnit("mm");
  fRInnerCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fRInnerCmd->SetToBeBroadcasted(false);
  
  fROuterCmd = new G4UIcmdWithADoubleAndUnit("/Opt/detector/rOuter", this);
  fROuterCmd->SetGuidance("Set outer radius of the WLS fibre.");
  fROuterCmd->SetDefaultUnit("mm");
  fROuterCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fROuterCmd->SetToBeBroadcasted(false);

  fRTorCmd = new G4UIcmdWithADoubleAndUnit("/Opt/detector/rTor", this);
  fRTorCmd->SetGuidance("Set radius of the WLS torus.");
  fRTorCmd->SetDefaultUnit("mm");
  fRTorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fRTorCmd->SetToBeBroadcasted(false);
}  
  

OptDetectorMessenger::~OptDetectorMessenger()
{
  delete fBlockXCmd;
  delete fBlockYCmd;
  delete fBlockZCmd;
  delete fRInnerCmd;
  delete fROuterCmd;
  delete fRTorCmd;
}

void OptDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if(command==fBlockXCmd) {
    fOptDetector->SetBlockX(fBlockXCmd->GetNewDoubleValue(newValue));
  }

  if(command==fBlockYCmd) {
    fOptDetector->SetBlockY(fBlockYCmd->GetNewDoubleValue(newValue));
  }

  if(command==fBlockZCmd) {
    fOptDetector->SetBlockZ(fBlockZCmd->GetNewDoubleValue(newValue));
  }

  if(command==fRInnerCmd) {
    fOptDetector->SetRInner(fRInnerCmd->GetNewDoubleValue(newValue));
  }

  if(command==fROuterCmd) {
    fOptDetector->SetROuter(fROuterCmd->GetNewDoubleValue(newValue));
  }

  if(command==fRTorCmd) {
    fOptDetector->SetRTor(fRTorCmd->GetNewDoubleValue(newValue));
  }
}
