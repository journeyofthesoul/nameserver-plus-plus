#include <stdio.h>
#include <stdint.h>
#include <string.h>

// DNS header structure (12 bytes)
struct DNSHeader {
    uint16_t id;

    uint8_t rd     :1; // Recursion Desired
    uint8_t tc     :1; // Truncated
    uint8_t aa     :1; // Authoritative Answer
    uint8_t opcode :4;
    uint8_t qr     :1; // Query/Response

    uint8_t rcode  :4;
    uint8_t z      :3;
    uint8_t ra     :1; // Recursion Available

    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
};

// Question section structure
struct DNSQuestion {
    char qname[256]; // Domain name in dotted format
    uint16_t qtype;
    uint16_t qclass;
};

// Helper to read 16-bit values from network byte order
uint16_t read_uint16(const uint8_t* buffer, int offset) {
    return (buffer[offset] << 8) | buffer[offset + 1];
}

// Function to parse DNS header
void parse_dns_header(const uint8_t *buffer, struct DNSHeader *header) {
    header->id = read_uint16(buffer, 0);

    uint16_t flags = read_uint16(buffer, 2);
    header->qr = (flags >> 15) & 0x1;
    header->opcode = (flags >> 11) & 0xF;
    header->aa = (flags >> 10) & 0x1;
    header->tc = (flags >> 9) & 0x1;
    header->rd = (flags >> 8) & 0x1;
    header->ra = (flags >> 7) & 0x1;
    header->z  = (flags >> 4) & 0x7;
    header->rcode = flags & 0xF;

    header->qdcount = read_uint16(buffer, 4);
    header->ancount = read_uint16(buffer, 6);
    header->nscount = read_uint16(buffer, 8);
    header->arcount = read_uint16(buffer, 10);
}

// Function to parse a domain name from the DNS question section
int parse_qname(const uint8_t *buffer, int offset, char *qname) {
    int i = 0;
    int j = 0;
    while (buffer[offset] != 0) {
        uint8_t len = buffer[offset++];
        for (int k = 0; k < len; k++) {
            qname[j++] = buffer[offset++];
        }
        qname[j++] = '.';
    }
    qname[j - 1] = '\0'; // Remove last dot
    return offset + 1; // Return new offset past null byte
}

// Parse a single DNS question
int parse_question(const uint8_t *buffer, int offset, struct DNSQuestion *question) {
    offset = parse_qname(buffer, offset, question->qname);
    question->qtype = read_uint16(buffer, offset);
    offset += 2;
    question->qclass = read_uint16(buffer, offset);
    offset += 2;
    return offset;
}

int main() {
    // Example raw DNS request (query for www.example.com, type A)
    uint8_t dns_request[] = {
        0xab,0xcd,  // ID
        0x01,0x00,  // Flags
        0x00,0x01,  // QDCOUNT
        0x00,0x00,  // ANCOUNT
        0x00,0x00,  // NSCOUNT
        0x00,0x00,  // ARCOUNT
        // QNAME: 3www7example3com0
        0x03,'w','w','w',
        0x07,'e','x','a','m','p','l','e',
        0x03,'c','o','m',
        0x00,
        0x00,0x01, // QTYPE A
        0x00,0x01  // QCLASS IN
    };

    struct DNSHeader header;
    parse_dns_header(dns_request, &header);

    printf("DNS ID: 0x%x\n", header.id);
    printf("Questions: %d\n", header.qdcount);

    int offset = 12; // Header is 12 bytes
    for (int i = 0; i < header.qdcount; i++) {
        struct DNSQuestion question;
        offset = parse_question(dns_request, offset, &question);
        printf("Question %d: %s, Type: %d, Class: %d\n", i + 1, question.qname, question.qtype, question.qclass);
    }

    return 0;
}
