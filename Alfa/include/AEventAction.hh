#ifndef AEventAction_h
#define AEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// It defines data members to hold the track lengths
/// of charged particles in Absober
/// - fTrackLAbs
/// which are collected step by step via the function
/// - AddAbs()

class AEventAction : public G4UserEventAction
{
  public:
    AEventAction();
    virtual ~AEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void AddAbs(G4double de, G4double dl);
    
  private:
    G4double  fTrackLAbs;
    G4double  fEnergyAbs;
};

// inline functions

inline void AEventAction::AddAbs(G4double dl,G4double de) 
{ 
  fTrackLAbs += dl;
  fEnergyAbs += de;
}

       

#endif

    
