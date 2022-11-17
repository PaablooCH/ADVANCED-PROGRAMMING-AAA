#include "ModuleTexture.h"

void ModuleTexture::LoadTexture(const wchar_t* nameTexture, TexMetadata* metadata, ScratchImage& image)
{
    long success = LoadFromDDSFile(nameTexture, DDS_FLAGS_NONE, metadata, image);
    if (success < 0) {
        success = LoadFromTGAFile(nameTexture, metadata, image);
        if (success < 0) {
            LoadFromWICFile(nameTexture, WIC_FLAGS_NONE, metadata, image);
        }
    }
}
