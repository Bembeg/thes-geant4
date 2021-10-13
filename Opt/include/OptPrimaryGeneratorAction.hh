#ifndef OptPrimaryGeneratorAction_h
#define OptPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class OptPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    OptPrimaryGeneratorAction();
    virtual ~OptPrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun* fParticleGun;

};

#endif