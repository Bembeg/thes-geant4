#ifndef OptTrackerSD_h
#define OptTrackerSD_h 1

#include "G4VSensitiveDetector.hh"

#include "OptTrackerHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class OptTrackerSD : public G4VSensitiveDetector
{
  public:
    OptTrackerSD(const G4String& name, 
                const G4String& hitsCollectionName);
    virtual ~OptTrackerSD();
  
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    OptTrackerHitsCollection* fHitsCollection;
};  

#endif
