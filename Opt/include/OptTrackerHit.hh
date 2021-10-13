#ifndef OptTrackerHit_h
#define OptTrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class OptTrackerHit : public G4VHit
{
  public:
    OptTrackerHit();
    OptTrackerHit(const OptTrackerHit&);
    virtual ~OptTrackerHit();

    // operators
    const OptTrackerHit& operator=(const OptTrackerHit&);
    G4int operator==(const OptTrackerHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetTrackID  (G4int track)      { fTrackID = track; };
    void SetEdep     (G4double de)      { fEdep = de; };
    void SetPos      (G4ThreeVector xyz){ fPos = xyz; };
    void SetGlobalTime (G4double time){ fGlobalTime = time;};

    // Get methods
    G4int GetTrackID() const      { return fTrackID; };
    G4double GetEdep() const      { return fEdep; };
    G4ThreeVector GetPos() const  { return fPos; };
    G4double GetGlobalTime() const { return fGlobalTime; };
  private:

      G4int         fTrackID;
      G4double      fEdep;
      G4ThreeVector fPos;
      G4double      fGlobalTime;
};


typedef G4THitsCollection<OptTrackerHit> OptTrackerHitsCollection;

extern G4ThreadLocal G4Allocator<OptTrackerHit>* OptTrackerHitAllocator;


inline void* OptTrackerHit::operator new(size_t)
{
  if(!OptTrackerHitAllocator)
      OptTrackerHitAllocator = new G4Allocator<OptTrackerHit>;
  return (void *) OptTrackerHitAllocator->MallocSingle();
}


inline void OptTrackerHit::operator delete(void *hit)
{
  OptTrackerHitAllocator->FreeSingle((OptTrackerHit*) hit);
}


#endif
