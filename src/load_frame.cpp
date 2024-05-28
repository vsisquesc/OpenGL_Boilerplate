bool load_frame( int* width ,int* height, int* channels, unsigned char ** data ){
    *width = 640;
    *height = 480;
    *channels = 3;
    *data = new unsigned char[ *width * *height * *channels];

    auto ptr = *data;
    for(int x = 0; x < *width; ++x){
        for(int y = 0; y < *height; ++y){
            *ptr++ = 0xff;
            *ptr++ = 0x00;
            *ptr++ = 0x00;
        }
    }
    return true;
}
