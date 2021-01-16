

//    **********************************
//    *                                *
//    *  PrimaryGeneratorAction Class  *
//    *                                *
//    **********************************
//

#include "PrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4LogicalVolumeStore.hh"    //where volumes are stored
#include "G4LogicalVolume.hh"         // LogicalVolume permits a material to be putted into a solid
#include "G4Box.hh"                   // Box permits creating box-based geometry
#include "G4RunManager.hh"            // controls the flow of the program
 
#include "G4GeneralParticleSource.hh" // defines a particle source        
#include "G4ParticleTable.hh"         // can be used to create ions 
#include "G4ParticleDefinition.hh"    // has properties which characterize individual particles (mass, charge, spin,...)
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


//-----------------------------------------------------------------------------
//          Creating an instance of primary particle generator
//-----------------------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{ 
  // Use the GPS to generate primary particles,
  // Particle type, energy position, direction are specified in 
  // macro files.
  fParticleGun = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the beginning of event  
  fParticleGun -> GeneratePrimaryVertex(anEvent);	
  //fParticleGun -> SetParticlePosition(0.0*cm,0.0*cm,0.0*cm);
  //fParticleGun -> SetParticleEnergy(18.0*MeV);
}