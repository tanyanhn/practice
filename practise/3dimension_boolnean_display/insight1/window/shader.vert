R"==(
#version 110
uniform mat4 mvp;
uniform vec4 col;
uniform vec3 cameraPosition;

attribute vec3 pos;
attribute vec3 normal;

varying vec4 color;

void main(){
    vec3 light_direction = vec3(3.0, 3.0, 3.0);

    gl_Position = mvp * vec4(pos, 1.0);

    color = vec4(clamp(dot(normalize(light_direction), normalize(normal)), 0.2, 1.0) * col.xyz, col.w);
}
)==";
