
# Create Project

create_project -force -name __main__ -part xc7a100t-csg324-1
set_msg_config -id {Common 17-55} -new_severity {Warning}

# Add Sources

read_verilog {/home/lcdiazf/.local/lib/python3.8/site-packages/pythondata_cpu_vexriscv/verilog/VexRiscv.v}
read_verilog {/home/lcdiazf/Documents/Embebidos/HMI/build/gateware/__main__.v}

# Add EDIFs


# Add IPs


# Add constraints

read_xdc __main__.xdc
set_property PROCESSING_ORDER EARLY [get_files __main__.xdc]

# Add pre-synthesis commands


# Synthesis

synth_design -directive default -top __main__ -part xc7a100t-csg324-1

# Synthesis report

report_timing_summary -file __main___timing_synth.rpt
report_utilization -hierarchical -file __main___utilization_hierarchical_synth.rpt
report_utilization -file __main___utilization_synth.rpt

# Optimize design

opt_design -directive default

# Add pre-placement commands


# Placement

place_design -directive default

# Placement report

report_utilization -hierarchical -file __main___utilization_hierarchical_place.rpt
report_utilization -file __main___utilization_place.rpt
report_io -file __main___io.rpt
report_control_sets -verbose -file __main___control_sets.rpt
report_clock_utilization -file __main___clock_utilization.rpt

# Add pre-routing commands


# Routing

route_design -directive default
phys_opt_design -directive default
write_checkpoint -force __main___route.dcp

# Routing report

report_timing_summary -no_header -no_detailed_paths
report_route_status -file __main___route_status.rpt
report_drc -file __main___drc.rpt
report_timing_summary -datasheet -max_paths 10 -file __main___timing.rpt
report_power -file __main___power.rpt

# Bitstream generation

write_bitstream -force __main__.bit 

# End

quit