#include "ModuleTexture.h"
#include "Application.h"
#include "ModuleEditor.h"

void ModuleTexture::LoadTexture(const wchar_t* nameTexture, TexMetadata* metadata, ScratchImage& image)
{
    long success = LoadFromDDSFile(nameTexture, DDS_FLAGS_NONE, metadata, image);
    if (success < 0) {
        success = LoadFromTGAFile(nameTexture, metadata, image);
        if (success < 0) {
            LoadFromWICFile(nameTexture, WIC_FLAGS_NONE, metadata, image);
        }
    }
    App->editor->logs.emplace_back("Texture loaded");
}
