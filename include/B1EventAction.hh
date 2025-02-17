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
// $Id: B1EventAction.hh 75216 2013-10-29 16:08:11Z gcosmo $
//
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction();
    virtual ~B1EventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep;}
    void AddTr(G4int di, G4int nTr) {di == 1 ? nPTr1 += nTr : nPTr2 += nTr;}
    void AddETr(G4int di, G4int nTr) {di == 1 ? nETr1 += nTr : nETr2 += nTr;}
    void AddPhTr(G4int di, G4int nTr) {di == 1 ? nPhTr1 += nTr : nPhTr2 += nTr;}
    void AddPrTr(G4int di, G4int nTr) {di == 1 ? nPrTr1 += nTr : nPrTr2 += nTr;}
    void AddNeTr(G4int di, G4int nTr) {di == 1 ? nNeTr1 += nTr : nNeTr2 += nTr;}

  private:
    G4double  fEdep;
    G4int nPTr1, nETr1, nPhTr1, nPrTr1, nNeTr1;
    G4int nPTr2, nETr2, nPhTr2, nPrTr2, nNeTr2;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
