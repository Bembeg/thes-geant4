#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include <array>

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

    static const G4int ArrayXSize = 256;
    static const G4int ArrayYSize = 256;
    static const G4int ArrayXYSize = ArrayXSize*ArrayYSize;

private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();


    std::array <std::array<G4VPhysicalVolume*, ArrayXSize>, ArrayYSize> blockArray;
};


#endif

