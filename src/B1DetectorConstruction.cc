#include "B1DetectorConstruction.hh"

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

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0),
  fScoringVolume4(0),
  fScoringVolume5(0)

{ }

B1DetectorConstruction::~B1DetectorConstruction()
{ }

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  G4String name;
  G4double density;
  G4int nel, natoms;

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_W");
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  //G4Material* det_mat = nist->FindOrBuildMaterial("G4_PbWO4");
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  G4Material* vCh_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* vac_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4bool checkOverlaps = true;


  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       3*m, 3*m, 3*m);     //its size
      
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
  G4double tarLength =   200.0*cm;
  G4double tarCenter =   tarLength*0.5;

  G4Box* solidTarget =    
    new G4Box("Target",                    //its name
        15.*cm, 15.*cm, tarLength*0.5); //its size

  G4LogicalVolume* logicTarget =                         
    new G4LogicalVolume(solidTarget,            //its solid
                        target_mat,             //its material
                        "Target");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,tarCenter),         //at (0,0,0)
                    logicTarget,                //its logical volume
                    "Target",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4double detLength1 = 44.0*cm;
  G4double vChLength1 = 30.0*cm;
  G4double detCenter1 = tarLength + 41.0*cm + detLength1*0.5; 
  G4double vChaCenter1 = tarLength + 1.0*cm + vChLength1*0.5;

  G4Box* solidDet1 =    
    new G4Box("Det1",                    //its name
        6.0*cm, 6.0*cm, detLength1*0.5); //its size
  G4LogicalVolume* logicDet1 =
    new G4LogicalVolume(solidDet1,            //its solid
                        det_mat,             //its material
                        "Det1");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,detCenter1),         //at (0,0,0)
                    logicDet1,                //its logical volume
                    "Det1",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

 
  G4Tubs* solidVac1 =
    new G4Tubs("Vac1",                    //its name
        0.0*cm, 9.7*cm, vChLength1*0.5-0.6*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicVac1 =
    new G4LogicalVolume(solidVac1,            //its solid
                        vac_mat,             //its material
                        "Vac1");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,vChaCenter1),         //at (0,0,0)
                    logicVac1,                //its logical volume
                    "Vac1",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

 

  G4Tubs* solidVacCha1 =
    new G4Tubs("VacCha1",                    //its name
        9.7*cm, 10.0*cm, vChLength1*0.5, 0, 360.0*deg); //its size
  G4LogicalVolume* logicVacCha1 =
    new G4LogicalVolume(solidVacCha1,            //its solid
                        vCh_mat,             //its material
                        "VacCha1");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,vChaCenter1),         //at (0,0,0)
                    logicVacCha1,                //its logical volume
                    "VacCha1",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

 
  G4Tubs* solidVacCha2 =
    new G4Tubs("VacCha2",                    //its name
        0.0*cm, 9.7*cm, 0.15*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicVacCha2 =
    new G4LogicalVolume(solidVacCha2,            //its solid
                        vCh_mat,             //its material
                        "VacCha2");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,vChaCenter1-15.0*cm+0.15*cm),         //at (0,0,0)
                    logicVacCha2,                //its logical volume
                    "VacCha2",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4Tubs* solidVacCha3 =
    new G4Tubs("VacCha3",                    //its name
        0.0*cm, 9.7*cm, 0.15*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicVacCha3 =
    new G4LogicalVolume(solidVacCha3,            //its solid
                        vCh_mat,             //its material
                        "VacCha3");         //its name
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,vChaCenter1+15.0*cm-0.15*cm),         //at (0,0,0)
                    logicVacCha3,                //its logical volume
                    "VacCha3",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  fScoringVolume1 = logicWorld;
  fScoringVolume2 = logicTarget;
  fScoringVolume3 = logicDet1;
  fScoringVolume4 = logicVac1;
  fScoringVolume5 = logicVacCha3;
  
  return physWorld;
}

