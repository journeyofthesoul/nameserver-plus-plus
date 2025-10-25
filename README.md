# nameserver-plus-plus

Extended DNS Server that implements Weighted Resolution, Health-Based Resolution and more

## Description

This project aims to provide a DNS server capable of handling all types of valid DNS requests. It processes and responds directly to a specific set of queries, while forwarding all other queries to an external DNS server for resolution and returning the corresponding responses. The goal is to implement custom logic for certain queries that a standard RFC 1035–compliant DNS server would not normally be able to handle.

## Project Rationale

## Implementation Details

I do not aim to make a clone of BIND, nor make something on top of bind. Hence the name "nameserver++" and not "bind++". Current extensions that I think of adding are as follows:

- Weighted Round-Robin Resolution
- Resolution/Failover Based on Health Checks
- Geo-based Resolution using eDNS
- Library exposing resolution based on custom logic implemented in a function
