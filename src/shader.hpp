#ifndef LOPOLYN_SHADER_HPP
#define LOPOLYN_SHADER_HPP

#include <string>

auto VERTEX_SHADER_SOURCE = R"(
attribute vec2 a_Coordinate;

varying vec2 v_TextureCoordinate;

vec2 flip(vec2 coordinate) {
  return coordinate * vec2(1.0, -1.0);
}

vec4 toPosition(vec2 coordinate) {
  return vec4(flip(coordinate * 2.0 - 1.0), 0.0, 1.0);
}

void main() {
  gl_Position = toPosition(a_Coordinate);
  v_TextureCoordinate = a_Coordinate;
}
)";

auto FRAGMENT_SHADER_SOURCE = R"(
precision highp float;

uniform sampler2D u_Texture;

varying vec2 v_TextureCoordinate;

void main() {
  gl_FragColor = texture2D(u_Texture, v_TextureCoordinate);
}
)";

#endif//LOPOLYN_SHADER_HPP
