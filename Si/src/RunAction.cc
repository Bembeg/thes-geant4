#include "RunAction.hh"
#include "Analysis.hh"

#include <string>
#include <iostream>
#include <fstream>

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"
#include "G4EmCalculator.hh"


RunAction::RunAction()
 : G4UserRunAction()
{ 
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;



  /*analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);



  analysisManager->CreateNtuple("Blocks", "Energy deposits in blocks");

  for (int i=0; i<10; i++)
  {
      std::string histname = "Block";
      histname.append(std::to_string(i));
      analysisManager->CreateH1(histname, "hits", 100, 0., 10.*MeV);
      analysisManager->CreateNtupleDColumn(histname);
  }

  analysisManager->CreateH1("Labs","trackL in absorber", 100, 0., 1*m);
  analysisManager->CreateH1("Eabs","Edep in absorber", 100, 0., 800*MeV);*/


  /*analysisManager->CreateNtupleDColumn("Labs");
  analysisManager->CreateNtupleDColumn("Eabs");
  analysisManager->FinishNtuple();*/
}


RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}


void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
  auto analysisManager = G4AnalysisManager::Instance();


  for ( auto& edep : fEdep )
  {
    edep = 0.;
  }



  G4String fileName = "Si";
  analysisManager->OpenFile(fileName);


}


void RunAction::EndOfRunAction(const G4Run* run)
{
  auto analysisManager = G4AnalysisManager::Instance();

  std::ofstream outfile;
  std::string filename = "out"+std::to_string(DetectorConstruction::ArrayXSize)+"x"+std::to_string(DetectorConstruction::ArrayYSize)+".txt";
  outfile.open(filename);

  G4int nonempty = 0;

  for(G4int i=0; i<DetectorConstruction::ArrayXYSize; i++)
  {
    if (i%DetectorConstruction::ArrayXSize==0  && i!=0)
    {
      outfile << std::endl;
    }
    outfile << fEdep[i]*1000 << " "; 
   


    if (fEdep[i]!=0)
    {
      nonempty++;
      //G4cout << G4BestUnit(fEdep[i], "Energy") << G4endl;
    }

    
  }
  G4float ratio = (G4float)nonempty/(G4float)DetectorConstruction::ArrayXYSize;

  G4cout << "" << G4endl
         << "***************************************" << G4endl
         << "***************************************" << G4endl
         << "***************************************" << G4endl << "" << G4endl

         << "Source emitted " << run->GetNumberOfEvent() << " particles." << G4endl

         << "We have " << ratio*100 << "% (" << nonempty << "/" << DetectorConstruction::ArrayXYSize <<
             ") pixels with non-zero energy deposits." << G4endl << "" << G4endl

         << "***************************************" << G4endl
         << "***************************************" << G4endl
         << "***************************************" << G4endl
         << "" << G4endl;

  outfile.close();
  analysisManager->Write();
  analysisManager->CloseFile();
}

