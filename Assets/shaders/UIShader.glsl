#vertex
#version 430 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in float texture;
layout (location = 3) in vec4 color;

uniform mat4 V_Ortho;

out vec4 F_Color;
out vec2 F_TextureCoord;
out float F_TextureIndex;

void main() {
    F_Color = color;
    F_TextureCoord = textureCoord;
    F_TextureIndex = texture;
    gl_Position = V_Ortho * vec4(position, 0.0f, 1.0f);
}


#fragment
#version 330 core

in vec4 F_Color;
in vec2 F_TextureCoord;
in float F_TextureIndex;

uniform sampler2D F_Texture0;
uniform sampler2D F_Texture1;
uniform sampler2D F_Texture2;
uniform sampler2D F_Texture3;
uniform sampler2D F_Texture4;
uniform sampler2D F_Texture5;
uniform sampler2D F_Texture6;
uniform sampler2D F_Texture7;
uniform sampler2D F_Texture8;
uniform sampler2D F_Texture9;
uniform sampler2D F_Texture10;
uniform sampler2D F_Texture11;
uniform sampler2D F_Texture12;
uniform sampler2D F_Texture13;
uniform sampler2D F_Texture14;
uniform sampler2D F_Texture15;

out vec4 OutColor;

void main(){
    int textureIndex = int(F_TextureIndex);
    vec4 textureColor;
    switch (textureIndex){
        case -1:{
            textureColor = vec4(F_Color.rgba);
            break;
        }
        case 0:{
            textureColor = texture(F_Texture0, F_TextureCoord);
            break;
        }
        case 1:{
            textureColor = texture(F_Texture1, F_TextureCoord);
            break;
        }
        case 2:{
            textureColor = texture(F_Texture2, F_TextureCoord);
            break;
        }
        case 3:{
            textureColor = texture(F_Texture3, F_TextureCoord);
            break;
        }
        case 4:{
            textureColor = texture(F_Texture4, F_TextureCoord);
            break;
        }
        case 5:{
            textureColor = texture(F_Texture5, F_TextureCoord);
            break;
        }
        case 6:{
            textureColor = texture(F_Texture6, F_TextureCoord);
            break;
        }
        case 7:{
            textureColor = texture(F_Texture7, F_TextureCoord);
            break;
        }
        case 8:{
            textureColor = texture(F_Texture8, F_TextureCoord);
            break;
        }
        case 9:{
            textureColor = texture(F_Texture9, F_TextureCoord);
            break;
        }
        case 10:{
            textureColor = texture(F_Texture10, F_TextureCoord);
            break;
        }
        case 11:{
            textureColor = texture(F_Texture11, F_TextureCoord);
            break;
        }
        case 12:{
            textureColor = texture(F_Texture12, F_TextureCoord);
            break;
        }
        case 13:{
            textureColor = texture(F_Texture13, F_TextureCoord);
            break;
        }
        case 14:{
            textureColor = texture(F_Texture14, F_TextureCoord);
            break;
        }
        case 15:{
            textureColor = texture(F_Texture15, F_TextureCoord);
            break;
        }
    }
    if (textureIndex > -1){
        textureColor.rgb += F_Color.rgb;
    }
    OutColor = vec4(F_Color.rgb + textureColor.rgb, F_Color.a * textureColor.a);
}
