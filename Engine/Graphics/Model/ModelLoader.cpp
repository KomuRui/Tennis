//#include "ModelLoader.h"
//
//bool ModelLoader::Load(std::string filepath, std::vector<ModelData::Node>& nodes)
//{
//	Assimp::Importer importer;
//
//	int flag = 0;
//	flag |= aiProcess_CalcTangentSpace;
//	flag |= aiProcess_Triangulate;
//	flag |= aiProcess_GenSmoothNormals;
//	flag |= aiProcess_PreTransformVertices;
//	flag |= aiProcess_RemoveRedundantMaterials;
//	flag |= aiProcess_GenUVCoords;
//	flag |= aiProcess_OptimizeMeshes;
//
//	const aiScene* pScene = importer.ReadFile(filepath, flag);
//
//	if (pScene == nullptr)
//	{
//		assert(0 && "モデルのファイルが見つかりません");
//		return false;
//	}
//
//	nodes.resize(pScene->mNumMeshes);
//
//	std::string dirPath = GetDirFromPath(filepath);
//
//	for (UINT i = 0; i < pScene->mNumMeshes; i++)
//	{
//		aiMesh* pMesh = pScene->mMeshes[i];
//		aiMaterial* pMaterial = pScene->mMaterials[i];
//		nodes[i].spMesh = Parse(pScene, pMesh, pMaterial, dirPath);
//	}
//
//	return true;
//}
//
//std::shared_ptr<Mesh> ModelLoader::Parse(const aiScene* pScene, const aiMesh* pMesh,
//	const aiMaterial* pMaterial, const std::string& dirPath)
//{
//	std::vector<MeshVertex> vertices;
//	std::vector<MeshFace> faces;
//
//	vertices.resize(pMesh->mNumVertices);
//
//	for (UINT i = 0; i < pMesh->mNumVertices; ++i)
//	{
//		vertices[i].position.x = pMesh->mVertices[i].x;
//		vertices[i].position.y = pMesh->mVertices[i].y;
//		vertices[i].position.z = pMesh->mVertices[i].z;
//
//		if (pMesh->HasTextureCoords(0))
//		{
//			vertices[i].uv.x = static_cast<float>(pMesh->mTextureCoords[0][i].x);
//			vertices[i].uv.y = static_cast<float>(pMesh->mTextureCoords[0][i].y);
//		}
//
//		vertices[i].normal.x = pMesh->mNormals[i].x;
//		vertices[i].normal.y = pMesh->mNormals[i].y;
//		vertices[i].normal.z = pMesh->mNormals[i].z;
//
//		if (pMesh->HasTangentsAndBitangents())
//		{
//			vertices[i].tangent.x = pMesh->mTangents[i].x;
//			vertices[i].tangent.y = pMesh->mTangents[i].y;
//			vertices[i].tangent.z = pMesh->mTangents[i].z;
//		}
//	}
//
//	faces.resize(pMesh->mNumFaces);
//
//	for (UINT i = 0; i < pMesh->mNumFaces; ++i)
//	{
//		faces[i].Idx[0] = pMesh->mFaces[i].mIndices[0];
//		faces[i].Idx[1] = pMesh->mFaces[i].mIndices[1];
//		faces[i].Idx[2] = pMesh->mFaces[i].mIndices[2];
//	}
//
//	std::shared_ptr<Mesh>spMesh = std::make_shared<Mesh>();
//	spMesh->Create(&GraphicsDevice::Instance(), vertices, faces, ParseMaterial(pMaterial, dirPath));
//
//	return spMesh;
//}
//
//const Material ModelLoader::ParseMaterial(const aiMaterial* pMaterial, const std::string& dirPath)
//{
//	Material material = {};
//
//	// マテリアルの名前を取得
//	{
//		aiString name;
//
//		if (pMaterial->Get(AI_MATKEY_NAME, name) == AI_SUCCESS)
//		{
//			material.Name = name.C_Str();
//		}
//	}
//
//	// Diffuseテクスチャの取得
//	{
//		aiString path;
//
//		if (pMaterial->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &path) == AI_SUCCESS)
//		{
//			auto filePath = std::string(path.C_Str());
//
//			material.spBaseColorTex = std::make_shared<Texture>();
//
//			if (!material.spBaseColorTex->Load(dirPath + filePath))
//			{
//				assert(0 && "Diffuseテクスチャのロードに失敗");
//				return Material();
//			}
//		}
//	}
//
//	// DiffuseColorの取得
//	{
//		aiColor4D diffuse;
//
//		if (pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS)
//		{
//			material.BaseColor.x = diffuse.r;
//			material.BaseColor.y = diffuse.g;
//			material.BaseColor.z = diffuse.b;
//			material.BaseColor.w = diffuse.a;
//		}
//	}
//
//	// MetallicRoughnessテクスチャの取得
//	{
//		aiString path;
//
//		if (pMaterial->GetTexture(AI_MATKEY_METALLIC_TEXTURE, &path) == AI_SUCCESS ||
//			pMaterial->GetTexture(AI_MATKEY_ROUGHNESS_TEXTURE, &path) == AI_SUCCESS)
//		{
//			auto filePath = std::string(path.C_Str());
//
//			material.spMetallicRoughnessTex = std::make_shared<Texture>();
//
//			if (!material.spMetallicRoughnessTex->Load(dirPath + filePath))
//			{
//				assert(0 && "MetallicRoughnessテクスチャのロードに失敗");
//				return Material();
//			}
//		}
//	}
//
//	// Metallicを取得
//	{
//		float metallic = 0.0f;
//
//		if (pMaterial->Get(AI_MATKEY_METALLIC_FACTOR, metallic) == AI_SUCCESS)
//		{
//			material.Metallic = metallic;
//		}
//	}
//
//	// Roughness
//	{
//		float roughness = 1.0f;
//
//		if (pMaterial->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness) == AI_SUCCESS)
//		{
//			material.Roughness = roughness;
//		}
//	}
//
//	// Emissiveテクスチャの取得
//	{
//		aiString path;
//
//		if (pMaterial->GetTexture(AI_MATKEY_EMISSIVE_TEXTURE, &path) == AI_SUCCESS)
//		{
//			auto filePath = std::string(path.C_Str());
//
//			material.spEmissiveTex = std::make_shared<Texture>();
//
//			if (!material.spEmissiveTex->Load(dirPath + filePath))
//			{
//				assert(0 && "Emissiveテクスチャのロードに失敗");
//				return Material();
//			}
//		}
//	}
//
//	// Emissiveの取得
//	{
//		aiColor3D emissive;
//
//		if (pMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissive) == AI_SUCCESS)
//		{
//			material.Emissive.x = emissive.r;
//			material.Emissive.y = emissive.g;
//			material.Emissive.z = emissive.b;
//		}
//	}
//
//	// 法線テクスチャの取得
//	{
//		aiString path;
//
//		if (pMaterial->GetTexture(AI_MATKEY_NORMAL_TEXTURE, &path) == AI_SUCCESS)
//		{
//			auto filePath = std::string(path.C_Str());
//
//			material.spNormalTex = std::make_shared<Texture>();
//
//			if (!material.spNormalTex->Load(dirPath + filePath))
//			{
//				assert(0 && "Normalテクスチャのロードに失敗");
//				return Material();
//			}
//		}
//	}
//
//	return material;
//}
