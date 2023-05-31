# HoffCSP Encoding and Decoding

A very simple packet encoding for UCLA Bruinspace's flatsat. This is a test and proof of concept. Do not use this for real space applications.

## Build

Use `make` to build encode and decode executables. Use `make clean` to remove executables.

## Usage
Encode and decode read from stdin and write to stdout. See test.sh and below code for an example. Data streams sent to decode must be valid packets and streams must be in multiples of 128 bytes.

``` cat data.txt | ./encode > raw_packet_data ```

``` cat raw_packet_data | ./decode > data.txt ```

## Format
The format is very simple. Each packet is 128 bytes. There are only three fields: preamble (0xFFFFFFFF), length, and payload. Telecommands and telemetry go inside the payload section. Information on them can be found in [command_structure.md](command_structure.md).

<!-- ChatGPT generated ASCII -->
<!-- "give me ascii art of a table similar to Ipv4's packet header, but for the following struct: <code>" -->
```
     0               1               2               3
+---------------+---------------+---------------+---------------+
|                   Preamble = 0xFFFFFFFF                       |
+-------------------------------+---------------+---------------+
|              Length           |                               |
+-------------------------------+                               |
|                                                               |
|                            Payload                            |
|                                                               |
|                            (122 bytes)                        |
|                                                               |
+-------------------------------+---------------+---------------+
```

### TODO
- add CRC32 field for error detection and recovery
- add flag to encode/decode to save packet/data to files