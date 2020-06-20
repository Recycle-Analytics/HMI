#!/usr/bin/env python3

from migen import *

from migen.genlib.io import CRG

from litex.build.generic_platform import *
from litex.build.xilinx import XilinxPlatform

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.cores import dna

from lcd_core import *
from btn_itrupt import btnintrupt

# IO ----------------------------------------------------------------------------------------------

_io = [

    ("clk100", 0, Pins("E3"), IOStandard("LVCMOS33")),

    ("cpu_reset", 0, Pins("C12"), IOStandard("LVCMOS33")),


    ("serial", 0,
        Subsignal("tx", Pins("D4")),
        Subsignal("rx", Pins("C4")),
        IOStandard("LVCMOS33")
    ),
    ("serial", 1,
        Subsignal("tx", Pins("F3")),
        Subsignal("rx", Pins("G3")),
        IOStandard("LVCMOS33")
    ),
    
    ("tx2", 0, Pins("G3"), IOStandard("LVCMOS33")),
    ("rx2", 0, Pins("F3"), IOStandard("LVCMOS33")),
    
    ("user_btn", 0, Pins("M18"), IOStandard("LVCMOS33")),
    ("user_btn", 1, Pins("M17"), IOStandard("LVCMOS33")),
    ("user_btn", 2, Pins("P18"), IOStandard("LVCMOS33")),
    ("user_btn", 3, Pins("P17"), IOStandard("LVCMOS33")),
    ("user_btn", 4, Pins("N17"), IOStandard("LVCMOS33")),

    ("rst",0, Pins("E16"),IOStandard("LVCMOS33")),
    ("cs",0, Pins("D14"),IOStandard("LVCMOS33")),
    ("rs",0, Pins("F13"),IOStandard("LVCMOS33")),
    ("wr",0, Pins("F16"),IOStandard("LVCMOS33")),
    ("rd",0, Pins("G13"),IOStandard("LVCMOS33")),
    ("db",0, Pins("G18 G17 D17 C17 E17 D18 F18 E18"),IOStandard("LVCMOS33")),

    ("rst1",0, Pins("H2"),IOStandard("LVCMOS33")),
    ("cs1",0, Pins("H4"),IOStandard("LVCMOS33")),
    ("rs1",0, Pins("G4"),IOStandard("LVCMOS33")),
    ("wr1",0, Pins("H1"),IOStandard("LVCMOS33")),
    ("rd1",0, Pins("G2"),IOStandard("LVCMOS33")),
    ("db1",0, Pins("E6 G6 E7 K1 J3 F6 J4 J2"),IOStandard("LVCMOS33"))
]

# Platform -----------------------------------------------------------------------------------------

class Platform(XilinxPlatform):
    default_clk_name   = "clk100"
    default_clk_period = 1e9/100e6

    def __init__(self):
        XilinxPlatform.__init__(self, "xc7a100t-csg324-1", _io, toolchain="vivado")

# Design -------------------------------------------------------------------------------------------

# Create our platform (fpga interface)
platform = Platform()

# Create our soc (fpga description)
class BaseSoC(SoCCore):
    
    interrupt_map = {
        "buttons" : 4,
    }

    interrupt_map.update(interrupt_map)

    def __init__(self, platform):
        sys_clk_freq = int(100e6)

        # SoC with CPU
        SoCCore.__init__(self, platform,
            cpu_type                 = "vexriscv",
            clk_freq                 = 100e6,
            ident                    = "Human machine interface", ident_version=True,
            integrated_rom_size      = 0x8000,
            integrated_main_ram_size = 0x4000)

        # Clock Reset Generation
        self.submodules.crg = CRG(platform.request("clk100"), ~platform.request("cpu_reset"))

        # Buttons
        button_in = Cat(*[platform.request("user_btn", i) for i in range(5)])
        self.submodules.buttons = btnintrupt(button_in)
        self.add_csr("buttons")

        #LCD
        self.submodules.lcd_core = LCD_i80(sys_clk_freq)
        self.comb += [
            platform.request("db").eq(self.lcd_core.db_),
            platform.request("cs").eq(self.lcd_core.cs_),
            platform.request("rs").eq(self.lcd_core.rs_),
            platform.request("rd").eq(self.lcd_core.rd_),
            platform.request("wr").eq(self.lcd_core.wr_),
            platform.request("rst").eq(self.lcd_core.rst_),

            platform.request("db1").eq(self.lcd_core.db_),
            platform.request("cs1").eq(self.lcd_core.cs_),
            platform.request("rs1").eq(self.lcd_core.rs_),
            platform.request("rd1").eq(self.lcd_core.rd_),
            platform.request("wr1").eq(self.lcd_core.wr_),
            platform.request("rst1").eq(self.lcd_core.rst_),
           ]
        self.add_csr("lcd_core")
        #Serial clone
        #serial = platform.request("serial", 1)
        #serial = platform.request("serial", 0)

soc = BaseSoC(platform)

# Build --------------------------------------------------------------------------------------------

builder = Builder(soc, output_dir="build", csr_csv="test/csr.csv")
builder.build()
