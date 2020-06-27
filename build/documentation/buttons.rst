BUTTONS
=======

Register Listing for BUTTONS
----------------------------

+------------------------------------------------+----------------------------------------+
| Register                                       | Address                                |
+================================================+========================================+
| :ref:`BUTTONS_IN <BUTTONS_IN>`                 | :ref:`0x82003000 <BUTTONS_IN>`         |
+------------------------------------------------+----------------------------------------+
| :ref:`BUTTONS_DIR <BUTTONS_DIR>`               | :ref:`0x82003004 <BUTTONS_DIR>`        |
+------------------------------------------------+----------------------------------------+
| :ref:`BUTTONS_EV_STATUS <BUTTONS_EV_STATUS>`   | :ref:`0x82003008 <BUTTONS_EV_STATUS>`  |
+------------------------------------------------+----------------------------------------+
| :ref:`BUTTONS_EV_PENDING <BUTTONS_EV_PENDING>` | :ref:`0x8200300c <BUTTONS_EV_PENDING>` |
+------------------------------------------------+----------------------------------------+
| :ref:`BUTTONS_EV_ENABLE <BUTTONS_EV_ENABLE>`   | :ref:`0x82003010 <BUTTONS_EV_ENABLE>`  |
+------------------------------------------------+----------------------------------------+

BUTTONS_IN
^^^^^^^^^^

`Address: 0x82003000 + 0x0 = 0x82003000`


    .. wavedrom::
        :caption: BUTTONS_IN

        {
            "reg": [
                {"name": "in[4:0]", "bits": 5},
                {"bits": 3},
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


BUTTONS_DIR
^^^^^^^^^^^

`Address: 0x82003000 + 0x4 = 0x82003004`


    .. wavedrom::
        :caption: BUTTONS_DIR

        {
            "reg": [
                {"name": "dir[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


BUTTONS_EV_STATUS
^^^^^^^^^^^^^^^^^

`Address: 0x82003000 + 0x8 = 0x82003008`

    This register contains the current raw level of the Event trigger.  Writes to this register have no effect.

    .. wavedrom::
        :caption: BUTTONS_EV_STATUS

        {
            "reg": [
                {"name": "arriba",  "bits": 1},
                {"name": "abajo",  "bits": 1},
                {"name": "derecha",  "bits": 1},
                {"name": "izquierda",  "bits": 1},
                {"name": "pause",  "bits": 1},
                {"bits": 3}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-----------+--------------------------------+
| Field | Name      | Description                    |
+=======+===========+================================+
| [0]   | ARRIBA    | Level of the `arriba` event    |
+-------+-----------+--------------------------------+
| [1]   | ABAJO     | Level of the `abajo` event     |
+-------+-----------+--------------------------------+
| [2]   | DERECHA   | Level of the `derecha` event   |
+-------+-----------+--------------------------------+
| [3]   | IZQUIERDA | Level of the `izquierda` event |
+-------+-----------+--------------------------------+
| [4]   | PAUSE     | Level of the `pause` event     |
+-------+-----------+--------------------------------+

BUTTONS_EV_PENDING
^^^^^^^^^^^^^^^^^^

`Address: 0x82003000 + 0xc = 0x8200300c`

    When an Event occurs, the corresponding bit will be set in this register.  To clear the Event, set the corresponding bit in this register.

    .. wavedrom::
        :caption: BUTTONS_EV_PENDING

        {
            "reg": [
                {"name": "arriba",  "bits": 1},
                {"name": "abajo",  "bits": 1},
                {"name": "derecha",  "bits": 1},
                {"name": "izquierda",  "bits": 1},
                {"name": "pause",  "bits": 1},
                {"bits": 3}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-----------+-------------------------------------------------------------------------------------+
| Field | Name      | Description                                                                         |
+=======+===========+=====================================================================================+
| [0]   | ARRIBA    | `1` if a `arriba` event occurred. This Event is triggered on a **falling** edge.    |
+-------+-----------+-------------------------------------------------------------------------------------+
| [1]   | ABAJO     | `1` if a `abajo` event occurred. This Event is triggered on a **falling** edge.     |
+-------+-----------+-------------------------------------------------------------------------------------+
| [2]   | DERECHA   | `1` if a `derecha` event occurred. This Event is triggered on a **falling** edge.   |
+-------+-----------+-------------------------------------------------------------------------------------+
| [3]   | IZQUIERDA | `1` if a `izquierda` event occurred. This Event is triggered on a **falling** edge. |
+-------+-----------+-------------------------------------------------------------------------------------+
| [4]   | PAUSE     | `1` if a `pause` event occurred. This Event is triggered on a **falling** edge.     |
+-------+-----------+-------------------------------------------------------------------------------------+

BUTTONS_EV_ENABLE
^^^^^^^^^^^^^^^^^

`Address: 0x82003000 + 0x10 = 0x82003010`

    This register enables the corresponding Events.  Write a `0` to this register to disable individual events.

    .. wavedrom::
        :caption: BUTTONS_EV_ENABLE

        {
            "reg": [
                {"name": "arriba",  "bits": 1},
                {"name": "abajo",  "bits": 1},
                {"name": "derecha",  "bits": 1},
                {"name": "izquierda",  "bits": 1},
                {"name": "pause",  "bits": 1},
                {"bits": 3}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-----------+---------------------------------------------+
| Field | Name      | Description                                 |
+=======+===========+=============================================+
| [0]   | ARRIBA    | Write a `1` to enable the `arriba` Event    |
+-------+-----------+---------------------------------------------+
| [1]   | ABAJO     | Write a `1` to enable the `abajo` Event     |
+-------+-----------+---------------------------------------------+
| [2]   | DERECHA   | Write a `1` to enable the `derecha` Event   |
+-------+-----------+---------------------------------------------+
| [3]   | IZQUIERDA | Write a `1` to enable the `izquierda` Event |
+-------+-----------+---------------------------------------------+
| [4]   | PAUSE     | Write a `1` to enable the `pause` Event     |
+-------+-----------+---------------------------------------------+

