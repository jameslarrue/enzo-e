// See LICENSE_CELLO file for license and copyright information

/// @file     enzo_EnzoConfig.cpp
/// @author   James Bordner (jobordner@ucsd.edu)
/// @date     2012-10-03
/// @brief    Implementation of the EnzoConfig class 

#include "cello.hpp"
#include "enzo.hpp"

//----------------------------------------------------------------------

EnzoConfig::EnzoConfig() throw ()
  :
#ifdef CONFIG_USE_GRACKLE
  method_grackle_units(),
  method_grackle_chemistry(),
#endif
  ppm_density_floor(0.0),
  ppm_diffusion(false),
  ppm_dual_energy(false),
  ppm_dual_energy_eta_1(0.0),
  ppm_dual_energy_eta_2(0.0),
  ppm_flattening(0),
  ppm_minimum_pressure_support_parameter(0),
  ppm_number_density_floor(0.0),
  ppm_pressure_floor(0.0),
  ppm_pressure_free(false),
  ppm_steepening(false),
  ppm_temperature_floor(0.0),
  ppm_use_minimum_pressure_support(false),
  ppm_mol_weight(0.0),
  field_gamma(0.0),
  physics_cosmology(false),
  physics_cosmology_comoving_box_size(0.0),
  physics_cosmology_hubble_constant_now(0.0),
  physics_cosmology_initial_redshift(0.0),
  physics_cosmology_max_expansion_rate(0.0),
  physics_cosmology_omega_lamda_now(0.0),
  physics_cosmology_omega_matter_now(0.0),
  // EnzoInitialSedovArray[23]
  initial_sedov_rank(0),
  initial_sedov_radius_relative(0.0),
  initial_sedov_pressure_in(0.0),
  initial_sedov_pressure_out(0.0),
  initial_sedov_density(0.0),
  initial_turbulence_density(0.0),
  initial_turbulence_pressure(0.0),
  initial_turbulence_temperature(0.0),
  // EnzoProlong
  interpolation_method(""),
  // EnzoMethodHeat
  method_heat_alpha(0.0),
  // EnzoMethodNull
  method_null_dt(0.0),
  // EnzoMethodTurbulence
  method_turbulence_edot(0.0),
  method_turbulence_mach_number(0.0),
  // EnzoMethodGravity
  method_gravity_potential_field(""),
  method_gravity_density_field(""),
  // EnzoMethodGravityCg
  method_gravity_cg_iter_max(0),
  method_gravity_cg_res_tol(0.0),
  method_gravity_cg_grav_const(0.0),
  method_gravity_cg_diag_precon(false),
  method_gravity_cg_monitor_iter(0),
  // EnzoMethodGravityBiCGStab
  method_gravity_bicgstab_iter_max(0),
  method_gravity_bicgstab_res_tol(0.0),
  method_gravity_bicgstab_grav_const(0.0),
  method_gravity_bicgstab_diag_precon(false),
  method_gravity_bicgstab_monitor_iter(0),
  // EnzoMethodGravityMlat
  // EnzoMethodGravityMg0
  method_gravity_mg_type(""),
  method_gravity_mg_iter_max(0),
  method_gravity_mg_res_tol(0.0),
  method_gravity_mg_grav_const(0.0),
  method_gravity_mg_monitor_iter(0),
  method_gravity_mg_smooth(""),
  method_gravity_mg_smooth_weight(0.0),
  method_gravity_mg_smooth_pre(0),
  method_gravity_mg_smooth_coarse(0),
  method_gravity_mg_smooth_post(0),
  method_gravity_mg_restrict(""),
  method_gravity_mg_prolong(""),
  method_gravity_mg_min_level(0),
  method_gravity_mg_max_level(0),
  // EnzoInitialPm
  initial_pm_field(""),
  initial_pm_mpp(0.0),
  initial_soup_rank(0),
  initial_soup_file(""),
  initial_soup_rotate(false),

  // EnzoMethodPm
  method_pm_deposit_type(""),
  method_pm_update_max_dt(0.0)
{
  for (int i=0; i<3; i++) {
    initial_sedov_array[i] = 0;
    initial_soup_array[i]  = 0;
    initial_soup_d_pos[i]  = 0.0;
    initial_soup_d_size[i] = 0.0;
  }
}

