/*!
 * @file
 * @brief
 */

#ifndef configuration_h
#define configuration_h

#define block_size 64
#define app_address 0x8300
#define flash_end_address 0x9FFF
#define app_vector_table_address app_address
#define app_crc_address app_address
#define app_size (flash_end_address - app_address + 1)
#define app_size_in_blocks (app_size / block_size)

#endif
