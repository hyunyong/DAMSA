//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Analysis.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4INCLGlobals.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0),
  fScoringVolume4(0),
  fScoringVolume5(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  /*
  fScoringVolume1 = logicWorld;
  fScoringVolume2 = logicTarget;
  fScoringVolume3 = logicDet;
  fScoringVolume4 = logicDetCell;      
  */

  auto analysisManager = G4RootAnalysisManager::Instance();
  // get volume of the current step
  if (!fScoringVolume1) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();   
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();   
    fScoringVolume3 = detectorConstruction->GetScoringVolume3();   
    fScoringVolume4 = detectorConstruction->GetScoringVolume4();   
    fScoringVolume5 = detectorConstruction->GetScoringVolume5();   
  }
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume

  G4Track* tr = step->GetTrack();
  if (volume == fScoringVolume2) {
    auto x = tr->GetPosition()[0]/cm;
    auto y = tr->GetPosition()[1]/cm;
    auto z = tr->GetPosition()[2]/cm;
    auto theta = tr->GetMomentumDirection().theta();
    auto e = tr->GetKineticEnergy()/GeV;
    auto ed = step->GetTotalEnergyDeposit()/MeV;
    analysisManager->FillH2(3, z, y,ed);
    if (tr->GetParticleDefinition()->GetPDGEncoding() == 11) {
      analysisManager->FillH2(0, e, theta);
    }
    if (tr->GetParticleDefinition()->GetPDGEncoding() == -11) {
      analysisManager->FillH2(1, e, theta);
    }
    if (tr->GetParticleDefinition()->GetPDGEncoding() == 22) {
      analysisManager->FillH2(2, e, theta);
      analysisManager->FillH1(1, z);
    }
    if (tr->GetParticleDefinition()->GetPDGEncoding() == 2112) {
      analysisManager->FillH1(2, z);
    }	    
    auto postVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if (postVolume != fScoringVolume2) {
      //auto r = sqrt(x*x + y*y);
      if (tr->GetParticleDefinition()->GetPDGEncoding() == 11) analysisManager->FillH2(11,e,theta);
      if (tr->GetParticleDefinition()->GetPDGEncoding() == -11) analysisManager->FillH2(12,e,theta);
      if (tr->GetParticleDefinition()->GetPDGEncoding() == 22) analysisManager->FillH2(13,e,theta);
      if (tr->GetParticleDefinition()->GetPDGEncoding() == 2112) analysisManager->FillH2(14,e,theta);
      if (tr->GetParticleDefinition()->GetPDGEncoding() == 2212) analysisManager->FillH2(15,e,theta);
    }
  }
  if (volume == fScoringVolume3) {
    auto x = tr->GetPosition()[0]/cm;
    auto y = tr->GetPosition()[1]/cm;
    auto z = tr->GetPosition()[2]/cm;
    auto ed = step->GetTotalEnergyDeposit()/MeV;
    auto t = tr->GetGlobalTime()/ns;
    analysisManager->FillH1(0,ed);
    analysisManager->FillH2(4,z,y,ed);
    analysisManager->FillH2(5, z ,t, ed);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

