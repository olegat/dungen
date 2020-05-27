//
//  Material.cpp
//  Dissert
//
//  Created by Olivier Legat on 14/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Material.h"
#include <Engine/Graphics/Texture/Texture.h>

Material::Material() {
    diffuse = NULL;
}

Material::~Material() {
    
}
    
void Material::DeleteTextures()
{
    if (HasDiffuse()) delete diffuse;
}
