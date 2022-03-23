#vertex
#version 430 core

layout (std430, binding=0) buffer blockData
{
    int data[];
};

uniform int chunkX;
uniform int chunkZ;

uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition = vec3(0.5,400.f,0.5);

const vec3 CubeMeshData[6][4] = {
{
vec3(0, 0, 1),
vec3(1, 0, 1),
vec3(0, 1, 1),
vec3(1, 1, 1),
},
{
vec3(1, 0, 0),
vec3(0, 0, 0),
vec3(1, 1, 0),
vec3(0, 1, 0),
},
{
vec3(0, 0, 0),
vec3(0, 0, 1),
vec3(0, 1, 0),
vec3(0, 1, 1),
},
{
vec3(1, 0, 1),
vec3(1, 0, 0),
vec3(1, 1, 1),
vec3(1, 1, 0),
},
{
vec3(0, 1, 1),
vec3(1, 1, 1),
vec3(0, 1, 0),
vec3(1, 1, 0),
},
{
vec3(0, 0, 0),
vec3(1, 0, 0),
vec3(0, 0, 1),
vec3(1, 0, 1),
}
};
const vec3 CubeMeshNormals[6] = {
vec3(0, 0, -1),
vec3(0, 0, 1),
vec3(-1, 0, 0),
vec3(1, 0, 0),
vec3(0, 1, 0),
vec3(0, -1, 0)
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
out float blockID;
out float faceID;

void main() {

    int blockX = data[gl_InstanceID * 2] >> 24 & 0xff;
    int blockY = data[gl_InstanceID * 2] >> 16 & 0xff;
    int blockZ = data[gl_InstanceID * 2] >> 8 & 0xff;
    int face = data[gl_InstanceID * 2] >> 0 & 0xff;
    int blockType = int(data[gl_InstanceID * 2 + 1]) >> 24 & 0xff;
    int lightLevel = int(data[gl_InstanceID * 2 + 1]) >> 16 & 0xff;

    if(data.length() > 0){
        vec4 position = projection * view * vec4(CubeMeshData[face][gl_VertexID] + vec3((chunkX*16 + blockX),blockY, (chunkZ*16) + blockZ), 1);
        TextureCoords = CubeMeshTexures[gl_VertexID];
        Normals = CubeMeshNormals[face];
        LightVector = lightPosition - position.xyz;
        blockID = blockType;
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
in float blockID;
in float faceID;

out vec4 outColor;
uniform sampler2DArray image;

vec3 LightColor = vec3(1.0,1.0,1.0);


void main(){
   // outColor = vec4(1.0);s
    vec3 unitNormal = normalize(Normals);
    vec3 unitLightVector = normalize(LightVector);

    float nDotl = dot(unitNormal,unitLightVector);
    float brightness = max(nDotl,0.3);
    vec3 diffuse = brightness * LightColor;


    if(blockID == 1 && faceID == 4){
        outColor = vec4(diffuse,1.0) * texture(image,vec3(TextureCoords,(blockID-1) * 6 + faceID));
    }else{
        outColor = vec4(diffuse,1.0) * texture(image,vec3(TextureCoords,(blockID-1) * 6 + faceID));

    }
}
