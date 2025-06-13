#include "ALPGunSteppingAction.hh"
#include "ALPGunDetectorConstruction.hh"

#include "G4RootAnalysisManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4INCLGlobals.hh"

ALPGunSteppingAction::ALPGunSteppingAction()
: G4UserSteppingAction(),
  fScoringVolume1(0),
  fScoringVolume2(0)
{}

ALPGunSteppingAction::~ALPGunSteppingAction()
{}

void ALPGunSteppingAction::UserSteppingAction(const G4Step* step)
{
  /*
  fScoringVolume1 = logicWorld;
  fScoringVolume2 = logicDet;
  */

  auto analysisManager = G4RootAnalysisManager::Instance();
  // get volume of the current step
  if (!fScoringVolume1) { 
    const ALPGunDetectorConstruction* detectorConstruction
      = static_cast<const ALPGunDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();   
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();   
  }
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  if (volume == fScoringVolume2) {
    G4Track* tr = step->GetTrack();
    auto x = tr->GetPosition()[0]/cm;
    auto y = tr->GetPosition()[1]/cm;
    auto z = tr->GetPosition()[2]/cm;
    auto ed = step->GetTotalEnergyDeposit()/MeV;
    auto t = tr->GetGlobalTime()/ns;
    analysisManager->FillH1(0,ed);
    analysisManager->FillH1(1,t);
    analysisManager->FillH2(0,z,t,ed);
    analysisManager->FillH3(0,x,y,z,ed);
  }
}

