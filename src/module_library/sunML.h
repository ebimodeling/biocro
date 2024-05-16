#ifndef SUNML_H
#define SUNML_H

#include "AuxBioCro.h"  // for MAXLAY

struct Light_profile {
    double sunlit_incident_ppfd[MAXLAY];         // micromol / (m^2 leaf) / s
    double incident_ppfd_scattered[MAXLAY];      // micromol / m^2 / s
    double shaded_incident_ppfd[MAXLAY];         // micromol / (m^2 leaf) / s
    double sunlit_absorbed_ppfd[MAXLAY];         // micromol / (m^2 leaf) / s
    double shaded_absorbed_ppfd[MAXLAY];         // micromol / (m^2 leaf) / s
    double sunlit_absorbed_shortwave[MAXLAY];    // J / (m^2 leaf) / s
    double shaded_absorbed_shortwave[MAXLAY];    // J / (m^2 leaf) / s
    double sunlit_fraction[MAXLAY];              // dimensionless
    double shaded_fraction[MAXLAY];              // dimensionless
    double height[MAXLAY];                       // m
    double canopy_direct_transmission_fraction;  // dimensionless
};

double thin_layer_absorption(
    double leaf_reflectance,    // dimensionless
    double leaf_transmittance,  // dimensionless
    double incident_light       // Light units such as `micromol / m^2 / s` or
                                //   `J / m^2 / s`
);

double thick_layer_absorption(
    double leaf_reflectance,    // dimensionless
    double leaf_transmittance,  // dimensionless
    double incident_light       // Light units such as `micromol / m^2 / s` or
                                //   `J / m^2 / s`
);

double nir_from_ppfd(
    double ppfd,                // micromol / m^2 / s
    double par_energy_content,  // J / micromol
    double par_energy_fraction  // dimensionless
);

double absorbed_shortwave(
    double incident_nir,            // J / m^2 / s
    double incident_ppfd,           // micromol / m^2 / s
    double par_energy_content,      // J / micromol
    double leaf_reflectance_par,    // dimensionless
    double leaf_transmittance_par,  // dimensionless
    double leaf_reflectance_nir,    // dimensionless
    double leaf_transmittance_nir   // dimensionless
);

double total_radiation(
    double Q_o,    // Light units such as `micromol / m^2 / s` or `J / m^2 / s`
    double k,      // dimensionless
    double alpha,  // dimensionless
    double ell     // dimensionless from m^2 leaf / m^2 ground
);

double downscattered_radiation(
    double Q_ob,   // Light units such as `micromol / m^2 / s` or `J / m^2 / s`
    double k,      // dimensionless
    double alpha,  // dimensionless
    double ell     // dimensionless from m^2 leaf / m^2 ground
);

double shaded_radiation(
    double Q_ob,           // Light units such as `micromol / m^2 / s` or `J / m^2 / s`
    double Q_od,           // same units as `Q_ob`
    double k_direct,       // dimensionless
    double k_diffuse,      // dimensionless
    double alpha_direct,   // dimensionless
    double alpha_diffuse,  // dimensionless
    double ell             // dimensionless from m^2 leaf / m^2 ground
);

struct Light_profile sunML(
    double ambient_ppfd_beam,       // micromol / (m^2 beam) / s
    double ambient_ppfd_diffuse,    // micromol / m^2 / s
    double lai,                     // dimensionless from m^2 / m^2
    int nlayers,                    // dimensionless
    double cosine_zenith_angle,     // dimensionless
    double k_diffuse,               // dimensionless
    double chil,                    // dimensionless from m^2 / m^2
    double absorptivity_direct,     // dimensionless from mol / mol
    double heightf,                 // m^-1 from m^2 leaf / m^2 ground / m height
    double par_energy_content,      // J / micromol
    double par_energy_fraction,     // dimensionless
    double leaf_transmittance_par,  // dimensionless
    double leaf_reflectance_par     // dimensionless
);

#endif
