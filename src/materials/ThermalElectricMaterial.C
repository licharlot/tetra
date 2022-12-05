// This file is part of the MOOSE framework
// https://www.mooseframework.org
//
// All rights reserved, see COPYRIGHT for full restrictions
// https://github.com/idaholab/moose/blob/master/COPYRIGHT
//
// Licensed under LGPL 2.1, please see LICENSE for details
// https://www.gnu.org/licenses/lgpl-2.1.html

#include "ThermalElectricMaterial.h"
#include "Function.h"
#include "libmesh/quadrature.h"

registerMooseObject("TetraApp", ThermalElectricMaterial);
registerMooseObject("TetraApp", ADThermalElectricMaterial);

template <bool is_ad>
InputParameters
ThermalElectricMaterialTempl<is_ad>::validParams()
{
  InputParameters params = Material::validParams();

  params.addCoupledVar("temp", "Coupled Temperature");
  params.addParam<Real>("seebeck", "Seebeck value");
  params.addParam<FunctionName>(
      "seebeck_temperature_function", "", "Seebeck as a function of temperature.");
  params.addParam<Real>("resistance", "Resistance value");
  params.addParam<FunctionName>(
      "resistance_temperature_function", "", "Electrical Resistance as a function of temperature.");

  params.addClassDescription("General Purpose Thermal Electric Material with inputs from Seebeck");

  return params;
}

template <bool is_ad>
ThermalElectricMaterialTempl<is_ad>::ThermalElectricMaterialTempl(
    const InputParameters & parameters)
  : Material(parameters),

    _has_temp(isCoupled("temp")),
    _temperature(_has_temp ? coupledGenericValue<is_ad>("temp") : genericZeroValue<is_ad>()),
    // checking if value is valid and assigned default to 0 if not given

    // Seebeck
    _my_seebeck(isParamValid("seebeck") ? getParam<Real>("seebeck") : 0),
    _seebeck(declareGenericProperty<Real, is_ad>("seebeck")),
    _seebeck_temperature_function(getParam<FunctionName>("seebeck_temperature_function") != ""
                                      ? &getFunction("seebeck_temperature_function")
                                      : nullptr),

    // resistance
    _my_resistance(isParamValid("resistance") ? getParam<Real>("resistance") : 0),
    _resistance(declareGenericProperty<Real, is_ad>("resistance")),
    _resistance_temperature_function(getParam<FunctionName>("resistance_temperature_function") != ""
                                         ? &getFunction("resistance_temperature_function")
                                         : nullptr)
{
  // check if seebeck and seebeck temperature function is both defined
  if (_seebeck_temperature_function && !_has_temp)
    paramError("Seebeck_temperature_function",
               "Must couple with temperature if using seebeck temperature function");

  if (isParamValid("seebeck") && _seebeck_temperature_function)
    mooseError("Cannot define both seebeck and seebeck_temperature_function");
  // check if resistance and resistance function is both defined

  if (_resistance_temperature_function && !_has_temp)
    paramError("Resistance_temperature_function",
               "Must couple with temperature if using resistance_temperature_function");

  if (isParamValid("resistance") && _resistance_temperature_function)
    mooseError("Cannot define both resistance and resistance_temperature_function");
}

template <bool is_ad>
void
ThermalElectricMaterialTempl<is_ad>::computeQpProperties()
{
  // loop through all qp points
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
    auto qp_temperature = _temperature[qp];
    // checking if temperature is below zero
    if (_has_temp)
    {
      if (qp_temperature < 0)
      {
        std::stringstream msg;
        msg << "WARNING:  In HeatConductionMaterial:  negative temperature!\n"
            << "\tResetting to zero.\n"
            << "\t_qp: " << qp << "\n"
            << "\ttemp: " << qp_temperature << "\n"
            << "\telem: " << _current_elem->id() << "\n"
            << "\tproc: " << processor_id() << "\n";
        mooseWarning(msg.str());
        qp_temperature = 0;
      }
    }
    // if seebeck is a function of temperature
    if (_seebeck_temperature_function)
    {
      _seebeck[qp] = _seebeck_temperature_function->value(qp_temperature);
    }
    else
    {
      _seebeck[qp] = _my_seebeck;
    }

    if (_resistance_temperature_function)
    {
      _resistance[qp] = _resistance_temperature_function->value(qp_temperature);
    }
    else
    {
      _resistance[qp] = _my_resistance;
    }
  }
}

template class ThermalElectricMaterialTempl<false>;
template class ThermalElectricMaterialTempl<true>;
