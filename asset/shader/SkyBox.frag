#version 420

out vec4 FragColor;

layout (location = 1) in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{ 
    /*
    if(TexCoords.x == 0.0f)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else if(TexCoords.y == 0.0f)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else if(TexCoords.z == 0.0f)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    */
    
/*
    if(TexCoords.x == 0.0f)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else if(TexCoords.y == 0.0f)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else if(TexCoords.z == 0.0f)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else
    {
        FragColor = vec4(1.0,0.0,0.0,1.0);
    }
*/

/*
    if(texture(skybox,TexCoords).b == 0.0)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else if(texture(skybox,TexCoords).g == 0.0)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    } 
    else if(texture(skybox,TexCoords).b == 0.0)
    {
        FragColor = vec4(0.0,1.0,0.0,1.0);
    }





*/

    if(texture(skybox,TexCoords).r == 0.0f)
    {
//        FragColor = vec4(1.0,0.0,0.0,1.0);
    }
    else if(texture(skybox,TexCoords).g == 0.0f)
    {
//        FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    
    if(texture(skybox,TexCoords).b == 0.0f)
    {
        FragColor = vec4(1.0,0.0,0.0,1.0);
    }
    else
    {
//        FragColor = vec4(1.0,1.0,1.0,1.0);
    }





//    FragColor = vec4(texture(skybox,TexCoords).b,0.0,0.0,1.0);

 //   FragColor = texture(skybox,TexCoords);
}
