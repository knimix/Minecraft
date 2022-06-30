#vertex
#version 430 core

layout (std430, binding=0) buffer blockData
{
    int data[];
};
layout (std430, binding=1) buffer transparentBlockData
{
    int data2[];
};

vec3 GetFrontFace(int vertexID,int width, int height){
    float scale = 1.0 / 16.0;

    vec3[4] face = {
    vec3(0, 0, 1),
    vec3(scale * width, 0, 1),
    vec3(0, scale * height, 1),
    vec3(scale * width, scale * height, 1)};
    return face[vertexID];
}
vec2 GetFrontFaceTexures(int vertexID,int width, int height){
    float scale = 1.0 / 32.0;
    vec2[4] textures = {
    vec2(0  , 1),
    vec2(1 - scale * width, 1),
    vec2(0, 0 + scale*height),
    vec2(1 - scale * width, 0 + scale*height),
    };
    return textures[vertexID];


}

uniform int chunkX;
uniform int chunkZ;

uniform mat4 view;
uniform mat4 projection;

const  float scale = 1.0 / 16.0;

uniform vec3 lightPosition = vec3(0.5,40000.f,0.5);


const vec3 CubeMeshNormals[8] = {
vec3(0, 0, -1),
vec3(0, 0, 1),
vec3(-1, 0, 0),
vec3(1, 0, 0),
vec3(0, 1, 0),
vec3(0, -1, 0),
vec3(0, 1, 0),
vec3(0, 1, 0),
};

const vec2 CubeMeshTexures[4] = {
vec2(0, 1),
vec2(1, 1),
vec2(0, 0),
vec2(1, 0),
};

out vec2 TextureCoords;
out vec3 Normals;
out vec3 LightVector;
out float TextureIndex;
out float faceID;

vec2 GenerateTextureCoords(int vertexID, vec2 offset,int width, int height){
    if(vertexID == 0) return vec2(0,1) + offset;
    if(vertexID == 1) return vec2(width*scale,1) + offset;
    if(vertexID == 2) return vec2(0,-(height -16) * scale) + offset;
    if(vertexID == 3) return vec2(width*scale,-(height -16) * scale) + offset;
    return vec2(0);
}
vec3 GenerateFrontFace(int vertexID, vec3 offset,vec2 dimension){
    offset = vec3(vec2(offset),-offset.z) * scale;
    if(vertexID == 0) return vec3(0, 0, 1) + offset;
    if(vertexID == 1) return vec3(dimension.x * scale, 0, 1) + offset;
    if(vertexID == 2) return vec3(0, dimension.y * scale, 1) + offset;
    if(vertexID == 3) return vec3(dimension.x * scale, dimension.y * scale, 1 ) + offset;
    return vec3(0);
}
vec3 GenerateBackFace(int vertexID, vec3 offset,vec2 dimension){
    offset = vec3(-offset.x, vec2(offset.yz)) * scale;
    if(vertexID == 0) return vec3(1,0,0) + offset;
    if(vertexID == 1) return vec3(1-dimension.x * scale,0,0) + offset;
    if(vertexID == 2) return vec3(1, dimension.y * scale,0) + offset;
    if(vertexID == 3) return vec3(1-dimension.x * scale, dimension.y * scale,0) + offset;
    return vec3(0);
}
vec3 GenerateLeftFace(int vertexID, vec3 offset, vec2 dimension){
    offset = offset.zyx * scale;
    if(vertexID == 0) return vec3(0, 0, 0) + offset;
    if(vertexID == 1) return vec3(0, 0, dimension.x * scale) + offset;
    if(vertexID == 2) return vec3(0, dimension.y * scale, 0) + offset;
    if(vertexID == 3) return vec3(0, dimension.y * scale, dimension.x * scale) + offset;
    return vec3(0);
}
vec3 GenerateRightFace(int vertexID, vec3 offset, vec2 dimension){
    offset = vec3( -offset.z,offset.y, -offset.x) * scale;
    if(vertexID == 0) return vec3(1, 0, 1) + offset;
    if(vertexID == 1) return vec3(1, 0, 1 - dimension.x * scale) + offset;
    if(vertexID == 2) return vec3(1, dimension.y * scale, 1) + offset ;
    if(vertexID == 3) return vec3(1, dimension.y * scale, 1 - dimension.x * scale) + offset;
    return vec3(0);
}
vec3 GenerateTopFace(int vertexID, vec3 offset, vec2 dimension){
    offset = vec3( offset.x,-offset.z, -offset.y) * scale;
    if(vertexID == 0) return vec3(0,1,1) + offset;
    if(vertexID == 1) return vec3(dimension.x * scale,1,1)+ offset;
    if(vertexID == 2) return vec3(0,1,1-dimension.y * scale)+ offset;
    if(vertexID == 3) return vec3(dimension.x * scale,1,1-dimension.y * scale) + offset;
    return vec3(0);
}
vec3 GenerateBottomFace(int vertexID, vec3 offset, vec2 dimension){
    offset *= scale;
    if(vertexID == 0) return vec3(0, 0, 0) + offset;
    if(vertexID == 1) return vec3(dimension.x * scale, 0, 0) + offset;
    if(vertexID == 2) return vec3(0, 0, dimension.y * scale) + offset;
    if(vertexID == 3) return vec3(dimension.x * scale, 0, dimension.y * scale) + offset;
    return vec3(0);
}
vec3 GenerateRotatedLeftFace(int vertexID, vec3 offset, vec2 dimension){
    float diagonal = sqrt(2.0) * scale;
    if(vertexID == 0) return vec3(0 +diagonal, 0, 1 -diagonal) + offset * diagonal;
    if(vertexID == 1) return vec3(1 -diagonal, 0, 0 +diagonal) + offset * diagonal;
    if(vertexID == 2) return vec3(0 +diagonal, 1, 1 -diagonal) + offset * diagonal ;
    if(vertexID == 3) return vec3(1 -diagonal, 1, 0 +diagonal) + offset * diagonal;
    return vec3(0);
}
vec3 GenerateRotatedRightFace(int vertexID, vec3 offset, vec2 dimension){
    float diagonal = sqrt(2.0) * scale;
    if(vertexID == 0) return vec3(0+diagonal,0,0+diagonal) + offset * diagonal;
    if(vertexID == 1) return vec3(1-diagonal,0,1-diagonal) + offset * diagonal;
    if(vertexID == 2) return vec3(0+diagonal,1,0+diagonal) + offset * diagonal ;
    if(vertexID == 3) return vec3(1-diagonal,1,1-diagonal) + offset * diagonal;
    return vec3(0);
}

