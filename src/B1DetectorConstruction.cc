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
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 70*mm, env_sizeZ = 80*mm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
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
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //colors
 
  G4Color blue(0.537, 0.812, 0.941);
  G4VisAttributes* blueVis = new G4VisAttributes(blue);
  
  G4Color purple(0.5, 0.0, 0.5);
  G4VisAttributes* purpleVis = new G4VisAttributes(purple);
  
  G4Color yellow(1.0, 1.0, 0.0);
  G4VisAttributes* yellowVis = new G4VisAttributes(yellow);
  
  G4Color grey(0.5, 0.5, 0.5);
  G4VisAttributes* greyVis = new G4VisAttributes(grey);
  
  //     
  // Shape 1
  //  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4ThreeVector pos1 = G4ThreeVector(-13.255*mm, 13.255*mm, 0*mm);
        
  // Conical section shape       

  G4Box* solidShape1 =    
    new G4Box("Shape1", 
    0.5*26.5*mm, 0.5*26.5*mm, 0.5*20.0*mm);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  logicShape1->SetVisAttributes(blueVis);    
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



  //     
  // Shape 2
  //
  G4ThreeVector pos2 = G4ThreeVector(-13.255*mm, -13.255*mm, 0*mm);

  // Trapezoid shape       
  
  G4Box* solidShape2 =    
    new G4Box("Shape2",                      //its name
              0.5*26.5*mm, 0.5*26.5*mm, 0.5*20.0*mm); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape1_mat,          //its material
                        "Shape2");           //its name
                        
  logicShape2->SetVisAttributes(blueVis);                      
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                    
                    
  G4ThreeVector pos3 = G4ThreeVector(13.255*mm, 13.255*mm, 0*mm);
        
  // Conical section shape       

  G4Box* solidShape3 =    
    new G4Box("Shape3", 
    0.5*26.5*mm, 0.5*26.5*mm, 0.5*20.0*mm);
                      
  G4LogicalVolume* logicShape3 =                         
    new G4LogicalVolume(solidShape3,         //its solid
                        shape1_mat,          //its material
                        "Shape3");           //its name
      
   logicShape3->SetVisAttributes(blueVis);            
  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicShape3,             //its logical volume
                    "Shape3",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                  
  
   G4ThreeVector pos4 = G4ThreeVector(13.255*mm, -13.255*mm, 0*mm);
        
  // Conical section shape       

  G4Box* solidShape4 =    
    new G4Box("Shape4", 
    0.5*26.5*mm, 0.5*26.5*mm, 0.5*20.0*mm);
                      
  G4LogicalVolume* logicShape4 =                         
    new G4LogicalVolume(solidShape4,         //its solid
                        shape1_mat,          //its material
                        "Shape4");           //its name
   logicShape4->SetVisAttributes(blueVis);            
  new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                  
     G4ThreeVector pos5 = G4ThreeVector(0*mm, 0*mm, 11*mm);
        
  // Quartz window (monolithic)      

  G4Box* solidShape5 =    
    new G4Box("Shape5", 
    0.5*59.0*mm, 0.5*59.0*mm, 0.5*2.0*mm);
                      
  G4LogicalVolume* logicShape5 =                         
    new G4LogicalVolume(solidShape5,         //its solid
                        shape1_mat,          //its material
                        "Shape5");           //its name
               
  logicShape5->SetVisAttributes(purpleVis);           
               
  new G4PVPlacement(0,                       //no rotation
                    pos5,                    //at position
                    logicShape5,             //its logical volume
                    "Shape5",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                                  
                                       
  
    G4Material* shape6_mat = nist->FindOrBuildMaterial("G4_GALLIUM_ARSENIDE");
  G4ThreeVector pos7 = G4ThreeVector(-13.255*mm, 13.255*mm, 12.015*mm);
        
  // Conical section shape       

  G4Box* solidShape7 =    
    new G4Box("Shape7", 
    0.5*26.5*mm, 0.5*26.5*mm, 0.5*0.01*mm);
                      
  G4LogicalVolume* logicShape7 =                         
    new G4LogicalVolume(solidShape7,         //its solid
                        shape6_mat,          //its material
                        "Shape7");           //its name
        
  logicShape7->SetVisAttributes(yellowVis);      
               
  new G4PVPlacement(0,                       //no rotation
                    pos7,                    //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



  //     
  // Shape 2
  //

  G4ThreeVector pos8 = G4ThreeVector(-13.255*mm, -13.255*mm, 12.015*mm);

  // Trapezoid shape       
  
  G4Box* solidShape8=    
    new G4Box("Shape8",                      //its name
              0.5*26.5*mm, 0.5*26.5*mm, 0.5*0.01*mm); //its size
                
  G4LogicalVolume* logicShape8 =                         
    new G4LogicalVolume(solidShape8,         //its solid
                        shape6_mat,          //its material
                        "Shape8");           //its name
                        
  logicShape8->SetVisAttributes(yellowVis);  
               
  new G4PVPlacement(0,                       //no rotation
                    pos8,                    //at position
                    logicShape8,             //its logical volume
                    "Shape8",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                    

  G4ThreeVector pos9 = G4ThreeVector(13.255*mm, 13.255*mm, 12.015*mm);
        
  // Conical section shape       

  G4Box* solidShape9 =    
    new G4Box("Shape9", 
    0.5*26.5*mm, 0.5*26.5*mm, 0.5*0.01*mm);
                      
  G4LogicalVolume* logicShape9 =                         
    new G4LogicalVolume(solidShape9,         //its solid
                        shape6_mat,          //its material
                        "Shape9");           //its name
                        
  logicShape9->SetVisAttributes(yellowVis);                        
               
  new G4PVPlacement(0,                       //no rotation
                    pos9,                    //at position
                    logicShape9,             //its logical volume
                    "Shape9",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                  
  
   G4ThreeVector pos10 = G4ThreeVector(13.255*mm, -13.255*mm, 12.015*mm);
        
  // Conical section shape       

  G4Box* solidShape10 =    
    new G4Box("Shape10", 
    0.5*26.5*mm, 0.5*26.5*mm, 0.5*0.01*mm);
                      
  G4LogicalVolume* logicShape10 =                         
    new G4LogicalVolume(solidShape10,         //its solid
                        shape6_mat,          //its material
                        "Shape10");           //its name
                        
  logicShape10->SetVisAttributes(yellowVis);                        
               
  new G4PVPlacement(0,                       //no rotation
                    pos10,                    //at position
                    logicShape10,             //its logical volume
                    "Shape10",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                  
   
   
  //Photocathode
  G4Material* shape11_mat = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  G4ThreeVector pos11 = G4ThreeVector(0.0*mm, 0.0*mm, 21.03*mm);
           
  G4Box* solidShape11 =    
    new G4Box("Shape11", 
    0.5*59.0*mm, 0.5*59.0*mm, 0.5*18.0*mm);
                      
  G4LogicalVolume* logicShape11 =                         
    new G4LogicalVolume(solidShape11,         //its solid
                        shape11_mat,          //its material
                        "Shape11");           //its name
                        
  logicShape11->SetVisAttributes(greyVis);                        
               
  new G4PVPlacement(0,                       //no rotation
                    pos11,                    //at position
                    logicShape11,             //its logical volume
                    "Shape11",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                  
   
        
       
  
                    
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
