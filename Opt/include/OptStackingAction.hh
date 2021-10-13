#ifndef OptStackingAction_H
#define OptStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"


class OptStackingAction : public G4UserStackingAction
{
  public:
    OptStackingAction();
    virtual ~OptStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fScintillationCounter;
    G4int fWLSCounter;
};


#endif