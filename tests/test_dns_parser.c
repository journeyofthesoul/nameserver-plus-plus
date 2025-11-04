#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/dns_parser.h"

/* Example test function */
void test_parse_uint16(void) {
    uint8_t buffer[] = { 0x12, 0x34 };
    uint16_t val = read_uint16(buffer, 0);
    CU_ASSERT_EQUAL(val, 0x1234);
}

/* Another simple test */
void test_parse_qname_basic(void) {
    // "www.example.com" in DNS label format: 3www7example3com0
    uint8_t qname_data[] = { 3,'w','w','w',7,'e','x','a','m','p','l','e',3,'c','o','m',0 };
    char output[256];
    int offset = parse_qname(qname_data, 0, output);
    CU_ASSERT_STRING_EQUAL(output, "www.example.com");
    CU_ASSERT_EQUAL(offset, 17);
}

int main() {
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("DNS Parser Tests", 0, 0);
    CU_add_test(suite, "read_uint16()", test_parse_uint16);
    CU_add_test(suite, "parse_qname()", test_parse_qname_basic);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
