#ifndef OptDetectorMessenger_h
#define OptDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class OptDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;

class OptDetectorMessenger: public G4UImessenger
{
  public:

    OptDetectorMessenger(OptDetectorConstruction*);
    virtual ~OptDetectorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    OptDetectorConstruction*     fOptDetector;
    G4UIdirectory*               fDetectorDir;

    G4UIcmdWithADoubleAndUnit*   fBlockXCmd;
    G4UIcmdWithADoubleAndUnit*   fBlockYCmd;
    G4UIcmdWithADoubleAndUnit*   fBlockZCmd;
    G4UIcmdWithADoubleAndUnit*   fRTorCmd;
    G4UIcmdWithADoubleAndUnit*   fRInnerCmd;
    G4UIcmdWithADoubleAndUnit*   fROuterCmd;
};

#endif
