//    **********************************
//    *                                *
//    *     DetectorConstruction Class *
//    *                                *
//    **********************************
//

//-----------------------------------------------------------------------------
// OBJECTIF
//-----------------------------------------------------------------------------
// Définit les matériaux et contruit la géométrie de
// Rogers et Mohan.
//-----------------------------------------------------------------------------

  #include "DetectorConstruction.hh"
  
  #include "G4RunManager.hh"     // controls the flow of the program
  #include "G4NistManager.hh"    // Access to NIST materials 
  #include "G4Box.hh"            // Creating a Box geometry
  #include "G4LogicalVolume.hh"   // LogicalVolume permits a material to be putted into a solid
  #include "G4PVPlacement.hh"   
  #include "G4UnionSolid.hh"     // Physical Volume places logical volume in a specific place, e.g. a mother volume
  #include "G4SystemOfUnits.hh"  
  #include "G4VisManager.hh"
  #include "G4Material.hh"
  #include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Requires the user to define the detector

  DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fScoringVolume(0)
  { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  DetectorConstruction::~DetectorConstruction()
  { }
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  G4VPhysicalVolume* DetectorConstruction::Construct()
  {  

//------------------------------------------------------------------------
//                      "Initialisation" et définitions
//------------------------------------------------------------------------


  G4bool checkOverlaps = true;

  // Positions en "x" des slabs

  G4double x0 = 0.0 *cm ;
  G4double x1 = 1.0 *cm ; 
  G4double x2 = 4.0 *cm ;
  G4double x3 = 6.0 *cm ;
  G4double x4 = 13.0*cm ;
  G4double x5 = 31.0*cm ;
  
  G4double l  = 8.0*cm ; 
  
  //G4double WorldDimension = 0.5*m ;  
//------------------------------------------------------------------------
//                 Material definition (See Appendix-10 for NIST)
//------------------------------------------------------------------------

  G4NistManager* nist    = G4NistManager::Instance();
  G4Material* air_mat    = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* water_mat  = nist->FindOrBuildMaterial("G4_WATER"); 
  G4Material* bone_mat   = nist->FindOrBuildMaterial("G4_BONE_CORTICAL_ICRP");
  G4Material* lung_mat   = nist->FindOrBuildMaterial("G4_LUNG_ICRP");
  //G4Material* Vacuum     = new G4Material
  //            ("Vacuum", 1.0, 1e-12*g/cm3,kStateGas,273.15*kelvin, 1.01325*bar);
              
//------------------------------------------------------------------------
//                       Construction de la géométrie
//------------------------------------------------------------------------

  // Geometry construction   (name,   size in x, size in y, size in z)

  //G4Box* World     = new G4Box("World"  ,WorldDimension ,WorldDimension,WorldDimension) ;
  G4Box* World     = new G4Box("World"  ,0.5*(x5-x0) ,l,l) ;
  G4Box* Slab1Geo  = new G4Box("Slab1"  ,0.5*(x2-x1) ,l,l) ;
  G4Box* Slab2Geo  = new G4Box("Slab2"  ,0.5*(x3-x2) ,l,l) ;
  G4Box* Slab3Geo  = new G4Box("Slab3"  ,0.5*(x4-x3) ,l,l) ;
  G4Box* Slab4Geo  = new G4Box("Slab4"  ,0.5*(x5-x4) ,l,l) ;
  
//------------------------------------------------------------------------
//                         Construction du volume global
//------------------------------------------------------------------------

 // Construire le volume logique  

  G4LogicalVolume* logicWorld  = new G4LogicalVolume (World,  air_mat  ,"World" ) ; 
  

  // Placer le volume logique dans l'espace

  G4VPhysicalVolume* PhysWorld =   
    new G4PVPlacement(0,                         //no rotation
                      G4ThreeVector(x0,0.0,0.0), //at (0,0,0)
                      logicWorld,                 //its logical volume
                      "Slab",                    //its name
                      0,                         //its mother  volume
                      false,                     //no boolean operation
                      0,                         //copy number
                      checkOverlaps) ;           //overlaps checking


//------------------------------------------------------------------------
//                      Construction des volumes filles
//------------------------------------------------------------------------

// WATER
G4LogicalVolume* logicSlab1Geo  = 
   new G4LogicalVolume (Slab1Geo,  water_mat   ,"Slab1" ) ; 
   new G4PVPlacement(0,                          //no rotation
                     G4ThreeVector(-0.5*x5+x1+0.5*(x2-x1),0.0,0.0),  
                     logicSlab1Geo,              //its logical volume
                     "Slab1",                    //its name
                     logicWorld,                 //its mother  volume
                     false,                      //no boolean operation
                     0,                          //copy number
                     checkOverlaps) ;            //overlaps checking

// BONE
 G4LogicalVolume* logicSlab2Geo  = 
    new G4LogicalVolume (Slab2Geo,  bone_mat   ,"Slab2" ) ; 
    new G4PVPlacement(0,                          //no rotation
                      G4ThreeVector(-0.5*x5+x1+(x2-x1)+0.5*(x3-x2),0.0,0.0), 
                      logicSlab2Geo,              //its logical volume
                      "Slab2",                    //its name
                      logicWorld,                 //its mother  volume
                      false,                      //no boolean operation
                      0,                          //copy number
                      checkOverlaps) ;            //overlaps checking   
 
// LUNG
 G4LogicalVolume* logicSlab3Geo  = 
    new G4LogicalVolume (Slab3Geo,  lung_mat   ,"Slab3" ) ; 
    new G4PVPlacement(0,                          //no rotation
                      G4ThreeVector(-0.5*x5+x1+(x2-x1)+(x3-x2)+0.5*(x4-x3),0.0,0.0),  
                      logicSlab3Geo,              //its logical volume
                      "Slab3",                    //its name
                      logicWorld,                 //its mother  volume
                      false,                      //no boolean operation
                      0,                          //copy number
                      checkOverlaps) ;            //overlaps checking  
  fScoringVolume = logicSlab1Geo;

// WATER
 G4LogicalVolume* logicSlab4Geo  = 
    new G4LogicalVolume (Slab4Geo,  water_mat   ,"Slab4" ) ; 
    new G4PVPlacement(0,                          //no rotation
                      G4ThreeVector(-0.5*x5+x1+(x2-x1)+(x3-x2)+(x4-x3)+0.5*(x5-x4),0.0,0.0),  
                      logicSlab4Geo,              //its logical volume
                      "Slab4",                    //its name
                      logicWorld,                 //its mother  volume
                      false,                      //no boolean operation
                      0,                          //copy number
                      checkOverlaps) ;            //overlaps checking  
  

  fScoringVolume = logicSlab1Geo; // Pas de raison particulière pour le garder (héritage de B1)

  //always return the physical World (POURQUOI, GABRIEL ?)
  return PhysWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
