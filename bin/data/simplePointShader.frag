#version 150

in vec4 vertexColor;
out vec4 fragColor;

void main() {
    vec2 dist = gl_PointCoord.st - vec2(0.5, 0.5);
    float d = length(dist);
    if (d > 0.5)
        discard;

    fragColor = vertexColor;
}