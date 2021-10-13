#ifndef OptDetectorConstruction_h
#define OptDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "OptDetectorMessenger.hh"

class OptDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    OptDetectorConstruction();
    virtual ~OptDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetBlockX(G4double );
    void SetBlockY(G4double );
    void SetBlockZ(G4double );
    void SetRInner(G4double );
    void SetROuter(G4double );
    void SetRTor(G4double );

    G4double GetBlockX(){return blockX;}
    G4double GetBlockY(){return blockY;}
    G4double GetBlockZ(){return blockZ;}
    G4double GetRInner(){return rInner;}
    G4double GetROuter(){return rOuter;}
    G4double GetRTor(){return rTor;}

  private:

    OptDetectorMessenger* fDetectorMessenger;

    G4double worldX, worldY, worldZ;
    G4double blockX, blockY, blockZ;
    G4double rInner, rOuter, rTor; 
    G4double torStartAngle, torEndAngle;
    G4double detX, detY, detZ;
    G4double mirrorThickness;
    G4double fibreOffset;
    G4double sideOffset, dist;
};


#endif