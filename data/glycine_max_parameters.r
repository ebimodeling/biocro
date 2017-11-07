# Do the calculations inside an empty list so that temporary variables are not created in .Global.
glycine_max_parameters = with(list(), {
    datalines =
    "symbol value
     timestep      1
     lat           40
     Tfrosthigh    5   
     Tfrostlow     0   
     leafdeathrate 5
     soil_clod_size 0.04
     soil_reflectance 0.2
     soil_transmission 0.01
     specific_heat 1010
     stefan_boltzman 5.67e-8  
     seneLeaf       1200
     seneStem       1200
     seneRoot       1200
     seneRhizome    850
     grain_TTc 950
     iSp                 2.5      
     chil           0.8
     SpD                0        
     nlayers            10       
     kd                 0.1     
     mrc1             0.02
     mrc2             0.03
     heightf       3        
     growth_respiration_fraction 0
     vmax1   111.2 
     alpha1  32.5
     jmax   213.2 
     Rd     1.1 
     Catm   370
     O2     210 
     b0     0.048
     b1     5   
     theta  0.7 
     water_stress_approach     1   
     tp1       400   
     tp2       600
     tp3       800
     tp4       1000
     tp5       1250
     tp6       1400  
     kStem1    0.3
     kLeaf1    0.25
     kRoot1    0.45
     kRhizome1 0
     kGrain1   0
     kStem2    0.05
     kLeaf2    0.65
     kRoot2    0.29
     kRhizome2 0.00 
     kGrain2   0.01
     kStem3    0.35
     kLeaf3    0.4
     kRoot3    0.1
     kRhizome3 0.0 
     kGrain3   0.15
     kStem4    0.3
     kLeaf4    0.24
     kRoot4    0.23
     kRhizome4 0.0
     kGrain4   0.23
     kStem5    0.16
     kLeaf5    0.01
     kRoot5    0.5
     kRhizome5 0
     kGrain5   0.33
     kStem6    0.0   
     kLeaf6    0.0
     kRoot6    0.0  
     kRhizome6 0.0  
     kGrain6   1
     rate_constant_root_enzyme_inactivation 0.09
     rate_constant_leaf 1.0
     rate_constant_stem 2.6
     rate_constant_root 2
     rate_constant_rhizome  0
     rate_constant_grain 6.1
     KmLeaf     2.5
     KmStem     6
     KmRoot     5
     KmRhizome  5
     KmGrain    7
     resistance_leaf_to_stem 0.16
     resistance_stem_to_grain 0.1
     resistance_stem_to_root 0.16
     resistance_stem_to_rhizome 1
     rate_constant_leaf_senescence 2.5
     rate_constant_stem_senescence 3.9
     rate_constant_root_senescence 1.8
     rate_constant_rhizome_senescence  0
     KmLeaf_senescence     3.9
     KmStem_senescence     6.5
     KmRoot_senescence     6
     KmRhizome_senescence  4
     remobilization_fraction 0.6
     tbase     10     
     FieldC     -1       
     WiltP      -1       
     phi1       0.01     
     phi2       10       
     soil_depth  1        
     soilType   6        
     soilLayers 1        
     soil_depths1 0
     soil_depths2 1
     wsFun      0        
     scsf       1        
     transpRes  5e+06    
     leafPotTh  -800     
     hydrDist   0        
     rfl        0.2      
     rsec       0.2      
     rsdf       0.02
     LeafN_0   2   
     kln      0.5 
     vmax_n_intercept  0   
     alphab1 0   
     kpLN     0.2
     lnb0     -5  
     lnb1     18  
     lnfun    0
     electrons_per_carboxylation    4.5
     electrons_per_oxygenation 5.25
     assimilation_multiplier    1
     kc25   406.8055
     ko25   277.1209
     gstar25    42.92
     GI_on 1
     GI_off 1
     FKF1_on 1
     FKF1_off 1
     CDF_on 1
     CDF_off 1
     FT_on 1
     FT_inhibition 1
     FT_off 1
     FKF1_timing 1
     CDF_timing 1"
    
    data_frame = read.table(textConnection(datalines), header=TRUE)
    values = as.list(data_frame$value)
    names(values) = data_frame$symbol
    values
})

