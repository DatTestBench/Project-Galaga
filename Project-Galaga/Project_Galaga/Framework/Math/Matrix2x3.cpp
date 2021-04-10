#include "Matrix2x3.h"


Matrix2x3::Matrix2x3(Vector2f dirX, Vector2f dirY, Vector2f orig)
	: dirX{ dirX }
	, dirY{ dirY }
	, orig{ orig }
{
}

Matrix2x3::Matrix2x3(const float e1X, const float e1Y, const float e2X, const float e2Y, const float oX, const float oY)
	: Matrix2x3{ Vector2f{ e1X, e1Y }, Vector2f{ e2X, e2Y }, Vector2f{ oX, oY } }
{
}

Vector2f Matrix2x3::Transform(const Vector2f& v) const
{
	return Vector2f{ v.x * dirX + v.y * dirY };
}

Point2f Matrix2x3::Transform(const Point2f& p) const
{
	const Vector2f v{ Transform(Vector2f{ p }) + orig };
	return v.ToPoint2f();
}

std::vector<Point2f> Matrix2x3::Transform(const Rectf& r) const
{
	std::vector<Point2f> vertices{ 4 };
	vertices[0] = Transform(Point2f{ r.left, r.bottom });
	vertices[1] = Transform(Point2f{ r.left, r.bottom + r.height });
	vertices[2] = Transform(Point2f{ r.left + r.width, r.bottom + r.height });
	vertices[3] = Transform(Point2f{ r.left + r.width, r.bottom });
	return vertices;
}

void Matrix2x3::Transform(const Rectf& r, Point2f* transVertices) const
{
	transVertices[0] = Transform(Point2f{ r.left, r.bottom });
	transVertices[1] = Transform(Point2f{ r.left, r.bottom + r.height });
	transVertices[2] = Transform(Point2f{ r.left + r.width, r.bottom + r.height });
	transVertices[3] = Transform(Point2f{ r.left + r.width, r.bottom });
}


std::vector<Point2f> Matrix2x3::Transform(const std::vector<Point2f>& vertices) const
{
	const size_t nrVertices{ vertices.size() };
	std::vector<Point2f> transformedVertices{ nrVertices };
	for (size_t idx{ 0 }; idx < nrVertices; ++idx)
		transformedVertices[idx] = Transform(vertices[idx]);
	return transformedVertices;
}

std::vector<Vector2f> Matrix2x3::Transform(const std::vector<Vector2f>& vertices) const
{
	const size_t nrVertices{ vertices.size() };
	std::vector<Vector2f> transformedVertices{ nrVertices };
	for (size_t idx{ 0 }; idx < nrVertices; ++idx)
		transformedVertices[idx] = Vector2f(Transform(vertices[idx].ToPoint2f()));
	return transformedVertices;
}

void Matrix2x3::Transform(const std::vector<Point2f>& vertices, Point2f* transVertices) const
{
	Transform(vertices.data(), transVertices, vertices.size());
}


void Matrix2x3::Transform(const Point2f* vertices, Point2f* transVertices, const size_t nrVertices) const
{
	for (size_t idx{ 0 }; idx < nrVertices; ++idx)
		transVertices[idx] = Transform(vertices[idx]);
}

float Matrix2x3::Determinant() const
{
	return dirX.x * dirY.y - dirX.y * dirY.x;
}

Matrix2x3 Matrix2x3::Inverse() const
{
	//Calculate Determinant
	const float det = Determinant();

	//1)calculate matrix of minors
	//2)Use the alternating law of signs to produce the matrix of cofactors 
	//3)Transpose
	//4)the inverse matrix is 1/Determinant * the resulting matrix
	return Matrix2x3{
		Vector2f(+dirY.y, -dirX.y) / det,
		Vector2f(-dirY.x, +dirX.x) / det,
		Vector2f(dirY.x * orig.y - dirY.y * orig.x, -(dirX.x * orig.y - dirX.y * orig.x)) / det
	};
}

bool Matrix2x3::Equals(const Matrix2x3& other, const float epsilon) const
{
	return dirX.Equals(other.dirX, epsilon) &&
		   dirY.Equals(other.dirY, epsilon) &&
		   orig.Equals(other.orig, epsilon);
}

