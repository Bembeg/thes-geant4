#include "EventAction.hh"
#include "RunAction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>



EventAction::EventAction()
 : G4UserEventAction()
{}


EventAction::~EventAction()
{}


void EventAction::BeginOfEventAction(const G4Event* event)
{}


void EventAction::EndOfEventAction(const G4Event* event)
{

  /*auto analysisManager = G4AnalysisManager::Instance();

  for (int i=0; i<5; i++)
  {
    analysisManager->FillH1(i, edephists[i]);
    analysisManager->FillNtupleDColumn(i, edephists[i]);
    analysisManager->AddNtupleRow();
  }*/

}


