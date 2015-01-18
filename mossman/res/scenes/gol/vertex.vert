void main()
{
	gl_TexCoord[0] = gl_Vertex * 2.0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}