std::string Matrix2x3::ToString() const
{
	return std::string("Matrix2x3( x( ") +
		   std::to_string(dirX.x) + ", " + std::to_string(dirX.y)
		   + " ), y( " + std::to_string(dirY.x) + ", " + std::to_string(dirY.y)
		   + " ), orig( " + std::to_string(orig.x) + ", " + std::to_string(orig.y) + " )  )";
}

void Matrix2x3::SetAsIdentity()
{
	dirX = Vector2f{ 1, 0 };
	dirY = Vector2f{ 0, 1 };
	orig = Vector2f{ 0, 0 };
}

void Matrix2x3::SetAsRotate(const float degrees)
{
	const float radians = degrees * 3.1415926535f / 180;
	dirX = Vector2f{ cos(radians), sin(radians) };
	dirY = Vector2f{ -sin(radians), cos(radians) };
	orig = Vector2f{ 0, 0 };
}
void Matrix2x3::SetAsTranslate(const float tx, const float ty)
{
	dirX = Vector2f{ 1, 0 };
	dirY = Vector2f{ 0, 1 };
	orig = Vector2f{ tx, ty };
}

void Matrix2x3::SetAsTranslate(const Vector2f pt)
{
	dirX = Vector2f{ 1, 0 };
	dirY = Vector2f{ 0, 1 };
	orig = Vector2f{ pt.x, pt.y };
}

void Matrix2x3::SetAsScale(const float scaleX, const float scaleY)
{
	dirX = Vector2f{ scaleX, 0 };
	dirY = Vector2f{ 0, scaleY };
	orig = Vector2f{ 0, 0 };
}

void Matrix2x3::SetAsScale(const float scale)
{
	SetAsScale(scale, scale);
}

Matrix2x3 Matrix2x3::CreateRotationMatrix(const float degrees)
{
	const float radians = degrees * 3.1415926535f / 180;
	return Matrix2x3(Vector2f{ cos(radians), sin(radians) }, Vector2f{ -sin(radians), cos(radians) }, Vector2f{});
}

Matrix2x3 Matrix2x3::CreateIdentityMatrix()
{
	return Matrix2x3(Vector2f{ 1, 0 }, Vector2f{ 0, 1 }, Vector2f{});
}

Matrix2x3 Matrix2x3::CreateScalingMatrix(const float scale)
{
	return CreateScalingMatrix(scale, scale);
}

Matrix2x3 Matrix2x3::CreateScalingMatrix(const Vector2f scaleVector)
{
	return CreateScalingMatrix(scaleVector.x, scaleVector.y);
}

Matrix2x3 Matrix2x3::CreateScalingMatrix(const float scaleX, const float scaleY)
{
	return Matrix2x3(Vector2f{ scaleX, 0 }, Vector2f{ 0, scaleY }, Vector2f{});
}

Matrix2x3 Matrix2x3::CreateTranslationMatrix(const Vector2f origin)
{
	return Matrix2x3(Vector2f{ 1, 0 }, Vector2f{ 0, 1 }, origin);
}

Matrix2x3 Matrix2x3::CreateTranslationMatrix(const float tx, const float ty)
{
	return CreateTranslationMatrix(Vector2f{ tx, ty });
}

// Operator overloading functionality
bool operator==(const Matrix2x3& lhs, const Matrix2x3& rhs)
{
	return lhs.Equals(rhs);
}

bool operator!=(const Matrix2x3& lhs, const Matrix2x3& rhs)
{
	return !(lhs == rhs);
}

Matrix2x3 operator*(const Matrix2x3& lhs, const Matrix2x3& rhs)
{
	return Matrix2x3{
		Vector2f{ rhs.dirX.x * lhs.dirX.x + rhs.dirX.y * lhs.dirY.x, rhs.dirX.x * lhs.dirX.y + rhs.dirX.y * lhs.dirY.y },
		Vector2f{ rhs.dirY.x * lhs.dirX.x + rhs.dirY.y * lhs.dirY.x, rhs.dirY.x * lhs.dirX.y + rhs.dirY.y * lhs.dirY.y },
		Vector2f{ rhs.orig.x * lhs.dirX.x + rhs.orig.y * lhs.dirY.x + lhs.orig.x, rhs.orig.x * lhs.dirX.y + rhs.orig.y * lhs.dirY.y + lhs.orig.y }
	};
}

std::ostream& operator<<(std::ostream& os, const Matrix2x3& matrix)
{
	os << matrix.ToString();
	return os;
}
