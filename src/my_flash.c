#include "board.h"
#include "my_flash.h"
#include "flash.h"

#define FLASH_RD_START 0x80030000
#define FLASH_WR_START 0x80010000
#define FLASH_TEST_LEN 0x08

uint32_t writebuf[2] = {0x33, 0x39};

void Test_Flash_Write(void)
{
    FLASH_Unlock();
    FLASH_Erase(FLASH_WR_START, FLASH_TEST_LEN);
    FLASH_FastProgram(FLASH_WR_START, (uint32_t)writebuf, FLASH_TEST_LEN);
    // FLASH_StopFastProgram();
    FLASH_Lock();
}

void Test_Flash_Read(void)
{
    for (uint32_t offset = 0; offset < FLASH_TEST_LEN; offset += 4)
    {
        uint32_t data = RD_REG(FLASH_WR_START + offset);
        printf("%x", data);
    }
    // uint32_t data = RD_REG(FLASH_WR_START);
}