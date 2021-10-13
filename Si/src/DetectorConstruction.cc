#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4PVDivision.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{}


DetectorConstruction::~DetectorConstruction()
{}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  DefineMaterials();
  
  return DefineVolumes();
}


void DetectorConstruction::DefineMaterials()
{ 
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_Si");

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}


G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{

// rozmer pixelu
  auto pixX = 55.*um;
  auto pixY = 55.*um;
  auto pixZ = 300.*um;

// definice materialu
  auto worldMat = G4Material::GetMaterial("G4_AIR");
  auto detectorMat = G4Material::GetMaterial("G4_Si");

// vytvoreni sveta
  auto worldS       = new G4Box("World", 50.*cm, 50.*cm, 50.*cm);
  auto worldLV      = new G4LogicalVolume(worldS, worldMat, "World");
  auto worldPV      = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0);

//polozeni pixelu do sveta
  auto pixS         = new G4Box("DetectorDiv", pixX/2, pixY/2, pixZ/2);
  auto pixLV        = new G4LogicalVolume(pixS, detectorMat, "DetectorDiv");
  
  for(G4int y=0; y < DetectorConstruction::ArrayYSize; y++) {
    for (G4int x=0; x < DetectorConstruction::ArrayXSize; x++) {
      G4int copyN = 1000 + DetectorConstruction::ArrayXSize*y+x;
      blockArray[x][y] = new G4PVPlacement(0, G4ThreeVector(x*pixX, y*pixY, 0.),
                                           pixLV, "BlockArray", worldLV, false, copyN, false);
    }
  }


  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);

  return worldPV;
}


