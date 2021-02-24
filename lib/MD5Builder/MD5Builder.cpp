#include <Arduino.h>
#include <MD5Builder.h>

uint8_t hex_char_to_byte(uint8_t c) {
    return (c >= 'a' && c <= 'f') ? (c - ((uint8_t)'a' - 0xa)) :
           (c >= 'A' && c <= 'F') ? (c - ((uint8_t)'A' - 0xA)) :
           (c >= '0' && c <= '9') ? (c - (uint8_t)'0') : 0;
}

void MD5Builder::begin(void){
    memset(_buf, 0x00, 16);
    MD5::MD5Init(&_ctx);
}

void MD5Builder::add(const uint8_t * data, const uint16_t len){
    MD5::MD5Update(&_ctx, data, len);
}


void MD5Builder::calculate(void){
    MD5::MD5Final(_buf, &_ctx);
}

void MD5Builder::getBytes(uint8_t * output) const {
    memcpy(output, _buf, 16);
}

void MD5Builder::getChars(char * output) const {
    for (uint8_t i=0; i<16; i++){
        sprintf(output + (i * 2), "%02x", _buf[i]);
    }
}

String MD5Builder::toString(void) const {
    char out[33];
    getChars(out);
    return String(out);
}
