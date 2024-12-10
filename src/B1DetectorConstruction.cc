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
  G4Material* det_mat = new G4Material(name = "EJ301", density = 0.874*g/cm3, nel = 2);
  //det_mat->AddElement( nist->FindOrBuildElement("H"), natoms = 482);
  det_mat->AddElement( nist->FindOrBuildElement("H"), 0.121);
  //det_mat->AddElement( nist->FindOrBuildElement("C"), natoms = 398);
  det_mat->AddElement( nist->FindOrBuildElement("C"), 0.879);
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_W");
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* Alcell = nist->FindOrBuildMaterial("G4_Al");

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
  G4int nS = 16;
  //G4double tarCenter =   0.2*nS*0.5*cm;
  G4double tarCenter =   10.0*0.5*cm;

  G4Box* solidTarget =    
    new G4Box("Target",                    //its name
        5.0*cm, 2.2*cm, tarCenter*2.); //its size

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

  G4double detCenter1 = tarCenter*2.+32*cm+13.0*cm/2.0;
  //G4double detCenter1 = tarCenter*2.+12.4*cm+13.0*cm/2.0;
  //G4double detCenter2 = tarCenter*2.+31.2*cm+13.0*cm/2.0;
  G4double detCenter2 = detCenter1;
  G4double det2X = 18.8*cm;//13.0*cm+6.5*cm; 
  //G4double det2X = 0.0*cm;
  G4double detCB = -12.7*cm/2.0-0.15*cm;
  G4double detCT = 12.7*cm/2.0+0.15*cm;
  G4RotationMatrix* Rotation = new G4RotationMatrix();
  Rotation->rotateX(90*deg);
  Rotation->rotateY(0*deg);
  Rotation->rotateZ(0*deg);

  G4Tubs* solidDetCell1 =    
    new G4Tubs("DetCell1",                    //its name
        6.35*cm, 6.5*cm, 6.5*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDetCell1 =
    new G4LogicalVolume(solidDetCell1,            //its solid
                        Alcell,             //its material
                        "DetCell1");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(0,0,detCenter1),         //at (0,0,0)
                    logicDetCell1,                //its logical volume
                    "DetCell1",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  G4Tubs* solidDetCell1b =    
    new G4Tubs("DetCell1b",                    //its name
        0, 6.35*cm, 0.15*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDetCell1b =
    new G4LogicalVolume(solidDetCell1b,            //its solid
                        Alcell,             //its material
                        "DetCell1b");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(0,detCB,detCenter1),         //at (0,0,0)
                    logicDetCell1b,                //its logical volume
                    "DetCell1b",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  G4Tubs* solidDetCell1t =    
    new G4Tubs("DetCell1t",                    //its name
        0, 6.35*cm, 0.15*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDetCell1t =
    new G4LogicalVolume(solidDetCell1t,            //its solid
                        Alcell,             //its material
                        "DetCell1t");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(0,detCT,detCenter1),         //at (0,0,0)
                    logicDetCell1t,                //its logical volume
                    "DetCell1t",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking




  G4Tubs* solidDet1 =    
    new G4Tubs("Det1",                    //its name
        0*cm, 6.35*cm, 6.35*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDet1 =
    new G4LogicalVolume(solidDet1,            //its solid
                        det_mat,             //its material
                        "Det1");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(0,0,detCenter1),         //at (0,0,0)
                    logicDet1,                //its logical volume
                    "Det1",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



  G4Tubs* solidDetCell2 =    
    new G4Tubs("DetCell2",                    //its name
        6.35*cm, 6.5*cm, 6.5*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDetCell2 =
    new G4LogicalVolume(solidDetCell2,            //its solid
                        Alcell,             //its material
                        "DetCell2");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(det2X,0,detCenter2),         //at (0,0,0)
                    logicDetCell2,                //its logical volume
                    "DetCell2",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  G4Tubs* solidDetCell2b =    
    new G4Tubs("DetCell2b",                    //its name
        0, 6.35*cm, 0.15*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDetCell2b =
    new G4LogicalVolume(solidDetCell2b,            //its solid
                        Alcell,             //its material
                        "DetCell2b");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(det2X,detCB,detCenter2),         //at (0,0,0)
                    logicDetCell2b,                //its logical volume
                    "DetCell2b",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  G4Tubs* solidDetCell2t =    
    new G4Tubs("DetCell2t",                    //its name
        0, 6.35*cm, 0.15*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDetCell2t =
    new G4LogicalVolume(solidDetCell2t,            //its solid
                        Alcell,             //its material
                        "DetCell2t");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(det2X,detCT,detCenter2),         //at (0,0,0)
                    logicDetCell2t,                //its logical volume
                    "DetCell12",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4Tubs* solidDet2 =    
    new G4Tubs("Det2",                    //its name
        0*cm, 6.35*cm, 6.35*cm, 0, 360.0*deg); //its size
  G4LogicalVolume* logicDet2 =
    new G4LogicalVolume(solidDet2,            //its solid
                        det_mat,             //its material
                        "Det2");         //its name
  new G4PVPlacement(Rotation,                       //no rotation
                    G4ThreeVector(det2X,0,detCenter2),         //at (0,0,0)
                    logicDet2,                //its logical volume
                    "Det2",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



 
  fScoringVolume1 = logicWorld;
  fScoringVolume2 = logicTarget;
  fScoringVolume3 = logicDet1;
  fScoringVolume4 = logicDet2;
  
  return physWorld;
}

