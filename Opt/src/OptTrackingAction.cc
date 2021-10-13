
#include "OptTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4TrackVector.hh"
#include "OptTrackInfo.hh"

OptTrackingAction::OptTrackingAction()
{;}

OptTrackingAction::~OptTrackingAction()
{;}

void OptTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
    OptTrackInfo* anInfo = new OptTrackInfo(aTrack);
    G4Track* theTrack = (G4Track*)aTrack;
    theTrack->SetUserInformation(anInfo);
}

void OptTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  if(secondaries)
  {
    OptTrackInfo* info = (OptTrackInfo*)(aTrack->GetUserInformation());
    size_t nSeco = secondaries->size();
    if(nSeco>0)
    {
      for(size_t i=0;i<nSeco;i++)
      { 
        OptTrackInfo* infoNew = new OptTrackInfo(info);
        (*secondaries)[i]->SetUserInformation(infoNew);
      }
    }
  }
}