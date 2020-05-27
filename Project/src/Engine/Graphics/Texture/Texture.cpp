//
//  Texture.cpp
//  Dissert
//
//  Created by Olivier Legat on 14/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Texture.h"

Texture::Texture()
{
    glGenTextures(1, &texture_id);
    
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture_id);
}

void Texture::SetData(int width, int height, const GLvoid * data)
{
    SetData(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void Texture::SetData(int width, int height, GLenum format, GLenum type, const GLvoid * data)
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);
    gluBuild2DMipmaps( GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
}

Texture* Texture::CreateFromFile(File file)
{
    int width, height, channels;
    unsigned char* pixels = SOIL_load_image(file.GetFullname().c_str(), &width, &height, &channels, 0);
    if (pixels == NULL)
	{
		printf("Could not load %s\n",file.GetFullname().c_str());
		return NULL;
	}
    
    int format = GL_RED;
#ifdef GL_RB
	if(channels == 2) format = GL_RB;
#endif
    if(channels == 3) format = GL_RGB;
    if(channels == 4) format = GL_RGBA;
    
    Texture* texture = new Texture();
    texture->SetData(width, height, format, GL_UNSIGNED_BYTE, pixels);
    
    return texture;
}
