UART
====

Register Listing for UART
-------------------------

+------------------------------------------+-------------------------------------+
| Register                                 | Address                             |
+==========================================+=====================================+
| :ref:`UART_RXTX <UART_RXTX>`             | :ref:`0x82002000 <UART_RXTX>`       |
+------------------------------------------+-------------------------------------+
| :ref:`UART_TXFULL <UART_TXFULL>`         | :ref:`0x82002004 <UART_TXFULL>`     |
+------------------------------------------+-------------------------------------+
| :ref:`UART_RXEMPTY <UART_RXEMPTY>`       | :ref:`0x82002008 <UART_RXEMPTY>`    |
+------------------------------------------+-------------------------------------+
| :ref:`UART_EV_STATUS <UART_EV_STATUS>`   | :ref:`0x8200200c <UART_EV_STATUS>`  |
+------------------------------------------+-------------------------------------+
| :ref:`UART_EV_PENDING <UART_EV_PENDING>` | :ref:`0x82002010 <UART_EV_PENDING>` |
+------------------------------------------+-------------------------------------+
| :ref:`UART_EV_ENABLE <UART_EV_ENABLE>`   | :ref:`0x82002014 <UART_EV_ENABLE>`  |
+------------------------------------------+-------------------------------------+

UART_RXTX
^^^^^^^^^

`Address: 0x82002000 + 0x0 = 0x82002000`


    .. wavedrom::
        :caption: UART_RXTX

        {
            "reg": [
                {"name": "rxtx[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_TXFULL
^^^^^^^^^^^

`Address: 0x82002000 + 0x4 = 0x82002004`


    .. wavedrom::
        :caption: UART_TXFULL

        {
            "reg": [
                {"name": "txfull", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_RXEMPTY
^^^^^^^^^^^^

`Address: 0x82002000 + 0x8 = 0x82002008`


    .. wavedrom::
        :caption: UART_RXEMPTY

        {
            "reg": [
                {"name": "rxempty", "bits": 1},
                {"bits": 7},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


UART_EV_STATUS
^^^^^^^^^^^^^^

`Address: 0x82002000 + 0xc = 0x8200200c`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: UART_EV_STATUS

        {
            "reg": [
                {"name": "tx",  "bits": 1},
                {"name": "rx",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+-------------------------+
| Field | Name | Description             |
+=======+======+=========================+
| [0]   | TX   | Level of the `tx` event |
+-------+------+-------------------------+
| [1]   | RX   | Level of the `rx` event |
+-------+------+-------------------------+

UART_EV_PENDING
^^^^^^^^^^^^^^^

`Address: 0x82002000 + 0x10 = 0x82002010`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: UART_EV_PENDING

        {
            "reg": [
                {"name": "tx",  "bits": 1},
                {"name": "rx",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+------------------------------------------------------------------------------+
| Field | Name | Description                                                                  |
+=======+======+==============================================================================+
| [0]   | TX   | `1` if a `tx` event occurred. This Event is triggered on a **falling** edge. |
+-------+------+------------------------------------------------------------------------------+
| [1]   | RX   | `1` if a `rx` event occurred. This Event is triggered on a **falling** edge. |
+-------+------+------------------------------------------------------------------------------+

UART_EV_ENABLE
^^^^^^^^^^^^^^

`Address: 0x82002000 + 0x14 = 0x82002014`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: UART_EV_ENABLE

        {
            "reg": [
                {"name": "tx",  "bits": 1},
                {"name": "rx",  "bits": 1},
                {"bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+------+--------------------------------------+
| Field | Name | Description                          |
+=======+======+======================================+
| [0]   | TX   | Write a `1` to enable the `tx` Event |
+-------+------+--------------------------------------+
| [1]   | RX   | Write a `1` to enable the `rx` Event |
+-------+------+--------------------------------------+

