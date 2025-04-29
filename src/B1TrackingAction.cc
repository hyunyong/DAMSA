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

#include "B1TrackingAction.hh"
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

B1TrackingAction::B1TrackingAction(B1EventAction* eventAction)
: G4UserTrackingAction(),
  fEventAction(eventAction),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0),
  fScoringVolume4(0),
  fScoringVolume5(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1TrackingAction::~B1TrackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1TrackingAction::PreUserTrackingAction(const G4Track* tr)
{
 
 
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
    = tr->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  auto analysisManager = G4RootAnalysisManager::Instance();
  if (volume == fScoringVolume2) {
    auto x = tr->GetPosition()[0]/cm;
    auto y = tr->GetPosition()[1]/cm;
    auto z = tr->GetPosition()[2]/cm;
    auto theta = tr->GetMomentumDirection().theta();
    auto e = tr->GetKineticEnergy()/GeV;
    auto pdgID = tr->GetParticleDefinition()->GetPDGEncoding();
    if (pdgID == 11) {
      analysisManager->FillH2(0, e, theta);
      analysisManager->FillH2(6, z, e);
    }
    if (pdgID == -11) {
      analysisManager->FillH2(1, e, theta);
      analysisManager->FillH2(7, z, e);
    }
    if (pdgID == 22) {
      analysisManager->FillH2(2, e, theta);
      analysisManager->FillH1(1, z);
      analysisManager->FillH2(8, z, e);
    }
    if (pdgID == 2112) {
      analysisManager->FillH1(2, z);
      analysisManager->FillH2(9, z, e);
    }  
    if (pdgID == 2212) {
      analysisManager->FillH2(10, z, e);
    }
    /*if (pdgID != 11 and pdgID != -11 and pdgID != 22 and pdgID != 2112 and pdgID != 2212){
      if (e > 0.1) G4cout << "pdgID: " << tr->GetParticleDefinition()->GetParticleName() <<", Ek: " << e << G4endl;
    }*/
  }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

