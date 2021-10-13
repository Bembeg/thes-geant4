#include "OptDetectorConstruction.hh"
#include "OptDetectorMessenger.hh"
#include "OptTrackerSD.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UImanager.hh"
#include "G4CutTubs.hh"



OptDetectorConstruction::OptDetectorConstruction()
: G4VUserDetectorConstruction()
{
    worldX = worldY = worldZ = 1.0*0.5*m;
    blockX = blockY = 50*0.5*mm;
    blockZ = 6*0.5*mm;
    torStartAngle=-50*degree;
    torEndAngle=270*degree-torStartAngle;
    rInner = 4*0.5*mm;
    rOuter = 4.1*0.5*mm;
    rTor = 30*0.5*mm;
    detX = detY = 4.5*0.5*mm;
    detZ = 1*0.5*mm;
    mirrorThickness=0.05*0.5*mm;
    fibreOffset = 0*blockZ;
    sideOffset = 1*mm;
    dist = 2.2*cm;

    fDetectorMessenger = new OptDetectorMessenger(this);
}

OptDetectorConstruction::~OptDetectorConstruction(){
    delete fDetectorMessenger;
}

G4VPhysicalVolume* OptDetectorConstruction::Construct()
{
//Material Definitions
    G4NistManager* man = G4NistManager::Instance();
    G4Material* fWorldMat = man->FindOrBuildMaterial("G4_AIR");
    G4Material* fScintMat = man->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material* fWLSMat = man->FindOrBuildMaterial("G4_POLYSTYRENE");
    G4Material* fCladMat = man->FindOrBuildMaterial("G4_PLEXIGLASS");
    G4Material* fMirrorMat = man->FindOrBuildMaterial("G4_Al");
    G4Material* fDetecMat = man->FindOrBuildMaterial("G4_Si");

//
//Material Properties
//

    G4double photonWaveL[] = 
    {350, 410, 425, 438, 450,
    465, 490, 520, 540, 600};

    const G4int nOfEntries = sizeof(photonWaveL)/sizeof(G4double);
    
    G4double photonEnergy[nOfEntries];

    for(int i=0; i<nOfEntries; i++) 
    { 
        photonEnergy[i]=1.24e3/photonWaveL[i]*eV;
    }
    

    //Scintillation material properties
    G4double R=1.5;
    G4double scintRIndex[] =
    {R, R, R, R, R,
    R, R, R, R, R,};

    G4double scintAbsorb[] =
    {0.2*m, 0.2*m, 0.2*m, 0.2*m, 0.2*m,
     0.2*m, 0.2*m, 0.2*m, 0.2*m, 0.2*m};
    
    G4double scintFast[] =
    {1, 4, 5, 5, 5, 
    3, 1, 0.5, 0.3, 0.1};
 
    
    G4MaterialPropertiesTable* scintMPT = new G4MaterialPropertiesTable();
    scintMPT->AddProperty("RINDEX", photonEnergy, scintRIndex, nOfEntries)->SetSpline(true);
    scintMPT->AddProperty("ABSLENGTH", photonEnergy, scintAbsorb, nOfEntries)->SetSpline(true);
    scintMPT->AddProperty("FASTCOMPONENT",photonEnergy, scintFast, nOfEntries)->SetSpline(true);
    scintMPT->AddConstProperty("SCINTILLATIONYIELD",100./MeV);
    scintMPT->AddConstProperty("RESOLUTIONSCALE",1.0);
    scintMPT->AddConstProperty("FASTTIMECONSTANT", 5.*ns);
    fScintMat->SetMaterialPropertiesTable(scintMPT);


    //Worldmat material properties
    R=1.00;
    G4double worldRIndex[] =
    {R, R, R, R, R,
    R, R, R, R, R,};

    G4double worldAbsorb[] = 
    {10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
    10.*m, 10.*m, 10.*m, 10.*m, 10.*m};

    G4MaterialPropertiesTable* worldMPT = new G4MaterialPropertiesTable();
    worldMPT->AddProperty("RINDEX", photonEnergy, worldRIndex, nOfEntries)-> SetSpline(true);
    worldMPT->AddProperty("ABSLENGTH", photonEnergy, worldAbsorb, nOfEntries)->SetSpline(true);
    fWorldMat->SetMaterialPropertiesTable(worldMPT);


    //WLS material properties
    R=1.59;
    G4double WLSRIndex[] = 
    {R, R, R, R, R,
    R, R, R, R, R,};   
    
    G4double WLSAbsorb[] = 
    {1*cm, 0.1*cm, 0.1*mm, 0.5*mm, 0.3*mm,
    0.3*cm, 10*m, 10*m, 10*m, 10*m};

    G4double WLSEmission[] =
    {0, 0, 0, 0, 0,
    1, 10, 5.5, 2, 0}; 

    G4MaterialPropertiesTable* WLSMPT = new G4MaterialPropertiesTable();
    WLSMPT->AddProperty("RINDEX",photonEnergy, WLSRIndex, nOfEntries)->SetSpline(true);
    WLSMPT->AddProperty("WLSABSLENGTH",photonEnergy,WLSAbsorb,nOfEntries);//->SetSpline(true);
    WLSMPT->AddProperty("WLSCOMPONENT",photonEnergy,WLSEmission,nOfEntries)->SetSpline(true);
    WLSMPT->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);
    fWLSMat->SetMaterialPropertiesTable(WLSMPT);

    //Cladding material properties
    R=1.42;   
    G4double cladRIndex[] = 
    {R, R, R, R, R,
    R, R, R, R, R,};

    G4double cladAbsorb[] = 
    {10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
    10.*m, 10.*m, 10.*m, 10.*m, 10.*m};

    G4MaterialPropertiesTable* cladMPT = new G4MaterialPropertiesTable();
    cladMPT->AddProperty("RINDEX", photonEnergy, cladRIndex, nOfEntries)->SetSpline(true);
    cladMPT->AddProperty("ABSLENGTH", photonEnergy, cladAbsorb, nOfEntries)->SetSpline(true);
    fCladMat->SetMaterialPropertiesTable(cladMPT);    

    //Mirror material properties
    R=1.09;
    G4double mirrRIndex[] = 
    {R, R, R, R, R,
    R, R, R, R, R,};

    G4double mirrAbsorb[] = 
    {0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm,
    0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm};

    G4MaterialPropertiesTable* mirrMPT = new G4MaterialPropertiesTable();
    mirrMPT->AddProperty("RINDEX", photonEnergy, mirrRIndex, nOfEntries)->SetSpline(true);
    mirrMPT->AddProperty("ABSLENGTH", photonEnergy, mirrAbsorb, nOfEntries)->SetSpline(true);
    fMirrorMat->SetMaterialPropertiesTable(mirrMPT);

    //Detector material properties
    R=1.5;
    G4double detRIndex[] =
    {R, R, R, R, R,
    R, R, R, R, R};

    G4double detAbsorb[] = 
    {0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm,
    0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm, 0.1*mm};
    G4MaterialPropertiesTable* detMPT = new G4MaterialPropertiesTable();
    detMPT->AddProperty("RINDEX", photonEnergy, detRIndex, nOfEntries)->SetSpline(true);
    detMPT->AddProperty("ABSLENGTH", photonEnergy, detAbsorb, nOfEntries)->SetSpline(true);
    fDetecMat->SetMaterialPropertiesTable(detMPT);

