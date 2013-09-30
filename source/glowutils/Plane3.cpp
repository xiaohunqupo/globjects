
#include <cmath>
#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glowutils/Plane3.h>


using namespace glm;

namespace glow 
{

float pointToPlaneDistance(
    const vec3 & location
,   const vec3 & normal
,   const vec3 & point)
{
    assert(length(normal) == 1.f);

    const float distance = length(location);
    return abs(dot(point, normal) - distance);
}

const mat4 rotate(
    const vec3 & a
,   const vec3 & b)
{
    const vec3 anorm(normalize(a));
    const vec3 bnorm(normalize(b));

    const vec3 axis = cross(anorm, bnorm);
    const float angle = acos(dot(anorm, bnorm));

    return mat4_cast(angleAxis(degrees(angle), axis));
}

const mat4 transform(
    const vec3 & location
,   const vec3 & normal)
{
    const vec3 up(0.f, 1.f, 0.f);
    return translate(location) * rotate(normal, up);
}

const vec3 intersection(
	bool & intersects
,   const vec3 & location
,   const vec3 & normal
,	const vec3 & rnear
,	const vec3 & rfar)
{
    // thats root of the ray
	const vec3 & r0 = rnear;

	// a ray direction
	const vec3 r = rfar - rnear;

	// intersect with plane in point normal form
	const float rDotN = dot(r, normal);

	intersects = r != vec3() && rDotN < 0.; // // the later would happen if the intersection is above the "horizon"

	if(!intersects)
		return vec3();

	const float t = dot(location - r0, normal) / rDotN;

	// retrieve point via the ray
	return t * r + r0;
}



} // namespace glow
