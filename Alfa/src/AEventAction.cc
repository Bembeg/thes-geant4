#include "AEventAction.hh"
#include "ARunAction.hh"
#include "AAnalysis.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>



AEventAction::AEventAction()
 : G4UserEventAction(),
   fTrackLAbs(0.),
   fEnergyAbs(0.)
{
}


AEventAction::~AEventAction()
{
}


void AEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  // initialisation per event
  fTrackLAbs = 0.;
  fEnergyAbs = 0.;
}


void AEventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, fTrackLAbs);
  analysisManager->FillH1(1, 8.*MeV-fEnergyAbs);
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(0, fTrackLAbs);
  analysisManager->FillNtupleDColumn(1, 8.*MeV-fEnergyAbs);
  analysisManager->AddNtupleRow();  
  
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) 
  {
    G4cout << "---> End of event: " << eventID << G4endl;     

    G4cout
       << "      Absorber: total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLAbs,"Length")
       << "   Absorber: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyAbs,"Energy")
       << G4endl;
       
  }
}  


