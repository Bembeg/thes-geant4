#include "OptPrimaryGeneratorAction.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

OptPrimaryGeneratorAction::OptPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), 
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("proton");  //opticalphoton, mu+
  fParticleGun->SetParticleDefinition(particle);
 
  //test do detektoru zprava
  //fParticleGun->SetParticlePosition(G4ThreeVector(20*cm,-2.*cm,0*mm));  
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.,0.,0.));


  //test vlakna
  //fParticleGun->SetParticlePosition(G4ThreeVector(-2.2*cm,-2.2*cm,1.2*cm));
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1 ,1,0));


  //normal usporadani
  fParticleGun->SetParticlePosition(G4ThreeVector(0*cm,-0*cm,-0.8*m));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

  fParticleGun->SetParticleEnergy(1*GeV); //120GeV pro normal, 2.91eV pro test WLS
}

OptPrimaryGeneratorAction::~OptPrimaryGeneratorAction()
{
  delete fParticleGun; 
}


void OptPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

