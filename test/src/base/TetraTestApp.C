//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "TetraTestApp.h"
#include "TetraApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
TetraTestApp::validParams()
{
  InputParameters params = TetraApp::validParams();
  return params;
}

TetraTestApp::TetraTestApp(InputParameters parameters) : MooseApp(parameters)
{
  TetraTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

TetraTestApp::~TetraTestApp() {}

void
TetraTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  TetraApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"TetraTestApp"});
    Registry::registerActionsTo(af, {"TetraTestApp"});
  }
}

void
TetraTestApp::registerApps()
{
  registerApp(TetraApp);
  registerApp(TetraTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
TetraTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  TetraTestApp::registerAll(f, af, s);
}
extern "C" void
TetraTestApp__registerApps()
{
  TetraTestApp::registerApps();
}