void main() {

    int blockX = (data[gl_InstanceID * 3] & 0xFF000000) >> 24 ;
    int blockY = (data[gl_InstanceID * 3] & 0x00FF0000) >> 16 ;
    int blockZ = (data[gl_InstanceID * 3] & 0x0000FF00) >> 8 ;
    int face = (data[gl_InstanceID * 3] & 0x000000F0) >> 4 ;
    int lightLevel = (data[gl_InstanceID * 3] & 0x0000000F) >> 0 ;
    int textureIndex = data[gl_InstanceID * 3 + 1] >> 24 & 0xff;
    int width =  data[gl_InstanceID * 3 + 1] >> 16 & 0xff;
    int height = data[gl_InstanceID * 3 + 1] >> 8 & 0xff;
    int offsetX = (data[gl_InstanceID * 3 + 2] & 0xFF000000) >> 24;
    int offsetY = (data[gl_InstanceID * 3 + 2] & 0x00FF0000) >> 16 ;
    int offsetZ = (data[gl_InstanceID * 3 + 2] & 0x0000FF00) >> 8 ;
    if (offsetX >= 128) offsetX += 0xFFFFFF00;
    if (offsetY >= 128) offsetY += 0xFFFFFF00;
    if (offsetZ >= 128) offsetZ += 0xFFFFFF00;


    if(data.length() > 0){
        vec3 blockOffset =  vec3((chunkX*32 + blockX),blockY, (chunkZ*32) + blockZ);
        TextureCoords = GenerateTextureCoords(gl_VertexID, vec2(offsetX * scale, -offsetY * scale), width, height);

        vec3 faceCoord;
        if(face == 0) faceCoord = GenerateFrontFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 1) faceCoord = GenerateBackFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 2) faceCoord = GenerateLeftFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 3) faceCoord = GenerateRightFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 4) faceCoord = GenerateTopFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 5) faceCoord = GenerateBottomFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 6) faceCoord = GenerateRotatedLeftFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;
        if(face == 7) faceCoord = GenerateRotatedRightFace(gl_VertexID, vec3(offsetX, offsetY, offsetZ), vec2(width, height)) + blockOffset;



        vec4 position = projection * view * vec4(faceCoord, 1);
        Normals = CubeMeshNormals[face];
        LightVector = lightPosition - position.xyz;
        TextureIndex = textureIndex;
        faceID = face;
        gl_Position =  position;
    }

}


#fragment
#version 430 core
#extension GL_EXT_texture_array : enable

in vec2 TextureCoords;
in vec3 Normals;
in vec3 LightVector;
in float TextureIndex;
in float faceID;

out vec4 outColor;
uniform sampler2DArray image;

vec3 LightColor = vec3(1.0,1.0,1.0);


void main(){
    vec3 unitNormal = normalize(Normals);
    vec3 unitLightVector = normalize(LightVector);

    float nDotl = dot(unitNormal,unitLightVector);
    float brightness = max(nDotl,0.3);
    vec3 diffuse = brightness * LightColor;


    if(TextureIndex == 1 && faceID == 4){
        outColor = vec4(diffuse,1.0) * texture(image,vec3(TextureCoords,TextureIndex));
    }else{
        outColor = vec4(diffuse,1.0) * texture(image,vec3(TextureCoords,TextureIndex));

    }
    if(outColor.a < 0.5) { discard; }
}
