#include "TetraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
TetraApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_output_syntax") = false;
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_bahavior") = false;

  return params;
}

TetraApp::TetraApp(InputParameters parameters) : MooseApp(parameters)
{
  TetraApp::registerAll(_factory, _action_factory, _syntax);
}

TetraApp::~TetraApp() {}

void
TetraApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  // ModulesApp::registerAll(f, af, syntax);
  ModulesApp::registerAllObjects<TetraApp>(f, af, syntax);
  Registry::registerObjectsTo(f, {"TetraApp"});
  Registry::registerActionsTo(af, {"TetraApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
TetraApp::registerApps()
{
  registerApp(TetraApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
TetraApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  TetraApp::registerAll(f, af, s);
}
extern "C" void
TetraApp__registerApps()
{
  TetraApp::registerApps();
}
