#include "ALPGunDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "ALPGunRunAction.hh"
ALPGunDetectorConstruction::ALPGunDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0),
  fScoringVolume4(0),
  fScoringVolume5(0),
  detectorLength(0.),
  targetLength(0.)
{
  messenger = new G4GenericMessenger(this, "/detector/", "Detector properties");
  messenger->DeclarePropertyWithUnit("detectorLength","cm",detectorLength)
        .SetGuidance("Set detector size Z")
        .SetStates(G4State_PreInit, G4State_Idle);

}

ALPGunDetectorConstruction::~ALPGunDetectorConstruction()
{
  delete messenger;
}

G4VPhysicalVolume* ALPGunDetectorConstruction::Construct()
{  
  G4String name;
  G4double density;
  G4int nel, natoms;

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4bool checkOverlaps = true;

  G4double detLength = detectorLength;
  G4cout << "[DetCon] Detector length: " << detectorLength/cm << " cm" << G4endl;
  G4double detCenter = detLength*0.5; 

  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*m, 0.5*m, detLength + 0.5*m);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  G4Box* solidDet =    
    new G4Box("Det",                    //its name
        6.0*cm, 6.0*cm, 0.5*detLength); //its size
  G4LogicalVolume* logicDet =
    new G4LogicalVolume(solidDet,            //its solid
                        det_mat,             //its material
                        "Det");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,detCenter),         //at (0,0,0)
                    logicDet,                //its logical volume
                    "Det",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  fScoringVolume1 = logicWorld;
  fScoringVolume2 = logicDet;
 
  return physWorld;
}

