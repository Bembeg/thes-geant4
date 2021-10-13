#ifndef AActionInitialization_h
#define AActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ADetectorConstruction;

/// Action initialization class.

class AActionInitialization : public G4VUserActionInitialization
{
  public:
    AActionInitialization(ADetectorConstruction*);
    virtual ~AActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    ADetectorConstruction* fDetConstruction;
};

#endif

    
