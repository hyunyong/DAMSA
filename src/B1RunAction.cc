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
// $Id: B1RunAction.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Run.hh"
#include "B1Analysis.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <math.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction()
: G4UserRunAction()
{ 
  // add new units for dose
  // 
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);        

  auto analysisManager = G4RootAnalysisManager::Instance();
 
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetVerboseLevel(1);
  
  std::vector<G4double> eAxis;
  for (G4double i = 0.01; i < 10.; i += 0.01){eAxis.push_back(i);}
  std::vector<G4double> tAxis;
  for (G4double i = 0.0; i < 1.571; i += 1E-2){tAxis.push_back(i);}

  G4double targetL = 200.;
  std::vector<G4double> targetAxis;
  for (G4double i = 0.; i < targetL+1.; i += 1.){targetAxis.push_back(i);}

  G4int targetBin = G4int(targetL*10.);
  analysisManager->CreateH2("t_electron_et", "electron E [GeV] (10 Mev to 10 GeV)  Theta [rad] in target", eAxis, tAxis); //0
  analysisManager->CreateH2("t_positron_et", "positron E [GeV] (10 Mev to 10 GeV)  Theta [rad] in target", eAxis, tAxis); //1
  analysisManager->CreateH2("t_photon_et", "photon E [GeV] (10 Mev to 10 GeV)  Theta [rad] in target", eAxis, tAxis);     //2
  analysisManager->CreateH2("t_all_2D_ed", "Energy Deposit [MeV]", targetBin,0,targetL, 300,-15.,15.); //3
  analysisManager->CreateH2("d_all_2D_ed", "Energy Deposit [MeV]", 44,targetL+41,targetL+85, 12,-6,6); //4
  analysisManager->CreateH2("d_all_2D_edt", "Energy Deposit [MeV] by time [ns]", 44,targetL+41,targetL+85, 3000,0,3000); //5

  analysisManager->CreateH2("t_electron_ke", "electron production", targetAxis, eAxis); //6
  analysisManager->CreateH2("t_positron_ke", "positron production", targetAxis, eAxis); //7
  analysisManager->CreateH2("t_photon_ke", "photon production", targetAxis, eAxis); //8
  analysisManager->CreateH2("t_neutron_ke", "neutron production", targetAxis, eAxis); //9
  analysisManager->CreateH2("t_proton_ke", "proton production", targetAxis, eAxis); //10

  analysisManager->CreateH2("w_electron_ke", "leakage e- energy [GeV]", 500,0.001,5.001, 157,0,1.57); //11
  analysisManager->CreateH2("w_positron_ke", "leakage e+ energy [GeV]", 500,0.001,5.001, 157,0,1.57); //12
  analysisManager->CreateH2("w_photon_ke", "leakage photon energy [GeV]", 500,0.001,5.001, 157,0,1.57); //13
  analysisManager->CreateH2("w_neutron_ke", "leakage neutron energy [GeV]", 500,0.001,5.001, 157,0,1.57); //14
  analysisManager->CreateH2("w_proton_ke", "leakage proton energy [GeV]", 500,0.001,5.001, 157,0,1.57); //15

  analysisManager->CreateH1("d_all_ed", "Energy Deposit [MeV]",500,0.01,500.01); //0
  analysisManager->CreateH1("t_photon_z", "photon z [cm]", targetL*100, 0, targetL); //1
  analysisManager->CreateH1("t_neutron_z", "neutron z [cm]", targetL*100, 0, targetL); //2

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* B1RunAction::GenerateRun()
{
  return new B1Run; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile(); 
 
  const B1Run* b1Run = static_cast<const B1Run*>(run);

  // Compute dose
  //
  G4double edep  = b1Run->GetEdep();
  G4double edep2 = b1Run->GetEdep2();
  G4double rms = edep2 - edep*edep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

  const B1DetectorConstruction* detectorConstruction
   = static_cast<const B1DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double mass = detectorConstruction->GetScoringVolume1()->GetMass();
  G4double dose = edep/mass;
  G4double rmsDose = rms/mass;

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const B1PrimaryGeneratorAction* generatorAction
   = static_cast<const B1PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << " Dose in scoring volume : " 
     << G4BestUnit(dose,"Dose") << " +- " << G4BestUnit(rmsDose,"Dose")
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
