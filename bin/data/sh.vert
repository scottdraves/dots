#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 normal;
in vec4 color;
in vec2 texcoord;

in vec2 screen;
in float pointRadius;
in float lineWidth;

out float geomPointRadius, geomLineWidth;
out vec4 vertexColor;

void main(){
    geomPointRadius = pointRadius;
    geomLineWidth = lineWidth;

    // Throwaways so the data gets bound, there has
    // to be a way around this, but I don't know what it is
    float x = normal.x;
    float c = color.x;
    float t = texcoord.x;

    vertexColor = color;
    gl_Position = modelViewProjectionMatrix * position;
}
