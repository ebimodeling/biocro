#ifndef ED_ABC_BLC_H
#define ED_ABC_BLC_H

#include "../framework/module.h"
#include "../framework/state_map.h"
#include "AuxBioCro.h"  // for leaf_boundary_layer_conductance_nikolov

namespace standardBML
{
/**
 * @class ed_abc_blc
 *
 * @brief This module is a wrapper for the
 * `leaf_boundary_layer_conductance_nikolov()` (BLC) function in `AuxBioCro`
 * (ABC). Currently only intended for use by Ed.
 */
class ed_abc_blc : public direct_module
{
   public:
    ed_abc_blc(
        state_map const& input_quantities,
        state_map* output_quantities)
        : direct_module(),

          // Get pointers to input quantities
          windspeed(get_input(input_quantities, "windspeed")),
          leafwidth(get_input(input_quantities, "leafwidth")),
          temperature_air(get_input(input_quantities, "temp")),
          temperature_leaf(get_input(input_quantities, "temperature_leaf")),
          conductance_stomatal_h2o(get_input(input_quantities, "conductance_stomatal_h2o")),
          mole_fraction_h2o_atmosphere(get_input(input_quantities, "mole_fraction_h2o_atmosphere")),
          atmospheric_pressure(get_input(input_quantities, "atmospheric_pressure")),
          minimum_gbw(get_input(input_quantities, "minimum_gbw")),

          // Get pointers to output quantities
          conductance_boundary_h2o_op(get_op(output_quantities, "conductance_boundary_h2o"))
    {
    }
    static string_vector get_inputs();
    static string_vector get_outputs();
    static std::string get_name() { return "ed_abc_blc"; }

   private:
    // References to input quantities
    double const& windspeed;
    double const& leafwidth;
    double const& temperature_air;
    double const& temperature_leaf;
    double const& conductance_stomatal_h2o;
    double const& mole_fraction_h2o_atmosphere;
    double const& atmospheric_pressure;
    double const& minimum_gbw;

    // Pointers to output quantities
    double* conductance_boundary_h2o_op;

    // Main operation
    void do_operation() const override;
};

string_vector ed_abc_blc::get_inputs()
{
    return {
        "windspeed",                     // m / s
        "leafwidth",                     // m
        "temp",                          // degrees C
        "temperature_leaf",              // degrees C
        "conductance_stomatal_h2o",      //  mol / m^2 / s
        "mole_fraction_h2o_atmosphere",  // dimensionless from mol / mol
        "atmospheric_pressure",          // Pa
        "minimum_gbw"                    // mol / m^2 / s
    };
}

string_vector ed_abc_blc::get_outputs()
{
    return {
        "conductance_boundary_h2o"  // mol / m^2 / s
    };
}

void ed_abc_blc::do_operation() const
{
    double constexpr volume_of_one_mole_of_air = 24.39e-3;                                    // m^3 / mol
    double const delta_t = temperature_leaf - temperature_air;                                // degrees C
    double const stomcond = conductance_stomatal_h2o * volume_of_one_mole_of_air;             // m / s
    double const water_vapor_pressure = mole_fraction_h2o_atmosphere * atmospheric_pressure;  // Pa

    double const blc = leaf_boundary_layer_conductance_nikolov(
        windspeed,
        leafwidth,
        temperature_air,
        delta_t,
        stomcond,
        water_vapor_pressure,
        minimum_gbw);  // m / s

    double const blc_mol = blc / volume_of_one_mole_of_air;  // mol / m^2 / s

    // Update the output quantity list
    update(conductance_boundary_h2o_op, blc_mol);
}

}  // namespace standardBML
#endif