//
//Placement
//

//World
    G4Box* worldS = new G4Box("World", worldX, worldY, worldZ);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, fWorldMat, "World", 0,0,0);
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0);

//Scintillation Block
    G4Box* blockS = new G4Box("ScintBlock", blockX, blockY, blockZ);
    G4LogicalVolume* blockLV = new G4LogicalVolume(blockS, fScintMat, "ScintBlock", 0,0,0);
    G4VPhysicalVolume* blockPV = new G4PVPlacement(0, G4ThreeVector(), blockLV, "ScintBlock", worldLV, false, 0);
  

//WLS Tubes + Cladding
    G4Tubs* WLSTubeS = new G4Tubs("WLSTube", 0, rInner, blockX-3*sideOffset, 0*degree,360*degree);
    G4LogicalVolume* WLSTubeLV = new G4LogicalVolume(WLSTubeS, fWLSMat, "WLSTube", 0,0,0);

    G4Tubs* TubeCladS = new G4Tubs("TubeClad", rInner, rOuter,blockX-3*sideOffset, 0*degree,360*degree);
    G4LogicalVolume* TubeCladLV = new G4LogicalVolume(TubeCladS, fCladMat, "TubeClad", 0,0,0);

    //Bottom Tube
    G4RotationMatrix rotBot = G4RotationMatrix();
    rotBot.rotateY(90*deg);

    G4ThreeVector posBot = G4ThreeVector(3*sideOffset+detZ,-dist,fibreOffset);
    G4Transform3D transBot = G4Transform3D(rotBot,posBot);
    G4VPhysicalVolume* TubeBotPV = new G4PVPlacement(transBot, WLSTubeLV, "TubeBot", blockLV, false, 0);
    G4VPhysicalVolume* CladBotPV = new G4PVPlacement(transBot, TubeCladLV, "CladBot", blockLV, false, 0);

    //Top Tube
    G4ThreeVector posTop = G4ThreeVector(-3*sideOffset-detZ, dist, fibreOffset);
    G4Transform3D transTop = G4Transform3D(rotBot, posTop);
    G4VPhysicalVolume* TubeTopPV = new G4PVPlacement(transTop, WLSTubeLV, "TubeTop", blockLV, false, 0);
    G4VPhysicalVolume* CladTopPV = new G4PVPlacement(transTop, TubeCladLV, "CladTop", blockLV, false, 0);

    //Left Tube
    G4RotationMatrix rotLeft = G4RotationMatrix();
    rotLeft.rotateX(90*deg);

    G4ThreeVector posLeft = G4ThreeVector(-dist, -3*sideOffset-detZ, fibreOffset);
    G4Transform3D transLeft = G4Transform3D(rotLeft, posLeft);
    G4VPhysicalVolume* TubeLeftPV = new G4PVPlacement(transLeft, WLSTubeLV, "TubeLeft", blockLV, false, 0);
    G4VPhysicalVolume* CladLeftPV = new G4PVPlacement(transLeft, TubeCladLV, "CladLeft", blockLV, false, 0);

    //Right Tube
    G4ThreeVector posRight = G4ThreeVector(dist, 3*sideOffset+detZ, fibreOffset);
    G4Transform3D transRight = G4Transform3D(rotLeft, posRight);
    G4VPhysicalVolume* TubeRightPV = new G4PVPlacement(transRight, WLSTubeLV, "TubeRight", blockLV, false, 0);
    G4VPhysicalVolume* CladRightPV = new G4PVPlacement(transRight, TubeCladLV, "CladLeft", blockLV, false, 0);
    
