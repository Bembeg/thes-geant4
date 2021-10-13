#include "G4Timer.hh"
#include "g4root.hh"

#include "OptRunAction.hh"

#include "G4Run.hh"


OptRunAction::OptRunAction()
 : G4UserRunAction(),
   fTimer(0)
{
  fTimer = new G4Timer;

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true);

  //analysisManager->CreateH1("Scint","Scintillation emission spectrum", 400, 300, 650);
  //analysisManager->CreateH1("WLSabsorb", "WLS Absorption spectrum", 400, 300, 650);
  //analysisManager->CreateH1("WLSemission", "WLS Emission spectrum", 400, 300, 650);
  analysisManager->CreateNtuple("HitsTuple", "HitsTuple");
  analysisManager->CreateNtupleIColumn("EventID");
  analysisManager->CreateNtupleIColumn("DetID");
  analysisManager->CreateNtupleDColumn("Time");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->FinishNtuple();
}



OptRunAction::~OptRunAction()
{
  delete fTimer;
  delete G4AnalysisManager::Instance();  
}


void OptRunAction::BeginOfRunAction(const G4Run* aRun)
{
  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "out";
  analysisManager->OpenFile(fileName);

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();
}


void OptRunAction::EndOfRunAction(const G4Run* aRun)
{
  fTimer->Stop();
  //G4cout << " " << *fTimer << G4endl;
  
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}