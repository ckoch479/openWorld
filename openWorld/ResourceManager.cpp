#include "ResourceManager.h"

ID ResourceManager::loadMesh(std::string filepath)
{
	MeshData newMesh = loadMeshDataFromFile(filepath);
	ID meshID = meshes.add(newMesh);
	return meshID;
}

MeshData* ResourceManager::getMesh(ID& id)
{
	return &meshes.lookup(id);
}

MeshData ResourceManager::loadMeshDataFromFile(std::string filepath)
{
	std::fstream newfile;
	newfile.open(filepath.c_str(),std::ios::in);

	char fileData;
	

	if (!newfile.is_open())
	{
		std::cout << "ERROR::UNABLE::TO::READ::FILE::AT:" << filepath << std::endl;
	}
		
	if(newfile.is_open())
	{
		while (newfile.good())
		{
			std::string myline;
			std::getline(newfile, myline);
			//fileData = newfile.get();
			std::cout << myline << std::endl;
			
		}
		
	}
	
	//std::cout << fileData << std::endl;

	newfile.close();

	MeshData newMeshdata;

	return newMeshdata;
}