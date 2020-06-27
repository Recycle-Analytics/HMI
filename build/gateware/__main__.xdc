################################################################################
# IO constraints
################################################################################
# serial:0.tx
set_property LOC D4 [get_ports {serial_tx}]
set_property IOSTANDARD LVCMOS33 [get_ports {serial_tx}]

# serial:0.rx
set_property LOC C4 [get_ports {serial_rx}]
set_property IOSTANDARD LVCMOS33 [get_ports {serial_rx}]

# clk100:0
set_property LOC E3 [get_ports {clk100}]
set_property IOSTANDARD LVCMOS33 [get_ports {clk100}]

# cpu_reset:0
set_property LOC C12 [get_ports {cpu_reset}]
set_property IOSTANDARD LVCMOS33 [get_ports {cpu_reset}]

# user_btn:0
set_property LOC M18 [get_ports {user_btn0}]
set_property IOSTANDARD LVCMOS33 [get_ports {user_btn0}]

# user_btn:1
set_property LOC M17 [get_ports {user_btn1}]
set_property IOSTANDARD LVCMOS33 [get_ports {user_btn1}]

# user_btn:2
set_property LOC P18 [get_ports {user_btn2}]
set_property IOSTANDARD LVCMOS33 [get_ports {user_btn2}]

# user_btn:3
set_property LOC P17 [get_ports {user_btn3}]
set_property IOSTANDARD LVCMOS33 [get_ports {user_btn3}]

# user_btn:4
set_property LOC N17 [get_ports {user_btn4}]
set_property IOSTANDARD LVCMOS33 [get_ports {user_btn4}]

# db:0
set_property LOC G18 [get_ports {db[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[0]}]

# db:0
set_property LOC G17 [get_ports {db[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[1]}]

# db:0
set_property LOC D17 [get_ports {db[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[2]}]

# db:0
set_property LOC C17 [get_ports {db[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[3]}]

# db:0
set_property LOC E17 [get_ports {db[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[4]}]

# db:0
set_property LOC D18 [get_ports {db[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[5]}]

# db:0
set_property LOC F18 [get_ports {db[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[6]}]

# db:0
set_property LOC E18 [get_ports {db[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db[7]}]

# cs:0
set_property LOC D14 [get_ports {cs}]
set_property IOSTANDARD LVCMOS33 [get_ports {cs}]

# rs:0
set_property LOC F13 [get_ports {rs}]
set_property IOSTANDARD LVCMOS33 [get_ports {rs}]

# rd:0
set_property LOC G13 [get_ports {rd}]
set_property IOSTANDARD LVCMOS33 [get_ports {rd}]

# wr:0
set_property LOC F16 [get_ports {wr}]
set_property IOSTANDARD LVCMOS33 [get_ports {wr}]

# rst:0
set_property LOC E16 [get_ports {rst}]
set_property IOSTANDARD LVCMOS33 [get_ports {rst}]

# db1:0
set_property LOC E6 [get_ports {db1[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[0]}]

# db1:0
set_property LOC G6 [get_ports {db1[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[1]}]

# db1:0
set_property LOC E7 [get_ports {db1[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[2]}]

# db1:0
set_property LOC K1 [get_ports {db1[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[3]}]

# db1:0
set_property LOC J3 [get_ports {db1[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[4]}]

# db1:0
set_property LOC F6 [get_ports {db1[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[5]}]

# db1:0
set_property LOC J4 [get_ports {db1[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[6]}]

# db1:0
set_property LOC J2 [get_ports {db1[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {db1[7]}]

# cs1:0
set_property LOC H4 [get_ports {cs1}]
set_property IOSTANDARD LVCMOS33 [get_ports {cs1}]

# rs1:0
set_property LOC G4 [get_ports {rs1}]
set_property IOSTANDARD LVCMOS33 [get_ports {rs1}]

# rd1:0
set_property LOC G2 [get_ports {rd1}]
set_property IOSTANDARD LVCMOS33 [get_ports {rd1}]

# wr1:0
set_property LOC H1 [get_ports {wr1}]
set_property IOSTANDARD LVCMOS33 [get_ports {wr1}]

# rst1:0
set_property LOC H2 [get_ports {rst1}]
set_property IOSTANDARD LVCMOS33 [get_ports {rst1}]

# uart0:0.tx
set_property LOC G3 [get_ports {uart0_tx}]
set_property IOSTANDARD LVCMOS33 [get_ports {uart0_tx}]

# uart0:0.rx
set_property LOC F3 [get_ports {uart0_rx}]
set_property IOSTANDARD LVCMOS33 [get_ports {uart0_rx}]

################################################################################
# Design constraints
################################################################################

################################################################################
# Clock constraints
################################################################################


################################################################################
# False path constraints
################################################################################


set_false_path -quiet -through [get_nets -hierarchical -filter {mr_ff == TRUE}]

set_false_path -quiet -to [get_pins -filter {REF_PIN_NAME == PRE} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE || ars_ff2 == TRUE}]]

set_max_delay 2 -quiet -from [get_pins -filter {REF_PIN_NAME == C} -of_objects [get_cells -hierarchical -filter {ars_ff1 == TRUE}]] -to [get_pins -filter {REF_PIN_NAME == D} -of_objects [get_cells -hierarchical -filter {ars_ff2 == TRUE}]]