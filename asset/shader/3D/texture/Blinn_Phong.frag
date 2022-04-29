/*#########################################################################
# 
###########################################################################*/
#version 420
//#extension GL_ARB_explicit_uniform_location : require

layout(location = 3) in vec3 vPosition;
layout(location = 4) in vec2 vUV;
layout(location = 5) in vec3 vNormal;



uniform vec3 lightPosition;
uniform sampler2D sampleTexture;
uniform vec3 viewPosition;	//カメラ座標


out vec4 fragment;

void main()
{
      
      vec3 color = texture(sampleTexture, vUV).rgb;

      // ambient
      vec3 ambient = 1.00 * color;

      // diffuse
      vec3 lightDir = normalize(lightPosition - vPosition);
      vec3 normal = normalize(vNormal);
      float diff = max(dot(lightDir, normal), 0.0);
      vec3 diffuse = diff * color;

      // specular
      vec3 viewDir = normalize(viewPosition - vPosition);
      vec3 reflectDir = reflect(-lightDir, normal);
      

      vec3 halfwayDir = normalize(lightDir + viewDir);  
      float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);

      
      vec3 specular = vec3(1.0) * spec; // assuming bright white light color
      fragment = vec4(ambient + diffuse + specular, 1.0);
}
