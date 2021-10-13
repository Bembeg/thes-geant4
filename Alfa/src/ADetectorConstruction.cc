#include "ADetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

ADetectorConstruction::ADetectorConstruction() : G4VUserDetectorConstruction(),
   fAbsorberPV(nullptr),
   absorberPar(nullptr)
{}


ADetectorConstruction::~ADetectorConstruction()
{}


G4VPhysicalVolume* ADetectorConstruction::Construct()
{
  DefineMaterials();
  
  return DefineVolumes();
}

void ADetectorConstruction::DefineMaterials()
{ 
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_AIR");

  // Vacuum
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density;
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* ADetectorConstruction::DefineVolumes()
{
  G4double absoThickness = 6.*cm;
  G4double calorSizeXY  = 10.*cm;

  auto worldSizeXY = 5 * calorSizeXY;
  auto worldSizeZ  = 5 * absoThickness; 
  
  auto defaultMaterial = G4Material::GetMaterial("Galactic");
  auto absorberMaterial = G4Material::GetMaterial("G4_AIR");
  
  if ( ! defaultMaterial || ! absorberMaterial) 
  {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("ADetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }  
   

  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0);                // copy number

  auto absorberS
    = new G4Box("Abso",
                 1.*cm,1.*cm, 5.*cm);

  auto absorberLV
            = new G4LogicalVolume(
                    absorberS,        // its solid
                    absorberMaterial, // its material
                    "Abso");
  fAbsorberPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 0.), // its position
                 absorberLV,       // its logical volume
                 "Abso",           // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0);                // copy number
                 

  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> Absorber is" << absoThickness/mm << "mm of " << absorberMaterial->GetName() <<G4endl
    << "------------------------------------------------------------" << G4endl;
  

  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);


  return worldPV;
}


