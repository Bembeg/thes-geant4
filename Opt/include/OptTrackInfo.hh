#ifndef OptTrackInfoH
#define OptTrackInfoH_1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"
#include "G4VProcess.hh"

class OptTrackInfo : public G4VUserTrackInformation 
{
  public:
    OptTrackInfo();
    OptTrackInfo(const G4Track* aTrack);
    OptTrackInfo(const OptTrackInfo* aTrackInfo);
    virtual ~OptTrackInfo();
   
    inline void *operator new(size_t);
    inline void operator delete(void *aTrackInfo);
    inline int operator ==(const OptTrackInfo& right) const
    {return (this==&right);}

    void Print() const;

  private:
    G4double              originalEnergy;
    //const G4VProcess*           originalCreatProc;

  public:
    inline G4double GetOriginalEnergy() const {return originalEnergy;}
    //inline const G4VProcess* GetOriginalCreatProc() const {return originalCreatProc;}
};

extern G4Allocator<OptTrackInfo> aTrackInformationAllocator;

inline void* OptTrackInfo::operator new(size_t)
{ void* aTrackInfo;
  aTrackInfo = (void*)aTrackInformationAllocator.MallocSingle();
  return aTrackInfo;
}

inline void OptTrackInfo::operator delete(void *aTrackInfo)
{ aTrackInformationAllocator.FreeSingle((OptTrackInfo*)aTrackInfo);}

#endif