//Mirror
    G4Tubs* MirrorS = new G4Tubs("Mirror", 0, rOuter, mirrorThickness,0*degree,360*degree);
    G4LogicalVolume* MirrorLV = new G4LogicalVolume(MirrorS, fMirrorMat, "Mirror", 0,0,0);
    
    //Bot
    G4ThreeVector mirrBotPos = G4ThreeVector(-blockX+6*sideOffset+detZ-mirrorThickness , -dist, fibreOffset);
    G4Transform3D mirrBotTrans = G4Transform3D(rotBot,mirrBotPos);
    G4VPhysicalVolume* MirrorBot = new G4PVPlacement(mirrBotTrans, MirrorLV, "MirrBot", blockLV, false, 0);

    //Top
    G4ThreeVector mirrTopPos = G4ThreeVector(blockX-6*sideOffset-detZ+mirrorThickness, dist, fibreOffset);
    G4Transform3D mirrTopTrans = G4Transform3D(rotBot, mirrTopPos);
    G4VPhysicalVolume* MirrorTop = new G4PVPlacement(mirrTopTrans, MirrorLV, "MirrTop", blockLV, false, 0);
    
    //Left
    G4ThreeVector mirrLeftPos = G4ThreeVector(-dist, blockY-6*sideOffset-detZ+mirrorThickness, fibreOffset);
    G4Transform3D mirrLeftTrans = G4Transform3D(rotLeft, mirrLeftPos);
    G4VPhysicalVolume* MirrorLeft = new G4PVPlacement(mirrLeftTrans, MirrorLV, "MirrLeft", blockLV, false, 0);

    //Right
    G4ThreeVector mirrRightPos = G4ThreeVector(dist, -blockY+6*sideOffset+detZ-mirrorThickness, fibreOffset);
    G4Transform3D mirrRightTrans = G4Transform3D(rotLeft, mirrRightPos);
    G4VPhysicalVolume* MirrorRight = new G4PVPlacement(mirrRightTrans, MirrorLV, "MirrRight", blockLV, false, 0);

