enum CoderType:byte[Dir=Core/Coder]
{
    None = 0,

    Encoder_Begin = 0,
    Encoder_LZMA,
    Encoder_XOR ,
    Encoder_LZ4 ,
    Encoder_XXTEA,
    Encoder_Base64 ,
    Encoder_Base91,
    Encoder_Aes256,

    Decoder_Begin = 128,

    Decoder_LZMA,
    Decoder_XOR,
    Decoder_LZ4,
    Decoder_XXTEA,
    Decoder_Base64,
    Decoder_Base91,
    Decoder_Aes256,
};
