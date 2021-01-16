//    **********************************
//    *                                *
//    *        PhysicsList             *
//    *                                *
//    **********************************

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4EmConfigurator.hh"
#include "globals.hh"

class PhysicsListMessenger;

// Modular physics used in this application
class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
  ~PhysicsList();
  void ConstructParticle(); 
  void AddPhysicsList(const G4String& name);
  void ConstructProcess();

protected:
  void SetCuts();

private:
  G4VPhysicsConstructor* fEmPhysicsList;
  G4VPhysicsConstructor* fDecPhysicsList;
  G4VPhysicsConstructor* fRadDecayPhysicsList;
  PhysicsListMessenger* fMessenger;
  G4String fEmName;
};
#endif
