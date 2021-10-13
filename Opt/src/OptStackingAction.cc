#include "OptStackingAction.hh"
#include "g4root.hh"
#include "OptTrackInfo.hh"
#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"


OptStackingAction::OptStackingAction()
  : G4UserStackingAction(),
    fScintillationCounter(0),
    fWLSCounter(0)
{}


OptStackingAction::~OptStackingAction()
{}


G4ClassificationOfNewTrack
OptStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  auto analysisManager = G4AnalysisManager::Instance();

  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
  {
    if(aTrack->GetParentID()>0) 
    {
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation") 
      {
        fScintillationCounter++;
        //analysisManager->FillH1(0, 1.240824e-3/(aTrack->GetTotalEnergy()));
      }
        
      if(aTrack->GetCreatorProcess()->GetProcessName() == "WLS") 
      {
        fWLSCounter++;
        OptTrackInfo* info = (OptTrackInfo*)(aTrack->GetUserInformation());
  
        //analysisManager->FillH1(1, 1.240824e-3/(info->GetOriginalEnergy()));      
        //analysisManager->FillH1(2, 1.240824e-3/(aTrack->GetTotalEnergy()));
      }
    }
  }
  return fUrgent;
}


void OptStackingAction::NewStage()
{
  G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4cout << "----------------------------------" << G4endl
         << "### Event " << eventID << ":" << G4endl
         << "Particles created by process: " << G4endl
         << ">> Scintillation : "
         << fScintillationCounter << G4endl
         << ">> WLS : "
         << fWLSCounter << G4endl; 
}


void OptStackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
  fWLSCounter = 0;
}