//Detector Block
    G4Box* detectorS = new G4Box("Detector", detX, detY, detZ);
    G4LogicalVolume* detBotLV = new G4LogicalVolume(detectorS, fDetecMat, "DetBot", 0,0,0);
    G4LogicalVolume* detTopLV = new G4LogicalVolume(detectorS, fDetecMat, "DetTop", 0,0,0);
    G4LogicalVolume* detLeftLV = new G4LogicalVolume(detectorS, fDetecMat, "DetLeft", 0,0,0);
    G4LogicalVolume* detRightLV = new G4LogicalVolume(detectorS, fDetecMat, "DetRight", 0,0,0);

    G4ThreeVector detBotPos = G4ThreeVector(blockX+sideOffset,-dist,fibreOffset);
    G4Transform3D detBotTrans = G4Transform3D(rotBot, detBotPos);
    G4VPhysicalVolume* detBot = new G4PVPlacement(detBotTrans, detBotLV, "DetBot", worldLV, false, 0);

    G4ThreeVector detTopPos = G4ThreeVector(-blockX-sideOffset, dist, fibreOffset);
    G4Transform3D detTopTrans = G4Transform3D(rotBot, detTopPos);
    G4VPhysicalVolume* detTop = new G4PVPlacement(detTopTrans, detTopLV, "DetTop", worldLV, false, 0);

    G4ThreeVector detLeftPos = G4ThreeVector (-dist, -blockY-sideOffset, fibreOffset);
    G4Transform3D detLeftTrans = G4Transform3D(rotLeft, detLeftPos);
    G4VPhysicalVolume* detLeft = new G4PVPlacement(detLeftTrans, detLeftLV, "DetLeft", worldLV, false, 0);
    
    G4ThreeVector detRightPos = G4ThreeVector (dist, blockY+sideOffset, fibreOffset);
    G4Transform3D detRightTrans = G4Transform3D(rotLeft, detRightPos);
    G4VPhysicalVolume* detRight = new G4PVPlacement(detRightTrans, detRightLV, "DetRight", worldLV, false, 0);



//
//Optical Surfaces
//

//Mirror
    G4OpticalSurface* mirrOpSurf = new G4OpticalSurface("MirrorSurface");
    mirrOpSurf->SetType(dielectric_dielectric);
    mirrOpSurf->SetFinish(groundfrontpainted);
    mirrOpSurf->SetModel(unified);

    G4LogicalSkinSurface* mirrSurf = new G4LogicalSkinSurface("MirrorSurface", MirrorLV, mirrOpSurf);
    G4double mirrReflect[] = 
    {1.0, 1.0, 1.0, 1.0, 1.0, 
     1.0, 1.0, 1.0, 1.0, 1.0};

    G4MaterialPropertiesTable* mirrSurfMPT = new G4MaterialPropertiesTable();
    mirrSurfMPT->AddProperty("REFLECTIVITY", photonEnergy, mirrReflect, nOfEntries);
    
    mirrOpSurf->SetMaterialPropertiesTable(mirrSurfMPT);



