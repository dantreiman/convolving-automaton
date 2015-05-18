
in vec2 position;
out vec2 varTexcoord;

void main()
{
	gl_Position = position;
	varTexcoord = position;
}