//----------------------------------------------------------------------

EnzoConfig::~EnzoConfig() throw ()
{
}

//----------------------------------------------------------------------

void EnzoConfig::pup (PUP::er &p)
{

  Config::pup(p);

  TRACEPUP;

  // NOTE: change this function whenever attributes change

  p | ppm_density_floor;
  p | ppm_diffusion;
  p | ppm_dual_energy;
  p | ppm_dual_energy_eta_1;
  p | ppm_dual_energy_eta_2;
  p | ppm_flattening;
  p | ppm_minimum_pressure_support_parameter;
  p | ppm_number_density_floor;
  p | ppm_pressure_floor;
  p | ppm_pressure_free;
  p | ppm_steepening;
  p | ppm_temperature_floor;
  p | ppm_use_minimum_pressure_support;
  p | ppm_mol_weight;

  p | field_gamma;

  p | physics_cosmology;
  p | physics_cosmology_comoving_box_size;
  p | physics_cosmology_hubble_constant_now;
  p | physics_cosmology_initial_redshift;
  p | physics_cosmology_max_expansion_rate;
  p | physics_cosmology_omega_lamda_now;
  p | physics_cosmology_omega_matter_now;

  p | initial_sedov_rank;
  PUParray(p,initial_sedov_array,3);
  p | initial_sedov_radius_relative;
  p | initial_sedov_pressure_in;
  p | initial_sedov_pressure_out;
  p | initial_sedov_density;

  p | initial_turbulence_density;
  p | initial_turbulence_pressure;
  p | initial_turbulence_temperature;

  p | initial_pm_field;
  p | initial_pm_mpp;
  p | initial_pm_level;

  p | initial_soup_rank;
  p | initial_soup_file;
  p | initial_soup_rotate;
  PUParray(p,initial_soup_array,3);
  PUParray(p,initial_soup_d_pos,3);
  PUParray(p,initial_soup_d_size,3);

  p | interpolation_method;

  p | method_heat_alpha;

  p | method_null_dt;
  p | method_turbulence_edot;

  p | method_gravity_potential_field;
  p | method_gravity_density_field;

  p | method_gravity_cg_grav_const;
  p | method_gravity_cg_iter_max;
  p | method_gravity_cg_res_tol;
  p | method_gravity_cg_diag_precon;
  p | method_gravity_cg_monitor_iter;

  p | method_gravity_mg_type;
  p | method_gravity_mg_iter_max;
  p | method_gravity_mg_grav_const;
  p | method_gravity_mg_res_tol;
  p | method_gravity_mg_monitor_iter;
  p | method_gravity_mg_smooth;
  p | method_gravity_mg_smooth_weight;
  p | method_gravity_mg_smooth_pre;
  p | method_gravity_mg_smooth_coarse;
  p | method_gravity_mg_smooth_post;
  p | method_gravity_mg_restrict;
  p | method_gravity_mg_prolong;

  p | method_gravity_bicgstab_grav_const;
  p | method_gravity_bicgstab_iter_max;
  p | method_gravity_bicgstab_res_tol;
  p | method_gravity_bicgstab_diag_precon;
  p | method_gravity_bicgstab_monitor_iter;

  p | method_pm_deposit_type;
  p | method_pm_update_max_dt;

#ifdef CONFIG_USE_GRACKLE

  // Grackle cooling parameters

  // Units

  //  p | method_grackle_units;
  WARNING("EnzoConfig::pup",
	  "p|method_grackle_units not called");
  //  p | method_grackle_chemistry;
  WARNING("EnzoConfig::pup",
	  "p|method_grackle_chemistry not called");

#endif /* CONFIG_USE_GRACKLE */

}

//----------------------------------------------------------------------

