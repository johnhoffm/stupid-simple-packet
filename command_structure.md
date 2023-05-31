# Telemetry and Telecommands Structure

## **\*\*This is just an example for the flatsat.**

The payload portion of the packet contains either telecommands or telemetry data. Images are not supported yet. 

Since the payload portion of each packet is 122 bytes, fields must be small to fit in a single packet. Likewise telemetry data must be small or include a sequence number for data that does not fit in a single packet.

## Telecommands

All commands take 1 byte. There is space for 16 commands in the first two bytes. The remaining space is for additional data.


| Command                | Hex   |
|------------------------|-------|
| Ping                   | 0x01  |
| Collect Data           | 0x02  |
| Request Telemetry      | 0x03  |
| System Reset           | 0x04  |
| Update System          | 0x05  |
| Self Destruct          | 0xFF  |



## Telemetry
Here packet type is always set to 0. Support for more packet types can be added by changing the packet type byte. There is a lot of unused space for new data fields.


| Data Field              | Description                               | Unit        | Data Type | Length  |
|-------------------------|-------------------------------------------|-------------|-----------|---------|
| Packet Type             | Type of packet (0)                        | -           | uint      | 1 bytes |
| Timestamp               | Time elapsed since last epoch             | Seconds     | uint      | 4 bytes |
| Last Restart Time       | Time elapsed since last restart           | Seconds     | uint      | 4 bytes |
| Last Communication Time | Time since last command received          | Seconds     | uint      | 4 bytes |
| Battery                 | Current battery level                     | Percentage  | Float     | 2 bytes |
| CPU Temperature         | Current CPU temperature                   | Celsius     | Float     | 2 bytes |
| Unused                  | Bytes left in the packet                  | -           | -         | 105 bytes|

