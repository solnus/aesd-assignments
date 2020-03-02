#include "unity.h"
#include "aesd-circular-buffer.h"
#include <string.h>

static void write_circular_buffer_packet(struct aesd_circular_buffer *buffer,
                                         const char *writestr)
{
    struct aesd_buffer_entry entry;
    entry.buffptr = writestr;
    entry.size=strlen(writestr);
    aesd_circular_buffer_add_entry(buffer,&entry);
}

static void verify_find_entry(struct aesd_circular_buffer *buffer, size_t entry_offset_byte, const char *expectstring)
{
    size_t offset_rtn=0;
    char message[250];
    struct aesd_buffer_entry *rtnentry = aesd_circular_buffer_find_entry_offset_for_fpos(buffer,
                                                entry_offset_byte,
                                                &offset_rtn);
    snprintf(message,sizeof(message),"null pointer unexpected when verifying offset %zu with expect string %s",
                                        entry_offset_byte, expectstring);
    TEST_ASSERT_NOT_NULL_MESSAGE(rtnentry,message);
    snprintf(message,sizeof(message),"entry string does not match expected value at offset %zu",
                                        entry_offset_byte);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectstring,&rtnentry->buffptr[offset_rtn],message);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE((uint32_t)rtnentry->size,(uint32_t)strlen(rtnentry->buffptr),
            "size parameter in buffer entry should match total entry length");
}

static void verify_find_entry_not_found(struct aesd_circular_buffer *buffer, size_t entry_offset_byte)
{
    size_t offset_rtn;
    char message[150];
    struct aesd_buffer_entry *rtnentry = aesd_circular_buffer_find_entry_offset_for_fpos(buffer,
                                                entry_offset_byte,
                                                &offset_rtn);
    snprintf(message,sizeof(message),"Expected null pointer when trying to validate entry offset %zu",entry_offset_byte);
    TEST_ASSERT_NULL_MESSAGE(rtnentry,message);
}

void test_circular_buffer(void)
{
    struct aesd_circular_buffer buffer;
    aesd_circular_buffer_init(&buffer);
    write_circular_buffer_packet(&buffer,"write1\n"); 
    write_circular_buffer_packet(&buffer,"write2\n"); 
    write_circular_buffer_packet(&buffer,"write3\n"); 
    write_circular_buffer_packet(&buffer,"write4\n"); 
    write_circular_buffer_packet(&buffer,"write5\n"); 
    write_circular_buffer_packet(&buffer,"write6\n"); 
    write_circular_buffer_packet(&buffer,"write7\n"); 
    write_circular_buffer_packet(&buffer,"write8\n"); 
    write_circular_buffer_packet(&buffer,"write9\n"); 
    write_circular_buffer_packet(&buffer,"write10\n"); 
    verify_find_entry(&buffer,0,"write1\n");
    verify_find_entry(&buffer,7,"write2\n");
    verify_find_entry(&buffer,14,"write3\n");
    verify_find_entry(&buffer,21,"write4\n");
    verify_find_entry(&buffer,28,"write5\n");
    verify_find_entry(&buffer,35,"write6\n");
    verify_find_entry(&buffer,42,"write7\n");
    verify_find_entry(&buffer,49,"write8\n");
    verify_find_entry(&buffer,56,"write9\n");
    verify_find_entry(&buffer,63,"write10\n");
    verify_find_entry(&buffer,70,"\n");
    verify_find_entry_not_found(&buffer,71);
    write_circular_buffer_packet(&buffer,"write11\n"); 
    verify_find_entry(&buffer,0,"write2\n");
    verify_find_entry(&buffer,7,"write3\n");
    verify_find_entry(&buffer,14,"write4\n");
    verify_find_entry(&buffer,21,"write5\n");
    verify_find_entry(&buffer,28,"write6\n");
    verify_find_entry(&buffer,35,"write7\n");
    verify_find_entry(&buffer,42,"write8\n");
    verify_find_entry(&buffer,49,"write9\n");
    verify_find_entry(&buffer,56,"write10\n");
    verify_find_entry(&buffer,64,"write11\n");
    verify_find_entry(&buffer,71,"\n");
    verify_find_entry_not_found(&buffer,72);
}
