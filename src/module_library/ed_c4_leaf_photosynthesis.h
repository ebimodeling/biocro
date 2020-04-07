#ifndef ED_C4_LEAF_PHOTOSYNTHESIS_H
#define ED_C4_LEAF_PHOTOSYNTHESIS_H

#include "ed_leaf_photosynthesis.h"
#include "ed_leaf_photosynthesis_nr.h"  // for get_reference_inputs and get_reference_outputs

/**
 * @class ed_c4_leaf_photosynthesis
 * 
 * @brief Module describing photosynthesis at the leaf level.
 * Stomatal water stress is included by modifying stomatal conductance,
 * the Ball-Berry model is used to calculate stomatal conductance,
 * the Collatz model for C4 photosynthesis is used to calculate assimilation,
 * and the Penman-Monteith model is used to calculate leaf temperature.
 * The Newton-Raphson method is used to find self-consistent values for 
 * stomatal conductance, net assimilation, and leaf temperature.
 */
class ed_c4_leaf_photosynthesis : public ed_leaf_photosynthesis_nr::module_base
{
   public:
    ed_c4_leaf_photosynthesis(
        const state_map* input_parameters,
        state_map* output_parameters)
        : ed_leaf_photosynthesis_nr::module_base("ed_c4_leaf_photosynthesis",
                                                 string_vector{"ed_apply_stomatal_water_stress_via_conductance",
                                                               "ed_gas_concentrations",
                                                               "ed_ball_berry",
                                                               "ed_collatz_c4_assimilation",
                                                               "ed_long_wave_energy_loss",
                                                               "water_vapor_properties_from_air_temperature",
                                                               "ed_penman_monteith_leaf_temperature"},
                                                 input_parameters,
                                                 output_parameters)
    {
    }
    static string_vector get_inputs();
    static string_vector get_outputs();
};

// Get inputs from the typical modules
string_vector ed_c4_leaf_photosynthesis::get_inputs()
{
    return ed_leaf_photosynthesis::get_reference_inputs();
}

// Get outputs from the typical modules
string_vector ed_c4_leaf_photosynthesis::get_outputs()
{
    return ed_leaf_photosynthesis::get_reference_outputs();
}

#endif
