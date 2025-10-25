# nameserver-plus-plus

An extended DNS server that implements weighted resolution, health-based resolution, and more.

## Description

This project aims to provide a DNS server capable of handling all types of valid DNS requests. It processes and directly responds to a specific set of queries, while forwarding all other queries to an external DNS server for resolution and returning the corresponding responses. The goal is to implement custom logic for certain queries that a standard RFC 1035–compliant DNS server would not normally be able to handle.

## Project Rationale

Given how widely DNS is used in load balancing, content distribution, and latency reduction, I’ve always wondered why dynamic and custom resolutions are not standard extensions to DNS — and therefore absent from open-source implementations such as BIND. The fact that many managed services (e.g., AWS Route 53, NS1, etc.) support dynamic resolution demonstrates its importance in the industry. Since it all builds on the DNS protocol, why can’t we have the same capabilities in open-source tooling?

## Specifications

This isn’t a clone of BIND, nor is it built on top of it — hence the name “nameserver++,” not “bind++.”
The planned extensions include:

- Weighted Round-Robin Resolution

- Health-Based Resolution and Failover

- Geo-Based Resolution using EDNS

- A Library Interface for Custom Logic–Based Resolution

## Usage
