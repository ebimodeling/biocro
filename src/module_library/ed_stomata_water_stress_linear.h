#ifndef ED_STOMATA_WATER_STRESS_LINEAR_H
#define ED_STOMATA_WATER_STRESS_LINEAR_H

#include "../framework/module.h"
#include "../framework/state_map.h"

namespace standardBML
{
/**
 * @class ed_stomata_water_stress_linear
 *
 * @brief Determine the stomata water stress factor.
 * If the soil water content is below the wilting point,
 * the stress factor takes its minimum value. If the water
 * content is at or above the field capacity, the stress
 * factor reaches its maximum of 1. Between the wilting
 * point and the field capacity, the stress factor is
 * determined by a straight line.
 */
class ed_stomata_water_stress_linear : public direct_module
{
   public:
    ed_stomata_water_stress_linear(
        state_map const& input_quantities,
        state_map* output_quantities)
        : direct_module(),

          // Get pointers to input quantities
          soil_field_capacity_ip(get_ip(input_quantities, "soil_field_capacity")),
          soil_wilting_point_ip(get_ip(input_quantities, "soil_wilting_point")),
          soil_water_content_ip(get_ip(input_quantities, "soil_water_content")),
          StomataWS_min_ip(get_ip(input_quantities, "StomataWS_min")),

          // Get pointers to output quantities
          StomataWS_op(get_op(output_quantities, "StomataWS"))
    {
    }
    static string_vector get_inputs();
    static string_vector get_outputs();
    static std::string get_name() { return "ed_stomata_water_stress_linear"; }

   private:
    // Pointers to input quantities
    const double* soil_field_capacity_ip;
    const double* soil_wilting_point_ip;
    const double* soil_water_content_ip;
    const double* StomataWS_min_ip;

    // Pointers to output quantities
    double* StomataWS_op;

    // Main operation
    void do_operation() const;
};

string_vector ed_stomata_water_stress_linear::get_inputs()
{
    return {
        "soil_field_capacity",  //
        "soil_wilting_point",   //
        "soil_water_content",   //
        "StomataWS_min"         //
    };
}

string_vector ed_stomata_water_stress_linear::get_outputs()
{
    return {
        "StomataWS"  //
    };
}

void ed_stomata_water_stress_linear::do_operation() const
{
    // Collect inputs and make calculations
    double soil_wilting_point = *soil_wilting_point_ip;
    double soil_field_capacity = *soil_field_capacity_ip;
    double soil_water_content = *soil_water_content_ip;
    double StomataWS_min = *StomataWS_min_ip;

    double StomataWS;
    if (soil_water_content < soil_wilting_point) {
        StomataWS = StomataWS_min;
    } else if (soil_water_content < soil_field_capacity) {
        const double slope = (1.0 - StomataWS_min) / (soil_field_capacity - soil_wilting_point);
        const double intercept = 1.0 - soil_field_capacity * slope;
        StomataWS = slope * soil_water_content + intercept;
    } else {
        StomataWS = 1.0;
    }

    // Update the output quantity list
    update(StomataWS_op, StomataWS);
}

}  // namespace standardBML
#endif