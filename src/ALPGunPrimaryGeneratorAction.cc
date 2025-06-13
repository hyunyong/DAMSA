#include "ALPGunPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

ALPGunPrimaryGeneratorAction::ALPGunPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fDir1(), fDir2(), fE1(0), fE2(0) 
{
    messenger = new G4GenericMessenger(this, "/ALPGun/", "ALP to two photons");
    messenger->DeclareProperty("pDirPhoton1", fDir1);
    fDir1.unit();
    messenger->DeclareProperty("pDirPhoton2", fDir2);
    fDir2.unit();
    messenger->DeclarePropertyWithUnit("EPhoton1", "GeV", fE1);
    messenger->DeclarePropertyWithUnit("EPhoton2", "GeV", fE2);

    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
      = particleTable->FindParticle(particleName="gamma");
    fParticleGun->SetParticleDefinition(particle);
}

ALPGunPrimaryGeneratorAction::~ALPGunPrimaryGeneratorAction()
{
    delete fParticleGun, fDir1, fDir2, fE1, fE2;
}

void ALPGunPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->SetParticleMomentumDirection(fDir1);
    fParticleGun->SetParticleEnergy(fE1);
    fParticleGun->GeneratePrimaryVertex(anEvent);
    fParticleGun->SetParticleMomentumDirection(fDir2);
    fParticleGun->SetParticleEnergy(fE2);
    fParticleGun->GeneratePrimaryVertex(anEvent);
    G4cout << "photon1 direction: " << fDir1 << ", E: " << fE1 << ", photon2 direction: " << fDir2 << ", E: " << fE2 << G4endl;
}
