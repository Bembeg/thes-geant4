#include "globals.hh"
#include "G4Track.hh"
#include "G4UserTrackingAction.hh"

class OptTrackingAction : public G4UserTrackingAction
{
    public:
        OptTrackingAction();
        virtual ~OptTrackingAction();

    public: 
        void PreUserTrackingAction(const G4Track*);
        void PostUserTrackingAction(const G4Track*);
};
