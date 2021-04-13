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
// -------------------------------------------------------------------
// -------------------------------------------------------------------

#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::DetectorConstruction()
        : fPhysiWorld(NULL), fLogicWorld(NULL), fSolidWorld(NULL) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::~DetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume *DetectorConstruction::Construct() {
    DefineMaterials();
    return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstruction::DefineMaterials() {
    // Silicon is defined from NIST material database
    G4NistManager *man = G4NistManager::Instance();
    G4Material *GaAs = man->FindOrBuildMaterial("G4_GALLIUM_ARSENIDE");

    G4int atomicNumber;
    G4Element *Si = man->FindOrBuildElement(atomicNumber = 14);


    G4int ncomponents, natoms;
    G4double density;
    G4double fractionmass;



    // Default materials in setup.


    G4double z, a;
    fSiMaterial = man->FindOrBuildMaterial("G4_Si");
//    G4Element *N = new G4Element("Nitrogen", "N", z = 7., a = 14.01 * g / mole);
    G4Element *C = new G4Element("Carbon", "C", z = 6., a = 12.0107 * g / mole);


    G4Material *SiC = new G4Material("SiC", density = 3.16 * g /cm3, ncomponents = 2);
    SiC -> AddElement(Si, natoms = 1);
    SiC-> AddElement(C, natoms = 1);
    fSiCMaterial = SiC;
    fAirMaterial = man->FindOrBuildMaterial("G4_AIR");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4VPhysicalVolume *DetectorConstruction::ConstructDetector() {

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

    // WORLD VOLUME

    fWorldSizeX = 200 * um;
    fWorldSizeY = 200 * um;
    fWorldSizeZ = 100 * um;

    fSolidWorld = new G4Box("World",                     //its name
                            fWorldSizeX * 0.5, fWorldSizeY * 0.5, fWorldSizeZ);  //its size


    fLogicWorld = new G4LogicalVolume(fSolidWorld,    //its solid
                                      fAirMaterial,        //its material
                                      "World");        //its name

    fPhysiWorld = new G4PVPlacement(0,            //no rotation
                                    G4ThreeVector(),    //at (0,0,0)
                                    "World",        //its name
                                    fLogicWorld,        //its logical volume
                                    0,            //its mother  volume
                                    false,            //no boolean operation
                                    0);            //copy number

    G4double TargetSizeZ1 = 100 * um;
    G4double TargetSizeZ2 = 200 * um;

    ;

    G4Box *targetSolid1 = new G4Box("Target1",                     //its name
                                    TargetSizeZ2 / 2, TargetSizeZ2/ 2, TargetSizeZ1/2 );   //its size


    G4LogicalVolume *logicTarget1 = new G4LogicalVolume(targetSolid1,       //its solid
                                                        fSiMaterial,    //its material
                                                        "Target1");        //its name

    new G4PVPlacement(0,                                           //no rotation
                      G4ThreeVector(0, 0, 0.5*TargetSizeZ1),
                      "Target1",        //its name
                      logicTarget1,    //its logical volume
                      fPhysiWorld,        //its mother  volume
                      false,        //no boolean operation
                      0);            //copy number



    // Visualization attributes
    G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); //White
    worldVisAtt->SetVisibility(true);
    fLogicWorld->SetVisAttributes(worldVisAtt);

    G4VisAttributes *worldVisAtt1 = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
    worldVisAtt1->SetVisibility(true);
    logicTarget1->SetVisAttributes(worldVisAtt1);



    // Create Target G4Region and add logical volume

    fRegion = new G4Region("Target");

    G4ProductionCuts *cuts = new G4ProductionCuts();

    G4double defCut = 1 * nanometer;
    cuts->SetProductionCut(defCut, "gamma");
    cuts->SetProductionCut(defCut, "e-");
    cuts->SetProductionCut(defCut, "e+");
    cuts->SetProductionCut(defCut, "proton");

    fRegion->SetProductionCuts(cuts);
//    fRegion->AddRootLogicalVolume(logicTarget1);
//    fRegion->AddRootLogicalVolume(logicTarget2);
//    fRegion->AddRootLogicalVolume(logicTarget3);
    return fPhysiWorld;
}
