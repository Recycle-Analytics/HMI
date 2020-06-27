LCD_CORE
========

Register Listing for LCD_CORE
-----------------------------

+------------------------------------------+-------------------------------------+
| Register                                 | Address                             |
+==========================================+=====================================+
| :ref:`LCD_CORE_DATA <LCD_CORE_DATA>`     | :ref:`0x82003800 <LCD_CORE_DATA>`   |
+------------------------------------------+-------------------------------------+
| :ref:`LCD_CORE_ADDR <LCD_CORE_ADDR>`     | :ref:`0x82003804 <LCD_CORE_ADDR>`   |
+------------------------------------------+-------------------------------------+
| :ref:`LCD_CORE_BUSY <LCD_CORE_BUSY>`     | :ref:`0x82003808 <LCD_CORE_BUSY>`   |
+------------------------------------------+-------------------------------------+
| :ref:`LCD_CORE_START <LCD_CORE_START>`   | :ref:`0x8200380c <LCD_CORE_START>`  |
+------------------------------------------+-------------------------------------+
| :ref:`LCD_CORE_OPTION <LCD_CORE_OPTION>` | :ref:`0x82003810 <LCD_CORE_OPTION>` |
+------------------------------------------+-------------------------------------+
| :ref:`LCD_CORE_CS_ <LCD_CORE_CS_>`       | :ref:`0x82003814 <LCD_CORE_CS_>`    |
+------------------------------------------+-------------------------------------+

LCD_CORE_DATA
^^^^^^^^^^^^^

`Address: 0x82003800 + 0x0 = 0x82003800`


    .. wavedrom::
        :caption: LCD_CORE_DATA

        {
            "reg": [
                {"name": "data[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


LCD_CORE_ADDR
^^^^^^^^^^^^^

`Address: 0x82003800 + 0x4 = 0x82003804`


    .. wavedrom::
        :caption: LCD_CORE_ADDR

        {
            "reg": [
                {"name": "addr[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


LCD_CORE_BUSY
^^^^^^^^^^^^^

`Address: 0x82003800 + 0x8 = 0x82003808`


    .. wavedrom::
        :caption: LCD_CORE_BUSY

        {
            "reg": [
                {"name": "busy", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


LCD_CORE_START
^^^^^^^^^^^^^^

`Address: 0x82003800 + 0xc = 0x8200380c`


    .. wavedrom::
        :caption: LCD_CORE_START

        {
            "reg": [
                {"name": "start[1:0]", "bits": 2},
                {"bits": 6},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


LCD_CORE_OPTION
^^^^^^^^^^^^^^^

`Address: 0x82003800 + 0x10 = 0x82003810`


    .. wavedrom::
        :caption: LCD_CORE_OPTION

        {
            "reg": [
                {"name": "option", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


LCD_CORE_CS_
^^^^^^^^^^^^

`Address: 0x82003800 + 0x14 = 0x82003814`


    .. wavedrom::
        :caption: LCD_CORE_CS_

        {
            "reg": [
                {"name": "cs_", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


