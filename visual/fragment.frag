#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Pos;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    if(abs(Pos.x)<0.3  && abs(Pos.y)<0.3){
        FragColor=mix(texture(texture1, vec2(TexCoord.x, -TexCoord.y)), texture(texture2, TexCoord), 0.5);
    } else {
        FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}
