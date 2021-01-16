//      *****************************************
//      *                                       *
//      *    PhysicsListMessenger Class         *
//      *                                       *
//      *****************************************
//


#include "PhysicsListMessenger.hh"
#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys)
:G4UImessenger(),
 fPhysicsList(pPhys),fPhysDir(0),fListCmd(0)
{ 
  fPhysDir= new G4UIdirectory("/UseEM/phys/");
  fPhysDir-> SetGuidance("physics list commands");


  fListCmd= new G4UIcmdWithAString("/UseEM/phys/addPhysics",this);  
  fListCmd->SetGuidance("Add modula physics list.");
  fListCmd->SetParameterName("PList",false);
  fListCmd->AvailableForStates(G4State_PreInit);  
}

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete fListCmd;
  delete fPhysDir;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{       
  if( command == fListCmd )
   { fPhysicsList->AddPhysicsList(newValue);}
}
