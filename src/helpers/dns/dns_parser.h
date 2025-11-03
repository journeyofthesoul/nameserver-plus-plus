#ifndef DNS_PARSER_H
#define DNS_PARSER_H

#include <stdint.h>

/**
 * @brief DNS packet header (12 bytes)
 *
 * Represents the fixed header portion of a DNS packet.
 */
struct DNSHeader {
    uint16_t id;       /**< Identifier for the DNS request/response */

    uint8_t rd     :1; /**< Recursion Desired flag */
    uint8_t tc     :1; /**< Truncated flag */
    uint8_t aa     :1; /**< Authoritative Answer flag */
    uint8_t opcode :4; /**< Operation code */
    uint8_t qr     :1; /**< Query/Response flag */

    uint8_t rcode  :4; /**< Response code */
    uint8_t z      :3; /**< Reserved */
    uint8_t ra     :1; /**< Recursion Available flag */

    uint16_t qdcount;  /**< Number of questions */
    uint16_t ancount;  /**< Number of answers */
    uint16_t nscount;  /**< Number of authority records */
    uint16_t arcount;  /**< Number of additional records */
};

/**
 * @brief DNS question section
 *
 * Represents a single question in a DNS query.
 */
struct DNSQuestion {
    char qname[256];   /**< Domain name in dotted format (e.g., www.example.com) */
    uint16_t qtype;    /**< Query type (A, AAAA, MX, etc.) */
    uint16_t qclass;   /**< Query class (usually IN for internet) */
};

/**
 * @brief Set the DO (DNSSEC OK) flag for DNS queries
 *        (optional, for future DNSSEC support)
 */
// void dns_set_dnssec_flag(...); // placeholder for extension

/**
 * @brief Parse the DNS header from a raw buffer
 *
 * @param buffer Pointer to the start of the DNS packet
 * @param header Pointer to DNSHeader struct to populate
 */
void parse_dns_header(const uint8_t *buffer, struct DNSHeader *header);

/**
 * @brief Parse a domain name (QNAME) from DNS packet format to dotted string
 *
 * @param buffer Pointer to the DNS packet
 * @param offset Offset in buffer where QNAME starts
 * @param qname Output buffer to store the dotted domain name
 * @return New offset in buffer immediately after the QNAME
 */
int parse_qname(const uint8_t *buffer, int offset, char *qname);

/**
 * @brief Parse a single DNS question from a DNS packet
 *
 * @param buffer Pointer to the DNS packet
 * @param offset Offset in buffer where question starts
 * @param question Pointer to DNSQuestion struct to populate
 * @return New offset in buffer immediately after the question section
 */
int parse_question(const uint8_t *buffer, int offset, struct DNSQuestion *question);

/**
 * @brief Read a 16-bit unsigned integer from buffer in network byte order
 *
 * @param buffer Pointer to the DNS packet
 * @param offset Offset in buffer to read from
 * @return 16-bit unsigned integer in host byte order
 */
uint16_t read_uint16(const uint8_t* buffer, int offset);

#endif // DNS_PARSER_H
