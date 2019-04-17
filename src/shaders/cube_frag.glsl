#version 330 core
out vec4 fragment_color;

uniform vec3 light_position;

in float top;
in vec3 normal;
in vec3 world_position;
in float bt;

float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
float lerp(float t, float a, float b) { return a + t * (b - a); }
float grad(int hash, float x, float y, float z) {
  int h = hash & 15;
  float u = h < 8 ? x : y;
  float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
int perm(int i) { return (int(11927 * sin(20*i + 4)) % 255); }

float perlin3d(float x, float y, float z) {
  x *= 10;
  y *= 10;
  z *= 10;

  int X = int(floor(x)) % 255;
  int Y = int(floor(y)) % 255;
  int Z = int(floor(z)) % 255;

  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  float u = fade(x);
  float v = fade(y);
  float w = fade(z);

  int A = perm(X) + Y;
  int AA = perm(A) + Z;
  int AB = perm(A + 1) + Z;
  int B = perm(X + 1) + Y;
  int BA = perm(B) + Z;
  int BB = perm(B + 1) + Z;

  return lerp(
      w,
      lerp(v, lerp(u, grad(perm(AA), x, y, z), grad(perm(BA), x - 1, y, z)),
            lerp(u, grad(perm(AB), x, y - 1, z),
                grad(perm(BB), x - 1, y - 1, z))),
      lerp(v,
            lerp(u, grad(perm(AA + 1), x, y, z - 1),
                grad(perm(BA + 1), x - 1, y, z - 1)),
            lerp(u, grad(perm(AB + 1), x, y - 1, x - 1),
                grad(perm(BB + 1), x - 1, y - 1, z - 1))));
}

void main() {
  // dirt
  if (bt <= 1.0) {
    float perl_mod = 0.5;
    vec3 col = vec3(0.4392, 0.2824, 0.2353) * 1.0;
    if (top > 0.9) {
      col = vec3(0.3, 0.7, 0.4);
      perl_mod = 0.3;
    }

    vec3 L = normalize(light_position - world_position);
    float kd = 0.75 + 0.25 * dot(L, normal);
    float perl = (1.0 - perl_mod) + perl_mod * perlin3d(world_position.x, world_position.y, world_position.z);
    perl = abs(perl);

    fragment_color = vec4(perl * kd * col, 1.0);
  }
  // water
   else {
    fragment_color = vec4(0.1,0.3,0.7,0.5);
  }

}