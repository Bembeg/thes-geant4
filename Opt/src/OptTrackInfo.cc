
#include "OptTrackInfo.hh"
#include "G4ios.hh"


G4Allocator<OptTrackInfo> aTrackInformationAllocator;

OptTrackInfo::OptTrackInfo()
{
    originalEnergy = 0.;
    //originalCreatProc = 0;
}

OptTrackInfo::OptTrackInfo(const G4Track* aTrack)
{
    originalEnergy = aTrack->GetTotalEnergy();
    //originalCreatProc = aTrack->GetCreatorProcess();
}

OptTrackInfo::OptTrackInfo(const OptTrackInfo* aTrackInfo)
{
    originalEnergy = aTrackInfo->originalEnergy;
    //originalCreatProc = aTrackInfo->originalCreatProc;
}

OptTrackInfo::~OptTrackInfo(){;}

void OptTrackInfo::Print() const
{}