#include "OptTrackerSD.hh"
#include "OptTrackerHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "g4root.hh"
#include "G4RunManager.hh"


OptTrackerSD::OptTrackerSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}


OptTrackerSD::~OptTrackerSD() 
{}


void OptTrackerSD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection = new OptTrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}


G4bool OptTrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* history)
{  
  G4double edep = aStep->GetTotalEnergyDeposit();

  if (edep==0.) return false;

  OptTrackerHit* newHit = new OptTrackerHit();

  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetEdep(edep);
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
  newHit->SetGlobalTime(aStep->GetTrack()->GetGlobalTime());
  fHitsCollection->insert(newHit);

  return true;
}


void OptTrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  G4int nofHits = fHitsCollection->entries();
  if (nofHits!=0)
  {
    G4String detName = fHitsCollection->GetName();
    G4int detID;
    if (detName[0]=='B') detID = 0;
    else if (detName[0]=='T') detID = 1;
    else if (detName[0]=='L') detID = 2;
    else if (detName[0]=='R') detID = 3;

    G4cout << detName << " summary:" << G4endl;
    for ( G4int i=nofHits-1; i>=0; i-- )
    {
      G4cout << ">> ";
      (*fHitsCollection)[i]->Print();

      man->FillNtupleIColumn(0, evID);  //eventID
      man->FillNtupleIColumn(1, detID);
      man->FillNtupleDColumn(2, (*fHitsCollection)[i]->GetGlobalTime());
      man->FillNtupleDColumn(3, (*fHitsCollection)[i]->GetEdep());
      man->AddNtupleRow();
    } 
  }
  G4cout << "----------------------------------" << G4endl; 
}
