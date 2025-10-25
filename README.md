# nameserver-plus-plus

Extended DNS Server that implements Weighted Resolution, Health-Based Resolution and more

## Description

This project aims to provide a DNS server capable of handling all types of valid DNS requests. It processes and responds directly to a specific set of queries, while forwarding all other queries to an external DNS server for resolution and returning the corresponding responses. The goal is to implement custom logic for certain queries that a standard RFC 1035–compliant DNS server would not normally be able to handle.

## Project Rationale

For something that is widely used in load-balancing solutions, content distribution and latency reduction, it has been a big question to me why dynamic, and custom resolutions are not supported extensions to the current DNS standard, and thus de-facto open source implementations of it such as BIND. The fact that a lot of managed services - AWS Route 53, NS1, etc., supports dynamic resolutions is testament for its need in the industry. It's all based on the DNS protocol, why can't we have it in Open Source tooling ?

## Specifications

This isn't a clone of BIND nor is it something on top of it, hence the name "nameserver++", not "bind++". Current extensions that I think of adding are as follows:

- Weighted Round-Robin Resolution
- Resolution/Failover Based on Health Checks
- Geo-based Resolution using eDNS
- Library exposing resolution based on custom logic implemented in a function

## Usage
