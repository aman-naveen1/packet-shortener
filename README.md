# Packet Shortener

A C++17 packet-processing project that demonstrates three core data structures and a real payload-shortening operation.

## What changed

The original repository was a small prototype containing a linked list and a binary search tree. The upgraded version keeps those ideas but turns them into a usable packet-processing pipeline.

The original source used a singly linked list and inserted every new packet at the head, so packets were processed in reverse arrival order. It also created a BST but did not implement packet lookup. The new version fixes both issues.

## Features

- FIFO packet queue
- Memory-safe ownership with `std::unique_ptr`
- Binary Search Tree index for packet ID lookup
- Run-Length Encoding (RLE) payload compression
- Automatic decision to keep compressed data only when it is smaller
- Payload decompression and integrity check
- IPv4-style source and destination metadata
- Protocol metadata such as TCP and UDP
- Packet size statistics
- C++17
- CMake and Makefile builds
- Automated tests

## Example

Input payload:

```text
AAAAABBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCDDDDDD
```

The program detects repeated bytes and applies RLE.

The compressed representation stores each run as:

```text
[count][byte]
```

For example:

```text
AAAA -> 4A
```

The program only keeps the compressed representation when it is smaller than the original payload. This avoids making already-random or short data larger.

## Build with g++

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude \
    src/main.cpp src/packet_shortener.cpp \
    -o packet_shortener
```

Run:

```bash
./packet_shortener
```

## Build with Make

```bash
make
./packet_shortener
```

Run tests:

```bash
make test
```

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Windows

With Visual Studio and CMake:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\packet_shortener.exe
```

## Architecture

```text
                    +----------------+
                    | Incoming Packet|
                    +-------+--------+
                            |
                            v
                    +---------------+
                    |  FIFO Queue   |
                    +-------+-------+
                            |
                            v
                    +---------------+
                    | RLE Compressor|
                    +-------+-------+
                            |
                    +-------+-------+
                    |               |
             smaller?              no
                    |               |
                    v               v
              compressed          original
                    |               |
                    +-------+-------+
                            |
                            v
                    +---------------+
                    |   BST Index   |
                    |   by Packet ID|
                    +---------------+
                            |
                            v
                    +---------------+
                    | Fast Lookup   |
                    +---------------+
```

## Data structures

### FIFO Queue

Packets are processed in the same order in which they are inserted.

The queue uses `std::unique_ptr`, so packet nodes are automatically destroyed.

### Binary Search Tree

The BST stores a copy of each processed packet indexed by its ID.

Average lookup is O(log n) for a reasonably balanced tree. The current implementation is an ordinary BST, so the worst case is O(n) if IDs are inserted in a highly ordered sequence.

### RLE

RLE is useful when a payload contains repeated consecutive bytes.

For example:

```text
AAAAAABBBB
```

becomes conceptually:

```text
6A 4B
```

This implementation uses two bytes per run:

```text
[count][value]
```

The implementation uses an 8-bit count, so a single run can contain at most 255 identical bytes. Longer runs are split into multiple runs.

## Important limitation

This project does not capture or modify live Ethernet/IP packets from a network interface.

It is a packet-processing and payload-compression project. The `Packet` structure models network metadata and payload data.

A future networking layer could connect this processing pipeline to:

- PCAP files
- Linux AF_PACKET
- Linux eBPF/XDP
- Windows WFP
- a TCP/UDP application
- a TUN/TAP interface

That networking layer should be added separately from the compression and data-structure code.

## Suggested next upgrades

1. PCAP reader and writer
2. Packet parser for Ethernet + IPv4 + TCP/UDP
3. Real packet capture
4. Packet statistics
5. Configurable compression algorithms
6. Benchmarking against raw payload storage
7. Hash-table comparison against the BST
8. Multithreaded packet processing
9. Checksum-aware packet reconstruction
10. Wireshark-compatible output
