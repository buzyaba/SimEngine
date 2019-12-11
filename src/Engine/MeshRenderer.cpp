#include <Engine/MeshRenderer.hpp>
#include <iostream>

MeshRenderer::MeshRenderer(MeshType modelType){
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	position = glm::vec3(0.0, 0.0, 0.0);

	switch (modelType){

		case kTriangle: Mesh::setTriangleData(vertices, indices); 
			//kTag = kTriangle;
			break;
		case kQuad: Mesh::setQuadData(vertices, indices); 
			//kTag = kQuad; 
			break;
		case kCube: Mesh::setCubeData(vertices, indices);
			//kTag = kCube; 
			break;
		case kSphere: Mesh::setSphereData(vertices, indices); 
			//kTag = kSphere; 
			break;
	}

    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),	&indices[0], GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoords)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

MeshRenderer::~MeshRenderer() {
    
}
