#include "ALPGunRunAction.hh"
#include "ALPGunPrimaryGeneratorAction.hh"
#include "ALPGunDetectorConstruction.hh"
#include "ALPGunRun.hh"

#include "G4RootAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include <math.h>

ALPGunRunAction::ALPGunRunAction()
: G4UserRunAction()
{
  auto analysisManager = G4RootAnalysisManager::Instance();
}

ALPGunRunAction::~ALPGunRunAction()
{}

G4Run* ALPGunRunAction::GenerateRun()
{
  return new ALPGunRun;
}

void ALPGunRunAction::BeginOfRunAction(const G4Run*)
{ 
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->OpenFile();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetVerboseLevel(1);

  const ALPGunDetectorConstruction* detectorConstruction
   = static_cast<const ALPGunDetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4double detL = detectorConstruction->GetDetectorLength()/cm;
  G4int detectorBin = G4int(detL)*10;

  analysisManager->CreateH1("d_1D_ed", "Energy Deposit [MeV]", 1000,0,100); 
  analysisManager->CreateH1("d_1D_t", "Energy Deposit time [ns]", 1000,0,1000);
  analysisManager->CreateH2("d_2D_edt", "Energy Deposit [MeV] by time [ns]", detectorBin,0,detL, 3000,0,3000);
  analysisManager->CreateH3("d_all_3D_ed","Energy Deposit [MeV]",120,-6,6,120,-6,6,detectorBin,0,detL);
}

void ALPGunRunAction::EndOfRunAction(const G4Run* run)
{
  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile(); 
}

