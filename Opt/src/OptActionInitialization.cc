#include "OptActionInitialization.hh"
#include "OptPrimaryGeneratorAction.hh"
#include "OptRunAction.hh"
#include "OptStackingAction.hh"
//#include "OptTrackingAction.hh"


OptActionInitialization::OptActionInitialization()
 : G4VUserActionInitialization()
{}


OptActionInitialization::~OptActionInitialization()
{}


void OptActionInitialization::BuildForMaster() const
{
  SetUserAction(new OptRunAction());
}


void OptActionInitialization::Build() const
{
  SetUserAction(new OptPrimaryGeneratorAction());
  SetUserAction(new OptRunAction());
  SetUserAction(new OptStackingAction());
  //SetUserAction(new OptTrackingAction());
}




