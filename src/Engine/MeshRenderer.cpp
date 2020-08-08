#include <Engine/MeshRenderer.hpp>
#include <stdexcept>

MeshRenderer::MeshRenderer(MeshType modelType){
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

MeshContainer* MeshContainer::instance = 0;

MeshContainer::MeshContainer(): cubeMesh(new MeshRenderer(MeshType::kCube)), 
								sphereMesh(new MeshRenderer(MeshType::kSphere)),
								triangleMesh(new MeshRenderer(MeshType::kTriangle)),
								quadMesh(new MeshRenderer(MeshType::kQuad))
{
}

MeshContainer* MeshContainer::getInstance() {
	if (!instance) {
		instance = new MeshContainer();
		return instance;
	} else {
		return instance;
	}
}

MeshRenderer* MeshContainer::getMesh(MeshType type) {
	switch (type) {
	case MeshType::kCube:
		return cubeMesh;
	case MeshType::kSphere:
		return sphereMesh;
	case MeshType::kTriangle:
		return triangleMesh;
	case MeshType::kQuad:
		return quadMesh;
	default:
		throw std::invalid_argument("type must be a member of MeshType enum"); 
	}
}
