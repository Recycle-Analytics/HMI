UART0
=====

Register Listing for UART0
--------------------------

+--------------------------------------------+--------------------------------------+
| Register                                   | Address                              |
+============================================+======================================+
| :ref:`UART0_RXTX <UART0_RXTX>`             | :ref:`0x82004000 <UART0_RXTX>`       |
+--------------------------------------------+--------------------------------------+
| :ref:`UART0_TXFULL <UART0_TXFULL>`         | :ref:`0x82004004 <UART0_TXFULL>`     |
+--------------------------------------------+--------------------------------------+
| :ref:`UART0_RXEMPTY <UART0_RXEMPTY>`       | :ref:`0x82004008 <UART0_RXEMPTY>`    |
+--------------------------------------------+--------------------------------------+
| :ref:`UART0_EV_STATUS <UART0_EV_STATUS>`   | :ref:`0x8200400c <UART0_EV_STATUS>`  |
+--------------------------------------------+--------------------------------------+
| :ref:`UART0_EV_PENDING <UART0_EV_PENDING>` | :ref:`0x82004010 <UART0_EV_PENDING>` |
+--------------------------------------------+--------------------------------------+
| :ref:`UART0_EV_ENABLE <UART0_EV_ENABLE>`   | :ref:`0x82004014 <UART0_EV_ENABLE>`  |
+--------------------------------------------+--------------------------------------+

UART0_RXTX
^^^^^^^^^^

`Address: 0x82004000 + 0x0 = 0x82004000`


    .. wavedrom::
        :caption: UART0_RXTX

        {
            "reg": [
                {"name": "rxtx[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART0_TXFULL
^^^^^^^^^^^^

`Address: 0x82004000 + 0x4 = 0x82004004`


    .. wavedrom::
        :caption: UART0_TXFULL

        {
            "reg": [
                {"name": "txfull", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART0_RXEMPTY
^^^^^^^^^^^^^

`Address: 0x82004000 + 0x8 = 0x82004008`


    .. wavedrom::
        :caption: UART0_RXEMPTY

        {
            "reg": [
                {"name": "rxempty", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART0_EV_STATUS
^^^^^^^^^^^^^^^

`Address: 0x82004000 + 0xc = 0x8200400c`


    .. wavedrom::
        :caption: UART0_EV_STATUS

        {
            "reg": [
                {"name": "ev_status[1:0]", "bits": 2},
                {"bits": 6},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART0_EV_PENDING
^^^^^^^^^^^^^^^^

`Address: 0x82004000 + 0x10 = 0x82004010`


    .. wavedrom::
        :caption: UART0_EV_PENDING

        {
            "reg": [
                {"name": "ev_pending[1:0]", "bits": 2},
                {"bits": 6},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART0_EV_ENABLE
^^^^^^^^^^^^^^^

`Address: 0x82004000 + 0x14 = 0x82004014`


    .. wavedrom::
        :caption: UART0_EV_ENABLE

        {
            "reg": [
                {"name": "ev_enable[1:0]", "bits": 2},
                {"bits": 6},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


