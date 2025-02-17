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
// $Id: B1EventAction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1Run.hh"
#include "B1Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction()
: G4UserEventAction(),
  fEdep(0.),
  nPTr1(0.),
  nETr1(0.),
  nPhTr1(0.),
  nPrTr1(0.),
  nNeTr1(0.),
  nPTr2(0.),
  nETr2(0.),
  nPhTr2(0.),
  nPrTr2(0.),
  nNeTr2(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
  nPTr1 = 0;
  nETr1 = 0;
  nPhTr1 = 0;
  nPrTr1 = 0;
  nNeTr1 = 0;
  nPTr2 = 0;
  nETr2 = 0;
  nPhTr2 = 0;
  nPrTr2 = 0;
  nNeTr2 = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in B1Run

  /*B1Run* run 
    = static_cast<B1Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);
  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->FillH1(0, nPTr1);
  analysisManager->FillH1(1, nETr1);
  analysisManager->FillH1(2, nPhTr1);
  analysisManager->FillH1(3, nPrTr1);
  analysisManager->FillH1(4, nNeTr1);
  analysisManager->FillH1(5, nPTr2);
  analysisManager->FillH1(6, nETr2);
  analysisManager->FillH1(7, nPhTr2);
  analysisManager->FillH1(8, nPrTr2);
  analysisManager->FillH1(9, nNeTr2);*/

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
