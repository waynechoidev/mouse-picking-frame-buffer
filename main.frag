#version 420

in vec2 TexCoord;
in vec3 posWorld;
in vec3 normalWorld;
in vec3 posModel;

out vec4 colour;

const float PI = 3.14159265359;

layout(std140) uniform Fragment
{
    vec3 viewPosition; // 12    4
    bool useTexture; // 4       0
    // 16
};

layout(std140) uniform Material
{
    float ambient; // 4     0
    float shininess; // 4   4
    float diffuse; // 4     8
    float specular; // 4    12
    // 16
} material;

layout(std140) uniform Light
{
    vec3 position; // 12        0
    float strength; // 4        12
    vec3 direction; // 12       16
    float fallOffStart; // 4    28
    float fallOffEnd; // 4      32
    float spotPower; // 4       36
    int isDirectional; // 4     40
    int isPoint; // 4           44
    int isSpot; // 4            48
    bool useBlinnPhong; // 4      52
    // 56
} light;

uniform sampler2D theTexture;
uniform bool isPicked;
uniform bool useFBO;
uniform vec3 indexColor;

float calcAttenuation(float d, float falloffStart, float falloffEnd)
{
    // Linear falloff
    return clamp((falloffEnd - d) / (falloffEnd - falloffStart), 0.0, 1.0);
}

vec3 blinnPhong(vec3 lightStrength, vec3 lightVec, vec3 normal, vec3 toEye)
{
    if(light.useBlinnPhong)
    {
        vec3 halfway = normalize(toEye + lightVec);
        float hdotn = dot(halfway, normal);
        vec3 specular = vec3(material.specular) * pow(max(hdotn, 0.0f), material.shininess);
        return material.ambient + (vec3(material.diffuse) + specular) * lightStrength;
    }
    else
    {
        vec3 r = -reflect(lightVec, normal);
        vec3 specular = vec3(material.specular) * pow(max(dot(toEye, r), 0.0f), material.shininess);
        return material.ambient + (vec3(material.diffuse) + specular) * lightStrength;    
    }
}

vec3 computeDirectionalLight(vec3 normal, vec3 toEye)
{
    vec3 lightVec = -light.direction;
    
    float ndotl = max(dot(lightVec, normal), 0.0f);
    vec3 lightStrength = vec3(light.strength) * ndotl;
    
    return blinnPhong(lightStrength, lightVec, normal, toEye);
}

vec3 computePointLight(vec3 pos, vec3 normal, vec3 toEye)
{
    vec3 lightVec = light.position - pos;

    float d = length(lightVec);

    if (d > light.fallOffEnd)
    {
        return vec3(0.0);
    }
    else
    {
        lightVec /= d;
        
        float ndotl = max(dot(lightVec, normal), 0.0f);
        vec3 lightStrength = vec3(light.strength) * ndotl;
        
        float att = calcAttenuation(d, light.fallOffStart, light.fallOffEnd);
        lightStrength *= att;
        
        return blinnPhong(lightStrength, lightVec, normal, toEye);
    }
}

vec3 computeSpotLight(vec3 pos, vec3 normal, vec3 toEye)
{
    vec3 lightVec = light.position - pos;

    float d = length(lightVec);

    if (d > light.fallOffEnd)
    {
        return vec3(0.0f);
    }
    else
    {
        lightVec /= d;
        
        float ndotl = max(dot(lightVec, normal), 0.0f);
        vec3 lightStrength = vec3(light.strength) * ndotl;
        
        float att = calcAttenuation(d, light.fallOffStart, light.fallOffEnd);
        lightStrength *= att;
        
        float spotFactor = pow(max(-dot(lightVec, light.direction), 0.0f), light.spotPower);
        lightStrength *= spotFactor;
        
        return blinnPhong(lightStrength, lightVec, normal, toEye);
    }
}

void main()
{
	vec3 toEye = normalize(viewPosition - posWorld);

	vec3 res = vec3(0.0);

    res += computeDirectionalLight(normalWorld, toEye) * light.isDirectional;
    
    res += computePointLight(posWorld, normalWorld, toEye) * light.isPoint;
    
    res += computeSpotLight(posWorld, normalWorld, toEye) * light.isSpot;

    if(useFBO || isPicked) colour = vec4(indexColor, 1.0);
    else colour = useTexture ? vec4(res, 1.0) * texture(theTexture, TexCoord) : vec4(res, 1.0);
}