#include "ADetectorConstruction.hh"
#include "AActionInitialization.hh"


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


int main(int argc,char** argv)
{
  // Evaluate arguments
  //
  if ( argc > 7 ) {
    return 1;
  }
  
  G4String macro;
  G4String session;
//#ifdef G4MULTITHREADED
//  G4int nThreads = 0;
//#endif
  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
//#ifdef G4MULTITHREADED
//    else if ( G4String(argv[i]) == "-t" ) {
//      nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
//    }
//#endif
    else {
      return 1;
    }
  }  
  
  // Detect interactive mode (if no macro provided) and define UI session
  //
  G4UIExecutive* ui = nullptr;
  if ( ! macro.size() ) {
    ui = new G4UIExecutive(argc, argv, session);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

//#ifdef G4MULTITHREADED
//    auto runManager = new G4MTRunManager;
//    if ( nThreads > 0 ) {
//        runManager->SetNumberOfThreads(nThreads);
//    }
//#else
    auto runManager = new G4RunManager;
//#endif

  // Set mandatory initialization classes
  auto detConstruction = new ADetectorConstruction();
  runManager->SetUserInitialization(detConstruction);

  auto physicsList = new FTFP_BERT;
  runManager->SetUserInitialization(physicsList);
    
  auto actionInitialization = new AActionInitialization(detConstruction);
  runManager->SetUserInitialization(actionInitialization);
  
  // Initialize visualization
  auto visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
  if ( macro.size() ) {
        // batch mode
      G4String command = "/control/execute ";
      UImanager->ApplyCommand(command+macro);
    }
  else  {
        // interactive mode : define UI session
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        if (ui->IsGUI()) {
            UImanager->ApplyCommand("/control/execute gui.mac");
        }
        ui->SessionStart();
        delete ui;
  }

  delete visManager;
  delete runManager;
}