//Scintillator Optical Surface
    G4OpticalSurface* ScintSurf = new G4OpticalSurface("ScintSurf");
    ScintSurf->SetType(dielectric_dielectric);
    ScintSurf->SetFinish(groundfrontpainted);
    ScintSurf->SetModel(unified);

    G4LogicalSkinSurface* ScintSkinSurf = new G4LogicalSkinSurface("ScintSkinSurf", blockLV, ScintSurf);
    G4double scintReflect[] =
    {1.0, 1.0, 1.0, 1.0, 1.0, 
     1.0, 1.0, 1.0, 1.0, 1.0};
    G4MaterialPropertiesTable* scintSurfMPT = new G4MaterialPropertiesTable();
    scintSurfMPT->AddProperty("REFLECTIVITY", photonEnergy, scintReflect, nOfEntries);
    ScintSurf->SetMaterialPropertiesTable(scintMPT);

//Air Optical Surface
    G4OpticalSurface* AirSurf = new G4OpticalSurface("AirSurf");
    AirSurf->SetType(dielectric_dielectric);
    AirSurf->SetFinish(polished);
    AirSurf->SetModel(unified);
    G4LogicalSkinSurface* AirSkinSurf = new G4LogicalSkinSurface("AirSkinSurf", worldLV, AirSurf);
    AirSurf->SetMaterialPropertiesTable(worldMPT);

//WLS Optical Surface  
    G4OpticalSurface* WLSSurf = new G4OpticalSurface("WLSSurf");
    WLSSurf->SetType(dielectric_dielectric);
    WLSSurf->SetFinish(polished);
    WLSSurf->SetModel(unified);
    G4LogicalSkinSurface* WLSTubeSkinSurf = new G4LogicalSkinSurface("WLSTubeSkinSurf", WLSTubeLV, WLSSurf);
    WLSSurf->SetMaterialPropertiesTable(WLSMPT);

//Cladding Optical Surface
    G4OpticalSurface* CladSurf = new G4OpticalSurface("CladSurf");
    CladSurf->SetType(dielectric_dielectric);
    CladSurf->SetFinish(polished);
    CladSurf->SetModel(unified);
    G4LogicalSkinSurface* TubeCladSkinSurf = new G4LogicalSkinSurface("TubeCladSkinSurf", TubeCladLV, CladSurf);
    CladSurf->SetMaterialPropertiesTable(cladMPT);

//Detector Optical Surface


    return worldPV;
}

void OptDetectorConstruction::ConstructSDandField()
{
    OptTrackerSD* detBot = new OptTrackerSD("DetBot", "Bot Detector Collection");
    G4SDManager::GetSDMpointer()->AddNewDetector(detBot);
    SetSensitiveDetector("DetBot", detBot, false);

    OptTrackerSD* detTop = new OptTrackerSD("DetTop", "Top Detector Collection");
    G4SDManager::GetSDMpointer()->AddNewDetector(detTop);
    SetSensitiveDetector("DetTop", detTop, false);

    OptTrackerSD* detLeft = new OptTrackerSD("DetLeft", "Left Detector Collection");
    G4SDManager::GetSDMpointer()->AddNewDetector(detLeft);
    SetSensitiveDetector("DetLeft", detLeft, false);

    OptTrackerSD* detRight = new OptTrackerSD("DetRight", "Right Detector Collection");
    G4SDManager::GetSDMpointer()->AddNewDetector(detRight);
    SetSensitiveDetector("DetRight", detRight, false);
}

void OptDetectorConstruction::SetBlockX(G4double BlockX) {
  this->blockX=BlockX;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void OptDetectorConstruction::SetBlockY(G4double BlockY) {
  this->blockY=BlockY;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void OptDetectorConstruction::SetBlockZ(G4double BlockZ) {
  this->blockZ=BlockZ;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void OptDetectorConstruction::SetRInner(G4double RInner) {
  this->rInner=RInner;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void OptDetectorConstruction::SetROuter(G4double ROuter) {
  this->rOuter=ROuter;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void OptDetectorConstruction::SetRTor(G4double RTor) {
  this->rTor=RTor;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}