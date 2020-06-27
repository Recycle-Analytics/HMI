UART_PHY
========

Register Listing for UART_PHY
-----------------------------

+------------------------------------------------------+-------------------------------------------+
| Register                                             | Address                                   |
+======================================================+===========================================+
| :ref:`UART_PHY_TUNING_WORD3 <UART_PHY_TUNING_WORD3>` | :ref:`0x82001800 <UART_PHY_TUNING_WORD3>` |
+------------------------------------------------------+-------------------------------------------+
| :ref:`UART_PHY_TUNING_WORD2 <UART_PHY_TUNING_WORD2>` | :ref:`0x82001804 <UART_PHY_TUNING_WORD2>` |
+------------------------------------------------------+-------------------------------------------+
| :ref:`UART_PHY_TUNING_WORD1 <UART_PHY_TUNING_WORD1>` | :ref:`0x82001808 <UART_PHY_TUNING_WORD1>` |
+------------------------------------------------------+-------------------------------------------+
| :ref:`UART_PHY_TUNING_WORD0 <UART_PHY_TUNING_WORD0>` | :ref:`0x8200180c <UART_PHY_TUNING_WORD0>` |
+------------------------------------------------------+-------------------------------------------+

UART_PHY_TUNING_WORD3
^^^^^^^^^^^^^^^^^^^^^

`Address: 0x82001800 + 0x0 = 0x82001800`

    Bits 24-31 of `UART_PHY_TUNING_WORD`.

    .. wavedrom::
        :caption: UART_PHY_TUNING_WORD3

        {
            "reg": [
                {"name": "tuning_word[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_PHY_TUNING_WORD2
^^^^^^^^^^^^^^^^^^^^^

`Address: 0x82001800 + 0x4 = 0x82001804`

    Bits 16-23 of `UART_PHY_TUNING_WORD`.

    .. wavedrom::
        :caption: UART_PHY_TUNING_WORD2

        {
            "reg": [
                {"name": "tuning_word[23:16]", "attr": 'reset: 75', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_PHY_TUNING_WORD1
^^^^^^^^^^^^^^^^^^^^^

`Address: 0x82001800 + 0x8 = 0x82001808`

    Bits 8-15 of `UART_PHY_TUNING_WORD`.

    .. wavedrom::
        :caption: UART_PHY_TUNING_WORD1

        {
            "reg": [
                {"name": "tuning_word[15:8]", "attr": 'reset: 127', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_PHY_TUNING_WORD0
^^^^^^^^^^^^^^^^^^^^^

`Address: 0x82001800 + 0xc = 0x8200180c`

    Bits 0-7 of `UART_PHY_TUNING_WORD`.

    .. wavedrom::
        :caption: UART_PHY_TUNING_WORD0

        {
            "reg": [
                {"name": "tuning_word[7:0]", "attr": 'reset: 90', "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


