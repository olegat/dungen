//
//  Texture.h
//  Dissert
//
//  Created by Olivier Legat on 14/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <platform.h>
#include <Engine/Core/File/File.h>

class Texture
extends Object
{
public:
    Texture();
    ~Texture();
    
    // SetData with GL_RGB and GL_UNSIGNED_BYTE defaults
    void SetData(int width, int height, const GLvoid * data);
    
    /**
     * @param width Width of the texture.
     * @param height Height of the texture.
     * @param format GL_RED​, GL_RG​, GL_RGB​, GL_BGR​, GL_RGBA​, or GL_BGRA.
     * @param type GL_UNSIGNED_BYTE​, GL_BYTE​, GL_UNSIGNED_SHORT​, GL_SHORT​, GL_UNSIGNED_INT​,
     *             GL_INT​, GL_FLOAT​, GL_UNSIGNED_BYTE_3_3_2​, GL_UNSIGNED_BYTE_2_3_3_REV​, 
     *             GL_UNSIGNED_SHORT_5_6_5​, GL_UNSIGNED_SHORT_5_6_5_REV​, GL_UNSIGNED_SHORT_4_4_4_4​,
     *             GL_UNSIGNED_SHORT_4_4_4_4_REV​, GL_UNSIGNED_SHORT_5_5_5_1​, GL_UNSIGNED_SHORT_1_5_5_5_REV​,
     *             GL_UNSIGNED_INT_8_8_8_8​, GL_UNSIGNED_INT_8_8_8_8_REV​, GL_UNSIGNED_INT_10_10_10_2​
     *             or GL_UNSIGNED_INT_2_10_10_10_REV​
     * @param data The data of the image.
     */
    void SetData(int width, int height, GLenum format, GLenum type, const GLvoid * data);
    GLuint GetTextureId() const {return texture_id;}
    
    static Texture* CreateFromFile(File filename);
    
private:
    GLuint texture_id;
};

#endif
