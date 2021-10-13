#ifndef ADetectorConstruction_h
#define ADetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class ADetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ADetectorConstruction();
    virtual ~ADetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    
    // get methods
    const G4VPhysicalVolume* GetAbsorberPV() const;
    const G4VPhysicalVolume* GetAbsorberPar() const;
     
  private:
    // methods
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    G4VPhysicalVolume*   fAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   absorberPar;
};

// inline functions

inline const G4VPhysicalVolume* ADetectorConstruction::GetAbsorberPV() const 
{ 
  return fAbsorberPV; 
}

inline const G4VPhysicalVolume* ADetectorConstruction::GetAbsorberPar() const
{
  return absorberPar;
}
#endif