void EnzoConfig::read(Parameters * p) throw()
{
  TRACE("BEGIN EnzoConfig::read()");

  // Read Cello parameters

  
  TRACE("EnzoCharm::read calling Config::read()");

  ((Config*)this) -> read (p);

  double floor_default = 1e-6;

  ppm_density_floor = p->value_float
    ("Method:ppm:density_floor",  floor_default);
  ppm_diffusion = p->value_logical 
    ("Method:ppm:diffusion",  false);
  ppm_dual_energy = p->value_logical 
    ("Method:ppm:dual_energy",false);
  ppm_dual_energy_eta_1 = p->value_float
    ("Method:ppm:dual_energy_eta_1", 0.001);
  ppm_dual_energy_eta_2 = p->value_float
    ("Method:ppm:dual_energy_eta_2", 0.1);
  ppm_flattening = p->value_integer
    ("Method:ppm:flattening", 3);
  ppm_minimum_pressure_support_parameter = p->value_integer
    ("Method:ppm:minimum_pressure_support_parameter",100);
  ppm_number_density_floor = p->value_float
    ("Method:ppm:number_density_floor", floor_default);
  ppm_pressure_floor = p->value_float
    ("Method:ppm:pressure_floor", floor_default);
  ppm_pressure_free = p->value_logical
    ("Method:ppm:pressure_free",false);
  ppm_steepening = p->value_logical 
    ("Method:ppm:steepening", false);
  ppm_temperature_floor = p->value_float
    ("Method:ppm:temperature_floor", floor_default);
  ppm_use_minimum_pressure_support = p->value_logical
    ("Method:ppm:use_minimum_pressure_support",false);
  ppm_mol_weight = p->value_float
    ("Method:ppm:mol_weight",0.6);


  physics_cosmology = p->value_logical ("Method:cosmology",false);
  physics_cosmology_comoving_box_size = p->value_float
    ("Method:cosmology:comoving_box_size", 64.0);
  physics_cosmology_hubble_constant_now = p->value_float
    ("Method:cosmology:hubble_constant_now",0.701);
  physics_cosmology_initial_redshift = p->value_float
    ("Method:cosmology:initial_redshift",  20.0);;
  physics_cosmology_max_expansion_rate = p->value_float
    ("Method:cosmology:max_expansion_rate", 0.01);
  physics_cosmology_omega_lamda_now = p->value_float
    ("Method:cosmology:omega_lambda_now",   0.721);
  physics_cosmology_omega_matter_now = p->value_float
    ("Method:cosmology:omega_matter_now",   0.279);

  // PM method and initialization

  method_pm_deposit_type = p->value_string ("Method:pm_deposit:type","cic");

  method_pm_update_max_dt = p->value_float 
    ("Method:pm_update:max_dt", std::numeric_limits<double>::max());
				     
  initial_pm_field        = p->value_string  ("Initial:pm:field","density");
  initial_pm_mpp          = p->value_float   ("Initial:pm:mpp",-1.0);
  initial_pm_level        = p->value_integer ("Initial:pm:level",-1);

  field_gamma = p->value_float ("Field:gamma",5.0/3.0);

  // InitialSoup initialization

  initial_soup_rank      = p->value_integer ("Initial:soup:rank",0);
  initial_soup_file      = p->value_string ("Initial:soup:file","soup.png");
  initial_soup_rotate    = p->value_logical ("Initial:soup:rotate",false);
  for (int axis=0; axis<3; axis++) {
    initial_soup_array[axis]  = p->list_value_integer
      (axis,"Initial:soup:array",1);
    initial_soup_d_pos[axis]  = p->list_value_float
      (axis,"Initial:soup:d_pos",0.0);
    initial_soup_d_size[axis] = p->list_value_float
      (axis,"Initial:soup:d_size",0.0);
  }
  
  // Sedov initialization

  TRACE1("field_gamma = %f",field_gamma);

  initial_sedov_rank = p->value_integer ("Initial:sedov:rank",0);

  initial_sedov_array[0] = p->list_value_integer (0,"Initial:sedov:array",1);
  initial_sedov_array[1] = p->list_value_integer (1,"Initial:sedov:array",1);
  initial_sedov_array[2] = p->list_value_integer (2,"Initial:sedov:array",1);

  initial_sedov_radius_relative = 
    p->value_float("Initial:sedov:radius_relative",0.1);
  initial_sedov_pressure_in = 
    p->value_float("Initial:sedov:pressure_in",1.0);
  initial_sedov_pressure_out = 
    p->value_float("Initial:sedov:pressure_out",1e-5);
  initial_sedov_density = 
    p->value_float("Initial:sedov:density",1.0);

  // Turbulence method and initialization

  initial_turbulence_density = p->value_float 
    ("Initial:turbulence:density",1.0);

  // Must specify pressure or temperature
  initial_turbulence_pressure =    p->value_float 
    ("Initial:turbulence:pressure",   0.0);
  initial_turbulence_temperature = p->value_float 
    ("Initial:turbulence:temperature",0.0);

  bool uses_turbulence = false;
  for (size_t i=0; i<method_list.size(); i++) {
    if (method_list[i] == "turbulence") uses_turbulence=true;
  }

  if (uses_turbulence) {
    ASSERT ("EnzoConfig::read",
  	    "Either initial turbulence pressure or temperature must be defined",
  	    ! ((initial_turbulence_pressure == 0.0) &&
  	       (initial_turbulence_temperature == 0.0)));
    ASSERT ("EnzoConfig::read",
  	    "Initial turbulence pressure and temperature cannot "
	    "both be defined",
  	    ! ((initial_turbulence_pressure != 0.0) &&
  	       (initial_turbulence_temperature != 0.0)));
  }

  method_turbulence_edot = p->value_float
    ("Method:turbulence:edot",-1.0);
  method_turbulence_mach_number = p->value_float 
    ("Method:turbulence:mach_number",0.0);

  interpolation_method = p->value_string 
    ("Field:interpolation_method","SecondOrderA");

  method_heat_alpha = p->value_float 
    ("Method:heat:alpha",1.0);

  method_null_dt = p->value_float 
    ("Method:null:dt",std::numeric_limits<double>::max());



  method_gravity_potential_field = p->value_string
    ("Method:gravity_cg:potential_field","potential");

  method_gravity_density_field = p->value_string
    ("Method:gravity_cg:density_field","density");

  method_gravity_cg_iter_max = p->value_integer
    ("Method:gravity_cg:iter_max",100);

  method_gravity_cg_grav_const = p->value_float
    ("Method:gravity_cg:grav_const",6.67384e-8); // default: G (cgs)

  method_gravity_cg_res_tol = p->value_float
    ("Method:gravity_cg:res_tol",1e-6);

  method_gravity_cg_diag_precon = p->value_logical
    ("Method:gravity_cg:diag_precon",false);

  method_gravity_cg_monitor_iter = p->value_integer
    ("Method:gravity_cg:monitor_iter",1);


  method_gravity_mg_type = p->value_string
    ("Method:gravity_mg:type","unknown");

  method_gravity_mg_iter_max = p->value_integer
    ("Method:gravity_mg:iter_max",10);

  method_gravity_mg_grav_const = p->value_float
    ("Method:gravity_mg:grav_const",6.67384e-8); // default: G (cgs)

  method_gravity_mg_res_tol = p->value_float
    ("Method:gravity_mg:res_tol",1e-6);

  method_gravity_mg_monitor_iter = p->value_integer
    ("Method:gravity_mg:monitor_iter",1);

  method_gravity_mg_smooth = p->value_string
    ("Method:gravity_mg:smooth","jacobi");

  method_gravity_mg_smooth_weight = p->value_float
    ("Method:gravity_mg:smooth_weight",1.0);

  method_gravity_mg_smooth_pre = p->value_integer
    ("Method:gravity_mg:smooth_pre",1);

  method_gravity_mg_smooth_coarse = p->value_integer
    ("Method:gravity_mg:smooth_coarse",1);

  method_gravity_mg_smooth_post = p->value_integer
    ("Method:gravity_mg:smooth_post",1);

  method_gravity_mg_restrict = p->value_string
    ("Method:gravity_mg:restrict","linear");

  method_gravity_mg_prolong = p->value_string
    ("Method:gravity_mg:prolong","linear");

  method_gravity_mg_min_level = p->value_integer
    ("Method:gravity_mg:min_level",0);

  method_gravity_mg_max_level = p->value_integer
    ("Method:gravity_mg:max_level",mesh_max_level);


  method_gravity_bicgstab_iter_max = p->value_integer
    ("Method:gravity_bicgstab:iter_max",100);

  method_gravity_bicgstab_grav_const = p->value_float
    ("Method:gravity_bicgstab:grav_const",6.67384e-8); // default: G (cgs)

  method_gravity_bicgstab_res_tol = p->value_float
    ("Method:gravity_bicgstab:res_tol",1e-6);

  method_gravity_bicgstab_diag_precon = p->value_logical
    ("Method:gravity_bicgstab:diag_precon",false);

  method_gravity_bicgstab_monitor_iter = p->value_integer
    ("Method:gravity_bicgstab:monitor_iter",1);



  //======================================================================

#ifdef CONFIG_USE_GRACKLE

  /// Grackle parameters

  bool uses_grackle = false;
  for (size_t i=0; i<method_list.size(); i++) {
    if (method_list[i] == "grackle") uses_grackle=true;
  }
  
  // Defaults alert PUP::er() to ignore
  method_grackle_chemistry.use_grackle = uses_grackle;

  if (uses_grackle) {

    method_grackle_units.comoving_coordinates 
      = p->value_logical ("Method:cosmology",false);

    method_grackle_units.density_units             // 1 m_H/cc
      = p->value_float("Method:grackle:density_units",1.67e-24);

    method_grackle_units.length_units              // 1 kpc
      = p->value_float("Method:grackle:length_units",3.086e21);

    method_grackle_units.time_units                // 1 Myr
      = p->value_float("Method:grackle:time_units",3.15569e13);

    method_grackle_units.a_units   // units for the expansion factor
      = p->value_float("Method:grackle:a_units",1.0);

    // computed
    method_grackle_units.velocity_units 
      = method_grackle_units.length_units / method_grackle_units.time_units;

    method_grackle_units.velocity_units = 
      method_grackle_units.length_units / method_grackle_units.time_units;

  
    //method_grackle_chemistry.set_default_chemistry_parameters();
    chemistry_data chemistry = set_default_chemistry_parameters();

    method_grackle_chemistry.Gamma = p->value_float
      ("Method:grackle:gamma",method_grackle_chemistry.Gamma);
  
    method_grackle_chemistry.with_radiative_cooling =p->value_logical
      ("Method:grackle:with_radiative_cooling",
       method_grackle_chemistry.with_radiative_cooling);

    method_grackle_chemistry.primordial_chemistry = p->value_logical
      ("Method:grackle:primordial_chemistry",
       method_grackle_chemistry.primordial_chemistry);

    method_grackle_chemistry.metal_cooling = p->value_logical
      ("Method:grackle:metal_cooling",method_grackle_chemistry.metal_cooling);

    method_grackle_chemistry.h2_on_dust = p->value_logical
      ("Method:grackle:h2_on_dust",method_grackle_chemistry.h2_on_dust);

    method_grackle_chemistry.cmb_temperature_floor = p->value_logical
      ("Method:grackle:cmb_temperature_floor",
       method_grackle_chemistry.cmb_temperature_floor);

    method_grackle_chemistry.grackle_data_file 
      = strdup(p->value_string
	       ("Method:grackle:data_file",
		method_grackle_chemistry.grackle_data_file).c_str());

    method_grackle_chemistry.cie_cooling = p->value_integer
      ("Method:grackle:cie_cooling",method_grackle_chemistry.cie_cooling);

    method_grackle_chemistry.h2_optical_depth_approximation = p->value_integer
      ("Method:grackle:h2_optical_depth_approximation",
       method_grackle_chemistry.h2_optical_depth_approximation);

    method_grackle_chemistry.photoelectric_heating = p->value_integer
      ("Method:grackle:photoelectric_heating",
       method_grackle_chemistry.photoelectric_heating);

    method_grackle_chemistry.photoelectric_heating_rate = p->value_float
      ("Method:grackle:photoelectric_heating_rate",
       method_grackle_chemistry.photoelectric_heating_rate);

    method_grackle_chemistry.UVbackground = p->value_integer
      ("Method:grackle:UVbackground",method_grackle_chemistry.UVbackground);

    // initialize chemistry data: required here since EnzoMethodGrackle may not be used

    const gr_float a_value = 
      1. / (1. + physics_cosmology_initial_redshift);

    if (initialize_chemistry_data
	(method_grackle_chemistry, method_grackle_units, a_value) == 0) {
      ERROR("EnzoMethodGrackle::EnzoMethodGrackle()",
	    "Error in initialize_chemistry_data");
    }
  }  
#endif /* CONFIG_USE_GRACKLE */

  //======================================================================

  TRACE("END   EnzoConfig::read()");
}

//======================================================================

