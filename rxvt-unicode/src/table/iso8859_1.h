//
// AUTOMATICALLLY GENERATED by gentables
//
#ifdef ENCODING_DEFAULT


static uint32_t cs_iso8859_1_from_unicode (unicode_t unicode) {
    if (unicode <= 0x00ff) return unicode;
    return NOCHAR;
}

#else

#define cs_iso8859_1_from_unicode cs_unknown_from_unicode
#define cs_iso8859_1_to_unicode   cs_unknown_to_unicode

#endif
